#include <stdio.h>
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
    return  tribonacci(num - 3) + tribonacci(num - 2) + tribonacci(num - 1);
}


void fibonacci_test() {
  for (double i = 0; i < 5; i++) {
    printf("[%d]\n", fibonacci(i));
  }
}

void tribonacci_test() {
  for (double i = 0; i < 5; i++) {
    printf("[%d]\n", tribonacci(i));
  }
}

int paging_ackermann(unsigned  a, unsigned b)
{
  if (a == 0)
    return b + 1;
  else if (b == 0) {
    if (a > 0)
      return paging_ackermann(a - 1, 1);
    else
      return b + 1;
  } else
    return paging_ackermann(a - 1, paging_ackermann(a, b -1));
}

int Zibonacci(unsigned number )
{
  unsigned n = 0;

  if (number <= 1) {
    return 1;
  }

  if (number == 2) {
    return 2;
  }

  if (number % 2 == 1) {
    n = --number / 2;
    return Zibonacci(n) + Zibonacci(n - 1) + 1;
  }

  if (number % 2 == 0) {
    n = number / 2;
    return Zibonacci(n) + Zibonacci(n + 1) + 1;
  }
  return n;

}

void Zibonacci_test()
{
  int data;
  for (int i = 0; i <10; i++) {
    data = Zibonacci(i);
    printf("%d --> %d\n", i, data );
  }
}

int main()
{
  Zibonacci_test();
}