#include <vector>
#include <iostream>
#include <deque>
#include <array>
#include <map>
#include <algorithm>
#include <numeric> 
#include <random>
#include <cassert> 
#include <stdexcept> // Required for standard exceptions
#include <string>
#include <utility> 

struct Node;
using Histogram = std::map<char, int>;
using Substrings = std::map< unsigned , std::string>;
// using TableValueList = std::vector< std::pair<std::string, Node* > >;

using RouteMap = std::map<unsigned int , std::pair< std::string, Node* > >;

using Table = std::map< char, RouteMap >;

// std::pair<int, std::string> p1 = {1, "Apple"};

struct Node {
    char value;
    Table table;

};

struct Tree {
    struct Node *root;
};

std::ostream& operator<<(std::ostream& os, const Histogram & h) {

    os << "[ ";
    for ( const auto &[value, count ]: h ) {
        os << " " << value  <<  "[" << count << " ]"<< ","  ;
    }
     os << " ]\n";

    return os; 

}


void strip (std::string & s, const Histogram &histo) {
    int left = 0;
    int right = s.length() - 1;


    while ( histo.count( s[0] ) == 0  && !s.empty()) {
        s.erase( 0, 1);

        if (s.length() == 0)
            return;
        
    }

    if (s.length() == 0)
        return;

    while ( histo.count( s[s.length()-1] ) == 0 ) {
        s.erase( s.length() - 1 , 1);
    }

}

void set_t_histogram(const std::string &s , Histogram & histo) {
    

            // set histogram 
        for (const auto &c: s) {
            if (histo.count(c) == 0) {
                histo[c] = 0;
            }
            histo[c]++;
        }
}

void set_s_histogram(const std::string &s , const Histogram & master_histo , Histogram & histo) {
        // set histogram 
        for (const auto &c: s) {
            if (master_histo.count(c)) {

                if (histo.count(c) == 0) {
                    histo[c] = 0;
                }
                histo[c]++;
            }
        }
}

class Solution {
public:
    std::string minWindow(std::string s, std::string t) {
        
        Histogram histo_main, t_histo, s_histo, s_raw_histo, tt_histo;
        Substrings substrings{}; 
        unsigned min_size = 1000000000;
        std::string min_result;
        std::string pad;
        char c , c_prev;
        bool width_full = false;
        std::string min_string;
        std::map<char, Node*> vertices, s_vertices;

        set_t_histogram(t, histo_main);
        set_s_histogram(s, histo_main, s_histo);

        strip(s, histo_main);
        
        if (s.length() == 0) 
            return "";

        t_histo = histo_main;
        s_raw_histo = s_histo;

        Tree tree{nullptr};

        Node *root{nullptr}, *node{nullptr}, *prev{nullptr}; 
        std::string buffer;     

            
        for (unsigned int i = 0; i < t.length(); i++) {
        
            c = t[i];

            // root = new Node{c, {}};
            if (root == nullptr) {
                vertices[c] = new Node{c, Table{}};
        
            } else if (s_raw_histo.count(c) == 0) {
                // high piroroty resource 
                vertices[c] = new Node{c, Table{}};
            }

            // if (s_histo.count(c) ) {

                buffer += c;

                if (buffer.length() > 1) {

                    
                    // closeing 

                    std::cout << " IN " << buffer << "\n";
                    
                    char c_next = buffer[ buffer.length()-1 ];
                    char c_prev = buffer[ 0 ];
                    
                    unsigned int path_len = 0; //buffer.length()-2;
                    
                    Node *current = vertices[c_prev];
                    
                    Node *next_node = vertices[c_next];
                    
                    std::string next_buffer = "";//buffer.substr(1, buffer.length()-2);
                    
                    // forward connection
                    current->table[c_next][path_len]= {next_buffer, next_node}; 

                    // reverse connection
                    next_node->table[c_prev][path_len]= {next_buffer, current}; 

                    // reset 
                    buffer = "";

                    buffer += c;

                }

            
            prev = vertices[c];

        }

        std::cout << "-----" << "\n";
        std::string buffer_s;
        std::string acc;
        int acc_size = -1;

        tt_histo = histo_main;

        std::cout << s_histo;
        Node *curr_node;
        Node *prev_node{nullptr};
        Node *next_node;
        Node *start{nullptr};
        Node *end{nullptr};
        Node *t_node{nullptr};


        int count = 0;
        std::cout << tt_histo;
        int counter = 0;
        int indices[2] = {-1,-1};
        for (unsigned int i = 0; i < s.length(); i++) {
            

        char curr = s[i];
        char next = s[i+1];
        
        std::map<char, std::map<char, int>> distance_map;
        
        if (s_histo.count(curr)) {
            
            curr_node = vertices[curr];

            indices[0] = indices[1];

            indices[1] = i;
            
            std::cout << indices[0] << " , " << indices[1] << "\n";

            if (indices[0] >=0) {
                
                char c1 = s[indices[0]];
                
                char c2 = s[indices[1]];

                int delta = indices[1] - indices[0];
                
                if (distance_map[c1].count(c2) == 0 ) {
                    distance_map[c1][c2] = delta ;
                    distance_map[c2][c1] = delta ;
                } else if (distance_map[c1][c2] <= delta) {
                    distance_map[c1][c2] = delta ;
                    distance_map[c2][c1] = delta ;
                }

                for (const auto [first_c, distance_map_2]: distance_map) {
                    for (const auto [second_c, distance]: distance_map) {
                        std::cout << first_c << "\t" << "\t" << second_c << "\t"<< distance << "\n";
                    }   
                    
                }
                
                
                // distance_map[c1][c2] = indices[1] - indices[0] ;

                
                // int tmp_indices[2] = indices;
                
                // std::array<int ,2 > data {c1, c2   };
                
                // std::sort(tmp_indices.begin(), tmp_indices.end(), [](int i, int j){return s[i] < s[j]} );

            }


            // if (start == nullptr) {

            //     start = curr_node;

            //     if (tt_histo.count(curr))
            //         tt_histo[curr]--;
                
            //     if (tt_histo[curr] == 0)
            //         tt_histo.erase(curr);

            //     continue;
            // }

            // if (start ) {
                
            //     // curr_node = vertices[curr];
            // } 



            // if (prev_node) {

            //     if ( test_node->table.count(next)  && test_node) {
            //         // std::cout << "GOOD\n";
            //         // std::cout << "GOOD\n";

            //     }
            // }

            // std::cout << curr << "\n";

                    
                    // if (curr_node)
                    //     std::cout << " CURR " << curr_node->value << "\n";
                
                    // if (prev_node)
                    //     std::cout << " PREV " << prev_node->value  << "\n";
                    

                    // if (tt_histo.count(curr))
                    //     tt_histo[curr]--;

                    // // if (tt_histo.count(next))
                    // //     tt_histo[next]--;

                    // if (tt_histo[curr] == 0)
                    //     tt_histo.erase(curr);

                    // // if (tt_histo[next] == 0)
                    // //     tt_histo.erase(next);

                    // std::cout << " ANALYSIS CURR " << curr_node->value << " -- " << curr_node << "\n";
                        
                    // if (prev_node)
                    //     std::cout << " ANALYSIS PREV " << prev_node->value << " -- " << prev_node << "\n";
                    
                    // if (tt_histo.empty()) {

                    //     std::cout << " RESETR CURR " << prev << " -- " << next << "\n";

                    //     tt_histo = histo_main;
                    //     acc = curr;
                    // } else {
                    //     acc += curr;

                    // }


                    // std::cout << "-------" <<  acc <<  "\n";
            
                    prev_node = curr_node;
                } else {
                        acc += curr;

            }
        }
        

        // for (unsigned int i = 0; i < s.length(); i++) {
        //     c = s[i];
            
         
        //     // // root = new Node{c, {}};
        //     // if (root == nullptr) {
        //     //     s_vertices[c] = new Node{c, Table{}};
        
        //     // } else if (s_raw_histo.count(c) == 0) {
        //     //     // high piroroty resource 
        //     //     s_vertices[c] = new Node{c, Table{}};
        //     // }

        //     bool safe = false;
        //     if (s_histo.count(c) ) {

        //         buffer_s += c;
                

        //         if (buffer_s.length() > 1) {
                    
        //             // std::cout << " IN " << buffer_s << "\n";
        //             // char curr = buffer_s[0];
        //             // char next = buffer_s[buffer_s.length()-1];

        //             // Node *next_node = vertices[ curr ];
        //             // Node *current = vertices[next];


        //             // if (tt_histo.count(curr))
        //             //     tt_histo[curr]--;

        //             // if (tt_histo.count(next))
        //             //     tt_histo[next]--;
                    
        //             // if (tt_histo[curr] == 0) 
        //             //     tt_histo.erase(curr);

        //             // if (tt_histo[next] == 0) 
        //             //     tt_histo.erase(next);
                



        //             // std::cout << " current " << current << "\n";
        //             // std::cout << " next_node " << next_node << "\n";
        //             // std::cout << " current " << current->value << "\n";
        //             // std::cout << " next_node " << next_node->value << "\n";
                    
        //             // if(current->table.count(next_node->value)) {

        //             //     std::string sub = buffer_s.substr(1, buffer_s.length()-2);
                        
        //             //     acc +=  curr +  sub;
                        
        //             //     acc_size += sub.length(); 
                        
        //             //     std::cout << " ACC " << acc << "\n";
        //             //     std::cout << " BEFORE HISTOGRAM " << t_histo << "\n";
                        
        //             //     if (t_histo.count(curr))
        //             //         t_histo[curr]--;
                        
        //             //         if (t_histo.count(next))
        //             //         t_histo[next]--;

        //             //     if (t_histo[curr] == 0) {
        //             //         t_histo.erase(curr);
        //             //     }
                        
        //             //     if (t_histo[next] == 0) {
        //             //         t_histo.erase(next);
        //             //     }
        //             //         std::cout << " NEXT HISTOGRAM " << t_histo << "\n";

        //             //     if (t_histo.empty()) {
        //             //         safe

        //             //         t_histo = histo_main;
        //             //         if (min_size == -1 || acc.length() < min_size) {
        //             //             min_size = acc.length();
        //             //             min_string = acc;
        //             //         }

        //             //         acc = "";

        //             //     }

        //             // }
                    
        //     //         // closeing 

                    
        //     //         char c_next = buffer[ buffer.length()-1 ];
        //     //         char c_prev = buffer[ 0 ];
                    
        //     //         unsigned int path_len = buffer.length()-2;
                    
                    
                    
        //     //         std::string next_buffer = buffer.substr(1, buffer.length()-2);
                    
        //     //         // forward connection
        //     //         current->table[c_next][path_len]= {next_buffer, next_node}; 

        //     //         // reverse connection
        //     //         next_node->table[c_prev][path_len]= {next_buffer, current}; 

        //             // reset 
        //             if (tt_histo.empty()){
                        
        //                 buffer_s = "";
        //                 tt_histo = histo_main;
        //             }

        //             buffer_s += c;

        //         }

        //     } else {

        //         buffer_s +=c;

        //     }
            
        //     prev = s_vertices[c];

        // }

        return min_string;
        // conneection tail to head 
//         char head_char = buffer[ buffer.length()-1 ];
//         char tail_char = buffer[  0 ];
        
//         // forward connection
//         vertices[head_char]->table[tail_char][0]= {"",  vertices[tail_char ]   }; 

//         // reverse connection
//         vertices[tail_char]->table[head_char][0]= {"",  vertices[head_char]   }; 

//         std::cout << " ******* "  << "\n";

//         std::string acc;

//         for (int i = 1; i < t.length(); i++) {
            
//             char c_curr  = t[i-1];
            
//             char c_next  = t[i];
            
//             std::cout << " MOVE " << c_curr  << " " << c_next << " " << "\n";

//             acc += c_curr;
            
//             Node *node = vertices[c_curr];
            
//             std::cout << node->value << "\n";
            
//             RouteMap route_table = node->table[c_next];
            
//             std::cout << route_table.size() << "\n";

//             unsigned low_length = route_table.begin()->first;

//             std::pair< std::string, Node* > low_pair = route_table.begin()->second;

//             std::cout << low_pair.first << "\n";

//             std::cout << low_pair.second->value << "\n";
//             std::cout << "----- "<< "\n";

// // 
//             // Node *next = node->table[c_curr];
//             break;
//         }            

//         for (const auto &[key, value]: substrings) {
//             std::cout << key << "\n";
//         }

//         // std::cout << substrings.size() << " SIZEZIE \n";
//         // std::cout << substrings.begin()->first << " SIZEZIE \n";
//         // std::cout << substrings[4]<< " SIZEZIE \n";
//         // std::cout << min_result << " SIZEZIE \n";

//         if (substrings.size()) {

//             return substrings.begin()->second;
//         } else {
//             return "";
//         }

    }
};


int main(int param_count, char *args[]) {
    Solution sol;
    std::string s;
    std::string t;

    try {

        if (param_count  < 2)
            return 1;
        
        int test = std::stoi(args[1]);

        switch(test) {

            case (0):
                s = "ADOBECODEBANC";
                t = "ABC";
                break;
            case (1):
                s = "a";
                t = "a";
                break;
            case (2):
                s = "a";
                t = "aa";
                break;
            case (3):
                s = "aa"; 
                t = "aa";
                break;
            case (4):
                s = "bba"; 
                t = "ab";
                break;
            case (5):
                s = "aab"; 
                t = "aab";
                break;
            default:
                break;
        }
    } catch (const std::runtime_error & e) {

        std::cout << " RUNTIME ERROR "<< e.what() << "\n" ;

    }
    
    auto start = std::chrono::steady_clock::now();
    std::string result = sol.minWindow(s, t);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << "\n";
    std::cout << " result \t: " << result << "\n";
}


