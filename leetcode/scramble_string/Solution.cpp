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
    Store  active;
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



void gravity_split(Node * root ) {

    Q q;

    q.push_back(root);

    std::string l, r;

    while (!q.empty()) {

        Node *node = q.front();

        q.pop_front(); 

        if (node->depth < 1) {
            
            q.push_back(node->left);
            q.push_back(node->right);
            
        } else if (node->wordn.size() > 1) {
            
            // node has more than 1  sample 
            WordN left_vector(node->wordn.begin() , node->wordn.begin() + 1);
            WordN right_vector(node->wordn.begin() + 1, node->wordn.end());

            node->left = new Node {left_vector, nullptr, nullptr, node , false, node->depth + 1};
            node->right = new Node {right_vector, nullptr, nullptr, node , false, node->depth + 1};

            q.push_back(node->left);
            q.push_back(node->right);

        } 

        std::cout << node->wordn << "\n";
        
    }
    
}

void add_root_node(WordN vector, WordN left_vector, WordN right_vector, Q &q) {
    
    Node *ptr_left, *ptr_right;

    Node * root = new Node {vector, nullptr, nullptr, nullptr , false, 0};

    root->left = new Node{left_vector, nullptr, nullptr, root, false, 1};
    
    root->right = new Node{right_vector, nullptr, nullptr, root, false, 1};

    gravity_split(root);

    q.push_back(root);
}

void init_trees(std::string s1, std::string s2,  Q &q) {
    
    char c = s2[0];

    std::string left, right, left2, right2;

    WordN wordvector;

    // 
    for (std::size_t i = 0; i < s1.length(); i++) {
        wordvector.push_back(  new NodeWord{ s1[i], i }  );
    }
    
    std::cout << wordvector;

    // load initial roots 
    for (int i = 0; i < wordvector.size(); i++)  {
        
        if (wordvector[i]->c == c) {
            
            if (i == 0) { 

                // left = s1.substr(0, 1);
                // right = s1.substr(1);
                int idx =  1 ;
                WordN left_vector(wordvector.begin() , wordvector.begin() + idx);
                WordN right_vector(wordvector.begin() + idx, wordvector.end());
                add_root_node(wordvector, left_vector, right_vector, q);

            } else if (i == s1.length() - 1) {

                // left = s1.substr(0, i);
                // right = s1.substr(i);
                int idx =  s1.length() - 1 ;
                WordN left_vector(wordvector.begin() , wordvector.begin() + idx );
                WordN right_vector( wordvector.begin() + idx ,  wordvector.end() );
                add_root_node(wordvector, left_vector, right_vector, q);

            } else {

                int idx =  i + 1 ;
                WordN left_vector(wordvector.begin() , wordvector.begin() + idx );
                WordN right_vector( wordvector.begin() + idx ,  wordvector.end() );

                std::cout << left_vector << "\n";
                std::cout << right_vector << "\n";
                
                // left = s1.substr(0, i + 1);
                // right = s1.substr(i + 1);
                add_root_node(wordvector, left_vector, right_vector, q);
                
                // left2 = s1.substr(0,i);
                // right2 = s1.substr(i);
                
                idx = i;
                WordN left_vector2(wordvector.begin() , wordvector.begin() + idx );
                WordN right_vector2( wordvector.begin() + idx ,  wordvector.end() );

                std::cout << left_vector2 << "\n";
                std::cout << right_vector2 << "\n";
                add_root_node(wordvector, left_vector2, right_vector2, q);
            }
            
        }
    }

}

// void search(Node *root, std::string s) {
//     Node *node = root; 
//     Node *prev = nullptr; 
//     std::string acc;
    
//     for (const char c: s ) {
        
//         std::string target(1, c);

//         // target must be on left side 
//         while (1) {

//         }
    
//     }
// }

bool find_right(Node *node, char c,  std::size_t &index, bool find_index) {

    if (!node->right)
        return false;   

    WordN collection = node->right->wordn;

    if (find_index) {
            std::cout << "FIND RIGHT TARGET INDEX: " << index << "\n";

        auto it = std::find_if(collection.begin(), collection.end(), 

            [&]( NodeWord *this_wnode) { 
                return (this_wnode->c == c );
            }
        );

        if (it != collection.end() ) {
            
            auto idx =  std::distance(collection.begin(), it);

            index = collection[idx]->index;

            std::cout << "FOUND NODAL INDEX: " << index << "\n";

            return true; 

        }
        
        return false; 

    } else {
            
        std::cout << " DOES VALUE EXIST ON RIGHT SIDE : " << "\n";

        auto it = std::find_if( collection.begin(), collection.end(), 

            [&]( NodeWord *this_wnode) {  return (this_wnode->c == c &&  this_wnode->index == index); }
        );

        if (it != collection.end() ) {
            
            std::cout << "FOUND ON RIGHT SIDE "  << "\n";

            return true; 

        }

        return false; 

    }

}

void swap (Node *node) {
    Node *temp = node->left;
    node->left = node->right;
    node->right = temp;
    node->flipped = true;
    std::cout << "swapped" << "\n";
}

bool find_left(Node *node, char c,  std::size_t &index, bool find_index) {

    // std::cout << "FIND LEFT " << "\n";
    // std::cout << "DEOTH " << node->depth << "\n";
    // std::cout << "data parent " << node->wordn << "\n";
    // std::cout << "data left " << node->left->wordn << "\n";
    // std::cout << "data right " << node->right->wordn << "\n";

    if (!node->left)
        return false;   

    WordN collection = node->left->wordn;

    if (find_index) {

        auto it = std::find_if(collection.begin(), collection.end(), 
            
            [&]( NodeWord *this_wnode) { 
                return (this_wnode->c == c );
            }
        );
        
        if (it != collection.end() ) {
            
            auto idx =  std::distance(collection.begin(), it);
            
            index = collection[idx]->index;
            
            std::cout << "FOUND ON LEFT SIDE "  << "\n";
            
            return true; 
            
        }
        
        return false; 
    
    } else {


        auto it = std::find_if(collection.begin(), collection.end(), 
            
            [&]( NodeWord *this_wnode) { 
                return (this_wnode->c == c  &&  this_wnode->index == index );
            }
        );
        
        if (it != collection.end() ) {
            
            auto idx =  std::distance(collection.begin(), it);
            
            // index = collection[idx]->index;
            
            std::cout << "FOUND ON LEFT SIDE "  << "\n";
            
            return true; 
            
        }
        
        return false; 

    }
}

void delete_node(Node *node, char c, std::size_t index) {

    std::size_t object_index;
    Node *tmp; 

    while (node) {

        std::cout << node->wordn << "\t -----" << node->depth <<  " \t " << node->left  << " " << node->right << " " << " :) " << "\n";
        

        if (!node->left && !node->right) {
            
            node->wordn.erase( node->wordn.begin() );

            if (node->depth == 0) {
                
                node->flipped = false;

            }
            
            node  = node->prev;

        } else {

            // find location c, index
            auto it = std::find_if(node->wordn.begin(), node->wordn.end(), 
        
                [&]( NodeWord *n) { 
                    return (n->c == c &&  n->index == index);
                }
            );

            if (it != node->wordn.end() ) {
                

                // find pos 
                std::size_t pos = std::distance(node->wordn.begin(), it);

                std::cout << "position: " << pos << "\n"; 
                    std::cout << "LIST: " << node->wordn << "\n"; 

                node->wordn.erase( node->wordn.begin() + pos );
                
                // if (node->depth == 0) {
                node->flipped = false; 
                // }
                
                node  = node->prev;
    
            } else {
                return;
            }

        }

    }
    
}

bool test_node(Node *root , std::string s) {
    
    Node *node = root; 
    std::size_t found_index = s.length();
    char target; 

    for (int i = 0; i < s.length(); i++ ) {

        target = s[i];
        
        found_index  = s.length();

        node = root;

        std::cout << "START: " << target << " \n ";
        std::cout << "X: " << node->wordn << " \n ";
        // std::cout << "XLEFT: " << node->left << " \n ";
        // std::cout << "XRIGHT: " << node->right << " \n ";
        // std::cout << "XFLIPPED: " << node->flipped << " \n ";
        // std::cout << "XDEPTH: " << node->depth << " \n ";

        while (1) {

            if (!node->left  && !node->right) {

                if (node->depth == 0) {

                    std::cout << "\t\t\t\t\t-----------BOOM-------\t\t\t----BOOM" << "\n";

                    break ;

                } else {

                    std::cout << "focus on deletion of this node" << "\n";

                    delete_node(node, target, found_index);

                    std::cout << "focus on deletion of this node DONE" << "\n";
                    
                    break;

                }

            } 

            else if ( !node->left ) {

                if (node->flipped) {
                    return false;
                }

               swap(node);
               node = node->left;
                
            }

            else if (node->depth == 0 ) {
                
                std::cout << "DEPTH = 0" << "\n";
                std::cout << node->wordn << "\n";

                if (i == 0) {

                    // handle first branch (level 1)
                    WordN w1 = node->left->wordn;
                    
                    WordN w2 = node->right->wordn;
                    
                    if (w1[w1.size()-1]->c == target) {
                        node = node->left;
                        found_index = w1[w1.size()-1]->index;
                    }  
                    
                    else if (w2[0]->c == target) {
                        node = node->right;
                        found_index = w2[0]->index;
                    }

                } else {

                    find_right(node, target, found_index, found_index == s.length()) ;
                    
                    if (found_index != s.length()) {
                        
                        std::cout << " found_index ON RIGHT SIDE NEW POSITION: " << found_index << "\n";

                        std::cout << node->flipped << "\n";

                        if (node->flipped)
                            return false; 

                        swap(node);
                            
                        node = node->left;
                        continue;
                    }


                    find_left(node, target, found_index, found_index == s.length());

                    if (found_index != s.length()) {
                        
                        std::cout << " found_index ON LEFT SIDE NEW POSITION: " << found_index << "\n";
                    
                        node = node->left;
                        continue;
                    }

                    found_index = s.length();

                    if (found_index == s.length()) {
                        // target not found
                        return false;
                    }

                }
                        
            }

            else if (  find_right(node, target, found_index, found_index == s.length())   ) {

                if (node->flipped)
                    return false;

                swap(node);

                node = node->left;

            }

            else if (  find_left(node, target, found_index, found_index == s.length())  ) {

                node = node->left;

            }


            std::cout << node->wordn;


        }


    }


    if (node->wordn.empty()) {
        
        std::cout << node->wordn << "\n";
        return true;
    }

    return false;


}


void init_sol(std::string s1, std::string s2,  Qt &q, ActiveTable &table) {

    // loaded first node into q 

    TNode * tnode = new TNode{s1, s2, nullptr, nullptr, nullptr, nullptr, 0, nullptr};
    
    tnode->root = tnode;
    
    table[tnode->root] = { tnode };
    
    tnode->active = table[tnode->root];
    
    
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


    if ( source->active[0]->s == dest->s ) {

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
    new_node->active = table[new_node->root];

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
    TNode *curr_node = node->active[0];

    char c = curr_node->sgoal[0];

    curr_node->sgoal = curr_node->sgoal.substr(1);


    for(int i = 0; i < curr_node->s.length(); i++) {
        
        if (c == curr_node->s[i]) {
            // num+=;

            if (i == 0) {
                
                // copy tree 
                TNode *new_node = copy_node_network(node, table);

                TNode *parent = new_node->active[0];


                // leaf node for active node
                std::string s_left = curr_node->s.substr(0, i);
                std::string s_right = curr_node->s.substr(i);

                // parent->left = new TNode{s2_left_left,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                // parent->left->active = table[parent->root];

                // parent->right = new TNode{s2_left_right,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                // parent->right->active = table[parent->root];
                // std::cout << parent->left->s << "\t" << parent->right->s << "\n";

            } else if (i == curr_node->s.length() - 1) {

                // copy tree 

                // leaf node for active node
                std::string s_left = curr_node->s.substr(0, i);
                std::string s_right = curr_node->s.substr(i);

            } else {

                // copy tree

                TNode *new_node = copy_node_network(node, table);

                TNode *node1 = new_node->active[0];

                // leaf node for active node
                std::string s1_left = node1->s.substr(0, i);
                std::string s1_right = node1->s.substr(i);

                node1->left = new TNode{s1_left,  node1->sgoal, nullptr, nullptr, node1, nullptr, node1->depth + 1, node1->root};
                node1->left->active = table[node1->left->root];

                node1->right = new TNode{s1_right, node1->sgoal, nullptr, nullptr, node1, nullptr, node1->depth + 1, node1->root};
                node1->right->active = table[node1->left->root];

                std::cout << s1_left << "\t" << s1_right << "\n";
                std::cout << node1->left << "\t" << node1->right << "\n";

                //split parent.left 

                TNode *parent = node1->left;

                std::string s1_left_left = parent->s.substr(0, parent->s.length() - 1);
                std::string s1_left_right = parent->s.substr(parent->s.length() - 1);

                parent->left = new TNode{s1_left_left,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                parent->left->active = table[parent->left->root];

                parent->right = new TNode{s1_left_right,  parent->sgoal, nullptr, nullptr, parent, nullptr, node1->right->depth + 1, parent->root};
                parent->right->active = table[parent->right->root];

                std::cout << s1_left_left << "\t" << s1_left_right << "\n";

                // swap 

                swapT(node1->left);
                std::cout << node1->left->left->s << "\t" << node1->left->right->s << "\n";
                
                std::cout << "\n-----\n";
                
                // copy tree
                new_node = copy_node_network(node, table);

                TNode *node2 = new_node->active[0];

                // leaf node for active node
                std::string s2_left = node2->s.substr(0, i-1);
                std::string s2_right = node2->s.substr(i-1);


                node2->left = new TNode{s2_left,  curr_node->sgoal, nullptr, nullptr, node2, nullptr, node2->depth + 1, node2->root};
                node2->left->active = table[node2->root];

                node2->right = new TNode{s2_right, curr_node->sgoal, nullptr, nullptr, node2, nullptr, node2->depth + 1, node2->root};
                node2->right->active = table[node2->root];


                std::cout << s2_left << "\t" << s2_right << "\n";
                std::cout << node2->left << "\t" << node2->right << "\n";

                swapT(node2);
                std::cout << node2->left->s << "\t" << node2->right->s << "\n";

                // split parent .left at zero index

                std::string s2_left_left = node2->left->s.substr(0,  1);
                
                std::string s2_left_right = node2->left->s.substr(1);

                std::cout << s2_left_left<< "\t" << s2_left_right << "\n";

                parent = node2->left;
                parent->left = new TNode{s2_left_left,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                parent->left->active = table[parent->root];

                parent->right = new TNode{s2_left_right,  parent->sgoal, nullptr, nullptr, parent, nullptr, parent->depth + 1, parent->root};
                parent->right->active = table[parent->root];
                std::cout << parent->left->s << "\t" << parent->right->s << "\n";
                std::cout << "\n-----\n";

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