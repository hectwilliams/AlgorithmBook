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

int BST::min_height ()
{
  int min = 0;
  min_height_helper(min);
  return min;
}

int BST::min_height_helper ( int &min, BTNode *node , int depth )
{

  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {
    if (node->left)
    {
      min_height_helper(min, node->left,  depth + 1 );
    }

    if (node->right)
    {
      min_height_helper(min, node->right, depth  + 1 );
    }

    if (node->right == NULL && node->left == NULL)
    {
      if (min == 0 || depth < min)
      {
        min = depth;
      }
    }
  }
}

void min_height_test()
{
  BST tree = BST();
  tree.add(5);
  tree.add(100);
  tree.add(2);
  tree.add(1);
  tree.add(0);
  std::cout <<  tree.min_height() << '\n';
}

void BST::preOrderTraverselNoRecursion(BTNode *node)
{
  std::vector<BTNode*> collection;
  if (node == NULL)
  {
    node = root;
  }

  while (node)
  {
    if (node->right)
    {
      collection.push_back(node->right);
    }
    std::cout << node->value << '\n';

    if (node->left)
    {
      node = node->left;
    }
    else if (collection.size())
    {
      node = collection.back();
      collection.pop_back();
    }
    else
    {
      break;
    }
  }
}

void preOrderTraverselNoRecursion_test()
{
  BST tree = BST();
  tree.add(5);
  tree.add(100);
  tree.add(2);
  tree.add(1);
  tree.add(0);
  tree.preOrderTraverselNoRecursion();
}

BTNode *BST::successor(BTNode * node)
{
  BTNode *deleteNode = node;
  BTNode *prev = NULL;

  if (node)
  {
    if (node->right)
    {
      prev = node;
      node = node->right;
      while (node->left)
      {
        prev = node;
        node = node->left;
      }
    }

    /*re-route prev node */
    if (prev)
    {
      if (prev->left == node)
      {
        prev->left = node->right;
      }
      else
      {
        prev->right = node->right;
      }
    }

    delete(deleteNode);
  }
  return node;
}

void BST::remove(const int &value, BTNode *node, BTNode *prev)
{
  BTNode *tmp;
  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {
    if (node->value == value)
    {
      delete(node);

      if (node->left != NULL && node->right != NULL)  /* MAX CHILDREN */
      {
        tmp = successor(node);

        tmp->left = node->left;
        tmp->right = node->right;

        if (prev == NULL)
        {
          root = tmp;
        }
        else if (prev->left == node)
        {
          prev->left = tmp;
        }
        else
        {
          prev->right = tmp;
        }
      }

      else if (node->left == NULL ^ node->right == NULL)  /* 1 CHILD */
      {
        if (prev == NULL)
        {
          if (node->right)
          {
            root = node->right;
          }
          else
          {
            root = node->left;
          }
        }
        else if (prev->left == node)
        {
          if (node->right)
          {
            prev->left = node->right;
          }
          else
          {
            prev->left = node->left;
          }
        }
        else if (prev->right == node)
        {
          if (node->right)
          {
            prev->right = node->right;
          }
          else
          {
            prev->right = node->left;
          }
        }

      }

      else if (node->left == NULL && node->right == NULL)  /* NO CHILDREN */
      {
        if (prev == NULL)
        {
          root = NULL;
        }
        else if (prev->left == node)
        {
          prev->left = NULL;
        }
        else if (prev->right == node)
        {
          prev -> right = NULL;
        }
      }
    }

    if (node->left)
    {
      remove(value ,node->left, node);
    }

    if (node->right)
    {
      remove (value, node->right, node);
    }
  }
}

void remove_test()
{
  BST tree = BST();
  tree.add(5);
  tree.add(100);
  tree.add(2);
  tree.add(1);
  tree.add(0);
  tree.remove(0);
  tree.inOrder();
}

void BST::removeAll(BTNode *node, BTNode *prev)
{
  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {
    if (node->left)
    {
      removeAll(node->left, node);
    }

    if (node->right)
    {
      removeAll(node->right, node);
    }

    if (prev)
    {
      if (prev->left)
      {
        prev->left = NULL;
      }

      if (prev->right)
      {
        prev->right = NULL;
      }

      delete(node);
    }
    else
    {
      root = NULL;
    }
  }
}

void removeAllTest ()
{
  BST tree = BST();
  tree.add(5);
  tree.add(100);
  tree.add(2);
  tree.add(1);
  tree.add(0);
  tree.inOrder();
}

bool BST::isValid(BTNode *node)
{
  bool result = true;

  if (node == NULL)
  {
    node = root;
  }

  if (node )
  {
    if (node->left)
    {
      if (node->left->value < node->value && node->left != node)
      {
        result &= isValid(node->left);
      }
      else
      {
        result &= false;
      }
    }

    if (node->right)
    {
      if (node->right->value >= node->value && node->right != node)
      {
        result &= isValid(node->right);
      }
      else
      {
        result &= false;
      }

    }
  }

  return result;
}

void isValidTest()
{
  BST tree = BST();
  tree.add(5);
  tree.add(100);
  tree.add(2);
  tree.add(1);
  tree.add(0);

  std::cout << tree.isValid() << '\n'; // true

  // tree.root->left->value = 100; // not allowed proerty pro
  // std::cout << tree.isValid() << '\n'; // false
}

void BST::add_no_dupes(const int &value, BTNode *node)
{
  if (node == NULL)
  {
    node = root;
  }

  if (root == NULL)
  {
    root = btnodeAllocate(value);
  }
  else if (value < node->value)
  {
    if (node->left)
    {
      add_no_dupes(value, node->left);
    }
    else
    {
      node->left = btnodeAllocate(value);
    }
  }
  else if(value > node->value)
  {
    if (node->right)
    {
      add_no_dupes(value, node->right);
    }
    else
    {
      node->right = btnodeAllocate(value);
    }
  }
}

void add_no_dupes_test()
{
  BST tree = BST();
  tree.add_no_dupes(5);
  tree.add_no_dupes(100);
  tree.add_no_dupes(2);
  tree.add_no_dupes(2);
  tree.inOrder();
}

void BST::bst_reverse_order(BTNode *node)
{

  if (node == NULL)
  {
    node = root;
  }

  if (node)
  {
    if (node->right)
    {
      bst_reverse_order(node->right);
    }

    std::cout << node->value << '\n';

    if (node->left)
    {
      bst_reverse_order(node->left);
    }
  }
}


int main()
{
  add_no_dupes_test();
}
