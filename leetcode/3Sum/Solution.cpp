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

std::ostream& operator<<(std::ostream& os, const std::array<int,2> &arr) {
    os << "[ ";
    os << " " << arr[0] ;
    os << ", " << arr[1]  ;
    
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

bool read_three ( Numbers &data, CNode *node  ) {

    if (!node->prevnode)
        return false ;

    if (!node->prevnode->prevnode)
        return false;

    data.push_back(node->prevnode->prevnode->value);
    data.push_back(node->prevnode->value);
    data.push_back(node->value);

    // sort vector ( in place ) 
    std::sort(
        data.begin(), 
        data.end(), 
        [](int a, int b)  {
            return a < b;
        }
    );

    
    // zero sum boolean return 
    int sum = 0;

    sum = (node->prevnode->prevnode->value) + node->prevnode->value + node->value;

    return sum == 0;
}

void shift_vector(Numbers &inout, const Numbers & v ) {
    int tail_index = v.size() - 1 ;
    inout.clear();
    inout.insert( inout.end(),  {v[tail_index]}  );
    inout.insert( inout.end(), v.begin(), v.end() - 1);   
}

/* returns column with zero sum; -1 otherwise*/
int  sum_window_three (Numbers &a, Numbers &b, Numbers &c) {
    
    // col 0
    int col0 = a[0] + b[0] + c[0];
    
    // col 2
    int col1 = a[1] + b[1] + c[1];

    // col 3
    int col2 = a[2] + b[2] + c[2];

    if (col0 == 0)
        return 0;

    if (col1 == 0) 
        return 1;

    if (col2 == 0)
        return 2;

    return -1; 

}

void print_sets (const Numbers &a, const Numbers &b, const Numbers &c ) {

    std::cout << a[0] << " " << b[0]<< " " << c[0]<< " "  << " | \t" << a[1] << " " << b[1]  << " " << c[1]  << " " <<  " | \t"  <<  a[2]  << " " << b[2]  << " " << c[2]  << " " << "\n";

}

void test_zero_sum(int i, int i2, int v1, int v2, int v3,  std::map< int , std::map<int, bool>  >  & v_map,  std::vector<Numbers >  & data_io, std::map< Numbers , bool > &u_map ) {
    
    if ( (v3 + v1 + v2) == 0 &&  v_map.count(v3)) {
        
        auto lmap = v_map[v3];  

        // v3 must be a value with index exclusive to v1 and v2
        std::cout << "v1: " << v1 << " i= " << i << "\t" << "v2: "<<  v2 << " i2= " <<  i2 <<  " v3 " << v3  << "\n";

        // std::cout << "number of indices with value of v3: " << lmap.size() << "\n";
        // std::cout << "number of indices with value of v3: " << lmap.size() << "\n";



        // find index exclusive 
        auto it = std::find_if(
            lmap.begin(), 
            lmap.end(), 
            [i, i2]( const auto& pair) {
                // std::cout << " indices \t" << pair.first << " " << i << " " << i2 << "\n"; 
                // lmap is a list of indices; the condition block checks whether current index is unique compared to the index of the other two values 
                return pair.first  != static_cast<int>(i) && pair.first  != static_cast<int>(i2);
            }
        );

        // valid if unique indices found above
        if (it != lmap.end() ) {
            Numbers valid_entry_3Sum{v1, v2, v3};
            
            std::sort(
                valid_entry_3Sum.begin(), 
                valid_entry_3Sum.end(), 
                [](int a, int b)  {
                    return a < b;
                }
            );

            // std::cout << " " << valid_entry_3Sum[0] << " " << valid_entry_3Sum[1] << " " << valid_entry_3Sum[2] << "\n"; 
            
            // add valid unique three sum values  
            if (u_map.count(valid_entry_3Sum) == 0  &&  std::accumulate(valid_entry_3Sum.begin(), valid_entry_3Sum.end(), 0)  == 0) {
                u_map[valid_entry_3Sum] = true;
                data_io.push_back(valid_entry_3Sum);
            }

        }
    }
}


void random_values (Numbers & v) {
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // // Distribution for the amount of numbers (between 1 and 3000)
    std::uniform_int_distribution<int> count_dist(1, N_SAMPLES);
    // int total_numbers = count_dist(gen);
    
    // // Distribution for the actual values (for example, between 1 and 100)
    std::uniform_int_distribution<int> value_dist(-150, 150);
    
    // // 2. Generate and store the random numbers
    // // std::vector<int> random_values;
    // random_values.reserve(total_numbers); // Optimize memory allocation
    
    for (int i = 0; i < N_SAMPLES; ++i) {

        auto value = value_dist(gen);
        v.push_back(value);
        // std::cout << value << "\n";
        // random_values.push_back(value);
    }

}

void add_to_map ( const int v, std::map<int, int> &pos, std::map<int, int> &neg, std::map<int, int> &zero ) {
    std::map<int, int> *ref {nullptr}; 
        
    if (v < 0) {
        ref = &pos;
    } else if (v > 0) {
        ref = &neg;

    } else if (v == 0) {
        ref = &zero;
    }

    if (ref->count(v) == 0)  {
        (*ref)[v] = 0;
    }
    (*ref)[v]++;
}


/*
    validates sum vector with the number of resources available in object (i.e. histogram bin table models available resources )
*/
bool valid_sum (const Numbers &test_sum,  std::map<int, int> histo) {
    
    for (const int &v: test_sum) {
        
        if (histo[v] == 0) {
            // not enough resources 
            return false;
        }

        histo[v]--;
        
    }

    
    return true;
}

std::vector<Numbers > Solution::threeSum(Numbers& nums) {
    
    std::map< int/* number */ , std::map<int, bool> /* indices map */ > v_map; // values map 
    std::vector<Numbers > data_return;
    std::map< Numbers , bool > unique_map; // values map 
    std::map< int, int > neg_map{}; 
    std::map< int, int > pos_map{}; 
    std::map< int, int > zero_map{}; 
    std::map< int, std::vector<std::array<int,2>> > sum_2_assoc_map{}; 
    std::map< int, int > histo{}; 

    // std::map< int, bool > sum_3_assoc_map{}; used for 4sums 

    int first_pos_index{-1};

    if (EN_DEBUG) {
        Numbers nums2;
        random_values(nums2);
        nums = nums2;
    }

    // indices 
    Numbers indices(nums.size());
    std::iota(indices.begin(), indices.end(), 0 );

    // sort indices using values 
    std::sort(
        indices.begin(), 
        indices.end(), 
        [  &nums](int index_i, int index_j)  {
            int a = nums[index_i];
            int b = nums[index_j];
            return a < b;
        }
    );

    // transfrom indices to value (map)
    Numbers eff_nums(indices.size());
    int new_index = 0;
    std::transform(
        indices.begin(), 
        indices.end(), 
        eff_nums.begin(), 
        [ &nums, &v_map, &new_index, &neg_map, &pos_map, &zero_map, &first_pos_index, &histo ](int i) {

            int v = nums[i];
            // add_to_map(v, pos_map, neg_map, zero_map);

            if (histo.count(v) == 0){
                histo[v] = 0;
            }
            histo[v]+= 1;

            

            if (v_map.count(v) == 0) {
                v_map[v] = std::map<int, bool>  {};
            }
            v_map[v][new_index++] = true;

            if (v > 0 && first_pos_index == -1) {
                // first positive index
                first_pos_index = new_index - 1;
            }
            // std::cout << " hello world " << v << " " << ( new_index - 1 )  << "\n"  ;
            return nums[i];
        }
    );


    // print numbers 
    std::cout << eff_nums << "\n";
    // std::cout << pos_map.size() << "\n";
    // std::cout << neg_map.size() << "\n";
    // std::cout << zero_map.size() << "\n";
    // std::cout << first_pos_index << "\n";

    // branch network (fractal)
    int window_size = 2;
    while (window_size > 0) {
        
        int s_index = 0;
        int e_index = s_index + window_size - 1;
        
        std::map< std::array<int, 2> , bool > unique_arr2; // unique_arr2 map 

        while (e_index < eff_nums.size()) {
            
            int curr_sun = eff_nums[s_index] + eff_nums[e_index];
            
            if (sum_2_assoc_map.count(curr_sun) == 0) {
                sum_2_assoc_map[curr_sun] = {};
            }

            // sum_2_assoc_map[curr_sun].push_back( {eff_nums[s_index], eff_nums[e_index]} );
            std::array<int,2> entry = { eff_nums[s_index],  eff_nums[e_index] };
            std::cout << " TEST " << entry;

            
            // sort entry 
            std::sort(
                entry.begin(), 
                entry.end(),  
                [](int a, int b) {
                    return a < b;
                }
            );

            // add to sum_2_assoc_map map
            if (unique_arr2.count(entry) == 0) {
                sum_2_assoc_map[curr_sun].push_back( entry ); // capture potential sum 
            }

            s_index += 1;   //window_size - 1;
            e_index += 1;  // window_size - 1;
        }

        window_size++;
        
        if (s_index == 0) {
            // fractals stopped
            break;
        }
    }

    // find 3 sum 
    std::cout << "----" << "\n";

    std::map< Numbers, bool > unique_set{}; // unique_arr2 map 

    for ( auto &[accumulator, vector_of_arr2] : sum_2_assoc_map) {

        int next_acc = accumulator*-1;

        for (const std::array<int,2> arr2: vector_of_arr2 ) {

            if (v_map.count(next_acc)) {

                Numbers entry{arr2[0], arr2[1], next_acc}; // possible sum 
                
                // sort entry 
                std::sort(
                    entry.begin(), 
                    entry.end(),  
                    [](int a, int b) {
                        return a < b;
                    }
                );
                
                //
                if (!valid_sum(entry, histo)) {
                    continue;
                }

                // unique sum 
                if (unique_set.count(entry) == 0) {
                    unique_set[entry] = true;
                    data_return.push_back(entry);
                    std::cout << entry << "\n";
                }

            }
            
        }

    }

    return data_return;

}




