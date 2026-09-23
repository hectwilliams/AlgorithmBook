#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define test_01_s babgbag

typedef struct Node {
    char acc[1000];
    int s_index;
    int t_index; 
    struct Node *next; 
    int count;
    int index;
} Node; 

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

int numDistinct(char* s, char* t) {

    // init node 
    Node *node = malloc( sizeof(Node));
    
    int s_length = length(s);
    int t_length = length(t);
    
    printf("%d\n", s_length);
    printf("%d\n", t_length);
    
    if (s_length == -1) {
        // null-termination node found in string 
        return  0;
    }
    
    if (strcmp(s, t) == 0) {
        return 1;
    }

    init_node(node, s, s_length);
    int ret = search(node, s, s_length, t, t_length);

    return ret;

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