
#ifndef CHAPTER8_H
#define CHAPTER8_H

typedef enum boolean {False, True} boolean;

typedef struct return_data {
	boolean valid;
	int value;
} return_data;

typedef struct SLNode_t {
	int value;
	struct SLNode_t* next;
	struct SLNode_t* child;
} SLNode_t;

typedef struct SList_t {
	struct SLNode_t* head;
	struct SLNode_t* tail;
} SList_t;

struct addr_data {
	void **base;
	int count;
}addr_cpy;

SLNode_t *sl_node(int value);
SList_t *slist_malloc(void); /* allocate new node */
void slist_destruct_list(void);

void slist_enqueue (void *data, int value);
return_data slist_dequeue (void *data);
void  slist_display(void *data); 
SList_t *slist_sum_numerals (SList_t *a, SList_t *b);
void slist_flatten_children(SList_t *list);
void slist_unflatten_children(SList_t *list);
struct SList_t *slist_setup_loop(unsigned int count, unsigned int repeat_n);
boolean slist_has_loop(SLNode_t *node);
SLNode_t*  slist_loop_start (SLNode_t *node);
void slist_break_loop(SLNode_t *node);
unsigned int slist_number_of_nodes (SLNode_t *node );
void slist_swap_pairs(SList_t *list);
SList_t *slist_sl_list(); /* allocate linked list */


typedef struct DLNode_t {
	int value;
	struct DLNode_t* next;
	struct DLNode_t* prev;
} DLNode_t;

typedef struct DList_t {
	struct DLNode_t *head;
	struct DLNode_t *tail; 
} DList_t;

DList_t *dlist_malloc(void) ;
void dlist_destruct(void) ;

void dlist_push(DList_t *list, int value);
return_data dlist_pop(DList_t *list);
void dlist_display(struct  DList_t *list);
return_data dlist_front(struct DList_t *list);
return_data dlist_back(struct DList_t *list);
boolean dlist_contains(struct DList_t *list, int value);
unsigned int dlist_size(struct DList_t *list);
void dlist_prepend_value(struct DList_t *list, int new_value, int existing_value);
void dlist_append_value(struct DList_t *list, int new_value, int existing_value);
return_data dlist_kth_to_last_value(struct DList_t *list, unsigned int k);
void dlist_delete_middle_node(DLNode_t *dnode);
boolean dlist_is_valid(struct DList_t *list);
void dlist_partition(struct DList_t *list, int value);
boolean dlist_palindrome(struct DList_t *list);
void dlist_reverse(struct DList_t *list);
DLNode_t * dlist_loop_start(struct DList_t *list);
void dlist_break_loop(struct DList_t *list);
void dlist_repair(struct DList_t *list);
#endif
