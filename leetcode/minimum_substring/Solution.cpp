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
        
        Histogram histo_main, t_histo, s_histo, s_raw_histo;
        Substrings substrings{}; 
        unsigned min_size = 1000000000;
        std::string min_result;
        std::string pad;
        char c , c_prev;
        bool width_full = false;

        std::map<char, Node*> vertices;

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

        for (unsigned int i = 0; i < s.length(); i++) {
        
            c = s[i];

            // root = new Node{c, {}};
            if (root == nullptr) {
                vertices[c] = new Node{c, Table{}};
        
            } else if (s_raw_histo.count(c) == 0) {
                // high piroroty resource 
                vertices[c] = new Node{c, Table{}};
            }

            if (t_histo.count(c)) {
                buffer += c;

                if (buffer.length() > 1) {
                    // closeing 

                    // std::cout << " IN " << buffer << "\n";
                    
                    char c_next = buffer[ buffer.length()-1 ];
                    
                    unsigned int path_len = buffer.length()-2;

                    Node *next_node = vertices[c_next];

                    Node *current = vertices[c];

                    std::string next_buffer = buffer.substr(1, buffer.length()-2);
                    
                    // std::cout << " OUT " << next_buffer << "\n";

                    current->table[c_next][path_len]= {next_buffer, next_node}; 

                    // reset 
                    buffer = "";

                    buffer += c;

                }

            } else {

                buffer +=c;

            }
            
            prev = vertices[c];


        }

        std::string acc;

        for (int i = 1; i < t.length(); i++) {
            
            char c_head  = t[i-1];
            
            char c_curr  = t[i];

            acc += c_head;
            
            Node *node = vertices[c_head];
            
            std::cout << node->value << "\n";
            
            RouteMap route_table = node->table[c_curr];
            
            std::cout << route_table.size() << "\n";

            unsigned low_length = route_table.begin()->first;

            std::pair< std::string, Node* > low_pair = route_table.begin()->second;

            // std::cout << low_length << "\n";

            // std::cout << low_pair.first << "\n";

            std::cout << low_pair.second << "\n";
            std::cout << "----- "<< "\n";

// 
            // Node *next = node->table[c_curr];
            break;
        }            

        for (const auto &[key, value]: substrings) {
            std::cout << key << "\n";
        }

        // std::cout << substrings.size() << " SIZEZIE \n";
        // std::cout << substrings.begin()->first << " SIZEZIE \n";
        // std::cout << substrings[4]<< " SIZEZIE \n";
        // std::cout << min_result << " SIZEZIE \n";

        if (substrings.size()) {

            return substrings.begin()->second;
        } else {
            return "";
        }

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


