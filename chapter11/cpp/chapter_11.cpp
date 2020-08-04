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

unsigned BST::height(BTNode *node)
{
  unsigned height_left = 0, height_right = 0;

  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {
    if (node->left)
    {
      height_left += 1 +height(node->left);
    }

    if (node->right)
    {
      height_right = 1 + height(node->right);
    }
  }

  if (height_left == height_right)
  {
    return height_right;
  }

  if (height_left > height_right)
  {
    return height_left;
  }
  else
  {
    return height_right;
  }
}

unsigned heightTest ()
{
  BST tree;
  tree.add(5);
  tree.add(6);
  tree.add(32);
  tree.add(1);
  std::cout << tree.height() << '\n';
}

bool BST::is_balanced (BTNode *node , BTNode *prev )
{
  int l, r;

  l = r = 0;

  if (prev == NULL)
  {
    node = root;
  }

  if (node == NULL)
  {
    return 1;
  }

  if (node)
  {
    l = height(node->left);
    r = height(node->right);
    return std::abs(l - r) <= 1 && is_balanced(node->left, node) && is_balanced(node->right, node);
  }
}

unsigned isBalancedTest ()
{
  BST tree;
  tree.add(5);
  tree.add(6);
  tree.add(32);
  tree.add(1);
  std::cout << tree.is_balanced() << '\n';
}

BST BST::array_to_bst (const std::vector<int> &collection )
{
  BST tree;
  int lpos, rpos;

  lpos = collection.size() / 2;
  rpos = lpos + 1;

  while (1)
  {

    if (lpos >=0)
    {
      tree.add(collection[lpos--]);
    }

    if (rpos < collection.size())
    {
      tree.add(collection[rpos++]);
    }

    if (lpos < 0 && rpos >= collection.size())
    {
      break;
    }
  }
  return tree;
}

void array_to_bst_test()
{
  std::vector<int> collection;
  for (int i = 5; i--;)
  {
    collection.push_back(i);
  }
  BST tree = BST::array_to_bst(collection);

  tree.display();
}

  int BST::common_ancestor(int a, int b, BTNode *node)
  {
    if (node == NULL)
    {
      node = root;
    }

    if (a < node->value && b < node->value && node->left)
    {
      if (node->left->value != a && node->left->value != b)
      {
        return common_ancestor(a,b, node->left);
      }
    }

    if (a > node->value && b > node->value && node->right)
    {
      if (node->right->value != a && node->right->value != b)
      {
        return common_ancestor(a,b, node->right);
      }
    }

    return node->value;
  }

void common_ancestor_test()
{
  BST tree = BST();
  tree.add(5);
  tree.add(100);
  tree.add(2);
  tree.add(1);
  tree.add(0);

  std::cout << tree.common_ancestor(1,0) << '\n';
}
int main()

{
  common_ancestor_test();
}
