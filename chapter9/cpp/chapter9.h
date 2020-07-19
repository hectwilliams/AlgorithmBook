#ifndef CHAPTER_9_H
#define CHAPTER_9_H
#include <vector>
#include <array>
#include <string>
#include <iostream>

int recursive_sigma(int number);
int recursive_factorial(double number);
template <class T>
void floodFill(std::vector<std::vector<T> > &canvas2D, const T startXY[2], const T &newColor);
template <class T>
bool binarySearch(std::vector<T> collection, const T &target);
int tarai(int x, int y, int z);
std::vector<std::string> inorder_subsets(std::string str);
std::string inorder_subsets_remove_char_from_string(std::string &str, int index, int remove_count);
std::ostream &operator<<(std::ostream &out, const std::vector<std::string> &collection); /* print string vector */
struct SLNode
{
  int value;
  struct SLNode *next;
};
unsigned recursive_list_length(void *node);
int got_any_grapes(int &max, std::vector<int> collection, unsigned index = 0, unsigned curr_max = 0);
int collatz_apalooza(unsigned num);
void telephone_permutation(std::vector<std::string> &collection, const std::string &phone_number, unsigned index = 0, std::string str_accum = "");
std::string rising_squares(unsigned num, std::string str = "");
void string_expansion(std::vector<std::string> &collection, std::string bin_string, std::string str_buffer = "");
void string_anagram ( std::vector<std::string> &collection, const std::string &str, std::string &&str_buffer = "") ;
void climbing_stairs (std::vector<std::vector<int> > &collection, const unsigned &climb_count, std::vector<int> &&buffer = std::vector<int>() );
std::ostream &operator<<(std::ostream &out, const std::vector < std::vector<int> >  &collection);  /* print string vector */
void sum_of_squares(std::vector< std::vector<int> >  & collection, const unsigned &target, unsigned start = 1, std::vector<int> &&buffer = std::vector<int>());
void all_valid_n_paren (std::vector<std::string> &collection, unsigned n, std::string &&buffer = "");
bool valid_paren (std::string str);

typedef std::array < std::vector<int> , 3 > tower_t;
std::ostream &operator << (std::ostream &out, const tower_t &tower);

typedef unsigned int uint32_t;
void tower_of_hanoi_helper(unsigned size, std::vector <tower_t *> **towers_used, tower_t *tower, unsigned &search_count, unsigned  &&curr_count);
unsigned  tower_of_hanoi(unsigned size);
void tower_of_hanoi_deep_copy_tower(tower_t *dest, tower_t *src, uint32_t size);
bool tower_of_hanoi_mv(tower_t *tower, uint32_t dest_index, uint32_t src_index, uint32_t size);
void tower_of_hanoi_shift_pole(tower_t *tower, uint32_t pole_index, bool right_shift_en = false, uint32_t size = 3);
bool tower_of_hanoi_tower_in_collection(std::vector<tower_t*> **collection, tower_t *tower, uint32_t size);
void tower_of_hanoi_tower_add_to_collection(std::vector<tower_t*> **collection, tower_t *tower);
bool tower_of_hanoi_compare_towers(tower_t *tower_a, tower_t *tower_b, uint32_t size );
void  tower_of_hanoi_remove_collection (std::vector <tower_t *> ** collection);
void ipAddress_add (std::vector<std::string> &collection ,const std::string digits, const std::vector<int> &buffer);
void ipAddress(const std::string &digits, std::vector<std::string> &collection, std::vector<int>  &&buffer = std::vector<int>() );

int unevenDigit(int number, unsigned index = 0, bool is_neg = false);

struct CoinData
{
 unsigned dimes;
 unsigned nickels;
 unsigned pennies;
 unsigned quarters;
};

 enum coins
  {
    PENNY = 1,
    NICKEL = 5,
    DIME = 10,
    QUARTER = 25
  };

void  generate_coin_change_data (unsigned cents, struct CoinData &obj);
typedef std::array<int, 2> chess_pos_t;
bool isMoveSafe(  std::array<int ,2 > intended_move, std::array<int, 2> queen);
bool isMoveSafe_queens( chess_pos_t mv, std::vector< chess_pos_t> &collection, unsigned index = 0 );

void allSafeChessSquares (chess_pos_t queen, std::vector<chess_pos_t> &collection, unsigned count = 0);
void allSafeChessSquares (std::vector<chess_pos_t> queens, std::vector<chess_pos_t> &collection, int index = 0);

bool chessMoveCmpr(chess_pos_t pos_a, chess_pos_t pos_b);
void positionListAdd(chess_pos_t mv, std::vector<chess_pos_t> &collection);

void positionListRemove(chess_pos_t mv, std::vector<chess_pos_t> &collection);

#define CHESS_BOARD_ROW 8
#define CHESS_BOARD_COL 8

#endif

