/*
  Purpose: Sudoku solver (leetcode problem) 

  Author: HW 

*/

#include <iostream>
#include <string>
#include <stack>
#include <utility>
#include <map>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <functional>
#include <thread>
#include <mutex>

constexpr int BOARD_SIDE_LENGTH = 9;
constexpr int BOARD_SIDE_LENGTH_SQ = BOARD_SIDE_LENGTH * BOARD_SIDE_LENGTH;
const std::map<int, void *> BOARD_PIECES {
    {1,nullptr},
    {2,nullptr},
    {3,nullptr},
    {4,nullptr},
    {5,nullptr},
    {6,nullptr},
    {7,nullptr},
    {8,nullptr},
    {9,nullptr}
};


// Evaluated at compile time

using SudokuBoard  = std::vector< std::vector<char> >;

using EvalListTuple = std::vector<   std::pair <    std::array<int,3> , std::map<int, void *> > > ;

using BoxMap = std::map<int, std::map<int, void*>>;

using ColumnMap = std::map<int, std::map<int, void*>>;
using RowMap = std::map<int, std::map<int, void*>>;

using WriteMap = std::map<int, std::vector<int> >;

using Binny = std::map<int, std::map<int, int>  >;

using ThreadList = std::vector<std::thread>; 

struct Node {
    int row;
    int col;
    std::string state; 
    int depth;
    BoxMap box_map;
    RowMap row_map;
    ColumnMap column_map; 
    std::map<int, std::map<int, void *> > used;
    std::vector<int> used2;
    Binny binRow;
    Binny binCol;
    Binny binBlock;

};

/**
 * Loads box numerical values into dict-style map
 */
void box_test(Node *node,  std::map<int, void *> & emap) ;

/**
 * Loads row values to dict-style map
 */
void row_test(Node *node,  std::map<int, void *> & emap) ;

/**
 * Loads col values to dict-style map
 */
void col_test(Node *node,  std::map<int, void *> & emap) ;

/**
 * Concat board's characters
 */
void concat_board(const SudokuBoard &sb, int &dot_count, Node *const node);
/**
 * Get next empty cell on board
 */
 void next_empty_cell(Node *node);
 
 /**
  * Read node's board state and print 2D board
  */
 void display_board(Node *node);
 
 /**
  * Read node's board state and print 2D board
  */
 void load_sodoku_board(SudokuBoard &board, Node *node);
 
 /**
  * Update node's eval list
  * 
  * @param state Board state 
  * @param elist Sorted evaluation (next best empty cell to eval) list  
  */
//   void get_eval_list( const std::string &state, EvalListTuple &elist_tuple);
  void get_eval_list(  Node * const node);

  /**
   * Convert row,column location to linear position
   */
  int get_1D_pos(Node *node);
  
  /** 
   * Get Box ID
   * 
  */
  int get_box_id(int row, int col);
  
  /** 
   * Converts row, col to upper left corner of box
   * 
  */
  std::array<int,2> get_box_2D(int row, int col);
  
   /** 
   * Converts row, col to position on sudoku board
   * 
  */
  std::array<int,2> pos_to_rc(int pos) {
    int row = pos /BOARD_SIDE_LENGTH;
    int col = pos - (row * BOARD_SIDE_LENGTH)    ;
    return {row, col};
}

  /** 
   * Calculates number of neighbors ( non-dot) at position on board 
   * 
  */
int n_neighbors(Node *node, int pos) {
    std::array<int,2> data = pos_to_rc(pos);
    int r = data[0];
    int c = data[1];
    int box_id = get_box_id(r, c);
    
    std::map<int, void*> tmp;
    
    tmp.insert(node->box_map[box_id].begin(), node->box_map[box_id].end() );
    
    tmp.insert(node->column_map[c].begin(), node->column_map[c].end() );
    
    tmp.insert(node->row_map[r].begin(), node->row_map[r].end() );
    
    return tmp.size();
}

  /** 
   * Sort positions vector used to move the position on board with most neihghors to hear of array
   * 
  */
void sort_used(Node *node) {
    std::sort( node->used2.begin(), node->used2.end(),
    [node](const int &dot_pos_a, const int &dot_pos_b){
        // sort using size of node->used mapped list
        std::map<int, void*> list1 = node->used[dot_pos_a];
        std::map<int, void*> list2 = node->used[dot_pos_b];
        return list1.size() < list2.size();
    });
}

class Solution {

public:
    void solveSudoku(SudokuBoard & board) {
        std::deque<Node*> q; 
        int dot_count; 
        std::string s;
        // std::mutex mtx; 
        
        std::map<int, std::map<int, void *> > used;
        Node * node = new Node{0, 0,  "", 0, {}, {}, {}, {}, {}, {}, {}  };
        concat_board(board, dot_count, node);
        get_eval_list(node); // ->state /*current board state*/, node->elist_tuple /* get recommend list*/
        q.push_back(node); 
        
        while (!q.empty()) {
            // pop node from queue
            node = q.front();
            q.pop_front();
            
            if (node->depth == dot_count) {
                display_board(node);
                load_sodoku_board(board, node);
                return;
            } else {
                
                int best_pos = node->used2.front();
                std::map<int, void *> list = node->used[best_pos];
                
                node->used2.erase(node->used2.begin());
                std::array<int,2> data = pos_to_rc(best_pos);
                int r = data[0];
                int c = data[1];
                int box_id = get_box_id(r, c);
                
                for (const auto &[value, _] : list ){
                    std::string s = node->state;
                    s[ best_pos ] = value + '0';
                    Node *new_node = new Node{r, c, s, node->depth + 1, node->box_map, node->row_map , node->column_map, node->used , node->used2 , node->binRow , node->binCol, node->binBlock };
                    // continue search with newly added entry
                    new_node->box_map[box_id][value] = nullptr;
                    new_node->row_map[r][value] = nullptr;
                    new_node->column_map[c][value] = nullptr;
                    new_node->binRow[r][value] += 1;
                    new_node->binCol[c][value] +=1;
                    new_node->binBlock[ box_id ][value] += 1;
                    
                    if (new_node->binRow[r][value]  <= 1 && new_node->binCol[c][value]  <= 1 &&  node->binBlock[ box_id ][value]  <= 1) {
                        get_eval_list(new_node);
                        q.push_back(new_node);
                    }
                } 
                        
            }
            delete node; 
        }
    }
};



void get_eval_list(  Node * const node) {
    int r;
    int c;
    int before;
    int after;
    int hit = 0;

    std::map<int, void *> tmp;
    
    for (int i = 0; i < node->used2.size(); i++) {
        
        int pos_key = node->used2[i];
        std::array<int,2> rc = pos_to_rc(pos_key);
        
        int r = rc[0];
        int c = rc[1];
        
        int box_id = get_box_id(r,c);
        
        tmp.insert(node->box_map[box_id].begin(), node->box_map[box_id].end() );

        tmp.insert(node->column_map[c].begin(), node->column_map[c].end() );

        tmp.insert(node->row_map[r].begin(), node->row_map[r].end() );
        
        for (auto [x, y] :  tmp ) {
            // exclude_map.erase(x);
            before = node->used[pos_key].count(x);
            node->used[pos_key].erase(x);
            after = node->used[pos_key].count(x);
            hit += (before != after);
        }
        
        tmp.clear();
    }
    
    if (hit >0)
        sort_used(node);

  }
  
 void load_sodoku_board(SudokuBoard &board, Node *node) {
     int k = 0;
     std::vector<char> char_list;
     int index = 0;
     for (int i =0 ; i < BOARD_SIDE_LENGTH_SQ; i++) {
         char c = node->state[i];
         char_list.push_back( c );
         // replace board sub-list 
         k += 1;
         if (k == BOARD_SIDE_LENGTH ) {
            board[index] = char_list;
            k = 0;
            char_list.clear();
            index += 1;
         }
     }
 }

 void display_board(Node *node) {
     int k = 0;
     for (int i =0 ; i< BOARD_SIDE_LENGTH_SQ; i++) {
         std::cout << node->state[i] << " ";
         k += 1;
         if (k == BOARD_SIDE_LENGTH ) {
             k = 0;
             std::cout << "\n";
         }
     }
 }

int get_box_id(int row, int col) { 
    int row_box = row / 3;
    int col_box = col / 3;
    return (row_box*3  + col_box) + 1;
}

std::array<int,2> get_box_2D(int row, int col) {
    int row_box = row / 3;
    int col_box = col / 3;
    
    // int upper_corner_row_box =  row_box;
    // int upper_corner_col_box =  col_box* ;
    
    return {row_box, col_box};
}

void concat_board(const SudokuBoard &sb, int &dot_count, Node * const node) {

    dot_count = 0;
    std::map<int, void *> exclude_map;

    // fill state with sudoku chars 
    for (int r = 0; r< BOARD_SIDE_LENGTH; r++) {
        for(int c = 0; c < BOARD_SIDE_LENGTH; c++) {
            node->state += sb[r][c];
            dot_count += +(sb[r][c] == '.');
            int box_id = get_box_id(r, c);
            std::array<int,2> box_upper = get_box_2D(r, c);
            
            int value = sb[r][c] - '0';
            
            // bin maps
            if (node->box_map.count(box_id) == 0) {
                node->box_map[box_id] = {};
            }
            
            if (node->row_map.count(r) == 0) {
                node->row_map[r] = {};
            }
            
            if (node->column_map.count(c) == 0) {
                node->column_map[c] = {};
            }
            
            
            // set up bins 
            
                // Row Case
            if (node->binRow.count(r) == 0)
                node->binRow[r] = {};
            
            if(node->binRow[r].count(value) == 0) 
                node->binRow[r][value] = 0;
                
            //  Column Case
            if (node->binCol.count(c) == 0)
                node->binCol[c] = {};
            
            if(node->binCol[c].count(value) == 0) 
                node->binCol[c][value] = 0;
            
            
            // binBox Case
            
            if (node->binBlock.count(box_id) == 0 )
                node->binBlock[ box_id ] = {};
                
            if (node->binBlock[box_id].count(value) == 0 )
                node->binBlock[ box_id ][value] = 0;
                
            
            if (sb[r][c] != '.') {
                
                // bin maps 
                if (node->box_map.count(box_id)) {
                    node->box_map[box_id][value] = nullptr;
                }
                
                if (node->row_map.count(r)) {
                    node->row_map[r][value] = nullptr;
                }
                
                if (node->column_map.count(c)) {
                    node->column_map[c][value] = nullptr;
                }
                
                // BinRow
                node->binRow[r][value] += 1;
                //BinCol
                node->binCol[c][value] +=1;
                // BinBlock
                node->binBlock[ box_id ][value] += 1;
                    
            }  else {
                
                node->used[r *BOARD_SIDE_LENGTH + c] = BOARD_PIECES;
                node->used2.push_back(r *BOARD_SIDE_LENGTH + c);
            }
            
        }
        
    }
    
    // for (const auto [row, c_data]: node->binRow) {
        
    //     std:: cout << row << ": "<< "\n";
        
    //     for (const auto [  col , count ] : c_data  ) {
            
    //         std::cout << col << " " << count << "\n";
    //     } 
    //     std::cout << "\n";
        
    // }
    
    
    //   for (const auto [col, r_data]: node->binCol) {
        
    //     std:: cout << col << ": "<< "\n";
        
    //     for (const auto [  row , count ] : r_data  ) {
            
    //         std::cout << row << " " << count << "\n";
    //     } 
        
    // }
    
        

}

int main() {
    Solution sol = Solution();
   
    SudokuBoard board{
        {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
        }
    };
    
    
    board = {
        
    {'.','.','3','.','.','.','.','.','.'}, 
    
    {'4','.','.','.','8','.','.','3','6'}, 
    
    {'.','.','8','3','.','.','1','.','.'}, 
    
    {'.','4','.','.','6','.','.','7','3'}, 
    
    {'.','.','.','9','.','.','.','1','.'}, 
    
    {'.','.','.','.','.','2','.','.','.'}, 
    
    {'.','.','4','.','7','.','.','6','8'}, 
    
    {'6','.','.','.','.','.','.','.','.'}, 
    
    {'7','.','.','.','.','.','5','.','.'}
};
    
    // [[".",".",".",".",".",".",".",".","."],
    // [".","9",".",".","1",".",".","3","."],
    // [".",".","6",".","2",".","7",".","."],
    // [".",".",".","3",".","4",".",".","."],
    // ["2","1",".",".",".",".",".","9","8"],
    // [".",".",".",".",".",".",".",".","."],
    // [".",".","2","5",".","6","4",".","."],
    // [".","8",".",".",".",".",".","1","."],
    // [".",".",".",".",".",".",".",".","."]]
    
    
    sol.solveSudoku(board);
    // for (const auto this_board: board) {
    //     for (const auto c: this_board) {
    //         std::cout << c <<"," << "\n";
    //     }
    //     std::cout << "\n";
    // }
    
}
