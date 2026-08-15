

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

struct Node {
    // std::string s1;
    // std::string s2;
    STable data; 
    // bool swapped; 
    int index;
};


std::ostream& operator<<(std::ostream& os, const std::vector<unsigned>& data) {
    std::size_t i = 0;

     os << "[ ";
    for ( const auto &value: data ) {
        os << " " << value << ", "  ;
        i++;
    }
     os << " ]\n";

    return os; 

}

std::ostream& operator<<(std::ostream& os, Node* node) {
     os << "[\n";
    
    //  os  << "\ts1: "<< node->s1 << " s2: " << node->s2  << "\n";

     for (const auto &[key, value]: node->data) {
        os << "\t" << key << " | " << value << "\n";
     }
     os << "]\n";

    return os; 

}


void add_to_queue() {

}

/* 
    
    First splits of analysis string 

*/
void init_split(std::string s1, std::string s2, Q &q) {
    const char s2_first_char  = s2[0];
    std::size_t index;

    for (std::size_t i = 0; i < s1.length(); i++) {
        if (s1[i] == s2_first_char) {

            if (i == 0) {

                index = 0;
                std::string sub1 = s1.substr(0, 1); 
                std::string sub2 = s2.substr(1); 

                q.push_back(new Node {STable{ {0 ,sub1}, {i+1,sub2} }, 0 });

            } else if (i < s1.length() - 1) {
                
                std::string sub1 = s1.substr(0, i+1); 
                std::string sub2 = s2.substr(i + 1); 

                q.push_back(new Node { STable{ {i,sub1}, {i+1,sub2} },  0 });

            } else if (i == s1.length()-1) {

                q.push_back(new Node {STable{ {i , s1 } }, 0});

            }


            std::cout << q.back();
        }
    }
}

/* 
    True if every entry in table contains single char and matches the characters(in order) of s2 target string
*/
bool test_stable(const STable & table, std::string target) {

    if (table.size() != target.length()) {
        return false;
    }

    std::size_t  n_matches = 0;

    for (std::size_t i = 0; i < target.length(); i++) {

        if (!table.count(i))  // index not present in table 
            return false;

        if (table.at(i).length() != 1)  // string must be length of 1
            return false;

        n_matches += +( table.at(i) == std::string( 1, target[i]) );

    }

    return n_matches == target.length();

}

/*
    search for target index and place in node's table
*/
bool recursive_search(Node *node, std::string s) {
    
    int target_index = node->index;
    char target_char = s[target_index];
    STable table = node->data; 
    std::string single_s = std::string(1, target_char);

    while (table[target_index] != single_s) {
            break;
    }

    return false;
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

void search(std::string s, Node *node, Q & q ) {

    std::size_t targetindex = node->index; 
    
    char target_c = s[targetindex];

    std::vector<unsigned> hits;
    
    // find all indices where

    std::string analysis_s = node->data[targetindex];

    for (std::size_t i = 0; i < analysis_s.length(); i++) {
        
        if (target_c == analysis_s[i]) {
            
            
            hits.push_back(i);

            // new node;
            Node * new_node = new Node{};
            new_node->data = node->data;  // copy data 

            // 
            std::string curr_s = node->data[targetindex];
            std::string a;
            std::string b;

            if (i == 0) {

                a = analysis_s.substr(0, 1);
                // new_node->[i] = a;
                b = analysis_s.substr(1);
                // new_node->[i+1] = b;
                
            } else if(i == analysis_s.length() - 1) {

                 a = analysis_s.substr(0 , i);
                //  new_node->[i] = a;
                 b = analysis_s.substr(i);
                //  new_node->[i] = a;

            } else {
                
                std::cout << i << "\n";
                
                 a = analysis_s.substr(0, i + 1);
                 b = analysis_s.substr(i + 1);
                 std::size_t a_len = a.length();
                 std::size_t b_len = b.length();
                 
            }
                
            if (a[0] != target_c) {
                //move char to front ( equivalent to splitting tail)

                std::string temp_1 = a.substr(0, a.length() - 1);

                std::string temp_0 = a.substr(a.length() - 1);

                a  = temp_0 + temp_1;

            }

            new_node->data[targetindex] = a;
            new_node->data[targetindex + a.length()] = b;

            if (new_node->data[targetindex].length() != 0) {
                // split first

               std::string a  = new_node->data[targetindex].substr(0,1);
                std::string b  = new_node->data[targetindex].substr(1);

                new_node->data[targetindex ] = a;
                new_node->data[targetindex + 1] = b;

            }
            
            std::cout << new_node;
            
            
        }
    }

    std::cout << hits << "\n";

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
            return false; 
        }

        // init
        q.push_back(new Node{  STable{{0, s1 }},  0});
        
        while (!q.empty())  {
             
            Node *node = q.front();

            q.pop_front(); 

            search(s2, node, q);
            
            // for (std::size_t target_index; target_index < s1.length(); target_index++) {
                // break; 
            // }
            
            break; 

        }

        return false;

        // init_split(s1, s2, q);

        // // load first value into 
        // q.push_back(new Node{s1, s2, s1+s2, false, 0});

        while (!q.empty()) {
            
            Node *node = q.front();

            q.pop_front(); 

            // test current node 
            bool found = test_stable(node->data, s2);

            std::cout << " found " << found << "\n";
            std::cout << "\n";

            if (node->index >= s2.length()) {
                continue;
            }

            bool safe_continue = recursive_search(node, s2);
            if (safe_continue) {
                q.push_back(node);
            }

            


            // split
            

            // swap 


        //     if (s1.length() == 0 && s2.length() == 0) {
        //         // test 
        //     }

        //     // swap
        //     if (node->swapped) {
        //         continue; 
        //     } else {
        //         node->swapped = true; 
        //         q.push_back(new Node{s2, s1, s2+s1, true, node->index});
        //     }

        }

        return false;
    }
};

int main() {
    Solution sol;

    std::string s1,s2;

    s1 = "great";
    s2 = "rgeat";

    bool result = sol.isScramble(s1, s2);

    std::cout << " is sramble " << result << "\n";
}