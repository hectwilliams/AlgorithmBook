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

void process(Numbers &other, Numbers &positive, Vertices &vertices, Numbers &raw_pos, Numbers &raw_other, int depth, std::map<int, int> histo) {

    int o;
    int p;
    bool zero_sum_mode{ depth == N_SUM - 1 };

    for (std::size_t i = 0; i < positive.size(); i++) {
        for (std::size_t j = 0; j < other.size(); j++) {
                    
            p = positive[i];
            o =  other[j];

            if (o > 0 && p > 0) {

                return; 

            } else {

                if ( vertices[o]->depth == 0 & vertices[p]->depth == 0) {
                    std::map<int, int> histo_next = histo;
                    vertices[o]->intercect.push_back(new PNode{{o}, histo_next});
                    histo_next[o]+= -1;
                    
                    histo_next = histo;
                    vertices[p]->intercect.push_back(new PNode{ {p}, histo_next});
                    histo_next[p]+= -1;
                }
                
                int s = p + o;

                if (zero_sum_mode && s!=0) {
                    continue;
                }

                if (s > 0) {
                    raw_pos.push_back(s);
                } else {
                    raw_other.push_back(s);
                }
                
                if (vertices.count(s) == 0) {
                    vertices[s] =  new TNode{s, {}, depth};
                }

                bool stop = false; 
                // find childs that produce sum of s 

                for (const auto pnode_o: vertices[o]->intercect) {
                    for (const auto pnode_p: vertices[p]->intercect) {
                        
                        std::vector< int > potential_path = pnode_o->path;
                        
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
                            
                            // merge new histogram 
                            for (const auto &[key , _]: histo) {
                                
                                if (ho[key] <= hp[key]) {
                                    new_histo[key] = ho[key];
                                } else {
                                    new_histo[key] = hp[key];
                                }
                            }
                        
                            // std::cout << " BEFORE :\n"  ;
                            // std::cout << " LEFT  \n" << pnode_o->histo;
                            // std::cout << " RIGHT  \n" << pnode_p->histo;
                            

                            if (new_histo[p] <= 0)
                                continue;
                            
                            if (new_histo[o] <= 0)
                                continue;
                            
                            new_histo[p]+= -1;
                            new_histo[o]+= -1;

                            // std::cout << " AFTER :\n"  ;
                            // std::cout << " LEFT  \n" << pnode_o->histo;
                            // std::cout << " RIGHT  \n" << pnode_p->histo;
                            

                            // new pnode 
                            PNode *new_pnode = new PNode{potential_path, new_histo};
                            
                            // 
                            if (s == acc) {
                                std::cout << " EXISTS: "<< (path_exists? 1: 0) <<  "  VALUE GOAL: " << s << " " << potential_path;

                                std::cout << "VALUE GOAL: " << s << " " << potential_path ;
                                std::cout << "NEW HISTO: \n" << new_histo ;
                                std::cout << "\n-----\n";
                                vertices[s]->intercect.push_back(new_pnode);
                                stop = true;
                                break;
                            }
                            
                        } else {

                            // stop = true;
                            // break;
                        }
                    
                    }
                    
                    if (stop)
                        break; 

                }

                // new path

                PNode *pnode = new PNode{};
                
            }
            
        }
    }

    return;
}

std::vector<Numbers > Solution::threeSum(Numbers& nums) {
    
    std::map< int/* number */ , std::map<int, bool> /* indices map */ > v_map; // values map 
    std::vector<Numbers > data_return;
    // std::map< Numbers , bool > unique_map; // values map 
    // std::map< int, int > neg_map{}; 
    // std::map< int, int > pos_map{}; 
    // std::map< int, int > zero_map{}; 
    // std::map< int, std::vector<std::array<int,2>> > sum_2_assoc_map{}; 
    std::map< int, int > histo{}; 
    // int first_pos_index{-1};
    // bool zero_set_exist{false};
    // int first_zero_index{-1};
    // int last_zero_index{-1};
    // NumbersThreeNode pos_numbers;
    // std::map< int , bool > unique_map_pos; // values map 

    // NumbersThreeNode other_numbers;
    Numbers eff_nums = nums;

    Vertices vertices;

    Numbers pos_list, pos_list_next_buffer, last_stage_numbers, raw_pos, raw_other;
    Numbers other_list, other_list_next_buffer;
    std::vector<TNode*> recycle_bin;
    intersectVertices intersect_vertices;

    // std::map<int , Network> VerticesTable;
    
    // set vertices  only

    // sort indices using values 
    // indices 
    
    std::map< std::array<int, 2>, int > histo_pad{}; 

    Numbers indices(nums.size());
    std::iota(indices.begin(), indices.end(), 0 );

    // sort indices using values 
    // setup histo 
    // setup vertices (lowest layer)
    std::sort(
        indices.begin(), 
        indices.end(), 
        [ &nums, &histo_pad, &histo, &pos_list_next_buffer, &other_list_next_buffer, &vertices](int index_i, int index_j)  {

            int a = nums[index_i];
            int b = nums[index_j];
            
            if (histo_pad.count({index_i, a})== 0 ) {
                histo_pad[{index_i, a} ] = 1;
                
                if (histo.count(a) == 0) {
                    histo[a] = 0;
                }
                
                histo[a]++;
                vertices[a] =  new TNode{a, {}, 0};
                
                if (a > 0 )
                    pos_list_next_buffer.push_back(a);
                else 
                    other_list_next_buffer.push_back(a);
            }

            if (histo_pad.count({index_j, b})== 0 ) {
                histo_pad[{index_j, b} ] = 1;

                if (histo.count(b) == 0) {
                    histo[b] = 0;
                }

                histo[b]++;
                vertices[b] =  new TNode{b, {}, 0};

                if (b > 0 )
                    pos_list_next_buffer.push_back(b);
                else 
                    other_list_next_buffer.push_back(b);

            }

            return a < b;
        }
    );

    // std::cout << histo;

    // assert(0);

    // for (const int &v: eff_nums) {
    //     // recycle_bin.push_back(vertices[v]);
    //     vertices[v] =  new TNode{v, {}, 0};

    // }


    // for (const int &v: eff_nums) {
    //      vertices[v]->histogram = histo;
    // }

    int pos_count = pos_list_next_buffer.size();
    int others_count = other_list_next_buffer.size();

    pos_list.reserve(nums.size() * 2);
    other_list.reserve(nums.size() * 2);
    raw_pos.reserve(nums.size() * 2); 
    raw_other.reserve(nums.size() * 2);

    // set network  
    int loop = 0;
    while (loop < N_SUM - 1) {
        
        loop++;

        pos_list.insert(pos_list.end(), pos_list_next_buffer.begin(), pos_list_next_buffer.end());
        other_list.insert(other_list.end(), other_list_next_buffer.begin(), other_list_next_buffer.end());
        process(other_list, pos_list, vertices, raw_pos, raw_other, loop, histo);

        // trumcare pos and other list to size  (i.e. pos count) 

        // update pos list and other list 

        // clear raws 
        

        // pos_list_next_buffer.clear();
        // other_list_next_buffer.clear();
        

        // bool stop = false;
        // int o;
        // int p;
        // for (std::size_t i = 0; i < pos_list.size(); i++) {
        //     for (std::size_t j = 0; j < other_list.size(); j++) {

        //         o = pos_list[i];
        //         p =  other_list[j];
        //         int s = p + o;

        //         stop = p > 0 && o > 0;
                
        //         if (stop)
        //             break;
                
        //         TNode *child_o  = vertices[o];
        //         TNode *child_p = vertices[p];
        //         TNode *parent_vertex;
                
        //         std::array <TNode* , 2 > record= {child_o, child_p};
                
        //         if (vertices.count(s) == 0) {
        //             parent_vertex = new TNode{s, { }, child_o->depth + 1};
        //             vertices[s] = parent_vertex;
        //         } 
        //         vertices[s]->intercect[  record ] = nullptr;

        //         // if (vertices.count(s * -1) ) {
        //         //     int s_compliment = s * -1;
        //         //     TNode *node = vertices[s_compliment];
                    
        //         //     std::array <TNode* , 2 > record= {node, nullptr};
                    
        //         //     node->intercect[record] = nullptr;

        //         // }


        //         // if(loop == 0) {
        //         //     // init hisogram table 
        //         //     child_o->histogram = histo;
        //         //     child_p->histogram = histo;
        //         // }

        //         // std::map<int, int> new_histogram = child_o->histogram; // copy
        //         // new_histogram.insert(child_o->histogram.begin(), child_o->histogram.end()); // copy
                
        //         // // new/referenced vertex 
        //         // if ( vertices.count(s) == 0 ) {
        //         //     // register new node to vertex 
        //         //     new_histogram[s] = 1; // persists 
        //         //     parent_vertex = new TNode{s, {}, new_histogram, child_o->depth + 1};
        //         //     vertices[s] = parent_vertex;
        //         // } else {
        //         //     parent_vertex = vertices[s];
        //         // }

        //         // if ( parent_vertex->histogram[o] <=  0  || parent_vertex->histogram[p] <=0) {
        //         //     // not enough resources (values) to register new vertex 
        //         //     continue;
        //         // } else {
        //         //     parent_vertex->histogram[o]--;
        //         //     parent_vertex->histogram[p]--;
        //         // }

        //         // parent_vertex->intercect[ {child_o, child_p}] = nullptr;

        //         /*

        //         update possible search values for next iteration (Four sum problem)

        //             - combine depth sums with all possible characters from init 

        //             - sort values 

        //             - split at midpoint 

        //             - sum 

        //             - continue until loop hits final count 

        //         // */

        //         // if (s > 0 )
        //         //     pos_list_next_buffer.push_back(s); // this should actually be positive vertex values (depth =o) values 
        //         // else 
        //         //     other_list_next_buffer.push_back(s);
        //     }
            

            
        //     stop = p > 0 && o > 0;

        //     if (stop) {

        //         break;
        //     }
        // }


    }

    // // // final stage 
    // last_stage_numbers = pos_list_next_buffer;
    // last_stage_numbers.reserve (pos_list_next_buffer.size() + other_list_next_buffer.size() );
    // last_stage_numbers.insert(last_stage_numbers.end(), other_list_next_buffer.begin(), other_list_next_buffer.end());

    // int count = 0;
    // // std::cout << "\t"  << 2233333 << "\n";

    // for (const auto &sum: last_stage_numbers) {

    //     int target = sum * -1;
        
    //     if (vertices.count(target) == 0) 
    //         continue; 

    //     TNode * curr_node = vertices[target];

    //     if (curr_node->depth !=0) {
    //         continue;
    //     }
        
    //     count++;
    // }
    // // std::cout << "\t"  << 2233333 << "\n";

    // std::cout << "\t"  << count << "\n";

 // network[o]->next_network =  new Network{p, {}};
            
            // if (network[p].count(s) == 0) {
                //     network[p] = new TNode{s, {}, {}};
                // }
                
                // if (network[o].count(s) == 0) {
                    //     network[o] = new TNode{s, {}, {}};
                    // }
    


    // // test zero three sum
    // if (histo.count(0)) {
    //     if (histo[0] >= N_SUM) {
    //         data_return.push_back({0,0,0});
    //     }
    // }

    // // sort indices using values 
    // std::sort(
    //     eff_nums.begin(), 
    //     eff_nums.end(), 
    //     [  &nums](int a, int b)  {
    //         return a < b;
    //     }
    // );


    // // find first position 
    // int index = 0;
    // for (const auto  &[v, _]: histo) {

    //     // if (v == 0) {
    //     //     if (first_zero_index == -1) {
    //     //         first_zero_index = index; 
    //     //     }

    //     //     if (index == eff_nums.size() - 1) {
    //     //         last_zero_index = index; 
    //     //     } else if (index + 1 < eff_nums.size() && eff_nums[index + 1] > 0 && eff_nums[index] == 0 ) {
    //     //         last_zero_index = index; 
    //     //     }
    //     // }

      

    //     if (v > 0) {
    //         pos_numbers.push_back(new thrNode{v, {v}, histo, 1});
    //         // if (unique_map_pos.count(v)  == 0) {
    //             // unique_map_pos[v] = true;
    //         // }
    //     } else {
    //         other_numbers.push_back(new thrNode{v, {v}, histo, 1});
    //         // if (unique_map_other.count(v)  == 0) {
    //         //     unique_map_other[v] = true;
    //         // }
    //     }

        



    //     // index++;
    // }

    // std::cout << pos_numbers;
    // std::cout << other_numbers;

    // // // 1st sum block 

    // // std::map< std::array<int,3>, bool > unique_set_arr3{}; // unique_arr2 map 
    // // std::map< Numbers, bool > unique_set_v{}; // unique_arr2 map 
    // std::deque<thrNode*> q; 
    // NumbersThreeNode others_next = other_numbers;
    // NumbersThreeNode pos_next = pos_numbers;
    // int sum_loop = 0;
    // NumbersThreeNode recycle_nodes;

    
    // while (sum_loop < N_SUM - 2) {

    //     q.clear();

    //     pos_numbers = pos_next;
    //     other_numbers = others_next;

    //     others_next.clear();
    //     pos_next.clear();


    //     for (int i = 0; i < pos_numbers.size() ; i++) {

    //         for(int k = 0; k < other_numbers.size(); k ++) {
                
    //             thrNode *node0 = other_numbers[k];
    //             thrNode *node1 = pos_numbers[i];

    //             int acc0 = node0->acc;
    //             int acc1 = node1->acc;
                
    //             // check connections 

    //             // if () {
    //             //     // already exists
    //             //     std::cout << "failuing" << "\n";
    //             //     continue; 
    //             // } 
                    
    //             // connections[acc0][acc1]= true;
    //             // connections[acc1][acc0]= true;

    //             int new_acc = acc0 + acc1;
                
    //             std::map<int, int> new_histo = node0->histo;
    //             new_histo.merge(node1->histo);

    //             new_histo[acc0]--;
    //             new_histo[acc1]--;

    //             if (new_histo.count(acc0) == 0)
    //                 new_histo.erase(acc0);
    //             if (new_histo.count(acc1) == 0)
    //                 new_histo.erase(acc1);

    //             std::vector<int> new_values = node0->values;
    //             new_values.push_back(acc1);

    //             int next_depth = node0->depth + 1;
                
    //             thrNode *new_node = new thrNode{ new_acc, new_values, new_histo , next_depth };

    //             q.push_back(new_node);
                
    //             // new stage ? 
    //             if (new_node->acc > 0)
    //                 pos_next.push_back(new_node);
    //             else 
    //                 others_next.push_back(new_node);
                
    //             recycle_nodes.push_back(node0);
    //             recycle_nodes.push_back(node1);

    //             // std::map<int, int> h = histo;
                
    //             // h[ other_numbers[k]]--;
    //             // h[ pos_numbers[i]]--;

    //             // if (h.count(other_numbers[k]) == 0)
    //             //     h.erase(other_numbers[k]);
                
    //             // if (h.count(pos_numbers[i]) == 0)
    //             //     h.erase(other_numbers[i]); 

    //             // thrNode *node = new thrNode{ other_numbers[i] + pos_numbers[k], {other_numbers[i] ,pos_numbers[k]}, h, 1 }; 
    //             // q.push_back(node);

    //             // // store sums for next stage 
    //             // if (node->acc > 0 ) {
    //             //     pos_next.push_back(node->acc);
    //             // } else  {
    //             //     others_next.push_back(node->acc);
    //             // }

    //         }
    //     }

    //     sum_loop++;
    // }


    // std::cout << "SIZE: " << q.size() << "\n";

    // while (!q.empty()) {

    //     thrNode *node = q.front();
    //     q.pop_front();

    //     int return_acc = node->acc * -1;
    //     int prev_acc0 = node->values[0];
    //     int prev_acc1 = node->values[1];

    //     int summ = prev_acc0 + prev_acc1 + return_acc;
    //     std::map< std::array<int, 2> , bool> histo_check;
        
    //     if (node->histo.count(return_acc) ) {
            
    //         if (node->histo[return_acc] > 0) {
                
    //             Numbers set;
                
    //             std::array<int,2> p0 {return_acc, prev_acc0};
    //             std::array<int,2> p00 {prev_acc0,  return_acc};

    //             std::array<int,2> p1 {return_acc, prev_acc1};
    //             std::array<int,2> p11 {prev_acc1,  return_acc};

    //             if ( histo_check.count(p0) == 0 && histo_check.count(p1) == 0  && histo_check.count(p00) == 0 && histo_check.count(p11) == 0) {

    //                 histo_check[p0]=true;
    //                 histo_check[p1]=true;
    //                 histo_check[p00]=true;
    //                 histo_check[p11]=true;

    //                 set = {return_acc, node->values[0], node->values[1]};
                    
    //                 // if (return_acc  < prev_acc0  ) {
    //                 // }
    //                 // else if (return_acc  > node->values[1] ) {
                        
    //                 //     set = {node->values[0], node->values[1], return_acc};
    //                 // }
    //                 // else  {
    //                 //     set = {node->values[0], return_acc, node->values[1] };
    //                 // }
                    
    //                 //  connections[return_acc][prev_acc0]= true;
    //                 //  connections[prev_acc0][return_acc]= true;

    //                 // connections[return_acc][prev_acc1]= true;
    //                 //  connections[prev_acc1][return_acc]= true;

    //                 std::cout << set << "\n";
    //             }
            
    //         }
    //     }
    //     // if (node.depth < N_SUM) {

    //     // }

    // }

    // std::cout << " SIZE QUEUE " << q.size() << "\n" ;

    return data_return;

}




