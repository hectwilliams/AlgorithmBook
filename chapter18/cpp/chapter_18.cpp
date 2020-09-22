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

int main ()
{
  std::cout << hexStr2Val( "1F") << '\n';
}