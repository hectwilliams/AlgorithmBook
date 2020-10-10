#include <iostream>
#include <math.h>


#include "chapter_19.h"

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

bool AVLTree::add(const int &value, AVLNode *node)
{

  if (node == nullptr)
  {
    node = head;
  }

  if (node == nullptr)
  {
    head = new AVLNode(value);
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

bool AVLTree::remove_helper(AVLNode *parent, AVLNode *node)
{
  AVLNode *successor = NULL, *parent_of_successor = NULL;
  // AVLNode *node = *target;

  if (node->count > 1)
  {
    node->count--;
    return false; // no updates to upstream nodes
  }

  if (node->left == NULL && node->right == NULL)
  {
    successor = NULL;
    if (parent == NULL)
    {
      this->head = successor;
    }
    else if (parent->left == node)
    {
      parent->left = successor;
    }
    else if (parent->right == node)
    {
      parent->right = successor;
    }

    if (parent)
    {
      return true; // update upstream nodes
    }
  }

  else if (node->left != NULL && node->right == NULL )
  {
    successor = node->left;
    if (parent == NULL)
    {
      this->head = successor;
    }
    else if (parent->left == node)
    {
      parent->left = successor;
    }
    else if (parent->right == node)
    {
      parent->right = successor;
    }

    if (parent)
    {
      return true; // update upstream nodes
    }

  }

  else if (node->right != NULL && node->left == NULL )
  {
    successor = node->right;
    if (parent == NULL)
    {
      this->head = successor;
    }
    else if (parent->left == node)
    {
      parent->left = successor;
    }
    else if (parent->right == node)
    {
      parent->right = successor;
    }

    if (parent)
    {
      return true;  // update upstream nodes
    }

  }

  else if (node->right != NULL && node->left != NULL)
  {
    if (node->right->left == NULL)
    {
      // NOTE: successor connected to predecessor

      // find successor
      {
        successor = node->right;
      }

      // update successor's parent's balance
      {
        node->balance++;
      }

      //promote successor
      {
        if (parent == NULL)
        {
          this->head = successor;
        }
        else if (parent->left == node)
        {
          parent->left = successor;
        }
        else if (parent->right == node)
        {
          parent->right = successor;
        }

        // copy predecessor's attributes (omit right and value attributes )
        successor->left = node->left;
        successor->balance = node->balance;
      }

      if (successor->balance == 0)
      {
        return true; // update upstream nodes
      }

    }
    else
    {

      // NOTE: successor is a leaf node

      // find successor
      {
        parent_of_successor = node->right;
        while (parent_of_successor->left->left)
        {
          parent_of_successor = parent_of_successor->left;
        }
        successor = parent_of_successor->left;
      }

      //update successor's parent's balance
      {
        if (parent_of_successor->left == successor)
        {
          parent_of_successor->balance--;
        }

        if (parent_of_successor->right == successor)
        {
          parent_of_successor->balance++;
        }
      }

      // update path balance ( from: predecessor(include) -> to: successor's parent(exclude) )
      {
        if (parent_of_successor->right == NULL)
        {
          update_balance_path(node, parent_of_successor);
        }
      }

      // remove successor from successor's parent
      {
        parent_of_successor->left = parent_of_successor->left->left;
      }

      // promote successor
      {
        if (parent == NULL)
        {
          this->head = successor;
        }
        else if (parent->left == node)
        {
          parent->left = successor;
        }
        else if (parent->right == node )
        {
          parent->right = successor;
        }

        // copy attributes (omit value)
        successor->left = node->left;
        successor->right = node->right;
        successor->balance = node->balance;
        successor->count = node->count;
      }

      if (parent_of_successor->balance == 0)
      {
        return true;  // update upstream nodes
      }

    }
  }

  delete(node);

  return false;

}

void AVLTree::update_balance_path(AVLNode *node, AVLNode *end)
{
  if (node && end)
  {
    while (node != end)
    {
      if (end->value < node->value)
      {
        node->balance--;
        return update_balance_path(node->left, end);
      }
      else
      {
        node->balance++;
        return update_balance_path(node->right, end);
      }
    }
  }
}


bool AVLTree::remove(const int &value, AVLNode *node)
{
  bool balanceFeedback = false;

  if (node == NULL)
  {
    node = head;
  }

  if (node)
  {
    if (node->value == value)
    {
       balanceFeedback = remove_helper(NULL, node);
    }

    else if (value < node->value)
    {
      if (node->left)
      {
        if (node->left->value == value)
        {
          balanceFeedback = remove_helper(node, node->left);
        }
        else
        {
          balanceFeedback = remove(value, node->left);
        }

        if (balanceFeedback)
        {
          node->balance--;
        }
       }
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        if (node->right->value == value)
        {
          balanceFeedback = remove_helper(node, node->right);
        }
        else
        {
          balanceFeedback = remove(value, node->right);
        }

        if (balanceFeedback)
        {
          node->balance++;
        }
      }
    }
  }

  return balanceFeedback;
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
    if ( (node->balance > 0) || (node->balance == 0 && node->left) )
    {
      return 1 + height(node->left);
    }

    else if ((node->balance < 0) || (node->balance == 0 && node->right) )
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


void AVLNode::setBalance()
{
  if (this->left && this->right)
  {
    this->balance = this->left->height() - this->right->height();
  }

  else if (this->left)
  {
    this->balance = 1 + this->left->height();
  }

  else if (this->right)
  {
    this->balance = -(1 + this->right->height());
  }

  else if (this->right == NULL && this->left == NULL)
  {
    this->balance = 0;
  }
}

void AVLNode::grandchild_promote()
{
  AVLNode *child, *grandchild, *tree;

  if (this->balance > 0)  // PARENT -> LEFT
  {
    if (this->left->balance > 0)  // PARENT - > LEFT -> LEFT
    {
      // RIGHT
      // child = this->left;
      // grandchild = child->left;
      // tree = grandchild->right;

      // grandchild->right = child;
      // child->left = tree;
      // this->left = grandchild;

      // child->setBalance();
      // grandchild->setBalance();
      // this->setBalance();
    }
    else if (this->left->balance < 0)  // PARENT -> LEFT -> RIGHT
    {
      // LEFT
      child = this->left;
      grandchild = child->right;
      tree = grandchild->left;

      grandchild->left = child;
      child->right = tree;
      this->left = grandchild;

      child->setBalance();
      grandchild->setBalance();
      this->setBalance();

    }
  }

  else if (this->balance < 0)  // PARENT -> RIGHT
  {
    if (this->right->balance > 0)  /// PARENT -> RIGHT -> LEFT
    {
      // RIGHT
      child = this->right;
      grandchild = child->left;
      tree = grandchild->right;

      grandchild->right = child;
      child->left = tree;
      this->right = grandchild;

      child->setBalance();
      grandchild->setBalance();
      this->setBalance();
    }

    else if (this->right->balance < 0) // PARENT ->RIGHT -> RIGHT
    {
      // LEFT
      // child = this->right;
      // grandchild = child->right;
      // tree = grandchild->left;

      // grandchild->left = child;
      // child->right = tree;
      // this->right = grandchild;

      // child->setBalance();
      // grandchild->setBalance();
      // this->setBalance();
    }
  }
}


void AVLTree::left_rotate(AVLNode *target, AVLNode *node )
{
  struct AVLNode *parent_of_target = NULL;
  struct AVLNode *target_ref = NULL;
  struct AVLNode *tree = NULL;
  struct AVLNode *child = NULL;

  if (!node)
  {
    node = head;
  }

  if (node)
  {
    if (node == target)
    {
      target_ref = node;
    }
    else if (node->left == target)
    {
      parent_of_target = node;
      target_ref =  node->left;
    }
    else if (node->right == target)
    {
      parent_of_target = node;
      target_ref = node->right;
    }
    else if (target->value < node->value)
    {
      return left_rotate(target, node->left);
    }
    else if (target->value > node->value)
    {
      return left_rotate(target, node->right);
    }
  }

  if (target_ref)
  {
    target_ref->grandchild_promote();  // AVLTree class is friend of AVLNode

    child = target_ref->right;
    tree = child->left;

    child->left = target_ref;
    target_ref->right = tree;

    target_ref->setBalance();
    child->setBalance();

    if (parent_of_target == NULL)
    {
      head = child;
    }
    else if (parent_of_target->left == target_ref)
    {
      parent_of_target->left = child;
      parent_of_target->setBalance();
    }
    else if (parent_of_target->right == target_ref)
    {
      parent_of_target->right = child;
      parent_of_target->setBalance();
    }
  }
}

void AVLTree::right_rotate(AVLNode *target, AVLNode *node )
{
  struct AVLNode *parent_of_target = NULL;
  struct AVLNode *target_ref = NULL;
  struct AVLNode *tree = NULL;
  struct AVLNode *child = NULL;

  if (!node)
  {
    node = head;
  }

  if (node)
  {
    if (node == target)
    {
      target_ref = node;
    }

    else if (node->left == target)
    {
      parent_of_target = node;
      target_ref = node->left;
    }

    else if (node->right == target)
    {
      parent_of_target = node;
      target_ref = node->right;
    }

    else if (target->value < node->value)
    {
      return right_rotate(target, node->left);
    }

    else if (target->value > node->value)
    {
      return right_rotate(target, node->right);
    }
  }

  if (target_ref)
  {
    target_ref->grandchild_promote();

    child = target_ref->left;
    tree = child->right;

    child->right = target_ref;
    target_ref->left = tree;

    target_ref->setBalance();
    child->setBalance();

    if (parent_of_target == NULL)
    {
      head = child;
    }
    else if (parent_of_target->left == target_ref)
    {
      parent_of_target->left = child;
      parent_of_target->setBalance();
    }
    else if (parent_of_target->right == target_ref)
    {
      parent_of_target->right = child;
      parent_of_target->setBalance();
    }

  }

}

bool AVLTree::balanced_add(const int &value, AVLNode *node)
{
  if (node == nullptr)
  {
    node = head;
  }

  if (node == nullptr)
  {
    head = new AVLNode(value);
  }
  else
  {
    if (value < node->value)
    {
      if (node->left)
      {
       if (balanced_add(value, node->left))
       {
         if (node->left->balance < -1)
         {
           left_rotate(node->left);
           node->setBalance();
         }
         else if (node->left->balance > 1)
         {
           right_rotate(node->left);
           node->setBalance();
         }
         else
         {
          node->balance++;
         }
         return node->balance != 0;
       }
      }
      else
      {
        node->left = new AVLNode(value);
        node->balance++;
        return node->balance != 0;
      }
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        if (balanced_add(value, node->right))
        {
          if (node->right->balance < -1)
          {
            left_rotate(node->right);
            node->setBalance();
          }
          else if (node->right->balance > 1)
          {
            right_rotate(node->right);
            node->setBalance();
          }
          else
          {
            node->balance--;
          }
          return node->balance != 0;
        }
      }
      else
      {
        node->right = new AVLNode(value);
        node->balance--;
        return node->balance != 0;
      }
    }

    else if (value == node->value)
    {
      node->count++;
    }

    // ROOT NODE CHECK
    if (node->balance < -1)
    {
      left_rotate(node);
    }
    else if (node->balance > 1)
    {
      right_rotate(node);
    }
  }
  return false;
}

bool AVLTree::balanced_remove(const int &value, AVLNode *node)
{
  bool balanceFeedback = false;

  if (node == NULL)
  {
    node = head;
  }

  if (node)
  {
    if (node->value == value)
    {
       balanceFeedback = remove_helper(NULL, node);
    }

    else if (value < node->value)
    {
      if (node->left)
      {
        if (node->left->value == value)
        {
          balanceFeedback = remove_helper(node, node->left);
        }
        else
        {
          balanceFeedback = balanced_remove(value, node->left);
        }

        if (balanceFeedback)
        {
          if (node->left)
          {
            if (node->left->balance > 1)
            {
              right_rotate(node->left);
              node->setBalance();

            }
            else if (node->left->balance < -1)
            {
              left_rotate(node->left);
              node->setBalance();
            }
            else
            {
              node->balance--;
            }
          }
          else
          {
            node->balance--;
          }
        }
       }
    }

    else if (value > node->value)
    {
      if (node->right)
      {
        if (node->right->value == value)
        {
          balanceFeedback = remove_helper(node, node->right);
        }
        else
        {
          balanceFeedback = balanced_remove(value, node->right);
        }

        if (balanceFeedback)
        {
          if (node->right)
          {
            if (node->right->balance > 1)
            {
              right_rotate(node->right);
              node->setBalance();
            }
            else if (node->right->balance < -1)
            {
              left_rotate(node->right);
              node->setBalance();
            }
            else
            {
              node->balance++;
            }
          }
          else
          {
            node->balance++;
          }
        }
      }
    }
  }

  if (node == this->head)
  {
    if (node->balance > 1)
    {
      right_rotate(node);
    }
    else if (node->balance < -1)
    {
      left_rotate(node);
    }
  }

  return balanceFeedback;
}

void AVLTree::repair(AVLNode *node)
{
  if (node == NULL)
  {
    node = head;
  }

  if (node)
  {
    if (node->balance > 0)
    {
      repair(node->left);

      if (node->left->balance > 1)
      {
        right_rotate(node->left);
        node->setBalance();
      }
      else if (node->left->balance < -1)
      {
        left_rotate(node->left);
        node->setBalance();
      }
    }

    else if (node->balance < 0)
    {
      repair(node->right);

      if (node->right->balance > 1)
      {
        right_rotate(node->right);
        node->setBalance();
      }
      else if (node->right->balance < -1)
      {
        left_rotate(node->right);
        node->setBalance();
      }
    }

    else if (node->balance == 0)
    {
      return;
    }

    if (node == this->head)
    {
      if (node->balance > 1)
      {
        right_rotate(node);
      }
      else if (node->balance < -1)
      {
        left_rotate(node);
      }
    }

  }



 }




int main()
{
  AVLTree tree;

  tree.add(200);
  tree.add(100);
  tree.add(25);
  tree.add(120);
  tree.add(110);
  tree.add(140);
  tree.add(105);

  tree.display();
  tree.remove(100);
  std::cout << '\n';
  tree.display();
}
