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

void BST::preOrder(BTNode *node)
{
  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {
    printf("[%d]", node->value);

    if (node->left)
    {
      preOrder(node->left);
    }

    if (node->right)
    {
      preOrder(node->right);
    }
  }
}

void preOrderTest()
{
  BST tree = BST();
  tree.add(5);
  tree.add(100);
  tree.add(2);
  tree.add(1);
  tree.add(0);
  tree.preOrder();
  printf("\n");
}

void BST::postOrder(BTNode *node)
{
  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {

    if (node->left)
    {
      postOrder(node->left);
    }

    if (node->right)
    {
      postOrder(node->right);
    }

    printf("[%d]", node->value);

  }
}


void BST::inOrder(BTNode *node)
{
  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {

    if (node->left)
    {
      postOrder(node->left);
    }

    printf("[%d]", node->value);

    if (node->right)
    {
      postOrder(node->right);
    }


  }
}

void BST::bst_to_array(std::vector<int> &collection, BTNode *node, int mode)
{
  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {
    if (mode == 1)
    {
      /* pre order*/
      collection.push_back(node->value);
    }

    if (node->left)
    {
      bst_to_array(collection, node->left, mode);
    }

    if (mode == 0)
    {
      /*in order */
      collection.push_back(node->value);
    }

    if (node->right)
    {
      bst_to_array(collection, node->right, mode);
    }

    if (mode == 2)
    {
      /*post order*/
      collection.push_back(node->value);
    }
  }
}

void BST::bst_to_array_pre(std::vector<int> &collection)
{
  bst_to_array(collection, NULL, 1);
}

void BST::bst_to_array_post(std::vector<int> &collection)
{
  bst_to_array(collection, NULL, 2);
}

void bst_to_array_test()
{
  std::vector<int> array;
  BST tree = BST();

  tree.add(5);
  tree.add(100);
  tree.add(2);
  tree.add(1);
  tree.add(0);

  tree.bst_to_array(array);

  for (auto ele: array)
  {
    std::cout << '\t' << ele << '\n';
  }
}

BST_LL *allocate_bst_ll (int value)
{
  BST_LL *node =  (struct BST_LL*)  malloc(sizeof(struct BST_LL));
  node->value = value;
  node->next = NULL;
  return node;
}

void bst_ll_insert( BST_LL **llist, int data)
{
   BST_LL *runner;

  if (*llist == NULL)
  {
    *llist = allocate_bst_ll(data);
  }
  else
  {
    runner  = *llist;
    while (runner->next)
    {
      runner = runner->next;
    }

    if (runner->value != data)
    {
      runner->next  =  allocate_bst_ll(data);
    }
  }
}

struct BST_LL * BST::bst_to_list(int mode)
{
  BST_LL *llist = NULL;
  bst_to_list_helper(root, mode, &llist);
  return llist;
}

void BST::bst_to_list_helper(BTNode *node, int mode, BST_LL **llist)
{
  if (node )
  {
    if (mode == 1 ) //
    {
      bst_ll_insert(llist, node->value);
    }

    if (node->left)
    {
      bst_to_list_helper(node->left, mode, llist);
    }

    if (mode == 0)  //
    {
      bst_ll_insert(llist, node->value);
    }

    if (node->right)
    {
      bst_to_list_helper(node->right, mode, llist);
    }

     if (mode == 2)  //
    {
      bst_ll_insert(llist, node->value);
    }
  }
}

struct BST_LL * BST::bst_to_list_post(int mode )
{
 return  bst_to_list(mode);
}

struct BST_LL * BST::bst_to_list_pre(int mode)
{
  return bst_to_list(mode);
}

void bst_to_list_test()
{
  BST tree = BST();
  tree.add(5);
  tree.add(100);
  tree.add(2);
  tree.add(1);
  tree.add(0);
  struct BST_LL *llist =  tree.bst_to_list();
  struct BST_LL *runner = llist;

  while (runner)
  {
    std::cout << runner->value << '\n';
    runner = runner->next;
  }
}

int main()
{
  bst_to_list_test();
}
