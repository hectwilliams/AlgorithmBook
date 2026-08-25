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

#define COMMENTS_OFF 0

struct TNode;
struct Node;

using Qt = std::deque<TNode*>;
using Q = std::deque<Node*>;

using Store = std::array< TNode* , 1> ;
using ActiveTable = std::map<TNode*, Store >;
using UsedTable  = std::map<std::string, void*>;

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
    std::size_t depth;
    std:: string *s_accum;
    std:: string path;

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

}


void print_node(Node *parent) {

    // std::cout << " PRINT INFO: " << "\n";

    // std::cout << "\tparent:\t" << parent->s << "\n";
    
    if (parent->left && parent->right) {
        //  
            #if COMMENTS_OFF

        std::cout << "\t\t" << parent->left->s << " ( " << parent->left->sgoal  << " ) " << "\t" << parent->right->s << " ( " << parent->right->sgoal  << " ) "<< "\n";
    #endif 

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

// void split_node(TNode *parent, std::string sleft, std::string sright) {

//     parent->left = new TNode{sleft,  parent->sgoal.substr(0, sleft.length()), nullptr /* left ptr */, nullptr /* right ptr */, parent, parent->depth + 1, parent->root, false, parent->index, parent->active_dptr_cstyle_t };

//     parent->right = new TNode{sright, parent->sgoal.substr(sleft.length()), nullptr, nullptr, parent, parent->depth + 1, parent->root, false, parent->index,  parent->active_dptr_cstyle_t};

// }

void clear_node(TNode *node) {
    *node->active_dptr_cstyle_t = nullptr;
    std::free(node->active_dptr_cstyle_t); // free double pointer 
    delete node->index;

    delete node; 
}


void copy_node_network_helper(Node * source, Node * dest) {

    if (source->left) {
        
        dest->left = new Node{source->left->s, source->left->sgoal, source->left->gold_sgoal, nullptr, nullptr, dest, dest->root, source->left->staged, dest->index , dest->active_dptr_cstyle_t, source->depth, dest->s_accum, source->left->path};
        
        copy_node_network_helper(source->left, dest->left);

    }

    if (source->right) {
        
        dest->right = new Node{source->right->s, source->right->sgoal,  source->right->gold_sgoal, nullptr, nullptr, dest, dest->root, source->right->staged, dest->index, dest->active_dptr_cstyle_t, source->depth, dest->s_accum, source->right->path};
        
        
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
    std::string  *  s_accum = new std::string{*source->s_accum}; // const adress ( non-const value )

    void ** const active_mem_addr_shared = (void ** const )malloc(sizeof( void *)) ; // allocate const 8 bytes  ( oouter ) 
    
    Node * node = new Node{source->root->s, source->root->sgoal, source->root->gold_sgoal, nullptr, nullptr, nullptr, nullptr, false, index_ptr,  active_mem_addr_shared, 0, s_accum , "root-"};

    node->root = node;
    
    *active_mem_addr_shared = node;

    return  node;

}


void create_root(std::string s, std::string sgoal,  Q &q) {

    // loaded first node into q 

    std::size_t  *  index_ptr = new std::size_t{0}; // const adress ( non-const value )
    std::string  *  s_accum = new std::string{}; // const adress ( non-const value )

    void ** const active_mem_addr_shared = (void ** const )malloc(sizeof( void *)) ; // allocate const 8 bytes  ( oouter ) 
    
    Node * node = new Node{s, sgoal, sgoal, nullptr, nullptr, nullptr, nullptr, false, index_ptr,  active_mem_addr_shared, 0, s_accum ,  "root-"};

    node->root = node;
    
    *active_mem_addr_shared = node;

    q.push_back(node);

}

/*
    find possible sgoal prefix that matches to s
*/

std::vector< std::pair<int, std::string >>  largest_header_match(Node *node , Q &q) {
    
    std::vector< std::pair<int, std::string >> list;
    std::vector< std::pair<int, std::string >> list2;
    std::string s = node->s; 
    std::string sgoal = node->sgoal;
    std::map< int, std::vector<std::pair<int, std::string >>  > map;

    if (!histo_valid(s, sgoal)) {
        return list;
    }

    if (node->s.length() == 1) {

        list2.push_back({0, node->s});
        return list2;
    }



    for (std::size_t i = 1; i < s.length(); i++) {

        int start = 0;

        int end = sgoal.length() - i;
        
        std::string sgoal_prefix_test =  sgoal.substr(start, i);

    #if COMMENTS_OFF

        std::cout << "Y_ygoal:\t" << sgoal_prefix_test << "\tY-LENGTH:\t" << sgoal_prefix_test.length() << "\n";
    #endif 

        // convolve 

        for (std::size_t j = 0; j < s.length(); j++) {

            std::string x = s.substr( j,  sgoal_prefix_test.length());

            if (histo_valid(x, sgoal_prefix_test)) {

                list.push_back({j, sgoal_prefix_test});

                // std::cout << "X_s:\t"<< x << "\n";
            }

        }

    }

    // assert(0);
    
    return list;

  
}

void set_next_node(Node *anchor_node) {
    std::string s = anchor_node->s;
    
    if (!anchor_node || anchor_node == anchor_node->root) {
        return;
    }
    
    // *(anchor_node->index) = * (anchor_node->index ) + 1;

    if (  *anchor_node->s_accum + anchor_node->s == anchor_node->gold_sgoal) {

            *anchor_node->s_accum =  *anchor_node->s_accum + s; 

            *anchor_node->active_dptr_cstyle_t = anchor_node->root;


        return;
    }
    
    // std::cout << "PREV" << anchor_node->prev->prev <<  "\n";
    // print_node(anchor_node->prev);

    // update active node
    while (anchor_node->prev) {
        
        anchor_node = anchor_node->prev;

        if (anchor_node->right && !anchor_node->right->staged) {

            *anchor_node->s_accum =  *anchor_node->s_accum + s; 
            
            #if COMMENTS_OFF

                std::cout << " ANCHORED " <<  *anchor_node->s_accum << "\n";

            #endif 

            anchor_node = anchor_node->right;

            *anchor_node->active_dptr_cstyle_t = anchor_node;

            anchor_node->staged = true; 

            ((Node *)*anchor_node->active_dptr_cstyle_t)->staged = true;

            break;
        }
    }

}

void leaf_left(Node *node , std::string s, std::size_t len_or_index) {
    // std::cout << "\t\t\t\t" << node << "\n";
    Node * child = new Node{s, node->sgoal.substr(0, len_or_index), node->gold_sgoal, nullptr, nullptr, node, node->root, false, node->index,  node->active_dptr_cstyle_t, node->depth + 1, node->s_accum, node->path + 'l'};
    node->left = child;
}

void leaf_right(Node *node , std::string s, std::size_t len_or_index) {
    // std::cout << "\t\t\t\t" << node << "\n";
    Node * child = new Node{s, node->sgoal.substr(len_or_index), node->gold_sgoal, nullptr, nullptr, node, node->root, false, node->index,  node->active_dptr_cstyle_t , node->depth + 1, node->s_accum,  node->path + 'r'};
    node->right = child; 
}

bool anchored_leaf (Node *node) {
    
    #if COMMENTS_OFF
    
        std::cout << "anchor test NODE: " << node << "\n";
        std::cout << "anchor test NODE GOAL-FULL: " << node->gold_sgoal << "\n";
        std::cout << "anchor test NODE: " << node->s << "\n";
        std::cout << "anchor test NODE SGOAL: " << node->sgoal << "\n";
            std::cout << "anchor test ACC: " << *node->s_accum << "\n";

    #endif 

    bool is_leaf = !node->left && !node->right ;
    bool is_match = node->s == node->sgoal ;

    return is_leaf && is_match;
}

Node *clone_network (Node *active_node) {

     Node * new_node = copy_root(active_node); // init new node to root 
        
    copy_node_network_helper(active_node->root, new_node->root);

    new_node = (Node *) (*new_node->active_dptr_cstyle_t); // update new_node 

    return new_node;
} 

bool split_this(Node * node, int index, unsigned length) {

    std::string l, r;

    #if COMMENTS_OFF
        std::cout  << "NODE: -->  " << node << "\n SIGNAL: " << node->s << "\n SGOAL: " << node->sgoal << "\t \nINDEX " << index << "\t\n LENGTH " << length <<  " ACCUM " << *node->s_accum << "\n";
    #endif 


    if (index == 0) {

        #if COMMENTS_OFF
            std::cout << " MODE 0" << "\n"; 
        #endif 

        if (index + length == node->s.length()) {
            std::cout << index << "\n";


            l = node->s.substr(0, length);
            
            r = node->s.substr(length);
        
            // split  
            leaf_left(node, l, length );
        
            leaf_right(node, r , length);

              node = node->left;
            
            *node->active_dptr_cstyle_t = node;
            if ( ( histo_valid(node->prev->left->s, node->prev->left->sgoal) && histo_valid(node->prev->right->s, node->prev->right->sgoal) )  ) {
                return true;
            }
        


            return false; 


        } else {

            l = node->s.substr(0, length);
            
            r = node->s.substr(length);
        
            // split  
            leaf_left(node, l, length );
        
            leaf_right(node, r , length);
        
        
            // std::cout << "PARENT" << "\n";
            // print_node(node->prev);
        
            // std::cout << "CURRENT" << "\n";
            // print_node(node);

            #if COMMENTS_OFF

                if (node->prev) {

                    std::cout <<"PARENT\t" << node->s << "\n";
                    std::cout <<"PAREN GT\t" << node->sgoal << "\n";

                }

                std::cout <<"LEFT" << node->left << "\n";
                std::cout <<"RIGHT" << node->right << "\n";
            
            
                std::cout <<"RIGHT: " << node->right->s << "\n";
                std::cout <<"RIGHT: " << node->right->sgoal << "\n";
            
                std::cout <<"LEFT: " << node->left->s << "\n";
                std::cout <<"LEFT: " << node->left->sgoal << "\n";
            
            #endif 
        
        
            node = node->left;
            
            *node->active_dptr_cstyle_t = node;
            if ( ( histo_valid(node->prev->left->s, node->prev->left->sgoal) && histo_valid(node->prev->right->s, node->prev->right->sgoal) )  ) {
                return true;
            }
        
                        assert(0);

            return false;        
        }

    }

    else if (index == node->s.length() - 1) {
        #if COMMENTS_OFF
            std::cout << " MODE 1\n" << "\n"; 
        #endif 

        
        l = node->s.substr(0, index); // index = number of samples 

        r = node->s.substr(index);
        
        // split 
        leaf_left(node, r, 1 );

        leaf_right(node, l , 1);

        // print_node(node);
            #if COMMENTS_OFF

        std::cout <<"LEFT: " << node->left << "\n";
        std::cout <<"RIGHT: " << node->right << "\n";

        std::cout <<"RIGHT: " << node->right->s << "\n";
        std::cout <<"RIGHT: " << node->right->sgoal << "\n";

        std::cout <<"LEFT: " << node->left->s << "\n";
        std::cout <<"LEFT: " << node->left->sgoal << "\n";
            #endif 

        node = node->left;

        *node->active_dptr_cstyle_t = node;

        if ( ( histo_valid(node->prev->left->s, node->prev->left->sgoal) && histo_valid(node->prev->right->s, node->prev->right->sgoal) )  ) {
            return true;
        }

        
        return false;        

    }

    else if (index + length == node->s.length()) {
        #if COMMENTS_OFF

            std::cout << " MODE 2" << "\n"; 

        #endif 

        l = node->s.substr(0, index);  // index = number of samples 

        r = node->s.substr(index );

        leaf_left(node, r, index );

        leaf_right(node, l , index);

        node->left->sgoal = node->sgoal.substr(0, length);
        node->right->sgoal = node->sgoal.substr( length);

                    #if COMMENTS_OFF

        std::cout <<"LEFT" << node->left << "\n";
        std::cout <<"RIGHT" << node->right << "\n";
            #endif 

        node = node->left;
        
        *node->active_dptr_cstyle_t = node;

         if ( ( histo_valid(node->prev->left->s, node->prev->left->sgoal) && histo_valid(node->prev->right->s, node->prev->right->sgoal) )  ) {
            return true;
        }

        return false;

    } else {
                                    #if COMMENTS_OFF
        std::cout << " MODE 3" << "\n"; 
                    #endif 

        l = node->s.substr(0, index + length);
        
        r = node->s.substr(index + length);
        
        // std::cout << " INDEX " << index << " " << length << "\n"; 
        // std::cout << " INDEX " << l << " " << r << "\n"; 

        leaf_left(node, l, index + length );  // index = number of samples 

        leaf_right(node, r , index + length);

        node->left->sgoal = node->sgoal.substr(0, l.length());
        node->right->sgoal = node->sgoal.substr( l.length());

                            #if COMMENTS_OFF

        std::cout <<"LEFT: " << node->left << "\n";
        std::cout <<"RIGHT: \t" << node->right << "\n";
        std::cout <<"LEFT: \t" << node->left->s << "\n";
        std::cout <<"RIGHT: \t" << node->right->s << "\n";
        std::cout <<"LEFT: \t" << node->left->sgoal << "\n";
        std::cout <<"RIGHT: \t" << node->right->sgoal << "\n";

                            #endif 

        node = node->left;

        *node->active_dptr_cstyle_t = node;

    #if COMMENTS_OFF

        print_node(node->prev);

    #endif 

        if ( ( histo_valid(node->prev->left->s, node->prev->left->sgoal) && histo_valid(node->prev->right->s, node->prev->right->sgoal) )  ) {
            return true;
        }
        

        return false;

    }

    return false;

}

bool solver(Node *node, Q &q) {
    

    Node * active_node = (Node *) (*node->active_dptr_cstyle_t);
    
    active_node->staged = true;

                                #if COMMENTS_OFF

    std::cout << "ROOT " << active_node->root <<  "\n";

    if (active_node->prev)
        std::cout << "PARENT " << active_node->prev->s <<  "\n";
    else 
        std::cout << "PARENT " << "NULL" <<  "\n";

    std::cout << "NODE  " << active_node->s << "\n";

    std::cout << "NODE GOAL  " << active_node->sgoal  << "\n";

    std::cout << "NODE INDEX  " << *active_node->index  << "\n";
    
    std::cout << "NODE STAGED  " << active_node->staged  << "\n";

    std::cout << "NODE DEPTH  " << active_node->depth  << "\n";
    std::cout << "NODE ACCUM   " << *active_node->s_accum  << "\n";
    #endif 

    std::vector< std::pair<int, std::string >>  pairs = largest_header_match(active_node, q);
    
    if (pairs.empty()) {
        // no match match 
        // std::cout << "\t\t\t\t\t\t\t\tFAILURED \n"  << "\n";
        return false;
    }
    
    for (const auto s: pairs) {
        
        int this_index = s.first;
        
        std::string this_s = s.second;  

        // std::cout << active_node->s << " @  \t INDEX: " << this_index  << "\t SUBSTR: " << this_s <<  "  \t " << "\n";
        
        active_node->staged = true;

        // copy network 
        // Node * new_node = copy_root(active_node); // init new node to root 
        
        // copy_node_network_helper(active_node->root, new_node->root);

        // new_node = (Node *) (*new_node->active_dptr_cstyle_t); // update new_node 

         Node * new_node = clone_network(active_node);

        if (new_node->s.length() != 1) {

            bool response = split_this(new_node, this_index, this_s.length()); // split and move to leaf node
            
            if (!response) {
                continue; 
            }
            
        }
        
        new_node = (Node *) (*new_node->active_dptr_cstyle_t); // active node was updated 
                                        #if COMMENTS_OFF

        std::string tmp = new_node->s;
        std::cout <<  " " << new_node->depth << " "  << " --------- " << "\n";
        std::cout <<  " " << *new_node->s_accum << " "  << " --------- " << "\n";
            #endif 

        if (anchored_leaf(new_node)) {
            
            std::string tmp = new_node->s; 
            set_next_node(new_node);
            
            new_node = (Node *) (*new_node->active_dptr_cstyle_t); // active node was updated 
            
            if (new_node == new_node->root) {
                return true; 
            }

            
            // if (tmp == "d") {
            //     print_node(new_node);
            //     print_node(new_node->prev);
    
            //     assert(0);
            // }
                                                #if 1

            print_node(new_node->prev);
                                    #endif 

            // std::cout << "INTO QUEUE" <<  " \t\t " << new_node->s  << new_node->sgoal  << "\n";
        }

        // push to queueu 
        q.push_back(new_node);
        
    }

    return false; 
    
}




class Solution {
public:
    bool isScramble(std::string s1, std::string s2) {
        // Q q;
        // Qt q;
        bool found_u = false;
        Q queue;
        UsedTable usedTable;

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

            if (usedTable.count(node->s + node->path) == 0) {

                usedTable[node->s + node->path] = nullptr;

                    found_u = solver(node, queue);
                    
                    if (found_u) {
                        return true;
                    }
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
                s1 = "abcd";
                s2 = "acbd";
                break; 

            case(9):
                s1 = "abcd";
                s2 = "bdca";
                break; 

            default: 
                break;
        
        }

        result = sol.isScramble(s1, s2);

     } catch (const std::runtime_error & e) {

        std::cout << " RUNTIME ERROR "<< e.what() << "\n" ;

    }

    std::cout << " scrambled_word: " << (result == 1 ? "yes": " no") << "\n";
}