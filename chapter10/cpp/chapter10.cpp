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

bool ionisRotate(std::string str1, std::string str2)
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

void ionisRotate_test()
{
  std::cout << ionisRotate("abcd", "cbcd") << '\n'; //  false
  std::cout << ionisRotate("abcd", "dabc") << '\n'; // true
}

void badCharacters(std::string &str, std::string bad)
{
  std::size_t index ;

  for (char c: bad)
  {
    index = str.find(c);
    if (index != std::string::npos)
    {
      str.erase(index, 1);
    }
  }
}

void badCharacters_test()
{
  std::string str = "abcdef";
  badCharacters(str, "ac");
  std::cout << str << '\n';
}

void censor(std::string &str, std::vector<std::string> naughty_list)
{
  int pos;
  std::string insertion_data;

  for (std::string &word: naughty_list)
  {

    pos = str.find(word);
    if (pos != std::string::npos)
    {
      insertion_data.clear();
      for (int i = 0; i < word.size(); i++)
      {
        insertion_data += 'x';

      }
      str.replace( pos, word.size() , insertion_data);
    }
  }
}

void censor_test()
{
  std::string data = "hector_williams_abc_def";
  std::vector<std::string> list;
  list.push_back( "abc");
  list.push_back( "ee");
  list.push_back( "def");
  censor (data, list);
  std::cout << data << '\n';
}

int main()
{
  censor_test();
}