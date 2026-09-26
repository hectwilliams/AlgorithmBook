#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <assert.h>

#define TESTING 1

#if TESTING
    #define TEST_01 (char[2][1000]){ "babgbag", "bag"}
    #define TEST_02 (char[2][1000]){ "rabbbit", "rabbit"}
    
    #define TEST_03 (char[2][1000]){ \
        "aabb", \
        "abb"\
    }

    #define TEST_04 (char[2][1000]){ \
        "aabdbaabeeadcbbdedacbbeecbabebaeeecaeabaedadcbdbcdaabebdadbbaeabdadeaabbabbecebbebcaddaacccebeaeedababedeacdeaaaeeaecbe",  \
        "bddabdcae" \
    }

        #define TEST_05 (char[2][1000]){ \
        "gcaaafae",  \
        "ecag" \
    }
#endif 


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

typedef struct BNode {
    char c; 
    char *acc;
    char *target_string;
    unsigned long target_string_len;
    char * stream;
    unsigned long stream_length;
    unsigned long index;
    struct BNode *next; 
} BNode; 


unsigned long length(char *s) {
    unsigned long i = 0;

    while (s[i++] != '\0' && i != 1000) {}
    return i - 1 ; 
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

// Node * get_next_list(Node *node , const char *s, const int s_length, const char *t,  const int t_length ,   int * const number_substrings ) {
//     Node *head = NULL;
//     Node *tail = NULL;
//     Node *tmp = NULL;
//     Node *prev = NULL;
//     int c; 
//     printf("\n[%d] \t [%d]\n\n", node->index, t_length);
    
//     if ( node->index >= t_length  ) {
//         c = get_count(node);
//         if (*number_substrings < c) 
//             *number_substrings = c; 
//         printf("DEBUG  \t COUNT  [%d] [%d]\t", node->count, *number_substrings);

//         return NULL;
//     }

//     while (node) {

//         for (int w = node->s_index; w < s_length; w++ ) {

//             if ( t[node->index] == s[w] ) {

//                 tmp = malloc( sizeof(Node));
//                 tmp->s_index = w + 1;
//                 tmp->index = node->index + 1;
//                 tmp->next = NULL; 

//                 if (head == NULL) {
//                     head = tail = tmp; 
//                     tmp->count = 1;

//                 } else {
//                     tmp->count = prev->count + 1;
//                     tail->next = tmp;
//                     tail = tmp; 


//                 }

//                 prev = tmp; 

//                 // if (tmp->index  ==  t_length) {

//                 //     if (tmp->count ==  *number_substrings ) {
//                 //         *number_substrings = tmp->count;
//                 //     }
//                 // }

//                 // if (head == NULL) {

//                 //     head = malloc( sizeof(Node));
//                 //     head->next = NULL;
//                 //     head->s_index = w + 1;
//                 //     head->count = node->count + 1;
//                 //     head->index = node->index + 1;
//                 //     tail = head;

//                 // } else {

//                 //     tmp->next = NULL;

//                 // } 

//                 // if ()

//             }

//         }

//         node = node->next;
//     }

//     return head; 
// }

// int search(Node * node, char *s, int s_length, char *t,  int t_length) {

//     Node *new_list_head = NULL;
//     Node *new_list_tail = NULL;
//     Node *tmp = NULL;

//     int max_count = 0;
//     int found;
//     int found_count = 0;
//     char target;
//     int valid =0;
//     int i;
//     int number_substrings = 0;

//     // print_count(node);
//     int cnt = 0;

//     while (node) {

//         // update node
//         node = get_next_list(node, s, s_length, t, t_length, &number_substrings);
//         print_count(node);

//     }

//     return number_substrings; 


// }

void print_ll(TNode *node) {

    while (node) {
        printf("[%d]", node->index);
        node = node->next; 
    }
    printf("\n");
}

void print_mask(int * mask, int len) {


    for (int k = 0; k < len; k++) {
        printf("%d ", mask[k]);
    }
    printf("\n");

}

// void recursive_search(char *t, int t_length, char *s, int s_length, int *bitmask, int * n_sequences) {

//     // printf(" LENGTH %d\n", t_length);

//     if (t_length == 0) {
        
//         printf("\t\t\t\t\tUPDATE N SEQUENCE\n");
        
//         *n_sequences =  *n_sequences  + 1;
    
//     }
    
//     else if (t_length == 1) {

//         printf("SINGLE ELEMENT: TARGET %c \n", t[0]);

//         print_mask(bitmask, s_length);
//         int found = 0;

//         for (int i = 0; i < s_length; i++) {
//             if (bitmask[i] && t[0] == s[i]) {
//                 found++;
//                 recursive_search("", 0, s, s_length, bitmask, n_sequences); 
//             }
//         }

//         if (found == 0) {
//             printf("NO SOLUTION \n\n");
//         }

//     } else {
        
//         TNode *front_ll = NULL;
//         TNode *front_head = NULL;

//         TNode *end_ll = NULL;
//         TNode *end_head = NULL;
        
//         // set front target char
//         char front = t[0];

//         // set end target char
//         char end = t[t_length - 1];

//         int n_between_expect = (t_length - 1) - 1;
        
//         printf(" ---------------------------------------------------- \n\n");

//         printf(" NEW FRONT:%c  END: %c \n", front, end);

//         // print_mask(bitmask, s_length);

//         // find windows front - end target

//         for (int i = 0; i < s_length; i++) {

//             if (!bitmask[i]) 
//                 continue ;

//             if (front == s[i]) {
//                 TNode *tmp = malloc( sizeof(TNode));
//                 tmp->index = i; 
//                 tmp->next = NULL;
//                 if (front_ll == NULL) {
//                     front_ll = tmp;
//                     front_head = tmp; 
//                 } else {
//                     front_ll->next =  tmp;
//                     front_ll = tmp;
//                 }
                
//             }

//             if (end == s[i]) {
//                 TNode *tmp = malloc( sizeof(TNode));
//                 tmp->index = i; 
//                 tmp->next = NULL;

//                 if (end_ll == NULL) {
//                     end_ll = tmp;
//                     end_head = tmp; 
//                 } else {
//                     end_ll->next =  tmp;
//                     end_ll = tmp;
//                 }
                    
//             }
           
//         }


//         printf(" LENGTH TARGET: %d \t TARGET_DATA: %s \n", t_length, t);

//         if (front_head && end_head) {

//             printf(" NEW LINKED LIST HEADS: FRONT :%d  TAIL: %d \n", front_head->index, end_head->index);
            
//         } else {
            
//             printf(" FAILE  SEARCH RETURNING ");
//             return;


//         }
        

//         printf(" BOOM\n");
       

//         int n_samples_between = 0 ; 
//         TNode *w_front;
//         TNode *w_end = end_head;

//         // 

//         print_ll(front_head);
//         print_ll(end_head);

//         assert(0);

//         while (w_end) {

//             w_front = front_head;

//             while (w_front) {

                
//                 if  (w_end->index > w_front->index) {
//                     n_samples_between = w_end->index - w_front->index - 1;

//                     printf("between e - %d  f - %d \t nbtwn - %d \t nbtwnexp - %d\t T-LENGTH %d \n", w_end->index, w_front->index, n_samples_between, n_between_expect, t_length);
                    
//                     // new bitmask 
//                     int *new_bitmask = calloc( (unsigned)s_length,  sizeof(int));
                    
//                     // copy argument bitmask
//                     memcpy(new_bitmask, bitmask, ((unsigned) s_length) * sizeof(int)); 
                    
//                     new_bitmask[w_end->index ] = 0;
//                     new_bitmask[w_front->index ] = 0;

//                         // printf("%d %d %d %d %d %d %d\n", new_bitmask[0], new_bitmask[1],  new_bitmask[2], new_bitmask[3], new_bitmask[4], new_bitmask[5], new_bitmask[6]);

                    
                                
//                     // reduce t 
//                     printf("THIS T %s | THIS T_LENGTH %d\n", t, t_length);

//                     int t_length_new = t_length - 2;
                    
//                     char *t_new = calloc( t_length_new + 1,  sizeof(int));
                    
//                     memcpy(t_new, t + 1, t_length_new );
                    



//                     if (t_length > 2) {
                        
//                         if (n_samples_between >= n_between_expect ) {
//                             printf("POSSIBLE SOLUTION:  \n");
                            
//                             // grab sequences at different positions 

//                             for (int i = 0; i < s_length; i++) {
                                
//                                 if (i < w_front->index || i > w_end->index ) {
//                                     new_bitmask[i ] = 0;
//                                 }
                                
//                             }
                            
//                             if ()
//                             printf("T_NEW  %s | T_LENGTH %d\n", t_new, t_length_new);

//                             recursive_search(t_new, t_length_new, s, s_length, new_bitmask, n_sequences); 


//                         } else {
//                             // printf("NO SOLUTION: Invalid \n");
//                         }
                        
//                     }  
                    
//                     else if (t_length == 2) {

//                         if (n_samples_between >= n_between_expect ) {

//                             // assert(0);
                            
//                             printf("T_NEW  %s | T_LENGTH %d\n", t_new, t_length_new);

//                             recursive_search("",  t_length_new, s, s_length, new_bitmask, n_sequences); 

//                         }
                        
//                     }

//                     // printf("T_NEW  %s | T_LENGTH %d\n", t_new, t_length_new);

//                     // print_mask(bitmask, s_length);

//                     printf(" '''''''''''''''''''''''''''''''''''''''''''  \n\n");

//                 }

//                 // if (!bitmask[w_end->index] || !bitmask[w_front->index] ) {
//                 //     // noop
//                 // } else 
                
//                 // if (  t_length > 2 ) {

//                 // }

//                 // if ( (w_end->index > w_front->index) && n_samples_between <= n_between_expect) {

//                 //     // create new update bitmask 
//                 //     int *new_bitmask = calloc( (unsigned)s_length,  sizeof(int));
//                 //     // copy argument bitmask
//                 //     memcpy(new_bitmask, bitmask, ((unsigned) s_length) * sizeof(int)); 
     
//                 //     new_bitmask[w_end->index ] = 0;
//                 //     new_bitmask[w_front->index ] = 0;
                    
//                 //     // reduce t 
//                 //     int t_length_new = t_length - 2;
//                 //     char *t_new = calloc( t_length_new + 1,  sizeof(int));
                    
//                 //     if ( (n_samples_between > 0) ) {

//                 //         for (int i = 0; i < s_length; i++) {
                            
//                 //             if (i < w_front->index || i > w_end->index ) {
//                 //                 new_bitmask[i ] = 0;
//                 //             }
                            
//                 //         }
                        
//                 //     } 
                    
//                 //     if (n_samples_between >= 0 && t_length == 2 ) {
                        
//                 //         // assert(0);
                        
//                 //     }
//                 //     printf("%d %d %d %d %d %d %d\n", new_bitmask[0], new_bitmask[1],  new_bitmask[2], new_bitmask[3], new_bitmask[4], new_bitmask[5], new_bitmask[6]);
                    
//                 //     memcpy(t_new, t + 1, t_length_new );
                    
//                 //     printf("T_NEW  %s | T_LENGTH %d\n", t_new, t_length_new);
//                 //     recursive_search(t_new, t_length_new, s, s_length, new_bitmask, n_sequences); 
//                 //     printf(" RETURNED RECURSIVE\t %d \n ", *n_sequences);

                 
//                 // }

//                 w_front = w_front->next;
                
//             }
            
//             w_end = w_end->next;
//         }



//         //  if (front == 'b' && end == 'b') {
//         //     // print_ll(front_head);
//         //     // print_ll(end_head);
//         //     assert(0);
//         // }

//         // print_ll(end_head);
//         // print_ll(front_head);
        
        
//     }
// }


void delete_ll (BNode *node) {

    BNode *next;

    while (node) {
        next = node->next; 
        free(node->target_string);
        free(node->stream);
        free(node);
        node = next; 
    }
    

}

void show_newList (BNode *node, int *n_seq) {
    
    // clear 
    *n_seq  = 0; 
    
    // clear 
    printf("\n");
    while (node) {
        *n_seq = *n_seq + 1 ;
        printf(" TARGET: %s STREAM: %s \n", node->target_string, node->stream);
        node = node->next; 
    }
    printf("\n");
}

void recursive_search(char *t, unsigned long t_length, char *s, unsigned long s_length, int *bitmask, int * n_sequences) {
    BNode *node = NULL;
    BNode *head = NULL;
    BNode *currnt = NULL;
    BNode *currnt_head = NULL;

    BNode *new_list_node = NULL;
    BNode *new_list_head = NULL;
    BNode *tmp = NULL;
    BNode *pad = NULL;


    int idx = 0;
    char c_target;
    char c_eval;
    unsigned long stream_n;
    unsigned long stream_n_eff;
    int found = 0;

    // placeholder- entry node 

    currnt = malloc(sizeof(BNode));
    currnt->index = 0;
    currnt->target_string = t;
    currnt->target_string_len = t_length;
    currnt->stream_length = s_length;
    currnt->stream = s; 
    currnt->next = NULL;
    currnt_head = currnt;

    while (currnt->index < t_length) {
        // index guard 

        // create new llist 
        new_list_head = NULL;
        found = 0;
        
        while (currnt) {
            // iterate linked list 

            c_target = currnt->target_string[0]; 

            printf("target char : %c | TARGET STRING: %s | STREAM: %s | STREAM LENGTH: %lu |  %lu \n", c_target, currnt->target_string,  currnt->stream , currnt->stream_length ,  currnt->index);

            for (unsigned long i = 0; i < currnt->stream_length; i++) {
                c_eval = currnt->stream[i];
                
                if (c_target == c_eval  ) {
                    found = 1;
                    
                    printf("%c %c  %lu \n", c_eval, c_target, i);
                    
                    #if 1
                    
                    tmp  = malloc(sizeof(BNode));

                    tmp->next = NULL; 
                    
                    tmp-> index = currnt->index + 1; 

                    tmp->target_string_len = currnt->target_string_len - 1;
                    
                    tmp->target_string = calloc( ( (unsigned long) tmp->target_string_len + 1) , sizeof(char));
                    
                    memcpy( tmp->target_string /* string buffer*/, currnt->target_string + 1 /* offset 1 */,  (unsigned long)  tmp->target_string_len  );
                    
                    stream_n = (unsigned long) currnt->stream_length - (i + 1) ; // true size 
                    stream_n_eff = stream_n  + 1  ; // effective size tking into account terminating null 
                    
                    tmp->stream = calloc( stream_n_eff, sizeof(char) );

                    tmp->stream_length =  stream_n; // always positive 
                    
                    memcpy( tmp->stream, currnt->stream + (i + 1) , stream_n );
                    
                    printf(" NEXT STREAM %s   NEXT TARGET %s  NEXT TARGET INDEX %lu \n", tmp->stream, tmp->target_string, tmp->index);
                    
                    if (new_list_head == NULL) {
                        new_list_head = tmp;
                        new_list_node = tmp;
                    } else {
                        new_list_node->next = tmp;
                        new_list_node = tmp; 
                    }
                    
                    #endif 
                    
                }
            }


            if (currnt->index == t_length) {
                *n_sequences = *n_sequences + 1;
            }

            currnt = currnt->next; 
        }

        if (found ) {

            // new tree exist 
            
            pad = currnt_head; // pad new list
            
            currnt_head = new_list_head;
            currnt = currnt_head; // update new list 
            
            printf("show list");
            if (currnt->index == t_length) {
                show_newList(currnt, n_sequences);
            }
            printf("show list end\n");
            
            printf(" --   \n", pad);
            printf(" deleting    \n", pad);
            delete_ll(pad);
            printf(" deletion end   \n", pad);
            
        } else {
            break;
        }
        // printf("hello world\n");
        // break;
        
    }
    
   




}

int numDistinct(char* s, char* t) {

    // // init node 
    // Node *node = malloc( sizeof(Node));
    
    unsigned long s_length = length(s);
    unsigned long t_length = length(t);

    printf("%lu\n", s_length);
    printf("%lu\n", t_length);
    
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
    for (int i = 0; i < s_length; i++) {
        bitmask[i] = 1;
    }
    
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

#if TESTING

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
                memcpy(s, TEST_01[0], sizeof(TEST_01[0]));
                memcpy(t, TEST_01[1], sizeof(TEST_01[1]));
                break;

            case 2:
                memcpy(s, TEST_02[0], sizeof(TEST_02[0]));
                memcpy(t, TEST_02[1], sizeof(TEST_02[1]));
                break;
            
            case 3:
                // memset(s, "babgbag", 7);
                memcpy(s, TEST_03[0], sizeof(TEST_03[0]));
                memcpy(t, TEST_03[1], sizeof(TEST_03[1]));
                break;

            case 4:
                memcpy(s, TEST_04[0], sizeof(TEST_04[0]));
                memcpy(t, TEST_04[1], sizeof(TEST_04[1]));
                break;

            case 5:
                memcpy(s, TEST_05[0], sizeof(TEST_05[0]));
                memcpy(t, TEST_05[1], sizeof(TEST_05[1]));
                break;

            default:
                break;
        
        }

        int sol = numDistinct(s, t);
        printf("solution %d\n", sol);
    }

#endif 
   // if ( (n_samples_between > 0 && t_length > 2) ||  ) {

                    //     printf(" %d - %d  - 1 = %d\n", w_end->index, w_front->index, n_samples_between);
                        
                    //     // create new update bitmask 
                    //     // int *new_bitmask = calloc( (unsigned)s_length,  sizeof(int));
                        
                    //     // copy argument bitmask
                    //     // memcpy(new_bitmask, bitmask, ((unsigned) s_length) * sizeof(int)); 
                        
                    //     // set mask valid window
                    //     //  int k = w_front->index + 1;
                    //     //  while (k < w_end->index) {
                    //         //     new_bitmask[k++] = 1;
                    //         //  }
                   
                    // }
                    //  printf("new T %d \n", *n_sequences);

                    // passes search analysis requirement 