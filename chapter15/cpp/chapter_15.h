#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <array>
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
  private:
  bool bstRepairReinsert (BSTNode *node);

  public:

  BSTNode *root;

  BST ()
  {
    this->root = NULL;
  }
  void display(BSTNode *node = NULL);
  void add (int value, BSTNode *node = NULL);
  void addNode(BSTNode *targetNode, BSTNode *node = NULL);
  static BSTNode * remove_successor (BSTNode *node);
  void remove(int value, BSTNode *node = NULL,  BSTNode *prev = NULL);
  int height(BSTNode *node = NULL);
  bool is_full_tree(BSTNode *node = NULL);
  bool is_complete_tree(BSTNode *node = NULL);
  bool bstRepair (BSTNode *node = NULL);
  int smallest_difference (BSTNode *node = NULL, int *min = NULL);
  int closestValue (int value, BSTNode *node = NULL, std::array<int,1> closest = std::array<int , 1>() );

  BSTNode * partition_around_value( int value, BSTNode *node = NULL, BSTNode *prev = NULL );
  BST * partition_evenly(BSTNode *node = nullptr, BST *partitionA = nullptr, BST *partitionB = nullptr , int count = 0);

};