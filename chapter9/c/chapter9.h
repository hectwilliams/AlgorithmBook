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
void telephone_words(const char **collection, const char *phone_number, unsigned index, char *buffer);
#define telephone_words_MAX_WORD_LENGTH 8
#endif