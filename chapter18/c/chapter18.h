#include <stdlib.h>
#include <stdio.h>

#define OCTAL 8
#define HEXADECIMAL 16

char* dec2OctStr(int num);
int OctStr2Val(const char * str);
char HexEncode (unsigned num);
int HexDecode(char c);
char * dec2HexStr(int num);
int hexStr2Val(const char *str);