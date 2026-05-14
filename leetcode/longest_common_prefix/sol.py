"""
  Purpose: 
  
    Solution to leetcode problem. Suprisingly this took me a day to figure out. Enjoy!

  Author:

    HW

"""

#include <iostream>
#include <string> 
#include <vector>
#include <stack>
#include <map>
#include <array>
#include <deque>
#include <utility>

using Cmap = std::map<char, std::vector<int>>; 
using Binni = std::map< char, int>; 
using TestMap = std::map< std::string, std::string>; 

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        std::string lp;
        int lp_length = 0;
        int traverse_done = false;
        if (strs.size() == 0){
            // empty container
            return lp;
        } else if (strs.size()==1) {
            return strs[0];
        }else {
            Cmap cmap;
            TestMap tmap;
            Binni bins; // this is wasteful to check at least first two samples of column two 
            int c = -1;
            
            while(1) {
                int len = 0;
                int misses = 0;
                std::size_t s_pos;
                c += 1;
                std::string s; 
                for (s_pos = 0; s_pos < strs.size(); ++s_pos) { 
                    std::string s = strs[s_pos];
                    char character = strs[s_pos][c];
                    
                    if (c == 0) {
                        if (bins.count(character) == 0){
                            bins.insert({character, 0});
                        }
                        bins[character] += 1;
                        if (s_pos == 1 && bins[character] != 2) {
                            break;
                        }
                    }
                    
                    if (s.length() == 0) {
                        // empty strings are skipped 
                        break;
                    }
                    
                    // map char to list of indices
                    cmap[character].push_back(static_cast<int>(s_pos));
                    
                    // max length of cmap bins
                    if (cmap[character].size() > len) {
                        len = cmap[character].size();
                    }
                    
                    if (s_pos == strs.size() - 1  &&  c >= s.length()) {
                        // last round (i.e. column)
                        traverse_done = true;
                    }
                }
                
                if (bins[strs[0][0]] != strs.size()) {
                    break;
                }      
                if (traverse_done) 
                    break;
                
                // convert [char] -> [indices]  to [string] [string]
                std::string s_temp{};
                misses = 0;
                for (auto &[key_character, vect]: cmap) {
                    for(auto &num :vect) {
                        s_temp += std::to_string(num);
                    }
                
                    // test for continuation of prefix; len must be more than 1 to have potential prefix. All first (index = 0) characters differ in each string.  
                    if (c == 0) {
                        if ( s_temp.length() > 1) {
                            // init bookeeping object 
                            tmap[s_temp] = key_character;
                            lp = std::string{key_character};
                        } else {
                            // no prefixes
                            return lp;
                        }
                    } else if (tmap.count(s_temp) == 0) {
                        //prefix miss !
                        misses += 1;
                    } else if (tmap.count(s_temp) != 0  ) {
                        // prefix extended 
                        tmap[s_temp] += key_character;
                        
                        if (tmap[s_temp].length() >= lp.length()) {
                            lp = tmap[s_temp];
                        }
                    }
                    s_temp = "";
                }
                
                // clear cmap
                cmap.clear();
            
                if (traverse_done || misses >= tmap.size())
                    break;
            }
        }
        return lp; 
    }
};

int main() {
    // const char * strs[4] = {"abcd","abde","effc", "efff"};
    // const char * strs[3] = {"reflower","flow","flight"}; // {"flower","flow","flight"}; // {"flower","flow","flight"};
    // const char * strs[4] = {"flower","flower","flower","flower"};
    std::vector<std::string> dv;
    const char * strs[3] = {"a","a","b"};
    for (auto &loc_ch:  strs) {
        dv.push_back(loc_ch);
    }
    // d.push_back(strs[3]);
    Solution sol = Solution();
    std::string ref = sol.longestCommonPrefix(dv);
    std::cout <<"SOLUTION\t"  << ref << '\n';
    
    
}



