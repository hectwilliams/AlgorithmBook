
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

void selection_sort_list(SList &list)
{
  SLNode *curr, *k, *kprev, *curr_prev, *selection, *selection_prev;

  curr = list.head;
  while (curr)
  {
    k = curr;
    selection = curr;

    while (k->next)
    {
      if (k->next->value < selection->value)
      {
        selection = k->next;
        selection_prev = k;
      }
      k = k->next;
    }

    if (curr != selection)
    {
      selection_prev->next = selection_prev->next->next;

      /* front insert*/
      if (curr == list.head)
      {
        list.head = selection;
      }
      else
      {
        curr_prev->next = selection;
      }

      /*back insert*/
      curr->next = selection_prev->next;

      /*handle adjacent nodes*/
      if (curr != selection_prev)
      {
        selection_prev->next = curr;
      }
      else
      {
        selection->next = curr;
      }

      curr = selection;
    }

    curr_prev = curr;
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



NameList & NameList::add (std::string first_name, std::string last_name)
{
  NameNode *runner;

  if (head == NULL)
  {
    head = new NameNode(first_name, last_name);
  }
  else
  {
    runner = head;
    while(runner->next)
    {
      runner = runner->next;
    }
    runner->next = new NameNode(first_name, last_name);
  }

  return *this;

}


void NameList::display()
{
  NameNode *runner = head;
  while (runner)
  {
    std::cout << runner->first_name << ' ' << runner->last_name << '\n';
    runner = runner->next;
  }
}


void NameList::multiSort(unsigned prio)
{
  NameNode *curr, *curr_prev, *k, *k_prev, *selection, *selection_prev;

  if (prio >= 2)
  {
    return;
  }

  curr = head;
  curr_prev = NULL;

  while (curr)
  {

    k = curr;
    selection = curr;

    while(k->next )
    {
      if ((prio == 0 && k->next->last_name.compare(selection->last_name) < 0 )  || (prio == 1 && k->next->last_name.compare(selection->last_name) < 0 && k->next->first_name.compare(selection->first_name) == 0) )
      {
        selection_prev = k;
        selection = k->next;
      }
      k  = k->next;
    }

    if (curr != selection)
    {
      selection_prev->next = selection_prev->next->next;
      selection->next = curr->next;

      if (curr == head )
      {
        head = selection;
      }
      else
      {
        curr_prev->next = selection;
      }

      curr->next = selection_prev->next;

      if (curr != selection_prev)
      {
        selection_prev->next = curr;
      }
      else
      {
        selection->next = curr;
      }
      curr = selection ;
    }
    curr_prev = curr;
    curr = curr->next;
  }

  return multiSort(prio + 1);

}



void test2 ()
{
  NameList list;
  list.add("Aaron", "Carnevale");
  list.add("Lee", "Abbey");
  list.add ("Giorgio", "Carnevale");
  list.display();
  std::cout << "   ****\n " << '\n';
  list.multiSort();
  list.display();

}

int main()
{
  test2();
}
