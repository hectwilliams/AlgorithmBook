struct AVLTree
{
  int value;
  int balanace;
  struct AVLTree *left;
  struct AVLTree *right;
  int count;
};



void AVLTree_add(struct AVLTree **tree, int value);

