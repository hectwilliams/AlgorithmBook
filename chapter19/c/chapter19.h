struct AVLTree
{
  int value;
  int balance;
  struct AVLTree *left;
  struct AVLTree *right;
  int count;
};

int AVLTree_add(struct AVLTree **tree, int value);
int AVLTree_remove(struct AVLTree **tree, int value);
int AVLTree_remove_helper( struct AVLTree *parent, struct AVLTree **target);
int AVLTree_height( struct AVLTree **tree);
int AVLNode_height(const struct AVLTree *node);
int AVLTree_isBalanced (struct AVLTree *node);
void AVLTree_update_balance_path(struct AVLTree *node, struct AVLTree *stop) ;
void copy_attributes (struct AVLTree *successor, struct AVLTree *predecessor);

/* AVL Remove tree tests
*/


//  remove node with 1 child

void avl_remove_single_child_node_a ();  // refer to avl_remove_balanced.key  slide 1
void avl_remove_single_child_node_b ();  //  "                           "    slide 2
void avl_remove_single_child_node_c ();  //  "                           "    slide 3
