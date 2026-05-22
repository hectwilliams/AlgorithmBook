/*
 
  Purpose: Solve leetcode problem (NQueens). I have solved this before in the past, but this flow will capture how everything is done in real time.

  
 
  Author: HW 

*/

    

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <array>

const int N_DIRS = 16;

using Qmap = std::vector<std::vector<std::string>>;
using Queens = std::vector<std::array<int,2>>;
using TTable = std::map<std::string, bool>;
using StateTable = std::map<int,  std::map<std::string, int> >;

struct Node {
    int row;
    int col;
    bool state;
    Queens queens ;
};

struct QNode {
    int row;
    int col;
    bool has_queen ;
    QNode *prev;
    std::string state;
    Queens queens;
    std::vector<QNode*> children;
    StateTable to_stable;
};

using Vertices = std::vector< QNode* >;
using VerticesMap = std::map<std::string, QNode*>;
// using Positions = ;

using Children = std::vector<QNode *>;

using Qlist = std::deque<QNode *>;

/**
 * Right diagonal violation test
 * 
 * @param q_row Row location of queen
 * @param q_col Column location of queen 
 * @param target_row Target's row location
 * @param target_col Target's column location
 * @return True - target and queen don't violate chess rules; False - target and queen violate chess rules  
 * 
 */
 bool right_diagonal_valid(int q_row, int q_col, int target_row, int target_col, int n);

 
 /**
 * Left diagonal violation test
 * 
 * @param q_row Row location of queen
 * @param q_col Column location of queen 
 * @param target_row Target's row location
 * @param target_col Target's column location
 * @return True - target and queen don't violate chess rules; False - target and queen violate chess rules  
 * 
 */
 bool left_diagonal_valid(int q_row, int q_col, int target_row, int target_col, int n);

/**
 * Reverse search for vertex and test if transition occured in tree
 * 
 * @param curr_node Pointer to current vertex
 * @param test_has_queen Boolean representing whether queen is places on next possible move
 * @param test_row  Row position of next possible move 
 * @param test_col Col position of next possible move 
 * @return True - no loop found; false - loop found 
 */
 bool loop_test(QNode *curr_node, bool test_has_queen, int test_row, int test_col);

/**
 * Position row,col resides within limits of n square matrix
 * 
 * @param row Row location of queen 
 * @param col Column location of queen
 * @return True position is within bounds of grid; False position exceeds or hit boundary edge 
 */
 bool within_bound_test( int row, int col, int n);
 
 
 /**
 * Determines if next move (w/ queen) placement is valid 
 * 
 * @param curr_node Pointer to current node 
 * @param next_node Pointer to next node 
 * @return True - next move can place queen on board; False - next move violates rules 
*/
bool valid_queen_test(QNode *curr_node, QNode *next_node, int n );

/** Sets state id string from current node in tree 
 * 
 * @param node Pointer to current node 
 * @param n Size of matrix 
 * @param queen_tally String mapping of queens on board
 * @returns Boolean indicating a safe or bad test 
 */
std::string get_state(QNode *node, int n, std::string queen_tally); 


/**
* Generate string containing whether queen was places, and position of current node
* 
* @param node Pointer to current node 
* @returns string encode
*/
std::string get_state_id(QNode *node);

/**
* Test whether state has left cell more than once
* 
* @param curr_node Pointer to current node
* @param row Row of next move
* @param col Column of next move 
* @param has_queen Indicates if next move places queen on board
* @returns Boolean indicating whether or not state has occured 
*/
bool egress_test(QNode *curr_node, int row, int col, bool has_queen );

/**
* Print positions of queens at node 
* 
* @param node Pointer to node 
*/

void print_queens(QNode *node);

const std::array<int , 18> DIRS = { 0,0, 1, 0 /*up*/, -1, 0/*down*/, 0,1 /*right*/, 0,-1 /*left*/, -1,1/*diag forward (up)*/, 1,-1/*diag forwar(down)*/, -1,-1/*diag back (up)*/,  1,1/*diag back (up)*/};

const int STATES[2] = {0, 1};

class Solution {
    
    QNode  *root;
    TTable queen_tally_table;
    // VerticesMap verticesmap;

    /**
    * Builds network for NQueens; a traversable tree
    * 
    * @param n Size of chess grid 
    * 
    */
    void build_network(int n) {
        
        Qlist q;
        TTable table;
        std::string queen_tally;
        
        // queen tally
        for(int i = 0; i< n *n; i++) {queen_tally += ".";}
            
        // load root children
        for(int i = 0; i < root->children.size(); i++) {
            root->children[i]->state = queen_tally;
            // verticesmap[  get_state_id(root->children[i]) ] = root->children[i];
            q.push_back( root->children[i] );
        }
        
        while (!q.empty()) {
            QNode *curr_node = q.front();
            q.pop_front();
            
            if (curr_node->queens.size() == n) {
                int index = (curr_node->state.find("]"));
                std::string s_temp = curr_node->state.substr(index + 1, curr_node->state.size());
                if (queen_tally_table.count(s_temp) == 0) {
                    queen_tally_table[s_temp] = true;
                }  else {
                    continue;
                }
            }
            
           
            for(int k = 0; k < 2; k++) {
                bool next_has_queen = static_cast<bool>(k);
                for (int i = 0; i < N_DIRS ; i+=2) {
                    int next_row = DIRS[i] + curr_node->row;
                    int next_col= DIRS[i + 1] + curr_node->col;
                
                    QNode * new_node = new QNode{next_row, next_col, next_has_queen, curr_node, curr_node->state, curr_node->queens, {}, {}};
                    
                    if (within_bound_test(next_row, next_col, n)) {
                   
                        if (loop_test(curr_node, next_has_queen, next_row, next_col)) {
                            
                            std::string s_test = get_state(new_node, n, queen_tally);
                            if (table.count(s_test)  != 0) {
                                // is this a past experience?
                                delete new_node;
                                continue;   
                            } 

                            if (next_has_queen) { 
                                // non-queen move/set operation

                                if ( valid_queen_test(curr_node, new_node, n) ) {
                                    // queen set is valid                                                                        
                                    new_node->queens.push_back({next_row, next_col});
                                    // std::cout << curr_node->to_stable.size() << "\t" << curr_node->row << "\t" << curr_node->row    << "\t" << new_node->queens.size() << "\n";
                                    // set experience identfication string map
                                    std::string s_id = get_state(new_node, n, queen_tally);
                                    new_node->state = s_id;
                                    // add to child of current node
                                    curr_node->children.push_back(new_node);
                                    // add to queue for re-analysis 
                                    q.push_back(new_node);
                                    // add to state buffer network
                                    table[s_id] = true;
                                    
                                } else {
                                    delete new_node; 
                                }
                            } else {
                                // non-queen move/set operation
                                
                                // add to current node children
                                curr_node->children.push_back(new_node);
                                // add to queue for re-analysis 
                                q.push_back(new_node);
                                // add to state buffer network
                                table[s_test] = true; // use test ident because no queen was placed
                                // verticesmap[  get_state_id(new_node) ] = new_node;
                            }
                    
                        } 
                    }
                }
            }
        }
        
    }
    
    /**
     * Split identifcation map into string of rows
     * 
     * @param s_id Identifcation map
     * @param n size of board
     * @returns vector of string representing Q position on 2D N grid
     */
    

    std::vector<std::string> repr(const std::string &s_id, int n) {
        std::vector<std::string> result;
        std::string s;
        
        int k = 0;
        int m = 0;
        while (m < s_id.length() ) {
            
            s += s_id[m];
            k+=1;
            m+= 1;
            if (n == k) {
                k = 0;
                result.push_back(s);
                s = "";
            }
        }
        
        return result;
    }
    
    
public:
    ~Solution() {}
    
    
    Solution() {
        root = new QNode{   -1, -1, false, nullptr, "", {}, {  new QNode{0, 0, true, nullptr, "" , {},  {}} ,  new QNode{0, 0, false, nullptr, "", {},  {} }}    };
    }
    
    Qmap solveNQueens(int n) {
         Qmap qmap;
         build_network(n);
         
         for(const auto & [key, _]: queen_tally_table) {
             std::vector<std::string> s_array = repr(key, n);
             qmap.push_back(s_array);
         }
         
        return qmap;
    }
    
};


std::string get_state_id(QNode *node) {
    std::string s = "<" + std::to_string(node->has_queen)  +">-" + "["   + std::to_string(node->row) + "," + std::to_string(node->col) +   "]";
    return s;
}

std::string get_state(QNode *node,int n, std::string queen_tally) {
    std::string q_rep = queen_tally; 
    std::string s = get_state_id(node);
    int row;
    int col;
    
    for (const auto &pos : node->queens ) {
        row = pos[0];
        col = pos[1];
        q_rep[(row * n) + col] = 'Q'; 
    }
    return s + q_rep ;
}

 bool within_bound_test( int row, int col, int n) {
    return ! (row < 0 || row >= n || col < 0 || col >=n );
 }
 
 void print_queens(QNode *node) {
     
     std::string s;
     for (const auto  &queen: node->queens) {
         s += "["  + std::to_string(queen[0]) + "," +  std::to_string(queen[1])  + "]\t";
     }
     std::cout << s << "\n";
 }

 bool loop_test(QNode *curr_node, bool test_has_queen, int test_row, int test_col) {
    QNode *child_eval_node = curr_node;
    QNode *parent_eval_node;
    
    std::map<QNode*, int> map;
        
    if (curr_node->prev) {
        
        if ( (curr_node->prev->has_queen == test_has_queen) && (curr_node->prev->row == test_row) && (curr_node->prev->col == test_col) )
            return false;
    }
        
    while (child_eval_node->prev) {
        
        parent_eval_node = child_eval_node->prev;
        
        if (parent_eval_node->row == -1 && parent_eval_node->col == -1) {
            // root node reach, do not evaluate this node
            break;
        }
        
        if( (parent_eval_node->row == curr_node->row)    &&   (parent_eval_node->col == curr_node->col)   &&   (parent_eval_node->has_queen == curr_node->has_queen)   &&   (child_eval_node->row == test_row)   &&  (child_eval_node->col == test_col)   &&   (child_eval_node->has_queen == test_has_queen)  ) {
            // transition has occurred in tree
            return false;
        }
        
        if (map.count(child_eval_node) == 0) {
            map[child_eval_node] = 0;
        }
        
        map[child_eval_node] += 1;
        
        if (map[child_eval_node] > 1) {
            return false;
        }
        
        child_eval_node = child_eval_node->prev;
    }
    return true;
 }

bool egress_test(QNode *curr_node, int row, int col, bool has_queen ) {
    
    
    int index = (curr_node->state.find("]"));
    
    int q_id = static_cast<int>(has_queen);
    
    std::string q_tally = curr_node->state.substr(index + 1, curr_node->state.size());
    
    std::string pos_string = std::to_string(row) + "," + std::to_string(col) + "," + q_tally;
    
    // std::cout << pos_string << "\n";
    
    if (curr_node->to_stable.count(q_id) == 0 ) {
        curr_node->to_stable[q_id] = {};
    } 
        
    if (curr_node->to_stable[q_id].count(pos_string)== 0 ) {
        curr_node->to_stable[q_id][pos_string] = 0;
    } 
    
    curr_node->to_stable[q_id][pos_string] = curr_node->to_stable[q_id][pos_string] + 1;
    
    if ( curr_node->to_stable[q_id][pos_string]  > 1)
        return false; 
        
    return true;
}

bool right_diagonal_valid(int q_row, int q_col, int target_row, int target_col, int n) {
    int walk_pos_up[2] = {-1,1};
    int walk_pos_down[2] = {1,-1};
    bool up_hit = false;
    bool down_hit= false;
    
    while ( (+up_hit + +down_hit) != 2 ) {
        
        if ( (target_row + walk_pos_up[0] >= n)   || (target_row + walk_pos_up[0] <0) ||   (target_col + walk_pos_up[1] >= n)   || (target_col + walk_pos_up[1] <0) ) {
                up_hit = true;
        } else {
            
            if ((q_row == target_row  + walk_pos_up[0]) &&  (q_col == target_col  + walk_pos_up[1]))
                return false;
            
            walk_pos_up[0] += -1;
            walk_pos_up[1] += 1;
        }
        
        if ( (target_row + walk_pos_down[0] >= n)   || (target_row + walk_pos_down[0] <0) ||   (target_col + walk_pos_down[1] >= n)   || (target_col + walk_pos_down[1] <0) ) {
                down_hit = true;
        } else {
            
            if ((q_row == target_row  + walk_pos_down[0]) && (q_col == target_col  + walk_pos_down[1]))
                return false;
                
            walk_pos_down[0] += 1;
            walk_pos_down[1] += -1;
        }
        
    }
    
    return true;
}

bool left_diagonal_valid(int q_row, int q_col, int target_row, int target_col, int n) {
    int walk_pos_up[2] = {-1,-1};
    int walk_pos_down[2] = {1,1};
    bool up_hit = false;
    bool down_hit = false;
    
    
    while ( (+up_hit + +down_hit) != 2 ) {
        
        if ( (target_row + walk_pos_up[0] >= n)   || (target_row + walk_pos_up[0] <0) ||   (target_col + walk_pos_up[1] >= n)   || (target_col + walk_pos_up[1] <0) ) {
                up_hit = true;
        } else {
            
            if ((q_row == target_row  + walk_pos_up[0]) &&  (q_col == target_col  + walk_pos_up[1]))
                return false;
            
            walk_pos_up[0] += -1;
            walk_pos_up[1] += -1;
        }
        
        if ( (target_row + walk_pos_down[0] >= n)   || (target_row + walk_pos_down[0] <0) ||   (target_col + walk_pos_down[1] >= n)   || (target_col + walk_pos_down[1] <0) ) {
                down_hit = true;
        } else {
            
            if ((q_row == target_row  + walk_pos_down[0]) && (q_col == target_col  + walk_pos_down[1]))
                return false;
                
            walk_pos_down[0] += 1;
            walk_pos_down[1] += 1;
        }
        
    }
    
    return true;
}

bool valid_queen_test(QNode *curr_node, QNode *next_node, int n ) {
    
    for (const auto &queen_pos: curr_node->queens) {
        int q_row = queen_pos[0];    
        int q_col = queen_pos[1];
        
        if (q_row== next_node->row) 
            return false;
    
        if (q_col == next_node->col)
            return false;
    
        
        if (!left_diagonal_valid(q_row, q_col, next_node->row, next_node->col, n)){
            return false;
        }
        
        if (!right_diagonal_valid(q_row, q_col, next_node->row, next_node->col,n)){
            return false;
        }
    }
    
    return true;
}

int main() {
    
 
    Solution sol = Solution();
    auto result  = sol.solveNQueens(6);
    
    for (const auto &qsol: result) {
        std::cout << "------" << '\n' ;
        for (const auto & sline: qsol) {
            std::cout << "\n"   << sline << '\n';
        }
    }
    
}
