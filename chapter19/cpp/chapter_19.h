#include <vector>

class AVLNode
{
  public:
    AVLNode *left;
    AVLNode *right;
    int count;
    int balance;
    int value;

    AVLNode(int value)
    {
      this->left = nullptr;
      this->right = nullptr;
      this->count = 1;
      this->balance = 0;
      this->value = value;
    }

    unsigned height (AVLNode *node = NULL);
    bool isBalanced(AVLNode *node = NULL);
};

class AVLTree
{
  private:
    bool remove_helper(AVLNode *parent, AVLNode *node, AVLTree *tree);

  public:
    AVLNode *head;
    AVLTree()
    {
      this->head = nullptr;
    }
    void display(AVLNode * node = nullptr);
    bool add(const int &value, AVLNode *node = NULL);
    bool remove(const int &value, AVLNode *node = NULL);
    unsigned height ();
    bool isBalanced(AVLNode *node = NULL);

};

