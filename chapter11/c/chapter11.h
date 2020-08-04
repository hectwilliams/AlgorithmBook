
typedef enum boolean {false, true} boolean;


struct BTNode
{
  int value;
  struct BTNode *left;
  struct BTNode *right;
} ;

struct BST
{
  struct BTNode *root;
};

struct TreeNodeData
{
  int value;
  boolean valid;
};
struct BTNode * btnode_alloc(int value);
struct BST * bts_alloc();

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
int BST_is_balanced_helper(struct BTNode*node);

struct BST *BST_array_to_bst (int *array, int size);

int BST_common_ancestor(struct BST **tree, int val_a, int val_b);
int BST_common_ancestor_helper( struct BTNode *node, int val_a, int val_b);

void BST_traverse_pre_order(struct BST **tree);
void BST_traverse_pre_order_helper(struct BTNode *node);

void BST_traverse_post_order(struct BST **tree);
void BST_traverse_post_order_helper(struct BTNode *node);

void BST_traverse_in_order(struct BST **tree);
void BST_traverse_in_order_helper(struct BTNode *node);