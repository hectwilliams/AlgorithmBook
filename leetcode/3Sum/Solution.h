#pragma once // Prevents the header from being included more than once

#include <vector>
/*
    Purpose: solve leetcode 3Sum problem

    Author: HW 

    URL: https://leetcode.com/problems/3sum/

*/

using Numbers = std::vector<int>; 
using NumbersArray = std::vector<Numbers>;

class Solution {
public:
    std::vector<Numbers > threeSum( Numbers& nums);
    friend std::ostream& operator<<(std::ostream& os, const Numbers&  numbers );
    friend std::ostream& operator<<(std::ostream& os, const NumbersArray&  numbers_2D);
};

