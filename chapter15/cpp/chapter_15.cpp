#include "chapter_15.h"


void BST::display(BSTNode *node)
{

  node = !node ? root : node;

  if (node)
  {
    if (node->left)
    {
      display(node->left);
    }

    std::cout << node->value << '\n';

    if (node->right)
    {
      display(node->right);
    }
  }
}

void BST::add (int value, BSTNode *node)
{
  BSTNode *newNode = new BSTNode(value);

  node = !node ? root : node;

  if (node == NULL)
  {
    root = newNode;
  }
  else
  {
    if (value < node->value)
    {
      if (node->left)
      {
        add(value, node->left);
      }
      else
      {
        node->left = newNode;
      }
    }
    else
    {
      if (node->right)
      {
        add(value, node->right);
      }
      else
      {
        node->right = newNode;
      }
    }
  }

}

BSTNode *BST::remove_successor (BSTNode *node)
{

  BSTNode *prev = node;

  if (node->right)
  {
    node = node->right;

    while (node->left)
    {
      prev = node;
      node = node->left;
    }

    if (prev->left == node)
    {
      prev->left = NULL;
    }
    else
    {
      prev->right = NULL;
    }
  }
  return node;
}

int BST::height(BSTNode *node)
{
  int left, right;


  left = right = 0;
  node = !node ? root : node;

  if (node->left)
  {
    left = 1 + height(node->left);
  }

  if (node->right)
  {
    right = 1 + height(node->right);
  }

  return right > left ? right : left;
}

void BST::remove(int value, BSTNode *node,  BSTNode *prev)
{
  BSTNode *successor;
  node = !node ? root : node;

  if (node)
  {
    if (node->value == value)

    {
      if (node->left && node->right)
      {

        successor = remove_successor(node);
        successor->left = node->left;
        successor->right = node->right;

        if (prev == NULL)
        {
          root = successor;
        }
        else
        {
          if (prev->left == node)
          {
            prev->left = successor;
          }
          else
          {
            prev->right = successor;
          }
        }
      }
      else if (!!node->left ^ !! node->right)
      {
        if (prev == NULL)
        {
          root = !node->left ? node->right : node->left;
        }
        else
        {
          if (prev->left == node )
          {
            prev->left = !node->left ? node->right : node->left;
          }
          else
          {
            prev->right = !node->left ? node->right : node->left;
          }
        }
      }
      else if (!node->right && !node->left)
      {
        if (prev == NULL)
        {
          root = NULL;
        }
        else
        {
          if (prev->left == node)
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
    else
    {
      if (value < node->value)
      {
        if (node->left)
        {
          remove(value, node->left, node);
        }
      }
      else
      {
        if (node->right)
        {
          remove(value, node->right, node);
        }
      }
    }
  }

}

int main()
{

  BST tree;
tree.add(30);
tree.add(17);
tree.add(217);
tree.add(3);

tree.display();
tree.display();


}