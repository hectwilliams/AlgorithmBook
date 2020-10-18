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
int AVLNode_height(const struct AVLTree *node);
int AVLTree_isBalanced (struct AVLTree *node);
int AVLTree_remove(struct AVLTree **tree , int value);
void AVLTree_leftRotate(struct AVLTree **root, struct AVLTree *target);
void AVLTree_rightRotate(struct AVLTree **root, struct AVLTree *target);

// avl tree: remove  helper
int AVLTree_removeHelper(struct AVLTree *node, struct AVLTree **parent);
int AVLTree_balance_feedback_update(struct AVLTree *node, int code);
int balanceFlag(struct AVLTree *node, int isValid, int level);
int inOrderSuccessor (struct AVLTree *node);
void copy_attributes (struct AVLTree *dest, struct AVLTree *src);


// avl tree: rotation helper
void calBalance(struct AVLTree *node);
void AVLTree_leftRotate_translate(struct AVLTree *target, struct AVLTree **parent) ;
void AVLTree_rightRotate_translate(struct AVLTree *target, struct AVLTree **parent);

// avl tree  helper
void balanceCheck(struct AVLTree *target, struct AVLTree **parent);


int AVLTree_balancedAdd(struct AVLTree **root, int value);

int AVLTree_balancedRemove(struct AVLTree **tree, int value);
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

void RBTree_remove(struct RBTree **tree, int value);
int RBTree_remove_helper(struct RBTree *parent, struct RBTree **target);
int RBTree_balance_check(struct RBTree *node);

#endif


