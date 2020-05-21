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
#include "chapter7.h"

extern int errno;


namespace chapter7 {

	unsigned average(int unsorted_numbers[], const size_t& size)
	{
		int avg = 0;
		
		if (size == 0) {
			perror("size must be greater than 0");
			fprintf(stderr, "");
			avg = -1;
		} else {
			for (int *ptr = unsorted_numbers; ptr < &unsorted_numbers[size]; ptr++) {
				avg += *ptr;
			}
			avg /= size;
		}
		return avg;
	}

	bool balance_point(const int numbers[], const size_t &size)
	{	
		int left = 0, right = 0;
		for (int i = 0; i < std::floor(size / 2); i++) {
			left += numbers[i];
			right += numbers[size - 1 - i];
		}
		return left == right;
	}

	int balance_index(const int numbers[], const size_t& size)
	{
		int left, right;
		unsigned result = -1;

		for (int point = 1; point < size - 1 && result == -1; point++) {
			left = 0;
			right = 0;

			for (int l = 0; l < point; l++) {
				left += numbers[l];
			}

			for (int r = point + 1; r < size; r++) {
				right += numbers[r];
			}

			if (left == right) {
				result = point;
			}
		}

		return result; 
	}                      

	static int taco_truck_helper_sum_manhattan(int point_x, int point_y, const int  numbers[][2], size_t size) {
		int result = 0; 
		for (int i = size; i--;) {
			result += std::abs(point_x - numbers[i][0]) + std::abs(point_y - numbers[i][1]);
		}
		return result;
	}

	int* taco_truck(const int numbers[][2], const size_t size)
	{
		int xmin = 0, xmax = 0, ymin = 0, ymax = 0;
		int tmp, manhattan_sum;
		int count = 0;
		static int result[2];

		/* loop finds points to discovery plane*/
		for (int i = 0; i < size; i++) {
			if (numbers[i][0] < xmin) xmin = numbers[i][0];
			if (numbers[i][0] > xmax) xmax = numbers[i][0];
			if (numbers[i][1] < ymin) ymin = numbers[i][1];
			if (numbers[i][1] > ymax) ymax = numbers[i][1];
		}

		/* loops through points of discovery plane for minimum (i.e. manhattan distance) sum */

		for (int r = ymin; r <= ymax; r++) {
			for (int c = xmin; c <= xmax; c++) {
				tmp = taco_truck_helper_sum_manhattan(c, r, numbers, size);
				if (count++ == 0 ||  tmp < manhattan_sum) {
					manhattan_sum = tmp;
					*(result ) = c;
					*(result + 1)= r;
				}
			}
		}

		return result;
	}

	bool binary_search(const int numbers[], const size_t size, int value)
	{
		int mid_index = std::floor(size / 2);
		int left_count = mid_index, right_count = mid_index - +(size % 2 == 0);
		int data = numbers[mid_index];
		bool result = false; 
		int* buffer;

		buffer = (int*)malloc(mid_index * sizeof(int));
		
		if (data == value) {
			result = true;
		} else if (data > value) {
			std::memmove(buffer, numbers, left_count * sizeof(int));
			result = binary_search(buffer, left_count, value);
		} else if (data < value) {
			std::memmove(buffer, numbers + mid_index + 1, right_count * sizeof(int) );
			result = binary_search(buffer, right_count, value);
		}

		free(buffer); 
		return result; 
	}

	const char* min_of_sorted_rotated( const char *data[],  size_t size)
	{
		const char** buffer;
		int mid = std::floor(size / 2);
		int left, right;
		const char* result;
		int left_count = mid, right_count = mid - +(size % 2 == 0);

		if (size == 1)
			return *data;

		buffer = (const char**)malloc(mid * sizeof(const char**));

		if ( (std::strcmp(data[0], data[mid]) < 0) && (std::strcmp(data[0], data[size -1 ]) < 0)) {
			 std::memcpy(buffer, data, left_count *sizeof(char**));
			 result = min_of_sorted_rotated(buffer, left_count);
		} else if (std::strcmp(data[size - 1], data[mid]) < 0) {
			std::memcpy(buffer, data + mid + 1, right_count * sizeof(char**));
			result = min_of_sorted_rotated(buffer, right_count);
		} else {
			return *(data + mid);
		}

		free(buffer);
		return result;

	}

	bool str_binary_search(const char* data, const size_t size, const char* character)
	{
		unsigned mid = std::floor(size / 2);
		unsigned left = mid;
		unsigned right = mid - +(size % 2 == 0);
		bool result = false; 
		char* buffer = NULL;

		if (size <= 0)
			return false;
		
		if (std::memcmp(character,data + mid, 1) == 0) 
			return true;
		
		buffer = (char*) malloc(mid *sizeof( char*));

		if (std::memcmp(character, data + mid, 1) < 0) {
			std::memcpy(buffer, data , left * sizeof(char*));
			result = str_binary_search(buffer, left, character);
		} else {
			std::memcpy(buffer, data + mid + 1, right * sizeof(char*));
			result = str_binary_search(buffer, right, character);
		}

		if (buffer)
			free(buffer);

		return result;

	}

	int* remove_duplicates(int array_of_numbers[], int size)
	{
		static int* result;
		int* buffer = (int*)calloc(1, sizeof(int)); /* |size|d0|d1|d2.. */
		int bytes;
		int de_dupe_len;
		bool insert_unique_data;

		for (int i = 0; i < size; i++) {
			insert_unique_data = true;
			for (int n = 1; n < *buffer && insert_unique_data; n++) {
				insert_unique_data = !(*(buffer + n) == array_of_numbers[i]);
			}
			if (insert_unique_data) {
				*buffer += (*buffer == 0) ? 2 : 1;
				buffer = (int*)realloc(buffer, (*buffer * sizeof(int)));
				*(buffer + (*buffer - 1)) = array_of_numbers[i];
			}
		}

		de_dupe_len = *buffer - 1;
		bytes = de_dupe_len * sizeof(int);
		result = (int*) malloc(bytes);
		std::memcpy(result, buffer + 1, bytes);
		free(buffer);
		return result;
	}

	unsigned mode(int array_of_numbers[], int size)
	{
		static int result = 0; 
		int data, index = 0, tmp; 
		int count = 0;

		/* transform array - equal values are adjacent*/
		for (int i = 0; i < size ; i++) {
			data = *(array_of_numbers + i);
			index = i;
			for (int j = i; j < size; j++) {
				if (array_of_numbers[j] == data) {
					tmp = array_of_numbers[index];
					memset(array_of_numbers + index, data, 1);
					memset(array_of_numbers + j, tmp, 1);
					index++;
				}
			}
		}

		for (int i = 1; i < size; i++) {
			if (count > result) 
				result = count;
			if (array_of_numbers[i - 1] != array_of_numbers[i]) 
				count = 0;
			count++;
		}
		return result;
	}

	void array_buffer_copy(void* dest, size_t dest_size, void* src, size_t src_size, size_t bytes, size_t src_offset_start, size_t dest_offset_start)
	{
		size_t count = 0;
		
		void* start = (char*)dest + dest_offset_start;
		void* dest_ptr = start;
		void* dest_ptr_end = (char*)dest + dest_size;
		void* src_ptr = (char*)src + src_offset_start;
		void* src_ptr_end = (char*)src + src_size;
		
		while ((char*)src_ptr < (char*)src_ptr_end) {

			if (count >= bytes)
				break;

			/* wrap around destintation buffer*/
			if ((char*)dest_ptr == (char*)dest_ptr_end)
				dest_ptr = start;

			/*break at end*/
			//if ((char*)dest_ptr == (char*)dest_ptr_end || count >= bytes)  //break;

			memset(dest_ptr, *((char*)src_ptr), 1);
			src_ptr = (char*) src_ptr + 1;
			dest_ptr = (char*) dest_ptr + 1;
			count++;
		}
	}

	int smarter_sum(unsigned int num)
	{
		int result = num;
		for (int i = 1; i < num; i++) {
			result += i;
		}
		return result;
	}

	int faster_factorial(unsigned int num) 
	{
		int result = 1;
		for (; num > 1; num--) {
			result*= num;
		}
		return result;
	}

	int fancy_fib (unsigned int num) 
	{
		int* block = (int*)calloc(2, sizeof(int));
		int data; 
		memset(block + 1, 1, 1);

		if (num < 2)
			return *(block + num);

		for (int i = 2; i <= num; i++) {
			data = *(block + 1) + *(block);
			memset(block, *(block + 1), 1);
			memset(block + 1, data, 1);
		}

		free(block);
		return data;
	
	}

	int trick_trib(unsigned int num)
	{
		int data;
		int* block = (int*) calloc(3, sizeof(int));
		memset(block + 2, 1, 1);

		if (num < 3) {
			return *(block + num);
		}

		for (int i = 3; i <= num; i++) {
			data = block[0] + block[1] + block[2];
			memmove(block, block + 1, 2 * sizeof(int));
			block[2] = data;
		}

		free(block);
		return data;
	}
	
	double median_sorted_two_arrays(int a[], size_t size_a, int b[], size_t size_b)
	{
		unsigned a_ptr = 0, b_ptr = 0;
		unsigned  size = (size_a + size_b);
		unsigned mid =  std::floor(size / 2);
		int* addr = NULL, *addr_prev = NULL;;

		if (size == 0) {
			perror("size equal to zero...returning -1");
			fprintf(stderr, "");
		}
		while (mid--) {
			addr_prev = addr;
			if (a[a_ptr] < b[b_ptr]) {
				a_ptr++;
				addr = &a[a_ptr];
			} else {
				b_ptr++;
				addr = &b[b_ptr];
			}
		}
		return (size % 2 == 0) ? (*addr_prev + *addr)/2.0 : *addr ;
	}

	double median_sorted_three_arrays(int a[], size_t size_a, int b[], size_t size_b, int c[], size_t size_c)
	{
		int size = size_a + size_b + size_c;
		int mid = std::floor(size / 2);
		int **data = (int**) calloc(3, sizeof(int)), **min_addr = NULL, *min_addr_prev = NULL;

		/* reference pointers */
		data[0] = a;
		data[1] = b;
		data[2] = c;

		if (size == 0) {
			perror("arrays sum equal to zero returning -1 ");
			fprintf(stderr,"");
			return -1;
		}

		/* find min */
		while (mid--) {

			if (!!min_addr) {
				min_addr_prev = *min_addr;
			}

			min_addr = data;
			
			for (int i = 0; i < 3; i++) {
				if ( *data[i] < **min_addr) {
					min_addr = data + i;
				}
			}

			/* update reference pointer*/
			*min_addr = *min_addr + 1;
		}

		free(data);
		return (size % 2 == 0) ? (*min_addr_prev + **min_addr) / 2.0 : **min_addr;

	}

	const char* time_in_english(unsigned minutes)
	{
		unsigned h = (minutes / 60) % 24;
		unsigned m = minutes % 60;
		
		static char msg[50] = "";
		const char *meridiem = (h > 12) ? "pm" : "am"; 
		
		char * a = (char*)calloc(10, sizeof(char));
		char * b = (char*)calloc(6, sizeof(char));
		char*  c = (char*)calloc(10, sizeof(char));

		if (m <= 30) {
			sprintf_s(b, 6, "past ", m);
		} else {
			m = 60 - m;
			sprintf_s(b, 6, "till ", m);
		}

		sprintf_s(a, 4, "%d ", m);

		if (m == 15)
			sprintf_s(a, 10, "quarter ", m);
		if (m == 30)
			sprintf_s(a, 6, "half ", m);

		if ((!strncmp("till", b, 4) && (h + 1) % 24 == 0) || (!strncmp("past", b, 4) && h == 0)) {
			sprintf_s(c, 10, "midnight ");
		} else if ((!strncmp("till", b, 4) && h + 1 == 12) || (!strncmp("past", b, 4) && h == 12)) {
			sprintf_s(c, 10, "noon ");
		} else {
			sprintf_s(c, 10, "%d %s", h, meridiem);
		}
		
		strcat_s(msg, a);
		strcat_s(msg, b);
		strcat_s(msg, c);
		free(a);
		free(b);
		free(c);
		return msg;
	}

	int missing_value_u(int  data[], size_t size)
	{
		int acc = 0;
		int data_sum = 0;
		
		for (int i = 1; i <= size; i++) {
			acc += i;
			data_sum += data[i - 1];
		}
		return acc - data_sum;
	}

	int missing_value_s(int  data[], size_t size)
	{
		int min = 0, max = 0;
		int data_sum = 0, sum = 0;
		int a = 0, b = size - 1;

		if (size == 0) {
			perror("error: size equal to zero...returning -1");
			fprintf(stderr, "");
			return -1;
		}

		min = data[0];
		max = min;
		/* find min and max of shuffled data*/
		while (a <= b) {
			data_sum += (data[a] != data[b]) ? data[a] + data[b] : data[a];
			if (data[a] < min || data[b] < min)
				min = data[b] < data[a] ? data[b] : data[a];
			if (data[a] > max || data[b] > max)
				max = data[b] > data[a] ? data[b] : data[a];
			a++;
			b--;
		}

		/* calculate sum */
		while (min <= max) {
			sum += (min != max) ? min + max : min;
			min++;
			max--;
		}

		return sum - data_sum;
	}

	unsigned rain_terraces(int heights[], size_t size)
	{
		int h = 0;
		int max_height;
		int e[2];
		unsigned units_of_water = 0, units = 0;


		for (int i = 1; i < size; i++) {
			if (heights[i] != heights[i - 1]) {
				/* store discontinuity */
				e[0] = heights[i - 1];
				e[1] = heights[i];

				/* store height (marker) */
				if (e[0] > e[1] && !h) {
					h = e[0];
				}
			}
		
			if (!!h) {
				/*accumulate units - pool of rain */
				units += (h > e[1]) ? h - e[1] : units;
				/* reset h */
				if (e[1] >= h) {
					units_of_water += units;
					h = 0;
					units = 0;
				}
			}

		}

		return units_of_water;
	}

	unsigned int last_digit_A_to_B(unsigned base, unsigned exp)
	{
		unsigned val = base % 10;
		unsigned *data = (unsigned*) malloc(4 *sizeof(unsigned));
		unsigned result = 0; 

		for (int i = 0; i < 3; i++) {
			data[i] = ((unsigned) std::pow(val, i + 1)) % 10;
		}
		result = data[exp % 4];
		free(data);
		return result;
	}


	bool matrix_search(int image_one[matrix_rows][matrix_cols], int image_two[test_matrix_rows][test_matrix_cols])
	{
		unsigned valid_count = 0;
		for (int c = 0; c < matrix_cols - (test_matrix_rows - 1); c++) {
			for (int r = 0; r < matrix_rows - (test_matrix_cols - 1); r++) {
				valid_count = 0;
				for (int x = 0, y = 0, count = 0; (count < test_matrix_rows * test_matrix_cols); count++) {
					x = count % test_matrix_cols;
					y += (!!x && !(x % test_matrix_rows));
					valid_count += +(image_one[r + y][c + x] == image_two[y][x]);
				}
				if (valid_count == test_matrix_cols * test_matrix_rows) {
					printf("image two found  @ [%d][%d]\n", valid_count,r,c);
					return  true;
				}
			}
		}
		return  false;
	}

	unsigned int max_subarray_sums(int numerical_array[], size_t size)
	{
		int max_sum = 0;
		int curr_sum = 0;
		unsigned curr_step = 0;
		unsigned max_steps = 0;

		for (int i = 0; i < size; i++) {
			curr_sum += numerical_array[i];
			curr_step++;

			if (curr_sum > max_sum) {
				max_sum = curr_sum;
				max_steps = curr_step;
			}
			/* use cond. (curr_step < max_steps ) to track most efficient subarray block*/
			if (numerical_array[i] >= max_sum && curr_sum < numerical_array[i]) {
				curr_step = 1;
				curr_sum = numerical_array[i];
			}
		}
		return max_steps;
	}


}
