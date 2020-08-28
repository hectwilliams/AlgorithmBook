 enum boolean
{
  false,
  true
} boolean;

struct BST
{
  int value;
  struct BST *left;
  struct BST *right;
  struct BST *parent;
};

struct BST *btnode_alloc(int value);
void BST_display(struct BST **tree);
void BST_add(struct BST **tree, int value);
int BST_height(struct BST **tree);

void BST_contains(struct BST **tree, int value);
struct BST * BST_remove_successor(struct BST **tree);
void BST_remove(struct BST **tree, int value);
enum boolean BST_Full(struct BST **tree);
enum boolean BST_Complete(struct BST **tree);
