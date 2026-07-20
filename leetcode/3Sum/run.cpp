
#include <iostream>
#include "./Solution.h"
#include <chrono>

using Numbers = std::vector<int>; 

int main() {

    Numbers nums = {-1,0,1,2,-1,-4};
    auto start = std::chrono::steady_clock::now();
    Solution sol;
    sol.threeSum(nums);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << "\n";

}