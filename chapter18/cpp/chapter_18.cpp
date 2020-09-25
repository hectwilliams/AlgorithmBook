#include <math.h>
#include "chapter_18.h"

std::string dec2OctStr(int value)
{
  std::string str;
  while (value > 0)
  {
    str = std::to_string(value % OCTAL) + str;
    value /= OCTAL;
  }
  return "0o" + str;
}

int octStr2Val(std::string str)
{
  int sum = 0;
  for (int i = 0; i < str.size(); i++)
  {
    sum += (str[str.size() - 1 - i] - 48) * pow(OCTAL, i);
  }
  return sum;
}

std::string HexEncoder (std::string str )
{
  if (str == "15")
  {
    return "F";
  }
  else if (str == "14")
  {
    return "E";
  }
  else if (str == "13" )
  {
    return "D";
  }
  else if (str == "12")
  {
    return "C";
  }
  else if (str == "11")
  {
    return "B";
  }
  else if (str == "10")
  {
    return "A";
  }
  else
  {
    return str;
  }
}


std::string dec2HexStr(int value)
{
  std::string str;
  int tmp;

  while (value > 0)
  {
    str = HexEncoder (std::to_string(value % HEXADECIMAL)) + str;
    value /= HEXADECIMAL;
  }
  return "0x" + str;
}

int hexStr2Val(std::string str)
{
  int sum = 0;
  for (int i = 0; i < str.size(); i++)
  {
    sum += HexDecode(str[str.size() - 1 - i]) * pow(HEXADECIMAL, i);
  }
  return sum;
}

std::string dec2BinStr (int value)
{
  std::string str;
  while (value > 0)
  {
    str = std::to_string(value % BINARY ) + str;
    value /= BINARY;
  }
  return "0b" + str;
}

int binStr2Val (std::string str)
{
  int sum  = 0;
  for (int i = 0; i < str.size(); i++)
  {
    sum += (str[str.size() - 1- i]  - 48) * (int) pow(BINARY, i);
  }
  return sum;
}

void countInBinary (unsigned value)
{
  int counter = 0;
  int max = (int) pow(2, value);

  while (counter < max)
  {
    std::cout << counter << " -> " << dec2BinStr(counter++) <<'\n';
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

unsigned reversebits(unsigned value)
{
  int lb, rb;
  for (int i = 0; i < WORD_SIZE/2; i++)
  {
    lb = !!((1 << (WORD_SIZE - 1 - i)) & value) ;
    rb = !!((1 << i) & value) ;

    value &= ~(1 << (WORD_SIZE - 1 - i) ) & ~(1 << i);

    value |= (lb << i);
    value |= (rb << (WORD_SIZE - 1 - i));
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

std::array<unsigned char, 4> decode32(int value)
{
  std::array<unsigned char, 4> res;
  unsigned char mask = 0xFF;

  for (int i = 0; i < 4; i++)
  {
    res[i] = (value & ( mask << 8*i )) >> 8*i;
  }

  for (int i = 0; i < 4; i++)
  {
    std::cout << std::hex <<  i << " " <<  ((int) res[i] ) << '\n';
  }
  return res;
}

int encodeBit(int bit, int bitNumber, int value)
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
    bit = (value &  (1 << bitNumber)) >> bitNumber;
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

int main ()
{
 int x = decodeBit (  30,0x4FFFFFFF ) ;
 printf( " %x " ,  x ) ;
}