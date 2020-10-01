#include <iostream>
#include "chapter_19.h"


void AVLTree::display(AVLNode * node)
{
  if (node == nullptr)
  {
    node = head;
  }

  if (node )
  {
    if (node->left)
    {
      display(node->left);
    }
    std::cout << '[' << node->value << "--> " << node->balance << ']' ;
    if (node->right)
    {
      display(node->right);
    }
  }
}

bool AVLTree::add(const int &value, AVLNode *node)
{

  if (node == nullptr)
  {
    node = head;
  }

  if (node == nullptr)
  {
    head = new AVLNode(value);
  }
  else
  {
    if (value < node->value)
    {
      if (node->left)
      {
       if (add(value, node->left));
       {
         node->balance++;
         return true;
       }
      }
      else
      {
        node->left = new AVLNode(value);
        node->balance++;
        return true;
      }
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        if( add(value, node->right))
        {
          node->balance--;
          return true;
        }
      }
      else
      {
        node->right = new AVLNode(value);
        node->balance--;
        return true;
      }
    }

    else if (value == node->value)
    {
      node->count++;
    }
  }

  return false;

}

bool AVLTree::remove_helper(AVLNode *parent, AVLNode *node, AVLTree *tree)
{
  AVLNode *runner = NULL, *ancestor = NULL;
  if (node->count > 1)
  {
    node->count--;
    return true;
  }

  if (node->left == NULL && node->right == NULL)
  {
    if (parent == NULL)
    {
      tree->head = NULL;
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

  else if (node->left != NULL && node->right == NULL )
  {
    if (parent == NULL)
    {
      tree->head = node->left;
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

  else if (node->right != NULL && node->left == NULL )
  {
    if (parent == NULL)
    {
      tree->head = node->right;
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
        tree->head = node->right;
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
        tree->head = ancestor;
      }
      else if (parent->left == node)
      {
        parent->left = ancestor;
      }
      else if (parent->right == node )
      {
        parent->right = ancestor;
      }
    }
  }

  delete(node);

  return true;

}

bool AVLTree::remove(const int &value, AVLNode *node)
{
  AVLNode *prev = NULL;

  if (node == NULL)
  {
    node = head;
  }


  if (node)
  {
    if (node->value == value)
    {
      return remove_helper(NULL, node, this);
    }
    else if (value < node->value)
    {
      if (node->left)
      {
        if (node->left->value == value)
        {
          return remove_helper(node, node->left, this);
        }
        else
        {
          return remove(value, node->left);
        }
      }
    }
    else if (value > node->value)
    {
      if (node->right)
      {
        if (node->right->value == value)
        {
          remove_helper(node, node->right, this);
        }
        else
        {
          return remove(value, node->right);
        }
      }
    }
  }
  return false;
}

int main()
{
  AVLTree tree;
  tree.add(10);
  tree.add(8);
  tree.add(12);

  // tree.remove(10);
  // tree.display(); // 8 12

  // tree.remove(8);
  // tree.display(); // 10 12

  // tree.remove(12);
  // tree.display(); // 8 10

  // tree.add(11);
  // tree.add(14);
  // tree.add(4);
  // tree.add(6);

  // // tree.remove(8);
  // // tree.display(); // 4 6 10 11 12 14

  // tree.add(1);

  // // tree.remove(4);
  // // tree.display(); // 1 6 8 10 11 12 14

  // tree.remove(10);
  tree.display(); // 1 4 6 8 11 12 14

}
