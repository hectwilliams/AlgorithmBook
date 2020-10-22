
#include <iostream>
#include <math.h>
#include "chapter_19.h"
#include <new>          // ::operator new

void AVLTree::display(AVLNode * node)
{
  if (node == nullptr)
  {
    node = head;
  }

  if (node )
  {
    if (node->left)
    {
      display(node->left);
    }
    std::cout << '[' << "value: " << node->value << "  -> " << "balance: "<< node->balance << ']' << '\n' ;
    if (node->right)
    {
      display(node->right);
    }
  }
}

bool AVLTree::add(int value, AVLNode *node)
{

  if (node == nullptr)
  {
    node = head;
  }

  if (node == nullptr)
  {
    head = (new AVLNode(value));
  }
  else
  {
    if (value < node->value)
    {
      if (node->left)
      {
       if (add(value, node->left))
       {
          node->balance++;

          return node->balance != 0;
       }

      }
      else
      {
        node->left = new AVLNode(value);
        node->balance++;
        return (node->balance != 0);
      }
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        if( add(value, node->right))
        {
          node->balance--;
          return (node->balance != 0);

        }
      }
      else
      {
        node->right = new AVLNode(value);
        node->balance--;
        return (node->balance != 0);
      }
    }

    else if (value == node->value)
    {
      node->count++;
    }
  }

  return false;
}


int AVLNode::inOrderSuccessor()
{
  AVLNode *runner = this->right;
  while (runner->left)
  {
    runner = runner->left;
  }
  return runner->value;
}

void AVLNode::copyAttributes(AVLNode *src)
{
  this->left = src->left;
  this->right = src->right;
  this->count = src->count;
  this->value = src->value;
  this->balance = src->balance;
}



bool AVLTree::removeHelper(AVLNode *node, AVLNode *parent)
{
  AVLNode  *del = NULL;
  bool isRoot = (parent == node);
  int successor;
  bool flag = true;


  if (node->left && node->right)
  {
    successor = node->inOrderSuccessor();
    flag = remove( successor ,node) ;
    flag = node->updateBalanceAck(flag, 1);  // return from right side
    node->value = successor;

  }

  else if (node->right)
  {

    del = node->right;
    node->copyAttributes(  del);
    if (!isRoot)
    {
      parent->balance++;
    }
  }

  else if (node->left)
  {
    del = node->left;
    node->copyAttributes(   del);
    if (!isRoot)
    {
      parent->balance--;
    }
  }

  else if (node->left == NULL && node->right == NULL)
  {
    del = node;
    if (isRoot)
    {
      this->head = NULL;
    }

    else if (parent->right == node)
    {
      parent->balance++;
      parent->right = NULL;

      if (parent->left)   // leaf's parent has sibling  DO NOT UPDATE BALANCE via call stack return
      {
        flag = 0;
      }
    }

    else if (parent->left == node)
    {
      parent->balance--;
      parent->left = NULL;

      if (parent->right)  // leaf's parent has sibling  DO NOT UPDATE BALANCE via call stack return
      {
        flag = 0;
      }
    }
  }

  if (del)
  {
    delete(del);
  }

  return flag;
}

bool AVLNode::updateBalanceAck (bool isValid, int level)
{
  int prevBalance = this->balance;


  if ( isValid )
  {
    this->balance += level;

    if (prevBalance == 0)  // stop balance updates on call stack
    {
      isValid = false;
    }
  }
  return isValid;
}


bool AVLTree::remove(const int &value, AVLNode *node)
{
  int flag = 0;

  if (node == NULL)
  {
    node = head;
  }

  if (node->value == value)
  {
    flag = removeHelper(node, node);
  }

  else if (value < node->value)
  {
    if (node->left)
    {
      if (node->left->value == value)
      {
        flag = removeHelper(node->left, node);
      }
      else
      {
        flag = remove(value, node->left);
        flag = node->updateBalanceAck(flag, -1);

      }
    }
  }
  else if (value > node->value)
  {
    if (node->right)
    {
      if (node->right->value == value )
      {
        flag = removeHelper(node->right, node);
      }
      else
      {
        flag = remove(value, node->right);
        flag = node->updateBalanceAck(flag, 1);
      }
    }
  }

  if (node)
  {
    node->whoAmI();

  }
  return flag;
}

unsigned AVLTree::height ()
{
  if (head)
  {
    return head->height();
  }
  return -1;
}

unsigned  AVLNode::height (AVLNode *node )
{

  if (node)
  {
    if (node->left == NULL && node->right == NULL)
    {
      return 0;
    }
    else if ( node->balance > 0)
    {
      return 1 + height(node->left);
    }

    else if ( node->balance < 0)
    {
      return 1 + height(node->right);
    }
  }
  return 0;
}

bool AVLNode::isBalanced()
{
  return abs(this->balance) <= 1;
}

bool AVLTree::isBalanced()
{
  return head->isBalanced();
}


void AVLNode::calculateBalance()
{
  this->balance =  (1 + this->height(this->left)) - (1 + this->height(this->right));
}


void AVLNode::leftRotateTranslate(AVLNode *parent,  AVLTree *obj  )  // avl rotate
{
  AVLNode *promote, *c, *t;

  promote = this->right;

  if (this->right->balance > 0)
  {
    promote = this->right->left;
    obj->rightRotate(this->right, this);
  }

  c = this->right;
  t = c->left;

  c->left = this;
  this->right = t;

  this->calculateBalance();
  c->calculateBalance();

  if (parent == this)
  {
    obj->head = promote;
  }

  else if (parent->left == this)
  {
    parent->left = promote;
  }

  else if (parent->right == this)
  {
    parent->right = promote;
  }
}

 void AVLTree::leftRotate(AVLNode *target , AVLNode *node )
 {

    if (node == NULL)
    {
      node = head;
      if (!node)
      {
        return;
      }
    }

      if (target->right)
    {
      if (node == target)
      {
          node->leftRotateTranslate(node, this);
      }

      else if (target->value < node->value)
      {
        if (node->left == target)
        {
          node->left->leftRotateTranslate(node, this);
        }
        else
        {
          leftRotate(target, node->left);
        }
      }

      else if (target->value > node->value)
      {
        if (node->right == target)
        {
          node->right->leftRotateTranslate(node, this);
        }
        else
        {
          leftRotate(target, node->right);
        }
      }
    }

 }

void AVLNode::rightRotateTranslate(AVLNode *parent,  AVLTree *obj  )
{
  AVLNode *c, *t, *promote;

  promote = this->left;

  if (this->left->balance < 0)
  {
    promote = this->left->right;
    obj->leftRotate( this->left , this);
  }

  c = this->left;
  t = c->right;

  c->right = this;
  this->left = t;

  this->calculateBalance();
  c->calculateBalance();

  if (parent == this)
  {
    obj->head = promote;
  }

  else if (parent->left == this)
  {
    parent->left = promote;
  }

  else if (parent->right == this)
  {
    parent->right = promote;
  }

}

 void AVLTree::rightRotate(AVLNode *target , AVLNode *node )
 {

   if (node == NULL)
   {
     node = head;
     if (!node)
     {
       return;
     }
   }

   if(target->left)
   {
     if (node == target)
     {
       node->rightRotateTranslate(node, this);
     }

     else if (target->value < node->value)
     {

       if (node->left == target)
       {

         node->left->rightRotateTranslate(node, this);
       }

       else
       {
         rightRotate(target, node->left);
       }

     }

     else if (target->value > node->value)
     {

       if (node->right == target)
       {
         node->right->rightRotateTranslate(node, this);
       }
       else
       {
         rightRotate(target, node->right);
       }

     }

   }

 }

  void AVLNode::balanceCheck(AVLTree *avlTreeClass)
  {
    if (this->balance > 1)
    {
      avlTreeClass->rightRotate(this);
    }

    else if (this->balance < -1)
    {
      avlTreeClass->leftRotate(this);
    }
  }


  bool AVLTree::balancedAdd(const int &value, AVLNode *node )
  {
    bool ret = 0;

    if (node == NULL)
    {
      node = head;
    }

    if (head == NULL )
    {
      head =  new AVLNode(value);
    }
    else
    {
      if (value < node->value)
      {
        if (node->left)
        {
          if (balancedAdd(value, node->left))
          {
            node->balance++;
          }
          node->left->balanceCheck(this);
        }
        else
        {
          node->balance++;
          node->left = new AVLNode(value);
        }
        ret = node->balance != 0;
      }

      else if (value > node->value)
      {
        if (node->right)
        {
          if (balancedAdd(value, node->right))
          {
            node->balance--;
          }
          node->right->balanceCheck(this);
        }
        else
        {
          node->balance--;
          node->right = new AVLNode(value);
        }
        ret = node->balance != 0;
      }

      else if (value == node->value)
      {
        node->count++;
        ret = false;
      }
    }

      if (node == head)
      {
        head->balanceCheck(this);
      }
    return ret;
  }

bool AVLTree::balanceRemove(const int &value, AVLNode *node)
 {
  int flag = 0;

  if (node == NULL)
  {
    node = head;
  }

  if (node->value == value)
  {
    flag = removeHelper(node, node);
  }

  else if (value < node->value)
  {
    if (node->left)
    {
      if (node->left->value == value)
      {
        flag = removeHelper(node->left, node);
      }
      else
      {
        flag = remove(value, node->left);
        flag = node->updateBalanceAck(flag, -1);

      }
    }
    node->left->balanceCheck(this);
  }
  else if (value > node->value)
  {
    if (node->right)
    {
      if (node->right->value == value )

      {
        flag = removeHelper(node->right, node);
      }
      else
      {
        flag = remove(value, node->right);
        flag = node->updateBalanceAck(flag, 1);
      }
    }


    node->right->balanceCheck(this);

  }

  if (node == this->head)
  {
    this->head->balanceCheck(this);
  }

  return flag;
}

void AVLTree::repair(AVLNode *node)
{
  if (node == NULL)
  {
    node = head;
    if (!node)
    {
      return;
    }
  }

  if (node->left)
  {
    repair(node->left);
  }

  if (node->right)
  {
    repair(node->right);
  }

  if (node->left )
  {
    while ( abs(node->left->balance) )
    {
      node->left->balanceCheck(this);
    }
    node->calculateBalance();
  }

  if (node->right)
  {
    while (abs(node->right->balance))
    {
      node->right->balanceCheck(this);
    }
    node->calculateBalance();
  }
}

void RBNode::display ()
{

  if (this->left)
  {
    this->left->display();
  }

  std::cout << " value " << this->value << "   color  " << this->color << '\n';

  if (this->right)
  {
    this->right->display();
  }

}

bool RBTree::contains (const int &value , RBNode *node)
{
  if (node == NULL)
  {
    node = root;
  }

  if (node )
  {
    if (node->value == value)
    {
      return true;
    }

    else if (value < node->value)
    {
      return contains(value, node->left);
    }

    else if (value > node->value)
    {
      return contains(value, node->right);
    }
  }

  return false;
}

int RBTree::add(const int &value, RBNode *node )
{
  int count = 0;

  if (node == NULL)
  {
    node = root;
  }

  if (root == NULL)
  {
    node = root = new RBNode(value);
  }

  else if (value < node->value )
  {
    if (node->left)
    {
      count += add(value, node->left);
    }
    else
    {
      node->left = new RBNode(value);
      return 1 + node->color;
    }
  }

  else if (value > node->value)
  {
    if (node->right)
    {
      count += add(value, node->right);
    }
    else
    {
      node->right = new RBNode(value);
      return 1 + node->color;
    }
  }

  else if (value == node->value)
  {
    node->count++;
  }

  blackHeightErrorHandler(count >= 2, node);

  if (node->color == 0 || count >= 2)
  {
    count = 0;
  }
  else
  {
    count += node->color;
  }

  return count;
}


void RBNode::leftRotate ( RBNode *parent , RBTree *obj )
{
  RBNode *c, *t;

  c = this->right;
  t = c->left;

  c->left = this;
  this->right = t;

  if (parent == this)
  {
    obj->root = c;
  }
  else if (parent->left == this)
  {
    parent->left = c;
  }
  else if (parent->right == this)
  {
    parent->right = c;
  }
}

void RBNode::rightRotate ( RBNode *parent , RBTree *obj )
{
  RBNode *c, *t;

  c = this->left;
  t = c->right;

  c->right = this;
  this->left = t;

  if (this == parent)
  {
    obj->root = c;
  }

  else if (parent->left == this)
  {
    parent->left = c;
  }

  else if (parent->right == this)
  {
    parent->right = c;
  }
}

int RBNode::rotationCode ()
{
  int left = 0, right = 0;

  if (this->left == NULL )
  {
    left = 0;
  }
  else if (this->left->color == 1)
  {
    left = 1;
  }

  if (this->right == NULL)
  {
    right = 0;
  }
  else if (this->right->color == 1)
  {
    right = 1;
  }

  if (this->left)
  {


    if (this->left->left)
    {
      if (this->left->color && this->left->left->color)
      {
          if (right)
        {
          return 5;
        }
        return 1;
      }
    }

    if (this->left->right)
    {
      if (this->left->color && this->left->right->color)
      {
        if (right)
        {
          return 5;
        }
        return 2;
      }
    }
  }

  if (this->right)
  {


    if (this->right->right)
    {
      if (this->right->color  && this->right->right->color)
      {
        if (left)
        {
          return 5;
        }
        return 3;
      }
    }

    if (this->right->left)
    {
      if (this->right->color && this->right->left->color)
      {
        if (left)
        {
          return 5;
        }
        return 4;
      }
    }
  }

  return 0;

}

RBNode* RBTree::findParent(RBNode * target, RBNode *node)
{
  if (node == NULL)
  {
    node = root;
  }

  if (node == target)
  {
    return node;
  }

  else if (target->value < node->value)
  {

    if (node->left)
    {
      if (node->left == target)
      {
        return node;
      }
      else
      {
        return findParent(target, node->left);
      }
    }

  }

  else if (target->value > node->value)
  {
    if (node->right)
    {
      if (node->right == target )
      {
        return node;
      }
      else
      {
        return findParent(target, node->right);

      }
    }
  }

  return NULL;
}

void RBTree::blackHeightErrorHandler (bool hasImbalance, RBNode *target)
{
  int op = 0;
  RBNode *promote = NULL;

  if (hasImbalance)
  {
    op = target->rotationCode();

    switch (op)
    {

      case 1:

        promote = target->left;
      // right rotate target
        target->rightRotate(findParent(target), this);
        break;

      case 2:
        promote = target->left->right;

      // left rotate child
        target->left->leftRotate(target, this);

      // right rotate target
        target->rightRotate(findParent(target), this);

        break;

      case 3:
        promote = target->right;

      // left rotate target
        target->leftRotate(findParent(target), this);
        break;

      case 4:
        promote = target->right->left;

      // right rotate child
        target->right->rightRotate( target , this );

      // left rotate target
        target->leftRotate( findParent(target) , this );

        break;

      case 5:
        target->color ^= 1;
        target->left->color ^= 1;
        target->right->color ^= 1;
        break;

      default:
        break;
    }
  }

  if (promote != NULL )
  {
    promote->color = 0;
    promote->left->color = promote->right->color = 1;
  }

  root->color = 0;

}





void RBTree::display (RBNode *node)
{
  this->root->display();
}


int main()
{
  rb_tree_test();
}
