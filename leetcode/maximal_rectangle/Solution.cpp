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

    int32_t row;
    int32_t col;
    int32_t id;  
    int32_t v;
    int32_t h;
    int32_t *contigious_h;  
    int32_t *contigious_v;  
    int32_t *top_width;  
    int32_t *left_height;  
    int32_t full_vertical;

};

struct NodeTop {
    int32_t eval_row;
    int32_t eval_col;
    int32_t max_sum;
    ActiveVerticesMap map;
    int32_t n_rows;
    int32_t n_cols;
};


std::ostream& operator<<(std::ostream& os,  Node * const node) {

    os <<  "( " << node->row << "," << node->col << ") " << " V: " << node->v << " H: "<< node->h << "\t BIN_TOP_H: " << *node->contigious_h << " BIN_TOP_V: " << *node->contigious_v << " TOP_WIDTH: " << ((node->top_width !=nullptr)? *node->top_width: 0)<< "\t STACK TOP INDEX:" << *node->left_height  <<"\n";
    return os;
}

std::string akey(int32_t r, int32_t c) {
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

void test_rectangle(uint32_t w, uint32_t h, Node *node, NodeTop *nodetop) {

    uint32_t len_r = node->row + h;
    uint32_t len_c = node->col + w;

    for (uint32_t r = node->row; r < len_r ; r++) {
        for (uint32_t c = node->col; c < len_c ; c++) {

            // std::cout  << "test rectahnle "  << r << " , " << c << "\n";
            std::string key = akey(r, c);
            
            if (nodetop->map.count(key) == 0)
                return ;
            
        }
        
    }

    int32_t area = h * w ;
    
    if (nodetop->max_sum < area ) {
        nodetop->max_sum = area;
    }

    return ; 
}

bool valid_window(Node *source, Node *child) {

    int32_t n_child_cells = *child->contigious_h - child->h + 1;

    return n_child_cells >= *source->contigious_h;

}




void test_walk_away_contigious_less (int32_t w, Node *node, NodeTop *nodetop) {
    std::string key_up;
    std::string key_down;
    Node *child;
    int32_t depth = 1;
    bool done_down, done_up;
    int32_t kup = 0;
    int32_t kdown = 0;

    done_down = true;
    done_up = false; 
    int32_t n_child_cells;
    int32_t area = 0;

    std::cout << "SEARCH PROCESS 2 " << "\n";

    while ( !done_up || !done_down ) {
        
        
        if ( !done_up && node->row - (kup + 1) >= 0) {
            kup = kup + 1;
            key_up = akey(node->row - kup, node->col);
            std::cout <<  "  UP STEP : "  << " " <<  key_down <<  " " << node->row - (kup )  << "\n";
            
            if ( nodetop->map.count(key_up) ) {
                
                child = nodetop->map[key_up];
                
                n_child_cells = *child->contigious_h - child->h + 1;
                
                if (n_child_cells < w && n_child_cells != 1) {
                    w = n_child_cells; 
                    depth++;
                    std::cout << " N CHILD CELLS " <<   n_child_cells <<  " " << " UP DEPTH " << depth <<  "\n";
                } else {
                    done_up = true; 
                }
            } 

        } else {
            done_up = true; 
        }

        if ( !done_up && node->row + (kdown + 1) >= 0) {
            kdown = kdown + 1;
            key_down = akey(node->row + kdown, node->col);
            std::cout <<  " DOWN STEP: "  << " " <<  key_down <<  " " << node->row + (kdown )  << "\n";
        
            if ( nodetop->map.count(key_down) ) {
                
                child = nodetop->map[key_down];
                
                n_child_cells = *child->contigious_h - child->h + 1;
                
                if (n_child_cells < w && n_child_cells != 1) {
                    w = n_child_cells;
                    depth++;
                    std::cout << " N CHILD CELLS " <<   n_child_cells <<  " " << " DOWN DEPTH " << depth <<  "\n";
                } else {
                    done_down = true; 
                }
            } 

        } else {
            done_down = true;
        }

    }

    area = depth * w ;
    std::cout << "HELLO WORLD" << "\t\t\t\t\t\t\t\t\t\t\t\t" << area << "\n";
     if (nodetop->max_sum < area ) {
        nodetop->max_sum = area;
    }


}

void  test_walk_away_contigious_vertical(int32_t w, Node *node, NodeTop *nodetop) {

    int32_t k = 1;
    int32_t n_hits = 1; // start row contains contigious cells 
    std::string key_up;
    std::string key_down;
    bool done_up = false;
    bool done_down = false;
    Node *child;
    int32_t area;

    while ( !done_up || !done_down ) {
        
        key_up = akey(node->row - k, node->col);
        key_down = akey(node->row + k, node->col);

        std::cout << key_up  << " " <<  key_down << "\n";
        
        if (  !done_up  && nodetop->map.count(key_up) ) {
            
            child = nodetop->map[key_up];

            // if ( *child->contigious_h >= w) {
            if (  valid_window(node, child) ) {

                n_hits++; 
                // std::cout << "\n (1 up))\n ";

            } else {

                done_up = true;

            }
            
        } else {
            done_up = true;
        }
        
        if ( !done_down  && nodetop->map.count(key_down) ) {
            
            child = nodetop->map[key_down];

            if (  valid_window(node, child) ) {

                n_hits++; 

            } else {

               done_down = true;

            }

        } else {

            done_down = true;

        }

        k++;
    }
    
    if (n_hits != 1) {
        // no_change
        area = n_hits * w ;
        
        std::cout << n_hits << " <- " << "\n\n\n";
        std::cout << area << " <- " << "\n\n\n";
        
        if (nodetop->max_sum < area ) {
            nodetop->max_sum = area;
        }

    } else  {
        
        test_walk_away_contigious_less(w, node, nodetop);

    }
        
}

bool valid_window2(int32_t h, Node *source, Node *child, NodeTop *nodetop) {

    int32_t n_child_cells = 0; //  = source->col - child->col + 1;
    
    for (int32_t i = 0; i < h; i++) {

        std::string key = akey(child->row + i, child->col);

        if (nodetop->map.count(key) == 1) {

            n_child_cells++;
        }
    }

    return n_child_cells == h;

}

void  test_walk_away_contigious_horizontal(int32_t h, Node *node, NodeTop *nodetop) {

    int32_t k = 1;
    int32_t n_hits = 1; // start row contains contigious cells 
    std::string key_left;
    std::string key_right;
    bool done_left = false;
    bool done_right = false;
    Node *child;
    int32_t area;

    if (h <= 1)
        return;

    while ( !done_left || !done_right ) {

        key_left = akey(node->row , node->col - k);

        if (  !done_left  && nodetop->map.count(key_left) ) {
            
            child = nodetop->map[key_left];

            // if ( *child->contigious_h >= w) {
            if (  valid_window2(h , node, child, nodetop) ) {

                n_hits++; 


            } else {

                done_left = true;

            }
            
        } else {
            done_left = true;
        }
    
        key_right = akey(node->row , node->col + k);
        if (  !done_right  && nodetop->map.count(key_right) ) {
        
                std::cout << " CURRENT KEY " << key_right << "\n";
            
            child = nodetop->map[key_right];

            // if ( *child->contigious_h >= w) {
            if (  valid_window2(h /* centered ate a column*/, node, child, nodetop) ) {

                n_hits++; 
                // std::cout << "\n (1 up))\n ";

            } else {

                done_right = true;

            }
            
        } else {
            done_right = true;
        }
    
        k++;


    }

    if (n_hits > 1) {

        // no_change
        area = (n_hits) * (h) ;

        
        std::cout << n_hits << " <- " << "\n\n\n";
        std::cout << area << " <- " << "\n\n\n";
        
        if (nodetop->max_sum < area ) {
            nodetop->max_sum = area;
        }
    }    

}


void test_vh(NodeTop *nodetop, Node *node) {

     if (node->h > nodetop->max_sum)
        nodetop->max_sum = node->h;


    if (node->v > nodetop->max_sum)
        nodetop->max_sum = node->v;

    if (node->full_vertical) {
        int32_t n = nodetop->n_rows * node->full_vertical;
        if (n > nodetop->max_sum) {
            nodetop->max_sum = n;
        }

    }



    if (node->h == 1 && ! node->top_width) {

        if ( nodetop->max_sum < node->v ){
            nodetop->max_sum = node->v;
        }
    }

    if (node->v == 1 && !node->top_width) {
        
        if (nodetop->max_sum < node->h) {
            nodetop->max_sum = node->h;
        }
    
    } 
    
    if (node->top_width ) {

        int32_t w = *node->top_width;
        
        std::cout << " \t\t TOP WIDTH==ANALYSIS " << node->row << " , " << node->col <<  "\t\tBAKED " << w  << " , " << "\n";

        test_walk_away_contigious_vertical(w, node, nodetop);

    }

    if (node->left_height ) {

        int32_t h = *node->left_height;
        std::cout << h << "\n";
        
        std::cout << " \t\t LEFT HEIGHT==ANALYSIS " << node->row << " , " << node->col <<  "\t\tBAKED " << h  << " , " << "\n";
        // test_walk_away_contigious_horizontal(h, node, nodetop);

        // if (nodetop->max_sum == 120)
        //     assert(0);

    }


}


void evaluate(NodeTop * nodetop, int32_t n_rows, int32_t n_cols, const Matrix & matrix) {
    
    bool valid; 
    Node *node;
    std::string key; 

    std::cout << n_rows << " \t" << n_cols << "\n";

    for (int32_t r = nodetop->eval_row; r < n_rows; r++) {

        for (int32_t c = nodetop->eval_col; c < n_cols; c++) {
            
            valid = matrix[r][c] == '1';
            
            key = akey(r, c); 
            
            if (valid) {

                std::string key = akey(r,c ); 

                // create node 
                node = new Node{r, c, 0 /* id */, 1 /* v */, 1 /* h */,  new int32_t{1} , new int32_t{1}, nullptr, nullptr , 0 };

                // std::cout << key << " --\t" << r << ", " << c << "\n"; 
                nodetop->map[  key  ] = node;  // valid cells are added to map 

                #if COMMENTS_OFF
                    std::cout << "\t\t\tADD NODE " << "" << key<< "\n";
                #endif 

             
                if  ( nodetop->map.count(akey(r, c-1))   ) {
                        
                    Node *prev_node = nodetop->map[akey(r, c-1)];

                    node->contigious_h = prev_node->contigious_h; // shared addr

                    node->h = prev_node->h + 1;
                    
                    if (prev_node->h == 1) {
                        prev_node->top_width = node->contigious_h;
                        // *prev_node->top_width_row = prev_node->row;
                    }

                    *(node->contigious_h) = node->h;
                
                }
                
                if  (  nodetop->map.count(akey(r - 1, c))  ) {
                    
                    Node *up_node = nodetop->map[akey(r - 1, c)];
                    
                    if (up_node->v == 1) {
                        up_node->left_height = up_node->contigious_v;
                    }

                    node->v = up_node->v + 1;

                    node->contigious_v = up_node->contigious_v;  // base points to top

                    *node->contigious_v = node->v ; // up_node->contigious_v; 




                    // node->left_height = up_node->left_height;

                    if (node->v == nodetop->n_rows) {
                        
                        node->full_vertical = 1;
                        std::string left_key = akey(r, c-1);
                        if (nodetop->map.count(left_key)) {
                            Node * left_node = nodetop->map[left_key];
                            node->full_vertical = left_node->full_vertical + 1;
                            std::cout << "KEY: \t\t\t\t\t\t\t\t" << key << "\t" << node->full_vertical << "\n";
                        }
                    }

                    // if (node->v == n_rows) {
                    //     std::cout << r << ", " << c << "\n\n";
                    //     assert(0);
                    // }
                }
            
             
                // test_vh(nodetop, node);
            
            }

        }
    }

    for (auto [key, curr]: nodetop->map) {

        if (curr->v)
        // std::cout << curr;
        test_vh(nodetop, curr);
    }

    return; 
}


class Solution {
public:

    int maximalRectangle(Matrix& matrix) {

        int32_t rows = matrix.size();
        int32_t cols = matrix[0].size();
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

        std::cout << rows << "\t" << cols << "\n";


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
            
                case (10):
                matrix = matrix_test_10;
                break; 

            case (11):
                matrix = matrix_test_11;
                break; 

            case (12):
                matrix = matrix_test_12;
                break;

            case (13):
                matrix = matrix_test_13;
                break; 

            case (14):
                matrix = matrix_test_14;
                break; 
                
            case (15):
                matrix = matrix_test_15;
                break; 

            case (16):
                matrix = matrix_test_16;
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