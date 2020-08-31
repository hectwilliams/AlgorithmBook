#include "chapter_15.h"


void BST::display(BSTNode *node)
{

  node = !node ? root : node;

  if (node)
  {
    if (node->left)
    {
      display(node->left);
    }

    std::cout << node->value << '\n';

    if (node->right)
    {
      display(node->right);
    }
  }
}

void BST::add (int value, BSTNode *node)
{
  BSTNode *newNode = new BSTNode(value);

  node = !node ? root : node;

  if (node == NULL)
  {
    root = newNode;
  }
  else
  {
    if (value < node->value)
    {
      if (node->left)
      {
        add(value, node->left);
      }
      else
      {
        node->left = newNode;
      }
    }
    else
    {
      if (node->right)
      {
        add(value, node->right);
      }
      else
      {
        node->right = newNode;
      }
    }
  }
}

 void BST::addNode(BSTNode *targetNode, BSTNode *node)
{
  node = !node ? root : node;

  if (!node)
  {
    root = targetNode;
  }
  else
  {
    if (targetNode->value < node->value)
    {
      if (node->left)
      {
        addNode(targetNode, node->left);
      }
      else
      {
        node->left = targetNode;
      }
    }
    else
    {
      if (node->right)
      {
        addNode(targetNode, node->right);
      }
      else
      {
        node->right = targetNode;
      }
    }
  }
}


BSTNode *BST::remove_successor (BSTNode *node)
{

  BSTNode *prev = node;

  if (node->right)
  {
    node = node->right;

    while (node->left)
    {
      prev = node;
      node = node->left;
    }

    if (prev->left == node)
    {
      prev->left = NULL;
    }
    else
    {
      prev->right = NULL;
    }
  }
  return node;
}

int BST::height(BSTNode *node)
{
  int left, right;


  left = right = 0;
  node = !node ? root : node;

  if (node->left)
  {
    left = 1 + height(node->left);
  }

  if (node->right)
  {
    right = 1 + height(node->right);
  }

  return right > left ? right : left;
}

void BST::remove(int value, BSTNode *node,  BSTNode *prev)
{
  BSTNode *successor;
  node = !node ? root : node;

  if (node)
  {
    if (node->value == value)

    {
      if (node->left && node->right)
      {

        successor = remove_successor(node);
        successor->left = node->left;
        successor->right = node->right;

        if (prev == NULL)
        {
          root = successor;
        }
        else
        {
          if (prev->left == node)
          {
            prev->left = successor;
          }
          else
          {
            prev->right = successor;
          }
        }
      }
      else if (!!node->left ^ !! node->right)
      {
        if (prev == NULL)
        {
          root = !node->left ? node->right : node->left;
        }
        else
        {
          if (prev->left == node )
          {
            prev->left = !node->left ? node->right : node->left;
          }
          else
          {
            prev->right = !node->left ? node->right : node->left;
          }
        }
      }
      else if (!node->right && !node->left)
      {
        if (prev == NULL)
        {
          root = NULL;
        }
        else
        {
          if (prev->left == node)
          {
            prev->left = NULL;
          }
          else
          {
            prev->right = NULL;
          }
        }
      }
    }
    else
    {
      if (value < node->value)
      {
        if (node->left)
        {
          remove(value, node->left, node);
        }
      }
      else
      {
        if (node->right)
        {
          remove(value, node->right, node);
        }
      }
    }
  }

}

bool BST::is_full_tree(BSTNode *node)
{
  bool isFull = false;
  node = !node ? root : node;

  if (node)
  {
    isFull = (node->right && node->left) ^ (!node->left && node->right);

    if (node->left)
    {
      isFull &= is_full_tree(node->left);
    }
    if (node->right)
    {
      isFull &= is_full_tree(node->right);
    }
  }
  return isFull;
}

bool BST::is_complete_tree(BSTNode *node)
{
  bool isComplete = false;
  int left = 0, right= 0;

  if (node)
  {
    if (node->left)
    {
      left = height(node->left);
    }
    if (node->right )
    {
      right = height(node->right);
    }

    isComplete = left >= right;

    if (node->left)
    {
      isComplete &= is_complete_tree(node->left);
    }

    if (node->right)
    {
      isComplete &= is_complete_tree(node->right);
    }
  }

  return isComplete;
}


bool BST::bstRepairReinsert (BSTNode *node)
{
 BSTNode *tmp_insertionNode;

 node = !node? root : node;

 if (node)
 {
   if (node->left)
   {
     tmp_insertionNode = node->left;
     node->left = NULL;
     bstRepairReinsert(tmp_insertionNode );
   }

   if (node->right )
   {
     tmp_insertionNode = node->right;
     node->right = NULL;
     bstRepairReinsert(tmp_insertionNode);
   }
  }

  addNode(node, root);

}

bool BST::bstRepair (BSTNode *node)
{

  bool repaired = false;
  BSTNode *subtree;

  node = !node? root : node;

  if (node)
  {
    if (node->left)
    {
      if (node->left->value >= node->value)
      {
        repaired  |=1;
        subtree = node->left;
        node->left = NULL;
        bstRepairReinsert(subtree);
      }
    }

    if (node->right)
    {
      if (node->right->value < node->value)
      {
        repaired |= 1;
        subtree = node->right;
        node->right = NULL;
        bstRepairReinsert(subtree);
      }
    }

    if (node)
    {
      if (node->left)
      {
        repaired |= bstRepair(node->left);
      }
    }

    if (node->right)
    {
      repaired |= bstRepair(node->right);
    }
  }
  return repaired;
}

int BST::smallest_difference (BSTNode *node, int *min )

{
  int left = INT32_MAX, right = INT32_MAX;
  int data;

  node = !node ? root : node;

  if (!min)
  {
    data = INT32_MAX;
    min = &data;
  }

  if (node)
  {

    if (node->left)
    {
      left = std::abs(node->value - node->left->value);
      if (*min > left)
      {
        *min = left;
      }
    }

    if (node->right)
    {
      right = std::abs(node->value - node->right->value);
      if (*min > right)
      {
        *min = right;
      }
    }

   if (node->left)
    {
      smallest_difference(node->left, min);
    }

    if (node->right)
    {
      smallest_difference(node->right, min);
    }
  }

  return  *min;
}

int BST::closestValue (int value, BSTNode *node, std::array<int,1> closest)
{
  int diff;

  if (node == NULL)
  {
    node = root;
    closest[0] = 0;
  }

  if (node)
  {
    diff = std::abs(value - node->value);

    if (diff < std::abs(value - closest[0]))
    {
      closest[0] = node->value;
    }

    if (node->left)
    {
      closestValue(value, node->left, closest);
    }

    if (node->right)
    {
      closestValue(value, node->right, closest);
    }
  }
  return closest[0];
}

BSTNode * BST::partition_around_value(int value, BSTNode *node, BSTNode *prev)
{
  node = !node ? root : node;
  BSTNode *result;

  if (node)
  {
    if (value < node->value)
    {
      if (node->left )
      {
        return partition_around_value(value, node->left, node);
      }
      else
      {
        result = node;
      }
    }
    else if (value > node->value)
    {
      if (node->right)
      {
        return partition_around_value(value, node->right, node);
      }
      else
      {
        result = node;
      }
    }
    else
    {
      if (prev)

      {
        if (prev->left == node)
        {
          result = node;
          prev->left = NULL;
        }

        if (prev->right == node)
        {
          result = node;
          prev->right = NULL;
        }
      }
      else
      {
        result = node;
        root= NULL;
      }
    }
  }
  return result;
 }

BST * BST::partition_evenly(BSTNode *node, BST *partitionA , BST *partitionB , int count )
{
  node = !node ? root : node;

  if (!partitionA)
  {
    partitionA = new BST();
    partitionB = new BST();
  }

  if (node)
  {
    if (node->left)
    {
      partition_evenly(node->left, partitionA, partitionB, ++count);
      node->left = NULL;
    }

    if (node->right)
    {
      partition_evenly(node->right, partitionA, partitionB, ++count);
      node->right = NULL;
    }

    if (count % 2 == 0)
    {
      partitionA->addNode(node);
    }
    else
    {
      partitionB->addNode(node);
    }
  }

  if (node == this->root)
  {
    this->root = partitionA->root;
  }

  return partitionB;

}

void BST::reverse(BSTNode *node)
{
  BSTNode left, right;
  node = !node ? root : node;

  if (node )
  {
    left = node->left;
    right = node->right;

    node->left = right;
    node->right = left;

    if (node->left)
    {
      reverse(node->left);
    }

    if (node->right)
    {
      reverse(node->right);
    }
  }
}



int main()
{

  BST tree;
tree.add(32);
tree.add(17);
tree.add(28);
tree.add(23);
tree.add(29);
tree.add(49);
tree.add(2);

tree.display();

tree.root->left->right->value = 1;
tree.bstRepair();

std::cout << '\n';

std::cout << tree.closestValue(31) << '\n';


}