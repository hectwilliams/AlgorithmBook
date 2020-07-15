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

struct int_array_t
{
  unsigned size;
  int *data;
};

struct int_vector_array_t
{
  unsigned size;
  struct int_array_t ** array_vector;
};

struct int_vector_array_t climb_stairs(const unsigned climb_count);
void climb_stairs_helper(const unsigned climb_count, struct int_array_t *element, struct int_vector_array_t *info);

int int_array_t_sum (struct int_array_t *arr_element);

struct int_vector_array_t  square_sum( const unsigned num );
void square_sum_helper( const unsigned num, int start, struct int_vector_array_t *info , struct int_array_t *array);

struct const_char_array_t
{
  unsigned size;
  const char  **collection;
};

struct const_char_array_t valid_n_pair_paren (unsigned num);
void valid_n_pair_paren_helper(const unsigned num,  char * buffer, struct const_char_array_t *obj);
int valid_paren (const char * string);
int tower_of_hanoi(const unsigned size);

typedef struct disks {
  int value;
  struct disks *next;
} disks;

struct pole
{
  unsigned size;
  disks *disk_list;
};

struct pole_list {
  struct pole *curr_poles;
  struct pole_list *next;
};

typedef struct tower
{
  struct pole *poles;
  unsigned size;

  struct tower *children_array;
  unsigned children_size;
} tower;

void print_tower(struct pole *poles, unsigned size);
void tower_of_hanoi_helper(unsigned size, unsigned *search_count, unsigned iteration, struct pole *poles, struct pole_list **collection );
struct disks * tower_of_hanoi_pop();
void tower_of_hanoi_copy_tower_state(struct pole *dest, struct pole *src, unsigned size);
void tower_of_hanoi_insert(struct pole *pole, int value);
struct disks *disk_allocate(int value);
void print_disk(struct pole *pole);
int tower_of_hanoi_move_disk (struct pole *tower, unsigned dest_sel, unsigned  src_sel);
void tower_of_hanoi_buffer_poles_add (struct pole_list **collection, struct pole *poles);
unsigned  tower_of_hanoi_buffer_has_pole(struct pole_list **collection, struct pole *poles, unsigned size);
int tower_of_hanoi_compare_poles(struct pole *a, struct pole *b, unsigned size);
#endif




