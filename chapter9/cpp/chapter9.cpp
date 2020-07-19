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


void sum_of_squares(std::vector< std::vector<int> >  & collection, const unsigned &target, unsigned start , std::vector<int> &&buffer)
{
  int curr_sum = std::accumulate(buffer.begin(), buffer.end(), 0) ;

  if (curr_sum >= target)  {
    if (curr_sum == target) {
      collection.push_back(buffer);
    }
    return;
  }

  for (unsigned  i  = start; i < target; i++ )
  {
    buffer.push_back(i*i);
    sum_of_squares(collection, target, start + 1, std::vector<int>(buffer.begin(), buffer.end()) );  // new instance recursion
    buffer.pop_back();

  }
}

void sum_of_squares_test ()
{

  std::vector< std::vector<int> >  vector;
  sum_of_squares(vector, 10);  // [1][9]
  for (auto ele: vector)
    std::cout << vector;
}

void all_valid_n_paren (std::vector<std::string> &collection, unsigned n, std::string && buffer)
{
  char pair [2] = {'(', ')'};

  if ( buffer.size() >= std::pow(2,n))
  {
    if (valid_paren(buffer) &&  buffer.size() == std::pow(2, n))
    {
      collection.push_back(buffer);
    }
    return;
  }

  for (int i = 0; i < 2; i++)
  {
    all_valid_n_paren(collection, n, buffer + pair[i]);
  }
}

bool valid_paren (std::string str)
{
  std::vector<char> stack;

  for (auto ele: str) {
    if (ele == '(')
      stack.push_back(ele);

    if (ele == ')') {
      if (stack.empty())
        return false;
      stack.pop_back();
    }
  }
  return stack.empty();
}

void all_valid_n_paren_test()
{
  std::vector<std::string> collection;
  all_valid_n_paren(collection, 2);
  std::cout << collection;;
}

unsigned tower_of_hanoi_init_tower (tower_t *tower)
{
  int  poles = 3;

  for (unsigned i = 0; i < poles; i++)
  {
    for (unsigned n = 0; n < poles; n++)
    {
      tower->at(i).push_back( i == 0 ? n + 1 : 0);
    }
  }
}




std::ostream &operator << (std::ostream &out, const tower_t &tower)
{
  for (int row = 0; row < 3; row++)
  {
    out << "\t Tower " << row << "\t [  ";
    for (int col = 0; col < tower.size(); col++)
    {
      out << tower[row][col] <<  "  |   ";
    }
    out << "]\n";
  }
  return out;
}



void tower_of_hanoi_shift_pole(tower_t *tower, uint32_t pole_index, bool right_shift_en , uint32_t size)
{
  std::vector <int>  &vector = tower->at(pole_index);

  if ( right_shift_en == false )
  {
    for (int i = 0; i  < size - 1 ; i++)
    {
      vector[i] = vector[i + 1];
    }
    vector[size - 1] = 0;
  }
  else if (right_shift_en == true)
  {
    for (int i = size - 1; i > 0; i--)
    {
      vector[i] = vector[i - 1];
    }
    vector[0] = 0;
  }
}



bool tower_of_hanoi_mv(tower_t *tower, uint32_t dest_index, uint32_t src_index, uint32_t size)
{
  if (tower == NULL)
  {
    return false;
  }

  if (src_index == dest_index) /* reassigning itself not allowed */
  {
    return false;
  }

  if (tower->at(src_index)[0] == 0)   /* src pole empty */
  {
    return false;
  }

  if ( tower->at(dest_index)[0] == 0) /* empty dest index */
  {
    tower->at(dest_index)[0] = tower->at(src_index)[0];
    tower_of_hanoi_shift_pole(tower, src_index, false, size);  // false = left
    return true;
  }

  if (  (tower->at(dest_index)[ size - 1 ] == 0) &&  (tower->at(dest_index)[0] > tower->at(src_index)[0])  )
  {
    /* shift dest array right */
    tower_of_hanoi_shift_pole(tower, dest_index, true, size);

    /* insert src pole top value */
    tower->at(dest_index)[0] = tower->at(src_index)[0];

    /* shift src array left */
    tower_of_hanoi_shift_pole(tower, src_index, false, size);

    return true;
  }
  return false;
}

void tower_of_hanoi_deep_copy_tower(tower_t *dest, tower_t *src, uint32_t size)
{
  if (dest == NULL || src == NULL)
  {
    return;
  }
  for (int pole_index = 0; pole_index < 3; pole_index++)
  {
    for (int i = 0; i < size; i++)
    {
      dest->at(pole_index).push_back( src->at(pole_index)[i]);
    }
  }
}

bool tower_of_hanoi_tower_in_collection(std::vector<tower_t*> **collection, tower_t *tower, uint32_t size )
{
  tower_t *collection_element;

  if (*collection == NULL)
  {
    return false;
  }

  for (int i = 0; i < (*collection)->size(); i++)
  {
    if (tower_of_hanoi_compare_towers((*collection)->at(i), tower, size))
    {
      return true;
    }
  }
  return false;
}

void tower_of_hanoi_tower_add_to_collection(std::vector<tower_t*> **collection, tower_t *tower)
{
  if (*collection == NULL)
  {
    *collection = (std::vector<tower_t*> *) malloc( sizeof( std::vector<tower_t*> ) );
  }

  (*collection)->push_back(tower);
}

bool tower_of_hanoi_compare_towers(tower_t *tower_a, tower_t *tower_b, uint32_t size )
{
  for (int row = 0; row < 3; row++)
  {
    for (int col = 0; col < size; col++)
    {
      if ( tower_b->at(row)[col] != tower_a->at(row)[col])
      {
        return false;
      }
    }
  }
  return true;
}

void tower_of_hanoi_helper(unsigned size, std::vector <tower_t *> **towers_used, tower_t *tower, unsigned &search_count, unsigned  &&curr_count)
{
  uint32_t  sel = 0;
  tower_t *clone_tower;

  // std::cout << *tower;  /* view current tower state */

  if (search_count > 0) {
    return;
  }

  if (tower->at(2)[size - 1] != 0 )
  {
    // std::cout << *tower;
    search_count = curr_count;
    return;
  }

  if (tower_of_hanoi_tower_in_collection(towers_used, tower, size))
  {
    return;
  }
  else
  {
    tower_of_hanoi_tower_add_to_collection(towers_used, tower);
  }

  for (uint32_t pole_index = 0;  pole_index < 3; pole_index++)
  {
    for (uint32_t step_pole = 1; step_pole < 3; step_pole++)
    {
      sel = (pole_index + step_pole) % 3;
      clone_tower = (tower_t *) malloc(sizeof(tower_t));
      tower_of_hanoi_deep_copy_tower(clone_tower, tower, size);
      if (tower_of_hanoi_mv (clone_tower, sel, pole_index, size))
      {
        tower_of_hanoi_helper(size, towers_used, clone_tower, search_count, curr_count+ 1);
      }
    }
  }
}

void  tower_of_hanoi_remove_collection( std::vector<tower_t*> **collection) /*  free up resources usedd*/
{
  while ( (*collection)->size() != 1) /*0th pointer allocated on stack */
  {
     free ( (*collection)->back());
     (*collection)->pop_back();
  }
  free(*collection); /* free allocate vector */
}

unsigned  tower_of_hanoi(unsigned size)
{
  tower_t init_tower;
  unsigned search_count = 0;
  std::vector <tower_t *> *tower_collection = NULL;
  tower_of_hanoi_init_tower(&init_tower); // initliaze tower
  tower_of_hanoi_helper(size, &tower_collection, &init_tower, search_count, 0 ); // solver
  tower_of_hanoi_remove_collection(&tower_collection);
  return search_count;
}

void tower_of_hanoi_test ()
{
  unsigned test_data = tower_of_hanoi(3);
  std::cout << test_data << '\n';
}

void ipAddress_add (std::vector<std::string> &collection ,const std::string digits, const std::vector<int> &buffer)
{
  int digit_pos = 0;
  int dot_count = 0;

  collection.push_back("");

  for (auto counter: buffer )
  {
    while (counter)
    {
      collection[collection.size() - 1] += digits[digit_pos++];
      --counter;
    }

    if (++dot_count < 3)
    {
      collection[collection.size() - 1]  += '.';
    }
  }
  std::cout << collection.back() << '\n';
}

 void ipAddress(const std::string &digits, std::vector<std::string> &collection, std::vector<int>  &&buffer)
 {

   int curr_sum = std::accumulate( buffer.begin(), buffer.end(), 0);

   if (buffer.size() == 4)
   {
     if (curr_sum)
     {
       ipAddress_add(collection, digits, buffer);
     }
     return;
   }
   else if (curr_sum > digits.size())
   {
     return;
   }

   for (int i = 1; i <= 3; i++)
   {
     buffer.push_back(i);
     ipAddress(digits, collection, std::vector<int>(buffer.begin(), buffer.end()) );
     buffer.pop_back();
   }

 }

 void ipAddress_test ()
 {
   std::vector<std::string> collection;
   ipAddress("255255255", collection);

   for (auto ele: collection)
   {
     std::cout << ele << '\n';
   }
 }

int unevenDigit(int number, unsigned index, bool is_neg)
{
  int digit;
  int data;

  if (index == 0 && number < 0)
  {
    is_neg = true;
    number *= -1;
  }

  if (number <= 0)
  {
    return 0;
  }

  digit = number % 10;

  if (digit % 2 == 0)
  {
    data =  0 + unevenDigit(number / 10, index + 1, is_neg );
  }
  else
  {
    data =  digit * (int)pow(10, index) + unevenDigit(number / 10, index + 1, is_neg );
  }

  if (index == 0 && is_neg)
  {
    data *= -1;
  }
  return data;
}

void unevenDigit_test ()
{
  int answer = unevenDigit(79);
  std::cout << answer << '\n';
}

void generate_coin_change_data (unsigned cents, struct CoinData &obj)
{

  if (cents <= 0)
  {
    return;
  }

  if (cents >= QUARTER)
  {
    obj.quarters++;
    cents -= QUARTER;
  }

  else if (cents >= DIME)
  {
    obj.dimes++;
    cents -= DIME;
  }

  else if (cents >= NICKEL)
  {
    obj.nickels++;
   cents -= NICKEL;
  }

  else if (cents >= PENNY)
  {
    obj.pennies++;
    cents -= PENNY;
  }
  return generate_coin_change_data(cents, obj);
}

void generate_coin_change_test()
{
  struct CoinData obj = {.dimes = 0, .nickels = 0, .pennies = 0, .quarters = 0} ;
  generate_coin_change_data(23, obj);
  printf(" Quarte [%d] Dimes[%d] Nickel[%d]  Penny[%d] \n",
    obj.quarters,
    obj.dimes,
    obj.nickels,
    obj.pennies
  );
}

std::ostream &operator << (std::ostream &out, const chess_pos_t & arr)
{
  out << "[" << arr[0] << "," << arr[1] << "]";
  return out;
}
bool isMoveSafe (  chess_pos_t intended_move, chess_pos_t queen)
{
  /* left diagonal   \ */
  if (intended_move[0] - intended_move[1] == queen[0] - queen[1] )
  {
    return false;
  }

  /* right diagonal * / */
  if (intended_move[0] + intended_move[1] == queen[0] + queen[1] )
  {
    return false;
  }

  /* row */
  if (intended_move[0] ==  queen[0])
  {
    return false;
  }

  /* col */
  if (intended_move[1] == queen[1])
  {
    return false;
  }

  return true;
}

bool isMoveSafe_queens( chess_pos_t mv, std::vector< chess_pos_t> &collection, unsigned index  )
{
  if (collection.size() == index)
  {
    return true;
  }
  else
  {
    return isMoveSafe(mv, collection[index]) && isMoveSafe_queens(mv, collection, index + 1 );
  }
}

void isMoveSafe_test()
{
  std::array<int, 2> mv, queen;

  mv[0] = 0; mv[1] = 7; queen[0] = 6; queen[1] = 2;  // pass
  std::cout << isMoveSafe( mv, queen) << '\n';

  mv[0] = 0; mv[1] = 7; queen[0] = 6; queen[1] = 1; // fail
  std::cout << isMoveSafe( mv, queen) << '\n';

  std::vector<chess_pos_t> queens;
  chess_pos_t data = {6, 2};
  chess_pos_t data2 = {6,3};
  queens.push_back(data);
  queens.push_back(data2);
  std::cout << "array is  safe "<<  isMoveSafe_queens(mv, queens) << '\n';

}

bool chessMoveCmpr(chess_pos_t pos_a, chess_pos_t pos_b)
{
  for (int i = 0; i < pos_a.size(); i++)
  {
    if (pos_a[i] != pos_b[i])
    {
      return false;
    }
  }
  return true;
}

void allSafeChessSquares (chess_pos_t queen, std::vector<chess_pos_t> &collection, unsigned count)
{
  chess_pos_t pos = {count / CHESS_BOARD_ROW, count % CHESS_BOARD_COL};
  if (count>= CHESS_BOARD_COL * CHESS_BOARD_ROW)
  {
    return;
  }

  if (isMoveSafe(pos, queen))
  {
    positionListAdd(pos, collection);
  }
  else
  {
    positionListRemove(pos, collection);
  }
  return allSafeChessSquares( queen, collection , count + 1);
}

void allSafeChessSquares (std::vector<chess_pos_t> queens, std::vector<chess_pos_t> &collection, int index )
{
  int collection_index = 0;

  if (index >= queens.size())
  {
    return;
  }

  if (collection.empty())
  {
    for (int r = 0; r < 8; r++)
    {
      for (int c = 0; c < 8; c++)
      {
        chess_pos_t pos ={r,c};

        if  (isMoveSafe(queens[index] , pos))
        {
          positionListAdd(pos, collection);
        }
      }
    }
  }

  else
  {
    collection_index = 0;
    while(collection_index < collection.size())
    {
      if (!isMoveSafe(queens[index], collection[collection_index]))
      {
        collection.erase(collection.begin() + collection_index);
      }
      else

      {
        collection_index++;
      }
    }
  }

  return allSafeChessSquares( queens, collection , index + 1);

}

void positionListAdd(chess_pos_t mv, std::vector<chess_pos_t> &collection)
{
  /* redunancy not allowed */
  for (chess_pos_t & valid_moves: collection)
  {
    if ( chessMoveCmpr(valid_moves, mv))
    {
      return;
    }
  }
  collection.push_back(mv);
}

void positionListRemove(chess_pos_t mv, std::vector<chess_pos_t> &collection)
{
  int index = 0;
  chess_pos_t delme;

  while (index != collection.size())
  {
    if (chessMoveCmpr(collection[index], mv))
    {
      delme = collection[index];
      collection.erase(collection.begin() + index);
    }
    else
    {
      index = index + 1;
    }
  }
}

void allSafeChessSquaes_test ()
{
  std::vector<chess_pos_t> collection;
  chess_pos_t pos =  {0,1};
  allSafeChessSquares(pos, collection);
  std::cout <<  collection.size() << '\n';
  for (auto ele: collection)
  {
    std::cout << ele << '\n';
  }
}

void allSafeChessSquaes_queens_test ()
{
  std::vector<chess_pos_t> collection;
  std::vector<chess_pos_t> queens;

    chess_pos_t queen = {0,0};
  chess_pos_t queen2 = {0,3};
  chess_pos_t queen3 = {1,3};
  chess_pos_t queen4 = {7,3};
  chess_pos_t queen5 = {5,2};

  queens.push_back(queen);
  queens.push_back(queen2);
  queens.push_back(queen3);
  queens.push_back(queen4);
  queens.push_back(queen5);

  // queens.push_back(queen2);

  allSafeChessSquares(queens, collection);

  for (auto ele: collection)
  {
    std::cout << ele << '\n';
  }

}

int main()
{
  allSafeChessSquaes_queens_test();
}