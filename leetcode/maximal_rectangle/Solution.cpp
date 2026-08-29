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

#define COMMENTS_OFF 0

struct Node;
struct NodeTop;

// typedef unsigned  ; 
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
    int32_t *top_width;  

};

struct NodeTop {
    uint32_t eval_row;
    uint32_t eval_col;
    int32_t max_sum;
    ActiveVerticesMap map;
    uint32_t n_rows;
    uint32_t n_cols;
};


std::ostream& operator<<(std::ostream& os,  Node * const node) {

    os <<  "( " << node->row << "," << node->col << ") " << " V: " << node->v << " H: "<< node->h << "\t BIN_TOP_H: " << *node->contigious_h << " BIN_TOP_V: " << *node->contigious_v << " TOP_WIDTH: " << ((node->top_width !=nullptr)? *node->top_width: 0) <<"\n";
    return os;
}

std::string akey(uint32_t r, uint32_t c) {
    return std::to_string(r) + "," + std::to_string(c) ; 
}

void test_h(NodeTop *nodetop, Node *node) {

    if (node->h > nodetop->max_sum)
        nodetop->max_sum = node->h;

}

void test_v(NodeTop *nodetop, Node *node) {

    if (node->v > nodetop->max_sum)
        nodetop->max_sum = node->v;

}

bool test_rectangle(uint32_t w, uint32_t h, Node *node, NodeTop *nodetop) {

    uint32_t len_r = node->row + h;
    uint32_t len_c = node->col + w;

    for (uint32_t r = node->row; r < len_r ; r++) {
        for (uint32_t c = node->col; c < len_c ; c++) {

            // std::cout  << "test rectahnle "  << r << " , " << c << "\n";
            std::string key = akey(r, c);
            
            if (nodetop->map.count(key) == 0)
                return false;
            
        }
        
    }

    return true; 
}

void test_vh(NodeTop *nodetop, Node *node) {

     if (node->h > nodetop->max_sum)
        nodetop->max_sum = node->h;


    if (node->v > nodetop->max_sum)
        nodetop->max_sum = node->v;



    if (node->h == 1 && ! node->top_width) {

        if ( nodetop->max_sum < node->v ){
            nodetop->max_sum = node->v;
        }
    }

    else if (node->v == 1 && !node->top_width) {
        
        if (nodetop->max_sum < node->h) {
            nodetop->max_sum = node->h;
        }
    
    } 
    
    else if (node->top_width ) {

        int32_t w = *node->top_width;
        
        int32_t h = *node->contigious_v;// node->v - node->row;

   

        if (node->v > 1) {

            int32_t delta = h - node->row;

            h = delta;
        }

        int32_t substack_h = *node->contigious_v - nodetop->n_rows;
        
        if (   substack_h == node->row ) {
            // single contigious horiz seq
            h = *node->contigious_v;
        } else {
            h = *node->contigious_v - node->row;
        }

        std::cout << " \t\tANALYSIS " << node->row << " , " << node->col <<  "\t\tBAKED " << w  << " , " << h << "\n";

        std::map<int32_t, void*> used; 

        // while ( used.count(start_pivot) == 0) {

        //     node->row = start_pivot; 
            
            if (test_rectangle(w, h, node, nodetop)) {
    
                int32_t area = h * w ;
                
                if (nodetop->max_sum < area ) {
                    nodetop->max_sum = area;
                }
            }

            // used[start_pivot] = nullptr;

            // start_pivot = (start_pivot + 1) % h;
            
        // }

        // node->row = true_row;
    }

    else  {

        // int32_t m = *node->contigious_v  * node->v;

        // if (nodetop->max_sum < m ) {
        //     nodetop->max_sum = m;
        // }

    }
}


void evaluate(NodeTop * nodetop, uint32_t n_rows, uint32_t n_cols, const Matrix & matrix) {
    
    bool valid; 
    Node *node;
    std::string key; 

    std::cout << n_rows << " \t" << n_cols << "\n";

    for (uint32_t r = nodetop->eval_row; r < n_rows; r++) {

        for (uint32_t c = nodetop->eval_col; c < n_cols; c++) {
            
            valid = matrix[r][c] == '1';
            
            key = akey(r, c); 
            
            if (valid) {

                std::string key = akey(r,c ); 

                // create node 
                node = new Node{r, c, 0 /* id */, 1 /* v */, 1 /* h */,  new int32_t{1} , new int32_t{1}, nullptr };

                // std::cout << key << " --\t" << r << ", " << c << "\n"; 
                nodetop->map[  key  ] = node;  // valid cells are added to map 

                #if COMMENTS_OFF
                    std::cout << "\t\t\tADD NODE " << "" << key<< "\n";
                #endif 

                // if ( c >0 &&  matrix[r][c-1] == '0') {
                //     // headers of contigious cells
                //     node->top_width = node->contigious_h;
                // }
                
                if  ( nodetop->map.count(akey(r, c-1))   ) {
                        
                    Node *prev_node = nodetop->map[akey(r, c-1)];

                    node->contigious_h = prev_node->contigious_h; // shared addr

                    node->h = prev_node->h + 1;
                    
                    if (prev_node->h == 1) {
                        prev_node->top_width = node->contigious_h;
                    }

                    *(node->contigious_h) = node->h;

                    // *node->contigious_h = *node->contigious_h + 1; // increment
                    
                    
                        
                    // *node->contigious_v = node->h;
                    // *node->contigious_h = node->h;


                    // test_h(nodetop, node);
                
                }
                
                if  (  nodetop->map.count(akey(r - 1, c))  ) {
                    
                    Node *up_node = nodetop->map[akey(r - 1, c)];
                    
                    node->v = up_node->v + 1;

                    node->contigious_v = up_node->contigious_v; 
                    *node->contigious_v = node->v ; // up_node->contigious_v; 
                }
            
             
                // test_vh(nodetop, node);
            
            }

        }
    }

    for (auto [key, curr]: nodetop->map) {

        std::cout << curr;
        test_vh(nodetop, curr);
    }

    return; 
}


class Solution {
public:

    int maximalRectangle(Matrix& matrix) {

        unsigned rows = matrix.size();
        unsigned cols = matrix[0].size();
        int max_sum_out = 0;

        ActiveVerticesQueue q; 
        NodeTop *nodetop = new NodeTop{ 0, 0, 0,  {}, rows, cols};
        q.push_back(nodetop);

        while (!q.empty())  {
            
            NodeTop *nodetop = q.front();
            
            q.pop_front(); 

            evaluate(nodetop, rows, cols, matrix);

            if (nodetop->max_sum > max_sum_out) {
                max_sum_out = nodetop->max_sum ;
            }
        }

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
            
            case (1):
                matrix = matrix_test_1;
                break; 

            case (2):
                matrix = matrix_test_2;
                break; 

            case (3):
                matrix = matrix_test_3;
                break; 

            case (4): 
                matrix = matrix_test_4;
                break;

            case (5): 
                matrix = matrix_test_5;
                break;
            
            case (6): 
                matrix = matrix_test_6;
                break;

            case (7):
                matrix = matrix_test_7;
                break; 
            
            case (8):
                matrix = matrix_test_8;
                break; 

            case (9):
                matrix = matrix_test_9;
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