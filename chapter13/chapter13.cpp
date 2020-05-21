#include <iostream>
#include <math.h>
#include <set>
#include <vector>
#include <array>
#include <algorithm>
#include <string.h>
#include <cstdlib>
#include <numeric> // accumulate
#include <stdio.h> 
#include <stdlib.h>
#include <sstream>
#include <tuple>
#include <deque>
#include <exception>
#include <memory>
#include <chrono>
#include <mutex>
#include <future>
#include <iomanip>
#include <errno.h>
#include <string.h>
#include "chapter13.h"
extern int errno;



namespace chapter13 {

	std::array<int, 2> MinimalThreeArrayRange(std::vector<int> a, std::vector<int> b, std::vector<int> c ) {
		int currIndex;
		int min = INT_MIN, tupleIndex;
		std::vector<int> array, tupleBuffer;
		int a_int = 0, b_int = 0, c_int = 0;
		std::array<bool, 3> boolean = { false, false, false };
		std::vector < std::tuple< std::vector<int>, int>> tupleMap = {
			{a, a_int},
			{b, b_int},
			{c, c_int}
		};
		std::array<int, 2> result{};


		while (true) {
			min = INT_MIN;
			currIndex = -1;

			for (int i = 0; i < tupleMap.size(); i++) {	
				std::tie(array, tupleIndex) = tupleMap[i];
				if (tupleIndex < array.size()) {
					if (array[tupleIndex] < min || min == INT_MIN) {
						min = array[tupleIndex];
						currIndex = i;
					}
				}
			}

			if (currIndex != -1) {
				boolean[currIndex] = true;
				tupleBuffer.push_back(min);
				++std::get<1>(tupleMap[currIndex]);
			}

			if (boolean[0] && boolean[1] && boolean[2]) {
				result = { tupleBuffer[tupleBuffer.size() - 3] ,  tupleBuffer[tupleBuffer.size() - 1] };
				break;
			}

			if (std::get<1>(tupleMap[0]) == a.size() && std::get<1>(tupleMap[1]) == b.size() && std::get<1>(tupleMap[2]) == c.size() )
				break;
		}
		return result;
	}

	std::vector<int> IntersectSortedArray(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;
		int aa = 0, bb = 0;

		while (1) {
			
			if (aa >= a.size() || bb >= b.size())
			 break;
			else if (a[aa] < b[bb])
				aa++;
			else if (b[bb] < a[aa])
				bb++;
			else if (b[bb] == a[aa]) {
				result.push_back(a[aa]);
				bb++;
				aa++;
			}

		}

		printf("size \t%d", result.size());
		return result;
	}

	std::vector<int> IntersectSortedArrayDedupe(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;
		int aa = 0, bb = 0;

		while (1) {

			if (aa >= a.size() || bb >= b.size())
				break;
			
			if (!result.empty()) {  
				if (result.back() == a[aa]) {
					aa++;
					continue;
				}

				if (result.back() == b[bb]) {
					bb++;
					continue;
				}
			}

			 if (a[aa] < b[bb])
				aa++;
			else if (b[bb] < a[aa])
				bb++;
			else if (b[bb] == a[aa]) {
				result.push_back(a[aa]);
				bb++;
				aa++;
			}

		}

		printf("size \t%d", result.size());
		return result;
	}
	std::vector<int> UnionSortedArrays(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;
		int aa = 0, bb = 0;

		while (1) {
			if (aa >= a.size() && bb >= b.size())
				break;

			if (bb >= b.size())
				result.push_back(a[aa++]);

			else if (aa >= a.size())
				result.push_back(b[bb++]);

			else if (b[bb] < a[aa])
				result.push_back(b[bb++]);

			else if (a[aa] < b[bb])
				result.push_back(a[aa++]);

			else if (a[aa] == b[bb]) {
				result.push_back(a[aa]);
				bb++;
				aa++;
			}

		}

		return result;
	}


	std::vector<int> UnionSortedArraysDedupe(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;
		int aa = 0, bb = 0;
		
		while (1) {

			if (aa >= a.size() && bb >= b.size())
				break;

			if (result.size()) {
				if (result.back() == a[aa]) {
					aa++;
					continue;
				} else if (result.back() == b[bb]) {
					bb++;
					continue;
				}
			}


			if (bb >= b.size())
				result.push_back(a[aa++]);

			else if (aa >= a.size())
				result.push_back(b[bb++]);

			else if (b[bb] < a[aa])
				result.push_back(b[bb++]);

			else if (a[aa] < b[bb])
				result.push_back(a[aa++]);

			else if (a[aa] == b[bb]) {
				result.push_back(a[aa]);
				bb++;
				aa++;
			}

		}
		for (auto x : result)
			printf(" values %d \n", x);

		return result;
	}


	std::vector<int> IntersectionUnsortedArrayInPlace(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;

		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < b.size(); j++) {
				if (a[i] == b[j] && std::find(result.begin(), result.end(), j) == result.end()) {
					result.push_back(j);
					break;
				}
			}
		}

		for (auto &ele : result) {
			ele = b[ele];
		}
		
		return result;
	}


	std::vector<int> UnionUnsortedArrays(std::vector<int> a, std::vector<int> b) {
		std::map<int, int> a_map, b_map;
		std::map<int, int>::iterator it, prev_it;
		std::vector<int> result; 


		for (auto ele : a) {
			it = a_map.find(ele);

			if (it == a_map.end()) {
				a_map.insert(std::make_pair(ele, 1));
			} else {
				it->second++;
			}
			
			result.push_back(ele);
		}

		for (auto ele : b) {
			it = b_map.find(ele);
			prev_it = a_map.find(ele);

			if (it == b_map.end()) {
				b_map.insert(std::make_pair(ele, 1));

				if (prev_it == a_map.end())
					result.push_back(ele);
				
			} else {
				it->second++;
				
				if (prev_it != a_map.end()) {
					if (prev_it->second < it->second) 
						result.push_back(ele);
				} else {
					result.push_back(ele);
				}
			}
		}
		return result; 
	}

	std::vector<int> UnionUnsortedArraysInPlace(std::vector<int> &a, std::vector<int> b) {
		std::map<int, int> a_map, b_map;
		std::map<int, int>::iterator it, prev_it;

		for (auto ele : a) {
			it = a_map.find(ele);

			if (it == a_map.end()) 
				a_map.insert(std::make_pair(ele, 1));
			else 
				it->second++;
		}

		for (auto ele : b) {
			it = b_map.find(ele);
			prev_it = a_map.find(ele);

			if (it == b_map.end()) {
				b_map.insert(std::make_pair(ele, 1));

				if (prev_it == a_map.end())
					a.push_back(ele);
			} else {
				it->second++;

				if (prev_it != a_map.end()) {
					if (prev_it->second < it->second)
						a.push_back(ele);
				}
				else {
					a.push_back(ele);
				}
			}
		}
		return a;
	}


	std::vector<int> UnionUnsortedArraysDedupe(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;
		std::map<int, int> map;
		std::map<int, int>::iterator it;

		for (auto ele : a) {
			it = map.find(ele);
			if (it == map.end()) {
				map.insert(std::make_pair(ele, 1));
				result.push_back(ele);
			}
		}

		for (auto ele : b) {
			it = map.find(ele);
			if (it == map.end()) {
				map.insert(std::make_pair(ele, 1));
				result.push_back(ele);
			}
		}

		return result;
	}

	bool SubsetSortedArrays (std::vector<int> a, std::vector<int> b) {
		int index = -1; 
		std::map <int, int> map;
		std::vector<int> result; 
		
		for (int i = 0; i < a.size(); i++) {
			if (map.find(a[i]) == map.end())
				map.insert(std::make_pair(a[i], i));
		}
	
		for (auto ele : b) {
			if (map.find(ele) != map.end()) {
				if (index == -1)
					index = map.find(ele)->second;
				else if (a[++index] != ele)
					return false;
			} 
		}
		return true;
	}

	bool SubsetUnSortedArrays (std::vector<int> a, std::vector<int> b) {
		int tail = a.size() - 1;
		int head = 0;
		std::map <int, int> map;

		while (tail >= head) {
			if (map.find(a[head]) == map.end()) {
				map.insert(std::make_pair(a[head], 1));
			}
			if (map.find(a[tail]) == map.end()) {
				map.insert(std::make_pair(a[tail], 1));
			}
			tail--;
			head++;
		}

		tail = b.size() - 1;
		head = 0;
		while (tail >= head) {
			if (map.find(b[tail--]) == map.end() || map.find(b[head++]) == map.end())
				return false;
		}
		return true;
	}

	
	void Sequencer(std::vector < std::tuple<uint64_t, std::string>> array ) {
		uint64_t num;
		std::string str; 
		PriQueue<std::string, uint64_t> queue;

		for (int i = 0; i < array.size(); i++) {
			std::tie(num, str) = array[i];
			queue.push(str, num);
		}
	}
  
}