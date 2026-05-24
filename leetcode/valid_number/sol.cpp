/*

  Purpose: Solve 'hard' leetcode problem. 

  URL: https://leetcode.com/problems/valid-number/description/

  Author: HW
*/

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <algorithm>

 std::string vertex_names[7] {
    "sign_epsilon", 
    "digit_integer", 
    "dot",
    "digit_decimal",
    "sign",
    "digit_epsilon",
    "epsilon"
};
            
struct Node{
    std::string name;
    std::vector<Node*> children; 
};

/**
 * Adds vertex identified as name into current node's children list.
 * Adds recentlu added node into the queue 
 * 
 * @param parent_node Current node in network 
 * @param q Reference to caller's deque 
 * @param vertices List of linked or unlinked vertices 
 * @param vertices_used vertices add to the network
 * @param target_child_name Name of child node to add node's children list 
 */
void add_to_network(Node *parent_node, std::deque<Node * > &q,   std::map<std::string, Node*> vertices,  std::map <  Node* , void* >  &vertices_used, std::string target_child_name) {
    
    std::vector<Node*> p_children = parent_node->children; 
    
    auto child_exist {
        std::find_if(p_children.begin(), p_children.end(), [target_child_name](Node* p_child){
            return p_child->name == target_child_name;
        })
    };
    
    Node * new_child = vertices[target_child_name];
    if (child_exist == p_children.end()) {
        // child does not exist in parent; add child to parent
        parent_node->children.push_back(  new_child);
    } 
    
    if (vertices_used.count(new_child) == 0) {
        // add child to network to be extended  
        q.push_back(new_child);
        vertices_used[new_child] = nullptr;
    }

}

/**
*
* Test wheter character is a digit
* 
* @param c ASCII character
* @return True is character can be converts to digit; otherwise False 
* 
*/
bool digit_test( char c) {
    int num  = c - '0';
    return ( num >= 0  && num < 10) ;
}

class Solution {
    Node *root;
    std::map < std::string , Node*> vertices;
    std::map <  Node* , void* > vertices_used;

    void build_network() {
        
        if (root == nullptr) {
            root = vertices["sign"];
        }
        
        Node *node = root; 
        std::deque<Node *> q;
        q.push_back(root);
        
        while (!q.empty()) {
            node = q.front();
            q.pop_front();
            if (node->name == "sign") {
                add_to_network(node, q, vertices, vertices_used, "digit_integer");
                add_to_network(node, q, vertices, vertices_used,"dot");
                // add_to_network(node, q, vertices, vertices_used,"epsilon");

            } else if (node->name == "dot")  {
                add_to_network(node, q, vertices,vertices_used, "digit_decimal");
                add_to_network(node, q, vertices,vertices_used, "digit_decimal");

            } else if (node->name == "digit_integer") {
                add_to_network(node, q, vertices,vertices_used, "digit_integer");
                add_to_network(node, q, vertices, vertices_used, "dot");                
                add_to_network(node, q, vertices, vertices_used, "epsilon");                
            } else if (node->name == "epsilon") {
                add_to_network(node, q, vertices, vertices_used, "digit_epsilon");
                add_to_network(node, q, vertices, vertices_used, "sign_epsilon");
            } else if (node->name == "digit_epsilon") {
                add_to_network(node, q, vertices, vertices_used, "digit_epsilon");
            } else if (node->name == "sign_epsilon") {
                add_to_network(node, q, vertices, vertices_used, "digit_epsilon");
            } else if (node->name == "digit_decimal") {
                add_to_network(node, q, vertices, vertices_used, "digit_decimal");
                add_to_network(node, q, vertices, vertices_used, "epsilon");

            }
            
        }
        
    }
    

    bool find_s(std::string s)  {
        
        Node *node;
        std::deque < Node * > q;
        int watch_dog = 0;
        std::string acc; 
        std::string s_in = s;

        if (!root)
            return false; 
        
        q.push_back(root);
        
        while (!q.empty()) {
            
            node = q.front();
            q.pop_front();
            
            // std::cout << node->name << "\t" << s  << "\n\n";
            
            if (s.length() == 0) {
                break;
            }
                
            std::string s_gold = s; 
            
            if (node->name == "sign") {
                
                if (s[0] == '-' || s[0] == '+' ) {
                    char c = s[0];
                    s = s.substr(1, s.length());
                    if (s.length() == 0) {
                        // number is single sign character
                        break;
                    }
                    acc +=c;
                } else {
                    s_gold += '.'; // required to prevent break below after if-else block
                }
            } else if (node->name == "dot") {
                if (s[0] == '.') {
                    char c = s[0];
                    
                    // before pluck
                    if (s.length() == 1) {
                        // single character in buffer 
                        if (acc.length() == 0) {
                            // no values accumulated
                            break;
                        } else if(!digit_test(acc[acc.length() - 1])) {
                            // previous character was not a digit
                            break;
                        }
                    }

                    s = s.substr( 1, s.length() );
                    
                    acc +=c;
                } 
            } else if (node->name == "digit_integer") {
                if (digit_test(s[0])) {
                    acc +=s[0];
                    // is integer
                    s = s.substr( 1, s.length() );
                }
            } else if (node->name == "digit_decimal") {
                if (digit_test(s[0])) {
                    // is integer (after decimal)
                    acc +=s[0];
                    s = s.substr( 1, s.length() );
                }
            } else if (node->name == "epsilon") {
                if (s[0] == 'E' || s[0] == 'e' ) {
                    char c = s[0]; 
                    if (acc.length() == 0) {
                        // no proceeding digits before e
                        break;
                    } else if( acc[acc.length() - 1] == '.'  ) { 
                        // dot preceding e is okay
                        if (acc.length() == 1) {
                            // ".e" is invalid
                            break;
                        } else if (acc.length() > 1 ) {
                            if (acc[acc.length() - 2] == '-' || acc[acc.length() - 2] == '+') {
                                // "-.e" is invalid
                                // "+.e" is invalid
                                break;
                            } else if (digit_test(acc[acc.length() - 2])) {
                                // character before . is an integer (good do nothing)
                                // "6.e" is valid
                            }
                     
                        }
                    } else if( (!digit_test(acc[acc.length() - 1]))   ) { 
                        // procedding value is not a digit 
                        break;
                    }
                    
                    s = s.substr( 1, s.length() );
                    if (s.length() == 0) {
                        // no digits past e - empty exponent
                        break;
                    }
                    acc +=c;
                }
                
            } else if (node->name == "sign_epsilon") {
                if (s[0] == '-' || s[0] == '+' ) {
                    char c = s[0];
                    if (acc.length() == 0) {
                        // not possible
                        break;
                    } else if ( ! (acc[acc.length() - 1] == 'e'  || acc[acc.length() - 1] == 'E') ) {
                        break;
                    }

                    s = s.substr( 1, s.length() );

                    if (s.length() == 0) {
                        // digits are needed after signed epsilon
                        break;
                    }
                    acc +=c;
                }     
            } else if (node->name == "digit_epsilon") {

                if (digit_test(s[0])) {
                    acc +=s[0];
                    s = s.substr( 1, s.length() );
                } 
                
            }
            
            if (s_gold != s) {
                q.clear();
                watch_dog = 0;
            } else {
                watch_dog+=1;
                if (watch_dog>= 20) {
                    break;
                }
            }
            
            for ( Node* child_node: node->children) {
                q.push_back( child_node );
            }
            
        }
        
        return acc ==s_in  ;
        
    }

public:
    Solution() {
        root = nullptr; 
        for ( std::string name: vertex_names) {
            vertices[ name ] = new Node{name, {}};
        }
        build_network();
    }
    
    
    bool isNumber(std::string  s) {
        return find_s(s);
    }
};


int main() {
    Solution sol = Solution();
    std::string test_string = "-.E3";
    // std::string test_string = ".";
    bool ret = sol.isNumber(test_string);
    std::cout << test_string<< " is a valid number? " << ret << "\n";
    return ret;
}
