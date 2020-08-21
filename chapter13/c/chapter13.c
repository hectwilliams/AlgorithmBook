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

int main ()
{
  int a[] = { 6,7,2,7,6,2 } ;
  int b[] = {2,7,2,1,2  };
  int a_len = sizeof(a) / sizeof(a[0]);
  int b_len = sizeof(b) / sizeof(b[0]);


  struct array_obj arr = union_unsorted_arrays(a, a_len, b, b_len);

  for (int i = 0; i < arr.size; i++)
  {
    printf("[%d]", arr.data[i]);
  }
}