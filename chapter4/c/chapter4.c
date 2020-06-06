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



int main(void) {
  char data[100] = ""; 
  integer_to_roman_numerals(2, data);
  puts(data);
}