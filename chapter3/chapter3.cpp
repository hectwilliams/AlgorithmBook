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
#include "chapter3.h"


namespace chapter3
{

	template <typename T>
	T Arrays<T>:: pop_front(std::vector<T>& arr) {
		T data = arr[0];
		arr.erase(arr.begin());
		return data;
	}

	template <typename T>
	void Arrays<T>::push_front(std::vector<T>& arr, const T& data) {
		arr.insert(arr.begin(), data);
	}

	template <typename T>
	void Arrays<T>:: insert_at(std::vector<T>& arr, unsigned pos, T value) {
		arr.insert(arr.begin() + pos, value);
	}

	template <typename T>
	void Arrays<T>::remove_at(std::vector<T>& arr, unsigned pos, T value) {
		arr.erase(arr.begin() + pos);
	}

	template <typename T>
	void Arrays<T>::swap_pairs(std::vector<T>& arr) {
		for (int i = 0; i < arr.size(); i += 2) {
			if (i + 1 < arr.size() ) {
				auto tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
	}

	template<typename T>
	void Arrays<T>::remove_duplicates(std::vector<T>& arr) {
		int i = 1;
		while (i < arr.size()) {
			if (arr[i - 1] == arr[i]) {
				arr.erase(arr.begin() + i);
			} else {
				i++;
			}
		}
	}

	template <typename T>
	void Arrays<T>::min_to_front( std::vector<T> & arr) {
		T data;
		
		if (arr.empty())
			return; 

data = arr[0];
for (int i = 1; i < arr.size(); i++) {
	if (arr[i] < data) {
		data = arr[i];
	}
}
std::swap(data, arr[0]);
printf("%d", arr[0]);
	}

	template <typename T>
	void Arrays<T>::reverse(std::vector<T>& arr) {
		for (int i = 0; i < std::floor(arr.size() / 2); i++) {
			std::swap(arr[i], arr[arr.size() - 1 - i]);
		}
		print(arr);
	}

	template <typename T>
	void Arrays<T> ::print(std::vector<T> arr) {
		for (auto ele : arr) {
			printf("%d \t", ele);
		}
		printf("\n");
	}

	template <typename T>
	void Arrays<T>::rotate(std::vector<T>& arr, unsigned shiftBy) {
		for (int k = 0; k < shiftBy % arr.size(); k++) {
			/* move tail to front*/
			if (shiftBy > 0) {
				for (int i = arr.size() - 1; i > 0; i--)
					std::swap(arr[i], arr[i - 1]);
			}

			if (shiftBy < 0) {
				for (int i = 0; i < arr.size() - 1; i++)
					std::swap(arr[i], arr[i - 1]);
			}
		}
	}

	template <typename T>
	void Arrays<T>::filter_range(std::vector<T>& arr, unsigned min, unsigned max) {
		if (min >= max)
			return;

		for (; arr.size() < max;)
			arr.pop_back();
		for (int i = 0; i < min; i++)
			arr.erase(arr.begin());
	}

	template <typename T>
	std::vector<T> Arrays<T>::concat(const std::vector<T>& a, const std::vector<T>& b) {
		std::vector<T> result;
		unsigned ptr_a = 0, ptr_b = 0;
		while (ptr_a < a.size() || ptr_b < b.size()) {
			if (ptr_b >= b.size())
				result.push_back(a[ptr_a++]);
			else if (ptr_a >= a.size())
				result.push_back(b[ptr_b++]);
			else if (ptr_a < a.size())
				result.push_back(a[ptr_a++]);
			else if (ptr_b < b.size())
				result.push_back(b[ptr_b++]);
		}
		return result;
	}

	template <typename T>
	std::vector<T> Arrays<T>::skyline_heights(const std::vector<T>& arr) {
		std::vector<T> result;
		T data;

		if (arr.empty()) {
			return result;
		}

		data = arr[0];
		if (arr[0] > 0) {
			result.push_back(arr[0]);
		}

		for (int i = 1; i < arr.size(); i++) {
			if (arr[i] > data) {
				data = arr[i];
				result.push_back(data);
			}
		}
		return result;
	}

	template< typename T>
	bool Arrays<T>::credit_card_validation( const std::vector<T> arr) {
		unsigned max_index = arr.size() - 1;
		unsigned curr_index = max_index - 1;
		unsigned sum  = arr[max_index];
		unsigned digit = 0;

		if (!(arr.size() >= 13 && arr.size() <= 19) )
			return false;

		for (int i = curr_index; i >= 0; i--) {
			digit = arr[i];
			if (i % 2 == 1)
				digit *= 2;
			if (digit > 9)
				digit -= 9;
			sum += digit;
		}

		return (sum % 10) == 0;
	
	}

	template <typename T>
	void Arrays<T>::shuffle(std::vector<T>& arr) {
		unsigned r = 0;
		unsigned low_index = 0, upper_index = arr.size() - 1;

		for (int i = 0; i < arr.size() - 1; i++) {
			low_index = i + 1;
			r = (rand() % (upper_index - low_index + 1)) + low_index;
			std::swap(arr[i], arr[r]);
		}
	}

	template <typename T>
	void Arrays<T>::remove_range(std::vector<T>& arr, unsigned start, unsigned end) {
		int counter = end - start + 1;

		for (int i = 0; i < arr.size(); ) {
			if (i == start  &&  counter > 0) {
				--counter;
				arr.erase(arr.begin() + i);
			} else {
				i++;
			}
		}
	}

	template <typename T>
	void Arrays<T>::intermediate_sum(std::vector<T>& arr) {
		unsigned curr_index = 0;
		unsigned sum = 0;

		if (arr.size() == 0)
			return; 

		while (true) {
			sum += arr[curr_index++];
			if (curr_index % 10 == 0) {
				arr.insert(arr.begin() + curr_index++, sum);
				sum = 0;
			}
			if (curr_index >= arr.size()) {
				if (sum !=0) {
					arr.push_back(sum);
				}
				break;
			}
		}
	}

	template <typename T>
	std::vector<T> Arrays<T>::zip_it(const std::vector<T> &a, const std::vector<T> &b) {
		std::vector<T> result;
		unsigned ptr_a = 0, ptr_b = 0;

		while ( ptr_a < a.size() || ptr_b < b.size() ) {
			if (ptr_a >= a.size())
				result.push_back(b[ptr_b++]);
			else if (ptr_b >= b.size())
				result.push_back(a[ptr_a++]);
			else if (ptr_a == ptr_b)
				result.push_back(a[ptr_a++]);
			else if (ptr_a > ptr_b)
				result.push_back(b[ptr_b++]);
		}
		return result;
	}

	template <typename T>
	void Arrays<T>::double_trouble(std::vector<T>& arr) 
	{
		unsigned len = arr.size() * 2;
		
		for (int i = 0; i < len; i += 2) {
			arr.insert(arr.begin() + i + 1, arr[i]);
		}
		print(arr);
	}

	template class Arrays<unsigned>;
	template class Arrays<signed>;
};