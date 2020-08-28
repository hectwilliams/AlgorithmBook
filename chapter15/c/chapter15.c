#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "chapter15.h"

struct BST *btnode_alloc(int value)
{
  struct BST *node = (struct BST *)malloc(sizeof(struct BST));
  node->value = value;
  node->parent = node->left = node->right = NULL;
  return node;
}

void BST_display(struct BST **tree)
{
  if (*tree)
  {
    if ((*tree)->left)
    {
      BST_display( &(*tree)->left);
    }

    printf(" %d |" , (*tree)->value);

    if ((*tree)->right)
    {
      BST_display( & (*tree)->right);
    }
  }
}

void BST_add(struct BST **tree, int value)
{
  struct BST *node = btnode_alloc(value);
  struct BST *curr = *tree;

  if (*tree == NULL)
  {
    *tree = node;
  }
  else
  {
    if (value < curr->value)
    {
      if (curr->left == NULL)
      {
        curr->left = node;
      }
      else
      {
        return BST_add( & curr->left,value);
      }
    }
    else
    {
      if (value >= curr->value)
      {
        if (curr->right == NULL)
        {
          curr->right = node;
        }
        else
        {
          BST_add(& curr->right, value);
        }
      }
    }
  }
}

int BST_height(struct BST **tree)
{
  int left = 0, right = 0;

  if ((*tree)->left)
  {
    left = 1 + BST_height( &(*tree)->left);
  }

  if ((*tree)->right)
  {
    right = 1 + BST_height( &(*tree)->right);
  }

  return left == right ? right : left;
}

struct BST * BST_remove_successor(struct BST **tree)
{
  struct BST *node = *tree;
  struct BST *prev = node;

  if (node->right)
  {
    node = node->right;
    while (node->left)
    {
      prev = node;
      node = node->left;
    }
  }

  if (prev->left == node)
  {
    prev->left = NULL;
  }
  else
  {
    prev->right = NULL;
  }
  return node;
}

void BST_remove(struct BST **tree, int value)
{
  static struct BST *prev = NULL, *succesor;

  if (*tree == NULL)
  {
    return;
  }

  if ( (*tree)->value == value )
  {
    if (!! (*tree)->left && !!(*tree)->right)
    {

    // find successor
      succesor = BST_remove_successor(tree);

    // link successor
        succesor->left = (*tree)->left;
        succesor->right= (*tree)->right;

    // update root node
      if (prev ==NULL)
      {
        *tree = succesor;
      }
    // update subtree
      else
      {
        if (prev->left == *tree)
        {
          prev->left = succesor;
        }
        else
        {
          prev->right = succesor;
        }
      }
    }
    else if ( !!(*tree)->left ^ !!(*tree)->right )
    {
      if (prev == NULL)
      // update root
      {
        if ((*tree)->left == NULL)
        {
          *tree = (*tree)->right;
        }
        else
        {
          *tree = (*tree)->left;
        }
      }
      else
      // update subtree
      {
        if (prev->left == *tree)
        {
          if ((*tree)->left == NULL)
          {
            prev->left = (*tree)->right;
          }
          else
          {
            prev->left = (*tree)->left;
          }
        }
        else if (prev->right == *tree)
        {
          if ((*tree)->left == NULL)
          {
            prev->right = (*tree)->right;
          }
          else
          {
            prev->right = (*tree)->left;
          }
        }
      }
    }
    else if ( (*tree)->left == NULL && (*tree)->right == NULL)
    {
      if (prev == NULL)
      {
        *tree = NULL;
      }
      else
      {
        if (prev->left == *tree)
        {
          prev->left = NULL;
        }

        else
        {
          prev->right = NULL;
        }
      }
    }
  }

  if (*tree)
  {
    if ((*tree)->left)
    {
      if ( value < (*tree)->value)
      {
        prev = *tree;
        BST_remove(&(*tree)->left, value);
      }
    }

    if ((*tree)->right)
    {
      if (value >= (*tree)->value)
      {
        prev = *tree;
        BST_remove(&(*tree)->right, value);
      }
    }
  }

  prev = NULL;
}


enum boolean BST_Full(struct BST **tree)
{
  enum boolean isFull = false;

  if ((*tree))
  {
    isFull = ( (*tree)->left && (*tree)->right ) ^ ((*tree)->left == NULL && (*tree)->right == NULL);
    printf("\n[%d]\n", isFull);
    if ((*tree)->left)
    {
      isFull &= BST_Full (&(*tree)->left);
    }

    if ((*tree)->right)
    {
     isFull &=  BST_Full (&(*tree)->right);
    }
  }
  return isFull;
}

enum boolean BST_Complete(struct BST **tree)
{

  enum boolean isComplete = false ;
  int left = 0, right = 0;
  struct BST *node = *tree;

  if (node)
  {

    if (node->left)
    {
      left = BST_height(&node->left);
    }

    if (node->right)
    {
      right = BST_height(&node->right) ;
    }

    isComplete = left >= right;

    if (node->left)
    {
      isComplete &= BST_Complete(&node->left);
    }

    if (node->right)
    {
     isComplete &=  BST_Complete(&node->right);
    }
  }

  return isComplete;

}

int main()
{
  struct BST *bst = NULL;
  BST_add(&bst, 32);
  BST_add(&bst, 17);
  BST_add(&bst, 28);
  BST_add(&bst, 23);
  BST_add(&bst, 29);

  BST_add(&bst, 49);
  BST_add(&bst, 2);

  BST_display(&bst);
  // BST_remove(&bst, 2);
  printf("\n") ;
  BST_display(&bst);

  printf(" \nis complete - %d \n ", BST_Complete(&bst) );
}