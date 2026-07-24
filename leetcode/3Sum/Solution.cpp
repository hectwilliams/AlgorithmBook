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


std::vector<int> find_path(TNode *node_a, TNode *node_b, int sum) {
    
    for (const auto  pnode_a: node_a->intercect ) {
        
        for (const auto  pnode_b: node_b->intercect ) {

            // std::cout << " TEST  NODE " << node_a->acc << " "  << pnode_a->path << "\n";
            // std::cout << " TEST  NODE " << node_b->acc << " "  << pnode_b->path << "\n";
            
            std::vector<int> new_path;
            
            new_path.insert(new_path.end(), pnode_a->path.begin(), pnode_a->path.end());

            new_path.insert(new_path.end(), pnode_b->path.begin(), pnode_b->path.end());

            std::sort(new_path.begin(), new_path.end(), [](int a, int b) {return a < b;} );

            int test_sum = std::accumulate(new_path.begin(), new_path.end(), 0);
            
            if (test_sum == sum) {
                // return new path 
                return new_path;
            } 
        }
        
    }

    
    return {};
}


void process_helper( const int &o,  const int &p, Vertices &vertices,  int depth, Histogram histo, Numbers &recent_sums ,  std::map<int, void*> &unique_sum_vertex_id,   std::map < std::array<int,2>, void*> &unique_pair_sum,  std::vector<Numbers> &ref_out) {
  
    bool zero_sum_mode{ depth == (N_SUM - 1) };

    if (o > 0 && p > 0 && depth == 1) {

        return; 

    } else {
        
        int s = p + o;

        if (vertices.count(s) == 0) {

            vertices[s] =  new TNode{s, {}, depth};
        }

        if (unique_sum_vertex_id.count(s) == 0) {
            // capture summation '' nodes 
            recent_sums.push_back(s);
            unique_sum_vertex_id[s] = nullptr;
        }

        //  if (zero_sum_mode && s==0) {
        //     std::cout << "ZERO SUM \n";
        //     std::cout  << " o:  "  << o << " --  ";
        //     std::cout << vertices[o]->depth << "\n";
        //     std::cout  << " p: " << p << "---  ";
        //     std::cout << vertices[p]->depth << "\n";

        //     std::cout << "NUMBER OF PATHS IN o: " << vertices[o]->intercect.size() << "\n";
        //     std::cout << "NUMBER OF PATHS IN p: " << vertices[p]->intercect.size() << "\n" ;

        // }

        // if (depth == 1) {
        //     std::cout << "----";
        //     std::cout  << " o:  "  << o << " --  ";
        //     std::cout  << " p: " << p << " ---  \n";
        //     std::cout << vertices[o]->depth << "\n";
        //     std::cout << vertices[p]->depth << "\n";
        //     std::cout << "----";
        // }

        TNode *node_o = vertices[o];
        TNode *node_p = vertices[p];
        TNode *node_s = vertices[s]; // should exist 

        Histogram ho ;
        Histogram hp ;
        Histogram  new_histo;
        
        int next_depth;

       ;

        if (depth == 1) {

            // find path producing sum from child nodes
            std::vector<int> path = find_path(node_o, node_p, s);

            std::cout << " PATH " << path;
            std::cout << " SUM " << s;

            new_histo = histo;
            
            new_histo[p]+= -1;
            new_histo[o]+= -1;

            next_depth = depth;
            
            
            if (unique_pair_sum.count({o, p}) == 0) {
                
                std::cout << "\n  NEXT PATH " << path << "\n";

                unique_pair_sum[{o, p}] = nullptr;
                unique_pair_sum[{p, o}] = nullptr;

                PNode *new_pnode = new PNode{path, new_histo, next_depth};
                
                vertices[s]->intercect.push_back(new_pnode);
            }
            
        } else {    
            std::cout << "\n\n";
            std::cout << " NODES - " << o << "  NODES - " << p << "\n";
            std::cout << " PARENT - " << s  <<"\n\n";

            std::vector<std::vector<int>> paths; 
            bool stop = false; 

            for (const auto pnode_o: vertices[o]->intercect) {
                for (const auto pnode_p: vertices[p]->intercect) { 
                
                    std::vector<int> new_path;
                    
                    new_path.insert(new_path.end(), pnode_o->path.begin(), pnode_o->path.end());


                    new_path.insert(new_path.end(), pnode_p->path.begin(), pnode_p->path.end());

                    std::sort(new_path.begin(), new_path.end(), [](int a, int b) {return a < b;} );

                    
                    int test_sum = std::accumulate(new_path.begin(), new_path.end(), 0);
                    
                    if (test_sum != s) 
                        continue;
                    
                    if (new_path.size() != depth + 1)
                        continue; 

                    std::cout << "NEXT PATH : " << "\n";
                    std::cout << "\t\t" << pnode_o->path << "\n";
                    std::cout << "\t\t" << pnode_p->path << "\n";
                    
                    // does path exist vertex (s) node 
                    bool exists = false;
                    int count = 0;
                    for (const auto &pnode_s: vertices[s]->intercect) {
                        if (pnode_s->path.size() == new_path.size()) {
                            for (int n = 0; n < new_path.size(); n++) {
                                count += +(new_path[n] == pnode_s->path[n]);
                            }
                            if (count == new_path.size() ) {
                                exists = true; // path already exists to summation node 
                                break;
                            } 
                        }
                    }

                    if ( !exists ) {

                        // can higher node loose a sample 
                        if (pnode_o->depth == 0 && pnode_p->depth != 0) {
                            // p is main path 
                            if (pnode_p->histo[o] <= 0) 
                                continue;
                            
                            // update histogram of path
                            new_histo = pnode_p->histo;
                            new_histo[o] += -1;

                            PNode *new_pnode = new PNode{new_path, new_histo, depth};
                            vertices[s]->intercect.push_back(new_pnode); // add new path to node
                            paths.push_back(new_path);
                            stop = true;

                        } else if (pnode_o->depth != 0 && pnode_p->depth == 0) {
                            // o is main path 
                            if (pnode_o->histo[p] <= 0) 
                                continue;
                                
                                // update histogram of path
                                new_histo = pnode_o->histo;
                                new_histo[p] += -1;

                                PNode *new_pnode = new PNode{new_path, new_histo, depth};
                                vertices[s]->intercect.push_back(new_pnode); // add new path to node
                                paths.push_back(new_path);
                                stop = true;


                        }

                        
                    }
                    
                }

            }

            for (const auto &c: paths) {
                std::cout << c << "\n";
            }

            // std::cout << paths.size() << "\n";
        }
        

        
        std::cout << "\n";

        

    }

}

void sort_split(Numbers collection, const Numbers &raw, Histogram &histo, Vertices &vertices , int depth, Numbers &other_io, Numbers &positive_io, int &pos_index) {
    
    Numbers eff_nums;

    Numbers indices(collection.size());
    std::map< std::array<int, 2>, int > histo_pad{}; 
    std::iota(indices.begin(), indices.end(), 0 );

    if (depth == 0) {
        

        std::sort(
            indices.begin(), 
            indices.end(), 
            [  &collection, &histo_pad, &histo] (int index_i, int index_j)  {

                int a = collection[index_i];
                int b = collection[index_j];
                
                if (histo_pad.count({index_i, a})== 0 ) {
                    histo_pad[{index_i, a} ] = 1;
                    
                    if (histo.count(a) == 0) {
                        histo[a] = 0;
                    }
                    
                    histo[a]++;
                    
                }

                if (histo_pad.count({index_j, b})== 0 ) {
                    histo_pad[{index_j, b} ] = 1;

                    if (histo.count(b) == 0) {
                        histo[b] = 0;
                    }

                    histo[b]++;

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
    std::map<int, void*> unique_sum_vertex_id;
    std::map < std::array<int, 2> , void*> unique_pair;
    std::map < std::array<int,2>, void*> unique_pair_sum;
    std::cout << "PROCESSING" << "\n";
    std::cout << "previous sum\t\t"  << other;
    std::cout << "input data \t\t"  << positive;
    std::cout << "PROCESSING END" << "\n";
    
    if (depth < N_SUM  ) {
        
        io.clear();

        for (std::size_t i = 0; i < positive.size(); i++) {
            for (std::size_t j = 0; j < other.size(); j++) {
                p = positive[i];
                o =  other[j];
                // std::array<int, 2> t1{p, o};
                // // std::array<int, 2> t2{o ,p};

                // if (unique_pair.count(t1) == 0) {
                //     unique_pair[t1] = nullptr;
                //     // unique_pair[t2] = nullptr;
                // }
                if (depth == 1 &&  p > 0 && o > 0)  
                    return;
                
                if (depth == 2 &&  p + o != 0) 
                    continue;   

                process_helper(o, p, vertices, depth, histo, io, unique_sum_vertex_id ,unique_pair_sum, ref_out);
            }
        }

    } 
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
    // std::cout << "START" << "\n";

    //     std::cout << other_list;
    //     std::cout << pos_list;
    // std::cout << "END END" << "\n";
    // std::cout << "-------------" << "\n";



        process(other_list, pos_list, vertices, loop, histo, eff_nums, data_return);

        if (loop < N_SUM - 1)
            sort_split(eff_nums, raw, histo, vertices, loop , other_list, pos_list, pos_index );

    }    
    return data_return;

}




