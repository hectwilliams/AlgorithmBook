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
     int *min; 
    struct Node_t *next;
    struct Node_t *prev;
    struct Node_t *prev_h;

} Node_t;




void free_list(Node_t *node) {

    Node_t *next = NULL; 

    if (node == NULL) {
        return; 

    } else {

        
        if (node->min) {
            free(node->min);            
        }
        
        while (node) {
            
            node->min = NULL;
            
            next = node->next; 
            
            free(node); 
            
            node = next; 
        }
        
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

    printf("\n\n\n");
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
    
    if (prev > curr) {

        while (node) {
            node->locked = 1; 
            node = node->next; 
        }
    
    }
}


void set_min(Node_t *source, Node_t *dest /* seeks input from source */) {

    if (!source || !dest)
        return;

    dest->min = source->min ; // add to share network
    if (dest->value < *source->min) {
        *source->min = dest->value; // shared update
    }
}

int look_back(Node_t *node, int baseline) {
    int counter = 0;
    while (node) {
        printf("[%d]\n", node->value);
        if (node->value >= baseline) {
            counter++;
        } else {
            break; 
        }
        node = node->prev_h;
    }
    return counter; 
}

Node_t * insert_node(Node_t **head, int position,  int current_value, int previous_value, Node_t *prev_insert, int *max_out_addr) {
    Node_t *node = *head; 
    Node_t *prev = NULL; 
    int update_list = 0;
    

    // printf("previous %d", previous_value);
    printf("\n\n\n CURRENT  %d    PREVIOUS %d  PREVIOUS COUNT %d \n\n", current_value, previous_value, (prev_insert != NULL) ?  prev_insert->count : -1);


    while (node) {  
        

        if (current_value > node->value) {
            if (!node->locked)
                node->count++;

            gt_rect(node, max_out_addr);

        }

        else if (current_value == node->value) {

            // move to last copy 

            
            if (previous_value == current_value) {
                

                while (node->next) {
                    if(node->next->value != current_value)
                        break;
                    // prev_insert = node; 
                    node = node->next;
                }


                Node_t *next_node = node->next;
                Node_t *inner   = create_node(position, current_value);
                node->next = inner;
                inner->next = next_node;
                inner->prev_h = prev_insert;
                inner->count =   look_back(inner, inner->value); //node->count + 1;
                
                gt_rect(inner, max_out_addr);
                
                set_min( node, inner );

                return inner; 
            }

            else if (node->locked) {
                // unlock node 
                node->locked = 0;
                node->count = 1; 
            
            } else if (!node->locked) {
                // use ajacent height node stats 
                if ( node->value >= *node->min) {
                    node->count++;

                } else {
                    node->count =  1;
                }

            }

            gt_rect(node, max_out_addr);


            update_list = 1;

            return node; 
            break;

        }

        else if (current_value < node->value) {
        
            update_list = 1; 

            // int position_prev = position - 1;

            // Node_t *prev_height_node = get_node(*head, previous_value, position_prev);

            if ( (*head) == node ) {

                // new head 
                Node_t *new_node = create_node(position, current_value);
                new_node->count = node->count + 1;  // spread increases , like THE THINGS stretching 
                new_node->next = *head; 
                *head = new_node;
                (*head)->prev_h = prev_insert;

             
                // (*head)->next->prev_h = prev_insert;

                if (prev_insert) {

                    //  Mutiple elements , new min depression in histogram 

                    if ( new_node->value >= *prev_insert->min) {
                        // node->count++;
                        new_node->count =  prev_insert->count + 1;
                        new_node->count = look_back(new_node, new_node->value);
                        // printf("new node \t %d", new_node->value);
                        // assert(0);


                    } else {
                        new_node->count = look_back(new_node, new_node->value);
                    }



                } else {
                    
                    // single element prepended 

                    new_node->count = node->count + 1;

                    // if (new_node->value >= node->value) {
                    // } else {
                    //     new_node->count = node->count + 1;
                    // }

                }


                handle_neg_edge((*head)->next, current_value, previous_value);

                set_min((*head)->next , (*head));

                gt_rect(new_node, max_out_addr);

                return new_node;
                break;

            }

            else {

                // insert front of node 
                Node_t *new_node = create_node(position, current_value);
                prev->next = new_node;
                prev->next->next = node; 
                
                // head->prev_h = NULL;

                new_node->prev_h = prev_insert;
             

                if ( node->value  <= prev_insert->value )  {

                    // new_node->count = prev_insert->count + 1;
                    new_node->count = look_back(new_node, new_node->value);
                    // new_node->count = node->count + 1;
                } else {
                    new_node->count = 1; 
                    
                }
                // new_node->count++;
                // new_node->count =  prev_insert->count + 1;
                
                handle_neg_edge( prev->next->next, current_value, previous_value);
                set_min( prev->next->next, new_node);
                gt_rect(new_node, max_out_addr);
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
    
    if (!prev_insert) {
        new_node->prev_h = prev;
    } else {

        new_node->prev_h = prev_insert;
    }

    set_min(prev, new_node);
    
    gt_rect(new_node, max_out_addr);

    return new_node;

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
    int mallocs = 0;

    for (int i = 0; i  < heightsSize; i++) {

        value = heights[i];

        gt_rect_h(value, &max_out); // test immediate height 

        prev = NULL;
        node = head; 
        found = 0;

        if (value == 0) {
            print_list(head);
            // zero height
            free_list(node);
            head = NULL;
            node = NULL; 
            prev_return = NULL;
            prev = NULL;
            printf("\n\n\n BLACK HOLE REACHED \n\n");
        }
        
        else if (head == NULL) {
            head = create_node(i, value);
            head->count = 1;
            head->min = malloc(sizeof(int));
            *head->min  = value;
            node = head; 
            node->prev_h = NULL;
            prev = NULL; 
            prev_return = node;
            
        } else {
            
            prev_value = heights[i-1];

            prev_return = insert_node(&head, i, value, prev_value, prev_return, &max_out);
            

            print_list(head);
        }

        
    }
    // increment_each_node(head, value, i);
    // printf("\n");
    return max_out;
   
}