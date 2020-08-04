
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