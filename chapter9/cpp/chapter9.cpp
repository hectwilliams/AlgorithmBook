#include <stdio.h>
#include "chapter9.h"
#include <vector>
#include <iostream>
#include <initializer_list>
#include <math.h>
#include <numeric>

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
void floodFill(std::vector<std::vector<T> > &canvas2D, const T startXY[2], const T &newColor)
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
  std::vector<std::vector<int> > canvas;
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
  for (int r = 0; r < canvas.size(); r++)
  {
    for (int c = 0; c < canvas[r].size(); c++)
    {
      printf("[%d]", canvas[r][c]);
    }
    printf("\n");
  }
}

int ackerman(unsigned a, unsigned b)
{
  if (a == 0)
    return b + 1;
  else if (b == 0)
  {
    if (a > 0)
      return ackerman(a - 1, 1);
    else
      return b + 1;
  }
  else
    return ackerman(a - 1, ackerman(a, b - 1));
}

int Zib(unsigned number)
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
    return Zib(n) + Zib(n - 1) + 1;
  }

  if (number % 2 == 0)
  {
    n = number / 2;
    return Zib(n) + Zib(n + 1) + 1;
  }
  return n;
}

void Zib_test()
{
  int data;
  for (int i = 0; i < 10; i++)
  {
    data = Zib(i);
    printf("%d --> %d\n", i, data);
  }
}

template <class T>
bool binarySearch(std::vector<T> collection, const T &target)
{
  bool is_odd = false;
  T data;
  unsigned midpoint;

  if (collection.empty())
    return false;

  midpoint = (collection.size() / 2);
  data = collection[midpoint];
  is_odd = collection.size() % 2;

  if (data == target)
    return true;
  if (target < data)
    return binarySearch(std::vector<T>(collection.begin(), collection.begin() + midpoint), target);
  if (target > data)
    return binarySearch(std::vector<T>(collection.begin() + midpoint + 1 + is_odd, collection.end()), target);
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

std::string inorder_subsets_remove_char_from_string(std::string &str, int index, int remove_count)
{
  std::string substr = "";
  unsigned counter = 0;

  while (counter != str.size())
  {
    if (remove_count <= 0)
    {
      substr += str[index];
    }
    index = (index + 1) % str.size();
    remove_count--;
    counter++;
  }
  return substr;
}

std::vector<std::string> inorder_subsets(std::string str)
{
  std::vector<std::string> collection;
  for (int rcount = 1; rcount < str.size(); rcount++)
  {
    for (int i = 0; i < str.size(); i++)
    {
      collection.push_back(inorder_subsets_remove_char_from_string(str, i, rcount));
    }
  }
  collection.push_back(str);
  collection.push_back("{}");
  return collection;
}

std::ostream &operator<<(std::ostream &out, const std::vector<std::string> &collection)
{
  for (std::string element : collection)
    out << "[" << element << "]";
  return out;
}

void inorder_subsets_test()
{
  std::cout << inorder_subsets("abc");
}

unsigned recursive_list_length(void *node)
{
  struct SLNode slnode;

  if (node == NULL)
    return 0;
  return 1 + recursive_list_length(((struct SLNode *)node)->next);
}

int got_any_grapes(int &max, std::vector<int> collection, unsigned index, unsigned curr_max)
{
  unsigned odd = index * 2 + 1;
  unsigned even = index * 2;

  if (curr_max > max)
    max = curr_max;

  if (odd < collection.size())
    got_any_grapes(max, collection, index + 1, curr_max + collection[odd]);

  if (even < collection.size())
    got_any_grapes(max, collection, index + 1, curr_max + collection[even]);

  if (index == 0)
    return max;
}

void got_any_grapes_test()
{
  std::vector<int> collection;
  for (int i = 1; i < 5; i++)
    collection.push_back(i);

  int max = 0;
  int answer = got_any_grapes(max, collection);
  printf(" answer: %d \n", max);
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

void telephone_permutation(std::vector<std::string> &collection, const std::string &phone_number, unsigned index, std::string str_accum)
{
  char c;
  std::string map_seq;

  if (phone_number.size() == 0)
  {
    return;
  }

  if (index == phone_number.size())
  {
    std::cout << "[" << str_accum << "]" << '\n';
    collection.push_back(str_accum);
    return;
  }

  c = phone_number[index];

  if (c == '-')
    map_seq = '_';

  if (c == '0')
    map_seq = "O";

  if (c == '1')
    map_seq = "1";

  if (c == '2')
    map_seq = "ABC";

  if (c == '3')
    map_seq = "DEF";

  if (c == '4')
    map_seq = "GHI";

  if (c == '5')
    map_seq = "JKL";

  if (c == '6')
    map_seq = "MNO";

  if (c == '7')
    map_seq = "PQRS";

  if (c == '8')
    map_seq = "TUV";

  if (c == '9')
    map_seq = "WXYZ";

  for (int i = 0; i < map_seq.size(); i++)
  {
    telephone_permutation(collection, phone_number, index + 1, str_accum + map_seq[i]);
  }
}

void telephone_permutation_test()
{
  std::vector<std::string> collection;
  telephone_permutation(collection, "818-2612");
}

std::string rising_squares(unsigned num, std::string str)
{
  std::string data = std::to_string((int)pow(num, 2));

  if (num == 0)
    return str;

  if (num % 2 == 1)
  {
    str = " " + str + data + " ";
  }
  else
  {
    str = " " + data + str + +" ";
  }
  return rising_squares(num - 1, str);
}

void rising_squares_test()
{
  rising_squares(5);
}

void string_expansion(std::vector<std::string> &collection, std::string bin_string, std::string str_buffer)
{
  char c;

  if (bin_string.empty() && !str_buffer.empty())
  {
    collection.push_back(str_buffer);
    return;
  }
  c = bin_string[0];
  if (c == '?')
  {
    for (int i = 0; i < 2; i++)
    {
      c = i ? '1' : '0';
      string_expansion(collection, bin_string.substr(1), str_buffer + c);
    }
  }
  else
  {
    return string_expansion(collection, bin_string.substr(1), str_buffer + c);
  }
}

void string_expansion_test()
{
  std::vector < std::string>  collection;
  string_expansion(collection, "1?0?");
  for (auto ele: collection)
    std::cout << ele << '\n';
}

void string_anagram (std::vector<std::string> &collection, const std::string &str, std::string &&str_buffer )
{
  if (str.empty()) {
    collection.push_back(str_buffer);
    return;
  }

  for (int i = 0; i < str.size(); i++) {
    string_anagram(collection, str.substr(0, i) + str.substr(i + 1), str_buffer + str[i] );
  }
}

void string_anagram_test()
{
  std::vector<std::string> collection;
  string_anagram(collection, "lmi");
  for (auto ele: collection)
    std::cout << ele << '\n';
}

void climbing_stairs (std::vector<std::vector<int> > &collection, const unsigned &climb_count, std::vector<int> &&buffer )
{
  int curr_cum = std::accumulate(buffer.begin(), buffer.end(), 0);

  if (curr_cum >=  climb_count )
  {
    if (curr_cum == climb_count)
    {
      collection.push_back(buffer);
    }
    return;
  }

  for (int i = 1; i < 3; i++) {
    buffer.push_back(i);
    climbing_stairs(collection, climb_count, std::vector<int>(buffer.begin(), buffer.end()) );
    buffer.pop_back();
  }
}

void climbing_stairs_test()
{
  std::vector<std::vector<int> > collection;
  climbing_stairs(collection, 4);
  std::cout << collection;
}

std::ostream &operator<<(std::ostream &out, const std::vector < std::vector<int> >  &collection)  /* print int vector */
{
  for (int i = 0; i < collection.size(); i++) {
    for (auto ele: collection[i]) {
      out << "[" << ele << "]";
    }
    out << '\n';
  }
  return out;
}


int main()
{
  climbing_stairs_test();

}