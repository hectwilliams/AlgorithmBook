
#include <string>
#include <stdio.h>
#include <algorithm>

#include "chapter_12.h"

SList &SList::add(int value)
{
  SLNode *runner;

  if (!head)
  {
    head = new SLNode(value);
  }
  else
  {
    runner = head;
    while (runner->next)
    {
      runner = runner->next;
    }
    runner->next = new SLNode(value);
  }

  return *this;
}

void SList::display()
{
  SLNode *runner = head;
  while(runner)
  {
    std::cout << runner->value << '\n';
    runner = runner->next;
  }
}

void bubbleSort(std::vector<int> &collection)
{
  for (int i = 0; i < collection.size(); i++)
  {
    for (int k = 0; k < collection.size() - i - 1; k++)
    {
      if (collection[k] > collection[k + 1])
      {
        std::swap(collection[k] , collection[k+ 1]);
      }
    }
  }
}

void bubbleSortTest()
{
  std::vector<int> collection;

  /*load array  decreasing order */
  for (int i = 5; i--;)
  {
    collection.push_back(i);
  }

  /*sort*/
  bubbleSort(collection);

  /*print sorted array*/
  for (int ele: collection )
  {
    std::cout << ele << '\n';
  }
  std::cout << '\n';
}

int main()
{
  bubbleSortTest();
}
