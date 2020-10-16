
#ifndef CHAPTER19_H
#define CHAPTER19_H


#include <vector>

class AVLNode
{
  friend class AVLTree; // AVLTree can access AVLNode Class methods

  public:
    AVLNode *left;
    AVLNode *right;
    int count;
    int balance;
    int value;

    unsigned height (AVLNode *node = NULL);
    bool isBalanced();

  private:
    int inOrderSuccessor(); // avl remove
    void copyAttributes(AVLNode *src); // avl remove
    bool updateBalanceAck(bool isValid, int level);  // avl remove
    void whoAmI ()
    {
      std::cout <<  " [ ] " << this->value << " ,  " <<  this->balance << " " ;
    }

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
  friend class AVLNode;  // AVLNode can access AVLTree Class methods  (avl tree can delete friend )

  public:
    AVLNode *head;
    AVLTree()
    {
      this->head = nullptr;
    }
    void display(AVLNode * node = nullptr);
    bool isBalanced();
    unsigned height();
    bool add(int value, AVLNode *node = NULL);
    bool remove(const int &value, AVLNode *node = NULL);


    // void left_rotate(AVLNode *target, AVLNode *node = NULL );
    // void right_rotate(AVLNode *target, AVLNode *node = NULL );


    // bool balanced_add(const int &value, AVLNode *node = NULL);
    // bool balanced_remove(const int &value, AVLNode *node = NULL);
    // void repair(AVLNode *node = NULL);
  private:
    bool removeHelper(AVLNode *node, AVLNode *parent);  // avl remove

};

// AVL REMOVE TEST

void avl_remove_test ()
{
  const int array[] = {
           100,
        50,       500,
      25,      450,        1000,
    20,     300,  480,   900,   2000,
   15,    200,          800
  };

  AVLTree tree;

  for (int i = 0; i < sizeof(array) / sizeof(int) ; i++)
  {
    tree.add(array[i]);
  }

  tree.remove(100);
  tree.display();

}

// class RBNode
// {
//   friend class RBTree; //  RBTree class can access  node private members

//   public:
//     bool color;  // 0 -black 1-red
//     RBNode *left;
//     RBNode *right;
//     int count;
//     int value;

//     RBNode (const int &value)
//     {
//       this->value = value;
//       this->count = 1;
//       this->color = true;
//       this->left = NULL;
//       this->right = NULL;
//     }
//   private:
// };


// class RBTree
// {
//   public:
//     RBNode *root;
//     RBTree()
//     {
//       this->root = NULL;
//     }
//     bool contains (const int &value , RBNode *node = NULL);
//     int add(const int &value, RBNode *node = NULL, RBNode *parent = NULL );
//     void display (RBNode *node = NULL);
//     bool remove(const int &value, RBNode *node= NULL);

//   private:
//     void translate(RBNode *node = NULL, RBNode *parent = NULL, int code = -1);
//     void remove_helper(RBNode *parent, RBNode *node = NULL);


// };


#endif