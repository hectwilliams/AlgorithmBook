#include <iostream>
#include "chapter10.h"
#include <math.h>
#include <locale>
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
  optimumDisplay(result);
}

 std::string DedupeStr(const std::string &str)
{
  if (str.size() <= 0)
  {
    return  "";
  }

  if (str.find_last_of( str[0]) != 0)
  {
    return DedupeStr ( str.substr(1) );
  }
  else
  {
    return str[0] + DedupeStr ( str.substr(1) );
  }
}

std::string DedupeTest()
{
  std::cout << DedupeStr("Snaps! crackles! pops!") << '\n';
}

int firstUniqueLetter (const std::string & str, int index)
{
  if (index >= str.size())
  {
    return -1;
  }

  if ( std::count(str.begin(), str.end(), str[index] )  == 1)
  {
    return index;
  }

  return firstUniqueLetter(str, index + 1);
}

void firstUniqueLetterTest()
{
  std::string msg = "empathetic monarch meets primo stinker";

  std::cout <<  firstUniqueLetter(msg) << '\n';
}

std::string uniqueLetters (const std::string &str, int index)
{
  if (index >= str.size())
  {
    return "";
  }

  if (std::count(str.begin(), str.end(), str[index]) == 1)
  {
    return str[index] + uniqueLetters(str, index + 1);
  }
  else
  {
    return uniqueLetters(str, index + 1);
  }
}
void uniqueLetters_test ()
{
  std::string msg = "Snap! Crackle! Poop!";
  std::cout << uniqueLetters(msg) << '\n';
}

std::string numToString(double num, int n)
{
  long int numberInt =  static_cast< long int>(num) ;
  int digit = numberInt % 10;
  char c =  (char) (48 + digit);
  std::string a,b;

  if (n == 0)
  {
    a = c + numToString(num / 10, n + 1);
    b = numToString(num * 10.0, n - 1);
    return a + "." + b;
  }

  if (n > 0 )
  {
    if (numberInt > 0)
    {
      return c + numToString(num / 10, n + 1);
    }
    return "";
  }

  if (n < 0)
  {
    if (digit > 0 || !numToStringZeros(num))  /* function checks last digit in fractional value */
    {
      return c + numToString(num * 10.0, n - 1);
    }
    return "";
  }
}

bool numToStringZeros(double num, int size)
{
  for (int i = 0; i < size; i++)
  {
    num *= pow(10, i);
    if ( static_cast<long int>(num) % 10 != 0 )
    {
      return false;
    }
  }
  return true;
}

std::string numToText(double number)
{
  std::string base = numToString(number);
  std::string whole, dec;
  std::size_t pos = base.find('.') ;

  if (pos != std::string::npos)
  {
    dec = base.substr( pos + 1);
    whole = base.substr( 0, pos );
  }
  else
  {
    whole = base;
  }

  return numToTextParserWhole(whole) + numToTextParserDecimal(dec);
}

std::string numToTextParserDecimal( std::string data, int index)
{
  if (data.size() >= index)
  {
    return "";
  }
  return (index == 0 ? "point " : "") + digitToText( static_cast<int>(48 - data[index]), true);
}

std::string numToTextParserWhole( std::string data , int level)
{
  std::string buffer = "xxx";
  std::string text = "";

  for (int i = 0; i < 3 ; i++)
  {
    if ( data[i] >= 48 && data[i] < 58)
    {
      buffer[3 - 1 - i] = data[i];
    }
  }

  text = numToTextTranslate(buffer, level);

  if (data.size() >= 3)
  {
    return numToTextParserWhole(data.substr(3), level + 1)  + text;
  }

  return text;
}

std::string numToTextTranslate(std::string data, unsigned level)
{
  std::string buffer;
  int digit;
  char c;

  if (data[0] != 'x')
  {
    digit = data[0] - 48;
    switch(digit)
    {
      case 1:
        buffer += "One Hundred ";
        break;
      case 2:
        buffer += "Two Hundred ";
        break;
      case 3:
        buffer += "Three Hundred ";
      case 4:
        buffer += "Four Hundred ";
        break;
      case 5:
        buffer += "Five Hundred ";
        break;
      case 6:
        buffer += "Six Hundred ";
        break;
      case 7:
        buffer += "Seven Hundred ";
        break;
      case 8:
        buffer += "Eight Hundred ";
        break;
      case 9:
        buffer+= "Nine Hundred ";
        break;
    }
  }

  if (data[1] != 'x')
  {
    digit = data[1] - 48;

    switch(digit)
    {
      case 1:
        /* NO OP*/
        break;

      case 2:
        buffer += "Twenty ";
        break;

      case 3:
        buffer += "Thirty ";
        break;

      case 4:
        buffer += "Fourty ";
        break;

      case 5:
        buffer += "Fifty ";
        break;

      case 6:
        buffer += "Sixty ";
        break;

      case 7:
        buffer += "Seventy ";

      case 8:
        buffer += "Eighty ";

      case 9:
        buffer += "Ninety ";
    }

    if (data[2] != 'x')
    {
      digit = data[2] - 48;

      if (data[1] == '1')
      {
        /* n-TEENS */
        switch(digit)
        {
           case 0:
            buffer += "Ten ";
            break;
          case 1:
            buffer += "Eleven ";
            break;
          case 2:
            buffer += "Twelve ";
            break;
          case 3:
            buffer += "Thirteen ";
            break;
          case 4:
            buffer += "Fourteen ";
            break;
          case 5:
            buffer += "Fifteen ";
            break;
          case 6:
            buffer += "Sixteen ";
            break;
          case 7:
            buffer += "Seventeen ";
            break;
          case 8:
            buffer += "Eighteen ";
            break;
          case 9:
            buffer += "Nineteen ";
            break;
        }
      }
      else
      {
        buffer += digitToText(digit);
      }
    }

  }

  switch (level)
  {
    case 1:
      buffer+= "Thousand ";
      break;
    case 2:
      buffer += "Million ";
      break;
    case 3:
      buffer += "Billion ";
      break;
    case 4:
      buffer += "Trillion ";
      break;
    case 5:
      buffer += "Quadrillion ";
      break;
    case 6:
      buffer += "Quintillion ";
      break;

    default:
      break;
  }

  return buffer;

}

std::string digitToText(int digit,
 bool en_zero)
{
  std::string result;
  switch(digit)
  {
    case 0:
      if (en_zero)
      {
        result = "zero ";
      }
      break;
    case 1:
      result = "one ";
      break;

    case 2:
      result = "two ";
      break;

    case 3:
      result = "three ";
      break;

    case 4:
      result = "four ";
      break;

    case 5:
      result = "five ";
      break;

    case 6:
      result = "six ";
      break;

    case 7:
      result = "seven" ;
      break;

    case 8:
      result = "eight ";
      break;

    case 9:
      result = "nine ";
      break;
  }

  return result;

}

void numToTextTest()
{
  std::string test = numToText(40213.23);
  std::cout << test << '\n';
}

bool isPermtutaoin(std::string str,const std::string &perm, std::string &&buffer)
{
  bool state;

  if (buffer.size() == perm.size())
  {
    if (buffer.compare(perm) == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }


  for (int i = 0; i < str.size() && !state; i++)
  {
    state = isPermtutaoin( str.substr(0, i) + str.substr(i + 1), perm, buffer + str[i]);
  }

  return state;
}

void isPermutaoinTest()
{
  bool state = false;
  std::cout <<  isPermtutaoin("mister", "stimer") << '\n';
}

bool isPangram (std::string str)
{
  return 26 == isPangram_helper(str);
}

int isPangram_helper(std::string str, std::map<char, bool> mapper )
{
  int count = 0;
  char c;
  int bit = 0;

  if (str.size() == 0)
  {
    return 0;
  }

  c = std::tolower(str[0]);

  if (mapper.count(c) == 0 && std::isalpha(c))
  {
    mapper.insert( std::make_pair(c, 1) );
    bit = 1;
  }
  count = bit + isPangram_helper(str.substr(1), mapper);

  return count;
}

void isPangramTest()
{
  const char *msg = "How quickly daft jumping zebras vex!"; // true
  std::cout << isPangram(msg) << '\n';
  const char *msg2 = "abcdef ghijkl mno pqrs tuv wxy, not so fast!"; // false
  std::cout << isPangram(msg2) << '\n';

}

int main()
{
  isPangramTest();
}