#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <assert.h> // Required header

#define NODE_LIST_SIZE 100

// extern const int test_vector [];
static const int test_vector_1[7] = {2,1,5,6,6,2,3};
static const int test_vector_1_len = sizeof(test_vector_1)/ sizeof(int);

static const int test_vector_2[] = {9, 0};
static const int test_vector_2_len = sizeof(test_vector_2)/ sizeof(int);

static const int test_vector_3[] = {2, 1, 2};
static const int test_vector_3_len = sizeof(test_vector_3)/ sizeof(int);

static const int test_vector_4[] = {5, 4, 1, 2};
static const int test_vector_4_len = sizeof(test_vector_4)/ sizeof(int);


static const int test_vector_5[] = {2, 3};
static const int test_vector_5_len = sizeof(test_vector_5)/ sizeof(int);

static const int test_vector_6[] = {4,2,0,3,2,4,3,4};
static const int test_vector_6_len = sizeof(test_vector_6)/ sizeof(int);




int largestRectangleArea(int* heights, int heightsSize);
int test_conv_str(long value);
int test_digit_found(char *s, char *endptr);