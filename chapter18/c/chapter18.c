#include "chapter18.h"
#include <string.h>
#include <math.h>

int unsigned_pow(unsigned val, unsigned exponent)
{
  int res = 1;
  for (int i = 0; i < exponent; i++)
  {
    res *= val;
  }
  return res;
}

char * dec2OctStr(int num)
{
  static char str[10] = "";
  int pos = 2;
  int curr = 0;

  memset(str, 0, 10);

  memcpy(str, "0o", 2);

  while (num > 0)
  {
    if (num >= OCTAL)
    {
      curr = num / OCTAL;
      num -= curr * 8  ;
    }
    else
    {
      curr = num;
      num = 0;
    }
    str[pos++] = (48 + curr );
  }
  return str;
}

int OctStr2Val(const char * str)
{
  int len = strlen(str);
  int sum = 0;

  while (*str != '\0')
  {
    sum += ((*str++) - 48) * pow(OCTAL, --len);
  }
  return sum;
}

char HexEncode (unsigned num)
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
char * dec2HexStr(int num)
{
  static char str[10] = "";
  int pos = 2;
  int curr = 0;

  memset(str, 0, 10);
  memcpy(str, "0x", 2);
  while (num > 0)
  {
    if (num >= HEXADECIMAL)
    {
      curr = num / HEXADECIMAL;
      num -= curr * HEXADECIMAL  ;
    }
    else
    {
      curr = num;
      num = 0;
    }
    str[pos++] = HexEncode(curr);
  }
  return str;
}

int hexStr2Val(const char *str)
{
 int len = strlen(str);
 int sum = 0;
  while (*str != '\0')
  {
    sum += HexDecode(*str++) * (int) pow(HEXADECIMAL, --len);
  }
  return sum;
}

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
char * dec2BinStr (int num)
{
  const int  SPACE = 50;
  static char str[SPACE] = "";
  int pos = 2 + floor( log2(num) );
  int val = 0;

  memset(str, 0, SPACE);
  memcpy(str, "0b", 2);

  while (num > 0)
  {
    val = num % BINARY;
    str[pos--] = 48 + val;
    num /= 2;
  }
  return str;
}

int binStr2Val (const char * str)
{
  int sum = 0;
  int len = strlen(str);

  for (int i = 0; i < len; i++)
  {
    sum += (str[len - 1- i]  - 48) * (int) pow(BINARY, i);
  }
  return sum;
}

void countInBinary (unsigned numOfBits)
{
  int count = 0;
  while (count < pow(2, numOfBits) )
  {
    printf( " %d  -> number[ %s]\n ", count,  dec2BinStr(count) );
    count++;
  }
}

unsigned countSetBits(unsigned value)
{
  unsigned acc = 0;
  while (value > 0)
  {
    acc += value % 2;
    value /= 2;
  }
  return acc;
}

unsigned reverse32Bit(unsigned value)
{
  int leftBit = 0;
  int rightBit = 0;

  for (int i = 0; i < WORD_SIZE /2 ; i++)
  {
    leftBit = !!(value & (1 << WORD_SIZE - 1 - i));
    rightBit = !!(value & (1 << i));
    value = value & ~(1 << WORD_SIZE - 1 - i) & ~( 1 << i);
    value =  value | (leftBit << i) | (rightBit << WORD_SIZE - 1 -i);
  }
  return value;
}

unsigned encode32( unsigned char arr[4])
{
  unsigned sum = 0;
  for (int i = 0 ; i < 4; i++)
  {
    sum |= ( arr[i] ) << (4 - 1 - i)*8;
  }
  return sum;
}

struct byte4 decode32 (int value)
{
  struct byte4 res = {.offset0 = 0, .offset1 = 0, .offset2 = 0, .offset3 = 0};
  unsigned char mask = 0xFF;

  for (int i = 0; i < 4; i++)
  {
    switch (i)
    {
    case 0:
      res.offset0 = (value & ( mask << 8*i )) >> 8*i;
      break;
    case 1:
      res.offset1 =  (value & ( mask << 8*i )) >> 8*i;
      break;
    case 2:
      res.offset2 =  (value & ( mask << 8*i )) >> 8*i;
      break;
    case 3:
      res.offset3 = (value & ( mask << 8*i )) >> 8*i;
      break;
    default:
      break;
    }
  }
  return res;
}

int encodeBit (int bit, int bitNumber, int value)
{
  if (bitNumber < 32)
  {
    value &= ~(1 << bitNumber);
    value |= (bit << bitNumber);
  }
  return value;
}

int decodeBit (int bitNumber, int value)
{
  int bit = -1;

  if (bitNumber < 32)
  {
    bit = !!(value &  (1 << bitNumber));
  }
  return bit;
}

int LED2Numeral(unsigned char ledByte)
{
  int res = -1;
  switch (ledByte)
  {
  case LED_0:
    res = 0;
    break;
  case LED_1:
    res = 1;
    break;
  case LED_2:
    res = 2;
    break;
  case LED_3:
    res = 3;
    break;
  case LED_4:
    res = 4;
    break;
  case LED_5:
    res = 5;
    break;
  case LED_6:
    res = 6;
    break;
  case LED_7:
    res = 7;
    break;
  case LED_8:
    res = 8;
    break;
  case LED_9:
    res = 9;
    break;
  default:
    res = -1;
  }
  return res;
}


int main()
{
  for (int i = 0; i <)
  int x = LED2Numeral(0x7F);
  printf( " %x " ,  x ) ;
  // unsigned x = reverse32Bit(0b01100110011001101111000011110000);
  // printf("[%d]\n", x == 0b00001111000011110110011001100110);
}