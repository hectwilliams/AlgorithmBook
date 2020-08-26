#include "chapter_14.h"


std::ostream &operator << (std::ostream &out, const std::vector<int> &vect )
{
  std::cout << "[";
  for (auto ele: vect)
  {
    out << ele << ',';
  }
  std::cout << "]\n";
  return out;
}

std::ostream &operator << (std::ostream &out, const std::vector<std::pair<std::string, int> > &vect )
{
  std::pair<std::string, int> ele;
  std::cout << '[';
  for (int i = 0; i < vect.size(); i++)
  {
    ele = vect[i];
    out << "key:" << ele.first << ',' << "value:" << ele.second << '|';
  }
  std::cout << "]\n";
  return out;
}

void HashMap::display()
{
  for (int i = 0; i < table.size() ; i++)
  {
    std::cout << table[i];
  }
}


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

std::vector<int> HashMap::find(std::string key)
{
  int index = hashCode(key) % capacity;
  std::vector<std::pair<std::string, int> > &collection = table[index];
  std::vector<int> result;

  for (std::pair<std::string, int>  pairData: collection )
  {
    if (pairData.first == key)
    {
      result.push_back(pairData.second);
    }
  }
  return result;
}

int HashMap::remove(std::string key)
{
  int index = hashCode(key) % capacity;
  std::vector<std::pair<std::string, int> > &collection = table[index];
  int result = 0xDEADBEEF;
  int pos = 0;

  for (std::pair<std::string, int> &pairData: collection )
  {
    if (pairData.first == key)
    {
      result = pairData.second;
      break;
    }
    pos++;
  }

  if (pos < collection.size())
  {
    size--;
    collection.erase(collection.begin() + pos);
  }

  return result;
}

double HashMap::load_factor()
{
  return size / capacity;
}

void HashMap::grow ()
{
  int increase = capacity - capacity + int(capacity * 0.50);
  int bucket_index;
  int code;
  std::pair<std::string, int> pair;

  // update capacity
  capacity = capacity + increase;

  // increase array size
  for (; increase--; )
  {
    table.push_back(std::vector<std::pair<std::string, int> >());
  }

  // rehash
  for (int i = 0; i < capacity; i++)
  {
    bucket_index = 0;
    while (bucket_index < table[i].size())
    {
      pair = table[i][bucket_index];
      code = hashCode(pair.first);

      if (code % capacity != i )
      // delete and add
      {
        table[i].erase(table[i].begin() + bucket_index);
        add(pair.first, pair.second);
      }
      else
      {
        bucket_index++;
      }
    }
  }

}


int main()
{
  HashMap hasher;
  hasher.add("hector", 21);
  hasher.add("picnic", 21);

  hasher.display();
  hasher.grow();
  std::cout << '\n';
  hasher.display();

  auto x = hasher.find("hector");
}

