#include <iostream>
#include "chapter_11.h"

BTNode *btnodeAllocate(int value)
{
  BTNode *node = new BTNode(value);
  node->value = value;
  return node;
}

void BST::add(int value, BTNode *node)
{
  if (node == NULL)
  {
    node = root;
  }

  if (root == NULL)
  {
    root = btnodeAllocate(value);
  }
  else
  {
    if (value < node->value)
    {
      if (node->left == NULL)
      {
        node->left = btnodeAllocate(value);
      }
      else
      {
        return add(value, node->left);
      }
    }
    else if (value >= node->value)
    {
      if (node->right == NULL)
      {
        node->right = btnodeAllocate(value);
      }
      else
      {
        return add(value, node->right);
      }
    }
  }
}

void BST::display(BTNode *node)
{
  if (node == NULL)
  {
    node = root;
  }

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

bool BST::contains(int value, BTNode *node)
{
  bool result = false;

  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {
    result = (node->value == value);

    if (node->left)
    {
      result |= contains(value, node->left);
    }

    if (node->right)
    {
      result |= contains(value, node->right);
    }
  }
  return result;
}

struct nodeData BST::min(BTNode *node)
{
  struct nodeData result = {.valid = false};

  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {
    if (node->left)
    {
      return min(node->left);
    }
    else
    {
      result.valid = true;
      result.value = node->value;
    }
  }
  return result;
}


void bstMinTest()
{
  /*
       5
      / \
    1    100

  */
  BST tree;
  tree.add(5);
  tree.add(100);
  tree.add(1);
  std::cout << tree.min().value << '\n';
}



struct nodeData BST::max(BTNode *node)
{
  struct nodeData result = {.valid = false};
  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {
    if (node->right)
    {
      return max(node->right);
    }
    else
    {
      result.valid = true;
      result.value = node->value;
    }
  }
  return result;
}


void bstMaxTest()
{
  /*
       5
      / \
    1    100
  */
  BST tree;
  tree.add(5);
  tree.add(100);
  tree.add(1);
  std::cout << tree.max().value << '\n';
}

unsigned BST::size(BTNode *node)
{
  unsigned sum = 0;

  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {
    sum++;
    if (node->left)
    {
      sum += size(node->left);
    }
    if (node->right)
    {
      sum += size(node->right);
    }
  }
  return sum;
}

void bstSizeTest()
{
  BST tree;
  tree.add(5);
  tree.add(100);
  tree.add(1);
  std::cout << tree.size() << '\n';
}

bool BST::empty()
{
  return root == NULL;
}

void bstemptyTest()
{
  BST tree;
  tree.add(5);
  tree.add(6);
  std::cout << tree.empty() << '\n';

  BST empty_tree;
  std::cout << empty_tree.empty() << '\n';

}

int main()
{
  bstemptyTest();
}
