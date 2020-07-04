#ifndef CHAPTER_9_H
#define CHAPTER_9_H
#include <vector>
int recursive_sigma(int number);
int recursive_factorial(double number);
template <class T>
void floodF_fill(std::vector<std::vector<T>> canvas2D, const T startXY[2], const T &newColor);

#endif