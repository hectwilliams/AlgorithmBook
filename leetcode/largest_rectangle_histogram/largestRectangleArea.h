#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <assert.h> // Required header

#define NODE_LIST_SIZE 100
// 
int largestRectangleArea(int* heights, int heightsSize);
int test_conv_str(long value);
int test_digit_found(char *s, char *endptr);