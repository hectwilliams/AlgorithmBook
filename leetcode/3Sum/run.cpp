
#include <iostream>
#include "./Solution.h"
#include <chrono>

using Numbers = std::vector<int>; 

int main() {

    // Numbers nums = {-1,0,1,2,-1,-4};
    // Numbers nums = {-70,-100 ,-60,110,120,130,160};
    // Numbers nums = { 0, -1 ,1};
    Numbers nums = { 2,-3,0,-2,-5,-5,-4,1,2,-2,2,0,2,-4,5,5,-10 };

    auto start = std::chrono::steady_clock::now();
    Solution sol;
    NumbersArray result = sol.threeSum(nums);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << "\n";
    std::cout << " output \t " << result.size() << "\n";


}