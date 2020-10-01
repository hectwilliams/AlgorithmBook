#include "chapter19.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
  int bal = 0;


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
        bal = AVLTree_add(&node->left, value) ;
      }
      else
      {
        node->balance++;
        node->left = avlnode(value);
        return 1;
      }
    }

    else if (value > node->value)
    {
      if (node->right)
      {

        bal = AVLTree_add(&node->right, value);
      }
      else
      {
        node->balance--;
        node->right = avlnode(value);
        return -1;
      }
    }

    else if (value == node->value)
    {
      node->count++;
    }

    node->balance += bal;
  }

  return bal;

}

void display(struct AVLTree *tree)
{
  if (tree)
  {
    if (tree->left)
    {
      display(tree->left);
    }
    printf(" [val - %d  bal - %d ]  ", tree->value, tree-> balance);
    if (tree->right)
    {
      display(tree->right);
    }
  }
}

int AVLTree_remove_helper( struct AVLTree *parent, struct AVLTree **target)
{
  struct AVLTree *node = *target, *ancestor = NULL, *runner = NULL;

  if (node->count > 1)
  {
    node->count--;
    return 1;
  }

  if (node->left == NULL && node->right == NULL)
  {
    if (parent == NULL)
    {
      *target = NULL;
    }
    else if (parent->left == node)
    {
      parent->left = NULL;
    }
    else if (parent->right == node)
    {
      parent->right = NULL;
    }
  }

  else if (node->left != NULL && node->right == NULL)
  {
    if (parent == NULL)
    {
      *target = node->left;
    }
    else if (parent->left == node)
    {
      parent->left = node->left;
    }
    else if (parent->right == node)
    {
      parent->right = node->left;
    }
  }

  else if (node->right != NULL && node->left == NULL)
  {
    if (parent == NULL)
    {
      *target = node->right;
    }
    else if (parent->left == node)
    {
      parent->left = node->right;
    }
    else if (parent->right == node)
    {
      parent->right = node->right;
    }
  }

  else if (node->right != NULL && node->left != NULL)
  {
    if (node->right->left == NULL)
    {
      node->right->left = node->left;

      if (parent == NULL)
      {
        *target = node->right;
      }
      else if (parent->left == node)
      {
        parent->left = node->right;
      }
      else if (parent->right == node)
      {
        parent->right = node->right;
      }
    }
    else
    {
      runner = node->right;
      while (runner->left->left)
      {
        runner = runner->left;
      }
      ancestor = runner->left;
      runner->left = runner->left->left;

      ancestor->left = node->left;
      ancestor->right = node->right;

      if (parent == NULL)
      {
        *target = ancestor;
      }
      else if (parent->left == node)
      {
        parent->left = ancestor;
      }
      else if (parent->right == node)
      {
        parent->right = ancestor;
      }
    }
  }

  free(node);

  return 1;
}

int AVLTree_remove(struct AVLTree **tree, int value)
{
  struct AVLTree *node = NULL, *prev = NULL;

  // validate pointer
  if (tree == NULL)
  {
    return 0;
  }

  node = *tree;

  if (node)
  {
    if (node->value == value)
    {
     return  AVLTree_remove_helper(NULL, tree);
    }
    else if ( value < node->value)
    {
      if (node->left)
      {
        if (node->left->value == value)
        {
         return AVLTree_remove_helper(node, &node->left);
        }
        else
        {
          return AVLTree_remove(&node->left, value);
        }
      }
    }
    else if (value > node->value)
    {
      if (node->right)
      {
        if (node->right->value == value)
        {
          return AVLTree_remove_helper(node, &node->right);
        }
        else
        {
          return AVLTree_remove(&node->right, value);
        }
      }
    }
  }
  return 0;
}

int AVLTree_height(struct AVLTree **tree)
{
  int hleft = 0, hright = 0;

  if (tree == NULL)
  {
    return  -1;
  }

  if (*tree)
  {

    if ((*tree)->left != NULL)
    {
      hleft += 1 + AVLTree_height (&(*tree)->left);
    }

    if ((*tree)->right != NULL)
    {
      hright += 1 + AVLTree_height(& (*tree)->right);
    }
  }

  if (hleft > hright)
  {
    return hleft;
  }
  else
  {
    return hright;
  }
}

int AVLNode_height(const struct AVLTree *node)
{
  int hleft = 0, hright = 0;
  if (node)
  {
    if (node->left != NULL)
    {
      hleft = 1 + AVLNode_height(node->left);
    }
    if (node->right != NULL)

    {
      hright = 1 + AVLNode_height(node->right);
    }
  }

  if (hleft > hright)
  {
    return hleft;
  }
  else {
    return hright;
  }
}

int AVLTree_isBalanced (struct AVLTree *node)
{
  int height_left = 0, height_right = 0;

  if (!node)
  {
    return - 1;
  }

  if (node)
  {
    if (node->left)
    {
      height_left = AVLNode_height(node->left);
    }

    if (node->right)
    {
      height_right = AVLNode_height(node->right);
    }
  }


  if ( abs(height_left - height_right)  <= 1 )
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

int main()
{
  struct AVLTree *tree = NULL;

  AVLTree_add(&tree, 10);

  AVLTree_add(&tree, 8);
  AVLTree_add(&tree, 12);

  // AVLTree_remove(&tree, 10);
  // display(tree); // expect 8 12

  // AVLTree_remove(&tree, 8);
  // display(tree); // expect 10 12

  // AVLTree_remove(&tree, 12);
  // display(tree); // expect 8 10


  // AVLTree_add(&tree, 11);
  // AVLTree_add(&tree, 14);
  // AVLTree_add(&tree, 4);
  // AVLTree_add(&tree, 6);

  // AVLTree_remove(&tree, 8);
  // display(tree); // expect 4  6  10  11  12  14


  AVLTree_add(&tree, 1);
  // AVLTree_add(&tree, 0);
  // AVLTree_remove(&tree,4);
  // display(tree); // expect  1  6  8  10  11  12  14
//
  // AVLTree_remove(&tree, 10);
  display(tree); //expect  1  4  6  8  11  12  14
  printf("\n");
  printf(" [height %d] " , AVLNode_height(tree->left));
  printf(" [balanced -  %d] " , AVLTree_isBalanced(tree) );

}

