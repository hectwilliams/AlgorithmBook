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

struct Node2; 

using Q2 = std::deque<Node2 *>;

using UsedList = std::map<std::string, bool>;
using STable = std::map<std::size_t, std::string> ;
using Words = std::vector< std::string>;

struct Node2 {
    Words data;
    Words result;
    // std::string acc; 
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


std::ostream& operator<<(std::ostream& os, Node2* node) {
     os << "[\n";
    //  os  << "\ts1: "<< node->s1 << " s2: " << node->s2  << "\n";
     for (const auto &value: node->data) {
        os <<  value <<  ",";
     }
     os << "\n]\n";

    return os; 
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

void init_split2(std::string s1, Q2 &q) {
    // add s1 string to node 

    Node2 *node = new Node2{ {}, {},  0};

    node->data.push_back(s1);

    q.push_back(node);

}


bool search_2_test2(Node2 *node, std::string s) {
    
    if (node->result.size() != s.length()) {
        
        return false ;

    }

    for (std::size_t i = 0; i < s.length(); i++) {
        
        if ( node->result[i].length()  !=  1 ) {
            return false;
        }
        
        if ( std::string(1, s[i] ) != node->result[i] ) {
            return false; 
        }

    }
    
    return true;

}


void search_3(std::string s, Node2 *node, Q2 & q ) {

    char target_c = s[node->index];
    
    std::cout << " INDEX TARGET: " << node->index << "\n";
    std::cout << " NEXT LENGTH TARGET: " << node->index + 1 + 1 << "\n";

    std::cout << " DATA TARGET: " << node->data << "\n";

    // if (node->index == 11) {

    //     std::cout << node->data;

    //     std::cout << node->result;

    // //     std::cout << node->result;

    // //     std::cout << " x-------x: " << "\n";

    //     assert(0);
    // }

    std::string analysis_s = node->data[0];



    for (int i = 0; i < analysis_s.length(); i++) {

        if ( target_c == analysis_s[i] ) {
            
            if (i == 0) { 

                Node2 *new_node = new Node2{ {}, node->result, node->index }; // copy 

                      // split 
                std::string left = analysis_s.substr(0, 1);
                std::string right = analysis_s.substr(1);

                // std::cout << left << "\n";
                // std::cout << right << "\n" ;
                
                // remove prev head 
                Words next_vector = Words( node->data.begin() + 1 , node->data.end() );
                
                Words right_vector;
                if (right.length()) {
                    right_vector.push_back(right);
                }
                
                Words collection;
                
                collection.insert(collection.end(), right_vector.begin(), right_vector.end());
                collection.insert(collection.end(), next_vector.begin(), next_vector.end());
                
                // write to new node 
                new_node->result.push_back(left);
                new_node->data = collection;

                // incr
                new_node->index = node->index + 1;

                //
                std::cout << new_node->data;
                std::cout << new_node->result;

                // 
                std::cout << "------0" << "\n";

                q.push_back(new_node);


            } else if (i == analysis_s.length() - 1) {
                               // split 
                std::string left = analysis_s.substr(0, analysis_s.length() - 1 );
                std::string right = analysis_s.substr( analysis_s.length() - 1 );

                // remove prev head 
                Words next_vector = Words( node->data.begin() + 1 , node->data.end() ); 

                Node2 *new_node = new Node2{ {}, node->result , node->index }; // copy 
                
                // new head 
                Words left_vector = {left};
                Words right_vector = {right};
                Words collection;
                // concat 
                // collection.insert(collection.end(), right_vector.begin(), right_vector.end());
                collection.insert(collection.end(), left_vector.begin() , left_vector.end());
                collection.insert(collection.end(), next_vector.begin() , next_vector.end());

                // set data 
                new_node->data = collection;

                new_node->index = node->index + 1;

                new_node->result.push_back(right);

                std::cout << new_node->data;
                std::cout << new_node->result;
                std::cout << "------1" << "\n";

                q.push_back(new_node);

            } else {
                
                // split (overload left)
                Node2 *new_node1 = new Node2{ {}, node->result,  node->index }; // copy 
                std::string left = analysis_s.substr( 0, i + 1 );
                std::string right = analysis_s.substr( i + 1 );
                // std::string uni = left.substr( left.length() - 1 );
                // left = left.substr( 0, left.length() - 1 );
                Words next_vector = Words( node->data.begin() + 1 , node->data.end() ); 

                // new head 
                Words left_vector = {left};
                Words right_vector = {right};
                Words collection;
                
                collection.insert(collection.end(), left_vector.begin(), left_vector.end());
                collection.insert(collection.end(), right_vector.begin(), right_vector.end());
                collection.insert(collection.end(), next_vector.begin(), next_vector.end());
                
                new_node1->data = collection;
                q.push_back(new_node1);
                
                // split (overload right)
                Node2 *new_node2 = new Node2{ {}, node->result,  node->index }; // copy 
                left = analysis_s.substr( 0, i  );
                right = analysis_s.substr( i );
                next_vector = Words( node->data.begin() + 1 , node->data.end() ); 
                left_vector = {left};
                right_vector = {right};
                collection.clear();
                
                //swapp
                collection.insert(collection.end(), right_vector.begin(), right_vector.end());
                collection.insert(collection.end(), left_vector.begin(), left_vector.end());

                collection.insert(collection.end(), next_vector.begin(), next_vector.end());
                
                new_node2->data = collection;

                q.push_back(new_node2);

                std::cout << new_node1 << "\n";
                std::cout << new_node2 << "\n";

            }
        }

    }
        
}

class Solution {
public:
    bool isScramble(std::string s1, std::string s2) {
        UsedList usedList; 
        // Q q;

        Q2 q;

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

        // init
        init_split2(s1, q);

        bool found_u = false;

        while (!q.empty())  {
             
            Node2 *node = q.front();

            q.pop_front(); 
            
            if (s2.length() == node->result.size()) {
                std::cout << " LENS " << s1.length() << " " << node->result.size() << "\n"; 
                std::cout << " result "<< node->result << "\n";
                
                if (search_2_test2(node, s2))
                    found_u |= true;
                
            } else {

                search_3(s2, node, q);
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
                break; 

            case(5):
                s1 = "abcd";
                s2 = "bcad";
                break; 
                
            default: 
                break;
        
        }

        result = sol.isScramble(s1, s2);



     } catch (const std::runtime_error & e) {

        std::cout << " RUNTIME ERROR "<< e.what() << "\n" ;

    }


    std::cout << " is sramble " << result << "\n";
}