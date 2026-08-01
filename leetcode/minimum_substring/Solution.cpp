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
using IndicesTable = std::map<int, int>;

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

struct SNode {
    std::string s;
    int curr_index;
    int next_index;
    Histogram histo;
    int depth;
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

Histogram cpy_node( Histogram data) {
    
    Histogram res;

    for (const auto &[key, value]: data) {
        res[key] = value;
    }

    return res;
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
        int indices[2] = {-1,-1};
        std::string acc_string;
        std::map<char, std::map < char, std::string > > distance_map;
        DeltaList list;
        IndicesTable index_table;
        // s = s + "\0" ;

        for (unsigned int i = 0; i < s.length(); i++) {
                
            char curr = s[i];
            
            if (s_histo.count(curr)) {
                
                indices[0] = indices[1];

                indices[1] = i;
                
                if (indices[0] >=0) {
                    
                    char c1 = s[indices[0]];
                    
                    char c2 = s[indices[1]];

                    index_table[ indices[1] ] = indices[ 0 ] ;

                    index_table[ indices[0] ] = indices[ 1 ] ;


                    int delta = indices[1] - indices[0];

                    std::string str_tmp ;
                    
                    str_tmp = s.substr( indices[0] , delta + 1 );
                    
                    std::cout  << " INDEX " << i  << "STRING\t" << str_tmp <<  " " << tt_histo.size() << " " << " delta " << delta << "\n";

                    list.push_back(new BNode{c1, c2, delta + 1, indices[0], str_tmp });
                    
                    
                }


            } 
        }


        std::cout << list.size() << "\n";

        std::sort(list.begin(), list.end(), [](BNode *a, BNode *b){

            return a->size < b->size && a->index < b->index;

        });

        for (const auto ptr: list) {

            std::cout << " SOURCE: "<< ptr->source << " DEST: " << ptr->dest << " " << " SIZE " << ptr->size << "  INDEX: " << ptr->index << "\n";
         }

         std::string accum;
         t_histo = histo_main;
         
         std::map<int, SNode* > sratch_pad{};

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


            tt_histo = histo_main;

            for (std::size_t i = 0; i < list.size(); i++) { 
                // new adress 
                
                BNode *node = list[i];
                
                    char c = node->s[0];
                    
                    std::cout << " INDEX : " << i << "\n";
                    std::cout << "CHARACTER \t " << c << " " << '\n';

                    int next_index = index_table[node->index];
                    
                    if (sratch_pad.count(node->index) == 0) {
                        
                        // Histogram h = histo_main;
                        sratch_pad[node->index] = new SNode{node->s, node->index, next_index, histo_main, 1};
                        std::cout << "NEW ENTRY" << "\n";
                        std::cout << " HISTO START  \t"<<  sratch_pad[node->index]->histo;
                        std::cout << " THIS  \t"<<  sratch_pad[node->index]->curr_index<< '\n';
                        std::cout << " NEXT  \t"<<  sratch_pad[node->index]->next_index<< '\n';
                        std::cout << " DEPTH  \t"<<  sratch_pad[node->index]->depth << '\n';
                        std::cout << " DATA  \t"<<  sratch_pad[node->index]->s  << '\n';
                        
                        bin_handler(sratch_pad[node->index]->histo, c);
                        std::cout << " HISTO END  \t"<<  sratch_pad[node->index]->histo;
                        
                        // set up next slot
                        if (sratch_pad.count(next_index) == 0) {
                            
                            sratch_pad[next_index] = new SNode{node->s, next_index, -1,   sratch_pad[node->index]->histo , sratch_pad[node->index]->depth + 1}; // placeholder 
                        }
                        
                        std::cout << "----\n";
                    }  else {
                        // has forward address

                            SNode *snode = sratch_pad[node->index];

                            if (snode->histo.count(c)) {
                                std::cout << " RESOURCES AVAILABLE" << "\n";
                                bin_handler(snode->histo, c);
                                std::string s = snode->s.substr(0, snode->s.length() - 1) + node->s ;
                                snode->s = s;
                                // snode->depth += 1;
                                
                                if (sratch_pad.count(next_index) == 0) {

                                    sratch_pad[next_index] = new SNode{snode->s , next_index, -1,    snode->histo ,  snode->depth + 1}; // placeholder 
                                }
                                std::cout << " RESET DATA  \t"<<  sratch_pad[node->index]->s << "\n";
                                std::cout << " RESET  DEPTH \t"<<  sratch_pad[node->index]->depth<< "\n";
                                std::cout << " RESET  HISTO \t"<<  sratch_pad[node->index]->histo<< "\n";
                                
                                std::cout << "----\n";

                             
                            } else {

                                std::cout << "RESOURCES UNAVAILABLE" << "\n";
                                
                                // reset 
                                
                                std::cout << "CHARACTER \t " << c << " " << '\n';
                                std::cout << "ENTER  HISTO \t"<<  sratch_pad[node->index]->histo<< "\n";
                                // std::cout << " RESET  HISTO \t"<<  sratch_pad[node->index]->histo<< "\n";
                                std::cout << "RESET DATA BEFORE  \t"  << snode->s << "\n";
                                std::cout << "RESET  DEPTH \t"  <<  sratch_pad[node->index]->depth  << "\n\n";
                                
                                snode->histo = histo_main;
                                bin_handler(snode->histo, c);
                                snode->depth--;
                                snode->s = node->s;

                                std::cout << " RESET DATA AFTER  \t"<<  sratch_pad[node->index]->s << "\n";

                                std::cout << " RESET  HISTO AFTER\t" <<  sratch_pad[node->index]->histo << "\n";
                                
                                // std::cout << " RESET DATA  \t"<<  sratch_pad[node->index]->s << "\n";
                                std::cout << " RESET  DEPTH AFTER \t"<<  sratch_pad[node->index]->depth<< "\n";

                                if (sratch_pad.count(next_index) == 0) {

                                    sratch_pad[next_index] = new SNode{snode->s , next_index, -1,    snode->histo ,  snode->depth + 1}; // placeholder 
                                }
                                
                                std::cout << "----\n";

                            }



                            // std::cout << "NUMBER \t " << node->index << " " << '\n';

                            // // sratch_pad[node->index]

                            // std::cout << " RESET HISTO  \t"<<  sratch_pad[node->index]->histo;
                        
                    }

                    if ( list [ list.size() - 1 ] == node ) {
                        
                        SNode *snode = sratch_pad[node->index];

                        std::cout << "\t\t\t\t\tLAST WINDOW\n\n";
                        
                        bin_handler(snode->histo, node->source);
                        bin_handler(snode->histo, node->dest);
                        
                        std::cout << " LAST WINDOW HISTO AFTER\t" <<  sratch_pad[node->index]->histo << "\n";

                        
                    }

                    if ( static_cast<unsigned>(sratch_pad[node->index]->depth) == t.length() - 1) {
                        
                        std::cout << " STRING OUT: \t\t "<<  sratch_pad[node->index]->s << "\n";

                        substrings[sratch_pad[node->index]->s.length()] = sratch_pad[node->index]->s;
                    }

                    // std::cout << " CURR \t"<< node->index << "\n";
                    // std::cout << " NEXT \t"<< next_index << "\n";
                    // std::cout << " CURR  \t"<< sratch_pad[node->index]->s  << "\n";
                    // std::cout << " DEPTH  \t"<<  sratch_pad[node->index]->depth << "\n";
                    // std::cout << " HISTO  \t"<<  sratch_pad[node->index]->histo;
                    // std::cout << " STRING  \t"<<  sratch_pad[node->index]->s << "\n";
                    // std::cout << "----\n";

            }
        
        }

            
            
        if (substrings.size()) {
            return substrings.begin()->second;
        } 

        return "";
            
    }

};
        // sratch_pad[node->index].second + 1
                        // sratch_pad[node->index]->histo[c]--;
                        // if (sratch_pad[node->index]->histo[c] == 0) {
                        //     sratch_pad[node->index]->histo.erase(c);
                        // }

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


