/*
  Purpose: Solve leetcode's longest valid parentheses problem.

  LeetcodeURL: https://leetcode.com/problems/longest-valid-parentheses/

  Author: HW 

  " much cleaner than my first attempt using recursive if-else method :) " 
*/

#include <iostream>
#include <string>
#include <stack>
#include <utility>
#include <map>

struct Node {
    int start_index; 
    int end_index; 
    int num_chars;
};

using PStack = std::stack<std::pair<char, int>>;
using LLMap = std::map<int, Node>;

class Solution {
    PStack pstack; 
    LLMap llmap;
    
public:
    int longestValidParentheses(std::string s) {
        int start_index;
        int end_index = 0;
        int len;
        int longest_len = 0;
        
        for(int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (c == ')') {
                if (pstack.size() == 0) {
                    // closing an unopened door (invalid state)
                    ;
                } else if (pstack.top().first == '(') {
                    // close open door (requested above) 
                    end_index = i;
                    start_index = pstack.top().second;
                    pstack.pop();
                    len = end_index - start_index + 1;
                    
                    if (len > longest_len) {
                        // longer contigious paren found
                        longest_len = len;
                    }
                    
                    llmap[i] = Node{start_index, i, len};
                    int adjacent_index_back = llmap[i].start_index - 1;
                    if (llmap.count(adjacent_index_back)) {
                        // contigious valid paren found(extend current node size)
                        llmap[i].num_chars += llmap[adjacent_index_back].num_chars;
                        if (llmap[i].num_chars > longest_len) {
                            // longer contigious paren found
                            longest_len = llmap[i].num_chars;
                        }
                    }
                    
                }  
                
            } else if (c =='(') {
                pstack.push( {c, i} );
            } 
        }
        return longest_len;
    }
};
