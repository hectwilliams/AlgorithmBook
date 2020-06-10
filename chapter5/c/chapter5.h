typedef enum boolean {False, True} boolean;
typedef enum compare_state {less = -1, equal = 0, greater = 1, undefined = 2} compare_state;

typedef struct llnode{
  int val;
  struct llnode *next;
} llnode;

typedef struct {
  llnode *head;
} llist;

typedef struct {
  boolean valid;
  int data;
} return_data;

llist *LinkedList();
void sl_printNode (llist *llist);
void sl_print_list (llist *llist);
void sl_add_front (llist *list, int value);
boolean sl_contains (llist *list, int value);
llnode *sl_remove_front (llist *restrict  list);
unsigned sl_length (llnode *restrict node);
void sl_display (llnode *restrict node);
int sl_max(llnode *restrict node);
int sl_min(llnode *restrict node);
float sl_avg (llnode *restrict node);
llnode *sl_back(llnode *restrict node);
llist *sl_remove_back(llist *list);
llist * sl_add_back(llist *list, int value);
compare_state move_n_to_front_helper_cmp(llnode *a, llnode *b);
void move_min_to_front (llist *list );
void move_max_to_front (llist *list );
void sl_prepend_val(llist *list, int val, int before);
void sl_append_val (llist *list, int val, int after);
void sl_remove_val(llist *list, int val);
llist split_on_value (llist *list, int val);
llnode *remove_negatives(llnode *node);
llnode *concat(llnode *a, llnode *b);
llnode *partition(llnode *node, int val);
return_data second_largest_value (llnode *node);
llnode *copy (llnode *node);
llnode *delete_given_node(llnode *node);
llist *filter(llist *list, int low, int high);
return_data second_to_largest_value(llnode *node);
void dedupe(llist *list);
llnode *zip (llnode *a, llnode *b);