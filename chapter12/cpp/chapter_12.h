#include <iostream>
#include <vector>

class SLNode
{
  public:
    int value;
    SLNode *next;

    SLNode(int val)
    {
      value = val;
      next = NULL;
    }
};

class SList
{
  public:
    SLNode *head = NULL;
    SList &add(int value);
    void display();
};

void bubbleSort(std::vector<int> &collection);
void selectionSort(std::vector<int> &collection);
void bubbleSort(SList &list);


class NameNode
{
  public:
    std::string first_name;
    std::string last_name;
    NameNode *next;

    NameNode(std::string first, std::string last)
    {
      first_name = first;
      last_name = last;
    }

};

class NameList
{
  public:
    NameNode *head;
    NameList()
    {
      head = NULL;
    }
    NameList &add(std::string first_name, std::string last_name);
    void display();
    void multiSort(unsigned prio = 0);
};