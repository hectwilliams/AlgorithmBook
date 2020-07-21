#include <iostream>
#include "chapter10.h"

std::string rotateString(std::string str, unsigned n)
{
  std::string tmp = str;
  str.clear();
  unsigned pivot = tmp.size() - n;

  for (int i = pivot; i < tmp.size(); i++)
  {
    str += tmp[i];
  }

  for (int i = 0; i < pivot; i++)
  {
    str += tmp[i];
  }
  return str;
}

void rotateString_test()
{
  std::string s = "Boris Godunov";
  std::cout << rotateString(s, 5) << '\n';
}

bool ionis_rotate(std::string str1, std::string str2)
{
  if (str1.length() != str2.length())
  {
    return false;
  }

  for (int i = 0; i < str1.size(); i++)
  {
    if (str2.compare( rotateString(str1, i) ) == 0)
    {
      return true;
    }
  }

  return false;
}

void ionis_rotate_test()
{
  std::cout <<    ionis_rotate("abcd", "cbcd") << '\n'; //  false
  std::cout <<    ionis_rotate("abcd", "dabc") << '\n'; // true
}

int main()
{
  ionis_rotate_test();
}