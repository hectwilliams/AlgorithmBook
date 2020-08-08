#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "chapter12.h"

struct SList *allocate_slist(int value)
{
  struct SList *node = (struct SList*) malloc(sizeof(struct SList));
  node->next = NULL;
  node->value = value;
  return node;
}

void SList_add(int value, struct SList **node)
{
  struct SList *runner = NULL;

  if (*node == NULL)
  {
    *node = allocate_slist(value);
  }
  else
  {
    runner = *node;
    while(runner->next)
    {
      runner = runner->next;
    }
    runner->next = allocate_slist(value);
  }
}


void SList_display(struct SList **node)
{
  struct SList *runner;

  if (*node )
  {
    runner = *node;
    while (runner)
    {
      printf(" %d\n", runner->value);
      runner = runner->next;
    }
  }
}


/* LIST COMPONENTS ABOVE */
void array_display(int *array, int length)
{
  /*print array data*/
  for (int i = 0; i < length; i++)
  {
    printf("[%d]", array[i]);
  }
  printf("\n");
}

void swap(int *array, int i, int k)
{
  int tmp = array[k];
  array[k] = array[i];
  array[i] = tmp;
}

void bubble_sort_array(int *array, int size)
{
  int tmp;

  for (int i = 0; i < size - 1; i++)
  {
    for (int k = 0 ; k < size - i - 1; k++)
    {
      if (array[k]  > array[k + 1])
      {
        swap(array, i, k);
      }
    }
  }
}

void bubble_sort_array_test()
{
  int array[] = {4,3,2,1,0};
  int length = sizeof(array)/sizeof(array[0]) ;
  bubble_sort_array(array, length);
  array_display(array, length);
}

void selectionSort_array(int *array, int size)
{
  int sel_index;
  for (int i = 0; i < size - 1 ; i ++)
  {
    sel_index = i;
    for (int k = sel_index + 1; k < size; k++)
    {
      if (array[k] < array[sel_index])
      {
        sel_index = k;
      }
    }

    if (sel_index != i)
    {
      swap(array, i, sel_index);
    }
  }
}

void selectionSort_array_test()
{
  int array[] = {4,3,2,1,0};
  int length = sizeof(array)/sizeof(array[0]) ;
  selectionSort_array(array, length);
  array_display(array, length);
}

void bubbleSort_list(struct SList ** head)
{
  struct SList *curr = *head;
  struct SList *k = NULL, *kprev = NULL;
  struct SList *buffer = NULL;
  struct SList *end = NULL;

  while (curr != end)
  {
    k =  *head;
    kprev = NULL;

    while(k->next != end)
    {
      if (k->value > k->next->value)
      {

        buffer = k->next;
        k->next = k->next->next;

        if (curr == k) // curr pointer updated
        {
          curr = buffer;
        }

        if (k == *head)
        {
          buffer->next = *head;
          *head = buffer;
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
        k = k->next;
      }
    }

    end = k; /* updated tail is ordered */

    curr = curr->next;

  }
}

void bubbleSort_list_test()
{
  struct SList *list = NULL;
  SList_add(5, &list);
  SList_add(4, &list);
  SList_add(3, &list);
  SList_add(2, &list);
  SList_add(1, &list);
  bubbleSort_list(&list);
  SList_display(&list);
}

int main()
{
  bubbleSort_list_test();
}