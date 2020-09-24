#include <stdlib.h>
#include <stdio.h>

#define OCTAL 8
#define HEXADECIMAL 16
#define BINARY 2
#define WORD_SIZE 32

char* dec2OctStr(int num);
int OctStr2Val(const char * str);
char HexEncode (unsigned num);
int HexDecode(char c);
char * dec2HexStr(int num);
int hexStr2Val(const char *str);
char * dec2BinStr (int num);
int binStr2Val (const char * str);
void countInBinary (unsigned number);
unsigned countSetBits(unsigned value);
unsigned reverse32Bit(unsigned value);
unsigned encode32( unsigned char arr[4]);
