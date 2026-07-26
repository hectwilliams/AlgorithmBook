#include "Solution.h"
#include <vector>
#include <iostream>
#include <deque>
#include <map>
#include <algorithm>
#include <numeric> 
#include <random>
#include <cassert> 
#include <array>
#include <stdexcept> // Required for standard exceptions

std::ostream& operator<<(std::ostream& os, const Histogram &h) {

    os << "[ ";
        
    for (const auto &[key, cnt]: h) {
        
        os << key;
        os << "[";
        os << cnt;
        os << "]";
        os << " ,";

    }
     
     os << " ]\n";

     return os;

}

std::ostream& operator<<(std::ostream& os, const PNode *node) {


    os << "[ ";
        
    for (const auto &[key, _]: node->histo) {
        
        os << key;
        
        os << ",";

    }
     
     os << " ]\n";

     return os;
}

    std::ostream& operator<<(std::ostream& os, const NumbersThreeNode &arr) {
            std::size_t i = 0;

     os << "[ ";
    for ( const auto node: arr ) {
        os << " " << node->acc <<  ( (i  == arr.size() - 1)? "" : "," ) ;
        i++;
    }
     os << " ]\n";

    return os; 

    }

std::ostream& operator<<(std::ostream& os, const std::array<int,2> &arr) {
    os << "[ ";
    os << " " << arr[0] ;
    os << ", " << arr[1]  ;
    
    os << " ]\n";

    return os;
}

std::ostream& operator<<(std::ostream& os, const std::array<int,3> &arr) {
    os << "[ ";
    os << " " << arr[0] ;
    os << ", " << arr[1]  ;
    os << ", " << arr[2]  ;
    
    os << " ]\n";

    return os;
}


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

std::ostream& operator<<(std::ostream& os, const CNode *node) {

     os << "[ ";
     
     os << node->prevnode->prevnode->value;
     
     os << ",";

     os << node->prevnode->value;
     
     os << ",";

     os << node->value;

     os << " ]\n";

     return os;

}

 
int first_positive_index(const Numbers &nums) {

    int pos_left = 0;
    int pos_right = nums.size() - 1;
    int sample_left = nums[pos_left];
    int sample_right = nums[pos_right];
    unsigned long watchdog = 1;
    
    while ( 1 ) {
        
        sample_left = nums[pos_left];


        sample_right = nums[pos_right];

        if (!(sample_left <= 0 && sample_right > 0) )
            break; 
            
        // std::cout << pos_right << "\n";

        pos_right--;
        pos_left++;
        
        watchdog++;

        if (watchdog == 0 || watchdog > nums.size())
            break;

    }

    if (sample_left > 0) {
        // std::cout << "left" << "\n";
        return pos_left;
    } else  {
        // std::cout << "right" << "\n";
        return pos_right + 1;

    }
}


void set_histogram(Numbers numbers, Histogram &histogram, Histogram &histogram_pos) {

    bool is_odd = (numbers.size() % 2 == 1);
    int half_length = numbers.size()/2;

    int left = 0;
    int right = numbers.size() - 1;

    int a;
    int b;

    for (int i = 0; i < half_length; i++) {
        
        a = numbers[left + i];
        b = numbers[right - i];

        if (histogram.count(a) == 0) {
            histogram[a] = 0;

            if (a > 0)
                histogram_pos[a] = 1;

        }
        histogram[a] += 1;
        
        if (histogram.count(b) == 0) {
            histogram[b] = 0;

            if (b > 0)
                histogram_pos[b] = 1;

        }
        histogram[b] += 1;
    }

    if (is_odd) {
        
        a = numbers[half_length];

         if (histogram.count(a) == 0) {
            histogram[a] = 0;
            
            if (a > 0)
                histogram_pos[a] = 1;
        }
        histogram[a] += 1;
    }
}

void sort_list(Numbers &numbers) {

    std::sort(numbers.begin(), numbers.end(), [](int a, int b){  return a < b ; });

}

void process_value (const int &value, Histogram &histo,  Numbers data, std::map<int, std::map<int, std::map<int, void*>>> path_map, std::vector<Numbers > &data_return) {

    Histogram histogram_pad = histo;
    int sum; 

    if (histo[value]) {
        
        
        std::sort(data.begin(), data.end(), [](int a, int b) {return a < b;});

        sum = std::accumulate(data.begin(), data.end(), 0);
        
        histogram_pad = histo;

        if (sum == 0) {

            std::cout << data << "\n";

            bool bin_exhausted = false;

            for (const auto &c: data) {
                bin_exhausted |= +( histogram_pad[c] <= 0 );
                histogram_pad[c]--;
            } 
            
            if ( !bin_exhausted && path_map[ data[0] ][ data[1]].count(data[2])  == 0) {
                // catch if fetch fails 
                
                path_map[ data[0] ][ data[1]][data[2]] = nullptr;
                
                // std::cout << data;
                data_return.push_back(data);

            }  
            
        }

    }
}

std::vector<Numbers > Solution::threeSum(Numbers& nums) {
    
    std::vector<Numbers > data_return;
    std::map< int, int > histo{}; 
    std::map< int, int > histo_pos{}; 

    int pos_index;

    Numbers eff_nums = nums;

    sort_list(eff_nums);
    set_histogram(eff_nums, histo, histo_pos);

    pos_index = first_positive_index(eff_nums);

     
     Numbers positive_io{};
     Numbers other_io{};
     
     other_io.clear();
     other_io.reserve(pos_index );
     other_io.assign(eff_nums.begin(), eff_nums.begin() + pos_index);
     
     // assign concat nodes to positive
     positive_io.clear();
     positive_io.reserve(eff_nums.size()  - pos_index );
     positive_io.insert(positive_io.end(), eff_nums.begin() + pos_index, eff_nums.end() );
    
     std::map<int, std::map<int, std::map<int, void*>>> path_map;

     Numbers output;
     int sample;
     int next = 0;
     int last = 0;
     int sum = 0;
     int value;
    int count  = other_io.size();
    int threshold_other_io =-1;
    
    if (positive_io.size()) {

        threshold_other_io = positive_io[positive_io.size() - 1];

    }
    

    std::cout << positive_io;

    std::cout << other_io;

    // left to right 

    for (int col = other_io.size() - 1; col  >= 0; col--) {

        for (int row = col ; row  >= 0; row--) {
            
            value = (other_io[col] + other_io[row]) * -1;
            
            Numbers data {value, other_io[col], other_io[row]};
            
            process_value(value, histo, data, path_map, data_return);

            if (threshold_other_io !=- 1 && value >=  threshold_other_io) {
                break;
            }

        }
        
    }

    return data_return;

}




