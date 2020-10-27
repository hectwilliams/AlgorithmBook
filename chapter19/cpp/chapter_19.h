
#ifndef CHAPTER19_H
#define CHAPTER19_H


#include <vector>
#include <functional>
#include <stdio.h>


class AVLTree;

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
    void calculateBalance(); // avl rotate
    void leftRotateTranslate(AVLNode *parent, AVLTree   *obj ) ; // avl rotate
    void rightRotateTranslate(AVLNode *parent,  AVLTree *obj  ); // avl rotate
    void balanceCheck(AVLTree *avlTreeClass); // avl balanced

    void whoAmI ()
    {
      // std::cout <<  " [ ] " << this->value << " ,  " <<  this->balance << " " ;
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

    void leftRotate(AVLNode *target , AVLNode *node = NULL);
    void rightRotate(AVLNode *target , AVLNode *node = NULL);

    bool balancedAdd(const int &value, AVLNode *node = NULL);
    bool balanceRemove(const int &value, AVLNode *node = NULL);

    void repair(AVLNode *node = NULL);

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

 char buffer [100];

  tree.add(100);
  tree.add(50 );
  tree.add(200);
  tree.add(300);
  tree.add(400);
  tree.add(25);
  tree.add(5 );
  tree.add(10);
  tree.display();
}


class RBTree;

class RBNode
{
  friend class RBTree; //  RBTree class can access  node private members

  public:
    int color;  // 0 -black 1-red
    RBNode *left;
    RBNode *right;
    int count;
    int value;

    RBNode (const int &value)
    {
      this->value = value;
      this->count = 1;
      this->color = true;
      this->left = NULL;
      this->right = NULL;
    }

    void display();
    int rotationCode ();
    void leftRotate ( RBNode *parent , RBTree *obj ) ;
    void rightRotate ( RBNode *parent , RBTree *obj ) ;

    int successor();
    void copy(const RBNode *src);
    void colorSwap(RBNode *node);

  private:


};


class RBTree
{

  public:
    RBNode *root;
    RBTree()
    {
      this->root = NULL;
    }
    bool contains (const int &value , RBNode *node = NULL);
    void display (RBNode *node = NULL);
    int add(const int &value, RBNode *node = NULL , RBNode *parent = NULL);
    void blackHeightErrorHandler (bool hasImbalance, RBNode *target, RBNode * targetParent );
    RBNode *findParent(RBNode * target, RBNode *node = NULL);
    void remove(const int &value, RBNode *node = NULL, RBNode *parent = NULL );

    private:
      void removeHelper(RBNode *target, RBNode *parent);
      void removeHelperBalance (RBNode *u,  int dir, RBNode *p );
};


void rb_tree_test ()
{

  // const int array[] = {
  //          100,
  //       50,       500,
  //     25,      450,        1000,
  //   20,     300,  480,   900,   2000,
  //  15,    200,          800
  // };

  // char buffer [100];

  RBTree tree;

  tree.add(3);
  tree.add(1 );
  tree.add(5);
  tree.add(7);
  tree.add(6);
  tree.add(8);
  tree.add(9 );
  tree.add(10);
  tree.add(12);
  tree.add(12333);
  tree.add(2);

  tree.remove(6);


  tree.display();
}

class SplayTree;

class SplayNode
{
  friend class SplayTree;

  public:
    int value;
    SplayNode *left;
    SplayNode *right;
    void display();

    SplayNode (const int &value)
    {
      this->value = value;
    }

  private:
    void copy(SplayNode *src);
    int successor();
    void leftRotate (SplayNode *parent, SplayTree * const splayTreeClass);
    void rightRotate (SplayNode *parent, SplayTree * const splayTreeClass);
};

class SplayTree
{
  friend class SplayNode;

  private:
    void  remove_ (int value, SplayNode *node = NULL, SplayNode *parent = NULL);
    void remove_helper(SplayNode *target, SplayNode *parent);
    void splay(int value, SplayNode *node , SplayNode *parent );
    SplayNode *root;

  public:
    SplayTree & add (const int & value);
    void  remove (int value, SplayNode *node = NULL, SplayNode *parent = NULL);
    void display();
    SplayTree()
    {
      root = NULL;
    }
};



void splay_tree_test ()
{
  SplayTree tree;
  tree.add(1);
  tree.add(2);
  tree.add(3);
  tree.add(1);
  tree.add(6);

  tree.remove(2);
  tree.display();
}


#endif