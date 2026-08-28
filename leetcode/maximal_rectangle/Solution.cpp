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

struct Node;

using Vertices = std::map<std::array<unsigned, 2> , Node*>; 

using Matrix = std::vector<std::vector<char>>;

struct Node {
    char value; 
    unsigned row;
    unsigned col;
    unsigned h;
    unsigned v;
    Node * right;
    Node * left;
    Node * up;
    Node * down;
};

// create node if nonexistent 
Node * create_node(unsigned value, unsigned row, unsigned col, const Matrix &matrix, Vertices &vertices) {
    unsigned x =  (value == '1') ? 1 : 0 ;
    Node *node = new Node(value, row, col , x, x, nullptr, nullptr, nullptr, nullptr);
    vertices[{row, col}] = node; 
    return node;
}

void test_cell(unsigned row, unsigned col , unsigned n_rows, unsigned n_cols, unsigned kernel_width, unsigned kernel_height , const Matrix &matrix, Vertices &vertices) {

    char c;
    
    for (unsigned curr_row = row; curr_row < n_rows; curr_row++ ) {
        
        c = matrix[curr_row][col];
        create_node(c, curr_row, col, matrix, vertices);
        std::cout << "\tROW \t" << curr_row << "\n";

        Node *top_node = nullptr;
        Node *bottom_node = nullptr;
        Node *top_node_prev;
        Node *bottom_node_prev;

        char c_top;
        char c_bottom; 
        char c_top_prev; 
        char c_bottom_prev; 
        
        if (curr_row >= 1) {
            
            c_top = matrix[curr_row - 1][col];
            c_bottom = matrix[curr_row][col];
            
            top_node = vertices[ {curr_row - 1 , col} ];
            bottom_node = vertices[ {curr_row, col} ];

            if (c_top == '1' &&  c_bottom == '1') {
                bottom_node->v = top_node->v  + 1;
                top_node->down = bottom_node;
                bottom_node->up = top_node;
            }

            if (col > 0 ) {
                c_top_prev = matrix[curr_row - 1][col-1];
                c_bottom_prev = matrix[curr_row][col-1];
                top_node_prev = vertices[{curr_row - 1, col-1}];
                bottom_node_prev = vertices[{curr_row, col - 1}];

                if (c_top == '1' && c_bottom == '1') {
                    
                    // bottom_node->v = bottom_node->v + 1;
                    
                        top_node->h = top_node_prev->h + 1;

                        bottom_node->h = bottom_node_prev->h + 1;


                } else if (c_top == '1'&& c_bottom == '0') {

                    bottom_node->v = 0;     // c_bottom - '0';
                    bottom_node->h = 0;     // c_bottom - '0';

                    if (c_top_prev == '1') {
                        top_node->h = top_node_prev->h + 1;
                    }



                } else if (c_top == '0' && c_bottom == '1') {
                    
                    top_node->v = 0;    // c_top - '0';
                    top_node->h = 0;
                    
                    if (c_bottom_prev == '1') {
                        bottom_node->h = bottom_node_prev->h + 1;
                    }

                
                } else  {

                    top_node->v = c_top - '0';
                    bottom_node->v = c_bottom - '0';
                    
                    top_node->h = c_top - '0';
                    bottom_node->h = c_bottom - '0';

                }

            }
        }

    }

    std::cout << " " << "\n";

}

class Solution {
public:

    int maximalRectangle(Matrix& matrix) {

        unsigned rows = matrix.size();
        unsigned cols = matrix[0].size();
        Vertices vertices;

        unsigned kernel_width = 1;
        unsigned kernel_height = 2;

        // eval first for row 
        unsigned row = 0;
        unsigned col = 0;

        for( ; col < cols; col++ ) {
            
            test_cell(row, col, rows, cols, kernel_width, kernel_height, matrix, vertices);

        }
            
        for (unsigned c = 0; c < 5; c++) {

            for (unsigned r = 0 ; r < 4; r++) {
                
                Node *node  = vertices[{r,c}];
                
                // while (node) {
                    std::cout << r << " , " << c << "\t" << " VERT SUM:\t"  << "\t\tROW: " << row << " \t\tCOL: " << col  << " VALUE " << node->v <<  " HORIZ "  << node->h <<"\n";
                    // node = node->down;
                
                std::cout << "\n";
            }
            
        }

        return 1;
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