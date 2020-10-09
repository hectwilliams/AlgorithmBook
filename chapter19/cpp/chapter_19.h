#include <vector>

class AVLNode
{
  friend class AVLTree;

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
    bool isBalanced();

  private:
      void setBalance();
      void grandchild_promote();
};

class AVLTree
{
  friend class AVLNode;

  private:
    bool remove_helper(AVLNode *parent, AVLNode *node );
    void update_balance_path(AVLNode *node, AVLNode *end);

  public:
    AVLNode *head;
    AVLTree()
    {
      this->head = nullptr;
    }
    void display(AVLNode * node = nullptr);
    bool add(const int &value, AVLNode *node = NULL);
    bool remove(const int &value, AVLNode *node = NULL);
    bool isBalanced();
    unsigned height();
    void left_rotate(AVLNode *target, AVLNode *node = NULL );
    void right_rotate(AVLNode *target, AVLNode *node = NULL );
    bool balanced_add(const int &value, AVLNode *node = NULL);
    bool balanced_remove(const int &value, AVLNode *node = NULL);

};

