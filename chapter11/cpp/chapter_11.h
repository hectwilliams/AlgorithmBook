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
    ~BTNode() {}
};

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

};

BTNode *btnodeAllocate(int value);
