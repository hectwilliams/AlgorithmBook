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

int main()
{
  test_recursive_factorial();
}