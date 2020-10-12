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

struct AVLTree *avlnode (int value);
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

int AVLTree_balanced_add(struct AVLTree **tree, int value);
int AVLTree_balanced_remove(struct AVLTree **tree, int value);
void AVLTree_repair(struct AVLTree **tree);


struct RBTree
{
  int value;
  int color;
  struct RBTree *left;
  struct RBTree *right;
  int count;
};

struct RBTree *rbnode (const int value);
int RBTree_contains(struct RBTree **tree, const int value);
int RBTree_add(struct RBTree **tree, const int value);
void RBTree_repaint(struct RBTree *parent);

void RBTree_display(struct RBTree *node);

void RBTree_translate(struct RBTree **root, struct RBTree *node, int rotate_code);
struct RBTree *findParent (struct RBTree *tree, struct RBTree *target);
int RBTree_height_valid(struct RBTree *node, int height);

struct llist
{
  int value;
  struct llist *next;
};
#endif

/*
          100
         /    \
       50      300
      /
     25
*/