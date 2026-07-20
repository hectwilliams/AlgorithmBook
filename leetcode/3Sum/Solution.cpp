#include "Solution.h"
#include <vector>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Numbers& numbers) {
    std::size_t i = 0;

     os << "[ ";
    for ( const auto &value: numbers ) {
        os << " " << value <<  ( (i  == numbers.size() - 1)? "" : "," ) ;
        i++;
    }
     os << " ]\n";

    return os; 
}

std::ostream& operator<<(std::ostream& os, const NumbersArray& numbers_2D) {
    
    for ( const auto &numbers: numbers_2D ) {
        os << numbers << "\n";
    }
    return os;
}

std::vector<std::vector<int> > Solution::threeSum(std::vector<int>& nums) {
    
    std::vector<std::vector<int> > data;
    
    Numbers nums1 = {-1,0,1,2,-1,-4};
    Numbers nums2 = {-1,0,1,2,-1,-4};

    for ( const auto &ref : nums ) {
        std::cout << ref << "\n";
    }

    data.push_back(nums1);
    data.push_back(nums2);
    std::cout << data;

    return data;

}



