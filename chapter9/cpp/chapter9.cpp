#include <stdio.h>
#include "chapter9.h"
#include <vector>
#include <iostream>

int sigma(int number)
{
  if (number <= 0)
    return 0;
  return number + sigma(number - 1);
}

int factorial(double number)
{
  if (number <= 1)
    return 1;
  return static_cast<int>(number) * factorial(number - 1);
}

template <class T>
void floodFill(std::vector< std::vector<T> > &canvas2D, const int startXY[2], const T &newColor)
{
  int row = startXY[0];
  int col = startXY[1];
  int rowSize;
  int colSize;
  T prevColor;
  int xy[2];

  /* outside limits */
  if (row < 0 || row >= canvas2D.size())
    return;

  if (col < 0 || col >= canvas2D[row].size())
    return;

  rowSize = canvas2D.size();
  colSize = canvas2D[row].size();
  prevColor = canvas2D[row][col];
  canvas2D[row][col] = newColor;

  /* walk up */
  if (row > 0)
  {
    xy[0] = row - 1;
    xy[1] = col;
    if (prevColor == canvas2D[xy[0]][xy[1]])
      floodFill(canvas2D, xy, newColor);
  }

  /* walk down */
  if (row < rowSize - 1)
  {
    xy[0] = row + 1;
    xy[1] = col;
    if (prevColor == canvas2D[xy[0]][xy[1]])
      floodFill(canvas2D, xy, newColor);
  }

  /* walk left */
  if (col > 0)
  {
    xy[0] = row;
    xy[1] = col - 1;
    if (prevColor == canvas2D[xy[0]][xy[1]])
      floodFill(canvas2D, xy, newColor);
  }

  /* walk right */
  if (col < colSize - 1)
  {
    xy[0] = row;
    xy[1] = col + 1;
    if (prevColor == canvas2D[xy[0]][xy[1]])
      floodFill(canvas2D, xy, newColor);
  }
}

void test_recursive_factorial()
{
  std::vector< std::vector<int> > canvas;
  // Array Data
  // {
  //     {3, 2, 3, 4, 3},
  //     {2, 3, 3, 4, 0},
  //     {7, 3, 3, 5, 3},
  //     {6, 5, 3, 4, 1},
  //     {1, 2, 3, 3, 3},
  // };

  int startXY[2] = {2, 2};
  floodFill(canvas, startXY, 1);

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

int ackerman(unsigned  a, unsigned b)
{
  if (a == 0)
    return b + 1;
  else if (b == 0) {
    if (a > 0)
      return ackerman(a - 1, 1);
    else
      return b + 1;
  } else
    return ackerman(a - 1, ackerman(a, b -1));
}

int Zib(unsigned number )
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
    return Zib(n) + Zib(n - 1) + 1;
  }

  if (number % 2 == 0) {
    n = number / 2;
    return Zib(n) + Zib(n + 1) + 1;
  }
  return n;

}

void Zib_test()
{
  int data;
  for (int i = 0; i <10; i++) {
    data = Zib(i);
    printf("%d --> %d\n", i, data );
  }
}

int main()
{
}