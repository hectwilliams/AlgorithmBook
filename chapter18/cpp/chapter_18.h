#include <iostream>
#include <string>
#include <array>

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

std::string dec2OctStr(int value);
int octStr2Val(std::string str);

std::string dec2HexStr(int value);
int hexStr2Val(std::string str);



int HexDecode(char c)
{
  int num;
  switch (c)
  {
    case 'F':
      num = 15;
      break;
    case 'E':
      num = 14;
      break;
    case 'D':
      num = 13;
      break;
    case 'C':
      num = 12;
      break;
    case 'B':
      num = 11;
      break;
    case 'A':
      num = 10;
      break;
    case '9':
      num = 9;
      break;
    case '8':
      num = 8;
      break;
    case '7':
      num = 7;
      break;
    case '6':
      num = 6;
      break;
    case '5':
      num = 5;
      break;
    case '4':
      num = 4;
      break;
    case '3':
      num = 3;
      break;
    case '2':
      num = 2;
      break;
    case '1':
      num = 1;
      break;
    case '0':
      num = 0;
      break;
    default:
      num = -1;
  }
  return num;
}
char HexEncoder (unsigned num)
{
  char res;

  switch (num)
  {
    case 10:
      res = 65;
      break;
    case 11:
      res = 66;
      break;
    case 12:
      res = 67;
      break;
    case 13:
      res = 68;
      break;
    case 14:
      res = 69;
      break;
    case 15:
      res = 70;
      break;
    default:
      if (num > 15 )
      {
        res =  0;
      }
      else
      {
        res = 48 + num;
      }
      break;
  }
  return res;
}

std::string dec2HexStr(int value);
int hexStr2Val(std::string str);
std::string dec2BinStr (int value);
int binStr2Val (std::string str);
void countInBinary (unsigned value);
unsigned countSetBits(unsigned value);
unsigned reversebits(unsigned value);
unsigned encode32( unsigned char arr[4]);
std::array<unsigned char, 4> decode32(int value);
int encodeBit(int bit, int bitNumber, int value);
int decodeBit (int bitNumber, int value);

int LED2Numeral(unsigned char ledByte);
