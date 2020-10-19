
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



int main()
{

  avl_remove_test();

}




// bool RBTree::contains (const int &value , RBNode *node)
// {
//   if (node == NULL)
//   {
//     node = root;
//   }

//   if (node )
//   {
//     if (node->value == value)
//     {
//       return true;
//     }

//     else if (value < node->value)
//     {
//       return contains(value, node->left);
//     }

//     else if (value > node->value)
//     {
//       return contains(value, node->right);
//     }
//   }

//   return false;
// }


// int RBTree::add(const int &value, RBNode *node , RBNode *parent )
// {
//   int acc = 0;

//   if (root == NULL)
//   {
//     root = new RBNode(value);
//     root->color = 0;
//   }
//   else
//   {
//     if (node == NULL)
//     {
//       node = root;
//     }

//     if (value < node->value)
//     {
//       if (node->left)
//       {
//         acc = add(value, node->left, node) + +(node->left->color);

//         if (acc == 2 )
//         {
//           acc = 0;
//           if (node->right == NULL)
//           {
//             if (node->left && node->left->left)
//             {
//               translate(node, parent, 1);
//             }
//             else if (node->left && node->left->right)
//             {
//               translate(node, parent, 2);
//             }
//           }

//           else if ( ! node->right->color )
//           {
//             if (node->left && node->left->left)
//             {
//               translate(node, parent, 1);
//             }
//             else if (node->left && node->left->right)
//             {
//               translate(node, parent, 2);
//             }
//           }

//           else if (node->right->color)
//           {
//             translate(node, parent, 0);
//           }
//         }
//       }
//       else
//       {
//         node->left = new RBNode(value);
//         acc = 1;
//       }
//     }

//     else if (value > node->value)
//     {
//       if (node -> right)
//       {
//         acc = add(value, node->right, node) + +(node->right->color);

//         if (acc == 2)
//         {
//           acc = 0;

//           if (node->left == NULL)
//           {
//             if (node->right && node->right->right)
//             {
//               translate(node, parent, 3);
//             }
//             else if (node->right && node->right->left)
//             {
//               translate(node, parent, 4);
//             }
//           }
//           else if ( ! node->left->color )
//           {
//             if (node->right && node->right->right)
//             {
//               translate(node, parent, 3);
//             }
//             else if (node->right && node->right->left)
//             {
//               translate(node, parent, 4);
//             }
//           }
//           else if (node->left->color)
//           {
//             translate(node, parent, 0);
//           }
//         }
//       }
//       else
//       {
//         node->right = new RBNode(value);
//         acc = 1;
//       }
//     }
//     else if (value == node->value)
//     {
//       node->count++;
//       acc = 0;
//     }

//     if (node->color == 0)
//     {
//       acc = 0;
//     }
//   }

//   return acc;
// }


// void RBTree::translate(RBNode *node, RBNode *parent, int code)
// {
//   RBNode *c, *gc, *gc_l, *gc_r, *tree;

//   switch (code)
//   {

//   case 0:
//     node->color = 1;
//     node->left->color = node->right->color = 0;
//     break;

//   case 1:  // LEFT LEFT
//     c = node->left;
//     tree = c->right;

//     c->right = node;
//     node->left = tree;

//     c->color = 0;
//     c->left->color = c->right->color = 1;

//     if (parent == NULL)
//     {
//       root = c;
//     }
//     else if (parent->left == node)
//     {
//       parent->left = c;
//     }
//     else if (parent->right == node)
//     {
//       parent->right = c;
//     }

//     break;

//   case 2:  // LEFT RIGHT
//     c = node->left;
//     gc = node->left->right;
//     gc_l = gc->left;
//     gc_r = gc->right;

//     gc->left = c;
//     gc->right = node;
//     node->left = gc_r;
//     c->right = gc_l;

//     gc->color = 0;
//     gc->left->color = gc->right->color = 1;

//     if (parent == NULL)
//     {
//       root = gc;
//     }
//     else if (parent->left == node)
//     {
//       parent->left = gc;
//     }
//     else if (parent->right == node)
//     {
//       parent->right = gc;
//     }

//     break;


//   case 3: // RIGHT RIGHT
//     c = node->right;
//     tree = c->left;

//     c->left = node;
//     node->right = tree;

//     c->color = 0;
//     c->left->color = c->right->color = 1;

//     if (parent == NULL)
//     {
//       root = c;
//     }
//     else if (parent->left == node)
//     {
//       parent->left = c;
//     }
//     else if (parent->right == node)
//     {
//       parent->right = c;
//     }

//     break;

//   case 4: // RIGHT LEFT
//     c = node->right;
//     gc = node->right->left;
//     gc_l = gc->left;
//     gc_r = gc->right;

//     gc->right = c;
//     gc->left = node;
//     node->right = gc_l;
//     c->left = gc_r;

//     gc->color = 0;
//     gc->left->color = gc->right->color = 1;

//     if (parent == NULL)
//     {
//       root = gc;
//     }
//     else if (parent->left == node)
//     {
//       parent->left = gc;
//     }
//     else if (parent->right == node)
//     {
//       parent->right = gc;
//     }
//     break;

//     default:
//       break;

//   }

//   if (root->color)
//   {
//     root->color = false;
//   }

// }


// void RBTree::display (RBNode *node)
// {
//   if (node == NULL)
//   {
//     node = root;
//   }

//   if (node)
//   {
//     if (node->left)
//     {
//       display(node->left);
//     }
//     std::cout << "val -  " << node->value << " " << "color - " << node->color << '\n';

//     if (node->right)
//     {
//       display(node->right);
//     }
//    }
// }

// bool RBTree::remove(const int &value, RBNode *node)
// {
//   if (node == NULL)
//   {
//     node = root;
//   }
//   if (node)
//   {
//     if (node->value == value)
//     {
//       remove_helper(NULL, node);
//     }
//     else if (value < node->value)
//     {
//       if (node->left->value == value)
//       {
//         remove_helper(node, node->left);
//       }
//       else
//       {
//         remove(value, node->left);
//       }
//     }
//     else if (value > node->value)
//     {
//       if (node->right)
//       {
//         if (node->right->value == value)
//         {
//           remove_helper(node, node->right);
//         }
//         else
//         {
//           remove(value, node->right);
//         }
//       }
//     }
//   }
//   return false;
// }

// void RBTree::remove_helper(RBNode *parent, RBNode *node)
// {
//   RBNode *successor = NULL, *successor_parent;

//   if (node->count > 1)
//   {
//     node->count--;
//   }
//   else if (node->left == NULL && node->right == NULL)
//   {
//     successor = NULL;
//   }
//   else if (node->left && !node->right)
//   {
//     successor = node->left;
//   }
//   else if (node->right && !node->left)
//   {
//     successor = node->right;
//   }
//   else if (node->right && node->left)
//   {
//     if (node->right->left == NULL)
//     {
//       successor = node->right;
//       successor->left = node->left;
//     }
//     else
//     {
//       successor_parent = node->right;
//       while (successor_parent->left->left)
//       {
//         successor_parent = successor_parent->left;
//       }
//       successor = successor_parent->left;
//       successor_parent->left = successor_parent->left->left;
//       successor->left = node->left;
//       successor->right = node->right;
//       successor->count = node->count;
//     }
//   }

//   if (parent == NULL)
//   {
//     root = successor;
//   }
//   else if (parent->left == node)
//   {
//     parent->left = successor;
//   }
//   else if (parent->right == node)
//   {
//     parent->right = successor;
//   }
// }


