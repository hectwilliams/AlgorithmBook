#include "chapter19.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
      return 1; // update upstream node balance
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

      // update path balance ( from: predecessor(include) -> to: successor's parent(exclude) )
      {
        if (successor_parent->right == NULL)  // path's balance update
        {
          AVLTree_update_balance_path(node, successor_parent);
        }
      }

      // remove heir from heir's parent
      {
        successor_parent->left = successor_parent->left->left;  //  note: successor_parent->left->left = NULL
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
  struct AVLTree *node = NULL;

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

int AVLNode_height(const struct AVLTree *node)   // logN
{
  if (node)
  {
    if (node->balance > 0)
    {
      return 1 + AVLNode_height(node->left);
    }

    else if (node->balance < 0)
    {
      return 1 + AVLNode_height(node->right);
    }

    else if (node->balance == 0 && node->right)
    {
      return 1 + AVLNode_height(node->right);
    }

    else if (node->balance == 0 && node->left)
    {
      return 1 + AVLNode_height(node->left);
    }
  }
  return 0;
}

int AVLTree_isBalanced (struct AVLTree *node)
{
    return abs (node->balance ) <= 1;
}


void AVLTree_setNodeBalance(struct AVLTree *node)
{
  if (node)
  {
    if (node->left && node->right)
    {
      node->balance = AVLNode_height(node->left) - AVLNode_height(node->right);
    }

    else if (node->right && node->left == NULL)
    {
      node->balance = - (1 + AVLNode_height(node->right));
    }

    else if (node->left && node->right == NULL)
    {
      node->balance = (1 + AVLNode_height(node->left));
    }
  }
}

void AVLTree_grandchild_promote (struct AVLTree *parent)
{
  struct AVLTree *child = NULL, *grandchild = NULL, *buffer_subtree = NULL;

  if (parent)
  {
    if (parent->balance > 0)  // TARGET.LEFT
    {

      if (parent->left->balance > 0)  // TARGET.LEFT.LEFT
      {
        // RIGHT ROTATE
        // child = parent->left;
        // grandchild = parent->left->left;
        // buffer_subtree = parent->left->left->right;

        // grandchild->right = child;
        // child->left = buffer_subtree;
        // parent->left = grandchild;


        // AVLTree_setNodeBalance(child);
        // AVLTree_setNodeBalance(grandchild);
        // AVLTree_setNodeBalance(parent);
      }

      else if (parent->left->balance < 0)  // TARGET.LEFT.RIGHT
      {
        // LEFT ROTATE
        child = parent->left;
        grandchild = parent->left->right;
        buffer_subtree = parent->left->right->left;

        grandchild->left = child;
        child->right = buffer_subtree;
        parent->left = grandchild;

        AVLTree_setNodeBalance(child);
        AVLTree_setNodeBalance(grandchild);
        AVLTree_setNodeBalance(parent);
      }

    }

    else if (parent->balance < 0)  // TARGET.RIGHT
    {

      if (parent->right->balance > 0)  // TARGET.RIGHT.LEFT
      {
        // RIGHT ROTATE
        child = parent->right;
        grandchild = child->left;
        buffer_subtree = grandchild->right;

        grandchild->right = child;
        child->left = buffer_subtree;
        parent->right = grandchild;

        AVLTree_setNodeBalance(child);
        AVLTree_setNodeBalance(grandchild);
        AVLTree_setNodeBalance(parent);
      }

      else if (parent->right->balance < 0)  // TARGET.RIGHT.RIGHT
      {
        // LEFT ROTATE
        // child = parent->right;
        // grandchild = parent->right->right;
        // buffer_subtree = parent->right->right->left;

        // grandchild->left = child;
        // child->right = buffer_subtree;
        // parent->right = grandchild;

        // AVLTree_setNodeBalance(child);
        // AVLTree_setNodeBalance(grandchild);
        // AVLTree_setNodeBalance(parent);
      }
    }
  }
}


void AVLTree_left_rotate(struct AVLTree **tree, struct AVLTree *target)
{
  struct AVLTree *node = *tree;
  struct AVLTree *parent_of_target = NULL;
  struct AVLTree *target_ref = NULL;
  struct AVLTree *subtree = NULL;
  struct AVLTree *child = NULL;

  // find target
  if (node)
  {
    // root
    if (node == target)
    {
      target_ref = node;
    }
    else if (node->left == target)
    {
      parent_of_target = node;
      target_ref = node->left;
    }
    else if (node->right == target)
    {
      parent_of_target = node;
      target_ref = node->right;
    }
    else if (target->value < node->value)
    {
      return AVLTree_left_rotate( & node->left, target);
    }

    else if ( target->value > node->value)
    {
      return AVLTree_left_rotate(&node->right, target);
    }
  }

  if (target_ref)
  {
    AVLTree_grandchild_promote(target_ref);

    child = target_ref->right;
    subtree = child->left;

    child->left = target_ref;
    target_ref->right = subtree;

    AVLTree_setNodeBalance(target_ref);
    AVLTree_setNodeBalance(child);

    if (parent_of_target == NULL)
    {
      *tree = child;
    }
    else if (parent_of_target->left == target_ref)
    {
      parent_of_target->left = child;
      AVLTree_setNodeBalance(parent_of_target);
    }
    else if (parent_of_target->right == target_ref)
    {
      parent_of_target->right = child;
      AVLTree_setNodeBalance(parent_of_target);
    }
  }
}

void AVLTree_right_rotate(struct AVLTree **tree, struct AVLTree *target)
{
  struct AVLTree *node = *tree;
  struct AVLTree *parent_of_target = NULL;
  struct AVLTree *target_ref = NULL;
  struct AVLTree *subtree = NULL;
  struct AVLTree *child = NULL;

  // find target

  if (node)
  {
    if (node == target)
    {
      target_ref = node;
    }
    else if (node->left == target)
    {
      parent_of_target = node;
      target_ref = node->left;
    }
    else if (node->right == target)
    {
      parent_of_target = node;
      target_ref = node->right;
    }
    else if (target->value < node->value)
    {
      return AVLTree_right_rotate( & node->left, target);
    }
    else if ( target->value > node->value)
    {
      return AVLTree_right_rotate(&node->right, target);
    }
  }

  if (target_ref)
  {
    AVLTree_grandchild_promote(target_ref);

    child = target_ref->left;
    subtree = child->right;

    child->right = target_ref;
    target_ref->left = subtree;

    AVLTree_setNodeBalance(target_ref);
    AVLTree_setNodeBalance(child);

    if (parent_of_target == NULL)
    {
      *tree = child;
    }
    else if (parent_of_target->left == target_ref)
    {
      parent_of_target->left = child;
      AVLTree_setNodeBalance(parent_of_target);
    }
    else if (parent_of_target->right == target_ref)
    {
      parent_of_target->right = child;
      AVLTree_setNodeBalance(parent_of_target);
    }
  }
}


void AVLTree_balanced_add(struct AVLTree **tree, int value)
{
  struct AVLTree *node;

  if (tree)
  {
    AVLTree_add(tree, value);

    if ( ! abs(AVLTree_isBalanced(*tree)))
    {

      if ((*tree)->balance > 1)  // right rotate
      {
                printf("RIGHT ROTATE\n");

        AVLTree_right_rotate(tree, *tree);
      }

      else if ((*tree)->balance < -1)  // left rotate
      {
                printf("LEFT  ROTATE\n");

        AVLTree_left_rotate(tree, *tree);
      }
    }
  }
}


int main()
{
 balanced_add_test();
}



