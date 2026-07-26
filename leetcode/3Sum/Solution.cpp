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


void set_histogram(Numbers numbers, Histogram *histogram, Histogram &histogram_pos) {

    bool is_odd = (numbers.size() % 2 == 1);
    int half_length = numbers.size()/2;

    int left = 0;
    int right = numbers.size() - 1;

    int a;
    int b;

    for (int i = 0; i < half_length; i++) {
        
        a = numbers[left + i];
        b = numbers[right - i];

        if ((*histogram).count(a) == 0) {
            (*histogram)[a] = 0;

            if (a > 0)
                histogram_pos[a] = 1;

        }
        (*histogram)[a] += 1;
        
        if ((*histogram).count(b) == 0) {
            (*histogram)[b] = 0;

            if (b > 0)
                histogram_pos[b] = 1;

        }
        (*histogram)[b] += 1;
    }

    if (is_odd) {
        
        a = numbers[half_length];

         if ((*histogram).count(a) == 0) {
            (*histogram)[a] = 0;
            
            if (a > 0)
                histogram_pos[a] = 1;
        }
        (*histogram)[a] += 1;
    }
}

void sort_list(Numbers &numbers) {

    std::sort(numbers.begin(), numbers.end(), [](int a, int b){  return a < b ; });

}

std::vector<Numbers > Solution::threeSum(Numbers& nums) {
    
    std::vector<Numbers > data_return;
    Histogram *histo = new Histogram{}; 
    std::map< int, int > histo_pos{}; 
    Numbers eff_nums = nums;
    Numbers data;
    int *sum = new int{};
    int value;
    int pos_threshold_other_io = -1;
    int neg_threshold_positive_io = -1;
    bool stop ; 
    int row_data;
    int col_data;
    int pos_index;
    std::map<int, std::map<int, std::map<int, void*>>> *path_map = new std::map<int, std::map<int, std::map<int, void*>>>{};


    sort_list(eff_nums);
    set_histogram(eff_nums, histo, histo_pos);

    pos_index = first_positive_index(eff_nums);

    Numbers *positive_io = new Numbers{};
    Numbers *other_io = new Numbers{} ;
    
    other_io->clear();
    other_io->reserve(pos_index );
    other_io->assign(eff_nums.begin(), eff_nums.begin() + pos_index);
    
    // assign concat nodes to positive
    positive_io->clear();
    positive_io->reserve(eff_nums.size()  - pos_index );
    positive_io->insert(positive_io->end(), eff_nums.begin() + pos_index, eff_nums.end() );


    data.reserve(3);
    data.insert(data.end(), {0,0,0});

    if (positive_io->size()) {

        pos_threshold_other_io = (*positive_io) [positive_io->size() - 1] ;

    }
    
    if (other_io->size()) {

        neg_threshold_positive_io = (*other_io)[ 0 ] ;

    }
    

    // all ones test 
    bool all_equal = eff_nums.empty() || std::all_of(eff_nums.begin(), eff_nums.end(), [&eff_nums](int element) { return element == eff_nums.front() && element == 0; });
    
    if (all_equal) {

        if (eff_nums.size() >=  N_SUM) {
            data_return.push_back({0,0,0} );
        }

    } else {

        for (int col = other_io->size() - 1; col  >= 0; col--) {
            
            for (int row = col - 1  ; row  >= 0; row--) {
                

                col_data = (*other_io)[col];
                row_data =  (*other_io)[row];
                value = (col_data + row_data) * -1;

                (*histo)[col_data]--; 
                (*histo)[row_data]--; 
                (*histo)[value]--; 

                int zero_sum = ( ((*histo)[col_data] == - 1  || (*histo)[row_data] == -1 ||  (*histo)[value] == -1 )  )  ;
                
                (*histo)[col_data]++; 
                (*histo)[row_data]++; 
                (*histo)[value]++; 

                if (zero_sum ) {
                    continue;
                }

                data[2] = value;

                if (row > col) {
                    
                    data[1] = row_data;
                    data[0] = col_data;
                    
                } else {
                    
                    data[0] = row_data;
                    data[1] = col_data;
                    
                }

                *sum = data[0] + data[1] + data[2];

                if (*sum == 0  ) {

                    if ( (*path_map)[ data[0] ][ data[1]].count(data[2])  == 0) {

                        (*path_map)[ data[0] ][ data[1]][data[2]] = nullptr;

                        data_return.push_back(data);

                    }  

                }

                if (pos_threshold_other_io !=- 1 && value >  pos_threshold_other_io) {
                    break; 
                }

            }
            
        }


        
        for ( int col = 0 ; col < (*positive_io).size(); col++ ) {

            for ( int row = col + 1 ; row  < (*positive_io).size(); row++ ) {
                
                col_data = (*positive_io)[col];
                row_data =  (*positive_io)[row];
                value = (col_data + row_data) * -1;
                
                (*histo)[col_data]--; 
                (*histo)[row_data]--; 
                (*histo)[value]--; 
                
                int zero_sum = ( ((*histo)[col_data] == - 1  || (*histo)[row_data] == -1 ||  (*histo)[value]  == -1 )  )  ;
                
                (*histo)[col_data]++; 
                (*histo)[row_data]++; 
                (*histo)[value]++; 
                
                if (zero_sum ) {
                    continue;
                }
                
                data[0] = value;

                if (row > col) {
                    
                    data[2] = row_data;
                    data[1] = col_data;
                    
                } else {
                    
                    data[1] = row_data;
                    data[2] = col_data;
                    
                }
                
                *sum = data[0] + data[1] + data[2];

                if (*sum == 0  ) {

                    if ( (*path_map)[ data[0] ][ data[1]].count(data[2])  == 0) {

                        (*path_map)[ data[0] ][ data[1]][data[2]] = nullptr;

                        data_return.push_back(data);

                    }  

                }
                    
                if (neg_threshold_positive_io !=- 1 && value <=  neg_threshold_positive_io) {
                    break;
                }
                

            }
            
        }

    }

    return data_return;

}




