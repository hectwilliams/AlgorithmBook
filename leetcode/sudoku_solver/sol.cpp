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

struct Node {
    int row;
    int col;
    std::string state; 
    int depth;
    EvalListTuple elist_tuple;
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
void concat_board(const SudokuBoard &sb, int &dot_count, std::string &s);

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
  void get_eval_list( const std::string &state, EvalListTuple &elist_tuple);
  
class Solution {

public:
    void solveSudoku(SudokuBoard & board) {
        std::deque<Node*> q; 
        int dot_count; 
        std::string s;
        EvalListTuple elist_tuple;
        
        concat_board(board, dot_count, s);

        q.push_back(new Node{0, 0, s, 0, elist_tuple }); 

        Node *node;

        std::map<int, void *> possible_insert_map =BOARD_PIECES;
        
        while (!q.empty()) {
            
            // pop node from queue
            node = q.front();
            q.pop_front();
            
            if (node->depth ==dot_count) {
                // display_board(node);
                load_sodoku_board(board, node);
                return;
            } else {

                // // search 
                
                // eval list ( updates evaluation list; top of list house positions of empty cells surrounded by non empty cell. This supports faster learning (i.e. easy puzzle pieces are insert first on the board ))
                get_eval_list(node->state /*current board state*/, node->elist_tuple /* get recommend list*/);
                
                // select next unused cell in list 
                std::pair <std::array<int,3> , std::map<int, void *> > pair = node->elist_tuple.front();
                
                std::array<int,3> array_3 = pair.first;
                std::map<int, void *> rec_list = pair.second;
                
                // select empty cell from recommendation list 
                node->row = array_3[0];
                node->col = array_3[1];
                
                // select exclude list from recommendation list
                possible_insert_map.clear();
                possible_insert_map = rec_list;
                
                // clear top of recommendation list 
                node->elist_tuple.erase(node->elist_tuple.begin());
                
               for ( const auto &[index, _]:possible_insert_map ) {
                   
                    // new state case 
                    std::string s_new_state = node->state;
                    // //update state
                    s_new_state[node->row * BOARD_SIDE_LENGTH + node->col ] = std::to_string( index )[0];
                    // new node (next action)
                    Node *new_node = new Node{node->row, node->col, s_new_state, node->depth + 1, node->elist_tuple };
                    q.push_back(new_node);
                    
               }
               
                
                // // run test for current cell 
                // box_test(node,exclude_map );
                // col_test(node,exclude_map );        
                // row_test(node,exclude_map );
            
                // only search nonconflicting values 
            }
            delete node; 
        }
    }
};
void get_eval_list( const std::string &state, EvalListTuple &elist_tuple) {
    elist_tuple.clear();
    int r;
    int c;
    int half = BOARD_SIDE_LENGTH_SQ / 2;
    
    int b = BOARD_SIDE_LENGTH_SQ-1;
    int f = 0;
    bool isOdd = (BOARD_SIDE_LENGTH_SQ % 2 == 1);
    
    for (int i = 0; i < (half + +(isOdd)) ; i++) {
        
        
        r = f / BOARD_SIDE_LENGTH;
        c = f - r * BOARD_SIDE_LENGTH;
        
        if (state[r * BOARD_SIDE_LENGTH + c] == '.') {
            Node test_node{r, c, state, 0,{}};
            std::map<int, void *> exclude_map = BOARD_PIECES;
            box_test(&test_node,exclude_map );
            col_test(&test_node,exclude_map );        
            row_test(&test_node,exclude_map );
            elist_tuple.push_back( { {r, c, static_cast<int>(exclude_map.size()) } , exclude_map }       );
        }
        
        
        r = b / BOARD_SIDE_LENGTH;
        c = b - r * BOARD_SIDE_LENGTH;
        
        if (state[r * BOARD_SIDE_LENGTH + c] == '.') {
            Node test_node{r, c, state, 0,{}};
            std::map<int, void *> exclude_map = BOARD_PIECES;
            box_test(&test_node,exclude_map );
            col_test(&test_node,exclude_map );        
            row_test(&test_node,exclude_map );
            elist_tuple.push_back( { {r, c, static_cast<int>(exclude_map.size()) } , exclude_map }       );
        }
        b--; 
        f++;
        
        
        
        
        
        // r = i / BOARD_SIDE_LENGTH;
        // c = i - r * BOARD_SIDE_LENGTH;
        
        // if (state[r * BOARD_SIDE_LENGTH + c] == '.') {
        //     Node test_node{r, c, state, 0,{}};
        //     std::map<int, void *> exclude_map = BOARD_PIECES;
        //     box_test(&test_node,exclude_map );
        //     col_test(&test_node,exclude_map );        
        //     row_test(&test_node,exclude_map );
        //     elist_tuple.push_back( { {r, c, static_cast<int>(exclude_map.size()) } , exclude_map }       );
        // }
    }
    
    // for (int r = 0; r< BOARD_SIDE_LENGTH; r++) {
    //     for(int c = 0; c < BOARD_SIDE_LENGTH; c++) {
    //     }
    // }    
    
    // sort elist_tuple
    std::sort(elist_tuple.begin(), elist_tuple.end(), [](const std::pair <    std::array<int,3> , std::map<int, void *> > &pair_a , std::pair <    std::array<int,3> , std::map<int, void *> > &pair_b){
        // sort in increasing order
        return pair_a.first[2]  < pair_b.first[2]; 
    });
    
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

 void next_empty_cell(Node *node) {
    int pos = node->row * BOARD_SIDE_LENGTH + node->col;
    while ( ( node->state[pos]  != '.')  && (pos < BOARD_SIDE_LENGTH_SQ )) {
        // move to empty cell in board 
        pos++;
    }
    node->row = pos /BOARD_SIDE_LENGTH;
    node->col = pos - node->row * BOARD_SIDE_LENGTH;
 }


void box_test(Node *node, std::map<int, void *> & emap) {
    int row_box = node->row / 3;
    int col_box = node->col / 3;
    
    int upper_corner_row_box =  row_box* 3;
    int upper_corner_col_box =  col_box* 3;
    
    for(int r = upper_corner_row_box ; r < upper_corner_row_box + 3; r++ ) {
        for(int c = upper_corner_col_box ; c < upper_corner_col_box + 3; c++ ) {
            char character = node->state[r * BOARD_SIDE_LENGTH + c] ;
            int num = character - '0';
            // std::cout << num << "\n";
            if (num >= 1 && num <=BOARD_SIDE_LENGTH) {
                emap.erase(num);
                // emap[num] = nullptr;
            }
        }
    }
    
}

void row_test(Node *node, std::map<int, void *> & emap) {
    for (int c = 0 ; c < BOARD_SIDE_LENGTH; c++) {
        char character = node->state[node->row * BOARD_SIDE_LENGTH + c] ;
        int num = character - '0';
        if (num >= 1 && num <= BOARD_SIDE_LENGTH) {
            // emap[num] = nullptr;
                emap.erase(num);

        }
    }
}

void col_test(Node *node,  std::map<int, void *> & emap) {
        for (int r = 0 ; r < BOARD_SIDE_LENGTH; r++) {
        char character = node->state[r * BOARD_SIDE_LENGTH + node->col] ;
        int num = character - '0';
        if (num >= 1 && num <= BOARD_SIDE_LENGTH) {
            // emap[num] = nullptr;
                emap.erase(num);

        }
    }
}


void concat_board(const SudokuBoard &sb, int &dot_count, std::string &s) {
    dot_count = 0;
    std::map<int, void *> exclude_map;

    // fill state with sudoku chars 
    for (int r = 0; r< BOARD_SIDE_LENGTH; r++) {
        for(int c = 0; c < BOARD_SIDE_LENGTH; c++) {
            s += sb[r][c];
            dot_count += +(sb[r][c] == '.');
        }
    }   
    
 
}
