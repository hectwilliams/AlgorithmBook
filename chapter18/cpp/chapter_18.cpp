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

int main ()
{
  std::cout << octStr2Val("37") << '\n';
}