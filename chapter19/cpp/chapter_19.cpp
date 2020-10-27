
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

int RBTree::add(const int &value, RBNode *node , RBNode *parent)
{
  int count = 0;

  if (node == NULL)
  {
    parent = node = root;
  }

  if (root == NULL)
  {
    node = root = new RBNode(value);
  }

  else if (value < node->value )
  {
    if (node->left)
    {
      count = add(value, node->left, node);
      count += node->left->color;
    }
    else
    {
      node->left = new RBNode(value);
      return 1 ;
    }
  }

  else if (value > node->value)
  {
    if (node->right)
    {
      count = add(value, node->right, node);
      count += node->right->color;

    }
    else
    {
      node->right = new RBNode(value);
      return 1;
    }
  }

  else if (value == node->value)
  {
    node->count++;
    return 0;
  }

  blackHeightErrorHandler(count >= 2, node, parent);

  if (node->color == 0 || count >= 2)
  {
    count = 0;
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
  RBNode *a, *b;

  a = b = NULL;

  if (node == NULL)
  {
    node = this->root;
  }

  if (node)
  {

    if (node->left)
    {
      a = this->findParent(target, node->left);
    }

    if (node->right)
    {
      b = this->findParent(target, node->right);
    }

    if (node->right == target)
    {
      return node;
    }

    if (node->left == target)
    {
      return node;
    }

  }

  if (a)
  {
    return a;
  }

  return b;

}

void RBTree::blackHeightErrorHandler (bool hasImbalance, RBNode *target, RBNode *targetParent)
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
        target->rightRotate(targetParent, this);

        break;

      case 2:
        promote = target->left->right;

      // left rotate child
        target->left->leftRotate(target, this);

      // right rotate target
        target->rightRotate(targetParent, this);

        break;

      case 3:
        promote = target->right;

      // left rotate target
        target->leftRotate(targetParent, this);
        break;

      case 4:
        promote = target->right->left;

      // right rotate child
        target->right->rightRotate( target , this );

      // left rotate target
        target->leftRotate( targetParent , this );

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

int RBNode::successor()
{
  RBNode *runner = this->right;
  while (runner->left)
  {
    runner = runner->left;
  }
  return runner->value;
}

void RBNode::copy(const RBNode *src)
{
  if (src)
  {
    this->left = src->left;
    this->right = src->right;
    this->count = src->count;
    this->value = src->value;
  }
}

void RBTree::remove(const int &value, RBNode *node  , RBNode *parent )
{
  if (!node)
  {
    parent = node = root;
  }

  if (node)
  {
    if (value == node->value)
    {
      if (node->count > 1)
      {
        node->count--;
      }
      else
      {
        removeHelper(node, parent);
      }
    }

    else if (value < node->value && node->left)
    {
      remove(value, node->left, node);
    }

    else if (value > node->value && node->right)
    {
      remove(value, node->right, node);
    }
  }
}

void RBTree::removeHelper(RBNode *target, RBNode *parent)
{
  bool isDoubleBlack;
  int successor;

  if (target->left && target->right)
  {
    successor  = target->successor();
    this->remove(successor);
    target->value = successor;
  }

  else if (target->left)
  {
    isDoubleBlack = (target->color || target->left->color) == 0;
    target->copy(target->left);

    if (!isDoubleBlack)
    {
      target->color = 0;
    }
    else
    {
      removeHelperBalance(target, 1, parent);
    }
  }


  else if (target->right )
  {
    isDoubleBlack = (target->color || target->right->color) == 0;
    target->copy(target->right);

    if (!isDoubleBlack)
    {
      target->color = 0;
    }
    else
    {
      removeHelperBalance(target, -1, parent);
    }
  }

  else if ( !target->left && !target->right)
  {
    isDoubleBlack = target->color == 0;

    if (this->root == target)
    {
      this->root = NULL;
    }

    else if (parent->left == target)
    {
      parent->left = NULL;

      if (isDoubleBlack)
      {
        removeHelperBalance(NULL, 1, parent);
      }
    }

    else if (parent->right == target)
    {
      parent->right = NULL;

      if (isDoubleBlack)
      {
        removeHelperBalance (NULL, -1, parent);
      }

    }

  }

}

void RBTree::removeHelperBalance (RBNode *u, int dir, RBNode *p )
{
  RBNode *s;
  int sibColorLeft, sibColorRight, sibColor;
  int tmp;
  RBNode *p_parent = findParent(p);

  if (this->root == u)
  {
    if (this->root)
    {
      this->root->color = 0;
    }
    return;
  }

  if (dir == -1)
  {
    s = p->left;
  }

  if (dir == 1)
  {
    s = p->right;
  }

  // find coloers of sibling

  if (s)
  {
    sibColor = s->color;

    if (s->left)
    {
      sibColorLeft = s->left->color;
    }
    else
    {
      sibColorLeft = 0;
    }

    if (s->right)
    {
      sibColorRight = s->right->color;
    }
    else
    {
      sibColorRight = 0;
    }
  }

  else
  {
    return;
  }

  if (sibColor == 0)
  {


    if (sibColorLeft == 0 && sibColorRight == 0)    /* CASE: SIBLING BLACK WITH BLACK CHILDREN */
    {

      // recolor sibling red
      s->color = 1;

      // red parent recolor
      if (p->color == 1)
      {
        p->color = 0;
      }

      // black parent
      else if (p->color == 0)
      {
        u = p;

        p = this->findParent(p);

        if (p->left == u)
        {
          dir = 1;
        }

        if (p->right == u)
        {
          dir = -1;
        }

        return this->removeHelperBalance(u, dir, p);
      }

    }

    else if (sibColorLeft == 1 && sibColorRight == 1)
    {
      if (dir == -1)
      {
        // SWAP COLORS BETWEEN PARENT AND SIBLING
        s->colorSwap(p);

        // SET SIBLING CHILD BLACK
        s->left->color = 0;

        // RIGHT ROTATE PARENT
        p->rightRotate( findParent(p) , this);

      }

      if (dir == 1)
      {
        // SWAP COLORS BETWEEN PARENT AND SIBLING
        s->colorSwap(p);

        // SET SIBLING CHILD BLACK
        s->right->color = 0;

        // LEFT ROTATE PARENT
        p->leftRotate( findParent(p) , this) ;

      }

    }

    else if (sibColorLeft == 1)  /* CASE: SIBLING BLACK WITH RED CHILDREN */
    {
      if (dir == -1) // LEFT LEFT CASE
      {
        // SET SIBLING CHILD BLACK
        s->left->color = 0;

        // EXCHANGE BETWEEN PARENT AND SIBLING
        s->colorSwap(p);

        // RIGHT ROTATE PARENT
        p->rightRotate( findParent(p) , this);

      }

      if (dir == 1) // right left case
      {
        // SET SIBLING RED
        s->color = 1;

        // SET SIBLING CHILD BLACK
        s->left->color = 0;

        // RIGHT ROTATE SIBLING
        s->rightRotate(p, this);

        // RECURSION
        removeHelperBalance(u, dir, p);
      }
    }

    else if (sibColorRight == 1)  /* CASE: SIBLING BLACK WITH RED CHILDREN */
    {
      if (dir == 1)  // RIGHT RIGHT CASE
      {
        // SET SIBLING CHILD BLACK
        s->right->color = 0;

        // EXCHANGE COLOR BETWEEN PARENT AND SIBLING
        s->colorSwap(p);

        // LEFT ROTATE PARENT
        p->leftRotate(findParent(p), this);
      }

      if (dir == -1)  // LEFT RIGHT CASE
      {
        // SET SIBLING RED
        s->color = 1;

        // SET SIBLING CHILD BLACK
        s->right->color = 0;

        // LEFT ROTATE SUBLING
        s->leftRotate(p, this);

        // RECURSION
        removeHelperBalance(u, dir, p);
      }

    }
  }

  if (sibColor == 1)  /* CASE: SIBLING RED */
  {

    // EXCHANGE PARENT AND SIBLING COLORS
    s->colorSwap(p);

    // RIGHT IMBALANCE
    if (dir == 1)
    {
      // LEFT ROTATE
      p->leftRotate(findParent(p), this);

      // RECURSION
      removeHelperBalance(p->left, 1, p);
    }

    // LEFT IMBALANCE
    if (dir == -1 )
    {
      // RIGHT ROTATE
      p->rightRotate(findParent(p), this);

      // RECURSION
      removeHelperBalance(p->right, -1, p);
    }

  }

}

void RBNode::colorSwap(RBNode *node)
{
  int color;
  if (node)
  {
    color = this->color;
    this->color = node->color;
    node->color = color;
  }
}


void SplayTree::display()
{
  if (root)
  {
    root->display();
  }
}

void SplayNode::display()
{
  if (this->left)
  {
    this->left->display();
  }

  std::cout << this->value << '\n';

  if (this->right)
  {
    this->right->display();
  }
}


SplayTree & SplayTree::add (const int & value)
{
  SplayNode *newRoot = new SplayNode(value);

  if (root)
  {
    if (root->value < value)
    {
      newRoot->left = root;
    }

    else
    {
      newRoot->right = root;
    }
  }

  root = newRoot;

  return *this;
}

int SplayNode:: successor()
{
  SplayNode *runner = this->right;
  while (runner->left)
  {
    runner = runner->left;
  }
  return runner->value;
}

void SplayNode::copy(SplayNode *src)
{
  if (src)
  {
    this->left = src->left ;
    this->right = src->right;
    this->value = src->value;
  }
}


void SplayNode::leftRotate (SplayNode *parent, SplayTree * const splayTreeClass)
{
  SplayNode *t, *c;

  c = this->right;
  t = c->left;

  c->left = this;
  this->right = t;

  if (parent == NULL)
  {
    splayTreeClass->root = c;
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

void SplayNode::rightRotate (SplayNode *parent, SplayTree * const splayTreeClass)
{

  SplayNode *t, *c;

  c = this->left;
  t = c->right;

  c->right = this;
  this->left = t;

  if (parent == NULL)
  {
    splayTreeClass->root = c;
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

void SplayTree::splay(int value, SplayNode *node , SplayNode *parent )
{
  if (value == node->value)
  {
    return;
  }

  else if (value < node->value && node->left)
  {
    splay(value, node->left, node);

    if (node->left->value != value)
    {
      node->rightRotate(parent, this);
    }
  }

  else if (value > node->value && node->right)
  {
    splay(value, node->right, node);

    if (node->right->value != value)
    {
      node->leftRotate(parent, this);
    }
  }
}

void SplayTree::remove (int value, SplayNode *node, SplayNode *parent)
{
  splay(value, root, NULL);
  remove_(value, root, NULL);
}

void SplayTree::remove_ (int value, SplayNode *node, SplayNode *parent)
{
  if (node == NULL)
  {
    node = this->root;
  }

  if (node)
  {
    if (value == node->value)
    {
      remove_helper(node, parent);
    }

    else if (value < node->value && node->left)
    {
      this->remove_(value, node->left, node);
    }

    else if (value > node->value && node->right)
    {
      this->remove_(value, node->right, node);
    }
  }
}

void SplayTree::remove_helper(SplayNode *target, SplayNode *parent)
{
  int successor;
  void *del = NULL;

  if (target->right && target->left)
  {
    successor = target->successor();
    remove(successor);
    target->value = successor;
  }

  else if (target->right)
  {
    del = target->right;
    target->copy(target->right);
  }

  else if (target->left)
  {
    del = target->right;
    target->copy (target->left);
  }

  else if (target->right == NULL && target->left == NULL)
  {
    del = target;

    if (parent == NULL)
    {
      this->root = NULL;
    }

    else if (parent->left == target)
    {
      parent->left = NULL;
    }

    else if (parent->right == target)
    {
      parent->right = NULL;
    }
  }

  if (del)
  {
    delete(del);
  }

}



int main()
{
  splay_tree_test();
}
