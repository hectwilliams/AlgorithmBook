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
#include <string>

struct Node; 

using Q = std::deque<Node *>;
using UsedList = std::map<std::string, bool>;
using STable = std::map<std::size_t, std::string> ;
using Words = std::vector< std::string>;

struct Node {
    Words data;
    std::string acc; 
    int index;
};


std::ostream& operator<<(std::ostream& os, const Words & data) {

     os << "[ ";
    for ( const auto &value: data ) {
        os << " " << value << ", "  ;
    }
     os << " ]\n";

    return os; 

}


std::ostream& operator<<(std::ostream& os, Node* node) {


     os << "[\n";
    
    //  os  << "\ts1: "<< node->s1 << " s2: " << node->s2  << "\n";

     for (const auto &value: node->data) {
        os <<  value <<  ",";
     }
     os << "\n]\n";

    return os; 

}


void add_to_queue() {

}

bool histo_valid (std::string s1, std::string s2) {
    
    std::map<char, std::size_t> zero_map;

    for(std::size_t i = 0; i < s1.length(); i++) {
        
        if (zero_map.count(s1[i]) == 0)
            zero_map[s1[i]] = 0;

        if (zero_map.count(s2[i]) == 0)
            zero_map[s2[i]] = 0;

        zero_map[s1[i]]++;
        zero_map[s2[i]]--;

    }

    int sum = 0;

    for (const auto &[key, value]: zero_map) {
        sum += value;
    }

    return (sum == 0);
}


void init_split(std::string s1, Q &q) {
    // add s1 string to node 

    Node *node = new Node{ {}, "", 0};

    node->data.push_back(s1);

    q.push_back(node);

}


bool search_2_test(Node *node, std::string s) {
    
    
    for (std::size_t i = 0; i < s.length(); i++) {
        
        if ( s[i] != node->acc[i] ) {
            return false; 
        }

    }
    
    return true;

}

void search_2(std::string s, Node *node, Q & q ) {

    char target_c = s[node->index];

    std::string analysis_s = node->data[0];
    std::cout  << analysis_s << "\n";

    std::cout << " ANALYSIS\t" << analysis_s;
    std::cout << " ANALYSIS DONE" <<  "\n";
    std::cout << " AC "  << node->acc  << "\n";
    std::cout << " TARGET "  << target_c  << "\n";

    for (int i = 0; i < analysis_s.length(); i++) {
        

        if ( target_c == analysis_s[i] ) {

            if (i == 0) {

                // split 
                std::string left = analysis_s.substr(0, 1);
                std::string right = analysis_s.substr(1);

                Node *new_node = new Node{ {}, node->acc , node->index }; // copy 
                
                // remove prev head 
                Words next_vector = Words( node->data.begin() + 1 , node->data.end() );
                
                // new head 
                Words left_vector;
                
                if (right.length()) {
                    left_vector.push_back(right);
                }

                // concat
                left_vector.insert(left_vector.end(), next_vector.begin(), next_vector.end());
                
                // write to new node 
                new_node->data = left_vector;

                // append char to accumulator
                new_node->acc += left;

                // incr
                new_node->index = node->index + 1;

                std::cout << new_node->acc;
                std::cout << new_node->data;
                std::cout << "------0" << "\n";

                q.push_back(new_node);

            } else if (i == analysis_s.length()-1) {

                // split 
                std::string left = analysis_s.substr(0, analysis_s.length() - 1 );
                std::string right = analysis_s.substr( analysis_s.length() - 1 );

                // remove prev head 
                Words next_vector = Words( node->data.begin() + 1 , node->data.end() ); 

                Node *new_node = new Node{ {}, node->acc , node->index }; // copy 
                
                // new head 

                Words left_vector;

                if (left.length()) {
                    left_vector.push_back(left);
                }

                // concat 
                left_vector.insert(left_vector.end(), next_vector.begin() , next_vector.end());

                // set data 
                new_node->data = left_vector;

                // set accum
                new_node->acc += right;

                new_node->index = node->index + 1;

                std::cout << new_node->acc;
                std::cout << new_node->data;
                std::cout << "------1" << "\n";

                q.push_back(new_node);

            } else {
                
                // split 
                std::string left = analysis_s.substr(0, i + 1 );
                std::string right = analysis_s.substr(i + 1 );
                std::string uni = left.substr(left.length() - 1);
                left = left.substr( 0, left.length() - 1);
                
                Node *new_node = new Node{ {}, node->acc , node->index }; // copy 

                Words next_vector = Words( node->data.begin() + 1 , node->data.end() ); 

                // new head 
                Words left_vector = {left};
                Words right_vector = {right};
                Words collection = {};

                // concat with left
                // collection.insert(collection.end(), left_vector.begin(), left_vector.end());

                // concat with right
                left_vector.insert(left_vector.end(), right_vector.begin(), right_vector.end());

                left_vector.insert(left_vector.end(), next_vector.begin(), next_vector.end());


                // set data 
                new_node->data = left_vector;

                // set accum 
                new_node->acc += uni;

                new_node->index =  node->index + 1;
                
                std::cout << new_node->acc;
                std::cout << new_node->data;
                std::cout << "------" << "\n";
                q.push_back(new_node);
                
            }
        }

    }

}

class Solution {
public:
    bool isScramble(std::string s1, std::string s2) {
        UsedList usedList; 
        Q q;

        if (s2.length() == 0) {
            
            if (s1 == s2)
                return true;
            else 
                return false; 

        }

        if ( s2.length() == 1 ) {

            if (s2 == s1) 
                return true;
            else 
                return false; 

        }

        if (s2.length() != s1.length()) {
            return false;
        }

        if (!histo_valid(s1, s2)) {
            std::cout << "HISTO" << "\n";
            return false; 
        }

        // q.push_back(new Node{  STable{{0, s1 }},  0});
        
        // init
        init_split(s1, q);

        bool found_u = false;

        while (!q.empty())  {
             
            Node *node = q.front();

            q.pop_front(); 

            if (node->acc.length() == s2.length()) {
                
                found_u |= true;

            } else {
                search_2(s2, node, q);
            }
            
            // if (node->index == s1.length()) {

            //     if (search_2_test(node, s2)) {
            //         std::cout << "match found" << "\n";
            //         // std::cout << node;
            //         found_u |= true;

            //     }
                
            // } else {

            //     // search(s2, node, q);

            // }

        }

        return found_u;

        return false;
    }
};

int main(int param_count, char *args[]) {
    Solution sol;
    std::string s1,s2;
    bool result;

    try {

        if (param_count  < 2)
            return 1;
        
        int test = std::stoi(args[1]);

        switch(test) {

            case (0):
                s1 = "great";
                s2 = "rgeat";
                break;
            
            case (1):
                s1 = "abcde";
                s2 = "caebd";
                break;

            case (2):
                s1 = "a";
                s2 = "a";
                break;

            case(3):
                s1 = "abcdbdacbdac";
                s2 = "bdacabcdbdac";
                break;

            case(4):
                s1 = "abcde";
                s2 = "caebd";

            default: 
                break;
        
        }

        result = sol.isScramble(s1, s2);



     } catch (const std::runtime_error & e) {

        std::cout << " RUNTIME ERROR "<< e.what() << "\n" ;

    }


    std::cout << " is sramble " << result << "\n";
}