/*
  
 Solution to Zig Zag conversion problem from leetcode

 Author: Hectron
*/

#include <iostream>
#include <string>
#include <map>

class Solution {
public:
    string convert(string s, int numRows) {

 /**
        Rollercoaster coaster 

        |  /\ 
        | /  \
        |/    \



    */
        std::map<int , std::string > bucket;
        int p = 0;
        int dir = 0;
        
        if ( numRows <= 1)
            return s;

       for(int i = 0; i< s.length(); i++) {

            if(bucket.count(p) == 0){
                bucket[p] = std::string{};
            }
            
            bucket[p] += s[i];

            if(p == numRows - 1) {
                dir = 1;
            } else if (p == 0) {
                dir = 0;
            }
            
            if (dir)
                p--;
            else
                p++;
            
        }

        std::string ret;

        for (const auto &[key, value] : bucket) {
            ret += value;
        }

        return ret;
    }
};
