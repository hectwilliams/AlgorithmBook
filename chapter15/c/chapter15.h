 enum boolean
{
  false,
  true
} boolean;

struct LL
{
  int depth;
  void *node;
  struct LL *next;
};

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

enum boolean bstRepair(struct BST **tree);
void bstRepairReinsert(struct BST *src, struct BST **dest);
void BST_addNode (struct BST *node, struct BST **tree);
int BST_smallest_difference(struct BST **tree);
struct BST *partition_evenly (struct BST **tree);
void BST_reverse (struct BST **tree);
int BST_kthBiggest(struct BST **tree, int k);
void BST_print_value_for_layer(struct BST **tree,int layer);

