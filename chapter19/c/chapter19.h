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
int AVLTree_height(const struct AVLTree **tree);