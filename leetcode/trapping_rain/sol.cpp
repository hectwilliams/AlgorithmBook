/*

  Purpose: Solve leetcode's Trapping Rain Water 

  Author: HW 

  URL: https://leetcode.com/problems/trapping-rain-water/description/

*/

#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <array>


/**
 * View bin 
 * 
 */
 void show_bin(std::deque<int> bin) {
    for(const auto x: bin){
        std::cout << x << " - ";
    }
    std::cout << "\n";
 }
 
/**
 * Compute the sum of water within pocket of water
 * 
 * @param heights List of heights pertaining to block of water
 */
int solve_water(std::deque<int> heights ) {
    int min_boundary = 100000;
    int acc = 0;
    if (heights[0] < min_boundary)
        min_boundary = heights[0] ;
    
     if (heights[heights.size()-1] < min_boundary)
        min_boundary = heights[heights.size()-1] ;
        
    for (const auto h: heights) {
        if (h < min_boundary ) {
            acc += min_boundary - h;            
            // std::cout << min_boundary - h << " RER " << min_boundary << "\n";
        }
    }
    return acc;
}

/**
 * Lookahead for mountain end edge higher than enter edge height
 * 
 * @param index Current index in deque
 * @param heights Heights seen in front 
 * @param h_top Max height
 * @param highest_climbed_ascension Highest height out of water well 
 * @return False if future heights are equal to or greater than max height; True otherwise
*/
bool look_ahead_test(int start_index, std::vector<int> heights, int h_top, int highest_climbed_ascension) {
    
    for(int i = start_index; i < heights.size(); i++) {
        
        if ( heights[i] >= h_top ) {
            // ith-height equal max height
            if (i == start_index) {
                // start index is boundary
                return true;
            } else {
                // new end boundary found
                return false;
            }
        }
        
        if (i != start_index && heights[i] > highest_climbed_ascension) 
            return false;
    }
    return true;
}

class Solution {
public:
    int trap(std::vector<int>& height) {
        int rise_var = -1;
        int prev = 0;
        int curr; 
        bool turn_on = false;
        std::vector<int> inner_bin;
        std::deque<int> end_bin;
        std::deque<int> bin;
        int state{0};
        int acc{0};
        int current_max_edge = 0;
        
        for (int i = 0; i < height.size(); i++) {
            
            int curr = height[i];
            
            if ( curr > prev) {
                if (state == 0) {
                    // first climb up in window
                    state = state | (1 << 0);
                    if (i + 1 < height.size()) {
                        int next = height[i + 1];
                        if (next >= curr) {
                            // higher position found to look down; climb to higher peak 
                            state = 0;
                            continue;
                        }
                    }
                } else if (state & 1) {
                    // climb up
                    state = state | (1<<2);
                    current_max_edge = curr;
                }
            } 
            
            if (state) {
                bin.push_back(curr);
            }
            
            if (curr < prev ) {
                // well drop
                state = state | ( 1 << 1 );
            }
        
            
                if (i + 1 == height.size()) {
                    // end of the line !
                    if (state == 7) {
                                                show_bin(bin);

                        // solve water 
                        acc += solve_water(bin);
                    }
                } else if (height[i + 1] < curr  ) {
                    
                    
                    // next step is a drop
                    if (state == 7) {
                        
                        
                        if (!look_ahead_test(i, height, bin.front() , current_max_edge) ) {
                            continue;
                        }
                            std::cout << " HIT "<< bin.front() << "\t INDEX " << i << "\n";
                        // solve water  
                        acc += solve_water(bin);
                        std::cout <<  " ACC " << acc  << "\t\t";
                        //view bin
                        show_bin(bin);
                        //reset
                        bin.clear();
                        state = 0;
                        bin.push_back(curr);
                        state = state | (1 << 0);
                    }
                }
            
            
            prev = curr; 
        }
        
        return acc;
    }
};
