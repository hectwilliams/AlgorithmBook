#ifndef CHAPTER7_H
#define CHAPTER7_H
#include <vector>
#include <array>

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

#endif // !CHAPTER7_H
