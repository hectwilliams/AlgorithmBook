#ifndef CHAPTER_4_C
#define CHAPTER_4_C

typedef struct Books {
  char author[50];  
  char name[50];
  int number;
} Books;

char *remove_blanks(const char *data);
char *get_digits(const char *data);


#endif 

