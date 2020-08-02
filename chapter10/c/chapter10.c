#include <stdio.h>
#include "chapter10.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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

char * num_to_text(double number)
{
  struct NumToTextStruct obj;
  static char text [200];

  for (int i = 0; i < 200; i++)
  {
    text[i] = '\0';
  }

  num_to_text_helper(number , &obj, 0);
  num_to_text_helper(number * 10, &obj, -1);
  num_to_text_helper_parser_natural(obj.whole, text);
  num_to_text_helper_parser_decimal(obj.decimals, text);

  return text;
}

void num_to_text_helper_parser_decimal(char * string, char *text )
{
  int digit;

  if (string == NULL)
  {
    return;
  }

  if (*string == 0)
  {
    return;
  }

  strcat(text, "point ");

  while (*string != 0 )
  {
    digit = (char) *string - 48;
    switch (digit)
    {
      case 1:
        strcat(text, "one ");
        break;
      case 2:
        strcat(text, "two ");
        break;
      case 3:
        strcat(text, "three ");
        break;
      case 4:
        strcat(text, "four ");
        break;
      case 5:
        strcat(text, "five ");
        break;
      case 6:
        strcat(text, "six ");
        break;
      case 7:
        strcat(text, "seven ");
        break;
      case 8:
        strcat(text, "eight ");
        break;
      case 9:
        strcat(text, "nine ");
        break;

    }
    string++;
  }


}

void num_to_text_helper_parser_natural(char * string , char *text)
{
  int size = 3;
  char buffer[3];
  char data[100] = "";
  int data_len;
  static int counter = 0;

  if (text == NULL)
  {
    counter = 0;
  }

  if (*text == 0)
  {
    counter = 0;
  }

  for (int i = 0; i < size; i++)
  {
    buffer[size - 1 - i] = string[size - 1 - i];
  }

   if ( ( buffer[1] >=48 && buffer[1] < 58) == 0 )
  {
    /* 1 digit in buffer  */
    num_to_text_helper_translate(buffer, 1, data);
  }
  else if ( ( buffer[2] >=48 && buffer[2] < 58) == 0 )
  {
    /* 2 digits  buffer*/
    num_to_text_helper_translate(buffer, 2, data);
  }
  else
  {
    /* 3 digits  in buffer */
    num_to_text_helper_translate(buffer, 3, data);
  }

  switch(counter)
  {
    case 1:
      strcat(data, "thousand ");
      break;
    case 2:
      strcat(data, "million ");
      break;
    case 3:
      strcat(data, "billion ");
      break;
    case 4:
      strcat(data, "trillion ");
      break;
    case 5:
      strcat(data, "quadrillion ");
      break;
    case 6:
      strcat(data, "quintillion");
      break;
  }

  /* append to text */
  if (*data == 0)
  {
    strcat(text, data);
  }
  else
  {
    data_len = string_len(data);
    memmove(text + data_len, text, string_len(text));
    memcpy(text, data, data_len);
  }

  if (string[3] != 0) /* recursion*/
  {
    counter++;
    return num_to_text_helper_parser_natural(string + 3, text);
  }
}

void num_to_text_helper(double number, struct NumToTextStruct *obj, int pos )
{
  int digit = (int) number % 10;
  char c = (char) (48 + digit);
  int sel;

  /* decimal */
  if (pos < 0) {
    if ( digit > 0 || number - (float)( (int) number)  > 0 )
    {
      obj->decimals[ abs(pos) - 1] = c;
      return num_to_text_helper(number * 10, obj, pos - 1);
    }
    obj->decimals[abs(pos) - 1] = 0;
  }

  /* integer */
  else if (pos >= 0 )
  {
    if ( (int) number > 0 )
    {
      sel = (int) pos / 3;
      /* right shift segment*/
      for (int i = (sel + 1)* 3 - 1 ; i >  sel * 3; i--)
      {
        obj->whole[ i ] = obj->whole[i - 1];
      }
      /* insert @ pos 0 */
      obj->whole[  sel * 3 ] = c;
      return num_to_text_helper(number / 10, obj, pos + 1);
    }
  }
}

void num_to_text_helper_translate(char *data,  unsigned width, char *text )
{
  int real_pos = 3 - width;
  int index = 0;
  int digit;
  char prev_char;
  char msg[100];

  if (real_pos == 0 )   /* hundreds */
  {
    width--;
    digit = data[index] - 48;
    real_pos++;

    switch
     (digit)
    {
      case 1:
        strcat(text, "one hundred ");
        break;

      case 2:
        strcat(text, "two hundred ");
        break;

      case 3:
        strcat(text, "two hundred ");
        break;

      case 4:
        strcat(text, "three hundred ");
        break;

      case 5:
        strcat(text, "five hundred ");
        break;

      case 6:
        strcat(text, "six hundred ");
        break;

      case 7:
        strcat(text, "seven hundred ");
        break;

      case 8:
        strcat(text, "eight hundred ");
        break;

      case 9:
        strcat (text, "nine hundred ");
        break;
    }
    index++; /* next char */
  }

  if (real_pos == 1 && width--)   /* tens */
  {
    digit = data[index] - 48;
    prev_char = data[index];  /*store middle character */
    real_pos++;

    switch(digit)
    {
      case 1:
        break;
      case 2:
        strcat(text, "twenty ");
        break;
      case 3:
        strcat(text, "thirty ");
        break;
      case 4:
        strcat(text, "fourty ");
        break;
      case 5:
        strcat(text, "fifty ");
        break;
      case 6:
        strcat(text, "sixty ");
        break;
      case 7:
        strcat(text, "seventy ");
        break;
      case 8:
        strcat(text, "eighty ");
        break;
      case 9:
        strcat(text, "ninety ");
        break;
    }
    index++; /* next char */
  }

  if (real_pos == 2 && width)   /* ones (unit) */
  {
    digit = data[index] - 48;

    if (data[index - 1] - 48 == 1)
    {
       /* TEENS */
      switch (digit)
      {

        case 0:
          strcat(text, "ten" );
          break;

        case 1:
          strcat(text, "eleven ");
          break;

        case 2:
          strcat(text, "twelve ");
          break;

        case 3:
          strcat(text, "thirteen ");
          break;

        case 4:
          strcat(text, "fourteen ");
          break;

        case 5:
          strcat(text, "fifteen ");
          break;

        case 6:
          strcat(text, "sixteen ");
          break;

        case 7:
          strcat(text, "seventeen ");
          break;

        case 8:
          strcat(text, "eighteen ");
          break;

        case 9:
          strcat(text, "nineteen ");
          break;
      }
    }

    else

    {
      switch (digit)
      {
        case 1:
          strcat(text, "one ");
          break;
        case 2:
          strcat(text, "two ");
          break;
        case 3:
          strcat(text, "three ");
          break;
        case 4:
          strcat(text, "four ");
          break;
        case 5:
          strcat(text, "five ");
          break;
        case 6:
          strcat(text, "six ");
          break;
        case 7:
          strcat(text, "seven ");
          break;
        case 8:
          strcat(text, "eight ");
          break;
        case 9:
          strcat(text, "nine ");
          break;
      }
    }
  }
}

void num_to_text_test()
{
  char *text = num_to_text(40213.23);
  printf("%s \n", text);
}

boolean is_permtutaoin(const char *string, const char *perm)
{
  boolean search_done = 0;
  is_permtutaoin_helper(string, perm, NULL, &search_done);
  return search_done;
}

void is_permtutaoin_helper ( char *string,  const char *perm,  char *buffer, boolean *done)
{
  char clone_buffer[50] = "";
  char clone_string[50] = "";
  int buffer_index = 0;
  int clone_wr_index = 0;

  if (string == NULL || perm == NULL)
  {
    return;
  }

  if (*string == 0)
  {
    if (strcmp(buffer, perm) == 0) /* match found */
    {
      *done = 1;
    }
    return;
  }

  if (*done)  /* match previous found*/
  {
    return;
  }

   if (buffer)
  {
    buffer_index = string_len(buffer);
    if ( string_len(buffer) >= string_len(perm) )
    {
      return;
    }
    memcpy(clone_buffer, buffer, 50);
  }

  for (int i = 0;  *(string + i) != 0; i++)
  {
    clone_wr_index = 0;
    for (int k = 0; *(string + k) != 0; k++)
    {
      if (i != k)
      {
        clone_string[clone_wr_index++] = string[k];
      }
      else
      {
        clone_buffer[buffer_index] = string[k];
      }
    }
    is_permtutaoin_helper(clone_string, perm, clone_buffer, done);
  }
}

void is_permtutaoin_test()
{
  boolean result = is_permtutaoin("mister", "stimer");
  printf("permtation exist  %d\n", result);
}

boolean is_pangram(const char *str)
{
  char alpha[26] = "";
  return 26 == is_pangram_helper(str, alpha);
}

int is_pangram_helper(const char *str, char * array)
{
  int index;
  boolean bit = 0;

  if (*str == 0)
  {
    return 0;
  }

  index = tolower(*str) - 97; /* lower case only */

  if (index >= 0 && index < 26 )
  {
    if (array[index] == 0)  /*paint array */
    {
      array[index] = 1;
      bit = 1;
    }
  }
  return bit + is_pangram_helper(str + 1, array);
}

void is_pangram_test()
{
  const char *msg = "How quickly daft jumping zebras vex!"; // true
  const char *msg2 = "abcdef ghijkl mno pqrs tuv wxy, not so fast!"; // false
  printf("[%d]\n", is_pangram(msg2));
}

struct str_permutations all_string_permutations (const char *string)
{
  struct str_permutations *perms = NULL;
  int len = string_len(string);
  all_string_permutations_helper(string, len , &perms, NULL );
  return *perms;
}

void all_string_permutations_helper(const char *string, unsigned size, struct str_permutations **llist, char *buffer)
{

  int buffer_wr_index;
  char * clone_buffer;
  char * clone_string;
  int string_wr_index;

  buffer_wr_index = (!buffer) ? 0 : string_len(buffer);

  if (size == buffer_wr_index)
  {
     struct str_permutations *node = (char *) malloc(size);
     node->next = NULL;
     node->data = buffer;

    if (*llist == NULL)
    {
      *llist = node;
    }
    else
    {
      node->next = *llist;
      *llist = node;
    }
    return;
  }

  clone_buffer = (char *) malloc( sizeof( buffer_wr_index + 1));
  clone_string = (char *) calloc(sizeof(string_len(string)) , sizeof(char));

  if (buffer)
  {
    memcpy(clone_buffer, buffer, buffer_wr_index);
  }

  for (int i = 0; string[i] != 0; i++ )
  {
    string_wr_index = 0;
    for (int k = 0; k < string[k] !=0; k++)
    {
      if (i != k)
      {
        clone_string[string_wr_index++] = string[k];
      }
      else
      {
        clone_buffer[buffer_wr_index] = string[k];
      }

    }

    all_string_permutations_helper(clone_string, size, llist, clone_buffer);
  }

}


void all_string_permutations_test()
{
  struct str_permutations llist = all_string_permutations("team");
  struct str_permutations *runner = &llist;
  while (runner)
  {
    printf("\t[%s]\n", runner->data);
    runner = runner->next;
  }
}

boolean perfect_pangram (const char *str)
{
  char alpha[26] = "";
  return 26 == perfect_pangram_helper(str, alpha);
}

int perfect_pangram_helper(const char *str, char * alpha)
{
  char c;
  int bit = 0;

  if (*str == 0)
  {
    return 0;
  }

  c = tolower(*str);

  if (c >= 'a' && c <= 'z' )
  {
    if (alpha[c - 97] == 0)
    {
      bit = 1;
      alpha[c - 97] = 1;
    }
    else
    {
      bit = -1;
    }
  }

  return bit + perfect_pangram_helper(str+ 1, alpha);
}

void perfect_pangram_test()
{
  const char *msg = "Playing jazz vibe chords quickly excites my wife."; //false
  const char *msg2 = "Mr. Jock, TV quiz PhD, bags few lynx."; // true
  boolean x = perfect_pangram(msg);
  boolean y = perfect_pangram(msg2);

  printf(" is perfect pangram %d\n",y);
}

void best_single_buy_sell_test ()
{
  int mem[]  = {6,4,6,5,9,7,6,12,2,6,11,2,4};
  int size = sizeof(mem) / sizeof(mem[0]);
  int max = best_single_buy_sell(mem, size );
  printf("max %d \n", max);
}

int best_single_buy_sell (int *array, int size)
{
  int max = 0;
  best_single_buy_sell_helper(array, size, NULL, 0, &max);
  return max;
}

void best_single_buy_sell_helper  (int *array, int array_size, int *buffer, int buffer_size, int *max)
{
  int wr_index = buffer_size == 0 ? 0: buffer_size;
  int *clone_buffer = (int *) malloc(sizeof(int) * (wr_index + 1) );

  if (array_size <= 0)
  {
    return;
  }

  // #clone
  if (buffer_size > 0)
  {
    memcpy(clone_buffer, buffer, buffer_size);
  }

  clone_buffer[wr_index] = array[0]; /* recent entry aggregate */

  if (array[1] > array[0] && array_size - 1 != 0)
  {
    best_single_buy_sell_helper(array + 1, array_size -  1, clone_buffer, wr_index + 1, max);
  }
  else  /* discontinuity*/
  {
    if (buffer_size)
    {
      if (clone_buffer[wr_index] - clone_buffer[0] > *max)
      {
        *max = clone_buffer[wr_index] - clone_buffer[0];
      }
    }
    return best_single_buy_sell_helper(array + 1, array_size -  1, NULL, 0, max);
  }
}

int best_single_buy_sell_second (int *array, int size)
{
  int sum = 0;
  best_single_buy_sell_helper_second(array, size, NULL, 0, &sum);
  return sum;
}

void best_single_buy_sell_helper_second  (int *array, int array_size, int *buffer, int buffer_size, int *data)
{
  int wr_index = buffer == NULL ? 0: buffer_size;
  int *clone_buffer = (int *) malloc(sizeof(int) * (wr_index + 1) );

  if (array_size <= 0)
  {
    return;
  }

  if (buffer_size > 0)
  {
    memcpy(clone_buffer, buffer, buffer_size);
  }

  clone_buffer[wr_index] = array[0];


  if (array[1] >= array[0] && array_size - 1 != 0)
  {
    best_single_buy_sell_helper_second(array + 1, array_size - 1, clone_buffer, wr_index + 1, data);
  }
  else
  {
    if (buffer_size)
    {
      *data += clone_buffer[wr_index] - clone_buffer[0];  /* buy/ sell price (sum profits) */
    }

    return  best_single_buy_sell_helper_second(array + 1, array_size - 1, NULL, 0, data);
  }
 }

void best_single_buy_sell_second_test ()
{
  int mem[]  = {6,4,6,5,9,7,6,12,2,6,11,2,4};
  int size = sizeof(mem) / sizeof(mem[0]);
  int max = best_single_buy_sell_second(mem, size );
  printf("%d\n", max);
}


boolean loosely_interleaved(const char * a, const char *b , const char *c)
{
  boolean isInterleaved;
  int size = string_len(c);
  char * tmp_string = (char *) malloc(size);
  isInterleaved = loosely_interleaved_helper(a, b , c, tmp_string );

  free(tmp_string);
  return isInterleaved;
}

boolean loosely_interleaved_helper(const char * a, const char *b, const char *c, char *buffer)
{
  int index = string_len(buffer);

  if (*a == 0 ^ *b == 0)
  {
    return False;
  }

  if (strcmp(buffer, c) == 0)
  {
    return True;
  }

  if (*a == 0 && *b == 0)
  {
    return False;
  }

  buffer[index++] = *a;
  buffer[index++] = *b;

  return loosely_interleaved_helper(a + 1, b + 1, c, buffer);
}

void loosely_interleaved_test()
{
  boolean x = loosely_interleaved ( "dne", "ail", "daniel");
  printf(" \t [%d] \n", x);
}

struct str_llist *all_loosely_interleaved(const char *a, const char *b)
{
  char *data_a = (char *) malloc(string_len(a));
  char *data_b = (char *) malloc(string_len(b));
  char *data = (char *) malloc(string_len(a) + string_len(b));
  char *data_reverse = (char *) malloc(string_len(a) + string_len(b));

  struct str_llist *llist = NULL;
  all_loosely_interleaved_helper(a, b, "",  &llist);

  /* edge case interleave base data [a][b]  and reverse  [b][a]*/

  strcat(data,a);
  strcat(data,b);

  strcat(data_reverse,b);
  strcat(data_reverse,a);

  all_loosely_interleaved_helper_insert_interleave_data(data_reverse, &llist);
  all_loosely_interleaved_helper_insert_interleave_data(data, &llist);

  return llist;
}

void all_loosely_interleaved_helper_clone(char *dest, char *src, int length)
{
    char *  clone = (char *)  malloc(length);
    memcpy(dest,  src, length);
}

void all_loosely_interleaved_helper_insert_interleave_data(char *data, struct str_llist **llist)
{
  struct str_llist *llistElement =  (struct str_llist*) malloc(sizeof(struct str_llist));
  llistElement->data = data;
  llistElement->next = NULL;

  if (*llist == NULL)
  {
    *llist = llistElement;
  }
  else
  {
    llistElement->next =  *llist;
    *llist = llistElement;
  }

}

void all_loosely_interleaved_helper ( const char *a, const char *b, char * buffer , struct str_llist **llist)
{
  char *clone_a, *clone_b;
  int buffer_wr = string_len(buffer);
  int length_a  = string_len(a);
  int length_b = string_len(b);
  char *clone_buffer;


  if (*a == 0 && *b == 0)
  {
    all_loosely_interleaved_helper_insert_interleave_data(buffer, llist);
    return;
  }


  if (length_a == length_b)
  {
    /* BRANCH A */
    all_loosely_interleaved_helper_branch_search(a, length_a, b, buffer, buffer_wr, llist);


    /* BRANCH B */

    all_loosely_interleaved_helper_branch_search(b, length_b, a, buffer, buffer_wr, llist);

  }

  else if (length_a > length_b)
  {
    /* BRANCH A */
    all_loosely_interleaved_helper_branch_search(a, length_a, b, buffer, buffer_wr, llist);
  }

  else if (length_b > length_a)
  {
    /* BRANCH B */

    all_loosely_interleaved_helper_branch_search(b, length_b, a, buffer, buffer_wr, llist);
  }

}

void all_loosely_interleaved_helper_branch_search(char *a, int a_len,  char *b, char *buffer, int buffer_len , struct str_llist **llist)
{
  char *clone_a, *clone_buffer;

  /*branch data A */
  clone_a = (char *)  malloc(a_len - 1);
  all_loosely_interleaved_helper_clone(clone_a, a + 1, a_len - 1);

  clone_buffer = (char *) malloc(buffer_len + 1);
  all_loosely_interleaved_helper_clone(clone_buffer, buffer, buffer_len);
  clone_buffer[buffer_len] = *a;

  all_loosely_interleaved_helper(clone_a, b, clone_buffer, llist);
}

void all_loosely_interleaved_test()
{
 struct str_llist *llist =  all_loosely_interleaved ( "ab" , "yz");
 struct str_llist *runner = llist;

 while (runner)
 {
   printf( "[%s] \n", runner->data);
   runner = runner->next;
 }
}

boolean is_palindrome(const char *string )
{
  int len =  string_len(string);
  int mid = len / 2;

  for (int i = 0; i < mid ; i++)
  {
    if (string[i] != string[len - 1 - i])
    {
      return False;
    }
  }
  return True;
}

int make_string_palindrome_remove(const char * string)
{
  int start = 0;

  if (is_palindrome(string))
  {
    return -1;
  }
  return make_string_palindrome_remove_helper(string, start);
}

int make_string_palindrome_remove_helper(const char *string, int exclude_index)
{
  char buffer[20] = "";

  if ( string[exclude_index] == 0)
  {
    return -2;
  }

  if (exclude_index == 0)
  {
    strcat(buffer, string + 1);
    printf(" %s\n", buffer);
  }
  else
  {
    strncat(buffer, string, exclude_index);
    strcat(buffer, string + exclude_index + 1);
  }

  if (is_palindrome(buffer))
  {
    return exclude_index;
  }
  else
  {
    return make_string_palindrome_remove_helper(string, exclude_index + 1);
  }
}

void make_string_palindrome_remove_test()
{
  int answer = make_string_palindrome_remove("ene");
  printf(" [%d] \n", answer);
}

char * encode_string(const char *str)
{
  static int reset = 0;
  static int count = 0;
  static char data[25] = "";
  static int data_wr_pos = 0;

  if (reset == 1)
  {
    /* reset data array */
    for (int i = 0; i < 25; i++)
    {
      data[i] = '\0';
    }
  }

  if (*str == 0)
  {
    reset = 1;
    return data;
  }

  count++;

  if ( str[1] == 0 || str[0] != str[1] )
  {
    data[data_wr_pos++] = *str;
    data[data_wr_pos++] = (char) (48 + count);
    count = 0;
  }

  return encode_string(str + 1);
}

void encode_string_test()
{
  const char * msg = "aaaabbcddd";
  char * data = encode_string(msg);

  printf(" [%s] \n " , data);
}


char * string_decode(const char *str)
{
  static char buffer[25] = "";
  static reset = 0;
  char c;
  int count = 0 ;
  static int index = 0;

  if (reset == 1)
  {
    for (int i = 0; buffer[i] != 0; i++ )
    {
      buffer[i] = 0;
    }
    reset = 0;
    index = 0;
  }

  if (*str == 0)
  {
    reset = 1;
    return buffer;
  }

  c = str[0];
  count = str[1] - 48;
  while (count--)
  {
    buffer[index++] = c;
  }
  return string_decode(str + 2);
}

void string_decode_test ()
{
  const char * msg = "a4b2c1d3";

  char * solution = string_decode(msg);
  printf(" \t [%s] \n" , solution);
}

void shortener_string_remove_char(char *str)
{
  int len = string_len(str);

  memmove(str, str + 1, len - 1);
  memset(str + len - 1 , 0, 1 );
}

char * shortener_string(  char * str, int length)
{
  static int state = 0;
  int len = string_len(str) ;
  char * buffer = (char *) malloc(sizeof(char) * 50 ) ;
  char *ptr;


  if (len == length)
  {
    return str;

  }

  memcpy(buffer, str,len );

  switch (state)
  {
    case 0:
      ptr = buffer;

      if (length > len)
      {

        while (len != length)
        {
          if (length != string_len(buffer) )
          {
            memmove(buffer + 1, buffer, string_len(buffer));
            memset(buffer, 32 , 1);
          }

          if (length != string_len(buffer))
          {
            memset(buffer + string_len(buffer), 32, 1);
          }
          len = string_len(buffer);
        }
      }
      else
      {
        while (len > length &&   ( *ptr == ' ' || *(ptr + len - 1) == ' ' )  )
        {
          if (*ptr == ' ')
          {
            shortener_string_remove_char(ptr);
          }
          else if ( *(ptr + len - 1) == ' ' )
          {
            shortener_string_remove_char(ptr + len - 1) ;
          }
          else
          {
            ptr++;
          }
          len = string_len(buffer);
        }

        ++state;
        return shortener_string(buffer, length);
      }

    case 1:
      ptr = buffer + len - 1;

      while (len > length && ptr > buffer)
      {
        if (*(ptr - 1) == ' ' && *ptr != ' ')
        {
          *ptr = toupper(*ptr);
          shortener_string_remove_char(ptr - 1);
        }
        ptr--;

        len  = string_len(buffer);
      }

      ++state;
      return shortener_string(buffer, length);

    case 2:
      ptr = buffer + len - 1;

      while (len > length && ptr > buffer)
      {
        if (*ptr == ',' || *ptr == '\'' || *ptr == '!' || *ptr == '.' || *ptr == '-' || *ptr == '\"' || *ptr == ':' || *ptr == ';'  )
        {
          shortener_string_remove_char(ptr);
        }
        ptr--;
        len = string_len(buffer);
      }
      ++state;

      return shortener_string(buffer, length);

    case 3:
      ptr = buffer + len ;

      /* lower vowels first */
      while (len > length && ptr > buffer)
      {
        if ( *ptr == 'a' || *ptr == 'e' || *ptr == 'i' || *ptr == 'o' || *ptr == 'u')
        {
          shortener_string_remove_char(ptr);
        }
        ptr--;
        len = string_len(buffer);
      }

      ptr = buffer + string_len(buffer);

      /* others lower case values removed */

      while (len > length && ptr > buffer)
      {
        if (islower(*ptr))
        {
          shortener_string_remove_char(ptr);
        }
        ptr--;
        len = string_len(buffer);
      }
      ++state;
      return shortener_string(buffer, length);

    case 4:

      ptr = buffer + len;
      while (len > length && ptr > buffer)
      {
        if (isupper(*ptr))
        {
          shortener_string_remove_char(ptr);
        }
        ptr--;
        len = string_len(buffer);
      }
      ++state;
      return shortener_string(buffer, length);
  }
  return buffer;

}

void shortener_string_test()
{

  const char * msg = "It's a wonderful life, Beth! ";
  char * data = shortener_string(msg, 3);

  printf("[%s] \n", data);

}

int main()
{
  shortener_string_test();
}

