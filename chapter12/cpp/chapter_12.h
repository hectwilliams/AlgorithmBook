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