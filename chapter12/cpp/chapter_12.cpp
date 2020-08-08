
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


void selectionSort(std::vector<int> &collection)
{
  int size = collection.size();
  int sel_index = 0;

  for (int i = 0; i < size - 1; i++)
  {
    sel_index = i;
    for (int k = sel_index; k < size; k++ )
    {
      if (collection[k] < collection[sel_index])
      {
        sel_index = k;
      }
    }

    if (sel_index != i)
    {
      std::swap(collection[sel_index], collection[i]);
    }
  }
}

void bubble_sort_list(SList &list )
{
  SLNode *curr = list.head;
  SLNode *k = NULL, *kprev = NULL;
  SLNode *buffer = NULL;
  SLNode *end = NULL;

  while (curr != end)
  {
    k = list.head;
    kprev = NULL;
    while (k->next)
    {
      if (k->value > k->next->value)
      {
        buffer = k->next;
        k->next = k->next->next;

        if (curr == k)
        {
          curr = buffer;
        }

        if (k == list.head)
        {
          buffer->next = list.head;
          list.head = buffer;
        }
        else if (kprev)
        {
          kprev->next = buffer;
          buffer->next = k;
        }
        kprev = buffer;
        k = kprev->next;
      }
      else
      {
        kprev = k;
        k = kprev->next;
      }
    }
  end = k;
  curr = curr->next;

  }
}


void test()
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


void test2 ()
{
  SList list;
  list.add(5);
  list.add(4);
  list.add(3);
  list.add(2);
  list.add(1);
  bubble_sort_list(list);
  list.display();
}

int main()
{
  test2();
}
