#ifndef CHAPTER_9_H
#define CHAPTER_9_H

typedef enum boolean
{
  False,
  True
} boolean;

int recursive_sigma(int number);
int recursive_factorial(double number);
void flood_fill(int canvas2D[5][5], int startXY[2], int newColor);
boolean recursive_binary_search(int collection[], unsigned size, int target);
int rGCF(int a, int b);
int tarai(int x, int y, int z);
void in_order_subset_remove_string(const char *str, unsigned index, int remove_count, char *data);
char *inorder_subsets(const char *str, unsigned size);
struct SLNode
{
  int value;
  struct SLNode *next;
};
unsigned recursive_list_length(void *node);
int got_any_grapes_helper(int collection[], unsigned size, unsigned curr_index, unsigned curr_max, unsigned *max);
int got_any_grapes(int collection[], unsigned size);
int collatz_apalooza(unsigned num);
#define telephone_words_MAX_WORD_LENGTH 8
void telephone_words(const char **collection, const char *phone_number, int index, char *buffer);
void rising_squares(int num);
void rising_squares_step(int stop_index, int num);

void binary_expansion(const char **collection, const char *bin_string);
void binary_expansion_helper(const char **collection, unsigned *wr_index, const char *bin_string, const unsigned bin_string_len, unsigned index, char *str_buffer);

// #define FUNC_MACRO(function, ...)  (function)(__VA_ARGS__); /**/
struct anagram_data anagram(const char *string);
struct anagram_data
{
  unsigned word_size;
  unsigned array_size;
  const char ** collection;
};
void anagram_helper(const char ** collection, unsigned *wr_index, unsigned string_max_len, const char *string, char *buffer);

struct stair_info climb_stairs(const unsigned climb_count);


struct stair_climb_array
{
  unsigned size;
  unsigned *array;
};

struct stair_info
{
  unsigned size;
  struct stair_climb_array **stair_climb_array_list;
};

void climb_stairs_helper(const unsigned climb_count, struct stair_climb_array *element, struct stair_info *info);
unsigned climb_stairs_array_sum(struct stair_climb_array *arr_element);
#endif
