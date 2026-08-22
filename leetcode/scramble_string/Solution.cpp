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
    // Store * active;
    std::size_t depth;
    TNode *root;
    bool staged;
    std::size_t *  index; // const adress ( non-const value ),
    void ** const active_dptr_cstyle_t; 

    // TNode() : s(""), sgoal(""), left(nullptr), right(nullptr), prev(nullptr), active(nullptr), depth(0), root(nullptr), staged(false), index(nullptr), active_dptr_cstyle_t(nullptr)  {}
};
constexpr TNode TNODE_DUMMY = {};



// / const adress_of_address -> address_record ( non-const adress_record -> record ),
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


void print_info(TNode *parent) {
    std::cout << "parent:\t" << parent->s << "\n";
    if (parent->left && parent->right) {
        
        std::cout << "\t\t -> \t"<< parent->left->s << "\t" << parent->right->s << "\n";

    } else {
        std::cout << "--leaf node--" << "\n";
    }
}

void swapT (TNode * node) {
    TNode *temp = node->left;
    node->left = node->right;
    node->right = temp;
    std::cout << "swapped" << "\n";
}

void split_node(TNode *parent, std::string sleft, std::string sright) {

    parent->left = new TNode{sleft,  parent->sgoal, nullptr /* left ptr */, nullptr /* right ptr */, parent, parent->depth + 1, parent->root, false, parent->index, parent->active_dptr_cstyle_t};
    // parent->left->active = ; // each node points to the same array slot

    parent->right = new TNode{sright, parent->sgoal, nullptr, nullptr, parent, parent->depth + 1, parent->root, false, parent->index,  parent->active_dptr_cstyle_t};

    std::cout << "split" << "\n";
}




void copy_node_network_helper(TNode * source, TNode * dest) {

    if (source->left) {
        
        dest->left = new TNode{source->left->s, dest->sgoal, nullptr, nullptr, dest, source->left->depth, dest->root, source->left->staged, dest->index , dest->active_dptr_cstyle_t};
        

        copy_node_network_helper(source->left, dest->left);

    }

    if (source->right) {
        
        dest->right = new TNode{source->right->s, dest->sgoal, nullptr, nullptr, dest, source->right->depth, dest->root, source->right->staged, dest->index, dest->active_dptr_cstyle_t};
        
        
        copy_node_network_helper(source->right, dest->right);

    }

    if (*source->active_dptr_cstyle_t  == source ) {

        // update destination active node

        *dest->active_dptr_cstyle_t = dest;

    }

}

TNode* copy_node_network(TNode * node) {
    
    std::size_t *index_ptr = new std::size_t{ (* node->index) };

    void ** const mem_addr_shared = (void ** const )malloc(sizeof( void *)) ; // allocate const 8 bytes  ( oouter ) 

    TNode * new_node = new TNode{
        node->root->s,
        node->root->sgoal,
        nullptr,
        nullptr,
        nullptr,
        // nullptr,
        0, 
        nullptr,
        node->root->staged,
        index_ptr, 
        mem_addr_shared
    };

    new_node->root = new_node;


    *mem_addr_shared = new_node;

    // new_node->active_dptr_cstyle_t = (void*)new_node; TBD

    copy_node_network_helper(node->root, new_node);

    return (TNode *)*new_node->active_dptr_cstyle_t;     //return active node
}


/* 

    Splits strinf on all split points and creates full node

    Example:

    string s = "ABCD"

    Splits : A-BCD , AB-CD ,  ABC-D
*/
void init_sol_extend(TNode *node, Qt &q) {

    std::string sleft, sright;

    for (std::size_t i = 1; i < node->s.length();  i++) {

        sleft = node->s.substr(0, i );
        sright = node->s.substr(i);
        
        // copy
        
        TNode *curr_node = copy_node_network(node);
        
        // split onf string 

        split_node(curr_node, sleft, sright);
        
        print_info(curr_node);

        // add to queue 

        q.push_back(curr_node);

    }

}


void init_sol(std::string s, std::string sgoal,  Qt &q) {

    // loaded first node into q 

    std::size_t  *  index_ptr = new std::size_t{0}; // const adress ( non-const value )

    void ** const active_mem_addr_shared = (void ** const )malloc(sizeof( void *)) ; // allocate const 8 bytes  ( oouter ) 
    
    TNode * tnode = new TNode{s, sgoal, nullptr, nullptr, nullptr, 0, nullptr, false, index_ptr, active_mem_addr_shared};

    tnode->root = tnode;
    
    *active_mem_addr_shared = tnode;

    init_sol_extend(tnode, q); // loads queue 

}

void set_next_node(TNode *anchor_node) {
    
    if (!anchor_node) {
        return;
    }

    // anchor_node->staged = true;
    *(anchor_node->index) = * (anchor_node->index ) + 1;

    // update active node
    while (anchor_node->prev) {
        
        anchor_node = anchor_node->prev;

        if (anchor_node->right && !anchor_node->right->staged) {
            // if (anchor_node->right ) {

            anchor_node = anchor_node->right;

            *anchor_node->active_dptr_cstyle_t = anchor_node;

            anchor_node->staged = true; 

            ((TNode *)*anchor_node->active_dptr_cstyle_t)->staged = true;

            std::cout << "BOOM\t" << ((TNode *)*anchor_node->active_dptr_cstyle_t)-> s << "\n";

            // (*anchor_node->active_dptr_cstyle_t) = anchor_node; 
            
            // std::cout << "BOOM\t" << ((TNode*)(*anchor_node->active_dptr_cstyle_t) )->s << "\n";

            //  assign new active node  !

            // std::cout << "ANCHODR ADDRESS=ADDRESS+RECORD\t" << anchor_node->active_dptr_cstyle_t << "\n";
            // std::cout << "ANCHODR_RECORD\t" << anchor_node << "\n";
            // std::cout << "ANCHODR_RECORD\t" << *anchor_node->active_dptr_cstyle_t << "\n";

            break;
        }
    }

}

bool build_scramble_network(TNode *node, std::string sgoal, Qt &q) {

    std::cout << "ENTER NODE" << "\t" << node->s << "\n";
    assert(0);
    while (*node->index < sgoal.length()) {

        char character = sgoal[ *node->index ];

        std::cout << "character" << "\t" << character << "\n";

        node->staged = true;

        // make active node 
        *node->active_dptr_cstyle_t = node; 

        print_info(node);

        if (!node->s.contains(character)) {
            std::cout << "Error\t" << node->s << "\n";
            return false;
        } 

        if (!node->left && !node->right) {

            if (node->s.length() == 1) {

                set_next_node(node);

                node = (TNode*)(*node->active_dptr_cstyle_t);

            } else {
                
                std::string l, r;
                
                if (node->s[0] == character) {

                    l = node->s.substr(0, 1);

                    r = node->s.substr(1);

                    split_node(node, l , r);
                    
                } else if (node->s[node->s.length() - 1] == character) {

                    l = node->s.substr(0, node->s.length()-1);

                    r = node->s.substr(node->s.length()-1);
                    
                    split_node(node, l , r);

                } else if (  node->s.contains(character)  ) {
                    
                    std::cout << "BRANCH \t" << node->s << "\n";

                    init_sol_extend(node, q);

                    return false;

                } else {
                    return false; 
                }

            }

        }

        else if (node->left  && node->left->s.contains(character)) {

            node = node->left;

        }

        else if (node->right  && node->right->s.contains(character)) {

            swapT(node);
            print_info(node);

            node = node->left;

        }

    }

    // std::cout << "RESULT\t"<< *node->index << "\n";


    return *node->index  >= sgoal.length();

}

void test_new(TNode *node, Qt &q) {

    std::cout << "-------------------------------w------------------------" << "\n\n";

    // TNode *active_node = (*(node->active))[0]; // pull active node 
    TNode *active_node = (TNode*) (*node->active_dptr_cstyle_t); 

    if (active_node->prev){
        
        std::cout << "PREV " << active_node->prev->s << "\n";

    }

    std::cout << "ACTIVE " << active_node->s << "\n";
    
    // std::cout << *node->active_dptr_cstyle_t << "\n";

    std::cout << "INDEX \t" << *active_node->index << "\n";

    char c = active_node->sgoal[ * active_node->index ];

    std::cout << " current node string --> " << active_node->s << " \t EXPECT CHAR --> " << c << "\n";
    
    if ( ! active_node->s.contains(c) ) {

        return;

    } else {

        std::cout << "FOUND CHAR: " << c  << " " << " FRACTAL BRANCH OF " << active_node->s << "\n";
        
    }

    for(int i = 0; i < active_node->s.length(); i++) {
        
        if (c == active_node->s[i]) {

            if (i == 0) {
                
                if (active_node->s.length() == 1) {

                    TNode *new_node = copy_node_network(active_node);

                    // TNode *parent =  (*(new_node->active))[0]; // new_node->active[0]; // get path point

                    TNode *parent = (TNode *)(*new_node->active_dptr_cstyle_t);
                    print_info(parent);

                    set_next_node(parent);
                    
                    q.push_back(parent); 
                    std::cout << "\n---------------------------------------------------------i0-0------------------------------------------------\n";

                } else {

                    // copy tree 
                    TNode *new_node = copy_node_network(active_node);
                    
                    // TNode *parent =  (*(new_node->active))[0]; // new_node->active[0]; // get path point
                    
                    TNode *parent = (TNode*) *new_node->active_dptr_cstyle_t; // new_node->active[0]; // get path point

                    // assert(0);
                    
                    // leaf node for active node
                    std::string s_left = parent->s.substr(0, 1);
                    std::string s_right = parent->s.substr(1);

                    split_node(parent, s_left, s_right);
                    std::cout << "split\n";
                    std::cout << "grandparent:\t" << parent->prev->s << "\n";
                    print_info(parent);
                    
                    // parent->left->sgoal = curr_node->sgoal; // anchor (update sgoal)
                    
                    // std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                    // set 
                    parent->left->staged = true;
                    set_next_node(parent->left);
                    
                    q.push_back(parent->root);
                    
                    std::cout << "\n---------------------------------------------------------i0-1------------------------------------------------\n";

                }

            } else if (i == active_node->s.length() - 1) {

                // copy tree 
                TNode *new_node = copy_node_network(active_node); 

                // TNode *parent = (* new_node->active)[0]; // get path point

                TNode *parent = (TNode*) *new_node->active_dptr_cstyle_t; // new_node->active[0]; // get path point

                // leaf node for active node
                std::string s_left = parent->s.substr(0, i);
                std::string s_right = parent->s.substr(i);
                
                split_node(parent, s_left, s_right);
                std::cout << "split" << "\n";
                print_info(parent);
                swapT(parent);
                print_info(parent);
                    
                parent->left->staged = true;

                set_next_node(parent->left);
                    
                q.push_back(parent->root);
                
                std::cout << "\n---------------------------------------------------------iend------------------------------------------------\n";

            } else {

                // copy tree

                TNode *new_node = copy_node_network(active_node);

                // TNode *parent = (* new_node->active)[0];

                TNode *parent = (TNode*) *new_node->active_dptr_cstyle_t; // new_node->active[0]; // get path point

                // leaf node for active node
                std::string s_left = parent->s.substr(0, i);
                std::string s_right = parent->s.substr(i);
                split_node(parent, s_left, s_right);
                std::cout << "parent:\t" << parent->s << "\n";
                std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                // std::cout << s_left << "\t" << s_right << "\n";
                // std::cout << parent->left << "\t" << parent->right << "\n";

                swapT(parent);
                std::cout << parent->left->s << "\t" << parent->right->s << "\n";

                // std::cout << parent->left->s << "\t" << parent->right->s << "\n";
                
                parent->left->staged = true;
                parent = parent->left;

                s_left = parent->s.substr(0, 1);
                s_right = parent->s.substr(1);

                split_node(parent, s_left, s_right);
                print_info(parent);
                
                parent->left->staged = true;
                parent = parent->left;
                // std::cout << parent->left->s << "\t" << parent->right->s << "\n";
                set_next_node(parent);

                q.push_back(parent->root);

                std::cout << "\n---------------------------------------------------------c1------------------------------------------------\n";

                // copy tree
                new_node = copy_node_network(active_node);

                // parent = (*new_node->active)[0];

                parent = (TNode*) *new_node->active_dptr_cstyle_t; // new_node->active[0]; // get path point

                // leaf node for active node
                std::string s2_left = parent->s.substr(0, i+1);
                std::string s2_right = parent->s.substr(i+1);
                
                split_node(parent, s2_left, s2_right);

                // std::cout << parent->left << "\t" << parent->right << "\n";
                print_info(parent);

                parent->left->staged = true;
                parent = parent->left;
                s2_left = parent->s.substr(0,  parent->s.length()- 1);
                s2_right = parent->s.substr( parent->s.length()- 1 );
                
                split_node(parent, s2_left, s2_right);
                print_info(parent);
                swapT(parent);
                print_info(parent);
                
                parent->left->staged = true;
                parent = parent->left;
                std::cout << "parent:\t" << parent->s << "\n";

                set_next_node(parent);

                q.push_back(parent->root);

                std::cout << "\n-------------------------------------------------c2--------------------------------------------------------\n";

                // copy tree
                new_node = copy_node_network(active_node);


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

        init_sol(s1, s2, q);
        
        std::cout << " --------INIT COMPLETE----------" << "\n";
        
        while (!q.empty())  {
            
            TNode *node = q.front();
            
            q.pop_front(); 

            std::cout << "ATTEMPT\t\n";
            found_u = build_scramble_network(node, s2, q);
            if (found_u) {
                return true;
            }

            // if (*node->index >=  s2.length())
            // return true;

            // test_new(node, q);

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