/*
 
  Purpose: Solve leetcode problem (NQueens). I have solved this before in the past, but this flow will capture how everything is done in real time.

  
 
  Author: HW 

*/
    

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <algorithm> 

struct EvalNode {
     std::string queen_map;
     int column;
     int row;
};

using QElist = std::deque<EvalNode *>;
using Qmap = std::vector<std::vector<std::string>>;


/**
 * Position row,col resides within limits of n square matrix
 * 
 * @param row Row location of queen 
 * @param col Column location of queen
 * @return True position is within bounds of grid; False position exceeds or hit boundary edge 
 */
 bool within_bound_test( const int &row, const int &col, const int  &n);
 
 
 class Solution {
    
    /**
     * Tyoe: Member Function
     * 
     * Analyzes square matrix for n possible queens on nxn board 
     * 
     * @param n Size of both length and width of board 
     * @param qmap buffer storing queen maps
     */
     void eval (const int &n , Qmap &qmap) {
        QElist q;
        std::string  queen_map_start;
        int n_sq = n * n; 
        int max_row_eval = (n % 2 == 0)? (n/2)-1    : n/2 + 1;
        int r_down;
        int r_up;
        int c_up;
        int c_down;
        std::string s;
        int c; 
        int r;
        int pos;
        int cc;
        int rr;
       
        for(int i = 0; i < n_sq; i++) { queen_map_start += "X"; }
       
       
       // init queue (half row, all column)
        for (int cc = 0; cc < n; cc++) {
            q.push_back(new EvalNode{ queen_map_start, cc, 0});
        }
       

          
       while (!q.empty()) {
          
           EvalNode *node = q.front();
           q.pop_front();

           s = node->queen_map;
        
        // Set Queen marker for drop-in in cell  
        s[node->row*n +node->column] = 'Q';
        
           // row test ( row fixed; column change)
           r = node->row;
           for (int c = 0; c< n; c++) {
               pos = r * n + c;
               if (s[pos] == 'X') {
                   // blast away all queens on current board 
                   s[pos] = '.';
               }
           }
           
           // col test ( column fixed, row change)
            c = node->column;
            for ( int r = 0; r < n; r++) {
                pos = r*n + c;
                if (s[pos] == 'X') {
                    s[pos] = '.';
                }
            }
           
    
           
           // right diagonal test
           r_down =node->row;; 
           r_up = node->row;
           c_down = node->column;
           c_up = node->column;
           while (within_bound_test(r_down, c_down, n)) {
               pos = r_down++ * n + c_down--;
               if (s[pos] == 'X') {
                   s[pos] = '.';
               }
           }
           while (within_bound_test(r_up, c_up, n)) {
               pos = r_up-- * n + c_up++;
               if (s[pos] == 'X') {
                   s[pos] = '.';
               }
           }
           
           // left diagonal test 
           r_up = node->row;
           r_down = node->row;
           c_down =node->column;  
           c_up = node->column;
        
           while (within_bound_test(r_down, c_down, n)) {
               pos = r_down++ * n + c_down++;
               if (s[pos] == 'X') {
                   s[pos] = '.';
               }
           }
           while (within_bound_test(r_up, c_up, n)) {
               int pos = r_up-- * n + c_up--;
               if (s[pos] == 'X') {
                   s[pos] = '.';
               }
           }
           
            
            int found_index = s.find('X');
            std::vector<std::string> data;
           if ( node->row + 1== n) {
               // found valid queens configuration
                for (int i = 0; i < n; i++) {
                    data.push_back(  s.substr(i * n , n )    );
                }
               qmap.push_back(data);

            } else if (found_index != std::string::npos) {
                rr = node->row + 1; // next row of possible solver paths 
                for (int cc = 0; cc < n; cc++) {
                    EvalNode *new_node = new EvalNode{ s, cc, rr};
                    if (s[rr * n + cc] == 'X') {
                        // possible search path 
                        q.push_back(new_node);
                    }
                }
                

            } 
            delete node;
       }
    }
    
    
public:
    // ~Solution() {}
    
    
    // Solution() {}
    
    Qmap solveNQueens(int n) {
        Qmap qmap{};
        eval(n,  qmap);
        return qmap;
    }
    
};

 bool within_bound_test( const int &row, const int &col, const int &n) {
    return ! (row < 0 || row >= n || col < 0 || col >=n );
 }
 
 
    


