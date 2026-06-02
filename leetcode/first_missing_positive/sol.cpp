/*

  Purpose: Solve leetcode First Missing Positive problem

  Author: HW 

*/

// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <map>


class Solution {
public:
    int firstMissingPositive(std::vector<int>& nums) {
        int front_man = 1;
        std::map<int, void*> map;
        
        for(const auto & value : nums) {
            map[value] = nullptr;
            
            if (value == front_man)
               front_man =  front_man + 1;

              // move front man if possible
            while (map.count(front_man) ) {
                front_man += 1;
            }
        }
        
        
        if (map.size() == 0) {
            
            return 1;
            
        } else if (front_man != map.begin()->first) {
            
            return front_man;
        
        } else if (front_man == map.begin()->first) {
            //matching head on map  
            int n_elements_test = (map.begin()->first - map.rbegin()->first) + 1;
            if (n_elements_test == nums.size()) {
                return map.rbegin()->first + 1;
            } else {
                // discontinuity
                for (const auto &[v,_] : map) {
                    if (map.count(v + 1) ==0 ) {
                        return v + 1;
                    }
                }
            }
            
        }
        
        return 1;
    }
};
