#ifndef CHAPTER7_H
#define CHAPTER7_H

#include <vector>
#include <array>
#include <iostream>
#include <utility>   //pair 
#include <algorithm> // swap
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>
#include <set>

template <typename T>
double average(std::vector<T> numbers);

template <typename T>
bool balance_point(std::vector<T>const  &arr, unsigned *point = NULL);

template <typename T>
bool balance_index(std::vector<T> &arr);

typedef struct taco_truck_limits {
  int minX;
	int maxX;
  int minY;
  int maxY;
} taco_truck_limits;

template <typename T>
double taco_truck(std::vector<std::array<T,2>> arr);
bool binary_search(std::vector<int> arr, int target);
const char* min_of_sorted_rotated(std::vector<const char*> strings);
int binary_search_string(std::string str, char character);

std::vector<int> remove_duplicates(std::vector<int>& collection);
void remove_duplicates_second(std::vector<int>& collection);
void remove_duplicates_third(std::vector<int>& collection);

typedef struct mode_struct {
	bool valid;
	int max;
} mode_struct;
mode_struct  mode(std::vector<int> collection);

void arr_buffer_copy(std::vector<int> source, std::vector<int> dest,unsigned source_start_index, unsigned dest_start_index, unsigned numVals);
unsigned int smarter_sum(unsigned int num);
unsigned int faster_factorial(unsigned int num);
unsigned iFib(unsigned int num);
unsigned int iTrib(unsigned int num);
double median_sorted_arrays(std::vector<int> a, std::vector<int> b);
std::string time_to_english(unsigned int num);
int missing_value(std::vector<int> numbers);
unsigned int rain_terraces(std::vector<int> heights);
unsigned int last_digit_a_to_b(unsigned int a, unsigned int b);

bool matrix_search(std::vector<std::vector<int>> image, std::vector<std::vector<int>> sub_image);
std::string max_subarray(std::vector<int> numbers);

#endif // !CHAPTER7_H



