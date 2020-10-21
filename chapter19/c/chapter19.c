#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "chapter19.h"
#include "avl_tests.h"

struct AVLTree *avlnode (int value)
{
  struct AVLTree *node = (struct AVLTree *) malloc(sizeof(struct AVLTree));
  node->value = value;
  node->balance = 0;
  node->count = 1;
  node->left = NULL;
  node->right = NULL;
  return node;
}

int AVLTree_add(struct AVLTree **tree, int value)
{
  struct AVLTree *node = *tree;
  if (*tree == NULL)
  {
    *tree = avlnode(value);
  }
  else
  {

    if (value < node->value )
    {
      if (node->left)
      {
        if (AVLTree_add(&node->left, value) )
        {
          node->balance++;
          return node->balance != 0;
        }
      }
      else
      {
        node->balance++;
        node->left = avlnode(value);
        return node->balance != 0;
      }
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        if (AVLTree_add(&node->right, value))
        {
          node->balance--;
          return node->balance != 0;
        }
      }
      else
      {
        node->balance--;
        node->right = avlnode(value);
        return node->balance != 0;
      }
    }

    else if (value == node->value)
    {
      node->count++;
    }

  }
  return 0;

}


int inOrderSuccessor (struct AVLTree *node)
{
  if (node)
  {
    node = node->right;
    while (node->left)
    {
      node = node->left;
    }
    return node->value;
  }
  return -1;
}

int AVLTree_removeHelper(struct AVLTree *node, struct AVLTree **parent)
{

  void *del = NULL;
  int isRoot = (*parent == node );
  int successor;
  int flag = 1;

  if (node->left && node->right)
  {
    successor = inOrderSuccessor(node);
    flag = AVLTree_remove(&node, successor);
    flag = balanceFlag(node, flag, 1);
    node->value = successor;
  }

  else if (node->right)
  {
    del = node->right;
    copy_attributes(node, del);
    if (!isRoot)
    {
      (*parent)->balance++;
    }
  }

  else if (node->left)
  {
    del = node->left;
    copy_attributes(node, del);
    if (!isRoot)
    {
      (*parent)->balance--;
    }
  }

  else if (node->left == NULL && node->right == NULL)
  {
    del = node;
    if (isRoot)
    {
      *parent = NULL;
    }

    else if ((*parent)->right == node)
    {
      (*parent)->balance++;
      (*parent)->right = NULL;

      if ((*parent)->left)
      {
        flag = 0;
      }
    }

    else if ((*parent)->left == node)
    {
      (*parent)->balance--;
      (*parent)->left = NULL;

      if ((*parent)->right)
      {
        flag = 0;
      }
    }
  }

  if (del)
  {
    free(del);
  }

  return flag;
}

int AVLTree_remove(struct AVLTree **tree , int value)
{
  struct AVLTree *node = *tree;
  int updateBalanceFlag = 0;

  if (node)
  {

    if (node->value == value)
    {
      updateBalanceFlag = AVLTree_removeHelper(node , &node);
    }

    else if (value < node->value)
    {
      if (node->left)
      {
        if (node->left->value == value)
        {
          updateBalanceFlag = AVLTree_removeHelper(node->left , &node);
        }

        else
        {
          updateBalanceFlag = AVLTree_remove(&node->left, value);
          updateBalanceFlag = balanceFlag(node, updateBalanceFlag, -1);   // left side feedback
        }
      }
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        if (node->right->value == value)
        {
          updateBalanceFlag = AVLTree_removeHelper(node->right , &node);
        }
        else
        {
          updateBalanceFlag = AVLTree_remove(&node->right, value);
          updateBalanceFlag = balanceFlag(node, updateBalanceFlag, 1);     // right side feedback
        }
      }
    }
  }

  return updateBalanceFlag;
}

int balanceFlag(struct AVLTree *node, int isValid, int level)
{
  int prevBalance = node->balance;

  if (isValid)
  {
    node->balance += level;

    if (prevBalance == 0)
    {
      isValid = 0;
    }
  }
  return isValid;
}

int AVLTree_balance_feedback_update(struct AVLTree *node, int code)
{
  int prevBalance = 9;

  if (node)
  {
    prevBalance = node->balance;
    switch (code)
    {
      case -1:
        node->balance -= 1;
        break;
      case 1:
        node->balance += 1;
      default:
        break;
    }
  }
  return prevBalance;
}

void copy_attributes (struct AVLTree *dest, struct AVLTree *src)
{
  if (dest && src )
  {
    dest->left =   src->left;
    dest->right =  src->right;
    dest->count =  src->count;
    dest->value =  src->value;
    dest->balance = src->balance;
  }
}

void display(struct AVLTree *tree)
{
  if (tree)
  {
    if (tree->left)
    {
      display(tree->left);
    }
    printf(" [val - %d  bal - %d ]  \n", tree->value, tree-> balance);
    if (tree->right)
    {
      display(tree->right);
    }
  }
}

int AVLNode_height(const struct AVLTree *node)   // logN
{
  if (node)
  {
    if (node->left == NULL && node->right == NULL)
    {
      return 0;
    }
    if (node->balance > 0 && node->left)
    {
      return 1 + AVLNode_height(node->left);
    }

    else if (node->balance < 0 && node->right)
    {
      return 1 + AVLNode_height(node->right);
    }

  }
  return 0;
}


int AVLTree_isBalanced (struct AVLTree *node)
{
    return abs (node->balance ) <= 1;
}


void calBalance(struct AVLTree *node)
{
  if (node)
  {
    node->balance = (1 + AVLNode_height(node->left)) - (1 + AVLNode_height(node->right)) ;
  }
}



void AVLTree_rightRotate_translate(struct AVLTree *target, struct AVLTree **parent)
{
  struct AVLTree *c, *t, *promo;

  promo = target->left;

  if (target->left->balance < 0)
  {
    promo = target->left->right;
    AVLTree_leftRotate(&target,target->left);
  }


  c = target->left;
  t = c->right;

  c->right = target;
  target->left = t;

  calBalance(target);
  calBalance(c);

  if (*parent == target)
  {
    *parent = promo;
  }
  else if ((*parent)->left == target)
  {
    (*parent)->left = promo;
  }
  else if ( (*parent)->right == target)
  {
    (*parent)->right = promo;
  }

}


/*
  RIGHT ROTATE
  case 1: left left imbalance   ( right rotate target  )
  case 2: left right imbalance (left rotate target's child   ,  right rotate target)
*/

void AVLTree_rightRotate(struct AVLTree **root, struct AVLTree *target)
{
  struct AVLTree *node = *root, *promote = NULL;

  if (node && target->left)
  {
    if (node == target)
    {
        AVLTree_rightRotate_translate (node, root);
    }

    else if (target->value < node->value)
    {
      if (node->left == target)
      {
          AVLTree_rightRotate_translate (node->left, &node);
      }
      else
      {
        AVLTree_rightRotate(&node->left, target);
      }
    }

    else if (target->value > node->value)
    {
      if (node->right == target)
      {
          AVLTree_rightRotate_translate (node->right, &node);
      }
      else
      {
        AVLTree_rightRotate(&node->right, target);
      }
    }
  }
}

void AVLTree_leftRotate_translate(struct AVLTree *target, struct AVLTree **parent)
{
  struct AVLTree *c, *t, *promo;

  promo = target->right;

  if (target->right->balance > 0)
  {
    promo = target->right->left;
    AVLTree_rightRotate(&target, target->right);
  }

  c = target->right;
  t = c->left;

  c->left = target;
  target->right = t;

  calBalance(target);
  calBalance(c);

  if (*parent == target)
  {
    *parent = promo;
  }
  else if ((*parent)->left == target)
  {
    (*parent)->left = promo;
  }
  else if ( (*parent)->right == target)
  {
    (*parent)->right = promo;
  }
}

/*
  LEFT ROTATE
  case 1: right right imbalance (left rotate target)
  case 2: right left imbalance (right rotate target's child, left rotate target)
   * asssumes target always has right
*/

void AVLTree_leftRotate(struct AVLTree **root, struct AVLTree *target)
{
  struct AVLTree *node = *root;

  if (node && target->right)
  {
    if ( node == target)
    {
        AVLTree_leftRotate_translate(node, root);
    }

    else if ( target->value < node->value )
    {
      if (node->left == target)
      {
          AVLTree_leftRotate_translate(node->left, &node);
      }
      else
      {
        AVLTree_leftRotate(&node->left, target);  // recur
      }
    }

    else if ( target->value > node->value)
    {
      if (node->right == target)
      {
          AVLTree_leftRotate_translate(node->right, &node);
      }
      else

      {
        AVLTree_leftRotate(&node->right, target);  // recur
      }
    }
  }
}

void AVLTree_balanceCheck(struct AVLTree *target, struct AVLTree **root)
{
  if (!target)
  {
    return;
  }
  if (target->balance > 1)
  {
    AVLTree_rightRotate(root, target);
  }

  else if (target->balance < -1)
  {
    AVLTree_leftRotate(root, target);

  }
}

int AVLTree_balancedAdd(struct AVLTree **root, int value)
{
  int ret = 0;
  static void *currRoot = NULL;

  if (*root == NULL)
  {
    *root = avlnode(value);
  }
  else
  {
    if (currRoot == NULL)
    {
      currRoot = *root;
    }

    if (value < (*root)->value )
    {
      if ((*root)->left)
      {
        if (AVLTree_balancedAdd( &(*root)->left, value) == 1)
        {
          (*root)->balance++;
        }
        AVLTree_balanceCheck((*root)->left, root);
      }
      else
      {
        (*root)->balance++;
        (*root)->left = avlnode(value);
      }
       ret =  (*root)->balance != 0;
    }

    else if (value > (*root)->value)
    {
      if ((*root)->right)
      {
        if (AVLTree_balancedAdd( &(*root)->right, value)  == 1)
        {
          (*root)->balance--;
        }
        AVLTree_balanceCheck((*root)->right, root);
      }
      else
      {
        (*root)->balance--;
        (*root)->right = avlnode(value);
      }
      ret =  (*root)->balance != 0;
    }

    else if (value == (*root)->value)
    {
      (*root)->count++;
    }
  }

  if (currRoot == *root)
  {
    AVLTree_balanceCheck(*root, root); // balance check root
    currRoot = NULL;
  }

  return ret;
}


int AVLTree_balanceRemove(struct AVLTree **root , int value)
{
  struct AVLTree *node = *root;
  static void *currRoot = NULL;


  int updateBalanceFlag = 0;

  if (node)
  {

    if (currRoot == NULL)
    {
      currRoot = *root;
    }

    if (node->value == value)
    {
      updateBalanceFlag = AVLTree_removeHelper(node , &node);
    }


    else if (value < node->value)
    {
      if (node->left)
      {
        if (node->left->value == value)
        {
          updateBalanceFlag = AVLTree_removeHelper(node->left , &node);
        }
        else
        {
          updateBalanceFlag = AVLTree_balanceRemove(&node->left, value);
          updateBalanceFlag = balanceFlag(node, updateBalanceFlag, -1);   // left side feedback
        }
      }
        AVLTree_balanceCheck(node->left, root);
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        if (node->right->value == value)
        {
          updateBalanceFlag = AVLTree_removeHelper(node->right , &node);
        }
        else
        {
          updateBalanceFlag = AVLTree_balanceRemove(&node->right, value);
          updateBalanceFlag = balanceFlag(node, updateBalanceFlag, 1);     // right side feedback
        }
      }
        AVLTree_balanceCheck(node->right,  root);
    }
  }

  if (currRoot == *root)
  {
    AVLTree_balanceCheck(*root, root);
    currRoot = NULL;
  }
  return updateBalanceFlag;
}

void AVLTree_repair(struct AVLTree **root)
{
  struct AVLTree *node = *root;

  if (node)
  {
    if (node->left)
    {
      AVLTree_repair(& node->left);
    }

    if (node->right)
    {
      AVLTree_repair(& node->right);
    }
  }

  if (node->left)
  {
    while (node->left->balance > 1 || node->left->balance < -1)
    {
      AVLTree_balanceCheck(node->left, root);
    }
    calBalance(node);
  }

  if (node->right)
  {
    while (node->right->balance > 1 || node->right->balance < -1)
    {
      AVLTree_balanceCheck(node->right, root);
    }
    calBalance(node);
  }

}

struct RBTreeObj *rbobj ()

{
  struct RBTreeObj *obj = (struct RBTreeObj *) malloc(sizeof(struct RBTreeObj));
  obj->root = obj->node = NULL;
  return obj;
}

struct RBTree *rbnode (const int value)
{
  struct RBTree *node = (struct RBTree *) malloc(sizeof(struct RBTree));
  node->color = 1;
  node->count = 1;
  node->left =  node->right = NULL;
  node->value = value;
  return node;
}

int RBTree_contains(struct RBTree **tree, const int value )
{
  struct RBTree *node;

  if (tree)
  {
    node = *tree;
  }

  if (node)
  {
    if (node->value == value)
    {
      return 1;
    }

    else if (value < node->value)
    {
      return RBTree_contains(&node->left, value);
    }

    else if (value > node->value)
    {
      return RBTree_contains(&node->right, value);
    }
  }

  return 0;
}

void RBTree_leftRotate(struct RBTree *target, struct RBTree *parentOfTarget,  struct RBTreeObj *obj)
{
  struct RBTree *c, *t;

  c = target->right;
  t = c->left;

  c->left = target;
  target->right = t;

  if (target == parentOfTarget)
  {
    obj->root = c;
  }
  else if (parentOfTarget->left == target)
  {
      parentOfTarget->left = c;
  }
  else if (parentOfTarget->right == target)
  {
      parentOfTarget->right = c;
  }
}

void RBTree_rightRotate(struct RBTree *target, struct RBTree *parentOfTarget,  struct RBTreeObj *obj)
{
  
  struct RBTree *c, *t;


  c = target->left;
  t = c->right;

  c->right = target;
  target->left = t;

  if (target == parentOfTarget)
  {
    obj->root = c;
  }
  else if (parentOfTarget->left == target)
  {
      parentOfTarget->left = c;
  }
  else if (parentOfTarget->right == target)
  {
      parentOfTarget->right = c;
  }
}

int RBTree_addhelper(int value, struct RBTree *node , struct RBTreeObj *obj)
{
  int redCount = 0;


  if ( value < node->value)
  {
    if ( node->left)
    {
      redCount += RBTree_addhelper(value, node->left, obj ) ;
    }
    else
    {
      node->left = rbnode(value);
      return 1 + node->color;
    }
  }

  else if (value > node->value)
  {
    if ( node->right)
    {
      redCount += RBTree_addhelper(value, node->right, obj) ;
    }
    else
    {
      node->right = rbnode(value);
      return 1 + node->color;
    }
  }

  else if (value == node->value)

  {
    node->count++;
  }

  // printf(" value %d   count %d\n" , node->value, redCount);

  RBTree_blackErrorCheck (redCount >= 2 , node, obj);

  if (node->color == 0 || redCount >= 2)
  {
    redCount = 0;
  }
  else
  {
    redCount += node->color;
  }

  return redCount;

}


void RBTree_add(struct RBTreeObj **obj, int value)
{

  if (*obj == NULL)
  {
    *obj = rbobj();
  }

  if ( (*obj)->root == NULL)
  {
    (*obj)->root = rbnode(value);
  }
  else
  {
    RBTree_addhelper(value, (*obj)->root, *obj );
  }
}


int RBTree_rotationCode(struct RBTree *target)
{
  int rotateTarget = 0;

  if (target->left)
  {

    if (target->right)
    {
      if (target->right->color)
      {
        return 5;
      }
    }
    if (target->left->left)
    {
      if (target->left->color  && target->left->left->color)
      {
        return 1;
      }
    }

    if (target->left->right)
    {
      if (target->left->color && target->left->right->color)
      {
        return 2;
      }
    }

  }

  if (target->right)
  {

    if (target->left)
    {
      if (target->left->color)
      {
        return 5;
      }
    }

    if (target->right->right)
    {
      if (target->right->color  && target->right->right->color)
      {
        return 3;
      }
    }

    if (target->right->left)
    {
      if (target->right->color && target->right->left->color)
      {
        return 4;
      }
    }

  }
    return 0;
}

void RBTree_blackErrorCheck( int hasImbalance , struct RBTree *target , struct RBTreeObj *obj )
{
  struct RBTree *promote = NULL, p;
  int op = 0;


  if (hasImbalance)
  {

    op = RBTree_rotationCode(target);

    printf("operation %s \n ", ((op == 5) ? "color flip" : "rotation") );

    switch (op)
    {
    case 1:
    /* right rotate */
      promote = target->left;

      printf("right rotate*\n");
      RBTree_rightRotate(target, findParent(target, obj->root), obj);
      break;

    case 2:
      promote = target->left->right;
      /*left rotate -> right rotate*/

      printf("left rotate*\n");
      RBTree_leftRotate(target->left, findParent(target->left, obj->root), obj);

      printf("right rotate*\n");
      RBTree_rightRotate( target , findParent(target, obj->root), obj);
      break;

    case 3:
      promote = target->right;
  /* left rotate*/

      printf("left rotate*\n");
      RBTree_leftRotate(target, findParent(target , obj->root), obj);
      break;

    case 4:
      promote = target->right->left;
      /* right rotate  --> left rotate */
      printf("right rotate*\n");
      RBTree_rightRotate(target->right, findParent(target->right, obj->root), obj);
      printf("left rotate*\n");
      RBTree_leftRotate(target, findParent(target, obj->root), obj);
      break;

    case 5:
      target->color ^= 1;
      target->left->color ^= 1;
      target->right->color ^= 1;
      break;

    default:
      break;
    }

    /* update color */
    if (promote != NULL)
    {
      promote->color = 0;
      promote->left->color = promote->right->color = 1;
    }
  }

  /* root must be black */
  obj->root->color = 0;
}

void RBTree_display(struct RBTree *node)
{
  if (node)
  {
    if (node->left)
    {
      RBTree_display(node->left);
    }

    printf("[node %d  color %s]\n", node->value, ((node->color) ? "red": "black" )  );

    if (node->right)
    {
      RBTree_display(node->right);
    }
  }
}

struct RBTree *findParent (struct RBTree *target , struct RBTree *node)
{

  if (node)
  {
    if (node == target)
    {
      return node;
    }

    else if (target->value < node->value)
    {
      if (node->left == target)
      {
        return node;
      }
      else if (node->left)
      {
       return  findParent(target, node->left);
      }
    }
    else
    {
      if (node->right == target)
      {
        return node;
      }
      else if (node->right)
      {
       return  findParent(target, node->right );
      }
    }
  }

  return NULL;
}

int RBTree_height (struct RBTree *node)
{

  if (node)
  {
    return  (node->color == 0) + RBTree_height(node->left);
  }
  else
  {
    return 1;
  }
}

int RBTree_isValid(struct RBTree *node)
{
  printf("hight left  %d  height right  %d   ",RBTree_height(node->left)  , RBTree_height(node->right)  );
  return RBTree_height(node->left) == RBTree_height(node->right);
}

void RBTree_remove(struct RBTreeObj **obj, int value)
{


}

int main()
{
  red_black_tree_test();
}






