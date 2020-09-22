#include "chapter18.h"
#include <string.h>
#include <math.h>

int unsigned_pow(unsigned val, unsigned exponent)
{
  int res = 1;
  for (int i = 0; i < exponent; i++)
  {
    res *= val;
  }
  return res;
}

char * dec2OctStr(int num)
{
  static char str[10] = "";
  int pos = 2;
  int curr = 0;

  memset(str, 0, 10);

  memcpy(str, "0o", 2);

  while (num > 0)
  {
    if (num >= OCTAL)
    {
      curr = num / OCTAL;
      num -= curr * 8  ;
    }
    else
    {
      curr = num;
      num = 0;
    }
    str[pos++] = (48 + curr );
  }
  return str;
}

int OctStr2Val(const char * str)
{
  int len = strlen(str);
  int sum = 0;

  while (*str != '\0')
  {
    sum += ((*str++) - 48) * pow(OCTAL, --len);
  }
  return sum;
}

int main()
{
  // printf( "data %s\n", dec2OctStr(31));
 printf( "[%d]\n", OctStr2Val("37") );
}
