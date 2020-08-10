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



void selectionSort_list(struct SList **head)
{
  struct SList *curr, *k, *kprev;
  struct SList *curr_prev = NULL;
  struct SList *selection_prev, *selection;

  curr = *head;

  while (curr)
  {
    k = curr;
    selection = curr;

    while (k->next)
    {
      if (k->next->value < selection->value )
      {
        selection = k->next;
        selection_prev = k;
      }
      k = k->next;
    }

    if (curr != selection)
    {
      selection_prev->next = selection_prev->next->next;
      selection->next = curr->next;


       if (curr == *head)
      {
        *head = selection;
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

      curr = selection; // update curr pointer
    }

    curr_prev = curr;
    curr = curr->next;
  }
}


void selectionSort_list_test()
{
  struct SList *list = NULL;
  SList_add(5, &list);
  SList_add(4, &list);
  SList_add(3, &list);
  SList_add(2, &list);
  SList_add(1, &list);
  selectionSort_list(&list);
  SList_display(&list);
}



/* names */
void multikey_sort (struct NameList **head)
{
  struct NameList *curr, *curr_prev = NULL, *k, *kprev, *selection_prev, *selection;

  for (int i = 0; i < 2; i++)
  {
    curr = *head;
    curr_prev = NULL;

    while(curr)
    {
      k = curr;
      selection = curr;

      while (k->next)
      {

        if (i == 1)
        {
          if ( (strcmp(k->next->firstName, selection->firstName) < 0) &&  (strcmp(k->next->lastName, selection->lastName) == 0)  )
          {
            selection_prev = k;
            selection = k->next;
          }
        }
        else if (i == 0)
        {
          if ( strcmp(k->next->lastName, selection->lastName) < 0 )
          {
            selection_prev = k;
            selection = k->next;
          }
        }


        k = k->next;
      }



      if (curr != selection)
      {

        selection_prev->next = selection_prev->next->next;
        selection->next = curr->next;

        if (curr == *head)
        {
          *head = selection;
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


        curr = selection; // update curr pointer
      }

      curr_prev = curr;
      curr = curr->next;
    }

  }
}


struct NameList *allocate_namelist(const char *firstName, const char *lastName)
{
  struct NameList *node = (struct NameList*) malloc(sizeof(struct NameList));
  node->firstName = firstName;
  node->lastName = lastName;
  node->next = NULL;
  return node;
}


void NameList_add(const char *firstName, const char *lastName, struct NameList **node)
{
  struct NameList *runner = NULL;

  if (*node == NULL)
  {
    *node = allocate_namelist(firstName, lastName);
  }
  else
  {
    runner = *node;
    while(runner->next)
    {
      runner = runner->next;
    }
    runner->next = allocate_namelist(firstName, lastName);
  }
}


void NameList_display(struct NameList **node)
{
  struct NameList *runner;

  if (*node )
  {
    runner = *node;
    while (runner)
    {
      printf(" [ %s  %s  ] \n", runner->firstName, runner->lastName);
      runner = runner->next;
    }
  }
}


void multikey_sort_test()
{
  struct NameList *list = NULL;

  NameList_add("Aaron", "Carnevale", &list);
  NameList_add("Lee", "Abbey", &list);
  NameList_add("Giorgio", "Carnevale", &list);
  multikey_sort(&list);
  NameList_display(&list);
}



int main()
{
  multikey_sort_test();
}