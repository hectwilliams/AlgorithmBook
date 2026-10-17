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

typedef struct ENode {
    char c;
    unsigned long index;
    unsigned long depth;
    struct ENode *children; 
    unsigned long children_size; 
    struct ENode *prev;
    unsigned long enabled;
    char expect;
} ENode; 

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

typedef struct VertexList {
    struct Vertex *vertex;
    struct VertexList *next;
    unsigned active;
    unsigned stream_index; 
} VertexList; 

typedef struct VNextList {
    struct VertexList *vlist;
    struct VNextList *next; 
    unsigned active;
} VNextList; 

typedef struct Vertex {
    char c; 
    unsigned long index ;
    struct VertexList *children;
} Vertex; 

typedef struct Targets {
    char c;
    unsigned index; 
    struct Targets *next; 
} Targets;

typedef struct TreeId {
    int is_header;
    char c;
    unsigned index;
    struct TreeId *next;
    struct TreeId *down;
    struct Targets *next_targets;

} TreeId; 

typedef struct ANode {
    char c;
    unsigned index;
    struct ANode *next;
    unsigned long s_length;
    char * t;
    unsigned long t_length;
    unsigned offset;
    unsigned eval_count;

} ANode;

typedef struct ATree {
    ANode *head;
    ANode *tail;
} ATree;

unsigned long length(char *s) {
    unsigned long i = 0;
    while (s[i++] != '\0' && i != 1000) {}

    if (i > 1 )
        return i - 1 ; 
    else 
        return 0;
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




}

// void recursive_search(char *t, unsigned long t_length, char *s, unsigned long s_length, int *bitmask, int * n_sequences) {
//     BNode *node = NULL;
//     BNode *head = NULL;
//     BNode *currnt = NULL;
//     BNode *currnt_head = NULL;

//     BNode *new_list_node = NULL;
//     BNode *new_list_head = NULL;
//     BNode *tmp = NULL;
//     BNode *pad = NULL;


//     int idx = 0;
//     char c_target;
//     char c_eval;
//     unsigned long stream_n;
//     unsigned long stream_n_eff;
//     int found = 0;

//     // placeholder- entry node 

//     currnt = malloc(sizeof(BNode));
//     currnt->index = 0;
//     currnt->target_string = t;
//     currnt->target_string_len = t_length;
//     currnt->stream_length = s_length;
//     currnt->stream = s; 
//     currnt->next = NULL;
//     currnt_head = currnt;

//     while (currnt->index < t_length) {
//         // index guard 

//         // create new llist 
//         new_list_head = NULL;
//         found = 0;
        
//         while (currnt) {
//             // iterate linked list 

//             c_target = currnt->target_string[0]; 

//             printf("target char : %c | TARGET STRING: %s | STREAM: %s | STREAM LENGTH: %lu |  %lu \n", c_target, currnt->target_string,  currnt->stream , currnt->stream_length ,  currnt->index);

//             for (unsigned long i = 0; i < currnt->stream_length; i++) {
//                 c_eval = currnt->stream[i];
                
//                 if (c_target == c_eval  ) {
//                     found = 1;
                    
//                     printf("%c %c  %lu \n", c_eval, c_target, i);
                    
//                     #if 1
                    
//                     tmp  = malloc(sizeof(BNode));

//                     tmp->next = NULL; 
                    
//                     tmp-> index = currnt->index + 1; 

//                     tmp->target_string_len = currnt->target_string_len - 1;
                    
//                     tmp->target_string = calloc( ( (unsigned long) tmp->target_string_len + 1) , sizeof(char));
                    
//                     memcpy( tmp->target_string /* string buffer*/, currnt->target_string + 1 /* offset 1 */,  (unsigned long)  tmp->target_string_len  );
                    
//                     stream_n = (unsigned long) currnt->stream_length - (i + 1) ; // true size 
//                     stream_n_eff = stream_n  + 1  ; // effective size tking into account terminating null 
                    
//                     tmp->stream = calloc( stream_n_eff, sizeof(char) );

//                     tmp->stream_length =  stream_n; // always positive 
                    
//                     memcpy( tmp->stream, currnt->stream + (i + 1) , stream_n );
                    
//                     printf(" NEXT STREAM %s   NEXT TARGET %s  NEXT TARGET INDEX %lu \n", tmp->stream, tmp->target_string, tmp->index);
                    
//                     if (new_list_head == NULL) {
//                         new_list_head = tmp;
//                         new_list_node = tmp;
//                     } else {
//                         new_list_node->next = tmp;
//                         new_list_node = tmp; 
//                     }
                    
//                     #endif 
                    
//                 }
//             }


//             if (currnt->index == t_length) {
//                 *n_sequences = *n_sequences + 1;
//             }

//             currnt = currnt->next; 
//         }

//         if (found ) {

//             // new tree exist 
            
//             pad = currnt_head; // pad new list
            
//             currnt_head = new_list_head;
//             currnt = currnt_head; // update new list 
            
//             printf("show list");
//             if (currnt->index == t_length) {
//                 show_newList(currnt, n_sequences);
//             }
//             printf("show list end\n");
            
//             printf(" --   \n", pad);
//             printf(" deleting    \n", pad);
//             delete_ll(pad);
//             printf(" deletion end   \n", pad);
            
//         } else {
//             break;
//         }
//         // printf("hello world\n");
//         // break;
        
//     }
// }

// int numDistinct(char* s, char* t) {

//     // // init node 
//     // Node *node = malloc( sizeof(Node));
    
//     unsigned long s_length = length(s);
//     unsigned long t_length = length(t);

//     printf("%lu\n", s_length);
//     printf("%lu\n", t_length);
    
//     // if (s_length == -1) {
//     //     // null-termination node found in string 
//     //     return  0;
//     // }
    
//     // if (strcmp(s, t) == 0) {
//     //     return 1;
//     // }

//     // init_node(node, s, s_length);
//     // int ret = search(node, s, s_length, t, t_length);

//     // return ret;

//     int *bitmask = calloc( (unsigned)s_length,  sizeof(int));
//     for (int i = 0; i < s_length; i++) {
//         bitmask[i] = 1;
//     }
    
//     int n_sequences = 0;

//     if (t_length == 1) {

//         for (int i = 0; i < s_length; i++) {
//             n_sequences += +(t[0] == s[i]);
//         }

//     } else if (t_length > 1) {

//         recursive_search(t, t_length, s, s_length, bitmask, &n_sequences);

//     }

//     return n_sequences; 

// }

TreeId *new_treeid_node (unsigned index, char c, int is_header) {
    TreeId *treeNode = malloc( sizeof(TreeId));
    treeNode->is_header = is_header;
    treeNode->index = index;
    treeNode->c = c;
    treeNode->next = NULL;
    treeNode->down = NULL;
    treeNode->next_targets = NULL;
    return treeNode ;
}

Targets *next_target (unsigned index, char c) {

     Targets *targetNode = malloc( sizeof(Targets));
     targetNode->c = c;
     targetNode->index = index;
     targetNode->next = NULL;

     return targetNode;
}

void print_next_targets (Targets *target) {
    while (target) {
        printf("\t<%c - %d>\t", target->c, target->index);
        target = target->next;
    }
}

void print_children (Vertex *vertexNode) {

    VertexList *children = NULL;
    
    if (vertexNode) {

        children = vertexNode->children;
        
    }

    printf("CHILDREN: ");
    while (children) {

        printf("< %c _ %lu > \t", children->vertex->c, children->vertex->index);

        children = children->next;
    }

    printf("\n");

}

void insert_tree(unsigned index, char c, TreeId *tree) {
    TreeId *prev = NULL;
    // find char
    while (tree) {

        if ( tree->is_header != 1 && tree->c == c && tree->index == index) {
            
            // found column of interest (char)
            
            TreeId *column_tree = tree;

            // add index row 
            while (column_tree->down) {
                column_tree = column_tree->down;
            }

            column_tree->down =   new_treeid_node(index, c, 0);



            if (prev) {


                
                if (prev->next_targets == NULL) {
                    prev->next_targets = next_target(index, c);
                } else {
                    Targets *targets = prev->next_targets;
                    while (targets->next) {
                        targets = targets->next;
                    }
                    targets->next = next_target(index, c);
                }

            }

            prev = NULL;
            tree = NULL;
            break; 

        } else {

            
            prev = tree; 
            tree = tree->next; // next column

        } 
    }

    if (prev != NULL) {
        
        // add new column 
        prev->next =  new_treeid_node(index, c, 0); 

        // add column 
        if (prev) {
            if (prev->next_targets == NULL) {
                prev->next_targets = next_target(index, c);
            } else {
                Targets *targets = prev->next_targets;
                while (targets->next) {
                    targets = targets->next;
                }
                targets->next = next_target(index, c);
            }
        }

    } else {
        
        return; 

    }

}

void init_vertices(Vertex **vertices, char *s, unsigned long len, TreeId *treeid, VertexList *ascii_vertices) {
    
    *vertices = malloc( sizeof(Vertex) * len );
    VertexList *vlist;

    for (unsigned i = 0; i < len; i++) {
        
        (*vertices + i)->c = s[i];
        (*vertices + i)->index = i;
        (*vertices + i)->children = NULL;

        vlist = (ascii_vertices  + s[i]);
            // printf(" OUTER CHAR %c\n", s[i]);

        if (!vlist->active) {
            
            vlist->vertex =  (*vertices + i);
            vlist->active = 1;
            vlist->next = NULL;
            vlist->stream_index = i;

        } else {

            while (vlist->next) {
                vlist = vlist->next; 
            }
            
            // if (vlist->next == NULL) {
            //     printf(" LADINGIN NEW\n");
            // }

            // printf(" INNER CHAR %c\t%p\n", s[i], vlist->next);
            
            vlist->next = calloc(1 , sizeof(VertexList));
            vlist->next->vertex =  (*vertices + i);
            vlist->next->active = 1;
            vlist->next->stream_index = i;
            vlist->next->next = NULL;


        }

        // insert_tree( i , s[i] , treeid );

    }

}

void print_treeid (TreeId *node) {

    printf("\nTREE DATA\n\n");

    while (node) {

        if (node->is_header) {

            printf("[header]  ");

        } else {

            printf("COLUMN CHAR [%c]\n", node->c);

            TreeId *ctree_node = node;
            TreeId *ctree_node_prev = node;

            while (ctree_node) {
                printf("ROW CHAR [%d]\n", ctree_node->index);
                ctree_node_prev = ctree_node;
                ctree_node = ctree_node->down;
            }

            if (ctree_node_prev) {
                printf("\n");
            }

            printf("TARGETS:\n");
            
            print_next_targets(node->next_targets);
            
            printf("\n\n\n");
        }

        node = node->next; 
    }

    printf("\n");
}

TreeId * get_node (TreeId *node, char c) {
    while (node) {
        if (node->c == c) {
            return node;
        }
        node = node->next; 
    }
    return NULL;
}

void print_vlist(VertexList *node) {
    printf("vlist: start:\n");

    while (node) {
        printf("[%c]-", node->vertex->c);
        node = node->next;
    }
    printf("\n");
    printf("vlist: end\n");

}

void print_vnlist(VNextList *node) {
    printf("\nvnlist: start\n");
    while (node) {
        // printf("[%c]-", node->vertex->c);
        print_vlist(node->vlist);
        node = node->next;
    }
    printf("vnlist: end\n\n");

}

void connect_nodes (char *s, unsigned long s_length, Vertex *vertices, TreeId *treeid, VNextList *occurVerticesNext) {
    Vertex *vertex = NULL;
    Vertex *prev_vertex = NULL; 
    char c_curr;
    char c_next; 
    VNextList * vnlist = NULL; 
    VertexList *vlist = NULL;
    VertexList *runner; 
    VertexList *child; 
    VertexList *new_vertex; 

    for (int i = 1; i < s_length; i++) {

        c_next = s[i];
        
        c_curr = s[i - 1];

        vnlist = (occurVerticesNext + c_curr);
        
        // printf("\n\n EVAL CHAR %c:\n", c_curr);
        // printf("\n\n INDEX WRITE %d :\n", i);

        while (vnlist) {
            #if 0
                print_vnlist(vnlist);
            #endif 
            runner = vnlist->vlist;
            while (runner) {

                if (runner->vertex->index >= i) {

                    new_vertex = calloc(1, sizeof(VertexList));
                    new_vertex->vertex = runner->vertex;
                    new_vertex->active = 1;
                    new_vertex->stream_index = runner->stream_index;
                    new_vertex->next = NULL;


                    if ( (vertices + (i-1) )->children == NULL ) {
                        
                        (vertices + (i-1) )->children = new_vertex;
                        
                    }  else {

                        child = (vertices + (i-1) )->children;
                        while (child->next) {
                            // moves to tail node
                            child = child->next;
                        }
                        // append to children list 
                        child->next = new_vertex; 

                    }
                }
                runner = runner->next; 
            }
            
            vnlist = vnlist->next;
        }

        #if 0
            print_children((vertices + (i-1) ));
        #endif 

        // assert(0);
        

        if (i == s_length - 1) {
            // set last 
        }
    }

}

void init_vlist(char *s, unsigned long s_length, VertexList *occurVertices ) {

        for (int i = 0; i < s_length; i++ ) {

        printf(  "%c\t is_active %u \n", (occurVertices + s[i])->vertex->c, (occurVertices + s[i])->active ); 

        VertexList *vlist = (occurVertices + s[i]);

        while (vlist) {
            printf( "%c_ %lu -  " , vlist->vertex->c, vlist->vertex->index);
            vlist = vlist->next; 
        }

        printf("\n");

    }

}

void init_vnext(char *t, unsigned long t_length, VertexList *occurVertices, VNextList *occurVerticesNext ) {
    char c;
    char c_prev;

    for (int i = 0; i < t_length; i++ ) {

        c = t[i];
        
        if (i) {

            // possible next paths
            VertexList *vlist = (occurVertices + c);

            if ( (occurVerticesNext + c_prev)->active == 0 ) {

                (occurVerticesNext + c_prev)->active = 1;
                (occurVerticesNext + c_prev)->vlist = vlist; // prev char possible paths to next char 
                (occurVerticesNext + c_prev)->next = NULL;
                
            } else {
                
                VNextList *vnextlist = (occurVerticesNext + c_prev);
                // printf("c_prev: %c\n", c_prev);
                while (vnextlist->next) {
                    vnextlist = vnextlist->next; 
                }
                vnextlist->next = calloc(1, sizeof(VNextList));
                vnextlist->next->active = 1;
                vnextlist->next->vlist = vlist; // prev char possible paths to next char 
                vnextlist->next->next = NULL;

            }

        }
        
        c_prev = c; 

    }

}

int search_helper(Vertex *vertexNode, unsigned long s_index, char * t, unsigned long t_length, unsigned index) {
    // return 0;

    VertexList *runnerList;
    int sum = 0;

    // printf("\t \t ENTEREND SEARCH HEPER  \n");
    
    if (index >= t_length) {
        printf(" %c -- %u\n", t[index - 1], index);
        // printf("based reached\n");
        return 1;
    }

    if (!vertexNode->children) {
        return 0;
    }
    
    // printf("\t \t ENTRY SEARCH HELPER -- INDEX  %u  %lu  NEXT CHAR %c \n", index, t_length, t[index]);

    runnerList = vertexNode->children ;

    #if 1
        print_children(vertexNode);
    #endif 


    while (runnerList) {
        
        printf("\t\t\t CHAR %c \n", runnerList->vertex->c);

        if (runnerList->vertex->c  == t[index]  && runnerList->vertex->index > s_index) {
            
            // if (index + 1 == 9) {

            //     printf("IS ACTIVE %d\n", runnerList->active);
            //     printf("IS ACTIVE %d\n", index);
            //     printf("IS ACTIVE %d\n", t_length);
            //     printf("IS ACTIVE %p\n", vertexNode->children);


            //     assert(0);
            // }
            
            sum += search_helper(runnerList->vertex,  (unsigned ) runnerList->vertex->index, t, t_length, index + 1);

        }

        // if (index + 1 == 9) {

        //     printf("%p", runnerList);
        //     printf("%p", runnerList->next);

        //     assert(0);
            
        // }

        runnerList = runnerList->next;
    }

    return sum;
 }

void print_atree (ATree *tree) {
    
    if (tree == NULL)
        return; 

    ANode *node = tree->head;

    while (node) {
        printf("%c - %d\n", node->c, node->eval_count);
        node = node->next; 
    }

}
 int search(Vertex *vertices,  unsigned long s_length, char * t, unsigned long t_length) {
    int count = 0;
    Vertex *root;
    int n  = 0;
    
    ATree *atree = NULL;
    ANode *node = NULL;
    ANode *runner = NULL;
    ANode *runner_prev= NULL;

    // find 
    for (unsigned  i = 0; i < s_length; i++) {

        if ( (vertices + i)->c == t[0] ) {
            n++;   

            //    #if 1
            //     printf("\t\t SEARCH FUNCTION-->  idx:  %lu  t-len:%lu  SEARCH CHAR %c \n", i, t_length, (vertices + i)->c );
            //     #endif 
            // // root = (vertices + i);
            // // count += search_helper(root, i,  t, t_length, 1);
            // // assert(0);
            
            node =  malloc(sizeof(ANode));
            node->c =  (vertices + i)->c ;
            node->index = i;
            node->next = NULL;
            node->s_length = s_length;
            node->t = t;
            node->t_length = t_length;
            node->offset = 1;
            node->eval_count = 1;

            
            if (atree == NULL) {
                atree = malloc(sizeof(ATree));
                atree->head = node;
                atree->tail = node;
            } else {
                atree->tail->next = node;
                atree->tail = node; 
            }
            
        }
    }

    
    runner = atree->head;
    int k = 0;
    
    while (atree->head != NULL) {
        runner = atree->head;
        runner_prev = NULL;
        k = 0;
                printf(" :-------: \n");

        while (runner) {

            if ( runner->index + runner->offset >= s_length) {
                k++;
                printf("FIRST WINNER: %d \n", runner->index);
            
            } else {
                
                if ( (vertices + runner->index + runner->offset )->c == t[node->eval_count]) {
                    runner->eval_count++;
                }
                
                runner->offset++;
                
                if (runner->eval_count == t_length) {
                    runner->eval_count = 1; 
                }
                
            }
            runner_prev = runner; 
            runner = runner->next;

        }

        if (k == n)
            break;
    }

    printf("%d potential starts \n", n);

    // print_atree(atree);

    // search_helper(vertices + )
    return count; 
 }

 int child_exists(ENode *node, unsigned long s_index , char *s, unsigned long s_length) {
    // while (node) {
    //     if (node->c == s[index] ) {
    //         return true;
    //     }
    //     node = node->next;
    // }
    // return false;
    return 1;
 }

 void viewer (ENode *node) {

    ENode *runner = node;

    // while (node) {
        
    //     runner = node; 

    //     while (runner) {
    //         printf("%c\n", runner->c);
    //         runner = runner->next;
    //     }


    //     node = node->children;

    // }

}


 void solver(ENode *root, char *t, unsigned long t_length, char *s, unsigned long s_length) {

    unsigned long target_index = 0; 
    unsigned long parent_pos = root->index;
    unsigned long parent_pos_tmp;

    unsigned long child_pos = parent_pos; 
    unsigned long child_pos_next;
    char c_next;
    int inner_match_found ;
    int count = 0; 

    ENode *node = root;

    printf("WELCOMSE ROOT ADDRESS %p\n\n", node);
    
    while (parent_pos < s_length) {

        while (child_pos < s_length) {
    
            child_pos_next = child_pos + 1;
            // target_index controlled 
    
            c_next = t[target_index + 1];
            inner_match_found = -1;

            // test next
    #if 0

            printf("test evaluation \n"); 
            printf("c_next target: %c \n", c_next); 
            printf("child analyzer position = %lu -->  %c \n", child_pos_next, s[child_pos_next]); 
            printf("----\n"); 
    #endif 

            // current node expects 
            node->expect = c_next;

            // found char path (matching char in sequence)
            if (s[child_pos_next] == c_next) {

    #if 0

                printf(" match found \n"); 
    #endif 
                
                // child  match-slot not used 
                if ( (node->children + child_pos_next)->enabled != 1  ) {
                    (node->children + child_pos_next)->enabled= 1;
                    (node->children + child_pos_next)->index = child_pos_next;
                    (node->children + child_pos_next)->children_size= node->children_size;
                    (node->children + child_pos_next)->depth= node->depth + 1;
                    (node->children + child_pos_next)->prev= node;
                    (node->children + child_pos_next)->c= c_next;
                    (node->children + child_pos_next)->children = calloc(s_length, sizeof(ENode));
                    
                    
                    inner_match_found = 1;
    #if 0
                    
                    printf("address of drop down %p\n", node->children + child_pos_next );

    #endif 

                    node = (node->children + child_pos_next);


    #if 0

                    printf(" current address address %p\n", node);

                    // if (node->children == NULL) {
                    //     node->children = enode;
                    // } else {
                    //     // node->next = enode; // TBD
                    // }
                    printf("current match \n"); 
                    printf("%lu\n", child_pos_next); 
                    printf("%c\n", c_next);
                    printf("----\n"); 
    #endif 
                    
                    // move to next target char
                    
                    target_index++;
                    c_next = t[target_index];

                    if (target_index + 1  >= t_length) { 
                            count++;
    #if 0
                        
                        printf(" FULL MATCH FOUND \n\n");
    #endif 

                        
                        // viewer(root);
    #if 0
        
                        printf("go back previous\n");
                        printf("previous target SOF %lu\n", target_index - 1);
                        printf("previous node address   %p\n", node->prev);
                        printf("previous node->char  %c\n", node->prev->c);
                        printf("previous index (child)  %lu \n", node->prev->index);
                        printf("previous enabled  %lu \n", node->prev->enabled);
        
                        printf("\n\n");
        
    #endif 
                      

                        child_pos = s_length - 1;
        
                    }    

                } else {
    #if 0

                    printf(" match USED -- child pos %lu\n", child_pos); 
    #endif

                }

            }

            if (child_pos >= s_length - 1) {

                if (node == root) {

                    
                    // find next parent pos 
                    
                    // move to next root->c 
                    parent_pos_tmp = parent_pos;
                    
                    while (parent_pos++ < s_length) {
                        
                        if (s[parent_pos] == root->c) {
                            
    #if 0

                            printf(" NEW PARENT POSITION %lu \t COUntER = %d \t  INDEX %d \n", parent_pos, count, node->index ); 

    #endif 
                            // change root/master node 
                            ENode *tmp_enode = root; 
                            // free all branches from tmp_enode (TBD)
                            // free children nodes (TBD) 

                            root->children = calloc(s_length, sizeof(ENode));
                            root->index = parent_pos;
                            target_index = 0;
                            node = root;

    #if 0

                            printf("-------------------------------------------------------------------------------------------------------\n");
    #endif 
                            break;

                        }

                    }

                    // update child
                    child_pos = parent_pos;


                } else {

                    // set target 
                    target_index--;
                    
                    // set child pos 
                    child_pos = node->prev->index;
                    
                    // set node 
                    node = node->prev;
                }

            } else {

                child_pos++;

            }

    
        }
        
   

    }

                            printf("------------------------------------------------------------------------------------------------------- %d \n", count);


 }


int numDistinct(char* s, char* t) {

    // // init node 
    // Node *node = malloc( sizeof(Node));
    
    unsigned long s_length = length(s);
    unsigned long t_length = length(t);
    int n_sequences = 0;

    printf("%lu\t%s\n", s_length, s);
    printf("%lu\t %s\n", t_length, t);
    
    // if (s_length == -1) {
    //     // null-termination node found in string 
    //     return  0;
    // }
    
    if (strcmp(s, t) == 0) {
        return 1;
    }

    if (t_length == 0 || s_length == 0) {
        return 0;
    }

    for (int i = 0; i < t_length; i++) {
        printf("%c", t[i]);
    }
    printf("\n");

    for (int i = 0; i < s_length; i++) {
        printf("%c", s[i]);
    }

    printf("\n");

   


    // find first t in s 
    int first_char_find = -1;

    for (int i = 0; i < s_length; i++ ) {
        if (s[i] == t[0]) {
            first_char_find = i;
            printf("%d\n", first_char_find);
            // break;
        }
    }

    assert(0);

    if (first_char_find == -1)
        return 0;

    // create leaf/root node
    ENode enode_root  = {
        .c = s[first_char_find], 
        .index = (unsigned long ) first_char_find,
        .children_size = s_length,
        .children = calloc(s_length, sizeof(ENode)),
        .depth =0,
        .prev = NULL,
        .enabled = 1,
        .expect ='\0'

    }; 


    solver(&enode_root, t, t_length, s, s_length);


    return first_char_find;
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