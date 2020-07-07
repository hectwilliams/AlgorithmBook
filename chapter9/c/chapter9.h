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
#endif