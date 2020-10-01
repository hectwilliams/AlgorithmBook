#include "chapter19.h"
#include <stdio.h>
#include <stdlib.h>

struct AVLTree *avlnode (int value)
{
  struct AVLTree *node = (struct AVLTree *) malloc(sizeof(struct AVLTree));
  node->value = value;
  node->balanace = 0;
  node->count = 1;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void AVLTree_add(struct AVLTree **tree, int value)
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
        return AVLTree_add(&node->left, value);
      }
      else
      {
        node->left = avlnode(value);
      }

    }

    else if (value > node->value)
    {
      if (node->right)
      {

        return AVLTree_add(&node->right, value);
      }
      else
      {
        node->right = avlnode(value);
      }
    }

    else if (value == node->value)
    {
      node->count++;
    }

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
    printf(" %d ", tree->value);
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


  AVLTree_add(&tree, 11);
  AVLTree_add(&tree, 14);
  AVLTree_add(&tree, 4);
  AVLTree_add(&tree, 6);

  // AVLTree_remove(&tree, 8);
  // display(tree); // expect 4  6  10  11  12  14


  AVLTree_add(&tree, 1);

  // AVLTree_remove(&tree,4);
  // display(tree); // expect  1  6  8  10  11  12  14

  AVLTree_remove(&tree, 10);
  display(tree); //expect  1  4  6  8  11  12  14

  printf("\n");
}

