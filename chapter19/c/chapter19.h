struct AVLTree
{
  int value;
  int balanace;
  struct AVLTree *left;
  struct AVLTree *right;
  int count;
};

void AVLTree_add(struct AVLTree **tree, int value);
int AVLTree_remove(struct AVLTree **tree, int value);
int AVLTree_remove_helper( struct AVLTree *parent, struct AVLTree **target);

