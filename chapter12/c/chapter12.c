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
    printf("[");;
    while (runner)
    {
      printf(" %d ,", runner->value);
      runner = runner->next;
    }
    printf("]\n");

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

/*
  SPACE_TIME  N*LOG(N)
  RUN TIME  N*LOG(N)
*/
struct SList *mergeSort_list(struct SList *llist)
{
  struct SList  *left, *right_prev, *right;
  unsigned counter = 0;

  left = right = right_prev= llist;

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
    /* split nodes*/
    right = left->next;
    left->next = NULL;
    return combine_list(left, right);
  }
  else
  {
    right_prev->next = NULL;
    left = mergeSort_list(left);
    right = mergeSort_list(right);
  }

  return combine_list(left, right);
}

struct SList *partition_list(struct SList *llist)
{
  struct SList *curr, *pivot, *pivot_prev, *head, *buffer;
  head = curr = pivot = llist;
  buffer = pivot_prev= NULL;

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

int partition_array(int *collection, int size)
{
  int ptr = 0;
  int tmp = 0;
  for (int i = 0; i < size; i++)
  {
    if (collection[i] < collection[ptr])
    {
      /* update ptr */
      tmp = collection[i];
      collection[i] = collection[ptr];
      collection[ptr] = tmp;
      ptr++;
    }
  }
  return ptr;
}


int partition_array_second(int *collection, int size)
{
  int array[3];
  int pivot = 0;
  int k = 0;

  if (size <= 0)
  {
    return -1;
  }

  array[0] = collection[0];
  array[1] = collection[size / 2];
  array[2] = collection[size - 1];

  pivot = collection[1];

  for (int i = 0; i < size; i++)
  {
    if (collection[i] < pivot )
    {
      swap(collection, i, k);
      k++;
    }
  }
  return k;
}

int partition_array_third(int *collection, int size)
{
  int start = 0;
  int end  = size;
  return partition_array_third_helper(collection, start, end);
}

int  partition_array_third_helper(*collection,int start, int end)
{
  int k = -1;
  for (int i = start; i < end; i++)
  {
    if (k == -1  )
    {
      k = start;
    }
    if (collection[i] < collection[k])
    {
      swap(collection, i, k);
      k++;
    }
  }
  return k;
}

void quickSort(int *collection, int size)
{
  return quickSort_helper(collection, 0, size);
}

void quickSort_helper(int *collection, int start, int end)
{
  int pivot ;

  if (end - start > 0)
  {
    pivot = partition_array_third_helper(collection, start, end);
    if (pivot >= 0)
    {
      quickSort_helper(collection, 0, pivot); // left
      quickSort_helper(collection, pivot + 1, end); // right
    }
  }
}

int * partition_array_3 (int *collection, int size)
{
  static int result[2];
  int k = 0, k_end = size - 1;
  int pivot = collection[0];
  int count = 0;

  for (int i = 0; i < size; i++)
  {
    count += +(collection[i] == pivot);
    if ( collection[i] < pivot )
    {
      swap(collection, i, k);
      if (k < size)
      {
        k++;
      }
    }
  }

  result[0] = k;
  result[1] = k + count - 1;

  while (k + 1 < size)
  {
    if ( collection[k + 1] > collection[k_end] && k_end > k + 1)
    {
      swap(collection, k + 1, k_end);
      k_end--;
    }
    k++;
  }


  return result;
}

void  mergeSort_array(int *collection, int size)
{
  int mid = size / 2;
  int left_size;
  int right_size;
  int * clone_left;
  int * clone_right;
  struct array_obj combined = {.size = 0, .array = NULL};

  if (size <= 1)
  {
    return ;
  }

  if (size % 2 == 1)
  {
    left_size = mid + 1;
    right_size = mid;
  }
  else
  {
    left_size = right_size = mid;
  }

  clone_left = (int *) malloc(sizeof(int) * left_size);
  clone_right = (int *) malloc(sizeof(int) * right_size);

  memcpy(clone_left, collection, sizeof(int) * left_size);
  memcpy(clone_right, collection + mid  + (size % 2 == 1 ? 1 : 0) , sizeof(int) * right_size);

  mergeSort_array(clone_left, left_size);
  mergeSort_array(clone_right, right_size);

  if ( size > 1)
  {
    combined = combine_array(clone_left, left_size, clone_right, right_size);
    memcpy(collection, combined.array, sizeof(int) * combined.size);
  }
}

void test()
{
  int arr [] = { 5,1,8,4,5,9,2,5,3,5};
  int len  = sizeof(arr) / sizeof(arr[0]);
  mergeSort_array(arr, len);
  array_display(arr, len);
}

void test2()
{
  struct SList *list = NULL, *test;
  SList_add (5, &list);
  SList_add(1, &list);
  SList_add(8, &list);
  SList_add(4, &list);
  SList_add(9, &list);
  SList_add(2, &list);
  SList_add(5, &list);
  SList_add(3, &list);
  test = partition_list(list);
  SList_display(&test);
}

int main()
{
  test();
}