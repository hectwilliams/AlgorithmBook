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

int AVLTree_remove(struct AVLTree **tree , int value)
{
  int successor;
  struct AVLTree *node = *tree;
  void *del;
  int updateBalanceFlag = 0;

  if (node)
  {

    if (node->value == value)
    {
      if (node->left && node->right)
      {
        successor = inOrderSuccessor(node);
        updateBalanceFlag = AVLTree_remove(&node, successor);
        balanceFlag(node, &updateBalanceFlag, 1);   // always right side feedback
        node->value = successor;
      }

      else if (node->right)
      {
        del = node->right;
        copy_attributes(node, del);
        updateBalanceFlag = 1;
        free(del);
      }

      else if (node->left)
      {
        del = node->left;
        copy_attributes(node, del);
        updateBalanceFlag = -1;
        free(del);
      }

      else if (node->left == NULL && node->right == NULL)
      {
        del = (node);
        *tree = NULL;
        free(del);
      }
    }

    else if (value < node->value)
    {
      if (node->left)
      {
        if (node->left->value == value)
        {
          if (node->left->left && node->left->right)
          {
            successor = inOrderSuccessor(node->left);
            updateBalanceFlag = AVLTree_remove(&node->left, successor) ;
            balanceFlag(node, &updateBalanceFlag, 1);   // always right side feedback
            node->left->value = successor;
          }

           else if (node->left->right)
          {
            del = node->left->right;
            copy_attributes(node->left, del);
            updateBalanceFlag = -1;
            free(del);
            node->balance--;

          }

          else if (node->left->left)
          {
            del = node->left->left;
            copy_attributes(node->left, del);
            updateBalanceFlag = -1;
            free(del);
            node->balance--;
          }

          else if (node->left->left == NULL && node->left->right == NULL)  // LEAF
          {
            del = node->left;

            free(del);
            node->left = NULL;
            node->balance--;

            if (node->right)  // delete node has sibling - stop upward balance updates
            {
              updateBalanceFlag = 0;
            }
            else
            {
              updateBalanceFlag = -1;
            }
          }
        }

        else
        {
          updateBalanceFlag = AVLTree_remove(&node->left, value);
          // printf(" ---%d    %d ----\n  ", node->left->value, node->left->balance);
          balanceFlag(node, &updateBalanceFlag, -1);   // left side feedback
          return updateBalanceFlag;
        }
      }
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        if (node->right->value == value)
        {
          if (node->right->left && node->right->right)
          {
            successor = inOrderSuccessor(node->right);
            updateBalanceFlag = AVLTree_remove(&node->right, successor) ;  // feedback from deletion descendant
            balanceFlag(node, &updateBalanceFlag, 1);   // always right side feedback
            node->right->value = successor;
          }

          else if (node->right->right)
          {
            del = node->right->right;
            copy_attributes(node->right, del);
            updateBalanceFlag = 1;
            free(del);
            node->balance++;

          }

          else if (node->right->left)
          {
            del = node->right->left;
            copy_attributes(node->right, del);
            updateBalanceFlag = 1;
            free(del);
            node->balance++;

          }

          else if (node->right->left == NULL && node->right->right == NULL)  // LEAF
          {
            del = node->right;
            free(del);
            node->right = NULL;
            node->balance++;

            if (node->left)       // deleted node has has sibling - stop upward balance updates
            {
              updateBalanceFlag = 0;
            }
            else
            {
              updateBalanceFlag = 1;
            }
          }
        }

        else
        {
          updateBalanceFlag = AVLTree_remove(&node->right, value);
          balanceFlag(node, &updateBalanceFlag, 1);     // right side feedback
          return updateBalanceFlag;
        }
      }
    }

  }

  return updateBalanceFlag;
}

void balanceFlag(struct AVLTree *node, int *flag, int newFlag)
{
  if (node && flag)
  {

    if (*flag != 0)
    {
      if (AVLTree_balance_feedback_update(node, newFlag) == 0)
      {
        *flag = 0;      // turn balance upward update OFF
      }
      else
      {
        *flag = newFlag;
      }
    }
  }
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
    node->balance = (1 + AVLNode_height(node->left) )  ;
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

// int AVLTree_balanced_add(struct AVLTree **tree, int value)
// {
//   struct AVLTree *node = *tree;
//   int updated_subtree = 0;

//   if (*tree == NULL)
//   {
//     *tree = avlnode(value);
//   }
//   else
//   {

//     if (value < node->value )
//     {
//       if (node->left)
//       {
//         if (AVLTree_balanced_add(&node->left, value) )
//         {
//           if (node->left->balance < -1)
//           {
//             AVLTree_left_rotate(&node, node->left);
//             AVLTree_setNodeBalance(node);
//           }
//           else if (node->left->balance > 1)
//           {
//             AVLTree_right_rotate(&node, node->left);
//             AVLTree_setNodeBalance(node);
//           }
//           else
//           {
//             node->balance++;
//           }
//           return node->balance != 0;
//         }
//       }
//       else
//       {
//         node->balance++;
//         node->left = avlnode(value);
//         return node->balance != 0;
//       }
//     }

//     else if (value > node->value)
//     {
//       if (node->right)
//       {
//         if (AVLTree_balanced_add(&node->right, value))
//         {
//           if (node->right->balance < -1)
//           {
//             AVLTree_left_rotate(&node, node->right);
//             AVLTree_setNodeBalance(node);
//           }
//           else if (node->right->balance > 1)
//           {
//             AVLTree_right_rotate(&node, node->right);
//             AVLTree_setNodeBalance(node);
//           }
//           else
//           {
//             node->balance--;
//           }

//           return node->balance != 0;
//         }
//       }
//       else
//       {
//         node->balance--;
//         node->right = avlnode(value);
//         return node->balance != 0;
//       }
//     }

//     else if (value == node->value)
//     {
//       node->count++;
//     }

//     // ROOT NODE ANALYSIS
//     if (node->balance < -1)
//     {
//       AVLTree_left_rotate(tree, node);
//     }
//     else if (node->balance > 1)
//     {
//       AVLTree_right_rotate(tree, node);
//     }

//   }
//   return 0;

// }



// // int AVLTree_balanced_remove(struct AVLTree **tree, int value)
// // {
// //   static struct AVLTree *root_ref = NULL;
// //   int update_balance_feedback = 0;
// //   struct AVLTree *node = NULL;


// //   if (tree == NULL)
// //   {
// //     return 0;
// //   }

// //   node = *tree;

// //   // store root
// //   if (root_ref ==  NULL)
// //   {
// //     root_ref = *tree;
// //   }


// //   if (node)
// //   {
// //     if (node->value == value)
// //     {
// //       update_balance_feedback = AVLTree_remove_helper(NULL, tree);
// //     }

// //     else if ( value < node->value)
// //     {
// //       if (node->left)
// //       {
// //         if (node->left->value == value)
// //         {
// //          update_balance_feedback =  AVLTree_remove_helper(node, &node->left);
// //         }

// //         else
// //         {
// //           update_balance_feedback =  AVLTree_balanced_remove(&node->left, value); // recursion
// //         }

// //         if (update_balance_feedback)
// //         {
// //           if (node->left)
// //           {
// //             if (node->left->balance > 1)
// //             {
// //               AVLTree_right_rotate(&node, node->left);
// //               AVLTree_setNodeBalance(node);

// //             }

// //             else if (node->left->balance < -1)
// //             {
// //               AVLTree_left_rotate(&node, node->left);
// //               AVLTree_setNodeBalance(node);
// //             }
// //             else
// //             {
// //               node->balance--;
// //             }
// //           }
// //           else
// //           {
// //             node->balance--;
// //           }
// //         }
// //       }
// //     }

// //     else if (value > node->value)
// //     {
// //       if (node->right)
// //       {
// //         if (node->right->value == value)
// //         {
// //           update_balance_feedback =  AVLTree_remove_helper(node, &node->right);
// //         }
// //         else
// //         {
// //           update_balance_feedback =  AVLTree_balanced_remove(&node->right, value);  // recursion
// //         }

// //         if (update_balance_feedback)
// //         {
// //           if (node->right)
// //           {
// //             if (node->right->balance > 1)
// //             {
// //               AVLTree_right_rotate(&node, node->right);
// //               AVLTree_setNodeBalance(node);
// //             }

// //             else if (node->right->balance < -1)
// //             {
// //               AVLTree_left_rotate(&node, node->right);
// //               AVLTree_setNodeBalance(node);
// //             }
// //             else
// //             {
// //               node->balance++;
// //             }
// //           }
// //           else
// //           {
// //             node->balance++;
// //           }
// //         }
// //       }
// //     }
// //   }

// //    // reset root;
// //   if (root_ref ==  node)
// //   {
// //     if (node->balance > 1) {
// //       AVLTree_right_rotate(tree, node) ;
// //     }

// //     else if (node->balance < -1)
// //     {
// //       AVLTree_left_rotate(tree, node);
// //     }

// //     root_ref = NULL;
// //   }


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
  avl_remove_test_remove_x(50);
}






