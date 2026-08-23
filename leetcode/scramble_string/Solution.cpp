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
#include <cstdlib>

struct TNode;

using Qt = std::deque<TNode*>;

using Store = std::array< TNode* , 1> ;
using ActiveTable = std::map<TNode*, Store >;

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

};
constexpr TNode TNODE_DUMMY = {};


bool histo_valid (std::string s1, std::string s2) {
    // TBD this can be improved O(N)
    std::map<char, int > zero_map;

    if (s1.length() != s2.length())
        return false; 

    for ( std::size_t i = 0; i < s1.length(); i++) {

        char c1 = s1[i];
        char c2 = s2[i];

        if (zero_map.count(c1) == 0)
            zero_map[c1] = 0;

        if (zero_map.count(c2) == 0)
            zero_map[c2] = 0;

        zero_map[c1] -= 1;
        zero_map[c2] += 1;

    }

    unsigned not_zero_sum_count = 0;

    for (const auto &[key, value]: zero_map) {
        not_zero_sum_count += +(value != 0);
    }

    return not_zero_sum_count == 0;

    

    // for(std::size_t i = 0; i < s1.length(); i++) {
        
    //     if (zero_map.count(s1[i]) == 0)
    //         zero_map[s1[i]] = 0;

    //     if (zero_map.count(s2[i]) == 0)
    //         zero_map[s2[i]] = 0;

    //     zero_map[s1[i]]++;
    //     zero_map[s2[i]]--;

    // }

    // int sum = 0;

    // for (const auto &[key, value]: zero_map) {
    //     sum += value;
    // }

    // return (sum == 0);
}


void print_info(TNode *parent) {

    // std::cout << " PRINT INFO: " << "\n";

    // std::cout << "\tparent:\t" << parent->s << "\n";
    
    if (parent->left && parent->right) {
        //  
        // std::cout << "\t\t" << parent->left->s << " ( " << parent->left->sgoal  << " ) " << "\t" << parent->right->s << " ( " << parent->right->sgoal  << " ) "<< "\n";

    } else {

        // std::cout << "\t--is a leaf node--" << "\n";

    }
}

void swapT (TNode * node) {

    std::string sleft_sgoal = node->left->sgoal;
    std::string sright_sgoal= node->right->sgoal;
    
    TNode *temp = node->left;
    node->left = node->right;
    node->right = temp;

    node->left->sgoal = node->sgoal.substr(0, node->left->s.length()) ;
    node->right->sgoal = node->sgoal.substr(node->left->s.length()) ;

}

void split_node(TNode *parent, std::string sleft, std::string sright) {

    parent->left = new TNode{sleft,  parent->sgoal.substr(0, sleft.length()), nullptr /* left ptr */, nullptr /* right ptr */, parent, parent->depth + 1, parent->root, false, parent->index, parent->active_dptr_cstyle_t};

    parent->right = new TNode{sright, parent->sgoal.substr(sleft.length()), nullptr, nullptr, parent, parent->depth + 1, parent->root, false, parent->index,  parent->active_dptr_cstyle_t};

}

void clear_node(TNode *node) {
    *node->active_dptr_cstyle_t = nullptr;
    std::free(node->active_dptr_cstyle_t); // free double pointer 
    delete node->index;

    delete node; 
}


void copy_node_network_helper(TNode * source, TNode * dest) {

    if (source->left) {
        
        dest->left = new TNode{source->left->s, source->left->sgoal , nullptr, nullptr, dest, source->left->depth, dest->root, source->left->staged, dest->index , dest->active_dptr_cstyle_t};
        

        copy_node_network_helper(source->left, dest->left);

    }

    if (source->right) {
        
        dest->right = new TNode{source->right->s, source->right->sgoal, nullptr, nullptr, dest, source->right->depth, dest->root, source->right->staged, dest->index, dest->active_dptr_cstyle_t};
        
        
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

bool valid_split(std::string sleft, std::string sright, std::string sgoal) {

    unsigned len = sleft.length();

    std::string sleft_sgoal = sgoal.substr(0, len);
    std::string sright_sgoal = sgoal.substr(len);

    // histo check 

    // case 1 
    bool left_check = histo_valid(sleft, sleft_sgoal);
    bool right_check = histo_valid(sright, sright_sgoal);
    
    // std::cout << " TEST SPLIT PARENT STRING " << "\t" << sleft << "(" << sleft_sgoal << ")" << "-"  << " " << sright <<  " ( " << sright_sgoal <<  " ) " << "\n";

    if (left_check & right_check) {

        // std::cout << "TEST PASSED" << "\n";
        
        // std::cout << " CHILDREN " <<  sleft_sgoal << " \t"  << sright_sgoal << "\n";
        
    }
    // histo check 

    return left_check & right_check;
}

/* 

    Splits strinf on all split points and creates full node

    Example:

    string s = "ABCD"

    Splits : A-BCD , AB-CD ,  ABC-D

*/

void init_sol_extend(TNode *node, Qt &q) {
    
    std::string sleft, sright;

    std::vector< TNode* > trashmap;

    for (std::size_t i = 1; i < node->s.length();  i++) {

        sleft = node->s.substr(0, i);

        sright = node->s.substr(i);

        // copy
        // TNode *curr_node = copy_node_network(node);
        
        // add to queue  if passed 
        if (valid_split(sleft, sright, node->sgoal)) {
            
            trashmap.push_back(node);
            
            TNode *curr_node = copy_node_network(node);

            split_node(curr_node, sleft, sright);

            print_info(curr_node);

            // succesful split ( move left )
            // curr_node = curr_node->left;

            // * node->active_dptr_cstyle_t = curr_node;

            q.push_back(curr_node);
            

        } 

        // add to queue  if passed 
        if (valid_split( sright , sleft , node->sgoal)) {
            
            if (trashmap.empty() || trashmap[trashmap.size()- 1] != node) {
                trashmap.push_back(node);
            }

            TNode *curr_node = copy_node_network(node);

            split_node(curr_node, sright ,sleft );

            print_info(curr_node);

            // succesful split ( move left )
            // curr_node = curr_node->left;

            // * node->active_dptr_cstyle_t = curr_node;

            q.push_back(curr_node);
            

        } 

        
    }

    // clear stale/copied mem

    // for (const auto n: trashmap) {
    // }
 

    // std::cout  << n_possible << " added to queue "<< "\n\n\n";

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

            // std::cout << "BOOM\t" << ((TNode *)*anchor_node->active_dptr_cstyle_t)-> s << "\n";

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

    // std::cout << "ENTER STRING" << "\t" << node->s << "\n";
    // std::cout << "ENTER GOAL" << "\t" << node->sgoal << "\n";


    while (*node->index < sgoal.length()) {

        char character = sgoal[ *node->index ];

        // std::cout << "character" << "\t" << character << "\n";

        node->staged = true;

        // make active node 
        *node->active_dptr_cstyle_t = node; 

        // std::cout << "ACTIVE NODE" << "\t" << node->s << "\n";
        // std::cout << "ACTIVE NODE GOAL" << "\t" << node->sgoal << "\n";

        print_info(node);


        if (!node->s.contains(character)) {
            // std::cout << "Error\t" << node->s << "\n";
            clear_node(node);
            return false;
        } 

        if (!node->left && !node->right) {  

            // process leaf node

            if (node->s.length() == 1) {

                set_next_node(node);

                node = (TNode*)(*node->active_dptr_cstyle_t);
                
                node->staged = true;

            } else {
                
                std::string l, r;
                
                std::ptrdiff_t count = std::count(node->s.begin(), node->s.end(), character);

                if (node->s[0] == character && count == 1) {

                    l = node->s.substr(0, 1);

                    r = node->s.substr(1);

                    split_node(node, l , r);

                    node = node->left ;  // move left down 

                    *node->active_dptr_cstyle_t = node; // update active 


                    
                } else if (node->s[node->s.length() - 1] == character && count == 1) {

                    l = node->s.substr(0, node->s.length()-1);

                    r = node->s.substr(node->s.length()-1);
                    
                    split_node(node, l , r);

                    swapT(node); 

                    node = node->left; // move left down 
                    
                    *node->active_dptr_cstyle_t = node; // update active 

                } else if (  node->s.contains(character)  ) {
                    
                    // std::cout << "BRANCH NODE \t" << node->s << "\n";
                    // std::cout << "BRANCH SGOAL \t" << node->sgoal << "\n";
                    // std::cout << "BRANCH SGOAL \t" << ( (TNode *)(*node->active_dptr_cstyle_t))->sgoal << "\n";

                    *node->active_dptr_cstyle_t = node;  // parent is active 

                    init_sol_extend(node, q); 
                    

                    clear_node(node);

                    return false;

                } else {

                    clear_node(node);

                    return false; 
                }

            }

        }

            
        else if (node->left  && node->left->s.contains(character)) {

            node = node->left;
            
            // *node->active_dptr_cstyle_t = node; 

            // std::cout << "TARGET CHAR LEFT" << "\n";

            // std::cout << "ENTER STRING" << "\t" << node->s << "\n";
            
            // std::cout << "ENTER GOAL" << "\t" << node->sgoal << "\n";

        }

        else if (node->right  && node->right->s.contains(character)) {
            
            // std::cout << "TARGET CHAR RIGHT " << "\n";

            swapT(node);

            // print_info(node);

            node = node->left;
            
            // std::cout << "TARGET CHAR LEFT " << "\n";

            // *node->active_dptr_cstyle_t = node; 

            // std::cout << "ENTER STRING" << "\t" << node->s << "\n";
            
            // std::cout << "ENTER GOAL" << "\t" << node->sgoal << "\n";

        }

    }

    return *node->index  >= sgoal.length();

}



class Solution {
public:
    bool isScramble(std::string s1, std::string s2) {
        // Q q;
        bool found_u = false;

        Qt q;

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
            // std::cout << "HISTO" << "\n";
            return false; 
        }

        // init_trees(s1, s2, q);

        init_sol(s1, s2, q);
        
        // std::cout << " --------INIT COMPLETE----------" << "\n";
        
        while (!q.empty())  {
            
            TNode *node = q.front();
            
            q.pop_front(); 

            // std::cout << "\t\t\t ATTEMPT \t \n";
            
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
                
            case(6):
                s1 = "great";
                s2 = "gtear";
                break; 

            case(7):
                s1 = "abbbcbaaccacaacc";
                s2 = "acaaaccabcabcbcb";
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