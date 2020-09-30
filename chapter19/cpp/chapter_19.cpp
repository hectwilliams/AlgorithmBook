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
    std::cout << node->value << " ";
    if (node->right)
    {
      display(node->right);
    }
  }
}

void AVLTree::add(const int &value, AVLNode *node)
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
        return add(value, node->left);
      }
      else
      {
        node->left = new AVLNode(value);
      }
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        return add(value, node->right);
      }
      else
      {
        node->right = new AVLNode(value);
      }
    }

    else if (value == node->value)
    {
      node->count++;
    }
  }
}


int main()
{
  AVLTree tree;

  tree.add(10);
  tree.add(8);
  tree.add(12);
  tree.display();

}
