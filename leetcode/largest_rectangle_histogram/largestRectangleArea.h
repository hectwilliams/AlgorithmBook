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

static const int test_vector_7[] = {3,6,5,7,4,8,1,0};
static const int test_vector_7_len = sizeof(test_vector_7)/ sizeof(int);

static const int test_vector_8[] = {5,5,1,7,1,1,5,2,7,6};
static const int test_vector_8_len = sizeof(test_vector_8)/ sizeof(int);

static const int test_vector_9[] = {2,1,2};
static const int test_vector_9_len = sizeof(test_vector_9)/ sizeof(int);

static const int test_vector_10[] = {0};
static const int test_vector_10_len = sizeof(test_vector_10)/ sizeof(int);


static const int test_vector_11[] = {4,2,3};
static const int test_vector_11_len = sizeof(test_vector_11)/ sizeof(int);

static const int test_vector_12[] = {3,5,5,2,5,5,6,6,4,4,1,1,2,5,5,6,6,4,1,3};
static const int test_vector_12_len = sizeof(test_vector_12)/ sizeof(int);


static const int test_vector_13[] = {999, 999, 999, 999};
static const int test_vector_13_len = sizeof(test_vector_13)/ sizeof(int);


static const int test_vector_14[] = {1, 1};
static const int test_vector_14_len = sizeof(test_vector_14)/ sizeof(int);

static const int test_vector_15[] = {6,4,2,0,3,2,0,3,1,4,5,3,2,7,5,3,0,1,2,1,3,4,6,8,1,3};
static const int test_vector_15_len = sizeof(test_vector_15)/ sizeof(int);

static const int test_vector_16[] = {9,8,4,9,2,6,9,0,5,4,9,5,3,8,2,9};
static const int test_vector_16_len = sizeof(test_vector_16)/ sizeof(int);

static const int test_vector_17[] =  {1,1,6,4,5,1,4,5,1,9,6,5,6,2,7,0,7,7};
static const int test_vector_17_len = sizeof(test_vector_17)/ sizeof(int);

static const int test_vector_18[] =  {0,1,0,2,1,0,1,3,2,1,2,1};
static const int test_vector_18_len = sizeof(test_vector_18)/ sizeof(int);


static const int test_vector_19[] =  {1,9,3,7,3,2,1,3,6,5,9,1,2,7,6,5,9,4};
static const int test_vector_19_len = sizeof(test_vector_19)/ sizeof(int);


int largestRectangleArea(int* heights, int heightsSize);
int test_conv_str(long value);
int test_digit_found(char *s, char *endptr);