#ifndef CHAPTER_4_C
#define CHAPTER_4_C

typedef struct Books {
  char author[50];  
  char name[50];
  int number;
} Books;

char *remove_blanks( char *data);
char *get_digits( char *data);
char *acronyms ( char * data);
char *remove_shorter_strings( char *data, size_t length);
void remove_even_length_strings( char ** collection, const size_t size);  // [size][data0][data1]
int integer_to_roman_double_inject (unsigned int* number, unsigned int threshold, char * string, const char *character);
void  integer_to_roman_numerals(unsigned int number, char * output);
unsigned int roman_numeral_to_integer (char * roman_numeral);
typedef enum boolean {False, True} boolean;
boolean paren_valid (char * str);
boolean is_palindrome(char *str);

void longest_palindrome( char * str, char * output);


#endif 

 