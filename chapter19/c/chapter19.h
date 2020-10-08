#ifndef CHAPTER19_H
#define CHAPTER19_H

struct AVLTree
{
  int value;
  int balance;
  struct AVLTree *left;
  struct AVLTree *right;
  int count;
};

void display(struct AVLTree *tree);
int AVLTree_add(struct AVLTree **tree, int value);
int AVLTree_remove(struct AVLTree **tree, int value);
int AVLTree_remove_helper( struct AVLTree *parent, struct AVLTree **target);
int AVLNode_height(const struct AVLTree *node);
int AVLTree_isBalanced (struct AVLTree *node);
void AVLTree_update_balance_path(struct AVLTree *node, struct AVLTree *stop) ;
void copy_attributes (struct AVLTree *successor, struct AVLTree *predecessor);

void AVLTree_left_rotate(struct AVLTree **tree, struct AVLTree *target);
void AVLTree_right_rotate(struct AVLTree **tree, struct AVLTree *target);
void AVLTree_grandchild_promote(struct AVLTree *parent);
void AVLTree_setNodeBalance(struct AVLTree *node); // set 'balance' attribute

#endif
