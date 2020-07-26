#include <iostream>
#include "chapter10.h"
#include <string_view>

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

bool geneticMarker (const std::string &str, const std::vector<std::string> &collection, unsigned index)
{
  if (index >= collection.size())
  {
    return false;
  }

  if (collection[index].find(str) != std::string ::npos)
  {
    return true;
  }
  else
  {
    return geneticMarker(str, collection, index + 1);
  }
}

void geneticMarkerTest()
{
  std::string data = "abcd";

  std::vector<std::string> list;

  list.push_back("abc?r");
  list.push_back("jeff");
  list.push_back("kiki");
  std::cout << geneticMarker(data, list) << '\n';
}

std::vector<std::string> optimumSequence(std::vector<std::string> collection)
{
  std::vector<std::string> result;
  std::vector<std::string> buffer;

  if (collection.size() == 0)
  {
    return result;
  }

  for (std::string word: collection)
  {
    std::string data = std::string( word.size() , 'x');
    buffer.push_back( data  );
  }
  optimumSSequenceHelper(collection, buffer, result);
  return result;
}

void optimumSSequenceHelper(  std::vector<std::string> collection, std::vector<std::string> buffer, std::vector<std::string> &result,  unsigned col)
{
  std::vector<std::string> clone_collection ;
  std::vector<std::string> clone_buffer;

  if (result.size())
  {
    return;
  }

  if (col == collection[0].size())
  {
    for (auto word: buffer)
    {
      result.push_back(word);
    }
    return;
  }

    /* clone */

  for (int i = 0; i < collection.size(); i++)
  {
    clone_collection.push_back( collection[i] );
  }

  for (int i = 0; i < buffer.size(); i++)
  {
    clone_buffer.push_back( buffer[i] );
  }

  for (int code = 65; code < 91; code++)
  {
    for (int i = 0; i < clone_buffer.size(); i++)
    {
      if (clone_collection[i][col]  != '?')
      {
        clone_buffer[i][col] = clone_collection[i][col];
      }
      else
      {
        clone_buffer[i][col]= (char) code;
      }
    }

    optimumSequenceSortColumn(clone_collection, clone_buffer, col);

    if (optimumSequenceIsSorted(clone_buffer, col) )
    {
      optimumSSequenceHelper(clone_collection, clone_buffer, result, col + 1);
    }

    /* reset mutated clones */
    {
      clone_collection.clear();
      clone_buffer.clear();

      for (int i = 0; i < collection.size(); i++)
      {
        clone_collection.push_back( collection[i] );
      }

      for (int i = 0; i < buffer.size(); i++)
      {
        clone_buffer.push_back( buffer[i] );
      }
    }

  }
}

void optimumDisplay(std::vector<std::string> buffer)
{
    for (int i = 0; i < 3; i++)
    {
      std::cout << buffer[i] << '|';
    }
    std::cout << '\n';
}

bool optimumSequenceIsSorted(std::vector<std::string> collection, unsigned col)
{
  bool result = true;

  for (int i = 0; i < collection.size() - 1; i++ )
  {
    for (int c = 0 ; c < col + 1; c++ )
    {
      result = result &&  (collection[i][c] <= collection[i + 1][c] )  ;
    }
  }
  return result;
}

void optimumSequenceSortColumn(std::vector<std::string> &collection, std::vector<std::string> &buffer, unsigned col)
{
  int pos;
  char min_char;
  int length = buffer.size();

  for (int curr_index = 0; curr_index < length; curr_index++)
  {
    pos = curr_index;
    min_char = buffer[curr_index][col];

    for (int next_index = curr_index + 1 ;  next_index < length; next_index++)
    {
      if ( buffer[next_index][col] < min_char )
      {
        pos = next_index;
        min_char = buffer[next_index][col] ;
      }
    }

    if (pos != curr_index)
    {
      std::swap( buffer[pos] , buffer[curr_index] );
      std::swap(collection[pos], collection[curr_index]);
    }
  }
}

void optimumSequence_test()
{
  std::vector<std::string> data;
   std::vector<std::string> result;
  data.push_back("EA?K");
  data.push_back("?RX?");
  data.push_back("GAG?");
  result = optimumSequence(data);
  optimumDisplay(result)
  ;
}

int main()
{
  optimumSequence_test();
}