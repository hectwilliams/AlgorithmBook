#include <utility>
#include <vector>
#include <iostream>
#include <string>

std::ostream &operator << (std::ostream &out, const std::vector<int> &vect );
std::ostream &operator << (std::ostream &out, const std::vector<std::pair<std::string, int> > &vect );

class HashMap
{
  public:
    int capacity;
    int size;
    std::vector<std::vector <std::pair<std::string , int> > > table;
    HashMap(int cap = 10)
    {
      capacity = cap;
      size = 0;
      for (int i = 0; i < capacity; i++)
      {
        table.push_back(std::vector <std::pair<std::string , int> >());
      }
    }
    void display();
    int hashCode (std::string str);
    virtual void add(std::string key, int value);
    bool empty();
    std::vector<int> find(std::string key);
    int remove(std::string key);
    double load_factor();
    void grow();
    void set_size(const int &newCap);
    void addMap( HashMap &obj);
    void select_keys(std::vector<std::pair<std::string, int> > keys);
};

class HashMultiMap : public HashMap // unordered
{
  public:
  virtual void add(std::string key, int value);
};

