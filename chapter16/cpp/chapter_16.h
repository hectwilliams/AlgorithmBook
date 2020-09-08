#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <array>
#include <vector>
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
    int size (const std::string &key, TrieMapNode *node = NULL);
    std::pair<std::string, std::string> first(const TrieMapNode *node = NULL);
    std::pair<std::string, std::string> last(const TrieMapNode *node = NULL);

};