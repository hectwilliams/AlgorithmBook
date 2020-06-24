
#ifndef CHAPTER7_H
#define CHAPTER7_H
#include <stdlib.h>
#include <math.h>
#include <stdio.h> 
#include <errno.h>

namespace chapter7 {
	unsigned average(int unsorted_numbers[], const size_t& size);
	bool balance_point(const int numbers[], const size_t &size);
	int balance_index(const int numbers[], const size_t& size);
	int* taco_truck(const int numbers[][2], const size_t size);
	bool binary_search(const int numbers[], const size_t size, int value);
	const char* min_of_sorted_rotated(const char *data[],  size_t size);
	bool str_binary_search(const char* data, const size_t size, const char * character);
	int* remove_duplicates(int array_of_numbers[], int size);
	unsigned mode(int array_of_numbers[], int size);
	void array_buffer_copy( void* dest, size_t dest_size, void* src, size_t src_size, size_t bytes, size_t src_offset_start = 0, size_t dest_offset_start = 0 );
	int smarter_sum(unsigned int num);
	int faster_factorial(unsigned int num);
	int fancy_fib(unsigned int num);
	int trick_trib(unsigned int num);
	double median_sorted_two_arrays(int a[],size_t size_a, int b[],size_t size_b);
	double median_sorted_three_arrays(int a[], size_t size_a, int b[], size_t size_b, int c[], size_t size_c);
	const char* time_in_english(unsigned minutes);
	int missing_value_u(int data[], size_t size);
	int missing_value_s(int data[], size_t size);
	unsigned rain_terraces(int heights[], size_t size);
	unsigned int last_digit_A_to_B(unsigned base, unsigned exp);
	
	#ifndef MATRIX_TEST_DATA
	#define MATRIX_TEXT_DATA 
		#define matrix_cols 4
		#define matrix_rows 4
		#define test_matrix_rows 2
		#define test_matrix_cols 2
	#endif
	bool matrix_search(int image_one[matrix_rows][matrix_cols], int image_two[test_matrix_rows][test_matrix_cols]);
	unsigned int max_subarray_sums(int numerical_array[], size_t size);
}



#endif