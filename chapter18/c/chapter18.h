#include <stdlib.h>
#include <stdio.h>

#define OCTAL 8
#define HEXADECIMAL 16
#define BINARY 2
#define WORD_SIZE 32
#define LED_0 0b01110111
#define LED_1 0b00100100
#define LED_2 0b01011101
#define LED_3 0b01101101
#define LED_4 0b00101110
#define LED_5 0b01101011
#define LED_6 0b01111011
#define LED_7 0b00100101
#define LED_8 0b01111111
#define LED_9 0b00101111



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

struct byte4
{
  unsigned char offset0;
  unsigned char offset1;
  unsigned char offset2;
  unsigned char offset3;
};

struct byte4 decode32 (int value);
int encodeBit (int bit, int bitNumber, int value);
int decodeBit (int bitNumber, int value);
int LED2Numeral(unsigned char ledByte);