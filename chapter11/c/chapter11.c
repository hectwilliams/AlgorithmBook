#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chapter11.h"
#include  <math.h>

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

  if (curr == NULL)
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
    *tree = bts_alloc();
    return BST_add_node( & (*tree)->root, value);
  }

  return BST_add_node( &(*tree)->root, value);
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

int BST_is_balanced_helper(struct BTNode *node)
{
  int left = 0;
  int right = 0;

  if (node == NULL)
  {
    return 1;
  }

  if (node)
  {
    left  = BST_height_node(node->left);
    right  = BST_height_node(node->right);
    return (
      abs(left - right) <= 1) && BST_is_balanced_helper(node->left) && BST_is_balanced_helper(node->right);
  }

}

int BST_is_balanced(struct BST **tree)
{
  if (*tree)
  {
    return BST_is_balanced_helper ((*tree)->root );
  }
  return -1;
}

void BST_is_balanced_test()
{
 struct BST *tree = NULL;
  BST_add(&tree, 5);
  BST_add(&tree, 100);
  BST_add(&tree, 2);
  BST_add(&tree, 1);
  BST_add(&tree, 0);
  printf("is balanaced   %d\n", BST_is_balanced(&tree));
}

struct BST *BST_array_to_bst (int *array, int size)
{
  struct BST *tree = bts_alloc();
  int lpos, rpos;

  lpos = size / 2;
  rpos = lpos + 1;

  while (1)
  {

    if (lpos >= 0)
    {
      BST_add(&tree, array[lpos--]);
    }

    if (rpos < size)
    {
      BST_add(&tree, array[rpos++]);
    }

    if (lpos < 0 && rpos >= size)
    {
      break;
    }
  }
  return tree;
}

void BST_array_to_bst_test()
{
  int array[] = {1,2,3,4,5};
  struct BST *tree = BST_array_to_bst(array, sizeof(array)/ sizeof(array[0]));

  printf("  [%d]  [%d]  [%d]  [%d]   [%d] \n",

  tree->root->left->left->value,    // 1
  tree->root->left->value,  // 2
  tree->root->value,   // 3
  tree->root->right->value,  // 4
  tree->root->right->right->value  // 5
  );

}

int main()
{
  BST_array_to_bst_test();
}

