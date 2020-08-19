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

int main ()
{
  int a[] = {1,2,3,4};
  int b[] = {5,6,7,8};
  int a_len = sizeof(a) / sizeof(a[0]);
  int b_len = sizeof(b) / sizeof(b[0]);

  int* x = merge_sorted_arrays(a, a_len, b, b_len);
  for (int i = 0; i < a_len + b_len; i++)
  {
    printf(" %d \n", x[i]);
  }
}