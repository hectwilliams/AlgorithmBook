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


void insertionSort_array (int * array, unsigned size)
{
  for (int i = 1; i < size; i++)
  {
    for (int k = i - 1; k >=0; k--)
    {
      if (array[k]  > array[k + 1])
      {
        swap(array, k, k + 1);
      }
    }
   }
}


void insertionSort_list(struct SList **head)
{
  struct SList *curr, *curr_prev, *k, *k_prev, *buffer;

  curr = *head;

  while (curr->next)  // O(N)
  {
    if ((*head)->value > curr->value && curr_prev)       // 0(1)
    {
      buffer = curr;
      curr_prev->next = curr_prev->next->next;

      buffer->next = (*head);
      (*head) = buffer;

      curr = curr_prev;
    }
    curr_prev = curr;
    curr = curr->next;
  }
}

struct array_obj  combine_array(int * a, int a_size, int *b, int b_size)
{
  struct array_obj obj;
  int ptr_a = 0, ptr_b = 0, index = 0;
  int * collection = (int *) malloc(sizeof(int)  * (b_size + a_size));

  while (1)
  {
    if (ptr_a  < a_size && ptr_b < b_size)
    {
      if (a[ptr_a] == b[ptr_b])
      {
        collection[index++] = a[ptr_a++];
        collection[index++] = b[ptr_b++];
      }
      else if (a[ptr_a] < b[ptr_b])
      {
        collection[index++] = a[ptr_a++];
      }
      else
      {
        collection[index++] = b[ptr_b++];
      }
    }
    else if (ptr_a < a_size)
    {
      collection[index++] = a[ptr_a++];
    }
    else if (ptr_b < b_size)
    {
      collection[index++] = b[ptr_b++];
    }
    else
    {
      break;
    }
  }

  obj.array = collection;
  obj.size = index;

  return obj;
}

struct SList *combine_list  (struct SList *a, struct SList *b)
{
  struct SList *node;
  struct SList *head = (struct SList *) malloc( sizeof(struct SList) );

  head->next = NULL;
  node = head;

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

  free(head);

  return node;

 }

void test()
{
  int arr [] = {5, 3, 1, 6};
  int len  = sizeof(arr) / sizeof(arr[0]);
  struct array_obj data = combine_array( arr, len, arr, len );
  array_display(data.array, data.size);
}


void test2()
{
  struct SList *list = NULL;
  SList_add (5, &list);
  SList_add(6, &list);
  SList_add(7, &list);
  SList_add(8, &list);

  struct SList *list_two = NULL;
  SList_add (2, &list_two);
  SList_add(5, &list_two);
  SList_add(8, &list_two);
  SList_add(9, &list_two);

  struct SList *data = combine_list(list, list_two);

  SList_display(&data);
}


int main()
{
  test2();
}