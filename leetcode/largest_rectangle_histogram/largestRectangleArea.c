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


// binary tree 
typedef struct TNetwork {
    int value;
    struct TNetwork *prev;
    struct TNetwork *left;
    struct TNetwork *right;
    int depth;
    int is_root;
    int root_count;
    int right_count;
    int left_count;
    int *shared_counter;

} TNetwork;

typedef struct Data_t {
    int min_bin;
    int max_area;
}Data_t;


typedef struct Record_t {
     TNetwork *network;
    struct Record_t *next;
} Record_t;

void calculate_rectangle_eval(int area, Data_t *data) {
    if  (area > data->max_area) {
        data->max_area = area;
    }
}

void calculate_rectangle (TNetwork *node, Data_t *data, int id) {
    
    int area; 

    // test bin 

    if (node->value == 0) 
        return;
    
    if  (node->value > data->max_area) {
        data->max_area = node->value;
    }

    calculate_rectangle_eval(node->value, data); 

    // find min bin 
    if (node->value < data->min_bin) {
        data->min_bin = node->value; 
    }

    switch(id) {

    case 0:
        // root node (repeating adjacent bins)
        area = node->root_count *node->value;
        // if (area > data->max_area) {
        //     data->max_area = area;
        // }
        calculate_rectangle_eval(area, data);
        break;

    case 1:

        // left node  (decreasing ladder)

        area = *node->shared_counter * node->value;
        // if (area > data->max_area) {
            // data->max_area = area;
        // }
        calculate_rectangle_eval(area, data);

        area = node->left_count * node->value;
        // if (area > data->max_area) {
            // data->max_area = area;
        // }
        calculate_rectangle_eval(area, data);
        break;

    case 2:
        // right node  ( increasing ladder)
        area = node->right_count * node->value;
        //   if (area > data->max_area) {
            // data->max_area = area;
        // }
        calculate_rectangle_eval(area, data);
        break;

    default:
        ;

    }
}

void reset_network(TNetwork *network ) {
   
    network->value = 0;
    network->is_root = 0;
    network->left = NULL;
    network->right = NULL;
    network->prev = NULL;
    network->depth = 0;
    network->right_count = 0;
    network->left_count = 0;

   
    // network->shared_counter = malloc(sizeof(int));
    *network->shared_counter = 0; 

}

void reset_data (Data_t *node) {
    printf("RESET\n");
    node->min_bin = 10000000;
    node->max_area = 0;
    
}

Record_t * get_tail_record(Record_t *node) {
    while (node->next) {
        node = node->next;
    }
    return node; 
}

void init_shared(TNetwork *network) {

  network->shared_counter =  malloc(sizeof(int));

}

void delete_network(TNetwork **network_addr) {
    printf(" ------- deleted netowork -------\n");

    TNetwork *node = *network_addr;
    TNetwork *nodeHEAD = *network_addr;

    Record_t *ll =  malloc(sizeof(Record_t));
    ll->next = NULL; // init this 

    Record_t *head = ll;
    Record_t *eff_head = ll;

    Record_t *tmp;

    Record_t *ll_current_record = ll;
    Record_t *ll_current_left ;
    Record_t *ll_current_right;
    Record_t *ll_current_walk;
    Record_t *ll_tail_record;

    ll->network = node; 
    ll_current_walk = ll; 

    printf(" network mailbox ( %p) \n", node);
    printf(" network mailbox value ( %d) \n", node->value);
    printf(" Record mailbox ( %p) \n", ll_current_walk);

    while (ll_current_walk) {
        
        if (ll_current_walk->network->left) {

            ll_current_left = malloc(sizeof(Record_t));
            ll_current_left->network = ll_current_walk->network->left; // store left node in new record 
            ll_current_left->next = NULL;
            
            ll_tail_record = get_tail_record(eff_head);
            ll_tail_record->next = ll_current_left;

            printf(" left record addr %p \n", ll_tail_record);
            
        }
      
        if (ll_current_walk->network->right) {
            ll_current_right = malloc(sizeof(Record_t));
            ll_current_right->network = ll_current_walk->network->right; // store left node in new record 
            ll_current_right->next = NULL;
            
            ll_tail_record = get_tail_record(eff_head);
            ll_tail_record->next = ll_current_right;

            printf(" right record addr %p \n", ll_tail_record);
            
        }

        tmp = ll_current_walk; // this record 


        // next element in linked list 

        if (ll_current_walk->next) {
            
            // ELEMENTS AVAILABLE
            
            ll_current_walk = ll_current_walk->next; // next record 
            
            eff_head = ll_current_walk;
        
        } else {

            // END OF LIST 

            ll_current_walk = ll_current_walk->next; // this is null! 

        }

        // record dumps 

        if (tmp == head) {
            free(tmp);
        }
        
        if (tmp != head)  {
            free(tmp->network); // remove child nodes  (root network is NOT PERSISTENT)
            free(tmp);
        }
    }


    reset_network((*network_addr));

    printf(" ------- deleted done -------\n\n\n");
    

}


void print_network(TNetwork *network) {

    printf("print network\n");

    TNetwork *node = network;
    Record_t *ll = malloc(sizeof(Record_t));
    Record_t *llwalk = ll;
    Record_t *ll_node = ll;
    Record_t *record_left = NULL;
    Record_t *record_right = NULL ;
    Record_t *lllegs = ll;
    Record_t *tail_node;

    ll->network = node; 
    
            printf("print network\n");

    while (llwalk) {
        
        ll_node = llwalk;  //  current node/record
        printf("print network - ( %d) \t (%d) \n",  llwalk->network->value, *llwalk->network->shared_counter);
        

        if (ll_node->network->left) {
            record_left = malloc(sizeof(Record_t));
            record_left->network = ll_node->network->left; // store left node in new record 
            record_left->next = NULL;
            
            tail_node = get_tail_record(ll_node);
            tail_node->next = record_left;
        }

        if (ll_node->network->right) {

            record_right = malloc(sizeof(Record_t));
            record_right->network = ll_node->network->right; // store right node in new record 
            record_right->next = NULL;
            
            tail_node = get_tail_record(ll_node);
            tail_node->next = record_right; // add to list 
        }
    

        llwalk = llwalk->next;   // slow reads

    }

    printf("------- print network end-------\n");


}

void insert(int value, TNetwork *network, Data_t *data) {

    TNetwork * node;
    TNetwork * prev = network;

    if (value == 0) {
            
        if(*network->shared_counter ) {
            // free(network->shared_counter);
        }
   
        reset_network(network);
    }

    else {
        
        node = network; 

        while (node) {
            
            if (node->value  == 0) {
                // previous deleted network or first sample height; root node
                
                node->value = value; 
                node->prev = NULL;
                node->left = NULL;
                node->right = NULL;
                node->left_count = 1;
                node->right_count = 1;
                node->depth = 0;
                node->is_root = 1;
                *node->shared_counter = 1;
                node->root_count = 1;
                calculate_rectangle(node, data, 0);
                node = NULL;  // stop 
            }

            else if (node->value == value) {

                if (node->prev == NULL) {

                    // consecutive root hit 

                    node->root_count++;

                    calculate_rectangle(node, data, 0);

                }

                else if (node->prev) {
                    
                    // consecutive  right side leaf

                    if (node->prev->right == node) {
                        node->right_count+= 1;
                        calculate_rectangle(node, data, 2);
                    } 
                    
                    // consecutive left side leaf 

                    if (node->prev->left == node) {
                        node->left_count += 1;
                        calculate_rectangle(node, data, 1);
                        
                    }
                    
                }

                node = NULL;  // stop 

            } 
            
            else if (value < node->value ) {
                
                // left child traversal ( less than  )

                prev = node; 

                if (node->left) {
                    calculate_rectangle(node, data, 1);
                    node = node->left;
                } else {
                    node->left = malloc( sizeof( TNetwork) );
                    node = node->left; 
                    node->value = value;
                    node->depth = prev->depth + 1;
                    node->left_count = 1; 
                    node->prev = prev;
                    node->shared_counter = prev->shared_counter;
                    *node->shared_counter =  *node->shared_counter + 1; 
                    node->left =  NULL;
                    node->right = NULL;
                    calculate_rectangle(node, data, 1);
                    node = NULL;  // stop 
                    // printf(" add value %d ON NODE %d\n ", value, prev->value);
                }
            } 
            
            else { 

                // right child traversal ( greather than  or equal )

                prev = node; 

                node->right_count += 1;

                calculate_rectangle(node, data, 2);

                if (node->right) {

                    node = node->right;

                } else {
                    
                    node->right = malloc(sizeof(TNetwork));
                    node = node->right;
                    node->value = value;
                    node->depth = prev->depth + 1;
                    node->left_count = 1; 
                    node->right_count = 1;
                    node->prev = prev;
                    node->shared_counter = prev->shared_counter;
                    *node->shared_counter =  *node->shared_counter + 1; 
                    node->left =  NULL;
                    node->right = NULL;
                    // printf(" RIGHT SIDE count %d value %d \n" , node->right_count, node->value);
                    calculate_rectangle(node, data, 2);
                    node = NULL; 
                    // printf(" RIGHT SIDE value %d ; RIGHT DEPTH %d :  COUNTER %d \n ", value, prev->right_count,  *node->shared_counter );
                }

            }

        }
    
    }

}


int largestRectangleArea(int* heights, int heightsSize) {
    
    int value, prev_value; 
    
    Data_t data;

    TNetwork *network = malloc( sizeof( TNetwork) );
  
    init_shared(network);
    reset_network(network);
    reset_data(&data);

    value = 0;
    prev_value = 0;

    int decrease  = 1;
    int increase  = 0;

    for (int i = 0; i  < heightsSize; i++) {

        value = heights[i];

        if (value == 0) {
            increase = 0;
            decrease = 1;
            reset_data(&data);

        }
        
        if (prev_value < value) {
            // printf( "DELETE {PST} %p\n\n" , network->value);
            if (decrease) {
                
                delete_network(&network);

                // reset_data(&data);

                increase = 0;
                decrease = 0;
            }
            insert(value, network, &data);
        }
        else if (prev_value > value) {
            decrease = 1;
            insert(value, network, &data);
        } else {
            insert(value, network, &data);
        }
        
        prev_value = value; 
    }


    //delete network 

    return data.max_area; 
}