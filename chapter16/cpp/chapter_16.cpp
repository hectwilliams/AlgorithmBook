#include "chapter_16.h"

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

  std::string TrieMap::add(std::string key, std::string value)
  {
    TrieMapNode *curr, *node = this->root;
    std::string result;
    int pos = 0;

    if (!node)
    {
      return "";
    }

    while ( pos < key.length())
    {
      curr = node;
      pos++;

      for (int i = 0; i < node->children.size(); i++)
      {
        if ( key.find(value.substr(0, pos)))
        {
          node = node->children[i];
          break;
        }
      }

      if (key == node->key)
      {
        result = node->value;
        node->value = value;
        return result;
      }

      if (curr == node)
      {
        node->children.push_back(new TrieMapNode(key.substr(0, pos), ""));
        node = node->children.back();
        if (node->key == key)
        {
          node->value = value;
        }
      }
    }
    return "";
  }

  void TrieMap::removeAllchildren (TrieMapNode *node)
  {
    if (!node)
    {
      return;
    }

    for (int i = 0; i < node->children.size() ; i++)
    {
      removeAllchildren(node->children[i]);
      delete(node->children[i] );
    }

    node->children.clear();
  }

  bool TrieMap::remove(const std::string &key, TrieMapNode *node)
  {
    bool found = false;
    TrieMapNode *child;

    node = !node ? root : node;

    if (key == node->key)
    {
      return true;
    }

    for (int i = 0; i < node->children.size() && !found; i++)
    {
      if ( key.find( node->children[i]->key ) == 0)
      {
        found |= remove(key, node->children[i]);

        if (found)
        {
          if (node->children[i]->key == key)
          {
            removeAllchildren( node->children[i] );
            delete(node->children[i]);
            node->children.erase(node->children.begin() + i);
          }
          else if (node->children.size() == 1)
          {
            if (node->children[0]->children.size() == 0 && node->children[0]->value.length() == 0)
            {
              delete( node->children[0] ) ;
              node->children.clear();
            }
          }
        }
      }
    }
    return found;
  }

  std::string TrieMap::contains(const std::string &key, TrieMapNode *node)
  {
    node = !node ? root : node;

    if (!node)
    {
      return "";
    }
    if (node->key == key)
    {
      return node->value;
    }
    for (int i = 0; i < node->children.size(); i++)
    {
      if (key.find(node->children[i]->key ) == 0 )
      {
        return contains(key, node->children[i]);
      }
    }
    return  "";
  }

  int TrieMap::size (const std::string &key, TrieMapNode *node)
  {
    int count = 0;
    node = !node ? root : node;

    for (int i  = 0; i < node->children.size(); i++)
    {
      count += 1 + size(key, node->children[i]);
    }
  }

  std::pair<std::string, std::string> TrieMap::first(const TrieMapNode *node )
  {
    const TrieMapNode *curr;
    char currChar, minCHar = '\0';
    int pos = -1;
    std::pair<std::string, std::string> result;

    node = !node ? root : node;

    while(node != curr)
    {
      curr = node;
      pos++;
      for (int i = 0; i < curr->children.size(); i++)
      {
        currChar = curr->children[i]->key[pos];
        if (minCHar == 0 || currChar <= minCHar)
        {
          node = curr->children[i];
          minCHar = currChar;
        }
      }
    }

    if (node)
    {
      return std::make_pair(node->key, node->value);
    }

    return std::make_pair("","");
  }

  std::pair<std::string, std::string> TrieMap::last(const TrieMapNode *node )
  {
    const TrieMapNode *curr;
    std::string currString, maxString = "";
    std::pair<std::string, std::string> result;
    int pos = 0;
    node = !node ? root : node;

    while (node != curr)
    {
      curr = node;
      pos++;
      for (int i = 0; i < curr->children.size(); i++)
      {
        currString = curr->children[i]->key;
        if (maxString == "" || currString.compare(maxString) >=0 )
        {
          maxString = currString;
          node = curr->children[i];
        }
      }
    }

    if (node)
    {
      result.first = node->key;
      result.second = node->value;
    }
    return result;

  }

  std::pair<std::string, std::string> TrieMap::next(std::string key, const TrieMapNode *node)
  {
    std::pair<std::string, std::string> obj;
    node = !node ? root : node;

    if (node)
    {
      if (key.compare(node->key) == 0)
      {
        for (auto child: node->children)
        {
          if (obj.first.length() == 0 || child->key.compare(obj.first) <= 0)
          {
            obj.first = child->key;
            obj.second = child->value;
          }
        }
        return obj;
      }
      else
      {
        for (int i = 0; i<  node->children.size(); i++)
        {
          if (key.find(node->children[i]->key ) == 0)
          {
            return next(key, node->children[i]);
          }
        }
      }
    }

    return obj;

  }



int main()

{
  TrieMap trie;
  std::cout << trie.add("name", "hello") << '\n';
  std::cout << trie.add("name", "hello") << '\n';
  std::cout <<trie.add("nam", "down") << '\n';


  auto obj  = trie.next("nam");
  std::cout <<  obj.first << " " << obj.second << '\n';
  // TrieMulti.add("hellor");
  // TrieMulti.add("hellw");
}