#include <stdio.h>
#include <string.h>
#include "chapter4.h"

 char * remove_blanks(const char * data)
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


char * get_digits(const char * data)
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

int main(void) {
  puts(get_digits("He22ctor Williams"));
}