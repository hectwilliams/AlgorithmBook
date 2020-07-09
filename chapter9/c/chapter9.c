#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int got_any_grapes_helper(int collection[], unsigned size, unsigned curr_index, unsigned curr_max, unsigned *max)
{
  unsigned odd = curr_index * 2 + 1, even = curr_index * 2;
  if (curr_max > *max)
    *max = curr_max;

  if (odd < size)
    return got_any_grapes_helper(collection, size, curr_index + 1, curr_max + collection[odd], max);

  if (even < size)
    return got_any_grapes_helper(collection, size, curr_index + 1, curr_max + collection[even], max);
}

int got_any_grapes(int collection[], unsigned size)
{
  unsigned int max = 0;
  got_any_grapes_helper(collection, size, 0, 0, &max);
  return max;
}

int collatz_apalooza(unsigned num)
{
  if (num % 2 == 0)
    return num / 2;
  return 3 * num + 1;
}

void collatz_apalooza_test()
{
  int data = 5;
  for (int i = 5; i--;)
  {
    printf("[%d]", data);
    data = collatz_apalooza(data);
  }
  // 5 16 8 4 2 -- printed
}

unsigned word_count(char *word)
{
  unsigned count = 0;
  char *prev;

  while (*word != '\0')
  {
    prev = word;

    if (*prev == 0)
      break;

    word++;
    count++;
  }
  return count;
}

unsigned word_count(const char *word)
{
  unsigned count = 0;
  const char *prev;
  while (*word != '\0')
  {
    prev = word;
    if (*prev == 0)
      break;
    word++;
    count++;
  }
  return count;
}

unsigned collection_index = 0;
void telephone_words(const char **collection, const char *phone_number, int index, char *buffer)
{
  char digit;
  char str_buffer[5] = "";
  unsigned str_size = word_count(buffer);

  if (word_count(buffer) == telephone_words_MAX_WORD_LENGTH)
  {
    collection[collection_index] = buffer;
    collection[++collection_index] = "DEADBEEF";
    return;
  }

  digit = *(phone_number + index);

  if (digit == '-')
    strcat(str_buffer, "-");
  else if (digit == '0')
    strcat(str_buffer, "O");
  else if (digit == '1')
    strcat(str_buffer, "I");
  else if (digit == '2')
    strcat(str_buffer, "ABC");
  else if (digit == '3')
    strcat(str_buffer, "DEF");
  else if (digit == '4')
    strcat(str_buffer, "GHI");
  else if (digit == '5')
    strcat(str_buffer, "JKL");
  else if (digit == '6')
    strcat(str_buffer, "MNO");
  else if (digit == '7')
    strcat(str_buffer, "PQRS");
  else if (digit == '8')
    strcat(str_buffer, "TUV");
  else if (digit == '9')
    strcat(str_buffer, "WXYZ");
  else
    strcat(str_buffer, "\0");

  if (str_buffer)
  {
    for (char *ptr = str_buffer; *ptr != 0; ptr++)
    {
      char *clone = (char *)malloc(10); /* allocation heap data (persistent) */
      strncpy(clone, buffer, str_size); /* copy current string */
      clone[str_size] = *ptr;           /* append char */
      clone[str_size + 1] = '\0';       /* append NULL */
      telephone_words(collection, phone_number, index + 1, clone);
    }
  }
}

void telephone_words_test()
{
  const char *collection[300] = {"DEADBEEF"};
  char buffer[10] = "";
  telephone_words(collection, "818-2612", 0, buffer);
  for (int i = 0; collection[i] != "DEADBEEF"; i++)
  {
    printf(" %d  [%s] \n", i, collection[i]);
  }
}

void rising_squares_step(int stop_index, int num)
{

  if (num % 2 == 0)
  {
    if (num <= stop_index)
      return;
    printf("[%d]", num * num);
    return rising_squares_step(stop_index, num - 2);
  }
  else
  {
    if (num > stop_index)
      return;
    printf("[%d]", num * num);
    return rising_squares_step(stop_index, num + 2);
  }
}

void rising_squares(int num)
{
  rising_squares_step(num, 1);
  rising_squares_step(0, num - 1);
}

void rising_squares_test()
{
  rising_squares(5);
}

void binary_expansion(const char **collection, const char *bin_string)
{
  unsigned start_index = 0;
  unsigned len = word_count(bin_string) + 1; // tail char = null
  unsigned wr_index = 0;
  binary_expansion_helper(collection, &wr_index, bin_string, len, start_index, NULL);
  for (int i = 0; i < wr_index; i++)
    printf("%d  [%s]\n", i, collection[i]);
}

void binary_expansion_helper(const char **collection, unsigned *wr_index, const char *bin_string, const unsigned bin_string_len, unsigned index, char *str_buffer)
{
  char character;

  if (index == bin_string_len - 1)
  {
    str_buffer[index] = '\0'; /* add null end of string */
    collection[*wr_index] = str_buffer;
    (*wr_index)++;
    return;
  }

  if (str_buffer == NULL)
    str_buffer = (char *)malloc(bin_string_len); /* char vector allocation*/

  character = bin_string[index];

  if (character == '?')
  {
    char *str_buffer_one = (char *)malloc(bin_string_len);
    for (int i = 0; i < 2; i++)
    {
      char *str_buffer_copy = (char *)malloc(bin_string_len); /* char vector allocation*/
      memcpy(str_buffer_copy, str_buffer, bin_string_len);    /* copy input string to copy variable*/
      str_buffer_copy[index] = (i) ? '0' : '1';               /* possible expansion */
      binary_expansion_helper(collection, wr_index, bin_string, bin_string_len, index + 1, str_buffer_copy);
    }
  }
  else
  {
    str_buffer[index] = character;
    return binary_expansion_helper(collection, wr_index, bin_string, bin_string_len, index + 1, str_buffer);
  }
}

void binary_expansion_test()
{
  const char *collection[1000];
  binary_expansion(collection, "1?0??");
  /* solution 
    string buffer 1101
    string buffer 1100
    string buffer 1001
    string buffer 1000
  */
}

void anagram(const char **collection, const char *string, unsigned index, char *buffer)
{
}

void anagram(const char **collection, const char *string)
{
  unsigned string_len = word_count(string);
  char c;

  for (int i = 0; i < string_len; i++)
  {
    c = string[i];
    /* copy string */
    char *buffer = (char *)malloc(string_len);
  }
}

void anagram_test()
{
  const char *collection[100];
  anagram(collection, "lmi");
}

int main()
{
  binary_expansion_test();
}
