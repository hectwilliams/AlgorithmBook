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
    if (node->balance > 0)
    {
      return 1 + height(node->left);
    }

    if (node->balance < 0)
    {
      return 1 + height(node->right);
    }
  }
  return 0;
}

bool AVLNode::isBalanced(AVLNode *node)
{
  double left_height = 0, right_height = 0;

  if (node == NULL)
  {
    node = this;
  }

  if (node)
  {
    if (node->left)
    {
      left_height = height(node->left);
    }

    if (node->right)
    {
      right_height = height(node->right);
    }
  }

  if (abs(left_height - right_height) > 1)
  {
    return false;
  }

  return true;

}

bool AVLTree::isBalanced()
{
  if (head)
  {
    return head->isBalanced();
  }
  return false;
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
