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
     int repeat;
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
    node->repeat = 0;
    return node; 
}

void increment_each_node(Node_t *node, int value, int pos) {
    printf("print list\n");
    
    if (value == 0)
        return;

    while (node) {
        
        node->count++;

        node = node->next;

    }
}

void print_list (Node_t *node) {

    while (node) {
        printf(" (%d, %d,   locked:  %d , repeat: %d)  | ", node->value, node->count, node->locked, node->repeat);
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

void print_list_reverse(Node_t *node) {
    while (node) {
        printf("[-%d-]\n", node->value);
        node = node->prev_h;
    }
    printf("\n");
}
void hide_prev_value( Node_t *node, int target) {
    Node_t *head = node ;

    Node_t *a = NULL ;
    Node_t *prev_a = node ;
    Node_t *b = NULL ; 
    Node_t *source_back_link = node ;
    Node_t *dest_back_link = node ;

    int index = 0;
    int link_to_null = 0;
    
    printf("ENTERED   [%d] \n", node->value, node->position);

    while (node) {
        printf("search  [%d] \n", node->value, node->position);

        if (node->value == target) { 
    
            if (a == NULL) {
                a = node;
                b = a;
            } 
                
            printf("s found [%d]  [%d]  \n", node->value, node->position);

            b = node; 

        }

        if (!a) {
            prev_a = node; 
            source_back_link = node; 
        }
        node = node->prev_h; 
        index++;

    }
    
    printf(" a ENTRY VALUE    [%d]  POSITION  [%d]\n", head->value, head->position);
    // printf(" a   [%d]  [%d] \n", a->value, a->position);

   

  
    if (a) {

        printf("  START_LINK SOURCE   [%d]  [%d] \n", source_back_link->value, source_back_link->position);

        if (b->prev_h) {

            dest_back_link =  b->prev_h; 

            printf("END    [%d]  [%d] \n", dest_back_link->value, a->value);

        } else {

            printf("LINK TO NODE [%d]  \n", b->prev_h);
            
        }
    



         if (a == b) {
            
            // single occurence of value exists in list 
            
              if (a->prev_h == NULL) {
                    // effective header 
                    // // source_back_link->prev_h = NULL;
                    // printf("  EFFECT ROOT  \n");
                    // printf(" a ENTRY VALUE    [%d] \n", head->value, index);
                    // printf(" a NODE VALUE    [%d] \n", a->value, index);
                    // printf(" a NODE VALUE    [%d]  POSITITON  [%d] \n", a->value, a->position);
                    // printf(" a NODE VALUE    [%d]  POSITITON  [%d] \n", prev_a->value, prev_a->position);
                    prev_a->prev_h = NULL;
                    // print_list_reverse(head);

                } else {
                    // effective non-header 
                    source_back_link->prev_h = source_back_link->prev_h->prev_h;
                    // print_list_reverse(head);
                }
        
        } else {

            if (b->prev_h) {
                
                source_back_link->prev_h =  dest_back_link; 

            } else {
                
                printf(" a ENTRY VALUE    [%d] \n", head->value, index);

                source_back_link->prev_h = NULL ;

            }
            
        }
        
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

int look_back_v2(Node_t *node, int *heights) { 
    int counter = 0;
    int pos = node->position;

    while (heights[pos] >= node->value && pos >=0) {

        counter++;
        pos--;

        if (pos < 0)
            break;

    }

    return counter; 

}


Node_t * insert_node(Node_t **head, int position,  int current_value, int previous_value, Node_t *prev_insert, int *max_out_addr, int *heights ) {
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

                    node = node->next;

                }

                Node_t *next_node = node->next;
                Node_t *inner   = create_node(position, current_value);
                inner->repeat++;
                node->next = inner;
                inner->next = next_node;
                inner->prev_h = prev_insert;
                inner->count =   look_back_v2(inner, heights); //look_back(inner, inner->value); //node->count + 1;
                
                gt_rect(inner, max_out_addr);
                
                set_min( node, inner );

                return inner; 
            }

            else if (node->locked) {

                // unlock node 
                node->locked = 0;
                node->count = 1; 

                // node->prev_h->prev_h = NULL;
                //        if (position == 4) {
                    //     assert(0);
                    
                    // }
                    // if (prev_insert ) {
                        //     prev_insert->next = node; 
                        // }
                        if (position == 8) {
                            
                            print_list_reverse(prev_insert);
                            
                            print_list_reverse(node);
                            
                            printf(" a NEW VALUE  ==> [%d] \n", node->value);
                                                        printf(" a NEW PREV VALUE  ==> [%d] \n", node->prev_h->value);

                            printf(" a PREV VALUE  ==> [%d] \n", prev_insert->value);
                            
                            hide_prev_value(prev_insert, current_value);

                            
                            
                        }
                        print_list_reverse(prev_insert);

                        hide_prev_value(prev_insert, current_value);
                        
                        node->prev_h = prev_insert;
                        
                        print_list_reverse(node);

                         gt_rect(node, max_out_addr);
                
                        set_min( node, node->prev_h );



                        // print_list_reverse(prev_insert);
                    
                        // printf("AFTER [%d]\n", node->value); // entry  - 1 
                        // printf("ADTER [%d]\n", node->prev_h->value); // entry  - 1 

                        // assert(0);
                        // print_list_reverse(prev_insert);
                        // print_list_reverse(prev_insert);
                        
                        // printf("[%d]\n", prev_insert->value); // 6
                        // printf("[%d]\n", node->value); // 2  
                        // print_list(*head);
                    // printf("[%d]\n", prev_insert->value); // entry  - 1 
                    // printf("[%d]\n", prev_insert->prev_h->value); // entry  - 2
                    // printf("[%d]\n", prev_insert->prev_h->prev_h->value); // entry  - 3
                    // printf("[%d]\n", prev_insert->prev_h->prev_h->prev_h->value); // entry  - 3
                    
                    // }

                    
                    printf("\n\n\n\n");
                    // hide_prev_value(node, current_value);
                    
                    
                    //  node->count = look_back(node, current_value);

                
                    
                

            
            } else if (!node->locked) {
                // use ajacent height node stats 

                if ( node->value >= *node->min) {
                    node->count++;
                } else {
                    node->count =  1;
                }
                handle_neg_edge(node->next, current_value, previous_value);

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
                new_node->repeat++;

                new_node->count = node->count + 1;  // spread increases , like THE THINGS stretching 
                new_node->next = *head; 
                *head = new_node;
                (*head)->prev_h = prev_insert;
                // (*head)->prev_h = NULL;
             
                // (*head)->next->prev_h = prev_insert;

                if (prev_insert) {

                    //  Mutiple elements , new min depression in histogram 

                    if ( new_node->value >= *prev_insert->min) {
                        // node->count++;
                        // new_node->count =  prev_insert->count + 1;
                        new_node->count = look_back_v2(new_node, heights); // look_back(new_node, new_node->value);
                        // printf("new node \t %d", new_node->value);
                        // assert(0);
                    } else {

                        new_node->count = look_back_v2(new_node, heights); //look_back(new_node, new_node->value);

                    }

                    
                    int t = look_back_v2(new_node, heights);
                    t = new_node->count;
                    // print_list(*head);
                    
                    // assert(0);
                    // // look_back(new_node, new_node->value);
                    // if (position == 12) {}
                    

                } else {
                    
                    // single element prepended 

                    new_node->count = node->count + 1;
                    
                    // if (position == 12) {
                        
                    //     new_node->count = look_back_v2(new_node, heights); // 

                    //     assert(0);

                    // }

                    // new_node->count = look_back(new_node, new_node->value);

                    // if (new_node->value >= node->value) {
                    // } else {
                    //     new_node->count = node->count + 1;
                    // }


                }

                
                
                
                handle_neg_edge((*head)->next, current_value, previous_value);

                set_min((*head)->next , (*head));
                
                gt_rect(new_node, max_out_addr);
                
                    //  if (position == 3 ) {
                    //         print_list(*head);
                    //         assert(0);
                    //     }

                
             
                return new_node;
                break;

            }

            else {

                // insert front of node 
                Node_t *new_node = create_node(position, current_value);
                prev->next = new_node;
                prev->next->next = node; 
                new_node->repeat++;
                
                // head->prev_h = NULL;

                new_node->prev_h = prev_insert;

            

                // if ( node->value  <= prev_insert->value )  {
                
                    
                //     // new_node->count = prev_insert->count + 1;
                //     new_node->count = look_back(new_node, new_node->value);
                //     // new_node->count = node->count + 1;
                //     // if (position == 12)  {
                //     //     print_list(*head);
                //     //     assert(0);
                //     // }

                // } else {
                //     new_node->count = 1; 
                    
                // }
                
                // if ()
                new_node->count =  look_back_v2(new_node, heights); //look_back(new_node, new_node->value);
                
              

                // if (position == 12) {
                //     assert(0);
                // }

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
    // new_node->count++;

    new_node->count = look_back_v2(new_node, heights);
    
    if (!prev_insert) {
        new_node->prev_h = prev;
    } else {

        new_node->prev_h = prev_insert;
    }

    //    if (position == 3 ) {
    //             assert(0);
    //         }

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
            node->repeat = 0;

            prev = NULL; 
            prev_return = node;
            
        } else {
            
            prev_value = heights[i-1];

            prev_return = insert_node(&head, i, value, prev_value, prev_return, &max_out, heights);
            

            print_list(head);
        }

        
    }
    // increment_each_node(head, value, i);
    // printf("\n");
    return max_out;
   
}



