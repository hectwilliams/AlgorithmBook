#include <stdio.h>
#include "chapter10.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void bad_characters(char * str, char *bad_chars)
{
  char *ptr = str, *runner;
  uint32_t len = string_len(str);
  char *bad_ptr;

  while (*ptr != 0) /* iterate string characters */
  {
    /* chec for bad characters */
    bad_ptr = bad_chars;
    while (*bad_ptr)
    {
      if (*bad_ptr == *ptr)
      {
        /* shift sub-string removing bad character*/
        runner = ptr;
        while (*runner)
        {
          *runner = *(runner + 1);
          runner++;
        }
      }
      bad_ptr++;
    }
    ptr++;
  }
}

void bad_characters_test()
{
  char msg[20] = "abdcef";
  bad_characters(msg, "af");
  printf("result %s\n", msg);
}

void censor_string (char * string, char  ** naughty_list, uint32_t size)
{
  unsigned len = 0, count = 0;
  char *ptr;
  char *word;
  char c;
  uint32_t index = 0;

  for (int i = 0; i < size; i++)
  {
    word = naughty_list[i];
    len = string_len(word);
    ptr = string;
    count = 0;

    while (*ptr != 0 )
    {
      if (*ptr == *word)
      {
        count++;
        word++;
      }
      else
      {
        /* reset counter and word ptr */
        count = 0;
        word = naughty_list[i];
      }

      if (count == len)
      {
        memset(ptr - (len - 1), 'x', len);
        count = 0;
      }
      ptr++;
    }
  }

}


void censor_string_test ()
{
  char data[30] = "hector_williams_abc_def";
  char  *words[2] =  {
    "hector",
    "abc",
  };
  censor_string(data, words, 2);
  printf("\t [%s]\n", data);
}

boolean genetic_marker (char *string, char **string_list, uint32_t size)
{
  char *word;
  uint32_t len;

  if (size <= 0)
  {
    return False;
  }

  word = string_list[size - 1];
  len = string_len(word);

  if ( ! genetic_marker_compare_string(string, word, len) )
  {
    return genetic_marker(string, string_list, size - 1);
  }
  return True;

}

boolean genetic_marker_compare_string(char *str, char *marker, uint32_t size)
{
  uint32_t count = 0;

  while (*str != 0)
  {
    if ( *marker == *str || *marker != '?' && count != size )
    {
      count++;
    }
    else
    {
      count = 0;
    }
    str++;
    marker++;
  }
  return count == size;
}

void genetic_marker_test()
{
  char * list[3] = {
    "abc?r",
    "jeff",
    "kiki"
  };
  boolean bool = genetic_marker("abcd", list, 3);
  printf("string  found in list %d\n", bool);
}

void optimal_sequence_helper_display (char ** list, uint32_t list_size)
{
  printf("[");
  for (int i = 0; i < list_size; i++)
  {
    printf("%s", list[i]);
    if (i + 1 != list_size)
    {
      printf(",");
    }
  }
  printf("]\n");

}

struct optimal_seq optimal_sequence(char ** list, uint32_t list_size, uint32_t word_size)
{
  boolean done = 0;
  struct optimal_seq optimum  = {.size = list_size, .done = 0, .data = NULL};
  optimal_sequence_helper(list, list_size, word_size, NULL, 0, &optimum);
  return  optimum;
}

char ** optimal_sequence_helper_clone_list(char **list, uint32_t list_size, uint32_t word_size, boolean has_data)
{
  char **clone = (char **) malloc( sizeof(char*) * list_size);

  for (int i = 0; i < list_size; i++)
  {
    clone[i] = (char *) malloc( sizeof(char) * (word_size + 1));
    if (has_data)
    {
      memcpy(clone[i], list[i], word_size + 1 );
    }
    else
    {
      memset(clone[i] , '\0',  word_size + 1);
    }
  }
  return clone;
}

void optimal_sequence_helper_swap( char **collection, int src_pos, int dest_pos , uint32_t length)
{
  char *tmp = *(collection + src_pos);

  *(collection + src_pos) = *(collection + dest_pos);
  *(collection + dest_pos) = tmp;


}
void optimal_sequence_helper(char **list, const uint32_t list_size, uint32_t word_size, char **buffer, uint32_t col, struct optimal_seq  *obj)
{
  char ** clone_list = optimal_sequence_helper_clone_list(list, list_size, word_size, True);
  char ** clone_buffer  = (buffer == NULL) ? optimal_sequence_helper_clone_list(buffer, list_size, word_size, False) :  optimal_sequence_helper_clone_list(buffer, list_size, word_size, True);
  char *list_word, *buffer_word;



  if (col  == word_size  )
  {
    obj->done = True;
    obj->data = clone_buffer;
    obj->size = list_size;
  }

  if (obj->done)
  {
    return;
  }

  for (int alpha = 65; alpha < 91; alpha++)
  {
    for (int n = 0; n < list_size; n++)     /* iterate collection of words  updating buffer*/
    {
      list_word = *(clone_list + n );
      buffer_word = *(clone_buffer + n) ;

      if (  list_word [col] != '?')
      {
        buffer_word[col] = list_word[col];
      }
      else
      {
        buffer_word[col] = (char) alpha;
      }
    }

    /* sort clones */
    optimal_sequence_helper_helper_sort_by_column(clone_list, clone_buffer, list_size, word_size, col);

    // optimal_sequence_helper_display(clone_buffer, list_size);

    // /* recursive valid sequences */
    if ( optimal_sequence_helper_helper_col_is_sorted(clone_buffer, list_size, word_size, col))
    {
      optimal_sequence_helper(clone_list, list_size, word_size, clone_buffer , col + 1, obj);
    }

    clone_list = optimal_sequence_helper_clone_list(list, list_size, word_size, True);
    clone_buffer  = (buffer == NULL) ? optimal_sequence_helper_clone_list(buffer, list_size, word_size, False) :  optimal_sequence_helper_clone_list(buffer, list_size, word_size, True);

  }

}

boolean optimal_sequence_helper_helper_col_is_sorted(char **list, uint32_t list_size, uint32_t word_size, uint32_t col)
{
  boolean state = True;
  for (int i = 0; i < list_size - 1; i++)
  {
    for (int c = 0; c < col + 1; c++)
    {
      state = state &&  (*(list +i  ))[c]  <= (*(list + i + 1))[c];
    }
  }
  return state;
}

void optimal_sequence_helper_helper_sort_by_column(char **list, char **buffer, uint32_t list_size, uint32_t word_size, uint32_t col)
{

  char c;
  int pos = 0;

  /* insertion sort */

  for (int curr = 0; curr < list_size; curr++)
  {
    pos = curr;
    c = (*( buffer + curr ))[col];

    for (int next = curr; next < list_size; next++)
    {
      if ( (*( buffer + next )) [col]  < c)
      {
        c = (*( buffer + next )) [col];
        pos = next;
      }
    }

    if (pos != curr)
    {
    /* swap  addresses */
      optimal_sequence_helper_swap( list,  pos ,curr , word_size);
      optimal_sequence_helper_swap( buffer,  pos ,curr , word_size);
    }

  }
}

void optimal_sequence_test()
{
  char *collection[3] = {"EA?K","?RX?","GAG?"};
  int word_len = 4;
  int list_len = 3;
  struct optimal_seq optimum   = optimal_sequence(collection, list_len, word_len);
  optimal_sequence_helper_display(optimum.data, list_len);
}


char * dedupe (const char * string)
{
  static boolean reset = 0;
  static char buffer[20] ;
  static unsigned index = 0;

  if (reset == 1 )
  {
    /* clear string buffer */
    reset = 0;
    index = 0;
  }

  if (*string == '\0')
  {
    /*reset sub routine */
    reset = 1;
    return buffer;
  }

  char c = string[0];
  for (int n = 1;  string[n] != 0; n++)
  {
    if (string[n] == c)
    {
      return dedupe(string + 1);
    }
  }
  buffer[index++] = c;
  return dedupe(string + 1);
}

void dedupe_test()
{
  char * data = dedupe("Snaps! crackles! pops!");
}


int first_unique_letter_index (const char * msg)
{
  static int done_flag = 0;
  static unsigned index = 0;
  char curr_c;

  if (done_flag == 1)
  {
    index = 0;
  }

  if (*msg == 0 || msg == NULL)
  {
    return -1;
  }

  curr_c = msg[index];

  for (int i = 0; msg[i] != 0; i++)
  {
    if (i == index)
    {
      continue;
    }

    if (curr_c == msg[i])
    {
      index++;
      return first_unique_letter_index(msg);
    }
  }

  done_flag = 1;
  printf("[%s]\n", msg);
  return index;

}

void first_unique_letter_index_test()
{
  int i = first_unique_letter_index("empathetic monarch meets primo stinker");
  printf("index %d\n", i);
}

char * unique_letters (const char * str)
{
  static int search_index = 0;
  static int curr_index = 0;
  static int done = 0;
  static char buffer[100];
  char c;


  if (str == NULL || search_index >= 100)
  {
    search_index = curr_index = 0;
    return buffer;
  }

  if (done)
  {
    search_index = curr_index = 0;
    done = 0;
  }

  if ( str[search_index] == '\0' )
  {
    done = 1;
    return buffer;
  }

  for (int i = 0; str[i] != 0; i++)
  {
    if (i == search_index )
    {
      continue;
    }

    if ( str[i] == str[search_index])   /* not unique */
    {
      search_index++;
      return unique_letters(str);
    }
  }

  buffer[curr_index++] =  str[search_index] ;
  search_index++;
  return unique_letters(str);
}

void unique_letter_test()
{
  const char * msg = "Snap! Crackle! Poop!";
  char * data  = unique_letters(msg);
  printf("[%s]\n", data);
}

  void  num_to_string_helper(double number, int k, char *buffer)
 {

  int digit =  ( (int) (number) )% 10;
  char c = (char) ( 48 + digit );

  if (k >= 0)
  {
    if (digit)
    {
      memset(buffer + k, c, 1);
      return num_to_string_helper(number /10.0, k + 1, buffer);
    }
  }

  else if (  digit  || number - (float) ((int) number) >  0.0 )
  {
    memset(buffer + abs(k) - 1, c, 1);  /* k < 0 */
    return num_to_string_helper(number * 10.0, k - 1, buffer);
  }

  /* terminate string */

  if (k < 0)
  {
    memset(buffer + abs(k) - 1 , 0, 1);
  }
  else
  {
    memset(buffer + abs(k) , 0, 1);
  }
}

 char * num_to_string(double number)
{
  char buffer[100];
  char buffer_decimal[50];
  unsigned idx = 0;

  num_to_string_helper(number, 0, buffer);
  num_to_string_helper(number * 10.0, -1, buffer_decimal);

  /* append decimal to whole string */

  while (buffer[idx] != 0)
  {
    idx++;
  }

  /* write decimal char*/
  buffer[idx++] = '.';

  /* cpy mv decimal data*/
  memmove(buffer + idx, buffer_decimal, string_len(buffer_decimal));

  return buffer;
}

void num_to_string_test()
{
  double number = 11.2051;
  char * result = num_to_string(number);
  printf("result  = %s\n", result);
}

int main()
{
  num_to_string_test();
}

