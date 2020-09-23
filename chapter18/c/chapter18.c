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
  const int  NUM = 20;
  static char str[NUM] = "";
  int pos = 2;
  int val = 0;

  memset(str, 0, NUM);
  memcpy(str, "0b", 2);

  while (num > 0)
  {
    val = num % BINARY;
    str[pos++] = 48 + val;
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

int main()
{
  printf( "data %d\n", binStr2Val("11111"));
  //  printf( "[%s]\n", dec2HexStr(31) );
  // printf( "[%d]\n", hexStr2Val("1F") );
}
