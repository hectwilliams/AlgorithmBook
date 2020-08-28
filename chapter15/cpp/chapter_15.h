#include <stdlib.h>
#include <iostream>

class BSTNode
{
  public:
  int value;
  BSTNode *left;
  BSTNode *right;
  BSTNode *parent;


  BSTNode(int value)
  {
    this->value = value;
    this->right = this->left = this->parent =  NULL;

  }
};

class BST
{
  public:

  BSTNode *root;

  BST ()
  {
    this->root = NULL;
  }
  void display(BSTNode *node = NULL);
  void add (int value, BSTNode *node = NULL);
  static BSTNode * remove_successor (BSTNode *node);
  void remove(int value, BSTNode *node = NULL,  BSTNode *prev = NULL);
  int height(BSTNode *node = NULL);
  bool is_full_tree(BSTNode *node = NULL);
  bool is_complete_tree(BSTNode *node = NULL);

};