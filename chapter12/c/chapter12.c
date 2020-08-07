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

void bubble_sort_array(int *array, int size)
{
  int tmp;

  for (int i = 0; i < size - 1; i++)
  {
    for (int k = 0 ; k < size - i - 1; k++)
    {
      if (array[k]  > array[k + 1])
      {
        tmp = array[k];
        array[k] = array[k + 1];
        array[k + 1] = tmp;
      }
    }
  }
}

void bubble_sort_array_test()
{
  int array[] = {4,3,2,1,0};
  int length = sizeof(array)/sizeof(array[0]) ;
  bubble_sort_array(array, length);

  /*print array data*/
  for (int i = 0; i < length; i++)
  {
    printf("[%d]", array[i]);
  }
  printf("\n");
}

int main()
{
  bubble_sort_array_test();
}