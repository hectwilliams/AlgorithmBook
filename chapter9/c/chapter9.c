#include <stdio.h>
#include <string.h>
#include "chapter9.h"

int recursive_sigma(int number)
{
  if (number <= 0)
    return 0;
  return number + recursive_sigma(number - 1);
}

int recursive_factorial(double number)
{
  if (number <= 1)
    return 1;
  return (int)number * recursive_factorial(number - 1);
}

void flood_fill(int canvas2D[5][5], int startXY[2], int newColor)
{
  int row = startXY[0];
  int col = startXY[1];
  int currColor;
  int newStartXY[2];

  /* outside limits */
  if ((row < 0 || row >= 5) || (col < 0 || col >= 5))
    return;

  currColor = canvas2D[row][col];

  /* fill color */
  canvas2D[row][col] = newColor;

  /* walk up */
  if (row > 0)
  {
    newStartXY[0] = row - 1;
    newStartXY[1] = col;
    if (currColor == canvas2D[newStartXY[0]][newStartXY[1]])
      flood_fill(canvas2D, newStartXY, newColor);
  }

  /* walk down */
  if (row < 4)
  {
    newStartXY[0] = row + 1;
    newStartXY[1] = col;
    if (currColor == canvas2D[newStartXY[0]][newStartXY[1]])
      flood_fill(canvas2D, newStartXY, newColor);
  }

  /* walk left */
  if (col > 0)
  {
    newStartXY[0] = row;
    newStartXY[1] = col - 1;
    if (currColor == canvas2D[newStartXY[0]][newStartXY[1]])
      flood_fill(canvas2D, newStartXY, newColor);
  }

  /* walk right */
  if (col < 4)
  {
    newStartXY[0] = row;
    newStartXY[1] = col + 1;
    if (currColor == canvas2D[newStartXY[0]][newStartXY[1]])
      flood_fill(canvas2D, newStartXY, newColor);
  }
}

void test_recursive_factorial()
{
  int canvas[5][5] = {
      {3, 2, 3, 4, 3},
      {2, 3, 3, 4, 0},
      {7, 3, 3, 5, 3},
      {6, 5, 3, 4, 1},
      {1, 2, 3, 3, 3},
  };

  int startXY[2] = {2, 2};

  flood_fill(canvas, startXY, 1);

  /*print array*/
  for (int r = 0; r < 5; r++)
  {
    for (int c = 0; c < 5; c++)
    {
      printf("[%d]", canvas[r][c]);
    }
    printf("\n");
  }
}

int fibonacci(double num)
{
  if (num <= 0)
    return 0;
  else if (num == 1)
    return 1;
  else
    return fibonacci(num - 2) + fibonacci(num - 1);
}

int tribonacci(double num)
{
  if (num <= 1)
    return 0;
  else if (num == 2)
    return 1;
  else
    return tribonacci(num - 3) + tribonacci(num - 2) + tribonacci(num - 1);
}

void fibonacci_test()
{
  for (double i = 0; i < 5; i++)
  {
    printf("[%d]\n", fibonacci(i));
  }
}

void tribonacci_test()
{
  for (double i = 0; i < 5; i++)
  {
    printf("[%d]\n", tribonacci(i));
  }
}

int paging_ackermann(unsigned a, unsigned b)
{
  if (a == 0)
    return b + 1;
  else if (b == 0)
  {
    if (a > 0)
      return paging_ackermann(a - 1, 1);
    else
      return b + 1;
  }
  else
    return paging_ackermann(a - 1, paging_ackermann(a, b - 1));
}

int Zibonacci(unsigned number)
{
  unsigned n = 0;

  if (number <= 1)
  {
    return 1;
  }

  if (number == 2)
  {
    return 2;
  }

  if (number % 2 == 1)
  {
    n = --number / 2;
    return Zibonacci(n) + Zibonacci(n - 1) + 1;
  }

  if (number % 2 == 0)
  {
    n = number / 2;
    return Zibonacci(n) + Zibonacci(n + 1) + 1;
  }
  return n;
}

void Zibonacci_test()
{
  int data;
  for (int i = 0; i < 10; i++)
  {
    data = Zibonacci(i);
    printf("%d --> %d\n", i, data);
  }
}

boolean recursive_binary_search(int collection[], unsigned size, int target)
{
  unsigned mid;
  unsigned data;
  int *copy_collection;
  unsigned is_odd = 0;

  if (size == 0)
    return False;

  mid = (size / 2);
  data = collection[mid];
  is_odd = +(size % 2);

  if (target == data)
  {
    return True;
  }
  else if (target < data)
  {
    return recursive_binary_search(collection, mid, target);
  }
  else if (target > data)
  {
    return recursive_binary_search(collection + mid + 1, size - (mid + is_odd), target);
  }
}

void recursive_binary_search_test()
{
  int collection[5] = {4, 5, 6, 8, 12};
  int collection_size = 5;
  boolean answer = recursive_binary_search(collection, sizeof(collection) / collection[0], 4);
  printf(" has 5 in list --> %d", answer); // True
  answer = recursive_binary_search(collection, sizeof(collection) / collection[0], 4);
  printf(" has 5 in list --> %d", answer); // False
}

int rGCF(int a, int b)
{
  if (a == 0)
    return b;
  return rGCF(b % a, a);
}

int tarai(int x, int y, int z)
{
  if (x <= y)
    return y;
  return tarai(tarai(x - 1, y, z), tarai(y - 1, z, x), tarai(z - 1, x, y));
}

void tarai_test()
{
  int answer = tarai(10, 2, 9);
  printf("%d", answer);
}

void in_order_subset_remove_string(const char *str, unsigned index, int remove_count, char *data)
{
  char buffer[128]; //128 bytes should be enough :)
  unsigned str_size = sizeof(str);
  unsigned counter = 0;
  unsigned int bufer_index = 0;
  char c;
  while (counter != str_size)
  {
    c = *(str + index);
    if (remove_count <= 0 && c)
    {
      memset(buffer + bufer_index++, c, 1);
      memset(buffer + bufer_index, 0, 1);
    }
    index = (index + 1) % str_size;
    remove_count--;
    counter++;
  }

  if (bufer_index > 0)
  {
    strcat(data, buffer);
    strcat(data, ",");
    printf(" %d ", index);
    printf(" %s \n ", buffer);
  }
}

char *inorder_subsets(const char *str, unsigned size)
{
  static char data[] = "";
  for (int rcount = 0; rcount < size + 1; rcount++)
  {
    if (rcount == 0)
    {
      strcat(data, str);
      strcat(data, ",");
    }
    else if (rcount == size)
    {
      strcat(data, "{}");
      strcat(data, ",");
    }
    else
    {
      for (int start_index = 0; start_index < size; start_index++)
      {
        in_order_subset_remove_string(str, start_index, rcount, data);
      }
    }
  }
  return data;
}

void inorder_subsets_test()
{
  char *answer = inorder_subsets("abc", 3);
  printf("%s\n", answer);
}

unsigned recursive_list_length(void *node)
{
  struct SLNode slnode;

  if (node == NULL)
    return 0;
  return 1 + recursive_list_length(((struct SLNode *)node)->next);
}

int main()
{
  inorder_subsets_test();
  printf("dd");
}