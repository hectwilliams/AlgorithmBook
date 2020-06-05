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


#endif 

