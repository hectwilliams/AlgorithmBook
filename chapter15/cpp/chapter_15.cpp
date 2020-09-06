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
  BSTNode *left, *right;
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


int BST::kthBiggest(int k, BSTNode *node  , int *currCount  )
{
  int result = 0;

  currCount = !currCount ? (int*) malloc(sizeof(int)) : currCount;
  node = !node ? root : node;

  if (node)
  {
    if (node->right)
    {
      result |= kthBiggest(k, node->right, currCount);
    }

    (*currCount)++;

    if (k == *currCount)
    {

      result |= node->value;
    }

    if (node->left)
    {
      result |= kthBiggest(k, node->left, currCount);
    }
  }
  return result;
}

std::vector<int> BST::value_for_layer(int layer, BSTNode *node )
{
  std::vector<std::pair<BSTNode *, int> > queue_model;
  std::vector<int> result;

  node = !node ? root : node;

  queue_model.push_back( std::make_pair(node, 0));

  while (!queue_model.empty())
  {
    if (queue_model.front().second == layer)
    {
      result.push_back(queue_model.front().first->value);
    }
    if (queue_model.front().first->left)
    {
      queue_model.push_back(  std::make_pair(queue_model.front().first->left, queue_model.front().second + 1));
    }
    if (queue_model.front().first->right)
    {
      queue_model.push_back(  std::make_pair(queue_model.front().first->right, queue_model.front().second + 1));
    }
    queue_model.erase(queue_model.begin());
  }
}

std::vector<std::vector<int> > BST::layersArrays (BSTNode *node)
{
  std::vector<std::vector<int> > result;
  std::vector<std::pair<BSTNode*, int> > queue_model;
  BSTNode *curr;
  int depth;

  node = !node ? root : node;
  queue_model.push_back(std::make_pair(node, 0));
  result.push_back(std::vector<int>());

  while (!queue_model.empty())
  {
    curr = queue_model.front().first;
    depth = queue_model.front().second;

    if (depth > result.size())
    {
      result.push_back(std::vector<int>());
    }
    result [(depth - 1 < 0)? 0 : depth - 1 ].push_back(curr->value);

    if (curr->left)
    {
      queue_model.push_back(std::make_pair(curr->left, depth + 1));
    }
    if (curr->right)
    {
      queue_model.push_back(std::make_pair(curr->right, depth + 1));
    }

    queue_model.erase(queue_model.begin());
  }
  return result;

}

  bool Trie::add(const std::string &str)
  {
    int pos = 0;
    TrieNode *node, *curr;
    bool inserted = false;

    node = root;

    while (node->str.length() != str.length())
    {
      curr = node;
      pos++;
      for (TrieNode* child: node->children)
      {
        if (child->str.compare(str.substr(0, pos)) == 0 )
        {
          inserted |= true;
          node = child;
        }
      }

      if (curr == node)
      {
        node->children.push_back( new TrieNode(str.substr(0, pos))  );
        node = node->children.back();
      }
    }
    return inserted == 0;
  }

  bool Trie::contains(const std::string &str)
  {
    TrieNode *curr, *node = this->root;
    int pos = 0;


    while (curr != node )
    {
      curr = node;
      for (TrieNode* child: node->children)
      {
        if (child->str.compare(str.substr(0, pos + 1)) == 0)
        {
          std::cout << child->str << '\n';
          pos++;
          node = child;
        }
      }
    }
    return pos == str.length();
  }

  std::string Trie::first(TrieNode *node)
  {
    TrieNode *curr;
    char minChar= '\0', currChar= '\0';
    int pos = 0;

    node = !node ? root : node;

    while (node != curr)
    {
      curr = node;
      for (TrieNode *element: node->children)
      {
        currChar = element->str[pos];
        if (minChar == '\0' || currChar <= minChar)
        {
          node = element;
          minChar = currChar;
        }
      }
      pos++;
    }
    return node->str;
  }

  std::string Trie::last(TrieNode *node )
  {
    TrieNode *curr;
    std::string maxString = "", currString = "";
    int pos = 0;

    node = !node ? root : node;

    while (node != curr)
    {
      curr = node;
      pos++;
      for (TrieNode *element: node->children)
      {
        currString = element->str;
        if (maxString == "" || currString.compare(maxString) > 0)
        {
          node = element;
          maxString = node->str;
        }
      }
    }
    return node->str;
  }

  bool Trie::remove(std::string word, TrieNode *node)
  {
    int found = 0;

    node = !node ? root : node;

    if (!node)
    {
      return 0;
    }

    if (word == node->str)
    {
      return 1;
    }

    for (int i = 0; i < node->children.size(); i++)
    {
      if ( word.find(node->children[i]->str) == 0 )
      {
        found = remove(word,node->children[i] );
        if (found)
        {
          if (node->children[i]->str == word )
          {
            node->children.erase(node->children.begin() + i);
          }
          else if (node->children.size() == 1)
          {
            if (node->children.front()->children.size() == 0)
            {
              node->children.clear();
            }
          }
        }
      }
    }

    return found;
  }

  int Trie::size (TrieNode *node)
  {
    int count = 0;

    node = !node ? root : node;

    if (node->children.size() == 0)
    {
      return  0;
    }

    for (int i = 0; i < node->children.size(); i++)
    {
      count += +(node->str.length() > 0) + size(node->children[i]);
    }
    return count;
  }

  std::string Trie::next (std::string str, TrieNode *node)
  {
    std::string result;

    node = !node ? root : node;

    if (node)
    {
      for (int i = 0; i < node->children.size(); i++)
      {
        if (str.find(node->children[i]->str) == 0)
        {
          return next(str, node->children[i]);
        }
      }

      for (int i = 0; i < node->children.size(); i++)
      {
        if (result.length() == 0 || node->children[i]->str.compare(result) <= 0)
        {
          result = node->children[i]->str;
        }
      }

    }
    return result;
  }

  bool TrieMulti::add(const std::string &str)
  {
    TrieNode *curr = NULL, *node = NULL;
    int pos = 0;

    if (this->root == NULL)
    {
      this->root = new TrieNode("");
    }

    node = this->root;

    if (!node)
    {
      return false;
    }

    while (str[pos])
    {
      curr = node;
      pos++;

      for (int i = 0; i < node->children.size(); i++)
      {
        if (   node->children[i]->str.find ( str.substr(0, pos)   ) == 0  )
        {
          node->count++;
          node = node->children[i];
          break;
        }
      }

      if (curr == node)
      {
        node->children.push_back(new TrieNode(str.substr(0, pos)));
        node= node->children.back();
        node->count = 1;
      }
    }

    return true;
  }

  bool TrieMulti::remove(const std::string &str ,TrieNode *node)
  {
    bool valueFound = 0;

    node = !node ? this->root :  node;

    if (!node)
    {
      return false;
    }

    if (str.compare (node->str) == 0 )
    {
      return true;
    }

    for (int i = 0; i < node->children.size(); i++)
    {
      if (str.find(node->children[i]->str ) == 0 )
      {

        valueFound = remove(str, node->children[i]);

        if (valueFound)
        {
          if (node->count > 1)
          {
            node->count--;
          }
          else if (node->count == 1)
          {
            if (str.find(node->children[i]->str) == 0)
            {
              // TODO free and delete all children subtree (create remveChildren method)...alo delete node at index i
              node->children.erase(node->children.begin() + i);
            }
            else if (node->children.size() == 1)
            {
              // TODO free and delete all children subtree (create remveChildren method)

              if (node->children[0]->children.empty())
              {
                node->children.clear();
              }
            }
          }
        }
      }
    }

    return valueFound;
  }

  int TrieMulti::size (TrieNode *node)
  {
    int count = 0;

    node = !node ? this->root : node;

    if (!node)
    {
      return 0;
    }
    else
    {
      count += node->count;
    }

    for (int i = 0; i < node->children.size(); i++)
    {
      count += size(node->children[i]);
    }

    return count;
  }


  int TrieMulti::contains (std::string string, TrieNode *node)
  {
    node = !node ? this->root : node;

    if (node)
    {
      if (node->str == string)
      {
        return node->count;
      }

      for (int i = 0; i < node->children.size(); i++)
      {
        if (string.find(node->children[i]->str) == 0)
        {
          return contains(string, node->children[i]);
        }
      }
    }
    return 0;
  }

int main()
{
  TrieMulti trie;

  trie.add("hello");

  trie.add("hello");


  // trie.remove("hello");

  std::cout << trie.contains("meow") << '\n';
  // TrieMulti.add("hellor");
  // TrieMulti.add("hellw");
}