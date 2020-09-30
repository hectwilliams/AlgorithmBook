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

int main()
{
  struct AVLTree *tree = NULL;

  AVLTree_add(&tree, 10);
  AVLTree_add(&tree, 8);
  AVLTree_add(&tree, 12);

  display(tree);
}

