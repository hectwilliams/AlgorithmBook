#include <stdio.h>
#include <string.h>
#include "chapter4.h"
#include <stddef.h>


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
  int code;
  int i = 0;
  int pos = 0;

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


int main(void) {
  puts( remove_shorter_strings("He22ctor - dw dddd Williams", 4));
}