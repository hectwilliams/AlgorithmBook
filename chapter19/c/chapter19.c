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

// //   return update_balance_feedback;
// // }

// // void AVLTree_repair(struct AVLTree **tree)
// // {
// //   static struct AVLTree *root_ref = NULL;
// //   struct AVLTree *node;

// //   if (tree == NULL)
// //   {
// //     return;
// //   }

// //   node = *tree;

// //   if (root_ref == NULL)
// //   {
// //     root_ref = node;
// //   }

// //   if (node)
// //   {
// //     if (node->balance > 0)
// //     {
// //       AVLTree_repair(&node->left);

// //       if (node->left->balance > 1)
// //       {
// //         AVLTree_right_rotate(&node, node->left);
// //         AVLTree_setNodeBalance(node);
// //       }
// //       else if (node->left->balance < -1)
// //       {
// //         AVLTree_left_rotate(&node, node->left);
// //         AVLTree_setNodeBalance(node);
// //       }
// //     }
// //     else if (node->balance < 0)
// //     {
// //       AVLTree_repair(&node->right);

// //       if (node->right->balance > 1)
// //       {
// //         AVLTree_right_rotate(&node, node->right);
// //         AVLTree_setNodeBalance(node);

// //       }
// //       else if (node->right->balance < -1)
// //       {
// //         AVLTree_left_rotate(&node, node->right);
// //         AVLTree_setNodeBalance(node);
// //       }
// //     }

// //     else if (node->balance == 0)
// //     {
// //       return;
// //     }

// //     if (root_ref == node)
// //     {
// //       if (node->balance > 1)
// //       {
// //         AVLTree_right_rotate(tree, node);
// //       }
// //       else if (node->balance < -1)
// //       {
// //         AVLTree_left_rotate(tree, node);
// //       }
// //       root_ref = NULL;
// //     }

// //   }
// // }

struct RBTree *rbnode (const int value)
{
  struct RBTree *node = (struct RBTree *) malloc(sizeof(struct RBTree));
  node->color = 1;
  node->count = 1;
  node->left =  node->right = NULL;
  node->value = value;
  return node;
}

// int RBTree_contains(struct RBTree **tree, const int value )
// {
//   struct RBTree *node;

//   if (tree)
//   {
//     node = *tree;
//   }

//   if (node)
//   {
//     if (node->value == value)
//     {
//       return 1;
//     }

//     else if (value < node->value)
//     {
//       return RBTree_contains(&node->left, value);
//     }

//     else if (value > node->value)
//     {
//       return RBTree_contains(&node->right, value);
//     }
//   }

//   return 0;
// }

int RBTree_add(struct RBTree **tree, const int value)
{
  static struct RBTree **root_ref = NULL;
  struct RBTree *node = *tree;
  void *store_root_ptr = NULL;
  int acc = 0;

  if (*tree == NULL)
  {
    *tree = rbnode(value);
    (*tree)->color = 0;
    root_ref = tree;
  }
  else
  {
    store_root_ptr = *root_ref;

    if (value < node->value)
    {
      if (node->left)
      {
        acc = RBTree_add(&node->left, value);
        acc += node->left->color == 1;

        if (acc == 2 )  // red-black error
        {
          acc = 0;
          if (node->right == NULL)
          {
            if (node->left && node->left->left)
            {
              RBTree_translate(root_ref, node, 1);
            }
            else if (node->left && node->left->right)
            {
              RBTree_translate(root_ref, node, 2);
            }
          }
          else if (node->right->color ==  0)
          {
            if (node->left && node->left->left)
            {
              RBTree_translate(root_ref, node, 1);
            }
            else if (node->left && node->left->right)
            {
              RBTree_translate(root_ref, node, 2);
            }
          }
          else if (node->right->color)
          {
            RBTree_translate(root_ref, node, 0);
          }
        }
      }
      else
      {
        node->left = rbnode(value);
        acc = 1;
      }
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        acc = RBTree_add(&node->right, value);

        acc += node->right->color == 1;

        if (acc == 2 )  // red-black error
        {
          acc = 0;

          if (node->left == NULL)
          {
            if (node->right && node->right->right)
            {
              RBTree_translate(root_ref, node, 3);
            }
            else if (node->right && node->right->left)
            {
              RBTree_translate(root_ref, node, 4);
            }
          }

          else if (node->left->color == 0)
          {
            if (node->right && node->right->right)
            {
              RBTree_translate(root_ref, node, 3);
            }
            else if (node->right && node->right->left)
            {
              RBTree_translate(root_ref, node, 4);
            }
          }

          else if (node->left->color)
          {
            RBTree_translate(root_ref, node, 0);
          }
        }
      }
      else
      {
        node->right = rbnode(value);
        acc = 1;
      }
    }

    else if (value == node->value)
    {
      node->count++;
      acc =  0;
    }

    if (store_root_ptr != *root_ref)
    {
      root_ref = NULL;
    }

    if (node->color == 0)
    {
      acc = 0;
    }

  }
  return acc;
}


void RBTree_translate(struct RBTree **root, struct RBTree *node, int rotate_code)
{
  struct RBTree *c, *gc, *gc_l, *gc_r,*tree, *par = NULL;

  if (node)
  {
    par = findParent(  *root, node);

    switch (rotate_code)
    {
      case 0:

      node->color = 1;
      node->left->color = node->right->color  = 0 ;
      break;

    case  1:
    // LEEFT LEFT
      c = node->left;
      tree = c->right;

      c->right =node;
      node->left = tree;

      if ( par == NULL)
      {
        *root = c;
      }
      else if ( par->left == node)
      {
        par->left = c;
      }
      else if ( par->right == node)
      {
        par->right = c;
      }
      c ->color = 0;
      c->left->color = c->right->color = 1;
      break;

      case 2:
      // LEEFT RIGHT

        c = node->left;
        gc = node->left->right;
        gc_l = gc->left;
        gc_r = gc->right;

        gc->left = c;
        gc->right = node;
        node->left = gc_r;
        c->right = gc_l;

        gc->color = 0;
        c->color = 1;
        node->color = 1;

        if ( par == NULL)
        {
          *root = gc;
        }
        else if ( par->left == node)
        {
          par->left = gc;
        }
        else if ( par->right == node)
        {
          par->right = gc;
        }

        gc ->color = 0;
        gc->left->color = gc->right->color = 1;
        break;

      case 3:

        // RIGHT RIGHT

        c = node->right;
        tree = c->left;

        c->left = node;
        node->right = tree;

        if ( par == NULL)
        {
          *root = c;
        }
        else if ( par->left == node)
        {
          par->left = c;
        }
        else if ( par->right == node)
        {
          par->right = c;
        }

        c ->color = 0;
        c->left->color = c->right->color = 1;

        break;

      case 4:

      // RIGHT LEFT

        c = node->right;
        gc = node->right->left;
        gc_l = gc->left;
        gc_r = gc->right;

        gc->right = c;
        gc->left = node;
        node->right = gc_l;
        c->left = gc_r;

        if ( par == NULL)
        {
          *root = gc;
        }
        else if ( par->left == node)
        {
          par->left = gc;
        }
        else if ( par->right == node)
        {
          par->right = gc;
        }
        gc ->color = 0;
        gc->left->color = gc->right->color = 1;
        break;

      default:
        break;
    }
  }

  // ROOT MUST BE BLACK
  if (*root)
  {
    if((*root)->color == 1 )
    {
      (*root)->color = 0;
    }
  }

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

struct RBTree *findParent (struct RBTree *tree, struct RBTree *target)
{

  if (tree)
  {

    if (tree->left == target || tree->right == target)
    {
      return tree;
    }

    if (tree->left)
    {
      if ( target->value  < tree->value)
      {
        return findParent(tree->left, target);
      }
    }

    if (tree->right)
    {
      if (target->value > tree->value)
      {
        return findParent(tree->right, target);
      }
    }
  }

  return NULL;
}

int RBTree_height_valid(struct RBTree *node, int height)
{
  static int counter = 0;
  static int valid = 0;
  static int buffer = 0;
  int result = 0;

  if (node)
  {
    counter++;
    height += node->color == 0;
    RBTree_height_valid(node->left, height);
    RBTree_height_valid(node->right, height);
    counter--;
  }
  else  // BLACK (NULL)
  {
    height += 1;

    if (valid == 0)
    {
      buffer = height;
      valid = 1;
    }
    else if (buffer != height)
    {
      valid = 0;
    }
  }

  if (counter == 0)
  {
    buffer = 0;
    result = valid;
    valid = 0;
  }

  return result;
}

int RBTree_remove_helper(struct RBTree *parent, struct RBTree **target)
{
  struct RBTree *node = *target;
  struct RBTree *successor = NULL, *succesor_parent;

  if (node->count > 1)
  {
    node->count--;
  }
  else if (node->left == NULL && node->right == NULL)
  {
    successor = NULL;
  }
  else if (node->left && !node->right)
  {
    successor = node->left;
  }
  else if (node->right && !node->left)
  {
    successor = node->right;
  }
  else if (node->right && node->left)
  {
    if (node->right->left == NULL)
    {
      successor = node->right;
      successor->left = node->left;
    }
    else
    {
      succesor_parent = node->right;
      while (succesor_parent->left->left)
      {
        succesor_parent = succesor_parent->left;
      }
      successor = succesor_parent->left;
      succesor_parent->left = succesor_parent->left->left;

      successor->left = node->left;
      successor->right = node->right;
      successor->count = node->count;
    }
  }

  if (parent == NULL)
  {
    *target = successor;
  }
  else if (parent->left == node)
  {
    parent->left = successor;
  }
  else if (parent->right == node)
  {
    parent->right = successor;
  }

  return 0;
}

void RBTree_remove(struct RBTree **tree, int value)
{
  struct RBTree *node = NULL;
  int rebalance_code = 0;

  node = *tree;

  if (node)
  {
    if (node->value == value)
    {
      RBTree_remove_helper(NULL, tree);
    }
    else if ( value < node->value)
    {
      if (node->left)
      {
        if (node->left->value == value)
        {
          RBTree_remove_helper(node, &node->left);
        }
        else
        {
          RBTree_remove(&node->left, value);
        }
      }
    }
    else if (value > node->value)
    {
      if (node->right)
      {
        if (node->right->value == value)
        {
          RBTree_remove_helper(node, &node->right);
        }
        else
        {
          RBTree_remove(&node->right, value);
        }
      }
    }

    rebalance_code = RBTree_balance_check(node);
    printf("\ncode %d\n", rebalance_code);
  }



}

int RBTree_balance_check(struct RBTree *node)
{
  if (node)
  {
    if (node->left )
    {
      if (node->left->color)   // LEFT RED
      {
        if (node->left->left)
        {
          if (node->left->left->color)
          {
            return 1;   // LEFT RED -> LEFT RED
          }

        }

        if (node->left->right)
        {
          if (node->left->right->color)
          {
            return 2;  // LEFT RED -> RIGHT RED
          }
        }
      }

    }

    if (node->right)
    {
      if (node->right->color)
      {
        if (node->right->right)
        {
          if (node->right->right->color)
          {
            return 3;  // RIGHT RED RIGHT RED
          }
        }

        if (node->right->left)
        {
          if (node->right->left->color)
          {
            return 4;  /// RIGHT RED LEFT RED
          }
        }
      }

    }
  }
  return 0;
}


// void rbtree_test()
// {
//   struct RBTree *tree = NULL;
//   int  array[] = {3, 1, 5 , 7, 6, 8, 9, 10};
//   int size = sizeof(array) / sizeof(int);

//   RBTree_add(&tree, 3);
//   RBTree_add(&tree, 1);
//   RBTree_add(&tree, 5);
//   RBTree_add(&tree, 7);
//   RBTree_add(&tree, 6);
//   RBTree_add(&tree, 8);
//   RBTree_add(&tree, 9);
//   RBTree_add(&tree, 10);
//   RBTree_remove(&tree,6);
//   RBTree_display(tree);
//   printf("HEAD %d");
//   // printf ( " balanced red-black tree -> %d \n",  RBTree_height_valid(tree, 0) );
// }



int main()
{
  balanced_add_test();
}






