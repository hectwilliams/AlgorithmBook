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
using Vertices = std::map<char, Node*>;
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

struct BNode {
    char source;
    char dest;
    int size;
    int index;
    std::string s;
};

using DeltaList = std::vector<BNode*>;
std::ostream& operator<<(std::ostream& os, const Histogram & h) {

    os << "[ ";
    for ( const auto &[value, count ]: h ) {
        os << " " << value  <<  "[" << count << " ]"<< ","  ;
    }
     os << " ]\n";

    return os; 

}


void strip (std::string & s, const Histogram &histo) {

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

void set_t_histogram(const std::string &s , Histogram & histo, Vertices & vertices) {
    
    char c;
    std::string buffer;     

    // set histogram 
    for (unsigned int i = 0; i < s.length(); i++) {
        c = s[i];
        buffer += c;

        if (histo.count(c) == 0) {
            histo[c] = 0;
        }
        histo[c]++;


        if ( vertices.count(c) == 0) {
            vertices[c] = new Node{c, Table{}};
        }

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

bool compare_Histo(Histogram a, Histogram b ) {
    
    if ( a.size() != b.size() )
        return false;

    for(const auto [key_a, value_a]: a ) {

        if (a.count(key_a) != b.count(key_a) ) {
            return false;
        }
    }  

    return true; 
}

void bin_handler(Histogram &h, int value) {
    if (h.count(value)) {
        h[value]--;
        if (h[value] == 0) {
            h.erase(value);
        }
    }
}

class Solution {
public:
    std::string minWindow(std::string s, std::string t) {
        
        Histogram histo_main, t_histo, s_histo, s_raw_histo, tt_histo;
        Substrings substrings{}; 
        std::string min_result;
        std::string pad;
        std::string min_string;
        Vertices vertices, s_vertices;

        set_t_histogram(t, histo_main, vertices);
        set_s_histogram(s, histo_main, s_histo);

        strip(s, histo_main);
        
        if (s.length() == 0) 
            return "";
        
        if (t.length() == 0)
            return "";

        if ( s.length() == 1 ) {
            
            if ( t == s ) {
                return s;
            } else {
                return "";
            }
        }

        if (t.length() == 1) {

            if (s_histo.count( t[0] )) 
                return t;
            else 
                return "";
        }

        if (!compare_Histo(s_histo, histo_main) ) {
            return "";
        }

        std::cout << "S-DATA\n" << s_histo;
        std::cout << "T-DATA\n" << histo_main;

        tt_histo = histo_main;
        char prev_c1;
        int counter = 0;
        int indices[2] = {-1,-1};
        std::string acc_string;
        std::map<char, std::map < char, std::string > > distance_map;
        DeltaList list;
        // s = s + "\0" ;

        for (unsigned int i = 0; i < s.length(); i++) {
                
            char curr = s[i];
            
            if (s_histo.count(curr)) {
                
                indices[0] = indices[1];

                indices[1] = i;
                
                if (indices[0] >=0) {
                    
                    char c1 = s[indices[0]];
                    
                    char c2 = s[indices[1]];

                    int delta = indices[1] - indices[0];

                    std::string str_tmp ;
                    
                    str_tmp = s.substr( indices[0] , delta + 1 );
                    
                    std::cout << "STRING\t" << str_tmp <<  " " << tt_histo.size() << " " << " delta " << delta << "\n";

                    list.push_back(new BNode{c1, c2, delta + 1, indices[0], str_tmp });
                    
                    

                    prev_c1 = c1;
                }


            } 
        }


        std::cout << list.size() << "\n";

        std::sort(list.begin(), list.end(), [](BNode *a, BNode *b){

            return a->size < b->size;

        });

        for (const auto ptr: list) {

            std::cout << " SOURCE: "<< ptr->source << " DEST: " << ptr->dest << " " << " SIZE " << ptr->size << "  INDEX: " << ptr->index << "\n";
         }

         int cnt = 0;
         int growth = 0;
         std::string accum;
         t_histo = histo_main;
         
        if (list.size() == 1) {
            
            BNode *node = list[0];

            bin_handler(tt_histo, node->source);
            bin_handler(tt_histo, node->dest);

            if (tt_histo.empty()) {
                accum += node->s ;
                return accum;
            } else {
                return "";
                
            }
            
            
        } else {

            for (int i = 0; i < list.size(); i++) {
                BNode *node = list[i];
                
                if (i == 0) {
                    cnt +=1;
                    growth = node->index;
                    accum += node->s;

                    if (cnt == t.length() - 1 ) {
                        substrings[accum.length()] = accum;
                    } 

                } else {

                    if (node->index > growth) {
                        cnt++;
                        accum = accum.substr(0, accum.length() - 1) + node->s;
                        
                        if (cnt == t.length() - 1 ) {
                            substrings[accum.length()] = accum;
                        } 
                    }

                }
            }
        }

  


            // for (const auto [first_c, distance_map_2]: distance_map) {
            //     for (const auto [second_c, distance]: distance_map_2) {
            //         std::cout << first_c << " ->" << "\t" << second_c << ":\n " << distance << "\n\n\n";
            //     }   
                
            // }

            if (substrings.size()) {
                return substrings.begin()->second;
            } 

            return "";
      

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
                s = "bba"; 
                t = "ab";
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


