#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chapter11.h"

struct BTNode * btnode_alloc(int value)
{
  struct BTNode *node = (struct BTNode *) malloc(sizeof(struct BTNode));
  node->value = value;
  node->left = node->right = NULL;
  return node;
}

struct BST * bts_alloc()
{
  struct BST *tree = (struct BST *) malloc(sizeof(struct BST));
  return tree;
}

void BST_add_node(struct BTNode **node, int value)
{
  struct BTNode *curr = *node;

  if (*node == NULL)
  {
    *node = btnode_alloc(value);
    return;
  }

  else if (value < curr->value)
  {
    if (curr->left == NULL)
    {
      curr->left = btnode_alloc(value);
    }
    else
    {
      return BST_add_node(&curr->left, value);
    }
  }
  else
  {
    if (curr->right == NULL)
    {
      curr->right = btnode_alloc(value);
    }
    else
    {
      return BST_add_node(&curr->right, value);
    }
  }
}


void BST_add(struct BST **tree, int value)
{

  if (*tree == NULL)
  {
    *tree = bts_alloc(value);
    return BST_add_node( &(*tree)->root, value);

  }
  else if ((*tree)->root)
  {
    return BST_add_node( &(*tree)->root, value);
  }
}

void display(struct BTNode *node)
{
  if (node->left)
  {
    display(node->left);
  }

  printf(" \t [%d]\n", node->value);

  if (node->right )
  {
    display(node->right);
  }
}

boolean BST_contains(struct BTNode *node, int value)
{
  boolean result = false;

  if (node)
  {
    result = (value == node->value);

    if (node->right)
    {
      result |= BST_contains(node->right, value);
    }

    if (node->left)
    {
      result |= BST_contains(node->left, value);
    }
  }
  return result;
}


struct TreeNodeData BST_min(struct BTNode *node)
{
  struct TreeNodeData data = {.valid = false};
  if (node)
  {
    if (node->left)
    {
      return BST_min(node->left);
    }
    else
    {
      data.value = node->value;
      data.valid = true;
    }
  }
  return data;
}

void BST_min_test()
{

  /*

      5
    /   \
   1    100

  */

  struct BST *tree = NULL;
  BST_add(&tree, 5);
  BST_add(&tree, 100);
  BST_add(&tree, 1);
  BST_add(&tree, 0);

  struct TreeNodeData data;
  data = BST_min(tree->root);
  printf("\t [%d] [%d \n", data.value, data.valid);
}

struct TreeNodeData BST_max (struct BTNode *node)
{
  struct TreeNodeData data = {.valid = NULL};
  if (node)
  {
    if (node->right)
    {
      return BST_max(node->right);
    }
    else
    {
      data.valid = 1;
      data.value = node->value;
    }
  }
  return data;
}

void BST_max_test()
{
  /*

      5
    /   \
   1    100

  */
  struct BST *tree = NULL;
  BST_add(&tree, 5);
  BST_add(&tree, 100);
  BST_add(&tree, 1);

  struct TreeNodeData data;
  data = BST_max(tree->root);
  printf("\t [%d] [%d \n", data.value, data.valid);
}

int BST_size(struct BTNode *node)
{
  int sum = 0;

  if (node)
  {
    sum += 1;

    if (node->left)
    {
      sum += BST_size(node->left);
    }

    if (node->right)
    {
      sum += BST_size(node->right);
    }
  }
  return sum;
}

void BST_size_test()
{
  int total;
  struct BST *tree = NULL;
  BST_add(&tree, 5);
  BST_add(&tree, 100);
  BST_add(&tree, 1);
  BST_add(&tree, 1302);
  total = BST_size(tree->root);
  printf("\t [%d] \n", total);
}

int BST_is_empty(struct BST **tree)
{
  if (*tree)
  {
    if ((*tree)->root)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  return -1;
}

void BST_is_empty_test()
{
  struct BST *tree = NULL;
  BST_add(&tree, 5);
  BST_add(&tree, 100);
  BST_add(&tree, 1);
  printf(" is empty %d\n", BST_is_empty(&tree)); /* not empty */

  struct BST *tree2 = NULL;
  printf(" is empty %d\n", BST_is_empty(&tree2));   /* undefined*/

  struct BST *tree3 = bts_alloc();
  printf(" is empty %d\n", BST_is_empty(&tree3));  /*empty */

}

unsigned BST_height_node(struct BTNode *node)
{
  unsigned height_left = 0;
  unsigned height_right = 0;

  if (node)
  {
    if (node->left)
    {
      height_left = 1 + BST_height_node(node->left);
    }
    if (node->right)
    {
      height_right =  1 + BST_height_node(node->right);
    }
  }

  if (height_left == height_right)
  {
    return height_right;
  }
  if (height_right > height_left)
  {
    return height_right;
  }
  else
  {
    return height_left;
  }

}

int BST_height(struct BST **tree)
{
  if (*tree)
  {
    return BST_height_node((*tree)->root);
  }
  return -1;
}

void BST_height_test()
{
  struct BST *tree = NULL;
  BST_add(&tree, 5);
  BST_add(&tree, 100);
  BST_add(&tree, 2);
  BST_add(&tree, 1);
  BST_add(&tree, 0);

  int h = BST_height(&tree);
  printf("height [%d]\n", h);
}

int main()

{
  BST_height_test();
}

