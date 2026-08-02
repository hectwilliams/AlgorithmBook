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
#include <cmath> // Required header
// #include <cstdint> // uint ...

const std::uint8_t DEBUG_ON = 0;

struct Node;
struct BNode;

using Histogram = std::map<char, int>;
using Substrings = std::map< unsigned , std::string>;
using Vertices = std::map<char, Node*>;
using RouteMap = std::map<unsigned int , std::pair< std::string, Node* > >;
using Table = std::map< char, RouteMap >;
using IndicesTable = std::map<int, int>;
using DeltaList = std::vector<BNode*>;

struct Node {
    char value;
    Table table;
};

struct BNode {
    char source;
    char dest;
    int size;
    int index;
    std::string s;
};

struct AccumNode {
    // std::string path;
    int recent_index;
    // int dest_index;
    std::string s;
    Histogram histo;
    bool open;
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
    // a is s (string sequence ) !

    if ( a.size() != b.size() )
        return false;

    for(const auto [key_a, value_a]: a ) {

        // s-dict and t-dict must have the same keys 
        if (a.count(key_a) != b.count(key_a) ) {
            return false;
        }

        // s - resource count must be >= t- resource count 
        if ( !(a[key_a] >= b[key_a] )) {
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

void bin_handler(Histogram &h, char value) {
    if (h.count(value)) {
        h[value]--;
        if (h[value] == 0) {
            h.erase(value);
        }
    }
}

bool valid_sub_window(Histogram h, BNode *node) {
    char source = node->source;
    char dest = node->dest;
    
    if (h.count(source))
        h[source]--;
    else 
        return false; 

    if (h.count(dest))
        h[dest]--;
    else 
        return false; 
    

    if (h[dest] < 0 || h[source] < 0 ) {
        return false;
    }

    return true;
}

bool last_resource_test(AccumNode *accnode, char c) {

    if (accnode->histo.size() == 1 && accnode->histo.count(c) && accnode->histo[c] == 1) {
        
        accnode->histo[c]--;
        
        if (accnode->histo[c] == 0)
        {
            if (DEBUG_ON) {
                
                std::cout << "EVAL THIS NODE: TBD" <<"\n";

            }

            accnode->histo.erase(c);
            return true;
        }

    }
    return false; 
}

void log_search(DeltaList units_list, Substrings &substrings , Histogram h_main) {

    // double threshold = std::pow(static_cast<double>(10), static_cast<double>(5) );
    
    std::vector<AccumNode*> anodeLists[2];
    std::vector<int> valid_indices[2];
    unsigned int select = 0;

    std::cout << "------\n";

    AccumNode closed_accum_node{-1, "DEADBEEF", {}, false};
    AccumNode *closed_accum_node_ptr = &closed_accum_node;

    unsigned pos = 0;

    for (unsigned i = 0; i < units_list.size(); i++) {
        anodeLists[select].push_back(nullptr);
        anodeLists[1 ^ select].push_back(nullptr);
    }

    // show units list 
    if (DEBUG_ON) {

        std::cout << pos  << " STAGE : \n";
        
        for (unsigned n = 0; n < units_list.size(); n++) {
            
            std::cout << units_list[n]->s << "\t\tINDEX: " <<  n <<  "\n";
            
        }
        
        std::cout << "------" << "\n";
    }

    // first stage 
    
    while (pos < units_list.size()) {
        
        ++pos;
        if (DEBUG_ON) {
            
            std::cout << pos  << " STAGE : \n";

        }
        // unit postion  == pos 

        for (unsigned unit_index = pos; unit_index < units_list.size(); unit_index++) {

            int acc_index = unit_index - 1;
            // std::cout << " ACC INDEX " << acc_index << " UNIT INDEX " << unit_index << " , ";
            
            AccumNode *acc_node, *new_acc_node;
            
            BNode *unit_node = units_list[unit_index];
            
            if (!anodeLists[select][acc_index]) {
                
                Histogram histo = h_main;

                BNode *unit_node_prev = units_list[unit_index - 1];

                acc_node =  new AccumNode{ unit_node_prev->index, unit_node_prev->s, histo, true };
                
                char unit_char  = unit_node->source;
                char acc_char  = unit_node_prev->source;

                bin_handler(histo, unit_char);
                bin_handler(histo, acc_char);
                
                acc_node->histo = histo;
                
            } else {
                acc_node = anodeLists[select][acc_index];
            }
            
           

            std::string acc = acc_node->s.substr(0, acc_node->s.length()-1) + unit_node->s;

            new_acc_node = new AccumNode{ unit_node->index, acc, acc_node->histo, true };

            // eval next stage nodes 
            if (DEBUG_ON) {
                std::cout <<   "READING UNIT NODE MEM POS_INDEX " << unit_index  << "\n";
                std::cout <<   "READING ACC NODE MEM POS_INDEX " << acc_index  << "\n";
                
                std::cout << acc_node-> s  <<  " ACC POS_INDEX " << acc_node->recent_index  << "\n";
                std::cout << unit_node-> s  <<  "  INDEX " << unit_node->index  <<  "\t" << unit_node -> source <<"\n";
                std::cout << new_acc_node-> s  <<  "  NEXT_INDEX " << new_acc_node->recent_index  << "\n";
                std::cout << new_acc_node-> histo;
            }

            if (last_resource_test(new_acc_node, unit_node->source)) {
                
                // std::cout << new_acc_node-> histo;
            }

            if ( ! acc_node->open ) {
                // is operand accum node available  
                delete new_acc_node; // delete previous set mem
                new_acc_node = closed_accum_node_ptr;  
            }

            if (new_acc_node->histo.size() == 0) {
                // resources exhausted

                // add acc_node's accumulator to substring 
                substrings[acc_node->s.length()] = acc_node->s;


                // set next layer accum node as "OFF" 
                new_acc_node = closed_accum_node_ptr;  

            }

            // set next layer accum node 
            anodeLists[1 ^ select][unit_index] = new_acc_node;
            
            if (DEBUG_ON) {

                std::cout << "ACC LAYER: " << pos << "\t" << "WRITE  ACC NODE TO MEM AREA. (NON CONFLICT REGION) POSITION: " << unit_index  << "\n";

                std ::cout << "**" << "\n";

            }
        }
        
        if (DEBUG_ON) {
            
            std::cout << "--------\n";

        }

        select = 1 ^ select;

        if (pos == 2)
            break;

    }


    for (const auto &[length, value]: substrings) {
        
        std::cout << length << "\t" << value <<"\n";

    }

}


void sort_units_list (DeltaList &list) {

    std::sort(list.begin(), list.end(), [](BNode *a, BNode *b){

        return a->size < b->size && a->index < b->index;

    });

    for (const auto ptr: list) {

        if (DEBUG_ON) {
            
            std::cout << " SOURCE: "<< ptr->source << " DEST: " << ptr->dest << " " << " SIZE " << ptr->size << "  INDEX: " << ptr->index << "\n";

        }
    
    }

}

class Solution {
public:
    std::string minWindow(std::string s, std::string t) {
        
        Histogram histo_main, s_histo, s_raw_histo, tt_histo;
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

        tt_histo = histo_main;
        int indices[2] = {-1,-1};
        DeltaList list;
        // IndicesTable index_table;
        BNode *last_index = new BNode{'\0','\0',1, -1, ""};
        std::string dummy{};

        for (unsigned int i = 0; i < s.length(); i++) {
                
            char curr = s[i];
            
            if (s_histo.count(curr)) {
                
                indices[0] = indices[1];

                indices[1] = i;
                
                if (indices[0] >=0) {
                    
                    char c1 = s[indices[0]];
                    
                    char c2 = s[indices[1]];

                    // index_table[ indices[1] ] = indices[ 0 ] ;

                    // index_table[ indices[0] ] = indices[ 1 ] ;

                    int delta = indices[1] - indices[0];

                    std::string str_tmp ;
                    
                    str_tmp = s.substr( indices[0] , delta + 1 );
                    
                    if (DEBUG_ON) {

                        std::cout  << " INDEX " << i  << "STRING\t" << str_tmp <<  " " << tt_histo.size() << " " << " delta " << delta << "\n";
                    }


                    list.push_back(new BNode{c1, c2, delta + 1, indices[0], str_tmp });
                    
                    last_index->source = list[list.size()-1]->dest;
                    last_index->index =  list[list.size()-1]->index +  delta;
                    last_index->s = dummy + list[list.size()-1]->dest ;
                }               

            } 
        }

        list.push_back(last_index);
        sort_units_list(list);
         
        
         if (list.size() == 1) {
            
            std::string accum;
            Histogram t_histo = histo_main;
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

            tt_histo = histo_main;
            log_search(list, substrings, histo_main);
       
        }

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
                s = "bbaa"; 
                t = "aba";
                break;
            case (6):
                s = "cabwefgewcwaefgcf"; 
                t = "cae";
                break;
            case (7):
                s = "aa"; 
                t = "aaa";
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


