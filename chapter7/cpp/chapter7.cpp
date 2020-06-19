#include <iostream>
#include <utility>
#include <math.h>
#include "chapter7.h"
#include <stdlib.h>
#include <string.h>

template <typename T>
double average(std::vector<T> numbers)
{
  std::pair<bool, double> result = {false, 0};
  double avg = 0;
  double cnt = 0; 

  for (auto& num : numbers) {
    avg += num;
    cnt++;
  }
  return avg / cnt;
}

template <typename T>
bool balance_point(std::vector<T> &arr, unsigned *point)
{
  int left, right;
  bool result = false;

  for (int i = 0; i < arr.size() - 1; i++) {
		left = 0, right = 0;
	
    /*left sum*/
		for (int l = 0; l <= i; l++) {
      left += arr[l];
		}
    /*right sum*/
		for (int r = i + 1; r < arr.size(); r++) {
      right += arr[r];
		}
    result |= left == right;
    
    if (result)
			*point = i;
  }
  return result;
}

template <typename T>
bool balance_index(std::vector<T> &arr)
{
  unsigned index;
  balance_point(arr, &index);
  std::cout << index;
  return index;
}

template <typename T>
double taco_truck(std::vector<std::array<T, 2>> arr)
{
  double manhattanDistance;
  double result; 
  taco_truck_limits limits;
  int x, y;
  
for (int i = 0; i < arr.size(); i++) {
    x = arr[i][0];
    y = arr[i][1];

    if (i == 0) { 
      limits.minY = y;
      limits.maxY = y;
      limits.minX = x;
      limits.maxX = x;
    } else { 
      if (y < limits.minY)
        limits.minY = y;
      if (y > limits.maxY)
        limits.maxY = y;
      if (x < limits.minX)
        limits.minX = x;
      if (x > limits.maxX)
        limits.maxX = x;
    }
  }
  
  for (int x = limits.minX; x <= limits.maxX; x++) {
    for (int y = limits.minY; y <= limits.maxY; y++) {
      manhattanDistance = 0;
      for (auto& ele: arr) 
        manhattanDistance += std::abs(x - ele[0]) + std::abs(y - ele[1]);
      if ((x == limits.minX  && y == limits.minY) || (manhattanDistance < result))
        result = manhattanDistance;      
    }
  }
  return result;
}

bool binary_search(std::vector<int> arr, int target)
{
  unsigned curr_balance_point = std::floor( arr.size() / 2);
	
	if (arr.size() == 0)
    return false;
  if (target == arr[curr_balance_point])
    return true;
  else if (target < arr[curr_balance_point])
    return binary_search(std::vector<int>(arr.begin(), arr.begin() + curr_balance_point), target);  // vector copy constructor
  else if (target > arr[curr_balance_point])
    return binary_search(std::vector<int>(arr.begin() + curr_balance_point + 1, arr.end()), target);
}

const char* min_of_sorted_rotated(std::vector< const char*> strings)
{
  unsigned curr_balance_point = std::floor(strings.size() / 2);
  
  if (strings.size() ==  1)
    return strings[0];

  if (std::strcmp(strings[curr_balance_point +1 ], strings[curr_balance_point]) < 0 )
    return min_of_sorted_rotated(std::vector<const char*>(strings.begin()+curr_balance_point+1, strings.end()))  ;
  else if (std::strcmp(strings[curr_balance_point - 1], strings[curr_balance_point]) < 0)
    return min_of_sorted_rotated(std::vector<const char*>(strings.begin(), strings.begin() + curr_balance_point));
  else 
    return strings[curr_balance_point];
}

 int binary_search_string(std::string str, char character)
{
  unsigned curr_balance_point = std::floor(str.size() / 2); 
  
  if (str.size() == 0)
    return -1;
  
  if(str[curr_balance_point] == character)
    return true;

  if (character < str[curr_balance_point])
    return binary_search_string(str.substr(0, curr_balance_point), character);
  if (character > str[curr_balance_point])
    return binary_search_string(str.substr(curr_balance_point + 1), character);

}


 int main() {
	std::cout << binary_search_string("abcdefghijkz", 'y');
}