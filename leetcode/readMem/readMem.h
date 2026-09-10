#pragma once

#include <stdio.h>
#include <assert.h>  // Required header
#include <string.h>
#include <stdlib.h> 

#define OFFSET_COUNT 0
#define COUNT_SIZE_BYTES 4

#define OFFSET_NAME 4
#define NAME_SIZE_BYTES 6

#define OFFSET_HEIGHT 12  
#define HEIGHTS_SIZE_BYTES 4

typedef struct table_t {
    int count; // byte id --> 0 - 3 
    char name[NAME_SIZE_BYTES]; // byte id -->  4 - 11 
    int height; // byte id -->  12 - 15 

} table_t; 


#define OFFSET_PACKED_COUNT 0
#define OFFSET_PACKED_NAME 4
#define OFFSET_PACKED_HEIGHT 4+6

typedef struct __attribute__((packed)) 
table_packed_t {
    int count;
    char name[NAME_SIZE_BYTES];
    int height;
}table_packed_t;

void readMem();

void readMemp();
