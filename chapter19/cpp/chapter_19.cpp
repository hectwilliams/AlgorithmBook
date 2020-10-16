
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
      node->balance++;
    }
  }

  else if (node->left)
  {
    del = node->left;
    node->copyAttributes(   del);
    if (!isRoot)
    {
      node->balance--;
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
  return isValid
  ;
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
    std::cout << "  flag - " << flag << '\n';

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
  if (node == NULL)
  {
    node = this;
  }

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




int main()
{

  avl_remove_test();

}



// bool AVLTree::balanced_add(const int &value, AVLNode *node)
// {
//   if (node == nullptr)
//   {
//     node = head;
//   }

//   if (node == nullptr)
//   {
//     head = new AVLNode(value);
//   }
//   else
//   {
//     if (value < node->value)
//     {
//       if (node->left)
//       {
//        if (balanced_add(value, node->left))
//        {
//          if (node->left->balance < -1)
//          {
//            left_rotate(node->left);
//            node->setBalance();
//          }
//          else if (node->left->balance > 1)
//          {
//            right_rotate(node->left);
//            node->setBalance();
//          }
//          else
//          {
//           node->balance++;
//          }
//          return node->balance != 0;
//        }
//       }
//       else
//       {
//         node->left = new AVLNode(value);
//         node->balance++;
//         return node->balance != 0;
//       }
//     }

//     else if (value > node->value)
//     {
//       if (node->right)
//       {
//         if (balanced_add(value, node->right))
//         {
//           if (node->right->balance < -1)
//           {
//             left_rotate(node->right);
//             node->setBalance();
//           }
//           else if (node->right->balance > 1)
//           {
//             right_rotate(node->right);
//             node->setBalance();
//           }
//           else
//           {
//             node->balance--;
//           }
//           return node->balance != 0;
//         }
//       }
//       else
//       {
//         node->right = new AVLNode(value);
//         node->balance--;
//         return node->balance != 0;
//       }
//     }

//     else if (value == node->value)
//     {
//       node->count++;
//     }

//     // ROOT NODE CHECK
//     if (node->balance < -1)
//     {
//       left_rotate(node);
//     }
//     else if (node->balance > 1)
//     {
//       right_rotate(node);
//     }
//   }
//   return false;
// }

// bool AVLTree::balanced_remove(const int &value, AVLNode *node)
// {
//   bool balanceFeedback = false;

//   if (node == NULL)
//   {
//     node = head;
//   }

//   if (node)
//   {
//     if (node->value == value)
//     {
//        balanceFeedback = remove_helper(NULL, node);
//     }

//     else if (value < node->value)
//     {
//       if (node->left)
//       {
//         if (node->left->value == value)
//         {
//           balanceFeedback = remove_helper(node, node->left);
//         }
//         else
//         {
//           balanceFeedback = balanced_remove(value, node->left);
//         }

//         if (balanceFeedback)
//         {
//           if (node->left)
//           {
//             if (node->left->balance > 1)
//             {
//               right_rotate(node->left);
//               node->setBalance();

//             }
//             else if (node->left->balance < -1)
//             {
//               left_rotate(node->left);
//               node->setBalance();
//             }
//             else
//             {
//               node->balance--;
//             }
//           }
//           else
//           {
//             node->balance--;
//           }
//         }
//        }
//     }

//     else if (value > node->value)
//     {
//       if (node->right)
//       {
//         if (node->right->value == value)
//         {
//           balanceFeedback = remove_helper(node, node->right);
//         }
//         else
//         {
//           balanceFeedback = balanced_remove(value, node->right);
//         }

//         if (balanceFeedback)
//         {
//           if (node->right)
//           {
//             if (node->right->balance > 1)
//             {
//               right_rotate(node->right);
//               node->setBalance();
//             }
//             else if (node->right->balance < -1)
//             {
//               left_rotate(node->right);
//               node->setBalance();
//             }
//             else
//             {
//               node->balance++;
//             }
//           }
//           else
//           {
//             node->balance++;
//           }
//         }
//       }
//     }
//   }

//   if (node == this->head)
//   {
//     if (node->balance > 1)
//     {
//       right_rotate(node);
//     }
//     else if (node->balance < -1)
//     {
//       left_rotate(node);
//     }
//   }

//   return balanceFeedback;
// }

// void AVLTree::repair(AVLNode *node)
// {
//   if (node == NULL)
//   {
//     node = head;
//   }

//   if (node)
//   {
//     if (node->balance > 0)
//     {
//       repair(node->left);

//       if (node->left->balance > 1)
//       {
//         right_rotate(node->left);
//         node->setBalance();
//       }
//       else if (node->left->balance < -1)
//       {
//         left_rotate(node->left);
//         node->setBalance();
//       }
//     }

//     else if (node->balance < 0)
//     {
//       repair(node->right);

//       if (node->right->balance > 1)
//       {
//         right_rotate(node->right);
//         node->setBalance();
//       }
//       else if (node->right->balance < -1)
//       {
//         left_rotate(node->right);
//         node->setBalance();
//       }
//     }

//     else if (node->balance == 0)
//     {
//       return;
//     }

//     if (node == this->head)
//     {
//       if (node->balance > 1)
//       {
//         right_rotate(node);
//       }
//       else if (node->balance < -1)
//       {
//         left_rotate(node);
//       }
//     }

//   }
//  }


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


