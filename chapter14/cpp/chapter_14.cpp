#include "chapter_14.h"


int HashMap::hashCode(std::string str)
{
  int charCode = 0;
  int hashCode = 0;

  if (str.size() == 0)
  {
    return charCode;
  }

  for (int i = 0; i < str.size() ; i++)
  {
    charCode = (unsigned) str[i];
    hashCode += charCode;
  }
  return hashCode;
}

void HashMap::add(std::string key, int value)
{
  int index = hashCode(key) % capacity;
  std::vector<std::pair<std::string, int> > &collection = table[index];
  std::pair<std::string, int> pair = std::make_pair(key, value);;

  if (collection.empty())
  {
    collection.push_back(pair);
  }
  else
  {
    // search for key/value
    for (int i = 0; i < collection.size(); i++)
    {
      if (collection[i].first == key  && collection[i].second == value)
      {
        return;
      }
    }
    // add key/value
    collection.push_back(pair);
  }
  size++;
}

bool HashMap::empty()
{
  return size == 0;
}



int main()
{
  HashMap hasher;
  hasher.add("hector", 21);
  hasher.add("hector", 21);
}

