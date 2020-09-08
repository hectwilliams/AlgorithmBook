#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <array>
#include <vector>

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
  void reverse(BSTNode *node = NULL);
  int kthBiggest(int k, BSTNode *node = NULL , int *currCount = NULL );
  std::vector<int> value_for_layer(int layer, BSTNode *node = NULL);
  std::vector<std::vector<int> > layersArrays( BSTNode *node= NULL);

};


  class TrieNode
  {
    public:
      std::string str;
      std::vector<TrieNode *> children;
      int count;

    TrieNode(const std::string &str_data)
    {
      for (auto c :str_data)
      {
        str += tolower(c);
      }
      count = 0;
    }
  };

  class Trie
  {
    private :
    // void removeAllChildren(TrieNode *node = NULL);

    public:
    TrieNode *root;
    Trie ()
    {
      this->root = new TrieNode("");
    }
    std::string first(TrieNode *node = NULL);
    std::string last(TrieNode *node = NULL);
    std::string next (std::string str, TrieNode *node = NULL);

    protected:
    virtual bool add(const std::string &str);
    virtual bool contains(const std::string &str);
    virtual bool remove(std::string value, TrieNode *node = NULL);
    virtual int size (TrieNode *node = NULL );
  };

  class TrieMulti : public Trie
  {
    public:
      virtual bool add(const std::string &str);
      virtual bool remove(const std::string &str, TrieNode *node = NULL);
      virtual int size (TrieNode *node = NULL);
      virtual int contains (std::string string, TrieNode *node = NULL);
  };

class TrieMapNode
{
  public:
    std::string key;
    std::string value;
    std::vector<TrieMapNode *> children;

    TrieMapNode(std::string key, std::string value)
    {
      this->key = key;
      this->value = value;
    }
};

class TrieMap
{

  private:
    static void removeAllchildren (TrieMapNode *node);
  public:
    TrieMapNode *root;

    TrieMap()
    {
      this->root = new TrieMapNode("", "");
    }
    std::string add(std::string key, std::string value);
    bool remove(const std::string &key, TrieMapNode *node = NULL);
    std::string contains(const std::string &key, TrieMapNode *node = NULL);
};