#include <stdio.h>
#include "chapter10.h"
#include <stdlib.h>
#include <string.h>

uint32_t string_len (const char * string)
{
  uint32_t count = 0;
  char *ptr = string;
  while (*ptr++)
  {
    count++;
  }
  return count;
}


char * rotate_string(char *string, unsigned n)
{
  char *ptr = string;
  uint32_t len = string_len(string);
  static char *buffer = NULL;

  if (buffer != NULL)
  {
    free(buffer);
  }

  buffer = (char *) malloc(len);
  memcpy(buffer, string + len - n, n );
  memcpy(buffer + n, string, len - n );
  printf("buffer %s\n", buffer);
  return buffer;
}


void rotate_string_test ()
{
  char msg[40] = "Boris Godunov";
  char *data = rotate_string(msg, 5); // dunovBoris Go
    printf("rotated string %s\n", data);

}

boolean ionis_rotate(char* str1, char * str2)
{
  uint32_t strlen_1 = string_len(str1);
  uint32_t strlen_2 = string_len(str2);

  if (strlen_1 != strlen_2)
  {
    return False;
  }

  for (int i = 0; i < strlen_1; i++)
  {
    if ( strcmp(str1, rotate_string(str2, i)) == 0)
    {
      return True;
    }
  }
  return False;
}

void ionis_rotate_test ()
{
  ionis_rotate("abcd", "cbcd"); /*false */
  ionis_rotate("abcd", "dabc"); /*true */

}

int main()
{
  ionis_rotate_test();
}