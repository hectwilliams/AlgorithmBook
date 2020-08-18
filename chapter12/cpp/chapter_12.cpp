
#include <string>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include "chapter_12.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

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

void insertionSort(std::vector<int> &collection)
{
  int size = collection.size();
  for (int i = 0; i < size; i++)
  {
    for (int k = i - 1; k >= 0; k--)
    {
      if (collection[k] > collection[k + 1])
      {
        std::swap(collection[k] , collection[k + 1]);
      }
    }
  }
}

void insertionSort_list (SList &list)
{
  SLNode *buffer = NULL, *curr =  list.head;
  while (curr->next)
  {
    if (curr->next->value < list.head->value)
    {
      buffer = curr->next;
      curr->next = curr->next->next;
      buffer->next = list.head;
      list.head = buffer;
    }
    else
    {
      curr = curr->next;
    }
  }
}

std::vector<int>  combine(std::vector<int> a, std::vector<int> b)
{
  int ptrA, ptrB;
  std::vector<int> collection;

  ptrA = ptrB = 0;

  while (ptrA < a.size() || ptrB < b.size())
  {
    if (ptrA < a.size() && ptrB < b.size())
    {
      if (a[ptrA] == b[ptrB])
      {
        collection.push_back(a[ptrA++]);
        collection.push_back(b[ptrB++]);
      }
      else if (a[ptrA] < b[ptrB])
      {
        collection.push_back(a[ptrA++]);
      }
      else
      {
        collection.push_back(b[ptrB++]);
      }
    }
    else if (ptrA < a.size())
    {
      collection.push_back(a[ptrA++]);
    }
    else if (ptrB < b.size())
    {
      collection.push_back(b[ptrB++]);
    }
  }
  return collection;
}

SLNode *combine (SLNode *a, SLNode *b)
{
  SLNode *head = new SLNode(-1);  // dummy node s
  SLNode *node = head;
  node->next = NULL;

  while (a && b)
  {
    if (a->value <= b->value)
    {
      node->next = a;
      a = a->next;
    }
    else
    {
      node->next = b;
      b = b->next;
    }
    node = node->next;
  }

  if (a != NULL)
  {
    node->next = a;
  }

  if (b != NULL)
  {
    node->next = b;
  }

  node = head->next;
  delete(head);
  return node;
}

SLNode *mergeSort(SLNode *llist)
{
  SLNode *left, *right, *right_prev;
  unsigned counter = 0;

  left = right = right_prev = llist;
  while (llist->next)
  {
    ++counter;
    if (counter % 2 == 0 && counter > 0)
    {
      right_prev = right;
      right = right->next;
    }
    llist = llist->next;
  }

  if (counter <= 1)
  {
    return llist;
  }
  else if (counter == 2)
  {
    right = left->next;
    left->next = NULL;
    return combine(left, right);
  }
  else
  {
    right_prev->next = NULL;
    left = mergeSort(left);
    right = mergeSort(right);
  }
  return combine(left, right);
}

 SLNode *partition(SLNode *llist)
{
  SLNode *curr, *pivot, *pivot_prev, *head, *buffer;
  head = curr = pivot = llist;
  buffer = pivot_prev = NULL;

  while (curr->next)
  {
    if (curr->next->value < pivot->value)
    {
      buffer = curr->next;
      curr->next = curr->next->next;
      if (head == curr)
      {
        head = buffer;
        buffer->next = pivot;
      }
      else
      {
        buffer->next = pivot;
        pivot_prev->next = buffer;
      }
      pivot_prev = buffer;
    }
    else
    {
      curr = curr->next;
    }
  }
  return head;
}

int partition(std::vector<int> &arr)
{
  int size = arr.size();
  int k = 0;
  int tmp;

  for (int i = 0; i < size; i++)
  {
    if (arr[i] < arr[k])
    {
      tmp = arr[i];
      arr[i] = arr[k];
      arr[k] = tmp;
      ++k;
    }
  }
  return k;
}

int partition_second(std::vector<int> &arr)
{
  int median_array[3];
  int pivot = 0;
  int k = 0;

  if (arr.empty())
  {
    return - 1;
  }

  median_array[0] = arr[0];
  median_array[1] = arr[arr.size() / 2];
  median_array[2] = arr[arr.size() - 1];

  pivot = median_array[1];

  for (int i = 0; i < arr.size(); i++)
  {
    if ( arr[i] < pivot )
    {
      std::swap(arr[i], arr[k]);
      k++;
    }
  }

  return k;
}

int partition_third(std::vector<int> &arr, int start, int end)
{
  int k = -1;
  end = arr.size();

  for (int i = start; i < end; i++)
  {
    if (k == -1)
    {
      k = start;
    }
    if (arr[i]  < arr[k])
    {
      std::swap(arr[i], arr[k]);
      k++;
    }
  }
  return k;
}

void quickSort(std::vector<int> &arr, int start = 0, int end = -1)
{
  int pivot;

  if (end == -1)
  {
    end = arr.size();
  }

  if (end - start > 0)
  {
    pivot = partition_third(arr, start, end);
    if (pivot >= 0)
    {
      quickSort(arr, 0, pivot);
      quickSort(arr, pivot + 1, end );
    }
  }
}

std::array<int, 2> partition3(std::vector<int> &arr, int start , int end  )
{

  std::array<int , 2> result = {-1 , -1};
  int  k = 0;
  int  pivot;
  int size;
  int a,b,c;
  int count = 0;

  end = (end  <= -1) ? arr.size() : end;

  size = end - start;

  a = arr[start];
  b =  arr[  (start + size) / 2];
  c = arr[ start + size - 1];

  if (size  <= 0)
  {
    return result;
  }

  if ( (a > b) != ( a > c) )
  {
    pivot = a;
  }
  else if ( (b > a ) !=  (b > c ))
  {
    pivot = b;
  }
  else
  {
    pivot = c;
  }

 for (int i = start; i < start + size; i++)
  {
    count += +(arr[i] == pivot );
    if ( arr[i] < pivot)
    {
      std::swap(arr[i] , arr[k]);
      if (k < start + size)
      {
        k++;
      }
    }
  }

  k = start + size - 1;
  for (int i = start + size - 1; i >= 0; i--)
  {
    if ( arr[i] > pivot )
    {
      std::swap(arr[i] , arr[k]);
      {
        k--;
      }
    }
  }

  result[0] = k - (count - 1 );
  result[1] = k ;

  return result;
}

void mergeSort(std::vector<int> &collection)
{
  int mid = collection.size() / 2;
  std::vector<int> left, right, collection_concat;

  if (collection.size() <= 1)
  {
    return;
  }

  left = std::vector<int>(collection.begin(), collection.begin() + mid + +(collection.size() % 2) );
  right = std::vector<int>(collection.begin() + mid + +(collection.size() % 2), collection.end());

  mergeSort(left);
  mergeSort(right);
  collection_concat = combine(left, right);

  for (int i = 0 ; i < collection_concat.size(); i++)
  {
    collection[i] = collection_concat[i];
  }
}

void quickSort3(std::vector<int> &arr, const int &start, const int &end)
{
  std::array<int, 2> pivot;
  int size =  start - end;

  if (end - start > 0)
  {
    pivot = partition3(arr, start, end);
    if (pivot[0] >= 0)
    {
      quickSort3(arr, 0, pivot[0]);
      quickSort3(arr, pivot[1] + 1, end);
    }
  }
}

void urbanDictionaryDailyAdd()
{
  /*
    Use quickSort instead of selectionSort. Selection Sort would work if the new valuess were greater than
    the largest value in list.

    Model:
    1) insert 1 of remaining new values to end of list  (remove from new data list)
    2) partition using the most recent added value
    3) Order should still be retained '
    4)continue step 1 until 'new data list' array is empty
  */
}


void pancakeSort_flip(std::vector<int>  &collection, int end_pos)
{
  for (int i = 0; i < (end_pos + 1) / 2; i++)
  {
    std::swap(collection[i] ,collection[end_pos - i]);
  }
}

void pancakeSort(std::vector<int>  &collection, int size)
{

  int k;
  int max;
  int max_index;

  size = collection.size();
  k = size - 1;

  while (k > 0)
  {
    max = collection[0];
    max_index = 0;

    for (int i = 0; i <= k ; i++)
    {
      if (collection[i] >= max)
      {
        max = collection[i];
        max_index = i;
      }
    }

    pancakeSort_flip(collection, max_index);  // move max to top
    pancakeSort_flip(collection, k);  // move max to bottom
    k--;  // reduce active elements
  }
}

void radixSort(std::vector<int> &collection, int maxValue)
{
  int k = 0;
  int curr;
  int factor = 1;
  int counter = 0;
  bool complete = false;

  while (!complete)
  {
    k = 0;
    for (int i = 0; i < maxValue + 1  && !complete ; i++)
    {
      counter = 0;
      for (int j = 0; j < collection.size() && !complete; j++)
      {
        curr = (collection[j] / factor ) % 10;
        counter += +(curr == 0);
        if (curr == i)
        {
          std::swap(collection[k++] , collection[j]);
        }
      }
      complete = counter == collection.size() && i == 0;
    }

    factor *= 10;
  }
}

void beltSort(std::vector<Belt> &collection)
{
  int curr_index;

  for (int i = 0; i < collection.size(); i++)
  {
    curr_index = i;
    for (int j = i; j < collection.size(); j++)
    {
      if (collection[j].belt < collection[curr_index].belt)
      {
        curr_index = j;
      }
    }
    if (curr_index != i)
    {
      std::swap(collection[curr_index], collection[i]);
    }
  }
}


void wiggleSort(std::vector<int> & collection)
{
  int mid = collection.size() / 2;
  int pos, neg;

  for (int i = 0; i < mid; i++)
  {
    pos = 2*i;
    neg = 2*i + 1;

    for (int j = i; j < mid; j++)
    {
       if (collection[j*2 ] < collection[pos])
      {
        pos = j*2;
      }
      if (collection[j*2+1] < collection[neg])
      {
        neg = 2*j + 1;
      }
    }

    if (pos_index != i*2)
    {
      std::swap(collection[i*2], collection[pos]);
    }

    if (neg != i*2 + 1)
    {
      std::swap(collection[i*2 + 1], collection[neg]);
    }

  }

}

void test2 ()
{
    srand (time(NULL));

  // std::vector<int> data;
  // for (int i = 0; i < 10; i++)
  // {
  //   data.push_back(rand() % 100);
  // }

  //  for (auto ele: data)
  // {
  //   std::cout << ele << '|';
  // }
  // std::cout << ""<< '\n';

  std::vector<int> testData;
  int arr[] = {4, -1, 2, -4, 10, -2};
  int len  = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < len ; i++)
  {
    testData.push_back(arr[i]);
  }

  wiggleSort(testData);

  for (auto ele: testData)
  {
    std::cout << ele << '|';
  }
  std::cout << ""<< '\n';

}

int main()
{
  test2();
}
