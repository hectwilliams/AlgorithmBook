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
struct Node;

using Qt = std::deque<TNode*>;
using Q = std::deque<Node*>;

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

struct Node {
    std::string s;
    std::string sgoal;
    std::string gold_sgoal;
    Node * left;
    Node * right;
    Node * prev;
    Node *root;
    bool staged;
    std::size_t *  index; // const adress ( non-const value ),
    void ** const active_dptr_cstyle_t; 
};



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


void print_node(Node *parent) {

    // std::cout << " PRINT INFO: " << "\n";

    std::cout << "\tparent:\t" << parent->s << "\n";
    
    if (parent->left && parent->right) {
        //  
        std::cout << "\t\t" << parent->left->s << " ( " << parent->left->sgoal  << " ) " << "\t" << parent->right->s << " ( " << parent->right->sgoal  << " ) "<< "\n";

    } else {

        std::cout << "\t--is a leaf node--" << "\n";

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


// void copy_node_network_helper(TNode * source, TNode * dest) {

//     if (source->left) {
        
//         dest->left = new TNode{source->left->s, source->left->sgoal , nullptr, nullptr, dest, source->left->depth, dest->root, source->left->staged, dest->index , dest->active_dptr_cstyle_t};
        

//         copy_node_network_helper(source->left, dest->left);

//     }

//     if (source->right) {
        
//         dest->right = new TNode{source->right->s, source->right->sgoal, nullptr, nullptr, dest, source->right->depth, dest->root, source->right->staged, dest->index, dest->active_dptr_cstyle_t};
        
        
//         copy_node_network_helper(source->right, dest->right);

//     }

//     if (*source->active_dptr_cstyle_t  == source ) {

//         // update destination active node

//         *dest->active_dptr_cstyle_t = dest;

//     }

// }

// TNode* copy_node_network(TNode * node) {
    
//     std::size_t *index_ptr = new std::size_t{ (* node->index) };

//     void ** const mem_addr_shared = (void ** const )malloc(sizeof( void *)) ; // allocate const 8 bytes  ( oouter ) 

//     TNode * new_node = new TNode{
//         node->root->s,
//         node->root->sgoal,
//         nullptr,
//         nullptr,
//         nullptr,
//         // nullptr,
//         0, 
//         nullptr,
//         node->root->staged,
//         index_ptr, 
//         mem_addr_shared
//     };

//     new_node->root = new_node;

//     *mem_addr_shared = new_node;

//     // new_node->active_dptr_cstyle_t = (void*)new_node; TBD

//     copy_node_network_helper(node->root, new_node);

//     return (TNode *)*new_node->active_dptr_cstyle_t;     //return active node
// }

// bool valid_split(std::string sleft, std::string sright, std::string sgoal) {

//     unsigned len = sleft.length();

//     std::string sleft_sgoal = sgoal.substr(0, len);
//     std::string sright_sgoal = sgoal.substr(len);

//     // histo check 

//     // case 1 
//     bool left_check = histo_valid(sleft, sleft_sgoal);
//     bool right_check = histo_valid(sright, sright_sgoal);
    
//     // std::cout << " TEST SPLIT PARENT STRING " << "\t" << sleft << "(" << sleft_sgoal << ")" << "-"  << " " << sright <<  " ( " << sright_sgoal <<  " ) " << "\n";

//     if (left_check & right_check) {

//         // std::cout << "TEST PASSED" << "\n";
        
//         // std::cout << " CHILDREN " <<  sleft_sgoal << " \t"  << sright_sgoal << "\n";
        
//     }
//     // histo check 

//     return left_check & right_check;
// }




// /* 

//     Splits strinf on all split points and creates full node

//     Example:

//     string s = "ABCD"

//     Splits : A-BCD , AB-CD ,  ABC-D

// */

// void init_sol_extend(TNode *node, Qt &q) {
    
//     std::string sleft, sright;

//     std::vector< TNode* > trashmap;

//     for (std::size_t i = 1; i < node->s.length();  i++) {

//         sleft = node->s.substr(0, i);

//         sright = node->s.substr(i);

//         // copy
//         // TNode *curr_node = copy_node_network(node);
        
//         // add to queue  if passed 
//         if (valid_split(sleft, sright, node->sgoal)) {
            
//             trashmap.push_back(node);
            
//             TNode *curr_node = copy_node_network(node);

//             split_node(curr_node, sleft, sright);

//             print_info(curr_node);

//             // succesful split ( move left )
//             // curr_node = curr_node->left;

//             // * node->active_dptr_cstyle_t = curr_node;

//             q.push_back(curr_node);
            

//         } 

//         // add to queue  if passed 
//         if (valid_split( sright , sleft , node->sgoal)) {
            
//             if (trashmap.empty() || trashmap[trashmap.size()- 1] != node) {
//                 trashmap.push_back(node);
//             }

//             TNode *curr_node = copy_node_network(node);

//             split_node(curr_node, sright ,sleft );

//             print_info(curr_node);

//             // succesful split ( move left )
//             // curr_node = curr_node->left;

//             // * node->active_dptr_cstyle_t = curr_node;

//             q.push_back(curr_node);
            

//         } 

        
//     }

//     // clear stale/copied mem

//     // for (const auto n: trashmap) {
//     // }
 

//     // std::cout  << n_possible << " added to queue "<< "\n\n\n";

// }


// void init_sol(std::string s, std::string sgoal,  Qt &q) {

//     // loaded first node into q 

//     std::size_t * index_ptr = new std::size_t{0}; // const adress ( non-const value )

//     void ** const active_mem_addr_shared = (void ** const )malloc(sizeof( void *)) ; // allocate const 8 bytes  ( oouter ) 
    
//     TNode * tnode = new TNode{s, sgoal , nullptr, nullptr, nullptr, 0, nullptr, false, index_ptr, active_mem_addr_shared};

//     tnode->root = tnode;
    
//     *active_mem_addr_shared = tnode;

//     init_sol_extend(tnode, q); // loads queue 

// }


// void set_next_node(TNode *anchor_node) {
    
//     if (!anchor_node) {
//         return;
//     }

//     // anchor_node->staged = true;
//     *(anchor_node->index) = * (anchor_node->index ) + 1;

//     // update active node
//     while (anchor_node->prev) {
        
//         anchor_node = anchor_node->prev;

//         if (anchor_node->right && !anchor_node->right->staged) {

//             anchor_node = anchor_node->right;

//             anchor_node->staged = true; 

//             *anchor_node->active_dptr_cstyle_t = anchor_node;


//             // ((TNode *)*anchor_node->active_dptr_cstyle_t)->staged = true;

//             std::cout << "BOOM\t" << ((TNode*)(*anchor_node->active_dptr_cstyle_t) )->s << "\n";

//             break;
//         }
//     }

// }

// bool build_scramble_network(TNode *node, std::string sgoal, Qt &q) {

//     // std::cout << "ENTER STRING" << "\t" << node->s << "\n";
//     // std::cout << "ENTER GOAL" << "\t" << node->sgoal << "\n";


//     while (*node->index < sgoal.length()) {

//         char character = sgoal[ *node->index ];

//         std::cout << "character" << "\t" << character << "\n";

//         node->staged = true;

//         // make active node 
//         *node->active_dptr_cstyle_t = node; 

//         std::cout << "ACTIVE NODE" << "\t" << node->s << "\n";
//         std::cout << "ACTIVE NODE GOAL" << "\t" << node->sgoal << "\n";

//         print_info(node);


//         if (!node->s.contains(character)) {
//             // std::cout << "Error\t" << node->s << "\n";
//             clear_node(node);
//             return false;
//         } 

//         if (!node->left && !node->right) {  

//             // process leaf node

//             if (node->s.length() == 1) {

//                 set_next_node(node);

//                 node = (TNode*)(*node->active_dptr_cstyle_t);
                
//                 node->staged = true;

//             } else {
                
//                 std::string l, r;
                
//                 std::ptrdiff_t count = std::count(node->s.begin(), node->s.end(), character);

//                 if (node->s[0] == character && count == 1) {

//                     l = node->s.substr(0, 1);

//                     r = node->s.substr(1);

//                     split_node(node, l , r);

//                     node = node->left ;  // move left down 

//                     *node->active_dptr_cstyle_t = node; // update active 


                    
//                 } else if (node->s[node->s.length() - 1] == character && count == 1) {

//                     l = node->s.substr(0, node->s.length()-1);

//                     r = node->s.substr(node->s.length()-1);
                    
//                     split_node(node, l , r);

//                     swapT(node); 

//                     node = node->left; // move left down 
                    
//                     *node->active_dptr_cstyle_t = node; // update active 

//                 } else if (  node->s.contains(character)  ) {
                    
//                     // std::cout << "BRANCH NODE \t" << node->s << "\n";
//                     // std::cout << "BRANCH SGOAL \t" << node->sgoal << "\n";
//                     // std::cout << "BRANCH SGOAL \t" << ( (TNode *)(*node->active_dptr_cstyle_t))->sgoal << "\n";

//                     *node->active_dptr_cstyle_t = node;  // parent is active 

//                     init_sol_extend(node, q); 
                    

//                     clear_node(node);

//                     return false;

//                 } else {

//                     clear_node(node);

//                     return false; 
//                 }

//             }

//         }

            
//         else if (node->left  && node->left->s.contains(character)) {

//             node = node->left;
            
//             // *node->active_dptr_cstyle_t = node; 

//             // std::cout << "TARGET CHAR LEFT" << "\n";

//             // std::cout << "ENTER STRING" << "\t" << node->s << "\n";
            
//             // std::cout << "ENTER GOAL" << "\t" << node->sgoal << "\n";

//         }

//         else if (node->right  && node->right->s.contains(character)) {
            
//             // std::cout << "TARGET CHAR RIGHT " << "\n";

//             swapT(node);

//             // print_info(node);

//             node = node->left;
            
//             // std::cout << "TARGET CHAR LEFT " << "\n";

//             // *node->active_dptr_cstyle_t = node; 

//             // std::cout << "ENTER STRING" << "\t" << node->s << "\n";
            
//             // std::cout << "ENTER GOAL" << "\t" << node->sgoal << "\n";

//         }

//     }

//     return *node->index  >= sgoal.length();

// }






void copy_node_network_helper(Node * source, Node * dest) {

    if (source->left) {
        
        dest->left = new Node{source->left->s, source->left->sgoal, source->left->gold_sgoal, nullptr, nullptr, dest, dest->root, source->left->staged, dest->index , dest->active_dptr_cstyle_t};
        

        copy_node_network_helper(source->left, dest->left);

    }

    if (source->right) {
        
        dest->right = new Node{source->right->s, source->right->sgoal,  source->right->gold_sgoal, nullptr, nullptr, dest, dest->root, source->right->staged, dest->index, dest->active_dptr_cstyle_t};
        
        
        copy_node_network_helper(source->right, dest->right);

    }

    if (*source->active_dptr_cstyle_t  == source ) {

        // update destination active node

        *dest->active_dptr_cstyle_t = dest;

    }

}


Node * copy_root(Node *source) {

    // loaded first node into q 

    std::size_t  *  index_ptr = new std::size_t{*source->index}; // const adress ( non-const value )

    void ** const active_mem_addr_shared = (void ** const )malloc(sizeof( void *)) ; // allocate const 8 bytes  ( oouter ) 
    
    Node * node = new Node{source->root->s, source->root->sgoal, source->root->gold_sgoal, nullptr, nullptr, nullptr, nullptr, false, index_ptr,  active_mem_addr_shared};

    node->root = node;
    
    *active_mem_addr_shared = node;

    return  node;

}


void create_root(std::string s, std::string sgoal,  Q &q) {

    // loaded first node into q 

    std::size_t  *  index_ptr = new std::size_t{0}; // const adress ( non-const value )

    void ** const active_mem_addr_shared = (void ** const )malloc(sizeof( void *)) ; // allocate const 8 bytes  ( oouter ) 
    
    Node * node = new Node{s, sgoal, sgoal, nullptr, nullptr, nullptr, nullptr, false, index_ptr,  active_mem_addr_shared};

    node->root = node;
    
    *active_mem_addr_shared = node;

    q.push_back(node);

}


/*
    find possible sgoal prefix that matches to s
*/

std::vector< std::pair<int, std::string >>  largest_header_match(Node *node , Q &q) {
    
    std::vector< std::pair<int, std::string >> list;

    std::string s = node->s; 

    std::string sgoal = node->sgoal;

    std::cout << "SGOAL: " << sgoal << "\n";

    std::cout << "S: " << s << "\n\n";

    if (!histo_valid(s, sgoal)) {
        return list;
    }
    
    for (std::size_t i = 0; i < s.length(); i++) {

        std::string prefix_test =  sgoal.substr(0, sgoal.length() - 1 - i);

        auto found_index = s.find( prefix_test );

        // find largest substring at zero
        if (found_index !=-1) {

            if (prefix_test.length()) {
                list.push_back({found_index, prefix_test});

                // std::cout << " PREFIX TEST "  << found_index << "\t" << prefix_test << "\n";
            }

            // if (prefix_test.length() == 0)
            //     continue; 

            // if (map.count(found_index) == 0){
            //     map[found_index] = {};
            // }
            
            // map[found_index].push_back(prefix_test) ;

            // // if (map[found_index].size() == 0 ) {
                

                
            //     // finda largest prefix 
                // std::cout << " PREFIX TEST "  << found_index << "\t" << prefix_test << "\n";
            // }

        }
    }

    return list; 
}

void set_next_node(Node *anchor_node) {
    
    if (!anchor_node) {
        return;
    }

    *(anchor_node->index) = * (anchor_node->index ) + 1;
    std::cout << "PREV" << anchor_node->prev->prev <<  "\n";
    
    // print_node(anchor_node->prev);

    // update active node
    while (anchor_node->prev) {
        
        anchor_node = anchor_node->prev;

        if (anchor_node->right && !anchor_node->right->staged) {
            // if (anchor_node->right ) {

            anchor_node = anchor_node->right;

            *anchor_node->active_dptr_cstyle_t = anchor_node;

            anchor_node->staged = true; 

            ((Node *)*anchor_node->active_dptr_cstyle_t)->staged = true;

            // std::cout << "BOOM\t" << ((TNode *)*anchor_node->active_dptr_cstyle_t)-> s << "\n";

            // (*anchor_node->active_dptr_cstyle_t) = anchor_node; 
            
            std::cout << "BOOM\t" << ((Node*)(*anchor_node->active_dptr_cstyle_t) )->s << "\n";

            //  assign new active node  !

            // std::cout << "ANCHODR ADDRESS=ADDRESS+RECORD\t" << anchor_node->active_dptr_cstyle_t << "\n";
            // std::cout << "ANCHODR_RECORD\t" << anchor_node << "\n";
            // std::cout << "ANCHODR_RECORD\t" << *anchor_node->active_dptr_cstyle_t << "\n";

            break;
        }
    }

}


void leaf_left(Node *node , std::string s, std::size_t idx) {
    std::cout << "\t\t\t\t" << node << "\n";
    Node * child = new Node{s, node->sgoal.substr(0, idx), node->gold_sgoal, nullptr, nullptr, node, node->root, false, node->index,  node->active_dptr_cstyle_t};
    node->left = child;
}

void leaf_right(Node *node , std::string s, std::size_t idx) {
    std::cout << "\t\t\t\t" << node << "\n";
    Node * child = new Node{s, node->sgoal.substr(idx), node->gold_sgoal, nullptr, nullptr, node, node->root, false, node->index,  node->active_dptr_cstyle_t};
    node->right = child; 
}

bool anchored_leaf (Node *node) {
    
    std::cout << "anchor test NODE: " << node << "\n";

    // std::cout << node->s << "\n";
    // std::cout << node->gold_sgoal << "\n";
    // std::cout << *node->index << "\n";

    bool no_leaf = !node->left && !node->right ;
    bool match = (node->s.length() == 1)  &  ( (node->gold_sgoal[*node->index]) == (node->s[0]) ) ;

    return match && no_leaf;
}

void split_this(Node * node, int index, unsigned length) {

    std::string l, r;
    std::cout  << "NODE: -->  " << node << "\n SIGNAL: " << node->s << "\n SGOAL: " << node->sgoal << "\t \nINDEX " << index << "\t LENGTH " << length << "\n";


 if (index == 0) {

        l = node->s.substr(0, length);
        
        r = node->s.substr(length);

        // split  
        leaf_left(node, l, 1 );

        leaf_right(node, r , 1);

        // std::cout << "PARENT" << "\n";
        // print_node(node->prev);

        // std::cout << "CURRENT" << "\n";
        // print_node(node);

        node = node->left;
        
        *node->active_dptr_cstyle_t = node;
        
        std::cout << "CURRENT" << "\n";
        
    }

    else if (index == node->s.length() - 1) {
        
        // 
        l = node->s.substr(0, index);

        r = node->s.substr(index);
        
        // split 
        leaf_left(node, r, 1 );

        leaf_right(node, l , 1);

        print_node(node);

        node = node->left;

        *node->active_dptr_cstyle_t = node;

    }

    else if (index + length == node->s.length()) {

        l = node->s.substr(0, index);

        r = node->s.substr(index );

        leaf_left(node, r, index );

        leaf_right(node, l , index);

        node->left->sgoal = node->sgoal.substr(0, length);

        node->right->sgoal = node->sgoal.substr( length);

        node = node->left;
        
        *node->active_dptr_cstyle_t = node;
        
        print_node(node);

    } else {

        l = node->s.substr(0, index + length);

        r = node->s.substr(index + length);

        // std::cout << l << " " << r << "\n";

        leaf_left(node, l, index );

        leaf_right(node, r , index);

        node->left->sgoal = node->sgoal.substr(0, l.length());
        node->right->sgoal = node->sgoal.substr( l.length());

        node = node->left;

        *node->active_dptr_cstyle_t = node;

        print_node(node);

    }

}

bool solver(Node *node, Q &q) {
    

    Node * active_node = (Node *) (*node->active_dptr_cstyle_t);

    std::cout << "ROOT " << active_node->root <<  "\n";

    std::cout << "NODE  " << active_node->s << "\n";

    std::cout << "NODE GOAL  " << active_node->sgoal  << "\n";

    std::cout << "NODE INDEX  " << *active_node->index  << "\n";
    
    std::cout << "NODE STAGED  " << active_node->staged  << "\n";

    while (*active_node->index < active_node->gold_sgoal.length()) {

        active_node = (Node *) (*active_node->active_dptr_cstyle_t);

        active_node->staged = true;

        if (anchored_leaf(active_node)  ) {
            
            set_next_node(active_node);
            
            active_node = (Node *) (*active_node->active_dptr_cstyle_t);

            std::cout << active_node->s << " CURRENT NODE \n";

            // std::cout << " SET NEXT DONE  EVAL  \t\t" << "\n";

            // std::cout << ((Node *) active_node->prev) << " \t " << ((Node *) active_node->prev)->s << " PREV NODE \n";
            // std::cout << ((Node *) active_node->prev->prev)<< " \t " << ((Node *) active_node->prev->prev)->s << "  PREV PREV NODE \n";

            // if (active_node->s == std::string(1, 'c') ) {

            // }

            
            
            // std::cout << active_node->prev->prev->s << " DOO IT  ";

            // std::cout << active_node->prev->prev->prev->s << " DOO IT \n";


            // std::cout << " WHAT I: \t" <<  *(active_node->index)  << "\n";
            // std::cout << " WHAT I: \t" <<  active_node->gold_sgoal.length()  << "\n";

        }

        else {
            std::cout << "\n\nHEADER TEST \t\t" << "\n";

            std::vector< std::pair<int, std::string >>  pairs = largest_header_match(active_node, q);

            if (pairs.empty()) {
                // no match match 
                return false;
            }
            
            
            for (const auto s: pairs) {

                int this_index = s.first;
                std::string this_s = s.second;  

                // copy network 
                Node * new_node = copy_root(active_node);
                copy_node_network_helper(active_node->root, new_node->root);

                // copy network -- split active node 
                split_this(new_node, this_index, this_s.length());
                
                new_node = (Node *) (*new_node->active_dptr_cstyle_t);

                print_node(new_node->prev);
                std::cout << " --------- " << "\n";

                // push to queueu 
                q.push_back(new_node);
                
            }

            assert(0);
            
            return false;

        }
        
        
    }

    return true; 

}




class Solution {
public:
    bool isScramble(std::string s1, std::string s2) {
        // Q q;
        bool found_u = false;

        // Qt q;
        Q queue;

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

        // init_sol(s1, s2, q);

        create_root(s1, s2, queue);

        // init_sol_2(s1, s2, q);
        
        // std::cout << " --------INIT COMPLETE----------" << "\n";
        
        while (!queue.empty())  {
            
            // TNode *node = q.front();
            Node *node = queue.front();
            
            queue.pop_front(); 

            // std::cout << "\t\t\t ATTEMPT \t \n";
            
            // found_u = build_scramble_network(node, s2, q);
            found_u = solver(node, queue);

            if (found_u) {
                std::cout << "HELL GOT IT" << "\n";
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
            
            case(8):
                s1 = "abcdt";
                s2 = "tbdca";
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