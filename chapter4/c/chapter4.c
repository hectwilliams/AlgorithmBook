#include <stdio.h>
#include <string.h>
#include "chapter4.h"
#include <stddef.h>  // size_t
#include <stdlib.h> // malloc


 char * remove_blanks( char * data)
{
  static char result [] = "";
  int i = 0;

  for (char *ptr = data; *ptr != '\0'; ptr++) {
    if (*ptr != 32) {
      memset( (result + i++), *ptr, 1 );
    }
  }
  return result;
};

char * get_digits( char * data)
{
  static char result [] = "";
  char code;
  int i = 0;

  for (char *ptr = data; *ptr != '\0'; ptr++) {
    code = *ptr;
	  if (code >= 48 && code <= 57) {
      memset( (result + i++), code, 1 );
	  }
  }
  return result;
};

char * acronyms ( char * data)
{
  static char result [] = "";
  char code;
  int pluck = 1;
  int i = 0;

  for (char *ptr = data; *ptr != '\0'; ptr++) {
    code = *ptr;

    if (code == 32) {
      pluck = 1;
	  } else if (pluck) {
      if (code >= 97 && code <= 122)
        code = code;
      pluck = 0;
      memset( (result + i++), code, 1 );
	  }

  }

  return result;
};

unsigned int count_non_spaces( char *data)
{
  unsigned count = 0;
  for (char *ptr = data; *ptr != '\0'; ptr++) {
    count += +(*ptr == 32);
  } 
  return count;
}

char * remove_shorter_strings( char *data, size_t length)
{
  static char result[] = "";
  int start = 0; 
  int end = 0;
  int i = 0;
  int pos = 0;
  int code;

  for (char *ptr = data; *ptr != '\0'; ptr++, i++, end = i) {
    code = *ptr;
    if (code == 32) {
      if (length < end - start ) {
        for (char *r = data + start; r < data + end; r++) {
          result[pos++] = *r; 
        }
        result[pos++] = ' ';
      }
	    start = i + 1;
	  }
  }
  
  if (length < end - start) {
    for (char *r = data + start; r < data + end; r++) {
      result[pos++] = *r; 
    }
  }

  return result;
}

char * string_reverse(char *data) 
{
  static char result[] = "";
  unsigned int length = 0;

  for (char *ptr = data; *ptr != '\0'; ptr++) {
    length++;
  }
  
  for (int i = 0; i < length; i++) {
    memset(result + i, *(data + length - 1 - i), 1);
  }

  return result;

}

void remove_even_length_strings(char ** collection, const size_t size)
{

  int curr_length = 0;

  for (int i = 0; i < size; i++) {
    curr_length = 0;	  
    
    for (char *ptr = *(collection + i); *ptr != '\0'; ptr++) 
      curr_length++;
	
	  if (curr_length % 2 == 1)
	    *(collection + i) = "";
  }
}

/* Integer to Roman Numerals */

int integer_to_roman_double_trouble (unsigned int* number, unsigned int threshold, char * string, const char *character)
{
  unsigned int roman_list[7] = {1, 5, 10, 50, 100, 500, 1000}; 
  const char * roman_chars[7] = {"I", "V", "X", "L", "C", "D", "M"};
  unsigned int roman_value;

  for (int i = 0; i < 7; i++) {
    roman_value = roman_list[i];
    
    if (roman_value >= threshold)
      break;

    if ((threshold - roman_value)  <= *number) {
      strcat(string, roman_chars[i]);  	  
      strcat(string, character);
      *number = *number - (threshold - roman_value);
      return 1;	  
    }

  }

  return 0;

}

void  integer_to_roman_numerals(unsigned int number, char * output)
{
	
  enum romans {I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000};

  while (number > 0) {
    if (number >= M) {
      strcat(output, "M");
      number -= M;
    } 
    
    else if(number >= D) {
      if (integer_to_roman_double_trouble(&number, M, output, "M") == 0) {
	      strcat(output, "D");
        number -= D;
      }
    }

    else if(number >= C) {
      if (integer_to_roman_double_trouble(&number, D, output, "D") == 0) {
	      strcat(output, "C");
	      number -= C;
      }
    }

    else if(number >= L) {
      if (integer_to_roman_double_trouble(&number, C, output, "C") == 0) {
        strcat(output, "L");
        number -= L;
      }
    }

    else if(number >= X) {
      if (integer_to_roman_double_trouble(&number, L, output, "L") == 0 ) {
	      number -= X;
        strcat(output, "X");
      } 
    }
	
    else if(number >= V) {
      if (integer_to_roman_double_trouble(&number, X, output, "X") == 0) {
        number -= V;
        strcat(output, "V");
      }
    }

    else if(number >= I) {      
      if (integer_to_roman_double_trouble(&number, V, output, "V") == 0) {
        number -= I;
        strcat(output, "I");
      }
    }

  }

}

boolean paren_valid (char * str) 
{
  unsigned long counter = 0;
  int bit = -1;

  for (char *ptr = str; *ptr != '\0'; ptr++) {
    if (*ptr == '(') {
      counter++; 	  	
    } 

    if (*ptr == ')') {
      if (counter == 0) {
        return False; 
      } else {
        --counter;	  
      }
    }
  }  
  return (True ? counter == 0: False);
}

boolean braces_valid(char * str) {
  unsigned int counters[3] = {0, 0, 0};  // open, curly, square	
  int code;

  for (char *ptr = str; *ptr != '\0'; ptr++) {
    code = *ptr;

    counters[0] += +(code == 40);  // open 
    counters[1] += +(code == 123); // curly 
    counters[2] += +(code == 91);  // square 
	
    if (code == 41) {
      if (counters[0] == 0)
        return False;
      else 
        counters[0]--;
    }

    if (code == 125) {
      if (counters[1] == 0)
        return False;
      else 
        counters[1]--;
    }

    if (code == 93) {
      if (counters[2] == 0)
        return False;
      else 
      counters[2]--;
    }

  }

  for (int i = 0; i < 3; i++) {
    if (counters[i] > 0) 
      return False;	  
  }

  return True;

}

boolean is_palindrome(char *str) 
{

  unsigned int count = 0;

  for (char *ptr = str; *ptr != '\0'; ptr++) 
    count++;      

  for (int i = 0; i <= count; i++) {
    if (str[count - i - 1] != str[i])
      return False; 
  }

  return True; 
}

void longest_palindrome( char * str, char * output) {
  char *ptr = str; 
  int len_palindrome = 0;
  char test_string[100];
  int bytes = 0;

  while (*ptr != '\0') {
    for (char *end_char = ptr; *end_char != '\0'; end_char++) {
      bytes++;
      if ((bytes > len_palindrome) && (*ptr == *end_char)) {  
        memcpy(test_string, ptr, bytes);
        if (is_palindrome(test_string)) {
          len_palindrome = bytes;
          strcpy(output, test_string);
        }
      }
    }
    bytes = 0;
    ptr++;
  } 
}

boolean is_word_alphabetical(char * str)
{
  for (char *ptr = str + 1; *ptr != '\0'; ptr++) {
    if ( *(ptr - 1) > (*ptr))
      return False;    
  }
  return True;
}

void d_get_jiggy(char *name, char *output)
{
  char lastChar = *name;
  
  strcpy(output, name + 1);
  strcat(output, " to the ");
  
  if (lastChar >= 97 && lastChar <= 122) 
    lastChar -= 32;

  if (*output >= 97 && *output <= 122) 
    *output -= 32;

  strncat(output, &lastChar , 1);
}

void common_suffix(char * collection[], const size_t size, char * output) {
  char *word; 
  unsigned int lengths[size];
  int counter = 0;
  char c; 
  int pos = 0;
  int curr_index = 0;

  for (int i = 0; i < size; i++) {
    counter = 0;
    for (char *ptr = *(collection + i); *ptr != '\0'; ptr++) 
      counter++;    
    lengths[i] = counter;
  }
  

  while (output)  {
    c = '\0';
    for (int i = 0; i < size; i++) {
      word = collection[i];
      
      if (lengths[i] == 0)
        return;
      
      curr_index = lengths[i] - 1 - pos;
      
      if (c == '\0')
        c = word[curr_index];
      
      if (c != word[curr_index])
        return;
    }

    memset(output + pos++, c, 1);
    memset(output + pos, '\0',1);  // stop flag for string
  }
  
}

void book_index (int pages[], const size_t size, char * output)
{
  boolean rdy = True;
  int count = 0;
  char str_start[10];
  char str_end[10];
  char buffer[10];
  int index = 0;

  while (index < size) {
    
    if (count++ == 0) {
      sprintf(str_start, "%d", pages[index]);
    } 

    if ( (pages[index] + 1 != pages[index + 1]) || (index == size - 1) ) {
      sprintf(str_end, "%d", pages[index]);
      count = 0; 

      if (strcmp(str_end, str_start) == 0) {
        strcat(output, str_end);
      } else {
        sprintf(buffer, "%s-%s", str_start, str_end);
        strcat(output, buffer);  
      }

      if (index < size - 1) {
        strcat(output, ", ");  
      }
    }

    index++;
    
  }

}

void coin_change_with_object (unsigned int number, char *output) {
  enum coins {penny = 1, nickel = 5, dime = 10, quarter = 25};

  while (number > 0) {
    if (number >= quarter) {
      number -= quarter;
      strcat(output, "25\n");
    } else if (number >= dime) {
      number -= dime;
      strcat(output, "10\n");
    } else if (number >= nickel) {
      number -= nickel;
      strcat(output, "5\n");
    } else if (number >= penny) {
      number -= penny;
      strcat(output, "1\n");
    }
  }

}

void max_min_avg (int list[], size_t size) {
  int count = 0;
  int val; 
  max_min_avg_t obj;

  for (int i = 0; i < size; i++) {
    val = list[i];
    
    if (i == 0) {
      obj.min = val;
      obj.max = val;
    } 

    if (val < obj.min)
      obj.min = val;

    if (val > obj.max)
      obj.max = val; 

    obj.avg += val;
  }  

  obj.avg /= size;

}









int main(void) {
  char buffer[50] = "";
  int list[] = {1, 2};
  max_min_avg( list, 2);
  puts(buffer);
}