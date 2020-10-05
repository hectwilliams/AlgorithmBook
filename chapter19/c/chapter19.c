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
  struct AVLTree *node = *target, *successor = NULL, *runner = NULL, *successor_parent;

  if (node->count > 1)
  {
    node->count--;
    return 0;   // no updates to upstream nodes

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


    if (parent)
    {
      return 1;
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

    // update upstream node balance
    if (parent)
    {
      return 1; // update upstream node balance
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

    if (parent)
    {
      return 1; // update upstream node balance
    }

  }

  else if (node->right != NULL && node->left != NULL)
  {

    if (node->right->left == NULL)
    {
      // successor connected to predecessor

      successor = node->right;

      // update heir's parent's balance
        node->balance++;

      // promote heir ( ascend throne )
      {
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

        // copy predecessor attributes (right and value not included)
        successor->left = node->left;
        successor->balance = node->balance;

        if (successor->balance == 0)
        {
          return 1;  // update upstream node balance
        }

      }

    }

    else
    {
      // successor is always leaf node

      // find heir (i.e. successor )
      {
        successor_parent = node->right;
        while (successor_parent->left->left)
        {
          successor_parent = successor_parent->left;
        }
        successor = successor_parent->left;
      }

      // update heir's parent's balance
      {
        if (successor_parent->left == successor)
        {
          successor_parent->balance--;
        }

        if (successor_parent->right == successor)
        {
          successor_parent->balance++;
        }
      }

      // remove heir from heir's parent
      {
        successor_parent->left = successor_parent->left->left;  //  note: successor_parent->left->left = NULL
      }

      // update path balance ( from: predecessor(include) -> to: successor's parent(exclude) )
      {
        AVLTree_update_balance_path(node, successor_parent);
      }

      // promote heir ( ascend throne )
      {
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

        copy_attributes(successor, node);
      }

      if (successor_parent->balance == 0)
      {
        return 1;   // update upstream node balance
      }

    }

  }

  free(node);

  return 0;
}

/*
  copy predecessor attributes to successor (exclude value)
*/
void copy_attributes (struct AVLTree *successor, struct AVLTree *predecessor)
{
  if (successor && predecessor )
  {
    successor->left = predecessor->left;
    successor->right = predecessor->right;
    successor->balance = predecessor->balance;
    successor->count = predecessor->count;
  }
}

void AVLTree_update_balance_path(struct AVLTree *node, struct AVLTree *stop) // node (i.e start node)
{

  if (node && stop)
  {
    while (node != stop)
    {
      if (stop->value < node->value)
      {
        node->balance--;
        return AVLTree_update_balance_path(node->left, stop);
      }
      else
      {
        node->balance++;
        return AVLTree_update_balance_path(node->right, stop);
      }
    }
  }

}

int AVLTree_remove(struct AVLTree **tree, int value)
{
  int update_balance_feedback = 0;
  struct AVLTree *node = NULL, *prev = NULL;

  if (tree == NULL)
  {
    return 0;
  }

  node = *tree;

  if (node)
  {
    if (node->value == value)
    {
      update_balance_feedback = AVLTree_remove_helper(NULL, tree);
    }

    else if ( value < node->value)
    {
      if (node->left)
      {
        if (node->left->value == value)
        {
         update_balance_feedback =  AVLTree_remove_helper(node, &node->left);
        }
        else
        {
          update_balance_feedback =  AVLTree_remove(&node->left, value);
        }

        if (update_balance_feedback)
        {
          node->balance--;
        }
      }
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        if (node->right->value == value)
        {
          update_balance_feedback =  AVLTree_remove_helper(node, &node->right);
        }
        else
        {
          update_balance_feedback =  AVLTree_remove(&node->right, value);
        }

        if (update_balance_feedback)
        {
          node->balance++;
        }
      }
    }
  }

  return update_balance_feedback;
}

int AVLTree_height(struct AVLTree **tree)
{
  int hleft = 0, hright = 0;

  if (tree == NULL)
  {
    return  0;
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

void avl_remove_single_child_node_a ()
{
  struct AVLTree *tree = NULL;

  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 50);
  AVLTree_add(&tree, 25);
  AVLTree_add(&tree, 70);

  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 100); // delete root node
  display(tree);

  /*
    inOrder list:

    initial tree values
    [val - 25  bal - 0 ]
    [val - 50  bal - 0 ]
    [val - 70  bal - 0 ]
    [val - 100 bal - 2 ]

    mutated tree values
    [val - 25  bal - 0 ]
    [val - 50  bal - 0 ]
    [val - 70  bal - 0 ]

  */
}

void avl_remove_single_child_node_b ()
{
  struct AVLTree *tree = NULL;

  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 50);
  AVLTree_add(&tree, 25);
  AVLTree_add(&tree, 27);
  AVLTree_add(&tree, 16);

  display(tree);
  // printf("\n");
  // AVLTree_remove(&tree, 50); // delete root node
  // display(tree);

  /*
    [val - 16  bal - 0 ]
    [val - 25  bal - 0 ]
    [val - 27  bal - 0 ]
    [val - 50  bal - 0 ]
    [val - 100  bal - 1 ]

  */

}



int main()
{
  avl_remove_single_child_node_b();
//   /*
//     refer to
//   */
//   AVLTree_add(&tree, 100);
//   AVLTree_add(&tree, 50);
//   AVLTree_add(&tree, 25);
//   AVLTree_add(&tree, 70);

//   // AVLTree_remove(&tree, 10);
//   // display(tree); // expect 8 12

//   // AVLTree_remove(&tree, 8);
//   // display(tree); // expect 10 12

//   // AVLTree_remove(&tree, 12);
//   // display(tree); // expect 8 10


//   // AVLTree_add(&tree, 11);
//   // AVLTree_add(&tree, 14);
//   // AVLTree_add(&tree, 4);
//   // AVLTree_add(&tree, 6);

//   // AVLTree_remove(&tree, 8);
//   // display(tree); // expect 4  6  10  11  12  14


//   AVLTree_add(&tree, 1);
//   // AVLTree_add(&tree, 0);
//   // AVLTree_remove(&tree,4);
//   // display(tree); // expect  1  6  8  10  11  12  14
// //
//   // AVLTree_remove(&tree, 10);
//   display(tree); //expect  1  4  6  8  11  12  14
//   printf("\n");
//   printf(" [height %d] " , AVLNode_height(tree->left));
//   printf(" [balanced -  %d] " , AVLTree_isBalanced(tree) );
//   printf("\n");

}

