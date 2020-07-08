#ifndef CHAPTER_9_H
#define CHAPTER_9_H
#include <vector>
#include <string>
#include <array>
#include <iostream>

int recursive_sigma(int number);
int recursive_factorial(double number);
template <class T>
void floodFill(std::vector<std::vector<T>> &canvas2D, const T startXY[2], const T &newColor);
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
void telephone_words(std::vector<std::string> &collection, std::string *phone_number, std::string str_accum = "");

#endif