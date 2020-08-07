
typedef enum boolean
{
  false,
  true
} boolean;

struct BTNode
{
  int value;
  struct BTNode *left;
  struct BTNode *right;
  struct BTNode *parent;
};

struct BST
{
  struct BTNode *root;
};

struct TreeNodeData
{
  int value;
  boolean valid;
};
struct BTNode *btnode_alloc(int value);
struct BST *bts_alloc();

void BST_add(struct BST **tree, int value);
void BST_add_node(struct BTNode **node, int value);
boolean BST_contains(struct BTNode *node, int value);
struct TreeNodeData BST_min(struct BTNode *node);
struct TreeNodeData BST_min(struct BTNode *node);
int BST_size(struct BTNode *node);
int BST_is_empty(struct BST **tree);

int BST_height(struct BST **tree);
unsigned BST_height_node(struct BTNode *node);
int BST_is_balanced(struct BST **tree);
int BST_is_balanced_helper(struct BTNode *node);

struct BST *BST_array_to_bst(int *array, int size);

int BST_common_ancestor(struct BST **tree, int val_a, int val_b);
int BST_common_ancestor_helper(struct BTNode *node, int val_a, int val_b);

void BST_traverse_pre_order(struct BST **tree);
void BST_traverse_pre_order_helper(struct BTNode *node);

void BST_traverse_post_order(struct BST **tree);
void BST_traverse_post_order_helper(struct BTNode *node);

void BST_traverse_in_order(struct BST **tree);
void BST_traverse_in_order_helper(struct BTNode *node);

struct bst_to_array_data
{
  int *array;
  int size;
};

void bst_to_array_data_insert(struct bst_to_array_data *obj, int data);

struct bst_to_array_data BST_to_array(struct BST **tree);
void BST_to_array_helper(struct bst_to_array_data *obj, struct BTNode *node, int mode);
struct bst_to_array_data BST_to_array_pre(struct BST **tree);
struct bst_to_array_data BST_to_array_post(struct BST **tree);

struct BST_LL_NODE
{
  int value;
  struct BST_LL_NODE *next;
};

struct BST_LL_NODE *BST_to_list(struct BST **tree, int mode);
void BST_to_list_helper(struct BTNode *node, struct BST_LL_NODE **llnode, int mode);
void BST_LL_NODE_INSERT(struct BST_LL_NODE **node, int data);
void BST_LL_NODE_INSERT_STACK(struct BST_LL_NODE **node, int data);

struct BST_LL_NODE *allocate_BST_LL_NODE(int data);
struct BST_LL_NODE *BST_to_list_pre(struct BST **tree, int mode);
struct BST_LL_NODE *BST_to_list_post(struct BST **tree, int mode);

int BST_min_height(struct BST **tree);
void BST_min_height_helper(struct BTNode *node, int depth, int *min);

void BST_traverse_preOrder_no_recursion(struct BST **tree);

void BST_remove(struct BST **tree, int value);
void BST_remove_helper(int value, struct BTNode **node, struct BTNode *prev);
struct BTNode *BST_removal_successsor(struct BTNode *node);
// struct BTNode *BST_successsor(struct BTNode *node);

void BST_remove_all(struct BST **tree);
void BST_remove_all_helper(struct BTNode **node, struct BTNode *prev);

boolean BST_is_valid(struct BST **tree);
boolean BST_is_valid_helper(struct BTNode *node);
boolean BST_is_valid_helper_loop_test(struct BTNode *node);

void BST_add_no_dupes(struct BST **tree, int value);
void BST_add_node_no_dupes(struct BTNode **node, int value);

void BST_reverse_order(struct BTNode *root);
int BST_val_before(int val, struct BTNode *node);
int BST_val_after(int val, struct BTNode *node);
struct BTNode *node_before(struct BTNode *node);
struct BTNode *node_after(struct BTNode *node);
int closest_value(int value, struct BTNode *node);
int tree_path_contains_sum(int target, struct BTNode *node);
int tree_path_contains_sum_helper(int target, struct BTNode *node, int acc);

void sum_of_bst_root_leaf_numbers(struct BTNode *node);
void sum_of_bst_root_leaf_numbers_helper(struct BTNode *node, int depth, int buffer);

void left_side_binary_tree(struct BST **tree);
void left_side_binary_tree_helper(struct BTNode *node, int *maxdepth, int depth);
