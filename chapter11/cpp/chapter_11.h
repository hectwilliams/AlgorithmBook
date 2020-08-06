#include <string>
#include <vector>

struct nodeData
{
  int value;
  bool valid;
};

class BTNode
{
  private:
  public:
    int value;
    BTNode *left;
    BTNode *right;
    BTNode(int value)
    {
      value = value;
      left = right = NULL;
    }
    // ~BTNode() {}
};

struct BST_LL
{
  int value;
  struct BST_LL *next;
};
void bst_ll_insert( BST_LL *node, int data);
class BST
{
  private:
    BTNode *root;

  public:
    BST()
    {
      root = NULL;
    }
  void add(int value, BTNode *parent = NULL);
  void display(BTNode *node = NULL);
  bool contains(int value, BTNode *node);
  struct nodeData min(BTNode *node = NULL);
  struct nodeData max(BTNode *node = NULL);
  unsigned size(BTNode *node = NULL);
  bool empty();
  unsigned height(BTNode *node = NULL);
  bool  is_balanced (BTNode *node = NULL , BTNode *prev = NULL );
  static BST array_to_bst (const std::vector<int> &collection );
  int common_ancestor(int a, int b, BTNode *node = NULL);
  void preOrder(BTNode *node = NULL);
  void postOrder(BTNode *node = NULL);
  void inOrder(BTNode *node = NULL);
  void bst_to_array(std::vector<int> &collection, BTNode *node = NULL, int mode = 0);
  void bst_to_array_pre(std::vector<int> &collection);
  void bst_to_array_post(std::vector<int> &collection);
  struct BST_LL * bst_to_list(int mode = 0);
  struct BST_LL * bst_to_list_pre(int mode = 1);
  struct BST_LL * bst_to_list_post(int mode = 2);
  int min_height();
  void preOrderTraverselNoRecursion(BTNode *node = NULL);
  void remove(const int &value, BTNode *node = NULL, BTNode *prev = NULL);
  void removeAll(BTNode *node = NULL, BTNode *prev = NULL);

  bool isValid(BTNode *node = NULL);
  void add_no_dupes(const int &value, BTNode *node = NULL);

  void bst_reverse_order(BTNode *node = NULL);

  private:
  void bst_to_list_helper(BTNode *node, int mode , BST_LL **llist);
  int min_height_helper ( int &min, BTNode *node = NULL, int depth = 0 );
  BTNode *successor(BTNode * node = NULL);

};

BTNode *btnodeAllocate(int value);
