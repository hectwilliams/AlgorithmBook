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
#include <iterator>

struct Node2; 
struct Node; 
struct NodeWord;
struct TNode;

using Q2 = std::deque<Node2 *>;
using Q = std::deque<Node *>;
using Qt = std::deque<TNode*>;

using UsedList = std::map<std::string, bool>;
using STable = std::map<std::size_t, std::string> ;
using Words = std::vector< std::string>;
using WordN = std::vector<NodeWord*>;

using Store = std::array< TNode* , 1> ;

using ActiveTable = std::map<TNode*, Store >;

// using ActiveTable = std::map<TNode*,  TNode** >;


struct Node2 {
    Words data;
    Words result;
    // std::string acc; 
    int index;
};

struct NodeWord {
    char c;
    std::size_t index;
};

struct Node {
    WordN wordn;
    Node * left;
    Node * right;
    Node * prev;
    bool flipped;
    std::size_t depth;
};

struct TNode {
    std::string s;
    std::string sgoal;
    TNode * left;
    TNode * right;
    TNode * prev;
    Store * active;
    std::size_t depth;
    TNode *root;
};

struct Tree {
    Node * root;
};

std::ostream& operator<<(std::ostream& os, const WordN & data) {
    os << "[ ";
    for ( const auto &record: data ) {
        os << " " << record->c << "[" <<  record->index << "]"  << " , "  ;
    }
     os << " ]\n";
    return os; 
}

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







void init_sol(std::string s1, std::string s2,  Qt &q, ActiveTable &table) {

    // loaded first node into q 

    TNode * tnode = new TNode{s1, s2, nullptr, nullptr, nullptr, nullptr, 0, nullptr};
    
    tnode->root = tnode;
    
    table[tnode->root] = { tnode };
    
    tnode->active = &table[tnode->root];
    
    
    q.push_back(tnode);

}

void copy_node_network_helper(TNode * source, TNode * dest, ActiveTable & table) {

    if (source->left) {
        
        dest->left = new TNode{source->left->s, source->left->sgoal, nullptr, nullptr, dest, nullptr, source->left->depth, dest->root};
        
        copy_node_network_helper(source->left, dest->left, table);

    }

    if (source->right) {
        
        dest->right = new TNode{source->right->s, source->right->sgoal, nullptr, nullptr, dest, nullptr, source->right->depth, dest->root};
        
        copy_node_network_helper(source->right, dest->right, table);

    }


    if ( (*source->active)[0]->s == dest->s ) {

        // update destination active node

        table[dest->root][0] = dest;

    }

}

TNode* copy_node_network(TNode * node, ActiveTable &table) {

    TNode * new_node = new TNode{
        node->root->s,
        node->root->sgoal,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0, 
        nullptr,
    };

    new_node->root = new_node;
    table[new_node->root] = {new_node};
    new_node->active = &table[new_node->root];

    copy_node_network_helper(node->root, new_node, table);

    return new_node;
}

void swapT (TNode * node) {
    TNode *temp = node->left;
    node->left = node->right;
    node->right = temp;
    std::cout << "swapped" << "\n";
}

void test_new(TNode *node, Qt &q, ActiveTable &table) {

    std::size_t num = 0;
    TNode *curr_node = (*(node->active))[0];

    char c = curr_node->sgoal[0];

    curr_node->sgoal = curr_node->sgoal.substr(1);


    std::cout << "current node string --> " << curr_node->s << "\n";

   if (!curr_node->s.contains(c)) {
    std::cout << "TESTING "<< c << ", ERROR: failed char...skipping\n";

    return;
   } else {
    std::cout << "find char: " << c << "\n";
   }

   if (curr_node->sgoal.length() == 2) {
        assert(0);
   }

    if (curr_node->s.length() > 1) {

        for(int i = 0; i < curr_node->s.length(); i++) {
            
            if (c == curr_node->s[i]) {
                // num+=;
    
                if (i == 0) {
                    
                    // copy tree 
                    TNode *new_node = copy_node_network(node, table);
    
                    TNode *parent =  (*(new_node->active))[0]; // new_node->active[0]; // get path point
    
                    // leaf node for active node
                    std::string s_left = parent->s.substr(0, i + 1);
                    std::string s_right = parent->s.substr(i+1);
    
                    parent->left = new TNode{s_left,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                    parent->left->active = &table[parent->root];

                    // std::cout <<  &(parent->left->active)  << "\n";
    
                    parent->right = new TNode{s_right,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                    parent->right->active =  &table[parent->root];

                    // std::cout <<  &(parent->right->active)  << "\n";

    
                    {

                        TNode *anchor_node = parent->left; // set anchor node (recently found char)
                        
                        // update active node
                        while (anchor_node->prev) {
                            anchor_node = anchor_node->prev;
                            if (anchor_node->right) {
                                anchor_node = anchor_node->right;
                                table[anchor_node->root][0] = anchor_node;
                                std::cout << "BOOM\t" << anchor_node->s << "\n";
                                break;
                            }
                        }
                        
                    }
                    q.push_back(parent->root);


                    // update active
                    // table[parent->root][0] = parent->left;
    
                } else if (i == curr_node->s.length() - 1) {
    
                    // copy tree 
                    TNode *new_node = copy_node_network(node, table);
    
                    TNode *parent = (* new_node->active)[0]; // get path point
    
                    // leaf node for active node
                    std::string s_left = parent->s.substr(0, i);
                    std::string s_right = parent->s.substr(i);
    
    
                    parent->left = new TNode{s_left,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                    parent->left->active = &table[parent->root];
    
                    parent->right = new TNode{s_right,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                    parent->right->active = &table[parent->root];
    
                    swapT(parent);

                    {

                        TNode *anchor_node = parent->left; // set anchor node (recently found char)
                        
                        // update active node
                        while (anchor_node->prev) {
                            anchor_node = anchor_node->prev;
                            if (anchor_node->right) {
                                anchor_node = anchor_node->right;
                                table[anchor_node->root][0] = anchor_node;
                                std::cout << "BOOM\t" << anchor_node->s << "\n";
                                
                                break;
                            }
                        }
                        
                    }
                    q.push_back(parent->root);


                } else {
    
                    // copy tree
    
                    TNode *new_node = copy_node_network(node, table);
    
                    TNode *node1 = (* new_node->active)[0];
    
                    // leaf node for active node
                    std::string s1_left = node1->s.substr(0, i);
                    std::string s1_right = node1->s.substr(i);
    
                    node1->left = new TNode{s1_left,  node1->sgoal, nullptr, nullptr, node1, nullptr, node1->depth + 1, node1->root};
                    node1->left->active = &table[node1->left->root];
    
                    node1->right = new TNode{s1_right, node1->sgoal, nullptr, nullptr, node1, nullptr, node1->depth + 1, node1->root};
                    node1->right->active = &table[node1->left->root];
    
                    std::cout << s1_left << "\t" << s1_right << "\n";
                    std::cout << node1->left << "\t" << node1->right << "\n";
    
                    swapT(node1);

                    std::cout << node1->left->s << "\t" << node1->right->s << "\n";
                    
                    //split parent.left ( target index 0)
                    
                    TNode *parent = node1->left;
                    std::string s1_left_left = parent->s.substr(0, 1);
                    std::string s1_left_right = parent->s.substr(1);

                    // std::string s1_left_left = parent->s.substr(0, parent->s.length() - 1);
                    // std::string s1_left_right = parent->s.substr(parent->s.length() - 1);
    
                    parent->left = new TNode{s1_left_left,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                    parent->left->active = &table[parent->left->root];
    
                    parent->right = new TNode{s1_left_right,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                    parent->right->active = &table[parent->right->root];
    
                    std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                    {

                        TNode *anchor_node = parent->left; // set anchor node (recently found char)
                        
                        // update active node
                        while (anchor_node->prev) {
                            anchor_node = anchor_node->prev;
                            if (anchor_node->right) {
                                anchor_node = anchor_node->right;
                                table[anchor_node->root][0] = anchor_node;
                                std::cout << "BOOM\t" << anchor_node->s << "\n";
                                break;
                            }
                        }
                        
                    }
                    q.push_back(parent->root);

                    std::cout << "\n---------------------------------------------------------------------------------------------------------\n";
                    







                    // copy tree
                    new_node = copy_node_network(node, table);
    
                    TNode *node2 = (*new_node->active)[0];
    
                    // leaf node for active node
                    std::string s2_left = node2->s.substr(0, i+1);
                    std::string s2_right = node2->s.substr(i+1);
    
    
                    node2->left = new TNode{s2_left,  curr_node->sgoal, nullptr, nullptr, node2, nullptr, node2->depth + 1, node2->root};
                    node2->left->active = &table[node2->root];
    
                    node2->right = new TNode{s2_right, curr_node->sgoal, nullptr, nullptr, node2, nullptr, node2->depth + 1, node2->root};
                    node2->right->active = &table[node2->root];
    
    
                    std::cout << s2_left << "\t" << s2_right << "\n";
                    std::cout << node2->left << "\t" << node2->right << "\n";
    
                    std::cout << node2->left->s << "\t" << node2->right->s << "\n";
    
                    // split parent .left at zero index
    
                    parent = node2->left;
                    
                    std::string s2_left_left = parent->s.substr(0,  1);
                    
                    std::string s2_left_right = parent->s.substr(1);
    
                    std::cout << s2_left_left<< "\t" << s2_left_right << "\n";

                    
                    
                    
                    parent->left = new TNode{s2_left_left,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                    parent->left->active = &table[parent->root];
    
                    parent->right = new TNode{s2_left_right,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                    parent->right->active = &table[parent->root];
                    
                    swapT(parent);
                    std::cout << parent->left->s << "\t" << parent->right->s << "\n";
                    std::cout << "HAHAHAH\n";
                    
                    // std::string sl = parent->left->s.substr(0, parent->left->s.length()-1);
                    // std::string sr = parent->left->s.substr(parent->left->s.length()-1);
                    
                    // std::cout << sl << "\n";
                    // std::cout << sr << "\n";

                    // parent = parent->left;
                    
                    // parent->left = new TNode{sl,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                    // parent->left->active = &table[parent->root];
                    
                    // parent->right = new TNode{sr,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                    // parent->right->active = &table[parent->root];
                    
                    // swapT(parent);
                    std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                    {
                        TNode *anchor_node = parent->left; // set anchor node (recently found char)

                          // update active node
                        while (anchor_node->prev) {
                            anchor_node = anchor_node->prev;
                            if (anchor_node->right) {
                                anchor_node = anchor_node->right;
                                table[anchor_node->root][0] = anchor_node;
                                std::cout << "BOOM\t" << anchor_node->s << "\n";
                                break;
                            }
                        }
                    }

                    q.push_back(parent->root);
                    std::cout << "BOOM\t" << (*parent->active)[0]->s << "\n";

                    std::cout << "\n---------------------------------------------------------------------------------------------------------\n";
                }
    
            }
        }
    }

   


}


class Solution {
public:
    bool isScramble(std::string s1, std::string s2) {
        UsedList usedList; 
        // Q q;
        bool found_u = false;

        // Q2 q;

        // Q q;

        Qt q;

        ActiveTable table;

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

        // init_trees(s1, s2, q);

        init_sol(s1, s2, q, table);
        
        std::cout << "------------------" << "\n";


        while (!q.empty())  {
             
            TNode *node = q.front();

            q.pop_front(); 

            if (node->sgoal == "")
                assert(0);

            test_new(node, q, table);

            // std::cout << "\t\t\t\t\t-------START OF A NEW SESSION------------" << "\n";

            // bool response = test_node(node, s2);

            // found_u |=  response;

            // std::cout << node->wordn << "\n";

            

            // search(node, s2);


            
            // if (s2.length() == node->result.size()) {
            //     std::cout << " LENS " << s1.length() << " " << node->result.size() << "\n"; 
            //     std::cout << " result "<< node->result << "\n";
                
            //     if (search_2_test2(node, s2))
            //         found_u |= true;
                
            // } else {

            //     search_3(s2, node, q);
            // }
            
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