#include "largestRectangleArea.h" 


int test_conv_str(long value){

    if ( (value == LONG_MAX || value == LONG_MIN) && errno == ERANGE  ) {
        return 1;
    
    } else {
        return 0;
    }

}

int test_digit_found(char *s, char *endptr) {

    if (s == endptr) {
        return 1;
    }
    
    return 0;
}


typedef struct Node_t {
     int position;
     int count;
     int value; 
     int locked;
    struct Node_t *next;
} Node_t;




void free_list(Node_t *node) {
    Node_t *next = NULL; 

    while (node) {
        
        next = node->next; 

        free(node); 

        node = next; 
    }

}

Node_t* create_node(int position, int value) {
    Node_t *node = malloc(sizeof(Node_t));
    node->position = position;
    node->count = 0; 
    node->value = value;
    node->locked = 0;
    node->next = NULL; 
    return node; 
}

void increment_each_node(Node_t *node, int value, int pos) {
    printf("print list\n");
    
    if (value == 0)
        return;

    while (node) {
        
        node->count++;

        // if (value >= node->value) {

        //     if (!node->locked) {


        //     } else {

        //     }

        // }

        //  if (value < node->value ) {
            
        //     if (!node->locked ) {

        //         node->locked = 1;
                
        //         node->count--;

        //     }

        //  }

        //  if (node->locked && pos > node->position ) {
        //         node->count--;
        //  }
        
        // if (value <= node->value && node->locked && pos >= node->position) {
        //     node->count++;
        // }

        
        node = node->next;


        // if (value < node->value && pos > node->position) {

        // } else if (!node->locked){
        // }
        // // if (value >= node->value) {
            // }
    }
}

void print_list (Node_t *node) {

    while (node) {
        printf(" (%d, %d,   locked:  %d  )  | ", node->value, node->count, node->locked);
        node = node->next; 
    }
}

void lock_nodes (Node_t *node) {
    while (node) {

        node->locked = 1;
        node = node->next; 
    }
}

void gt_rect(Node_t *node,  int  *  const mox_out_addr /* address is fixed */){
    
    int area = node->count * node->value; 

    if ( area > *mox_out_addr ) {
        *mox_out_addr = area; 
    }

}

void gt_rect_h(int height,  int  *  const mox_out_addr){
    if (height > *mox_out_addr) {
        *mox_out_addr = height;
    }
}

Node_t * get_node(Node_t *node, int value, int position) {
    while(node) {
        if (node->value == value && node->position == position) {
            return node;
        }
        node = node->next; 
    }
    return NULL;
}
void handle_neg_edge(Node_t *node, int curr, int prev) {
    
}

Node_t * insert_node(Node_t **head, int position,  int current_value, int previous_value, Node_t *prev_insert) {
    Node_t *node = *head; 
    Node_t *prev = NULL; 
    int update_list = 0;
    
    // printf("previous %d", previous_value);
    printf("\n\n\n CURRENT  %d    PREVIOUS %d  PREVIOUS COUNT %d \n\n", current_value, previous_value, (prev_insert != NULL) ?  prev_insert->count : -1);

    while (node) {  
        

        if (current_value > node->value) {
            node->count++;
        }

        else if (current_value == node->value) {

            if (previous_value == current_value) {
                node->count++;
            }

            else if (node->locked) {
                node->locked = 0;
                node->count = 1; 
            }

            else if (!node->locked) {
                node->count++; 
            }

            update_list = 1;

            return node; 
            break;

        }

        else if (current_value < node->value) {
        
            update_list = 1; 

            int position_prev = position - 1;

            Node_t *prev_height_node = get_node(*head, previous_value, position_prev);


            if ( (*head) == node ) {

                // new head 

                Node_t *new_node = create_node(position, current_value);
                new_node->count = node->count + 1;  // spread increases , like THE THINGS stretching 
                new_node->next = *head; 
                *head = new_node;
                // new_node->count++;
                new_node->count =  prev_insert->count + 1;

                // if ( (*head)->count > new_node->count ) {// } 

                handle_neg_edge(*head, current_value, previous_value);
                return new_node;
                break;

            }

            else {

                // insert front of node 
                Node_t *new_node = create_node(position, current_value);
                prev->next = new_node;
                prev->next->next = node; 
                new_node->count++;
                new_node->count = node->count + 1;

                // new_node->count++;
                new_node->count =  prev_insert->count + 1;
                
                handle_neg_edge(*head, current_value, previous_value);

                return new_node;

                break;
            }
        }

        prev = node; 
        node = node->next; 
    }
    
    // if (update_list == 0) {
        // new tail
    Node_t *new_node = create_node(position, current_value);
    prev->next = new_node;
    new_node->count++;
    return new_node;

    // }

    // print_list(*head);

    // return NULL;

}

int largestRectangleArea(int* heights, int heightsSize) {

    Node_t *head = NULL;    
    Node_t *node = NULL;    
    Node_t *prev = NULL;  
     Node_t *prev_return = NULL;  


    int value = 0; 
    int found = 0; 
    int max_out = 0;
    int prev_value; 
    int *prev_value_ptr; 

    for (int i = 0; i  < heightsSize; i++) {

        value = heights[i];

        // printf("\n\n\n NEW VALUE  %d   %p\n\n", value, head);

        // gt_rect_h(value, &max_out); // test immediate height 

        prev = NULL;
        node = head; 
        found = 0;

        if (value == 0) {
            
            // zero height

            free_list(node);
            head = NULL;
            node = NULL; 

            printf("\n\n\n BLACK HOLE REACHED \n\n");
        }

        else if (head == NULL) {
            head = create_node(i, value);
            head->count = 1;
            node = head; 
            prev = NULL; 

        } else {

            prev_value = heights[i-1];
            
            prev_return = insert_node(&head, i, value, prev_value, prev_return);
            
            print_list(head);


            // while (node) {
                
            //     if (value == node->value) {
                    
            //         if (i == node->position - 1) {

            //             // adjacent 
            //             node->count++;

            //         }

            //         else {

            //             if (node->locked) {
            //                 node->locked = 0;
            //             }

            //             node->count = 1;

            //         }

            //         // // immediate 
            //         // if (node == head) {

            //         // }

            //         // // ajacent clone
            //         // else if (prev) {

            //         // } 

            //         // // displaced clone 
            //         // else {

            //         // }
                    
            //         // if (node->locked) {
            //         //     node->locked = 0;
            //         //     node->count = 1;
            //         // }

            //         gt_rect(node, &max_out);

            //         found = -1;

            //     } else if (value < node->value) {

            //         Node_t *new_node = create_node(i, value);

            //         if (prev == NULL) {

            //             // insert header 
            //             new_node->count = head->count + 1;  // spread increases , like THE THINGS stretching 
            //             new_node->next = head; 
            //             head = new_node;
            //             gt_rect(head, &max_out);
            //             lock_nodes(head->next);
            //             found = -1;


            //         } else {
                        
            //             // insert front of node 

            //             prev->next = new_node;
            //             prev->next->next = node; 
            //             if (new_node->value == prev->value)
            //                 new_node->count = prev->count - 1 ;
            //             else 
            //                 new_node->count = 1;
            //             // locked node and after 
            //             lock_nodes(node);
            //             gt_rect(new_node, &max_out);

            //         }

            //         found = 1;  
            //         break;

            //     } else {

            //         // // width increase 

            //         if (!node->locked) {
            //             node->count++;
            //             gt_rect(node, &max_out);
            //         }

            //     }

            //     prev = node; 
            //     node = node->next; 

            // }

            // if (found == 0) {
                
            //     prev->next = create_node(i, value);
            //     prev->next->count += 1;
            //     gt_rect(prev->next, &max_out);

            // }
            
        }

        
    }
    print_list(head);
        
    // increment_each_node(head, value, i);
    // printf("\n");
    return max_out;
   
}