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
};

class AVLTree
{
  public:

    AVLNode *head;

    AVLTree()
    {
      this->head = nullptr;
    }
    void display(AVLNode * node = nullptr);
    void add(const int &value, AVLNode *node = NULL);
};