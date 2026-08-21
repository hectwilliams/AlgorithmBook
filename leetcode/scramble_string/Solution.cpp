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
    bool staged;
    std::size_t * const index; // const adress ( non-const value ),
    TNode **  active_ptr; // const adress_of_address -> address_record ( non-const adress_record -> record ),
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



void init_sol(std::string s, std::string sgoal,  Qt &q, ActiveTable &table) {

    // loaded first node into q 

      std::size_t  * const index_ptr = new std::size_t{0}; // const adress ( non-const value )

    //   void mem_addr = (TNode**) malloc(1 * sizeof(TNode*));



    TNode * tnode = new TNode{s, sgoal, nullptr, nullptr, nullptr, nullptr, 0, nullptr, false, index_ptr, nullptr};

    std::cout << " ADDRESS INDEX : "<< (tnode->index) << "\n";
    std::cout << " VALUE INDEX : " << (* tnode->index) << "\n";

    tnode->root = tnode;
    
    table[tnode->root] = { tnode }; // each network has unique active node stored in a shared mem region 
    
    tnode->active = &table[tnode->root]; // point to shared mem region 
    
    TNode **  mem_addr = &tnode;

    tnode->active_ptr = mem_addr;

    q.push_back(tnode);

}

void copy_node_network_helper(TNode * source, TNode * dest, ActiveTable & table) {

    if (source->left) {
        
        dest->left = new TNode{source->left->s, dest->sgoal, nullptr, nullptr, dest, &table[dest->root], source->left->depth, dest->root, source->left->staged, dest->index , dest->active_ptr};
        
        // dest->left->active = &table[dest->root]; 

        copy_node_network_helper(source->left, dest->left, table);

    }

    if (source->right) {
        
        dest->right = new TNode{source->right->s, dest->sgoal, nullptr, nullptr, dest, &table[dest->root], source->right->depth, dest->root, source->right->staged, dest->index, dest->active_ptr};
        
        // dest->right->active = &table[dest->root]; 
        
        copy_node_network_helper(source->right, dest->right, table);

    }


    if ( (*source->active)[0]  == source ) {

        // update destination active node

        table[dest->root][0] = dest;

    }

}

TNode* copy_node_network(TNode * node, ActiveTable &table) {
    
    std::size_t *index_ptr = new std::size_t{ (* node->index) };

    TNode * new_node = new TNode{
        node->root->s,
        node->root->sgoal,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0, 
        nullptr,
        node->root->staged,
        index_ptr, 
        nullptr
    };

    new_node->root = new_node;
    table[new_node->root] = {new_node};
    new_node->active = &table[new_node->root];

    new_node->active_ptr = &new_node;

    copy_node_network_helper(node->root, new_node, table);

    return new_node;
}

void swapT (TNode * node) {
    TNode *temp = node->left;
    node->left = node->right;
    node->right = temp;
    std::cout << "swapped" << "\n";
}

void split_node(TNode *parent, std::string sleft, std::string sright, ActiveTable &table) {

    parent->left = new TNode{sleft,  parent->sgoal, nullptr /* left ptr */, nullptr /* right ptr */, parent, &table[parent->root], parent->depth + 1, parent->root, false, parent->index, parent->active_ptr};
    // parent->left->active = ; // each node points to the same array slot

    parent->right = new TNode{sright, parent->sgoal, nullptr, nullptr, parent, &table[parent->root], parent->depth + 1, parent->root, false, parent->index,  parent->active_ptr};
    // parent->right->active = &table[parent->root]; // each node points to the same array slot

}

void set_next_node(TNode *anchor_node, ActiveTable &table) {
    
    if (!anchor_node) {
        return;
    }

    anchor_node->staged = true;
    *(anchor_node->index) = * (anchor_node->index ) + 1;

    // update active node
    while (anchor_node->prev) {
        
        anchor_node = anchor_node->prev;
        // std::cout << anchor_node->s << "\n";
        if (anchor_node->right && !anchor_node->right->staged) {
            anchor_node = anchor_node->right;
            table[anchor_node->root][0] = anchor_node;  // start node upon entering new test 
            std::cout << "BOOM\t" << anchor_node->s << "\n";

            *anchor_node->active_ptr = anchor_node; 

            std::cout << "ANCHODR ADDRESS=ADDRESS+RECORD\t" << anchor_node->active_ptr << "\n";
            std::cout << "ANCHODR_RECORD\t" << *anchor_node->active_ptr << "\n";
            std::cout << "ANCHODR_RECORD\t" << anchor_node << "\n";

            break;
        }
    }

}

void test_new(TNode *node, Qt &q, ActiveTable &table) {

    TNode *active_node = (*(node->active))[0]; // pull active node 

    std::cout << active_node << "\n";
    
    std::cout << *active_node->index << "\n";

    char c = active_node->sgoal[ * active_node->index ];


    std::cout << " current node string --> " << active_node->s << " \t current char --> " << c << "\n";
    
    if ( ! active_node->s.contains(c) ) {

        return;

    } else {

        std::cout << "FOUND CHAR: " << c  << " " << " FRACTAL BRANCH OF " << active_node->s << "\n";
        
    }

    for(int i = 0; i < active_node->s.length(); i++) {
        
        if (c == active_node->s[i]) {

            if (i == 0) {
                
                if (active_node->s.length() == 1) {

                    TNode *new_node = copy_node_network(active_node, table);

                    TNode *parent =  (*(new_node->active))[0]; // new_node->active[0]; // get path point

                    set_next_node(parent, table);
                    std::cout << "parent:\t" << parent->s << "\n";
                    std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                    q.push_back(parent); 

                } else {

                    // copy tree 
                    TNode *new_node = copy_node_network(active_node, table);
                    
                    TNode *parent =  (*(new_node->active))[0]; // new_node->active[0]; // get path point
                    
                    // leaf node for active node
                    std::string s_left = parent->s.substr(0, 1);
                    std::string s_right = parent->s.substr(1);

                    split_node(parent, s_left, s_right, table);
                    std::cout << "parent:\t" << parent->s << "\n";
                    std::cout << parent->left->s << "\t" << parent->right->s << "\n";
                    
                    // parent->left->sgoal = curr_node->sgoal; // anchor (update sgoal)
                    
                    // std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                    set_next_node(parent->left, table);
                    
                    q.push_back(parent->root);

                }


            } else if (i == active_node->s.length() - 1) {

                // copy tree 
                TNode *new_node = copy_node_network(active_node, table); 

                TNode *parent = (* new_node->active)[0]; // get path point

                // leaf node for active node
                std::string s_left = parent->s.substr(0, i);
                std::string s_right = parent->s.substr(i);
                
                split_node(parent, s_left, s_right, table);
                std::cout << "parent:\t" << parent->s << "\n";
                std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                swapT(parent);
                std::cout << parent->left->s << "\t" << parent->right->s << "\n";


                set_next_node(parent->left, table);
                    
                q.push_back(parent->root);


            } else {

                // copy tree

                TNode *new_node = copy_node_network(active_node, table);

                TNode *parent = (* new_node->active)[0];

                // leaf node for active node
                std::string s_left = parent->s.substr(0, i);
                std::string s_right = parent->s.substr(i);
                split_node(parent, s_left, s_right, table);
                std::cout << "parent:\t" << parent->s << "\n";
                std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                // std::cout << s_left << "\t" << s_right << "\n";
                // std::cout << parent->left << "\t" << parent->right << "\n";

                swapT(parent);
                std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                // std::cout << parent->left->s << "\t" << parent->right->s << "\n";
                
                parent = parent->left;
                s_left = parent->s.substr(0, 1);
                s_right = parent->s.substr(1);

                split_node(parent, s_left, s_right, table);

                std::cout << "parent:\t" << parent->s << "\n";
                std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                parent = parent->left;
                std::cout << "parent:\t" << parent->s << "\n";

                // std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                set_next_node(parent, table);

                q.push_back(parent->root);

                std::cout << "\n---------------------------------------------------------c1------------------------------------------------\n";

                // copy tree
                new_node = copy_node_network(active_node, table);

                parent = (*new_node->active)[0];

                // leaf node for active node
                std::string s2_left = parent->s.substr(0, i+1);
                std::string s2_right = parent->s.substr(i+1);
                
                split_node(parent, s2_left, s2_right, table);

                // std::cout << parent->left << "\t" << parent->right << "\n";
                std::cout << "parent:\t" << parent->s << "\n";
                std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                
                parent = parent->left;
                s2_left = parent->s.substr(0,  parent->s.length()- 1);
                s2_right = parent->s.substr( parent->s.length()- 1 );
                
                split_node(parent, s2_left, s2_right, table);
                
                std::cout << "parent:\t" << parent->s << "\n";
                std::cout << parent->left->s << "\t" << parent->right->s << "\n";
                
                swapT(parent);
                std::cout << parent->left->s << "\t" << parent->right->s << "\n";
                
                parent = parent->left;
                std::cout << "parent:\t" << parent->s << "\n";


                

                // if (parent->s.length() > 1) {


                //     // example bbv<target>

                //     s2_left = parent->s.substr( 0, parent->s.length() - 1 );
                //     s2_right = parent->s.substr( parent->s.length() - 1 );

                //     split_node(parent, s2_left, s2_right, table);
                
                //     swapT(parent);

                //     parent = parent->left;
                    
                // }

                // std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                set_next_node(parent, table);

                q.push_back(parent->root);

                std::cout << "\n-------------------------------------------------c2--------------------------------------------------------\n";

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
        
        std::cout << " --------INIT COMPLETE----------" << "\n";

        while (!q.empty())  {
             
            TNode *node = q.front();

            q.pop_front(); 

            if (*node->index >=  s2.length())
                return true;

            test_new(node, q, table);

            // std::cout << "xxx---NEXT SET OF DATA--xxx\n" << "\n";
        }


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