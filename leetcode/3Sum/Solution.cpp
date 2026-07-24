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

void handler_histo (int value, std::map <int, int> &table) {

    if (table.count(value) == 0){
        table[value] = 0;
    }
    table[value]+= 1;
}

void process_helper( const int &o,  const int &p, Vertices &vertices,  int depth, Histogram histo, Numbers &recent_sums ,  std::map<int, void*> &unique_sum_vertex_id, std::vector<Numbers> &ref_out) {
  
    bool zero_sum_mode{ depth == (N_SUM - 1) };


    if (o > 0 && p > 0) {

        return; 

    } else {
        
        int s = p + o;

        if (zero_sum_mode && s!=0) {
            return;
        }

        if (vertices.count(s) == 0) {
            vertices[s] =  new TNode{s, {}, depth};
        }

        if (unique_sum_vertex_id.count(s) == 0) {
            // capture summation '' nodes 
            recent_sums.push_back(s);
            unique_sum_vertex_id[s] = nullptr;
        }

        bool stop = false; 
        // find childs that produce sum of s 

        for (const auto pnode_o: vertices[o]->intercect) {
            for (const auto pnode_p: vertices[p]->intercect) {
                
                std::vector< int > potential_path = pnode_o->path;
                
                // if (potential_path.size() == N_SUM)
                //     std::cout  << "\t\t\t\t\t\tPOTENTIAL\t" << potential_path << "\n";

                potential_path.insert(potential_path.end(), pnode_p->path.begin(), pnode_p->path.end());
                
                std::sort(potential_path.begin(), potential_path.end(), [](int &a, int &b){return a < b;} );

                if (potential_path.size() != depth + 1) {
                    // try another potential path 
                    continue;
                }

                // does new link exist already 

                bool path_exists = false;
                for (const auto parent: vertices[s]->intercect) {
                    int count = 0;
                    if (potential_path.size() == parent->path.size())  {
                        
                        for(int i = 0; i < potential_path.size(); i ++) {
                            count += +(potential_path[i] == parent->path[i]);
                        }

                        if (count == potential_path.size()) {
                            path_exists = true;
                            break;
                        }
                    }

                }
                
                
                if (!path_exists) {
                    
                    // adding new path to parent node 
                    
                    int acc = std::accumulate(potential_path.begin(), potential_path.end(), 0);   
                    
                    Histogram ho = pnode_o->histo;
                    Histogram hp = pnode_p->histo;
                    Histogram  new_histo;
                    int next_depth;
                    
                
                    // std::cout << " BEFORE :\n"  ;
                    // std::cout << " LEFT  \n" << pnode_o->histo;
                    // std::cout << " RIGHT  \n" << pnode_p->histo;



                    if (pnode_o->depth == 0 && pnode_p->depth == 0  ) {

                        new_histo = histo;

                        new_histo[p]+= -1;
                        new_histo[o]+= -1;

                        // std::cout << new_histo;
                        
                        next_depth = 1;

                    } else if (pnode_o->depth != 0 && pnode_p->depth == 0 ) {

                      

                        // std::cout << potential_path;
                        next_depth = pnode_o->depth + 1;
                        
                        new_histo = pnode_o->histo;
                        // std::cout << "BEFORE " << new_histo ;

                        new_histo[p] += -1;
                        // std::cout << " AFTER " << new_histo ;
                        

                    } else if (pnode_o->depth == 0 && pnode_p->depth != 0 ) {
                        // std::cout << "ARGUE WON\n";
                        // std::cout << vertices[p]->depth  << "\n";
                        // std::cout << vertices[o]->depth  << "\n";
                        // std::cout << vertices[s]->depth  << "\n";
                        // std::cout << p<< "\n";
                        // std::cout << o<< "\n";
                        // std::cout << s<< "\n";
                        // std::cout << pnode_o->depth<< "\n";
                        // std::cout << pnode_p->depth<< "\n";
                        
                        // std::cout << potential_path;
                        next_depth = pnode_p->depth + 1;
                        
                        new_histo = pnode_p->histo;
                        // std::cout << "BEFORE " << new_histo ;

                        new_histo[o] += -1;
                        // std::cout << " AFTER " << new_histo ;

                    }

                    // new pnode 
                    PNode *new_pnode = new PNode{potential_path, new_histo, depth};
                    
                    if (s == acc) {

                        // std::cout << " EXISTS: "<< (path_exists? 1: 0) <<  "  VALUE GOAL: " << s << " " << potential_path;
                        // std::cout << "VALUE GOAL: " << s << " " << potential_path ;
                        if (potential_path.size() == N_SUM && s == 0) {
                            ref_out.push_back(potential_path);
                        }
                        // std::cout << "NEW HISTO: \n" << new_histo ;
                        // std::cout << "\n-----\n";
                        vertices[s]->intercect.push_back(new_pnode);
                        stop = true;
                        break;
                    }
                    
                } 
                
            }
            
            if (stop)
                break; 
        }

        // new path

        PNode *pnode = new PNode{};
    }

}

void sort_split(Numbers collection, const Numbers &raw, Histogram &histo, Vertices &vertices , int depth, Numbers &other_io, Numbers &positive_io, int &pos_index) {
    
    Numbers eff_nums;

    Numbers indices(collection.size());
    std::map< std::array<int, 2>, int > histo_pad{}; 
    std::iota(indices.begin(), indices.end(), 0 );

    if (depth == 0) {
        std::cout << "INIT" << "\n";
        

        std::sort(
            indices.begin(), 
            indices.end(), 
            [  &collection, &histo_pad, &histo, &vertices] (int index_i, int index_j)  {

                int a = collection[index_i];
                int b = collection[index_j];
                
                if (histo_pad.count({index_i, a})== 0 ) {
                    histo_pad[{index_i, a} ] = 1;
                    
                    if (histo.count(a) == 0) {
                        histo[a] = 0;
                    }
                    
                    histo[a]++;
                    // vertices[a] =  new TNode{a, {}, 0};
                    
                }

                if (histo_pad.count({index_j, b})== 0 ) {
                    histo_pad[{index_j, b} ] = 1;

                    if (histo.count(b) == 0) {
                        histo[b] = 0;
                    }

                    histo[b]++;
                    // vertices[b] =  new TNode{b, {}, 0};

                }

                return a < b;
            }
            
        );

        eff_nums.reserve(collection.size());
        std::transform(indices.begin(), indices.end(), std::back_inserter(eff_nums),[&collection](const int & index) { return collection[index];});

        pos_index = first_positive_index(eff_nums);

        other_io.clear();
        other_io.reserve(pos_index + 1);
        other_io.assign(eff_nums.begin(), eff_nums.begin() + pos_index);

        positive_io.clear();
        positive_io.reserve(eff_nums.size() - pos_index);
        positive_io.assign(eff_nums.begin() + pos_index, eff_nums.end());

        // set histo 
        for (const auto  &[vertex_id, _ ] : histo) {
            
            intersectVertices list{ new PNode{ {vertex_id}, histo, 0} };
            vertices[vertex_id] =  new TNode{ vertex_id , list, 0};
            Histogram histo_new = histo;
            // histo_new[vertex_id]  // used resource (decr)
            vertices[vertex_id]->intercect.push_back(new PNode{{vertex_id}, histo_new});
        }

        std::cout << histo;


    } else {
        
        Numbers recent_sums = collection; // unique sums from process 
        
        Numbers raw_concat_recent_sums;
        
        raw_concat_recent_sums.insert(raw_concat_recent_sums.end(), raw.begin(), raw.end());
        
        std::sort(recent_sums.begin(), recent_sums.end(), [](int a, int b){  return a < b ; });

        std::sort(raw_concat_recent_sums.begin(), raw_concat_recent_sums.end(), [](int a, int b){  return a < b ; });
        
        auto end = std::unique(raw_concat_recent_sums.begin(), raw_concat_recent_sums.end()); // index of first duplicate (encode of uniqueness)
        
        raw_concat_recent_sums.erase(end, raw_concat_recent_sums.end());

        // assign sum nodes to other
        other_io.clear();
        other_io.reserve(recent_sums.size());
        other_io.assign(recent_sums.begin(), recent_sums.end());

        // assign concat nodes to positive
        positive_io.clear();
        positive_io.reserve(raw_concat_recent_sums.size());
        positive_io.assign(raw_concat_recent_sums.begin(), raw_concat_recent_sums.end());


    }

   
}

void process(Numbers other, Numbers positive, Vertices &vertices, int depth, Histogram histo,  Numbers &io , std::vector<Numbers> &ref_out) {

    int o;
    int p;
    bool zero_sum_mode{ depth == N_SUM - 1 };
    Numbers recent_sums{};
    Numbers list; 
    std::map<int, void*> unique_sum_vertex_id;
    
    std::cout << other;
    std::cout << positive;


    
    if (depth < N_SUM  ) {
        
        io.clear();

        for (std::size_t i = 0; i < positive.size(); i++) {
            for (std::size_t j = 0; j < other.size(); j++) {
                p = positive[i];
                o =  other[j];
                
                // if (p + o  == 0 && depth == N_SUM - 1)
                //     std::cout << " \t\t\t\t SUM \t" << (p + o) << "\n";

                process_helper(o, p, vertices, depth, histo, io, unique_sum_vertex_id ,ref_out);
            }
        }

    } else {
        
        // for (std::size_t i = 0; i < positive.size(); i++) {
        // for (std::size_t j = 0; j < other.size(); j++) {
        //     p = positive[i];
        //     o =  other[j];
        //     if ( p  > 0 && o > 0)
        //         return;
        //     process_helper(o, p, vertices, depth, histo, io);
        // }
        // }



    }
}

int first_positive_index(const Numbers &nums) {

    int mid = nums.size()/2;
    int pos_left = 0;
    int pos_right = nums.size() - 1;
    int sample_left = nums[pos_left];
    int sample_right = nums[pos_right];
    int watchdog = 1;
    
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

std::vector<Numbers > Solution::threeSum(Numbers& nums) {
    
    std::map< int/* number */ , std::map<int, bool> /* indices map */ > v_map; // values map 
    std::vector<Numbers > data_return;
    std::map< int, int > histo{}; 
    Numbers eff_nums = nums;
    Vertices vertices;
    intersectVertices intersect_vertices;

    int pos_index = 0;
    int loop = 0;
    Numbers other_list{};
    Numbers pos_list{};
    Numbers raw{};
    
    eff_nums.clear();
    eff_nums = nums;

    sort_split(eff_nums, raw, histo, vertices, loop , other_list, pos_list, pos_index );

    raw.insert(raw.end(), other_list.begin(), other_list.end());
    raw.insert(raw.end(), pos_list.begin(), pos_list.end());

    while (loop < N_SUM - 1) {
        
        loop++;

        process(other_list, pos_list, vertices, loop, histo, eff_nums, data_return);

        if (loop < N_SUM - 1)
            sort_split(eff_nums, raw, histo, vertices, loop , other_list, pos_list, pos_index );

    }    
    return data_return;

}




