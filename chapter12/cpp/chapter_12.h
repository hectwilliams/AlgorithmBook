#include <iostream>
#include <vector>
#include <array>

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

void insertionSort(std::vector<int> &collection);
std::vector<int>  combine(std::vector<int> a, std::vector<int> b);

SLNode *combine (SLNode *a, SLNode *b);
SLNode *mergeSort_list(SLNode *llist);
SLNode *partition(SLNode *llist);
int partition(std::vector<int> &arr);
int partition_second(std::vector<int> &arr);
int partition_third(std::vector<int> &arr, int start = 0, int end = 0);

std::array<int, 2> partition3(std::vector<int> &arr, int start  = 0, int end =  -1 );
void mergeSort(std::vector<int> &collection);