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
void AVLTree_balanceCheck(struct AVLTree *target, struct AVLTree **parent);


int AVLTree_balancedAdd(struct AVLTree **root, int value);
int AVLTree_balanceRemove(struct AVLTree **root, int value);
void AVLTree_repair(struct AVLTree **root);

struct RBTree
{
  int value;
  int color;
  struct RBTree *left;
  struct RBTree *right;
  int count;
};

struct RBTreeObj
{
  struct RBTree *root;
  struct RBTree *node;
};

struct RBTree *rbnode (const int value);
struct RBTreeObj *rbobj ();

void RBTree_display(struct RBTree *node);
int RBTree_contains(struct RBTree **tree, const int value);

void RBTree_add(struct RBTreeObj **obj, int value);
int RBTree_addhelper(int value, struct RBTree *node , struct RBTree *parent, struct RBTreeObj *obj); // helper
int RBTree_height (struct RBTree *node);  // helper


void RBTree_leftRotate(struct RBTree *target, struct RBTree *parentOfTarget,  struct RBTreeObj *obj);
void RBTree_rightRotate(struct RBTree *target, struct RBTree *parentOfTarget  ,struct RBTreeObj *obj);
void RBTree_blackErrorCheck( int hasImbalance , struct RBTree *target , struct RBTree *parent , struct RBTreeObj *obj ); // helper avl add
int RBTree_rotationCode(struct RBTree *target); // helper avl add

struct RBTree *findParent (struct RBTree *tree, struct RBTree *target);

int RBTree_successor (struct RBTree * node);
void RBTree_copyAttr (struct RBTree *dest, struct RBTree *src);
void RBTree_remove(struct RBTreeObj **obj, int value);
void RBTree_remove_(int value, struct RBTree *node, struct RBTree *parent, struct RBTreeObj *obj);
void RBTree_remove_helper(struct RBTree *target, struct RBTree *parent, struct RBTreeObj *obj);
void RBTree_remove_helper_balance(struct RBTree *u, int dir, struct RBTree *p, struct RBTreeObj *obj);

void swap(void *a, void *b, int mode);
#endif


