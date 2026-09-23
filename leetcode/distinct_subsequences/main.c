#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <assert.h>

#define test_01_s babgbag

typedef struct Node {
    char acc[1000];
    int s_index;
    int t_index; 
    struct Node *next; 
    int count;
    int index;
} Node; 


typedef struct TNode {
    int index;
    struct TNode *next; 
} TNode; 


int length(char *s) {
    int count = 0;
    int i = 0;

    while (s[i++] != '\0' && i != 1000) {}
    return i == 1000? -1 : i - 1; 
}


// Node * new_node(char c, int index) {
//     return NULL;
// }

void init_node (Node *node, char *s, int s_length){
    memset(node->acc, 0, sizeof(node->acc));
    memcpy(node->acc, s, (unsigned long ) s_length);
    node->s_index = 0;
    node->t_index = 0; 
    node->next = NULL;
    node->count = 0; 
    node->index = 0;
    printf(" size of %lu\t string %s \n", sizeof(node->acc), node->acc);
}

void print_count (Node *node) {
    while (node) {
        printf("[%d]\t index[%d]\n", node->count, node->s_index);
        node = node->next; 
    }
    printf("\n-----\n");
}

int  get_count (Node *node) {
    int n = 0;

    while (node)  {
        node = node->next; 
        n++;
    }

    return n; 
}

Node * get_next_list(Node *node , const char *s, const int s_length, const char *t,  const int t_length ,   int * const number_substrings ) {
    Node *head = NULL;
    Node *tail = NULL;
    Node *tmp = NULL;
    Node *prev = NULL;
    int c; 
    printf("\n[%d] \t [%d]\n\n", node->index, t_length);
    
    if ( node->index >= t_length  ) {
        c = get_count(node);
        if (*number_substrings < c) 
            *number_substrings = c; 
        printf("DEBUG  \t COUNT  [%d] [%d]\t", node->count, *number_substrings);

        return NULL;
    }

    while (node) {

        for (int w = node->s_index; w < s_length; w++ ) {

            if ( t[node->index] == s[w] ) {

                tmp = malloc( sizeof(Node));
                tmp->s_index = w + 1;
                tmp->index = node->index + 1;
                tmp->next = NULL; 

                if (head == NULL) {
                    head = tail = tmp; 
                    tmp->count = 1;

                } else {
                    tmp->count = prev->count + 1;
                    tail->next = tmp;
                    tail = tmp; 


                }

                prev = tmp; 

                // if (tmp->index  ==  t_length) {

                //     if (tmp->count ==  *number_substrings ) {
                //         *number_substrings = tmp->count;
                //     }
                // }

                // if (head == NULL) {

                //     head = malloc( sizeof(Node));
                //     head->next = NULL;
                //     head->s_index = w + 1;
                //     head->count = node->count + 1;
                //     head->index = node->index + 1;
                //     tail = head;

                // } else {

                //     tmp->next = NULL;

                // } 

                // if ()

            }

        }

        node = node->next;
    }

    return head; 
}

int search(Node * node, char *s, int s_length, char *t,  int t_length) {

    Node *new_list_head = NULL;
    Node *new_list_tail = NULL;
    Node *tmp = NULL;

    int max_count = 0;
    int found;
    int found_count = 0;
    char target;
    int valid =0;
    int i;
    int number_substrings = 0;

    // print_count(node);
    int cnt = 0;

    while (node) {

        // update node
        node = get_next_list(node, s, s_length, t, t_length, &number_substrings);
        print_count(node);

    }

    return number_substrings; 


}

void recursive_search(char *t, int t_length, char *s, int s_length, int *bitmask, int * n_sequences) {

    
    if (t_length == 0) {
        
        *n_sequences =  *n_sequences  + 1;
    }
    
    else if (t_length == 1) {
        // find char in s string (minding bitmask)
        // TNode node;
        // copy mask;
        for (int i = 0; i < s_length; i++) {
            if (bitmask[i] && t[0] == s[i]) {
                recursive_search("", 0, s, s_length, bitmask, n_sequences); 
            }
        }

    } else {
        
            TNode *front_ll = NULL;
    TNode *front_head = NULL;

    TNode *end_ll = NULL;
    TNode *end_head = NULL;

   
        char front = t[0];
        char end = t[t_length - 1];

        for (int i = 0; i < s_length; i++) {

            if (front == s[i]) {
                TNode *tmp = malloc( sizeof(TNode));
                tmp->index = i; 
                tmp->next = NULL;
                if (front_ll == NULL) {
                    front_ll = tmp;
                    front_head = tmp; 
                } else {
                    front_ll->next =  tmp;
                    front_ll = tmp;
                }
                
            }

            if (end == s[i]) {
                TNode *tmp = malloc( sizeof(TNode));
                tmp->index = i; 
                tmp->next = NULL;

                if (end_ll == NULL) {
                    end_ll = tmp;
                    end_head = tmp; 
                } else {
                    end_ll->next =  tmp;
                    end_ll = tmp;
                }
                    
            }
           
        }

        int n_samples_between = 0 ; 
        TNode *w_front;
        TNode *w_end = end_head;

        while (w_end) {

            w_front = front_head;

            while (w_front) {

                n_samples_between = w_end->index - w_front->index - 1;
                
                if (bitmask[w_end->index] || bitmask[w_front->index] ) {
                    // noop
                } else if (n_samples_between > 0) {

                    printf(" %d - %d  = %d\n", w_end->index, w_front->index, n_samples_between);

                    // create new update bitmask 
                     int *new_bitmask = calloc( (unsigned)s_length,  sizeof(int));

                     // copy argument bitmask
                     memcpy(new_bitmask, bitmask, (unsigned) s_length); // valid slots for next value 

                     // set mask valid window
                     int k = w_front->index + 1;
                     while (k < w_end->index) {
                        new_bitmask[k++] = 1;
                     }
                     //  new_bitmask[w_end->index ] = 1;
                     //  new_bitmask[w_front->index ] = 1;


                     printf("%d %d %d %d %d %d %d\n", new_bitmask[0], new_bitmask[1],  new_bitmask[2], new_bitmask[3], new_bitmask[4], new_bitmask[5], new_bitmask[6]);

                     // reduce t 
                     int t_length_new = t_length - 2;
                     char *t_new = calloc( t_length_new,  sizeof(int));
                     
                     memcpy(t_new, t + 1, t_length_new );
                     printf("new T %s\n", t_new);

                     recursive_search(t_new, t_length_new, s, s_length, new_bitmask, n_sequences); 

                     printf("new T %d \n", *n_sequences);

                    // passes search analysis requirement 
                }

                w_front = w_front->next;
                
            }
            
            w_end = w_end->next;
        }

        // print_ll(end_head);
        // print_ll(front_head);
        
        
    }
}

void print_ll(TNode *node) {

    while (node) {
        printf("[%d]", node->index);
        node = node->next; 
    }
    printf("\n");
}

int numDistinct(char* s, char* t) {

    // // init node 
    // Node *node = malloc( sizeof(Node));
     
    
    int s_length = length(s);
    int t_length = length(t);

    printf("%d\n", s_length);
    printf("%d\n", t_length);
    
    // if (s_length == -1) {
    //     // null-termination node found in string 
    //     return  0;
    // }
    
    // if (strcmp(s, t) == 0) {
    //     return 1;
    // }

    // init_node(node, s, s_length);
    // int ret = search(node, s, s_length, t, t_length);

    // return ret;


    int *bitmask = calloc( (unsigned)s_length,  sizeof(int));
    int n_sequences = 0;

    if (t_length == 1) {

        for (int i = 0; i < s_length; i++) {
            n_sequences += +(t[0] == s[i]);
        }

    } else if (t_length > 1) {

        recursive_search(t, t_length, s, s_length, bitmask, &n_sequences);

    }
    return n_sequences; 

}

int main(int argc, char *args[]) {
    
    char *s = calloc(1000, sizeof(char));
    char *t = calloc(1000, sizeof(char));
    
    if (argc != 2) {
        return 1;
    }
    
    char *endptr;
    long test_select = strtol(args[1], &endptr, 10);

    switch(test_select) {
        
        case 1:
            // memset(s, "babgbag", 7);
            memcpy(s, "babgbag", sizeof("babgbag"));
            memcpy(t, "bag", sizeof("bag"));
            break;

        case 2:
           memcpy(s, "rabbbit", sizeof("rabbbit"));
            memcpy(t, "rabbit", sizeof("rabbit"));
            break;

        case 3:
            memcpy(s, "aabb", sizeof("aabb"));
            memcpy(t, "abb", sizeof("abb"));
            break;
 
        default:
            break;
    
    }

    int sol = numDistinct(s, t);
    printf("solution %d\n", sol);
}