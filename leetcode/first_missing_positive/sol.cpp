/*

  Purpose: Solve leetcode First Missing Positive problem

  Author: HW 
  
  Url: https://leetcode.com/problems/first-missing-positive/description/

*/


#include <iostream>
#include <map>
#include <deque>

struct Node {
    long value;
    Node *next;
    Node *prev;
};

using Vertices = std::map<long, Node*>;

class Solution {
public:
    int firstMissingPositive(std::vector<int>& nums) {
        Vertices vertices;
        long k = 1;
        Node *head;
        Node *tail;
        Node *curr;
        Node *prev;
        Node *next;
        
        for(const int num_int: nums) {
            
            long num = static_cast<long>(num_int);
            
            if (num <=0 || vertices.count(num) !=0) {
                // not non positive
                continue;
            }
            
            vertices[num] = new Node{num, nullptr, nullptr};
          
            curr = vertices[num];
            
            if (vertices.count(num + 1)  &&  vertices.count(num - 1) ) {
                // inner connection 
                next = vertices[num + 1];
                prev = vertices[num - 1];
                curr->next = next;
                curr->prev = prev; 
    

                if (prev->prev == nullptr && next->next == nullptr) {
                    
                    head = prev;
                    tail = next;
                    
                    prev->next = curr;
                    next->prev = curr;
                
                    prev->prev = tail;
                    next->next = head;
                        
                } else if (prev->prev != nullptr && next->next == nullptr) {
                    
                    head = prev->next;
                    tail = next;
                    
                    prev->next = curr;
                    next->prev = curr;
                    
                    tail->next = head;
                    head->prev = tail;
                    
                } else if (prev->prev == nullptr && next->next) {
                        
                    head = prev;
                    tail = next->prev;
                    
                    prev->next = curr;
                    next->prev = curr;
                    
                    tail->next = head;
                    head->prev = tail;
                    
                } else /*prev->prev && next->next*/ {
                    head = prev->next;
                    tail = next->prev;
                    
                    prev->next = curr;
                    next->prev = curr;  
                    
                    head->prev = tail;
                    tail->next = head;
                    
                }
                
            } else if ( vertices.count(num + 1) ) {
                
                // tail
                next = vertices[num + 1];
                
                if (next->next == nullptr ) {
                    // single element     
                    curr->next = next;
                    next->prev = curr;
                    curr->prev = next;
                    next->next = curr;
                } else {
                    head = curr;
                    tail = next->prev;
                    curr->next = next;
                    next->prev = curr;
                    tail->next = head;
                    head->prev = tail;
                }
                
            } else if (vertices.count(num - 1)) {
                
                prev = vertices[num - 1];
                
                if ( (prev->prev == nullptr) &&  (prev->next == nullptr) )  {                    
                    // single element
                    curr->prev = prev;
                    prev->next = curr;
                    prev->prev = curr /*tail*/;
                    curr->next = prev /*head*/;
                } else {
                    // prev-prev is the end of a chain 
                    head = prev->next;
                    tail = curr;
                    curr->prev = prev;
                    prev->next = curr;
                    head->prev = tail;
                    tail->next = head;
                    
                } 
                
            }
                
        }
        
        
        Node * eval_node = vertices[1];
        
        if (!eval_node)  {
            // value of one never captured
            return 1;
            
        } else if (!eval_node->prev) {
            // value of one captured with no ajacent numbers 
            return static_cast<int>(eval_node->value)+ 1;

        } else {
            // value of one captured with adjacent numbers 
            return static_cast<int>(eval_node->prev->value ) + 1;
        }
        
    }
};



