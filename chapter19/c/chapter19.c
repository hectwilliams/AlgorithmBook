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

int RBTree_addhelper(int value, struct RBTree *node , struct RBTree *parent, struct RBTreeObj *obj)
{
  int redCount = 0;


  if ( value < node->value)
  {
    if ( node->left)
    {
      redCount =  RBTree_addhelper(value, node->left, node, obj ) ;
      redCount += node->left->color;
    }
    else
    {
      node->left = rbnode(value);
      return 1 ;
    }
  }

  else if (value > node->value)
  {
    if ( node->right)
    {
      redCount = RBTree_addhelper(value, node->right, node, obj) ;
      redCount += node->right->color;
    }
    else
    {
      node->right = rbnode(value);
      return 1 ;
    }
  }

  else if (value == node->value)

  {
    node->count++;
    return 0;
  }

  // printf(" value %d   count %d\n" , node->value, redCount);

  RBTree_blackErrorCheck (redCount >= 2 , node, parent,  obj);

  if (node->color == 0 || redCount >= 2)
  {
    return 0;
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
    RBTree_addhelper(value, (*obj)->root, (*obj)->root, *obj );
  }
}


int RBTree_rotationCode(struct RBTree *target)
{
  int left = 0, right = 0;

  if (target->left == NULL)
  {
    left = 0;
  }
  else if (target->left->color )
  {
    left = 1;
  }

  if (target->right == NULL)
  {
    right = 0;
  }
  else if (target->right->color)
  {
    right = 1;
  }

  if (target->left)
  {

    if (target->left->left)
    {
      if (target->left->color  && target->left->left->color)
      {
        if (right)
        {
          return 5;
        }
        return 1;
      }
    }

    if (target->left->right)
    {
      if (target->left->color && target->left->right->color)
      {
        if (right)
        {
          return 5;
        }
        return 2;
      }
    }

  }

  if (target->right)
  {

    if (target->right->right)
    {
      if (target->right->color  && target->right->right->color)
      {
        if (left)
        {
          return 5;
        }
        return 3;
      }
    }

    if (target->right->left)
    {
      if (target->right->color && target->right->left->color)
      {
        if (left )
        {

          return 5;
        }
        return 4;
      }
    }

  }
    return 0;
}

void RBTree_blackErrorCheck( int hasImbalance , struct RBTree *target , struct RBTree *parent , struct RBTreeObj *obj )
{
  struct RBTree *promote = NULL, p;
  int op = 0;


  if (hasImbalance)
  {
    op = RBTree_rotationCode(target);

    switch (op)
    {
    case 1:
      promote = target->left;

      // right rotate target
      RBTree_rightRotate(target, parent, obj);
      break;

    case 2:
      promote = target->left->right;

      // left rotate target
      RBTree_leftRotate(target->left, target, obj);

      // right rotate target
      RBTree_rightRotate( target , parent , obj);
      break;

    case 3:
      promote = target->right;

      // left rotate target
      RBTree_leftRotate(target, parent, obj);
      break;

    case 4:
      promote = target->right->left;

      // right rotate sibling
      RBTree_rightRotate(target->right, target, obj);

      // left rotate target
      RBTree_leftRotate(target, parent, obj);
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
  struct RBTree *a = NULL, *b = NULL;

  if (node->left)
  {
    a = findParent(target, node->left);
  }

  if (node->right )
  {
    b = findParent(target, node->right);
  }

  if (node->left == target )
  {
    return node;
  }

  if (node->right == target)
  {
    return node;
  }

  if (a)
  {
    return a;
  }

  return b;

}

int RBTree_successor (struct RBTree * node)
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

  return 0;

}

void RBTree_copyAttr (struct RBTree *dest, struct RBTree *src)
{
  if (src && dest)
  {
    dest->left = src->left;
    dest->right = src->right;
    dest->count = src->count;
    dest->value = src->value;
  }
}

void RBTree_remove(struct RBTreeObj **obj, int value)
{
  RBTree_remove_(value, (*obj)->root,  (*obj)->root, *obj);
}

void RBTree_remove_(int value, struct RBTree *node, struct RBTree *parent, struct RBTreeObj *obj)
{

  if (node)
  {
    if (value == node->value)
    {
      if (node->count > 1)
      {
        node->count--;
      }
      else
      {
        RBTree_remove_helper(node, parent, obj);
      }
    }

    else if (value < node->value && node->left)
    {
      RBTree_remove_(value, node->left ,node,  obj);
    }

    else if (value > node->value && node->right)
    {
      RBTree_remove_(value, node->right, node, obj);
    }

  }

}

void RBTree_remove_helper(struct RBTree *target, struct RBTree *parent, struct RBTreeObj *obj)
{
  int isDoubleBlack;
  int successor;

  if ( target->left && target->right)
  {
    successor = RBTree_successor(target) ;
    RBTree_remove(&obj, successor);
    target->value = successor;
  }

  else if (target->left)
  {
    isDoubleBlack = (target->color || target->left->color) == 0;
    RBTree_copyAttr(target, target->left);

    if ( ! isDoubleBlack )
    {
      target->color = 0;
    }
    else
    {
      RBTree_remove_helper_balance(target, 1, parent, obj);
    }
  }

  else if (target->right)
  {
    isDoubleBlack = (target->color || target->right->color) == 0;
    RBTree_copyAttr(target, target->right);

    if ( ! isDoubleBlack )
    {
      target->color = 0;
    }
    else
    {
      RBTree_remove_helper_balance(target, -1, parent, obj);
    }
  }

  else if (!target->right && !target->left)
  {
    isDoubleBlack = (target->color == 0);

    if (obj->root == target)
    {
      obj->root = NULL;
    }

    else if (parent->left == target)
    {
      parent->left = NULL;

      if ( isDoubleBlack )
      {
        RBTree_remove_helper_balance(NULL, 1, parent, obj);
      }
    }

    else if (parent->right == target)
    {
      parent->right = NULL;

      if ( isDoubleBlack )
      {
        RBTree_remove_helper_balance(NULL, -1, parent, obj);
      }
    }
  }

}

void RBTree_remove_helper_balance(struct RBTree *u, int dir, struct RBTree *p, struct RBTreeObj *obj)
{
  struct RBTree *s = NULL /* sibling node */, *pp /* sparent of parent node */;
  int sibColorLeft = -1, sibColorRight = -1, sibColor = -1;
  int tmp = -1;

  if (obj->root == u)
  {
    if (obj->root)
    {
      obj->root->color = 0;
    }
    return;
  }

  if (dir == -1)
  {
    s = p->left;
  }

  if (dir == 1)
  {
    s = p->right;
  }


  // sibling data
  if (s)
  {

    sibColor = s->color;

    if (s->left)
    {
      sibColorLeft = s->left->color;
    }
    else
    {
      sibColorLeft = 0;
    }

    if (s->right)
    {
      sibColorRight = s->right->color;
    }
    else
    {
      sibColorRight = 0;
    }

  }


  if (sibColor == 0)
  {

    if (sibColorLeft == 0 && sibColorRight == 0)  /* CASE SIBLING BLACK WITH BLACK CHILDREN */
    {
      // recolor sibling
      s->color = 1;

      // red parent
      if (p->color == 1)
      {
        p->color = 0;
      }

      // black parent
      else if (p->color == 0)
      {
         u = p;
         p = findParent(p, obj->root);

         if (p->left == u)
         {
           dir = 1;
         }

         if (p->right == u)
         {
           dir = -1;
         }

         return RBTree_remove_helper_balance(u, dir, p, obj);
      }
    }


    else if (sibColorLeft == 1 && sibColorRight == 1)
    {
      if (dir == -1) // LEFT LEFT
      {
        // SWAP COLORS OF PARENT AND SIBLING NODE
        swap(s, p, 0);

        // SET SIBLING CHILD BLACK
        s->left->color = 0;

        // RIGHT ROTATE PARENT
        pp = findParent(p, obj->root);
        RBTree_rightRotate(p, pp, obj);

        return;
      }

      if (dir == 1) // RIGHT RIGHT
      {
        // SWAP COLORS OF PARENT AND SIBLING NODE
        swap(s, p, 0);

        // SET SIBLING CHILD BLACK
        s->right->color = 0;

        // LEFT ROTATE PARENT
        pp = findParent(p, obj->root);
        RBTree_leftRotate(p, pp, obj);

        return;
      }

    }

    else if (sibColorLeft == 1)     /* CASE SIBLING BLACK WITH RED CHILD */
    {

      if (dir == -1)  // LEFT LEFT CASE
      {
        // SET SIBLING CHILD BLACK
        s->left->color = 0;

        // SWAP COLORS BETWEEM PARENT AND SIBLING
        swap(s, p, 0);

        // RIGHT ROTATION PARENT
        pp = findParent(p, obj->root) ;
        RBTree_rightRotate(p, pp, obj);
        return;
      }

      if (dir == 1) // right left case
      {
        // SET SIBLING RED
        s->color = 1;

        // SET SIBLING CHILD BLACK
        s->left->color = 0;

        // RIGHT ROTATE SIBLING
        RBTree_rightRotate(s, p, obj);

        // CASE RECURSION
        RBTree_remove_helper_balance(u, dir, p, obj);
      }

    }

    else if (sibColorRight == 1)  /* CASE SIBLING BLACK WITH RED CHILD */
    {

      if (dir == 1)  // RIGHT RIGHT CASE
      {
        // SET SIBLING CHILD BLACK
        s->right->color = 0;

        // EXCHANGE BETWEEN COLOR AND PARENT
        swap(s, p, 0);

        // LEFT ROTATE PARENT
        pp = findParent(p, obj->root) ;
        RBTree_leftRotate( p, pp, obj);
      }

      if (dir == -1)  // left right case
      {
        // SET SIBLING RED
        s->color = 1;

        // SET SIBLING CHILD BLACK
        s->right->color = 0;

        // LEFT ROTATE SIBLING
        RBTree_leftRotate(s, p, obj);

        // RECURSION
        RBTree_remove_helper_balance(u, dir, p, obj);
      }

    }

  }

  if (sibColor == 1)  /* CASE SIBLING RED */
  {
    // EXCHANGE COLORS BETWEEN PARENT AND SIBLING
    swap(s, p, 0);


    // RIGHT IMBALANCE
    if (dir == 1)
    {

      // LEFT ROTATE PARENT
      pp = findParent(p, obj->root);
      RBTree_leftRotate(p, pp, obj);

      // RECURSION
      RBTree_remove_helper_balance(p->left, 1, p, obj);

    }


    // LEFT IMBALANCE
    if (dir == -1)
    {
      // RIGHT ROTATE PARENT
      pp = findParent(p, obj->root);
      RBTree_leftRotate(p, pp, obj);

      //  RECURSION
      RBTree_remove_helper_balance(p->right, -1, p, obj);
    }

  }

}

void swap(void *a, void *b, int mode)
{
  void *tmp = NULL;

  enum SELECT_MODE {
    RBNODE_COLORS
  };

  switch (mode)
  {

  case RBNODE_COLORS:  // swap RBTree nodes colors

    tmp = & ((struct RBTree* )a)->color ;

    ((struct RBTree*) a)->color =  ((struct RBTree*) b)->color ;
    ((struct RBTree*) b)->color = *((int *) tmp);

    break;

  default:
    break;
  }
}



int main()
{
  red_black_tree_test();
}






