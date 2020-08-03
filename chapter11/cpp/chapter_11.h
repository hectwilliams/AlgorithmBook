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
};

BTNode *btnodeAllocate(int value);
