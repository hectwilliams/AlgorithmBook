#include <stdlib.h>
#include <stdio.h>
#include "chapter13.h"

int * interleave_arrays(int * a, const int a_size, int *b, const int b_size)
{
  static int *result = NULL;
  int index[2] = {0,0};
  int curr = 0;

  result = (int *) malloc (sizeof(int) * (a_size + b_size)) ;

  while (index[0] + index[1] < a_size + b_size)
  {
    if (index[0] < a_size)
    {
      result[curr++] = a[index[0]++];
    }

    if (index[1] < b_size)
    {
      result[curr++] = b[index[1]++];
    }
  }
  return result;
}

int * merge_sorted_arrays (int *a, const int a_size, int *b, const int b_size)
{
  static int *result = NULL;
  result = (int *) malloc (sizeof(int) * (a_size + b_size));
  int index[2] = {0,0};
  int curr = 0;

  while (index[0] + index[1] < a_size + b_size)
  {
    if ( index[0] < a_size && index[1] < b_size)
    {
      if (a[index[0]] < b[index[1]])
      {
        result[curr++ ] = a[index[0]++];
      }
      else if (b[index[1]] < a[index[0]])
      {
        result[curr++ ] = b[index[1]++];
      }
      else
      {
        result[curr++ ] = a[index[0]++];
        result[curr++ ] = b[index[1]++];
      }
    }
    else if (index[0] < a_size)
    {
      result[curr++ ] = a[index[0]++];
    }
    else if (index[1] < b_size)
    {
      result[curr++ ] = b[index[1]++];
    }
  }
  return result;

}

struct array_obj intersect_sorted_arrays(int *a, const int sizeA, int *b, const int sizeB)
{
  struct array_obj output;
  int index[2] = {0, 0};
  int * result = (int *) malloc(sizeof(int));
  int result_size = 0;

  while (1)
  {
    if (index[0] < sizeA && index[1] < sizeB)
    {
      if ( a[index[0]] < b[index[1]] )
      {
        index[0]++;
      }
      else if (b[index[1]] < a[index[0]])
      {
        index[1]++;
      }
      else
      {

        result[result_size++] = a[index[0]];
        index[0]++;
        index[1]++;
        result = realloc(result, sizeof(int) * (result_size +1 ) );
      }
    }
    else
    {
      break;
    }
  }
  output.data = result;
  output.size = result_size;
  return output;
}

struct array_obj intersect_sorted_arrays_dedupe(int *a, const int sizeA, int *b, const int sizeB)
{
  struct array_obj output;
  int index[2] = {0, 0};
  int * result = (int *) malloc(sizeof(int));
  int result_size = 0;

  while (1)
  {
    if (result_size > 0)
    {

      if (index[0] < sizeA)
      {
        if (result[result_size - 1] == a[index[0]] )
        {
          index[0]++;
          continue;
        }
      }
      if (index[0] < sizeA)
      {
        if (result[result_size - 1] == a[index[0]] )
        {
          index[1]++;
          continue;
        }
      }
    }

    if (index[0] < sizeA && index[1] < sizeB)
    {
      if ( a[index[0]] < b[index[1]] )
      {
        index[0]++;
      }
      else if (b[index[1]] < a[index[0]])
      {
        index[1]++;
      }
      else
      {
        result[result_size++] = a[index[0]];
        index[0]++;
        index[1]++;
      }
    }
    else
    {
      break;
    }
  }
  output.data = result;
  output.size = result_size;
  return output;
}

int func_ptr(int target, int *a, int a_size, int *b, int b_size, int *pos )
{
  if ( pos[0] < a_size )
  {
    if (target == a[pos[0]])
    {
      pos[0]++;
      return 1;
    }
  }

  if ( pos[1] < b_size )
  {
    if (target == b[pos[1]])
    {
      pos[1]++;
      return 1;
    }
  }
  return -1;
}

struct array_obj union_sorted_array (int *a, const int sizeA, int *b, const int sizeB, int (*callback)(int, int*, int, int*, int, int* ) )
{
  struct array_obj output;
  int pos[2] = {0, 0};
  int * result = (int *) malloc(sizeof(int));
  int result_size = 0;

  while (1)
  {
    if (result_size > 0)
    {
      if ( callback( result[result_size - 1], a, sizeA, b,sizeB , pos)  >= 0)
      {
        continue;
      }
    }

    if (pos[0] < sizeA && pos[1] < sizeB)
    {
      if (a[pos[0]] < b[pos[1]])
      {
        {
          result[result_size++] = a[pos[0]++];
          result = realloc(result, sizeof(int) * (result_size +1 ) );
        }

      }
      else if (b[pos[1]] < a[pos[0]])
      {
        if (a[pos[0]] > b[pos[1]])
        {
            result[result_size++] = b[pos[1]++];
            result = realloc(result, sizeof(int) * (result_size +1 ) );
        }
      }
      else
      {
          result[result_size++] = a[pos[0]];
          result = realloc(result, sizeof(int) * (result_size +1 ) );
          pos[0]++;
          pos[1]++;
      }
    }
    else if (pos[0] < sizeA)
    {
      result[result_size++] = a[pos[0]++];
      result = realloc(result, sizeof(int) * (result_size +1 ) );
    }
    else if (pos[1] < sizeB)
    {
      result[result_size++] = b[pos[1]++];
      result = realloc(result, sizeof(int) * (result_size +1 ) );
    }
    else
    {
      break;
    }
  }

  output.data = result;
  output.size = result_size;
  return output;
}

void swap (int * collection, int i, int j)
{
  int tmp;

  tmp = collection[i];
  collection[i] = collection[j];
  collection[j] = tmp;
}

struct array_obj union_sorted_array_dedupe (int *a, const int sizeA, int *b, const int sizeB)
{
  return union_sorted_array(a, sizeA, b, sizeB, func_ptr);
}

int arr_print (int *arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("[%d]", arr[i]);
  }
  printf("\n");
}

struct array_obj intersect_unsorted_array_in_place (int *a, const int sizeA, int *b, const int sizeB)
{
  struct array_obj output;
  int aa = 0;
  int bb = 0;
  int result_size = 0;
  int k = 0;

  while (aa < sizeA && bb < sizeB)
  {
    for (int i = bb; i < sizeB; i++)
    {
      if ( a[aa] == b[i] )
      {
        swap(b, i, bb++);
        swap(a, k, aa);
        k++;
        break;
      }
    }
    aa++;
  }

  output.data = a;
  output.size = k;
  return output;
}

struct array_obj intersect_unsorted_array (int *a, const int sizeA, int *b, const int sizeB)
{
  struct array_obj output;
  int * result = (int *) malloc(sizeof(int));
  int result_size = 0;
  int count_left = 0, count_right = 0;
  int curr;

  for (int aa = 0; aa < sizeA; aa++)
  {
    curr = a[aa];
    count_left = 0, count_right = 0;

    for (int i = 0; i < aa +1; i++)
    {
      count_left += (curr == a[i]);
    }

    for (int i = 0; i < sizeB; i++)
    {
      count_right += (b[i] == curr  );
    }

    if (!(count_right == 0 || count_right < count_left))
    {
      result[result_size++] = curr;
      result = realloc(result, sizeof(int) * (result_size + 1) );
    }

  }

  output.size = result_size;
  output.data = result;
  return output;
}

struct array_obj union_unsorted_arrays  (int *a, const int sizeA, int *b, const int sizeB)
{
  struct array_obj output;
  int * result = (int *) malloc(sizeof(int));
  int result_size = 0;
  int count = 0;

  for (int i = 0 ; i< sizeA ; i++)
  {
    result[result_size++] = a[i];
    result = realloc(result, sizeof(int ) * (result_size + 1) );
  }

  for (int i = 0; i < sizeB ; i++)
  {
    count = 0;

    for (int k = 0; k < sizeB; k++)
    {
      count += (b[i] == b[k]);
    }

    for (int j = 0; j < result_size; j++)
    {
      count -= (b[i] == result[j]);
    }

    if (count > 0)
    {
      result[result_size++] = b[i];
      result = realloc(result, sizeof(int ) * (result_size + 1) );
    }
  }

  output.data = result;
  output.size = result_size;
  return output;
}

int subset_sorted_array (int  *a, int sizeA, int *b, int sizeB)
{
  int count = 0;
  int bb = 0;

  for (int j = 0; j < sizeA; j++)
  {
    if (a[j] != b[bb])
    {
      count = 0;
      bb = 0;
    }

    if (a[j] == b[bb])
    {
      count++;
      bb++;
    }

    if (count ==sizeB)
    {
      return 1;
    }
  }

  return 0;
}

int subset_unsorted_array (int  *a, int sizeA, int *b, int sizeB)
{
  int end_a = sizeA - 1;
  int end_b = sizeB - 1;
  int aa = 0;
  int bb = 0;
  int count = 0;

  while (aa < sizeA && bb < sizeB)
  {
    if (a[aa] != b[bb])
    {
      if ( a[aa] == b[end_b] )
      {
        swap(b, end_b--, bb);
      }
      else if (b[bb] == a[end_a] )
      {
        swap(a, end_a--, aa);
      }
      else
      {
        aa++;
      }
    }

    if (a[aa] == b[bb])
    {
      count++;
      aa++;
      bb++;
    }

    if (count == sizeB)
    {
      return 1;
    }

  }

  return 0;
}


void PriQueue_push(struct  PriQNode **node, int priority, int value)
{
  struct PriQNode *runner;
  struct PriQNode *runner_prev = NULL;
  struct PriQNode *newNode = (struct PriQNode*) malloc(sizeof( struct PriQNode));

  newNode->next = NULL;
  newNode->pri = priority;
  newNode->value = value;

  if (*node == NULL)
  {
    *node = newNode;
  }
  else
  {
    runner = *node;
    if (priority <= runner->pri)
    {
      newNode->next = *node;
      *node = newNode;
    }
    else
    {
      while (runner->next )
      {
        if (priority <= runner->next->pri)
        {
          newNode->next = runner->next;
          runner->next = newNode;
          return;
        }
        runner = runner->next;
      }
      runner->next = newNode;
    }

  }
}

struct  PriQNode *PriQueue_pop(struct  PriQNode **node)
{
  struct PriQNode *output  = NULL;

  if (*node)
  {
    output = *node;
    (*node) = output->next;
  }
  return output;
}

void PriQueue_display(struct  PriQNode **node)
{
  struct PriQNode *runner = *node;
  while (runner)
  {
    printf("%d -- %d\n", runner->pri, runner->value);
    runner = runner->next;
  }
}

void PriQueueTest()
{
  struct PriQNode *list = NULL;
  PriQueue_push(&list, 0, 22);
  PriQueue_push(&list, 0, 25);
  PriQueue_push(&list, 2, 22);
  PriQueue_display(&list);
}




int main ()
{
  PriQueueTest();
  // int a[] = {11, 1, 13, 21, 3, 7}, b[] = {11, 3, 7, 1};
  // // int a[] = { 11, 1, 13, 21, 3, 7 } ;
  // // int b[] = { 11, 3, 7, 1  };
  // int a[] = {1, 2, 3, 4, 5, 6}, b[] = {1, 4,2, 4};
  // int a_len = sizeof(a) / sizeof(a[0]);
  // int b_len = sizeof(b) / sizeof(b[0]);
  // int x = subset_unsorted_array(a, a_len, b, b_len);
  // printf("[ %d] \n", x);

}