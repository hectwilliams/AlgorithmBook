#include <stdio.h>
#include <string.h>
#include "chapter4.h"

int main(void) {
  Books book;
  book.number = 22;
	
  strcpy( book.name, "Hunger Games");
  strcpy(book.author, "N/A");
	
  printf(" \t %s  \t %s", book.name, book.author);
}