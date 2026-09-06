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


// // binary tree 
// typedef struct TNetwork {
//     int value;
//     struct TNetwork *prev;
//     struct TNetwork *left;
//     struct TNetwork *right;
//     int depth;
//     int is_root;
//     int root_count;
//     int right_count;
//     int left_count;
//     int *shared_counter;
//     int *shared_min_h;

// } TNetwork;

// typedef struct Data_t {
//     int min_bin;
//     int max_area;
//     int blocked;
// }Data_t;


// typedef struct Record_t {
//      TNetwork *network;
//     struct Record_t *next;
// } Record_t;



// void calculate_rectangle_eval(int area, Data_t *data) {
//     if  (area > data->max_area) {
//         data->max_area = area;
//     }
// }

// void calculate_rectangle (TNetwork *node, Data_t *data, int id) {
    
//     int area; 

//     // test bin 

//     if (node->value == 0) 
//         return;
    
//     //test bin 
//     calculate_rectangle_eval(node->value, data); 

//     // // find min bin 
//     if (node->value < data->min_bin) {
//         data->min_bin = node->value; 
//         printf("MIN BIN ( %d ) \t ID BIN ( %d )  \t VALUE ( %d )\t COUNTER ( %d ) \n",data->min_bin,  id, node->value, *node->shared_counter );
//     }

//     // lowest bin area 
//     area = *node->shared_min_h * *node->shared_counter;
//     calculate_rectangle_eval(area, data); 

//     printf("ENTER MIN BIN ( %d ) \t  MAX AREA ( %d ) \n",data->min_bin , data->max_area );

//     switch(id) {

//     case 0:
//         printf("\ncase 0\n");

//         // area = *node->shared_counter * node->value;
//         // calculate_rectangle_eval(area, data);
        
//         area = node->root_count * node->value;
//         printf(" SHARED COUNTER (%d) \t ROOT COUNT ( %d )\t VALUE (%d) \t AREA (%d) \n ", *node->shared_counter , node->root_count , node->value , area);
//         calculate_rectangle_eval(area, data);

//         break;

//     case 1:
//         printf("\ncase 1\n");

//         // left node  (decreasing ladder)

//         // area = *node->shared_counter * node->value;
//         // if (area > data->max_area) {
//             // data->max_area = area;
//         // }
//         calculate_rectangle_eval(area, data);

//         printf(" SHARED COUNTER ( %d )\t VALUE (%d) \t (%d) \n ", *node->shared_counter , node->value , area);
//         area = node->left_count * node->value;
        
//         printf(" LEFT COUNTER ( %d )\t VALUE (%d) \t (%d) \n ", node->left_count , node->value , area);

//         // if (area > data->max_area) {
//             // data->max_area = area;
//         // }
//         calculate_rectangle_eval(area, data);
//         break;

//     case 2:
//         printf("\ncase 2\n");

//         // right node  ( increasing ladder)
//         area = node->right_count * node->value;
//         //   if (area > data->max_area) {
//             // data->max_area = area;
//         // }
//         calculate_rectangle_eval(area, data);
//         break;

//     case 3:
//         printf("\ncase 3\n");

//         // right node  ( increasing ladder)
//         area = data->min_bin * *node->shared_counter;
//         calculate_rectangle_eval(area, data);
//         break;

        
//     default:
//         ;

//     }

//     printf("MIN BIN ( %d ) \t \n",data->min_bin );
//     printf("MAX AREA ( %d ) \t \n",data->max_area );

// }

// void reset_network(TNetwork *network ) {
   
//     network->value = 0;
//     network->is_root = 0;
//     network->left = NULL;
//     network->right = NULL;
//     network->prev = NULL;
//     network->depth = 0;
//     network->right_count = 0;
//     network->left_count = 0;
//     // network->shared_counter = malloc(sizeof(int));
//     // *network->shared_counter = 0; c

// }

// void reset_data (Data_t *node) {
//     printf(" RESET DATA \n");
//     node->min_bin = 10000000;
//     node->max_area = 0;
//     node->blocked = 1; 
    
// }

// Record_t * get_tail_record(Record_t *node) {
//     while (node->next) {
//         node = node->next;
//     }
//     return node; 
// }

// void init_shared(TNetwork *network) {

//   network->shared_counter = (int*)  malloc(sizeof(int));
//   *network->shared_counter  = 0 ;
//   network->shared_min_h = (int*)  malloc(sizeof(int));
//   *network->shared_min_h = -1;
  
// }

// void delete_network(TNetwork **network_addr) {
//     printf(" ------- deleted netowork -------\n");

//     TNetwork *node = *network_addr;
//     TNetwork *nodeHEAD = *network_addr;

//     Record_t *ll =  malloc(sizeof(Record_t));
//     ll->next = NULL; // init this 

//     Record_t *head = ll;
//     Record_t *eff_head = ll;

//     Record_t *tmp;

//     Record_t *ll_current_record = ll;
//     Record_t *ll_current_left ;
//     Record_t *ll_current_right;
//     Record_t *ll_current_walk;
//     Record_t *ll_tail_record;

//     ll->network = node; 
//     ll_current_walk = ll; 

//     printf(" network mailbox ( %p) \n", node);
//     printf(" network mailbox value ( %d) \n", node->value);
//     printf(" Record mailbox ( %p) \n", ll_current_walk);

//     while (ll_current_walk) {
        
//         if (ll_current_walk->network->left) {

//             ll_current_left = malloc(sizeof(Record_t));
//             ll_current_left->network = ll_current_walk->network->left; // store left node in new record 
//             ll_current_left->next = NULL;
            
//             ll_tail_record = get_tail_record(eff_head);
//             ll_tail_record->next = ll_current_left;

//             printf(" left record addr %p \n", ll_tail_record);
            
//         }
      
//         if (ll_current_walk->network->right) {
//             ll_current_right = malloc(sizeof(Record_t));
//             ll_current_right->network = ll_current_walk->network->right; // store left node in new record 
//             ll_current_right->next = NULL;
            
//             ll_tail_record = get_tail_record(eff_head);
//             ll_tail_record->next = ll_current_right;

//             printf(" right record addr %p \n", ll_tail_record);
            
//         }

//         tmp = ll_current_walk; // this record 


//         // next element in linked list 

//         if (ll_current_walk->next) {
            
//             // ELEMENTS AVAILABLE
            
//             ll_current_walk = ll_current_walk->next; // next record 
            
//             eff_head = ll_current_walk;
        
//         } else {

//             // END OF LIST 

//             ll_current_walk = ll_current_walk->next; // this is null! 

//         }

//         // record dumps 

//         if (tmp == head) {
//             free(tmp);
//         }
        
//         if (tmp != head)  {
//             free(tmp->network); // remove child nodes  (root network is NOT PERSISTENT)
//             free(tmp);
//         }
//     }


//     reset_network((*network_addr));

//     printf(" ------- deleted done -------\n\n\n");
    

// }


// void print_network(TNetwork *network) {

//     printf("print network\n");

//     TNetwork *node = network;
//     Record_t *ll = malloc(sizeof(Record_t));
//     Record_t *llwalk = ll;
//     Record_t *ll_node = ll;
//     Record_t *record_left = NULL;
//     Record_t *record_right = NULL ;
//     Record_t *lllegs = ll;
//     Record_t *tail_node;

//     ll->network = node; 
    
//     printf("print network\n");

//     while (llwalk) {
        
//         ll_node = llwalk;  //  current node/record
//         printf("print network - ( %d) \t (%d) \n",  llwalk->network->value, *llwalk->network->shared_counter);
        

//         if (ll_node->network->left) {
//             record_left = malloc(sizeof(Record_t));
//             record_left->network = ll_node->network->left; // store left node in new record 
//             record_left->next = NULL;
            
//             tail_node = get_tail_record(ll_node);
//             tail_node->next = record_left;
//         }

//         if (ll_node->network->right) {

//             record_right = malloc(sizeof(Record_t));
//             record_right->network = ll_node->network->right; // store right node in new record 
//             record_right->next = NULL;
            
//             tail_node = get_tail_record(ll_node);
//             tail_node->next = record_right; // add to list 
//         }
    

//         llwalk = llwalk->next;   // slow reads

//     }

//     printf("------- print network end-------\n");

// }

// void insert(int value, TNetwork *network, Data_t *data) {

//     TNetwork * node;
//     TNetwork * prev = network;

//     printf( "REGISTERED:(%d)\n\n" , value);

//     if (value == 0) {
            
//         if(*network->shared_counter ) {} // free(network->shared_counter);
        
//         return;
//     }

//     data->blocked = 0;
    
//     node = network; 

//     if(*network->shared_min_h  == -1    ) {
//         *network->shared_min_h = value;
//     } else if (*network->shared_min_h  > value) {
//         *network->shared_min_h = value;
//     }

//     while (node) {
        
//         if (node->value  == 0) {
//             // previous deleted network or first sample height; root node
            
//             node->value = value; 
//             node->prev = NULL;
//             node->left = NULL;
//             node->right = NULL;
//             node->left_count = 1;
//             node->right_count = 1;
//             node->depth = 0;
//             node->is_root = 1;
//             *node->shared_counter = *node->shared_counter + 1;
//             node->root_count = 1;
//             calculate_rectangle(node, data, 0);
//             node = NULL;  // stop 
//         }

//         else if (node->value == value) {

//             if (node->prev == NULL) {

//                 // consecutive root hit 

//                 node->root_count++;

//                 calculate_rectangle(node, data, 0);

//                 *node->shared_counter = *node->shared_counter + 1;
//             }

//             else if (node->prev) {
                
//                 // consecutive  right side leaf

//                 if (node->prev->right == node) {
//                     node->right_count+= 1;
//                     *node->shared_counter = *node->shared_counter + 1;

//                     calculate_rectangle(node, data, 2);
//                 } 
                
//                 // consecutive left side leaf 

//                 if (node->prev->left == node) {
//                     node->left_count += 1;
//                     *node->shared_counter = *node->shared_counter + 1;

//                     calculate_rectangle(node, data, 1);
                    
//                 }
                
//             }

//             node = NULL;  // stop 

//         } 
        
//         else if (value < node->value ) {
            
//             // left child traversal ( less than  )

//             prev = node; 

//             if (node->left) {
//                 printf("STEP LEFT\n");
//                 // calculate_rectangle(node, data, 1);
//                 node = node->left;
//             } else {
//                 node->left = malloc( sizeof( TNetwork) );
//                 node = node->left; 
//                 node->value = value;
//                 node->depth = prev->depth + 1;
//                 node->left_count = 1; 
//                 node->prev = prev;
//                 node->shared_counter = prev->shared_counter;
//                 *node->shared_counter =  *node->shared_counter + 1; 
//                 node->shared_min_h = prev->shared_min_h;
//                 node->left =  NULL;
//                 node->right = NULL;
//                 calculate_rectangle(node, data, 1);
//                 node = NULL;  // stop 
//                 // printf(" add value %d ON NODE %d\n ", value, prev->value);
//             }
//         } 
        
//         else { 

//             // right child traversal ( greather than  or equal )

//             printf("STEP RIGHT\n");

//             prev = node; 

//             node->right_count += 1;

//             calculate_rectangle(node, data, 2);

//             if (node->right) {

//                 node = node->right;

//             } else {
                
//                 node->right = malloc(sizeof(TNetwork));
//                 node = node->right;
//                 node->value = value;
//                 node->depth = prev->depth + 1;
//                 node->left_count = 1; 
//                 node->right_count = 1;
//                 node->prev = prev;
//                 node->shared_counter = prev->shared_counter;
//                 *node->shared_counter =  *node->shared_counter + 1; 
//                 node->shared_min_h = prev->shared_min_h;
//                 node->left =  NULL;
//                 node->right = NULL;
//                 // printf(" RIGHT SIDE count %d value %d \n" , node->right_count, node->value);
//                 calculate_rectangle(node, data, 2);
//                 node = NULL; 
//                 // printf(" RIGHT SIDE value %d ; RIGHT DEPTH %d :  COUNTER %d \n ", value, prev->right_count,  *node->shared_counter );
//             }

//         }

    
//     }

//     // printf("counter ", *node->shared_counter);

// }


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
        printf(" (%d, %d,   locked - %d  )  | ", node->value, node->count, node->locked);
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

int largestRectangleArea(int* heights, int heightsSize) {

    Node_t *head = NULL;    
    Node_t *node = NULL;    
    Node_t *prev = NULL;    

    int value = 0; 
    int found = 0; 
    int max_out = 0;

    for (int i = 0; i  < heightsSize; i++) {

        value = heights[i];
        printf("\n\n\n NEW VALUE  %d   %p\n\n", value, head);

        prev = NULL;
        node = head; 
        found = 0;

        if (value == 0) {
            
            // delete network 
            free_list(node);
            head = NULL;
            node = NULL; 
        }

        else if (head == NULL) {
            head = create_node(i, value);
            head->count = 1;
            node = head; 
            prev = NULL; 

        } else {

            // search 
            
            while (node) {

                if(value < node->value) {

                    Node_t *new_node = create_node(i, value);

                    if (prev == NULL) {

                        // new head 

                        new_node->next = head; 
                        head = new_node;
                        head->count = head->next->count + 1;  // spread increases , like THE THINGS stretching 
                        lock_nodes(head->next);
                        gt_rect(head, &max_out);

                    } else {
                        
                        // insert front of node 

                        prev->next = new_node;
                        prev->next->next = node; 
                        
                        new_node->count = prev->count - 1 ;

                        // locked node and after 
                        lock_nodes(node);
                        
                        gt_rect(new_node, &max_out);

                    }

                    found = 1;

                    break;

                } else {

                    if (node->value == value) {
                        printf("HELLO WORLD. %d  %d \n", node->value, value);
                    }



                    // width increase 

                    if (node->locked)
                        break;

                    node->count++;
                    gt_rect(node, &max_out);


                }

                prev = node; 
                node = node->next; 
            }

            if (found == 0) {
                prev->next = create_node(i, value);
                prev->next->count += 1;
                gt_rect(prev->next, &max_out);

            }
            
        }

        print_list(head);


    }
        
        // increment_each_node(head, value, i);
        
        // printf("\n");

    return max_out;
   
}