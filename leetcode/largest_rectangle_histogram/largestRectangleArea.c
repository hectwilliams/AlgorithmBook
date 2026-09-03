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

typedef struct Node {
    int index;
    int value; 
    int n;
    int low;
    int prev_low ;
    int cont_count;
} Node;

// binary tree 
typedef struct TNetwork {
    int value;
    struct TNetwork *prev;
    struct TNetwork *left;
    struct TNetwork *right;
    int depth;
    int count;
    int is_root;
    int right_count;
    int left_count;
    int *shared_counter;

} TNetwork;

typedef struct Data {
    int min_bin;
    int area;
}Data;
// // list of tree
// typedef struct TNetworkLL {
//         TNetwork * network 
// } TNetworkLL; 

// typedef Node NodeList_t[NODE_LIST_SIZE];

// typedef int intlist_t[1];

typedef struct Record_t {
     TNetwork *network;
    struct Record_t *next;
} Record_t;


void reset_network(TNetwork *network ) {
    network->value = 0;
    network->left = NULL;
    network->right = NULL;
    network->prev = NULL;

    network->depth = 0;
    // network->count = 0;
    network->is_root = 0;
    network->right_count = 0;
    network->left_count = 0;

    if(network->shared_counter) {
        free(network->shared_counter);
    }
    network->shared_counter = malloc(sizeof(int));
    *network->shared_counter = 0; 
    
    // if (!network->min_bin) {
    //     network->min_bin = malloc(sizeof(int));
    // }

    // *network->min_bin = 1000000; // very large number 

}

Record_t * get_tail_record(Record_t *node) {
    while (node->next) {
        node = node->next;
    }
    return node; 
}

// void set_histo_min(int value, TNetwork *node) {
//     if ( value < *node->min_bin) {
//         *node->min_bin = value; 
//     }
// }

void delete_network(TNetwork **network_addr) {
    printf(" ------- deleted netowork -------\n");

    TNetwork *node = *network_addr;

    Record_t *ll = malloc(sizeof(Record_t));
    Record_t *head = ll;
    Record_t *tmp;

    Record_t *ll_current_record = ll;
    Record_t *ll_current_left ;
    Record_t *ll_current_right;
    Record_t *ll_current_walk;
    Record_t *ll_tail_record;

    ll->network = node; 
    ll_current_walk = ll; 

    // printf( "%p\n" , ll);
    // printf( "%p\n" , ll->next);

    while (ll_current_walk) {

        ll_current_record = ll_current_walk;

        if (ll_current_record->network->left) {
            ll_current_left = malloc(sizeof(Record_t));
            ll_current_left->network = ll_current_record->network->left; // store left node in new record 
            ll_current_left->next = NULL;
            
            ll_tail_record = get_tail_record(head);
            ll_tail_record->next = ll_current_left;
            
        }

        if (ll_current_record->network->right) {
            ll_current_right = malloc(sizeof(Record_t));
            ll_current_right->network = ll_current_record->network->right; // store left node in new record 
            ll_current_right->next = NULL;
            
            ll_tail_record = get_tail_record(head);
            ll_tail_record->next = ll_current_right;
            
        }
        
        tmp = ll_current_record;
        ll_current_walk = ll_current_walk->next; // walker steps forward once  

        // new head 
        head = tmp->next; 

        // free release previous head resources 
        free(tmp->network);
        free(tmp);

    }

    *network_addr = malloc( sizeof( TNetwork) );
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
        printf("print network - ( %d)\n",  llwalk->network->value);
        

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

void insert(int value, TNetwork *network, Data *data) {

    TNetwork * node = network;
    TNetwork * prev = network;

    // set_histo_min(value, network);
    // network->value = value;
    // network->depth = 1;

    if (value == 0) {

        // root 
        reset_network(network);
        network->is_root = 1; 
    }

    else {
        
        TNetwork *node = network; 

        while (node) {
                
            if (node->value  == 0) {
                //  // root condition 
                node->value = value; 
                node->prev = NULL;
                node->left = NULL;
                node->right = NULL;
                node->left_count = 1;
                node->right_count = 1;
                node->depth = 1;
                node->is_root = 1;
                printf(" add ROOT value %d ; depth %d ; area %d \n ", value, node->depth, value);
                node = NULL; 
            }

            else if (node->value == value) {

                if (node->prev->right == value) {
                    node->right_count+= 1;
                } 

                if (node->prev->left == value) {
                    node->left_count +1;
                }

                // node->count++;
                node = NULL; 

            } 
            
            else if (value < node->value ) {
                prev = node; 
                if (node->left) {
                    node = node->left;
                } else {
                    node->left = malloc( sizeof( TNetwork) );
                    node = node->left; 
                    node->value = value;
                    node->depth = prev->depth + 1;
                    node->left_count = 1; 
                    node->prev = prev;
                    node = NULL; 
                    // printf(" add value %d ON NODE %d\n ", value, prev->value);
                }
            } 
            
            else { 
                // greather than 

                prev = node; 
                prev->right_count += 1;
                printf(" RIGHT SIDE value %d ; RIGHT DEPTH %d \n ", value, prev->right_count);
                
                if (node->right) {
                    node = node->right;
                } else {
                    
                    node->right = malloc(sizeof(TNetwork));
                    node = node->right;
                    node->value = value;
                    node->depth = prev->depth + 1;
                    node->left_count = 1; 
                    node->right_count += 1;
                    node->prev = prev;

                    printf(" RIGHT SIDE value %d ; RIGHT DEPTH %d \n ", value, prev->right_count);
                    node = NULL; 
                }

            }

        }
    
    }

}


int largestRectangleArea(int* heights, int heightsSize) {
    
    int value, prev_value; 

    TNetwork *network = malloc( sizeof( TNetwork) );
    reset_network(network);

    prev_value = 0;
    value = 0;
    int decrease  = 1;
    int increase  = 0;

    Data data;

    data.min_bin = 10000000;
    data.area = 0;
    

    for (int i = 0; i  < heightsSize; i++) {

        value = heights[i];

        if (value == 0) {
            increase = 0;
            decrease = 1;
            data.min_bin = 10000000;
        }
        
        if (prev_value < value) {
            // printf( "DELETE {PST} %p\n\n" , network->value);
            if (decrease) {
                print_network(network);
                printf("---x");
                delete_network(&network);
                increase = 0;
                decrease = 0;
            }
            insert(value, network, &data);
        }
        else if (prev_value > value) {
            decrease = 1;
            insert(value, network, &data);
        }
        
        prev_value = value; 
    }

    return 1; 
}