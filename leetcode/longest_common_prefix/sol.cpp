/*
  Purpose: 
  
    Solution to leetcode problem. Suprisingly this took me a day to figure out. Enjoy!

  Author:

    HW

*/

#include <iostream>
#include <string> 
#include <vector>
#include <map>

using Cmap = std::map<char, std::vector<int>>; 
using Binni = std::map< std::string, int>; 
using TestMap = std::map< std::string, std::string>; 

// its always good to review c++ :)

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        std::string lp;
        if (strs.size() == 0){
            // empty container
            return lp;
        } else if (strs.size()==1) {
            return strs[0];
        }else {
            Cmap cmap;
            std::size_t s_pos;
            int c = 0;
            int word_index = 0;
            std::string s; 

            while(1) {
            
                for (s_pos = 0; s_pos < strs.size(); ++s_pos) { 
                    s = strs[s_pos];
                    if (c >= s.length()) {
                        // strings of differing size 
                        return lp;
                    }
                    char character = strs[s_pos][c];
                    cmap[character].push_back(static_cast<int>(s_pos));
                    // 1) discard invalid prefix (head char of string does not match)
                    // 2)first column must all have the same values 
                    if ( (c == 0 && (cmap[character].size() != s_pos + 1)) || ( s_pos == 0 && cmap.size() != 1)  ) {
                        return lp;
                    } 

                    if ( (word_index == lp.length()) && (cmap[character].size()== strs.size()) ) {
                        // add character if bin size matches length of 
                        lp += character;
                    }
                }
            
                if ( s_pos == strs.size() ) 
                    word_index += 1;
                    
                if (word_index == strs[strs.size() - 1].length() )
                    break;
                
                c+= 1;

                // clear cmap
                cmap.clear();
            }
        }
        return lp; 
    }
};


