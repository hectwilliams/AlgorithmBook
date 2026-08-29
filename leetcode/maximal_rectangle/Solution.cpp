#include <vector>
#include <iostream>
#include <deque>
#include <map>
#include <algorithm>
#include <numeric> 
#include <random>
#include <cassert> 
#include <array>
#include <stdexcept> // Required for standard exceptions
#include <string>
#include <iterator>
#include <chrono> // Required header
#include "Solution.h"

#define COMMENTS_OFF 1

struct Node;
struct NodeTop;

// typedef unsigned  ; 
using Vertices = std::map<std::array<unsigned, 2> , Node*>; 

using Matrix = std::vector<std::vector<char>>;

using ActiveVerticesQueue = std::deque< NodeTop* >; 

using ActiveVerticesMap = std::map< std::string ,  Node * >; 

struct Node {

    uint32_t row;
    uint32_t col;
    uint32_t id;  
    int32_t v;
    int32_t h;
    int32_t *contigious_h;  
    int32_t *contigious_v;  

};

struct NodeTop {
    uint32_t eval_row;
    uint32_t eval_col;
    int32_t max_sum;
    ActiveVerticesMap map;
};


std::ostream& operator<<(std::ostream& os,  Node * const node) {

    os <<  "( " << node->row << "," << node->col << ") " << " V: " << node->v << " H: "<< node->h << " BIN_TOP_H: " << *node->contigious_v << "\n";
    return os;
}
// struct Node {
//     char value; 
//     unsigned row;
//     unsigned col;
//     unsigned h;
//     unsigned v;
//     Node * right;
//     Node * left;
//     Node * up;
//     Node * down;
// };

// // create node if nonexistent 
// Node * create_node(unsigned value, unsigned row, unsigned col, const Matrix &matrix, Vertices &vertices) {
//     unsigned x =  (value == '1') ? 1 : 0 ;
//     Node *node = new Node(value, row, col , x, x, nullptr, nullptr, nullptr, nullptr);
//     vertices[{row, col}] = node; 
//     return node;
// }

// void test_cell(unsigned row, unsigned col , unsigned n_rows, unsigned n_cols, unsigned kernel_width, unsigned kernel_height , const Matrix &matrix, Vertices &vertices) {

//     char c;
    
//     for (unsigned curr_row = row; curr_row < n_rows; curr_row++ ) {
        
//         c = matrix[curr_row][col];
//         create_node(c, curr_row, col, matrix, vertices);
//         std::cout << "\tROW \t" << curr_row << "\n";

//         Node *top_node = nullptr;
//         Node *bottom_node = nullptr;
//         Node *top_node_prev;
//         Node *bottom_node_prev;

//         char c_top;
//         char c_bottom; 
//         char c_top_prev; 
//         char c_bottom_prev; 
        
//         if (curr_row >= 1) {
            
//             c_top = matrix[curr_row - 1][col];
//             c_bottom = matrix[curr_row][col];
            
//             top_node = vertices[ {curr_row - 1 , col} ];
//             bottom_node = vertices[ {curr_row, col} ];

//             if (c_top == '1' &&  c_bottom == '1') {
//                 bottom_node->v = top_node->v  + 1;
//                 top_node->down = bottom_node;
//                 bottom_node->up = top_node;
//             }

//             if (col > 0 ) {
//                 c_top_prev = matrix[curr_row - 1][col-1];
//                 c_bottom_prev = matrix[curr_row][col-1];
//                 top_node_prev = vertices[{curr_row - 1, col-1}];
//                 bottom_node_prev = vertices[{curr_row, col - 1}];

//                 if (c_top == '1' && c_bottom == '1') {
                    
//                     // bottom_node->v = bottom_node->v + 1;
                    
//                         top_node->h = top_node_prev->h + 1;

//                         bottom_node->h = bottom_node_prev->h + 1;


//                 } else if (c_top == '1'&& c_bottom == '0') {

//                     bottom_node->v = 0;     // c_bottom - '0';
//                     bottom_node->h = 0;     // c_bottom - '0';

//                     if (c_top_prev == '1') {
//                         top_node->h = top_node_prev->h + 1;
//                     }



//                 } else if (c_top == '0' && c_bottom == '1') {
                    
//                     top_node->v = 0;    // c_top - '0';
//                     top_node->h = 0;
                    
//                     if (c_bottom_prev == '1') {
//                         bottom_node->h = bottom_node_prev->h + 1;
//                     }

                
//                 } else  {

//                     top_node->v = c_top - '0';
//                     bottom_node->v = c_bottom - '0';
                    
//                     top_node->h = c_top - '0';
//                     bottom_node->h = c_bottom - '0';

//                 }

//             }
//         }

//     }

//     std::cout << " " << "\n";

// }

// assumes column > 0
bool has_reverse_adjacent(uint32_t r, uint32_t c, const Matrix &matrix) {
    
    if (c==0)
        return false;
    
    if (matrix[r][c-1] == '1'){
        return true;
    }

    return false; 
}

// assumes current r,c cell is a valid 

// Node * copy_node (Node *source) {
//     try {
        
//         if (!source)
//             throw std::runtime_error("undefined node: unable to copy");

//         Node *node = new Node{source->row, source->col, source->external_sum, source->id,  source->v_single_sum, new int32_t{*source->contigious_sum}};

//         return node; 

//     } catch(const std::runtime_error& e) {
//         return nullptr;
//     }
// }

// void copy_network( ActiveVerticesMap &source, ActiveVerticesMap &dest) {
//     for ( auto [ key2, source_node] : source) {
        
//         // std::cout  << " \t copied node: " << key2 << "\n";  
        
//         Node *dest_node = copy_node(source_node);

//         std::string key = std::to_string(dest_node->row) + "," + std::to_string(dest_node->col) ; 

//         dest[key] = dest_node;
//     }
// }

std::string akey(uint32_t r, uint32_t c) {
    return std::to_string(r) + "," + std::to_string(c) ; 
}

bool valid_cell (uint32_t r, uint32_t c, uint32_t n_cols, const Matrix & matrix) {

    // if (c >= n_cols)
    //     return false;

    return matrix[r][c] == '1';

}

// nodetop->map[ akey(r, c + 1) ]->contigious_sum = nodetop->map[ akey(r, c ) ]->contigious_sum ; 

// uint32_t forward_adjacent_count(uint32_t r, uint32_t c, NodeTop *nodetop, const Matrix & matrix, uint32_t n_cols ) {
//     uint32_t count = 1; // called by current node
//     uint32_t id = 0;
//     Node *header_node = nodetop->map[akey(r, c)];

//     while ( matrix[r][c + 1] == '1' && c < n_cols ) {
//         count  += 1;
//         std::string key_above = akey(r-1, c);
//         std::string next_key = akey(r, c + 1);

//         int32_t v_cnt = nodetop->map.count(key_above) ? nodetop->map[key_above]->v_single_sum + 1 : 1;
//         Node *new_node = new Node{r, c + 1, 0, id++,,  header_node->contigious_sum };
//         *header_node->contigious_sum = *header_node->contigious_sum + 1; // shared memory update count 
//         nodetop->map[next_key] = new_node;
//         c++;
//     }
//     return count;
// }

void evaluate(NodeTop * nodetop, uint32_t n_rows, uint32_t n_cols, const Matrix & matrix) {
    
    bool valid; 
    Node *node;
    std::string key; 

    for (uint32_t r = nodetop->eval_row; r < n_rows; r++) {

        for (uint32_t c = nodetop->eval_col; c < n_cols; c++) {
            
            valid = matrix[r][c] == '1';
            
            key = akey(r, c); 
            
            if (valid) {
                
                std::string key = akey(r,c ); 

                // create node 
                node = new Node{r, c, 0 /* id */, 1 /* v */, 1 /* h */,  new int32_t{1} , new int32_t{1} };
                nodetop->map[  key  ] = node;  // valid cells are added to map 
                std::cout << "\t\t\tADD NODE " << "" << key<< "\n";
                
                if  ( nodetop->map.count(akey(r, c-1))   ) {
                        
                    Node *prev_node = nodetop->map[akey(r, c-1)];
                        
                    node->contigious_h = prev_node->contigious_h; // shared addr

                    *node->contigious_h = *node->contigious_h + 1; // increment
                    
                    node->h = prev_node->h + 1;

                    *node->contigious_v = node->h;
                
                }
                
                if  (  nodetop->map.count(akey(r - 1, c))  ) {
                    
                    Node *up_node = nodetop->map[akey(r - 1, c)];
                    
                    node->v = up_node->v + 1;
                    
                    node->contigious_v = up_node->contigious_v; // top most valid bin keeps h values ( shared across all bin values )
                    
                    // *node->contigious_v = *node->contigious_v + 1; // increment
                    
                }
            
                Node *this_node = nodetop->map[ akey(r, c) ];
                std::cout << this_node << "\n";

                // find max 

                if (node->h == 1) {

                    if ( nodetop->max_sum < node->v ){
                        nodetop->max_sum = node->v;
                    }
                }

                else if (node->v == 1) {
                    
                    if (nodetop->max_sum < node->h) {
                        nodetop->max_sum = node->h;
                    }
                
                } 
                
                else  {

                    uint32_t m = *node->contigious_v  * node->v;

                    if (nodetop->max_sum < m ) {
                        nodetop->max_sum = m;
                    }




                }
            
            }

        }
    }

    return; 
}


class Solution {
public:

    int maximalRectangle(Matrix& matrix) {

        unsigned rows = matrix.size();
        unsigned cols = matrix[0].size();
        // Vertices vertices;
        int max_sum_out = 0;
        ActiveVerticesQueue q; 

        NodeTop *nodetop = new NodeTop{ 0, 0, 0,  {}};
        q.push_back(nodetop);

        while (!q.empty())  {
            
            NodeTop *nodetop = q.front();
            
            q.pop_front(); 

            evaluate(nodetop, rows, cols, matrix);

            if (nodetop->max_sum > max_sum_out) {
                max_sum_out = nodetop->max_sum ;
            }
        }

        std::cout << " RESULT:\t" << max_sum_out; 
        return max_sum_out;
    }
};

int main(int param_count, char *args[]) {
    
    Solution sol;

    Matrix  matrix; 
    

    int result;

    try {

        if (param_count  < 2)
            return 1;
        
        int test = std::stoi(args[1]);

        switch(test) {

            case (0):
                matrix = matrix_test_0;
                break;
        
            default: 
                break;
        
        }

        auto start = std::chrono::high_resolution_clock::now();
        result = sol.maximalRectangle(matrix);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Execution time: " << duration.count() << " microseconds\n";

    } catch (const std::runtime_error & e) {

        std::cout << " RUNTIME ERROR "<< e.what() << "\n" ;

    }

    std::cout << " max sum: " << result << "\n";
}