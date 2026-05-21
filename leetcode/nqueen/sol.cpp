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
using TTable = std::map<std::string, bool>;
using Queens = std::vector<std::array<int,2>>;
using TTable = std::map<std::string, bool>;

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
    std::vector<QNode*> children;
};

using Vertices = std::vector< QNode* >;
// using Positions = ;

using Children = std::vector<QNode *>;

using Qlist = std::deque<QNode *>;

/**
 * Test possibility of jump from current node position to next position 
 * 
 * @param node - Pointer to Node 
 * @param next_state State of cell 
 * @param row Row 
 * @param col Column 
 * @param n N size of matrix
*/
bool test_move(Node *node, int next_state, int row, int col , int n, const TTable & table );


/**
 * Generates transition log of occurred state transitions
 * 
 * @param node Pointer to Node
 * @param next_state State of cell
 * @param row Row
 * @col Column 
 * 
 */
std::array<std::string,2> get_transition_log (Node *node, int next_state, int row, int col);

/**
 * Returns whether a loop has been found during search
 * 
 * @param node Pointer to Node
 * @param next_state State of cell
 * @param row Row
 * @param col Column 
 */
bool has_loop(Node *node, int next_state, int row, int col, const TTable &table ) ;

 /**
  * parses queens list and create a string concatenation of positions on board
  * 
  * @param node Pointer to node
  */
 std::string queens_info(Node * node);
 

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
 * @param curr_node - Pointer to current node 
 * @param next_node - Pointer to next node 
 * @return True - next move can place queen on board; False - next move violates rules 
*/
bool valid_queen_test(Node *curr_node, Node *next_node );

const std::array<int , 16> DIRS = { 1, 0 /*up*/, -1, 0/*down*/, 0,1 /*right*/, 0,-1 /*left*/, -1,1/*diag forward (up)*/, 1,-1/*diag forwar(down)*/, -1,-1/*diag back (up)*/,  1,1/*diag back (up)*/};

const int STATES[2] = {0, 1};

class Solution {
    
    QNode  *root;
    Vertices vertices;
    
    /**
    * Traverses tree in search of current path
    * 
    */
    // bool path_exists(Node *prev, Node *curr) {}
    
    /**
    * Builds network for NQueens; a traversable tree
    * 
    * @param n Size of chess grid 
    * 
    */
    void build_network(int n) {
        
        Qlist q;
        
        // load root children
        for(int i = 0; i < root->children.size(); i++) {
            q.push_back(root->children[i]);
        }
        
        // 
        while (!q.empty()) {
            QNode *curr_node = q.front();
            q.pop_front();
            // 
            for(int k = 0; k < 2; k++) {
                bool next_has_queen = static_cast<bool>(k);
                for (int i = 0; i < N_DIRS; i+=2) {
                    int next_row = DIRS[i];
                    int next_col= DIRS[i + 1];
                    if (within_bound_test(next_row, next_col, n)) {
                        if (loop_test(curr_node, next_has_queen, next_row, next_col)) {
                            // if (
                            return;
                            QNode *new_node = new QNode{next_row, next_col, next_has_queen, curr_node,{}};
                            // add to child of current node 
                            curr_node->children.push_back(new_node);
                            // add to queue to potentially increase size of network 
                            q.push_back(new_node);
                        }
                    }
                }
            }
        }
    }
    
    
public:
    ~Solution() {
        
    }
    
    Solution() {
        root = new QNode{-1, -1, false, nullptr, {  new QNode{0, 0, true, nullptr,  {}} ,  new QNode{0, 0, false, nullptr,  {}}} };
        vertices.push_back(root->children[0]);
        vertices.push_back(root->children[1]);
    }
    
    Qmap solveNQueens(int n) {
         Qmap qmap;
         build_network(n);
         

        return qmap;
    }
};


std::array<std::string,2> get_transition_log (Node *node, int next_state, int row, int col) {
    std::array<std::string,2> ret{std::string{}, std::string{}};
    
    std::string q_info = queens_info(node);
 // test_encoding
    ret[0] = "from: "+ std::to_string(node->state) + "<" + std::to_string(node->row)  + "," + std::to_string(node->col)  + ">"  +  "\tto " +  std::to_string(next_state)+ "<" + std::to_string(row)  + "," + std::to_string(col)  + ">" ;
    ret[0] += "----------" + q_info;
    ret[1] = "from: "+ std::to_string(next_state) + "<" + std::to_string(row)  + "," + std::to_string(col)  + ">"  +  "\tto " +  std::to_string(node->state)+ "<" + std::to_string(node->row)  + "," + std::to_string(node->col)  + ">" ;    
    ret[1] += "----------" + q_info;
    return ret;
}

std::string queens_info(Node * node) {
    std::string s;
    s+= "[[";
    for (auto  &queen_pos: node->queens) {
        int q_row = queen_pos[0];
        int q_col = queen_pos[1];
        s+="{{{{";
        s+= std::to_string(q_row);
        s+= ",";
        s+= std::to_string(q_col);
        s+="}}}}";
    }
    s+= "]]";
    return s;
}

 bool within_bound_test( int row, int col, int n) {
    return ! (row < 0 || row >= n || col < 0 || col >=n );
     
     
 }

 bool loop_test(QNode *curr_node, bool test_has_queen, int test_row, int test_col) {
    QNode *child_eval_node = curr_node;
    QNode *parent_eval_node;

    while (child_eval_node->prev) {
        parent_eval_node = child_eval_node->prev;
        if( (parent_eval_node->row == curr_node->row)    &&   (parent_eval_node->col == curr_node->col)   &&   (parent_eval_node->has_queen == curr_node->has_queen)   &&   (child_eval_node->row == test_row)   &&  (child_eval_node->col == test_col)   &&   (child_eval_node->has_queen == test_has_queen)  ) {
            // transition has occurred in tree
            return false;
        }
        child_eval_node = child_eval_node->prev;
    }
    return true;
 }

bool has_loop(Node *node, int next_state, int row, int col, const TTable &table ) {
    std::array<std::string,2>  t = get_transition_log(node, next_state, row, col);
    std::string s_test;
    // check for repeat experience
    if ( table.count(t[0]) > 0  ||  table.count(t[1]) > 0) {
        // transition has occurred in the past
        return true; 
    }
    
    // // check for repeating queen placement
    // s_test = "{{{{" + std::to_string(row)  + "," + std::to_string(col) + "}}}}";
    // for(const auto &[key, _]: table) {
    //     if (key.find(s_test) != std::string::npos) {
    //         // found match
    //         std::cout << s_test << "\n";
    //         return true;
            
    //     }
    // }
    
    return false;
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

bool valid_queen_test(Node *curr_node, Node *next_node ) {
    
    if (curr_node->row == next_node->row) 
        return false;
    
    if (curr_node->col == next_node->col)
        return false;
    
    // if (left_diagonal_valid(curr->) ) {
        
    // }
    return true;
}


bool test_move(Node *node, int next_state, int row, int col, int n, const TTable &table ) {
    
    for (const auto &row_col: node->queens ) {
        int q_row = row_col[0];
        int q_col= row_col[1];
        
        // row test 
        if (row == q_row) 
            return false;
        
        // column test 
        if (col == q_col)
            return false;
            
        // back diagonal (\)
        if (node->queens.size()==2) {
            // std::cout << " ROW  "  << row << " COL " << col << "\n"; 
        }
        if (!left_diagonal_valid(q_row, q_col, row, col, n))
            return false;
            
        if (!right_diagonal_valid(q_row, q_col, row, col, n))
            return false;
    
    }
    
    
    return true;
}

int main() {
    
 
    Solution sol = Solution();
    auto result  = sol.solveNQueens(4);
    
    for (const auto &qsol: result) {
        std::cout << "------" << '\n' ;
        int i = 0;
        for (const auto & sline: qsol) {
            std::cout << "\n" << i << sline << '\n';
        }
    }
    
}
