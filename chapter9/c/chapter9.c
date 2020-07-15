#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "chapter9.h"

int recursive_sigma(int number)
{
  if (number <= 0)
    return 0;
  return number + recursive_sigma(number - 1);
}

int recursive_factorial(double number)
{
  if (number <= 1)
    return 1;
  return (int)number * recursive_factorial(number - 1);
}

void flood_fill(int canvas2D[5][5], int startXY[2], int newColor)
{
  int row = startXY[0];
  int col = startXY[1];
  int currColor;
  int newStartXY[2];

  /* outside limits */
  if ((row < 0 || row >= 5) || (col < 0 || col >= 5))
    return;

  currColor = canvas2D[row][col];

  /* fill color */
  canvas2D[row][col] = newColor;

  /* walk up */
  if (row > 0)
  {
    newStartXY[0] = row - 1;
    newStartXY[1] = col;
    if (currColor == canvas2D[newStartXY[0]][newStartXY[1]])
      flood_fill(canvas2D, newStartXY, newColor);
  }

  /* walk down */
  if (row < 4)
  {
    newStartXY[0] = row + 1;
    newStartXY[1] = col;
    if (currColor == canvas2D[newStartXY[0]][newStartXY[1]])
      flood_fill(canvas2D, newStartXY, newColor);
  }

  /* walk left */
  if (col > 0)
  {
    newStartXY[0] = row;
    newStartXY[1] = col - 1;
    if (currColor == canvas2D[newStartXY[0]][newStartXY[1]])
      flood_fill(canvas2D, newStartXY, newColor);
  }

  /* walk right */
  if (col < 4)
  {
    newStartXY[0] = row;
    newStartXY[1] = col + 1;
    if (currColor == canvas2D[newStartXY[0]][newStartXY[1]])
      flood_fill(canvas2D, newStartXY, newColor);
  }
}

void test_recursive_factorial()
{
  int canvas[5][5] = {
      {3, 2, 3, 4, 3},
      {2, 3, 3, 4, 0},
      {7, 3, 3, 5, 3},
      {6, 5, 3, 4, 1},
      {1, 2, 3, 3, 3},
  };

  int startXY[2] = {2, 2};

  flood_fill(canvas, startXY, 1);

  /*print array*/
  for (int r = 0; r < 5; r++)
  {
    for (int c = 0; c < 5; c++)
    {
      printf("[%d]", canvas[r][c]);
    }
    printf("\n");
  }
}

int fibonacci(double num)
{
  if (num <= 0)
    return 0;
  else if (num == 1)
    return 1;
  else
    return fibonacci(num - 2) + fibonacci(num - 1);
}

int tribonacci(double num)
{
  if (num <= 1)
    return 0;
  else if (num == 2)
    return 1;
  else
    return tribonacci(num - 3) + tribonacci(num - 2) + tribonacci(num - 1);
}

void fibonacci_test()
{
  for (double i = 0; i < 5; i++)
  {
    printf("[%d]\n", fibonacci(i));
  }
}

void tribonacci_test()
{
  for (double i = 0; i < 5; i++)
  {
    printf("[%d]\n", tribonacci(i));
  }
}

int paging_ackermann(unsigned a, unsigned b)
{
  if (a == 0)
    return b + 1;
  else if (b == 0)
  {
    if (a > 0)
      return paging_ackermann(a - 1, 1);
    else
      return b + 1;
  }
  else
    return paging_ackermann(a - 1, paging_ackermann(a, b - 1));
}

int Zibonacci(unsigned number)
{
  unsigned n = 0;

  if (number <= 1)
  {
    return 1;
  }

  if (number == 2)
  {
    return 2;
  }

  if (number % 2 == 1)
  {
    n = --number / 2;
    return Zibonacci(n) + Zibonacci(n - 1) + 1;
  }

  if (number % 2 == 0)
  {
    n = number / 2;
    return Zibonacci(n) + Zibonacci(n + 1) + 1;
  }
  return n;
}

void Zibonacci_test()
{
  int data;
  for (int i = 0; i < 10; i++)
  {
    data = Zibonacci(i);
    printf("%d --> %d\n", i, data);
  }
}

boolean recursive_binary_search(int collection[], unsigned size, int target)
{
  unsigned mid;
  unsigned data;
  int *copy_collection;
  unsigned is_odd = 0;

  if (size == 0)
    return False;

  mid = (size / 2);
  data = collection[mid];
  is_odd = +(size % 2);

  if (target == data)
  {
    return True;
  }
  else if (target < data)
  {
    return recursive_binary_search(collection, mid, target);
  }
  else if (target > data)
  {
    return recursive_binary_search(collection + mid + 1, size - (mid + is_odd), target);
  }
}

void recursive_binary_search_test()
{
  int collection[5] = {4, 5, 6, 8, 12};
  int collection_size = 5;
  boolean answer = recursive_binary_search(collection, sizeof(collection) / collection[0], 4);
  printf(" has 5 in list --> %d", answer); // True
  answer = recursive_binary_search(collection, sizeof(collection) / collection[0], 4);
  printf(" has 5 in list --> %d", answer); // False
}

int rGCF(int a, int b)
{
  if (a == 0)
    return b;
  return rGCF(b % a, a);
}

int tarai(int x, int y, int z)
{
  if (x <= y)
    return y;
  return tarai(tarai(x - 1, y, z), tarai(y - 1, z, x), tarai(z - 1, x, y));
}

void tarai_test()
{
  int answer = tarai(10, 2, 9);
  printf("%d", answer);
}

void in_order_subset_remove_string(const char *str, unsigned index, int remove_count, char *data)
{
  char buffer[128]; //128 bytes should be enough :)
  unsigned str_size = sizeof(str);
  unsigned counter = 0;
  unsigned int bufer_index = 0;
  char c;
  while (counter != str_size)
  {
    c = *(str + index);
    if (remove_count <= 0 && c)
    {
      memset(buffer + bufer_index++, c, 1);
      memset(buffer + bufer_index, 0, 1);
    }
    index = (index + 1) % str_size;
    remove_count--;
    counter++;
  }

  if (bufer_index > 0)
  {
    strcat(data, buffer);
    strcat(data, ",");
    printf(" %d ", index);
    printf(" %s \n ", buffer);
  }
}

char *inorder_subsets(const char *str, unsigned size)
{
  static char data[] = "";
  for (int rcount = 0; rcount < size + 1; rcount++)
  {
    if (rcount == 0)
    {
      strcat(data, str);
      strcat(data, ",");
    }
    else if (rcount == size)
    {
      strcat(data, "{}");
      strcat(data, ",");
    }
    else
    {
      for (int start_index = 0; start_index < size; start_index++)
      {
        in_order_subset_remove_string(str, start_index, rcount, data);
      }
    }
  }
  return data;
}

void inorder_subsets_test()
{
  char *answer = inorder_subsets("abc", 3);
  printf("%s\n", answer);
}

unsigned recursive_list_length(void *node)
{
  struct SLNode slnode;

  if (node == NULL)
    return 0;
  return 1 + recursive_list_length(((struct SLNode *)node)->next);
}

int got_any_grapes_helper(int collection[], unsigned size, unsigned curr_index, unsigned curr_max, unsigned *max)
{
  unsigned odd = curr_index * 2 + 1, even = curr_index * 2;
  if (curr_max > *max)
    *max = curr_max;

  if (odd < size)
    return got_any_grapes_helper(collection, size, curr_index + 1, curr_max + collection[odd], max);

  if (even < size)
    return got_any_grapes_helper(collection, size, curr_index + 1, curr_max + collection[even], max);
}

int got_any_grapes(int collection[], unsigned size)
{
  unsigned int max = 0;
  got_any_grapes_helper(collection, size, 0, 0, &max);
  return max;
}

int collatz_apalooza(unsigned num)
{
  if (num % 2 == 0)
    return num / 2;
  return 3 * num + 1;
}

void collatz_apalooza_test()
{
  int data = 5;
  for (int i = 5; i--;)
  {
    printf("[%d]", data);
    data = collatz_apalooza(data);
  }
  // 5 16 8 4 2 -- printed
}

unsigned word_count(char *word)
{
  unsigned count = 0;
  char *prev;

  if (word) {
    while (*word != '\0')
    {
      prev = word;

      if (*prev == 0)
        break;

      word++;
      count++;
    }
  }
  return count;
}

// unsigned word_count(const char *word)
// {
//   unsigned count = 0;
//   const char *prev;
//   while (*word != '\0')
//   {
//     prev = word;
//     if (*prev == 0)
//       break;
//     word++;
//     count++;
//   }
//   return count;
// }

unsigned collection_index = 0;
void telephone_words(const char **collection, const char *phone_number, int index, char *buffer)
{
  char digit;
  char str_buffer[5] = "";
  unsigned str_size = word_count(buffer);

  if (word_count(buffer) == telephone_words_MAX_WORD_LENGTH)
  {
    collection[collection_index] = buffer;
    collection[++collection_index] = "DEADBEEF";
    return;
  }

  digit = *(phone_number + index);

  if (digit == '-')
    strcat(str_buffer, "-");
  else if (digit == '0')
    strcat(str_buffer, "O");
  else if (digit == '1')
    strcat(str_buffer, "I");
  else if (digit == '2')
    strcat(str_buffer, "ABC");
  else if (digit == '3')
    strcat(str_buffer, "DEF");
  else if (digit == '4')
    strcat(str_buffer, "GHI");
  else if (digit == '5')
    strcat(str_buffer, "JKL");
  else if (digit == '6')
    strcat(str_buffer, "MNO");
  else if (digit == '7')
    strcat(str_buffer, "PQRS");
  else if (digit == '8')
    strcat(str_buffer, "TUV");
  else if (digit == '9')
    strcat(str_buffer, "WXYZ");
  else
    strcat(str_buffer, "\0");

  if (str_buffer)
  {
    for (char *ptr = str_buffer; *ptr != 0; ptr++)
    {
      char *clone = (char *)malloc(10); /* allocation heap data (persistent) */
      strncpy(clone, buffer, str_size); /* copy current string */
      clone[str_size] = *ptr;           /* append char */
      clone[str_size + 1] = '\0';       /* append NULL */
      telephone_words(collection, phone_number, index + 1, clone);
    }
  }
}

void telephone_words_test()
{
  const char *collection[300] = {"DEADBEEF"};
  char buffer[10] = "";
  telephone_words(collection, "818-2612", 0, buffer);
  for (int i = 0; collection[i] != "DEADBEEF"; i++)
  {
    printf(" %d  [%s] \n", i, collection[i]);
  }
}

void rising_squares_step(int stop_index, int num)
{

  if (num % 2 == 0)
  {
    if (num <= stop_index)
      return;
    printf("[%d]", num * num);
    return rising_squares_step(stop_index, num - 2);
  }
  else
  {
    if (num > stop_index)
      return;
    printf("[%d]", num * num);
    return rising_squares_step(stop_index, num + 2);
  }
}

void rising_squares(int num)
{
  rising_squares_step(num, 1);
  rising_squares_step(0, num - 1);
}

void rising_squares_test()
{
  rising_squares(5);
}

void binary_expansion(const char **collection, const char *bin_string)
{
  unsigned start_index = 0;
  unsigned len = word_count(bin_string) + 1; // tail char = null
  unsigned wr_index = 0;
  binary_expansion_helper(collection, &wr_index, bin_string, len, start_index, NULL);
  for (int i = 0; i < wr_index; i++)
    printf("%d  [%s]\n", i, collection[i]);
}

void binary_expansion_helper(const char **collection, unsigned *wr_index, const char *bin_string, const unsigned bin_string_len, unsigned index, char *str_buffer)
{
  char character;

  if (index == bin_string_len - 1)
  {
    str_buffer[index] = '\0'; /* add null end of string */
    collection[*wr_index] = str_buffer;
    (*wr_index)++;
    return;
  }

  if (str_buffer == NULL)
    str_buffer = (char *)malloc(bin_string_len); /* char vector allocation*/

  character = bin_string[index];

  if (character == '?')
  {
    char *str_buffer_one = (char *)malloc(bin_string_len);
    for (int i = 0; i < 2; i++)
    {
      char *str_buffer_copy = (char *)malloc(bin_string_len); /* char vector allocation*/
      memcpy(str_buffer_copy, str_buffer, bin_string_len);    /* copy input string to copy variable*/
      str_buffer_copy[index] = (i) ? '0' : '1';               /* possible expansion */
      binary_expansion_helper(collection, wr_index, bin_string, bin_string_len, index + 1, str_buffer_copy);
    }
  }
  else
  {
    str_buffer[index] = character;
    return binary_expansion_helper(collection, wr_index, bin_string, bin_string_len, index + 1, str_buffer);
  }
}

void binary_expansion_test()
{
  const char *collection[1000];
  binary_expansion(collection, "1?0??");
  /* solution
    string buffer 1101
    string buffer 1100
    string buffer 1001
    string buffer 1000
  */
}

void anagram_helper(const char **collection, unsigned *wr_index, unsigned string_max_len, const char *string, char *buffer)
{
  unsigned string_len = word_count(string);
  unsigned buffer_len;
  char c;


  if (buffer == NULL)
    buffer = (char *)malloc(string_len +1);

  buffer_len = word_count(buffer);

  if (string_len == 0) {
    collection [ (*wr_index)++ ] = buffer;
   return;
  }

  for (int i = 0; i < string_len; i++)
  {
    c = string[i];

    /* shrink string */
    {
      char *mutate_string = (char *) malloc(string_len +1);  /* allocate char vector */
      int index = 0;
      for (int k = 0; k < string_len; k++) {
        if (k != i) {                                     /* omit c(i index)*/
          mutate_string[index++] = string[k];
        }
        mutate_string[index] = '\0';
      }

    // /* expand buffer */
      char *expand_string = (char *)malloc(string_max_len +1);
      memcpy(expand_string, buffer, buffer_len + 2); /* chars + null */
      expand_string[buffer_len] = c;
      expand_string[buffer_len + 1] = '\0';

      anagram_helper(collection,wr_index, string_max_len, mutate_string, expand_string);
      free(mutate_string);
    }
  }
}

 struct anagram_data anagram(const char *string)
{
  static unsigned wr_index  = 0;
  static struct anagram_data data = {.collection = NULL};

  if (data.collection != NULL)
    free(data.collection);
  data.word_size = word_count(string);
  data.array_size = recursive_factorial(data.word_size);
  data.collection = (const char**) malloc(data.array_size * sizeof(const char**)); /* allocate array of strings */
  wr_index = 0;
  anagram_helper(data.collection, &wr_index,  data.word_size , string, NULL);
  return data;
}

void anagram_test()
{
  struct anagram_data data = anagram("lmi");
  for (int i = 0 ; i < data.array_size; i++)
    printf("%s/\n", data.collection[i]);
}

int int_array_t_sum(struct int_array_t *arr_element)
{
  int result = 0;

  if (arr_element) {
    for (int i = 0; i < arr_element->size; i++) {
      result += arr_element->data[i];
    }
  }
  return result;
}


  void print_int_array_t (struct  int_array_t *obj  )
  {
    printf(" size of array %d", obj->size);
    for (int i = 0; i < obj->size; i++) {
      printf( "   [ %d ] \n " , obj->data[i]  );
    }
    printf("\n");
  }

void climb_stairs_helper(const unsigned climb_count, struct int_array_t *element, struct int_vector_array_t *info)
{
  unsigned ele_count = element == NULL ? 0 : element->size;
  int curr_sum = int_array_t_sum(element);
  struct int_array_t *clone;


  if (curr_sum >= climb_count) {
    if (curr_sum == climb_count) {
      info->size++;

      if (info->array_vector == NULL)
        info->array_vector = (struct int_array_t **)  malloc ( sizeof(struct int_array_t *));   /* allocate vector of array elements */

      info->array_vector = realloc( info->array_vector,  info->size * sizeof(struct int_array_t *));

      info->array_vector[info->size - 1] = element;
    }
    return;
  }

  for (int  i = 1; i < 3; i++)
  {
    clone = (struct int_array_t *) malloc( sizeof(struct int_array_t) *  (ele_count + 1)  );  /* allocate new array element */
    clone->size = ele_count + 1;

    clone->data =  (int *) malloc( sizeof(int) *  clone->size ) ;  /* allocate unsigned array */
    if (element)
      memcpy(clone->data, element->data, ele_count * sizeof(int) * ele_count );    /* cpy input array element to clone*/

    clone->data[ele_count] = i;

    climb_stairs_helper(climb_count, clone, info);
  }
 }

struct int_vector_array_t climb_stairs(const unsigned climb_count)
{
  static struct int_vector_array_t info = {.size = 0, .array_vector = NULL};
  climb_stairs_helper(climb_count, NULL, &info);

  for (unsigned i = 0; i < info.size; i++) {      /* iterate list of array structures */
    struct int_array_t *array_element = info.array_vector[i];

    for (int k = 0; k < array_element->size; k++) {   /* print array elements */
      printf("[%d]", array_element->data[k]);
    }

    printf("\n");
  }
  return info;
}

void climb_stairs_test()
{
  climb_stairs(4);
}


void square_sum_helper( const unsigned num, int start, struct int_vector_array_t *info , struct int_array_t *array)
{
  struct int_array_t *clone;
  unsigned curr_size = array == NULL ? 0 : array->size;
  int array_sum = int_array_t_sum(array);

  if (array_sum >= num) {
    if (array_sum == num) {

      if (info->size == 0)
        info->array_vector = (struct int_array_t **) malloc( sizeof (struct int_array_t *));
      info->array_vector = realloc(info->array_vector, sizeof(struct int_array_t *) * (info->size + 1) );
      info->array_vector[info->size] = array;
      info->size++;
      return;
    }
    free (array);
    return;
  }


  for (int  i = start; i < num; i++) {
    /* allocate array structure */
    clone = (struct int_array_t *) malloc( sizeof(struct int_array_t) );
    clone->size = curr_size + 1;

    /* allocate array */
    clone->data = (int *) malloc(sizeof(int) * clone->size);

    /* copy element data to clone */
    if (array)
      memcpy(clone->data, array->data , sizeof(int) * curr_size);

    /* append(assign) number to array */
    clone->data[curr_size] = i*i;
    /*recursion */
    square_sum_helper(num, start + 1, info, clone);
  }
}

struct int_vector_array_t  square_sum( const unsigned num )
{
  struct int_vector_array_t vector  = {.size = 0, .array_vector = NULL};
  square_sum_helper(num, 1, &vector, NULL);
  return vector;
}

void square_sum_test()
{
  struct int_vector_array_t result  =  square_sum(30);
  struct int_array_t *array;

  for (int i = 0; i < result.size; i++) {
    array = result.array_vector[i];
    print_int_array_t(array);

 }
}

int valid_paren (const char * string)
{
  int opem_brace_count = 0;
  char c;

  for (int i = 0;  *(string + i) != 0; i++)
  {
    c = *(string + i);

    if (c == '(')
      opem_brace_count++;

    if (c == ')')
      opem_brace_count--;

    if (opem_brace_count < 0)
      return 0;
  }

  return (opem_brace_count == 0);
}

void valid_n_pair_paren_helper(const unsigned num,  char * buffer, struct const_char_array_t *obj )
{
  unsigned int str_len = word_count(buffer);
  unsigned paren_len = (int) pow(2, num ) ;
  char pair [2] = { '(', ')'};
  char *clone;
  char c;

  if ( str_len >=  paren_len)
  {
    if (valid_paren(buffer) && str_len == paren_len) {
      if (obj->collection == NULL)
        obj->collection = (const char **) malloc (sizeof(const char *) );

      obj->collection  = realloc(obj->collection, sizeof(const char *) * (obj->size + 1));
      obj->collection[ obj->size] = buffer;
      obj->size++;
      return;
    }
    free(buffer);
    return;
  }

  for (int k = 0; k < 2; k++)
  {
    c = pair[k];
    clone = ( char *) malloc ( sizeof( char)  * (str_len + 1)  );
    if (buffer )
      memcpy(clone , buffer, sizeof( char) * str_len );
    clone[str_len] = c;
    valid_n_pair_paren_helper(num, clone, obj);
  }

}

struct const_char_array_t  valid_n_pair_paren (unsigned num)
{
  struct const_char_array_t  result = {.size = 0, .collection= NULL};
  valid_n_pair_paren_helper(num, NULL, &result);
  return result;
}

valid_n_pair_paren_test()
{
   struct const_char_array_t  result  = valid_n_pair_paren(2);
   for (int i = 0 ; i < result.size; i++) {
    printf( "[%s]\n", result.collection[i] );
   }
}

struct disks *disk_allocate(int value)
{
  struct disks *node = (disks *) malloc(sizeof(disks));
  node->next = NULL;
  node->value = value;
  return node;
}

void print_disk(struct pole *pole)
{
  struct disks *disk_list;

  if (pole == NULL)
    return;

  disk_list = pole->disk_list;
  printf("DISK[%d]: \t", pole->size);
  while (disk_list) {
    printf( " [%d]", disk_list->value);
    disk_list = disk_list->next;
  }
  printf("\n");

}

void print_tower(struct pole *pole, unsigned size)
{
  disks *runner;
  struct pole *p;

  for (int i = 0 ; i < size; i++)
  {
    printf("TOWER %d \n", i);
    p = (pole + i);
    print_disk(p);
  }
  printf("---------------\n");
}

void tower_of_hanoi_insert(struct pole *pole, int value)
{
   struct disks *node;
  if (pole) {

    node = disk_allocate (value);

    if (pole->disk_list == NULL) {
      pole->disk_list = node;
      ++pole->size;
      return;
    } else {
      node->next = pole->disk_list;
      pole->disk_list = node;
      ++pole->size;
      return;
    }
    free(node);
  }
}

void tower_of_hanoi_copy_tower_state(struct pole *dest, struct pole *src, unsigned size)
{
  struct disks * disk = NULL;
  struct disks *runner_disk;
  struct pole *p, *dest_p;
  int *buffer = (int *) malloc (sizeof(int) *(size));
  unsigned index = 0;

  for (int i = 0; i < 3; i++) {
    p = (src + i) ;
    dest_p = (dest + i);
    index = 0;

    runner_disk = p -> disk_list;

    while (runner_disk) {
      buffer[ index++ ] = runner_disk->value;
      runner_disk = runner_disk->next;
    }

    while (index > 0) {
      tower_of_hanoi_insert(dest_p, buffer [ index - 1] );
      index = index - 1;
    }
  }

  free(buffer);
}


struct disks * tower_of_hanoi_pop( struct pole *pole )
{

 struct disks * disk = NULL;

  if (pole == NULL)
    return disk;

  if (pole->disk_list == NULL)
    return disk;

  --(pole->size);
  disk = pole->disk_list;
  pole->disk_list = pole->disk_list->next;

  return disk;
};


int tower_of_hanoi_move_disk (struct pole *tower, unsigned dest_sel, unsigned  src_sel)
{
  struct pole *src = tower + src_sel;
  struct pole *dest = tower + dest_sel;

  if (src == NULL || dest == NULL)
    return 0;

  if (dest_sel == src_sel)
    return 0;

  if (src->size == 0)
    return 0;

  if ( dest->size == 0 )
  {
    tower_of_hanoi_insert(dest, tower_of_hanoi_pop(src)->value );
    return 1;
  }
  else if (dest->disk_list->value > src->disk_list->value)
  {
    tower_of_hanoi_insert(dest, tower_of_hanoi_pop(src)->value);
    return 1;
  }

  return 0;
}

void tower_of_hanoi_buffer_poles_add (struct pole_list **collection, struct pole *poles)
{
  struct pole_list *runner;
  struct pole_list *node;

  if (collection == NULL || poles == NULL)
    return;

  /* new list element */
  node = (struct pole_list *) malloc ( sizeof(struct pole_list));
  node -> curr_poles = poles;
  node -> next = NULL;

  if (*collection == NULL) /* addr of pointer points to NULL */
  {
    *collection = node;
    return;
  }
  else
  {
    runner = *collection;
    while (runner->next)
      runner = runner->next;
    runner->next = node;
  }
}

int tower_of_hanoi_compare_poles(struct pole *a, struct pole *b, unsigned size)
{
  disks *data_a, *data_b;

  if (a == NULL || b == NULL)
  {
    return 0;
  }

  for (int i = 0; i < size; i++)
  {
    if ((a + i )->size != (b + i)->size )
    {
      return 0;
    }

    data_a = (a + i ) -> disk_list;
    data_b = (b + i ) -> disk_list;

    while (data_a)
    {
      if (data_a->value != data_b->value)
      {
        return 0;
      }
      data_a = data_a->next;
      data_b = data_b->next;
    }
  }

  return 1;

}


unsigned  tower_of_hanoi_buffer_has_pole(struct pole_list **collection, struct pole *poles, unsigned size)
{
  struct pole_list *runner;

  if (*collection == NULL)
    return 0;

  runner = *collection;

  while (runner)
  {
    if ( (tower_of_hanoi_compare_poles(runner->curr_poles, poles, size)) )
    {
      return 1;
    }
    runner = runner->next;
  }

   return 0;

}

void tower_of_hanoi_helper(unsigned size, unsigned *search_count, unsigned iteration, struct pole *poles, struct pole_list **collection )
{
  struct pole *a = poles, *b = poles + 1, *c = poles + 2;
  struct pole *clone_pole, *clone_ptr;

  if (*search_count != 0)
    return;
    // free(poles); /* possible leaks TODO */

  if (tower_of_hanoi_buffer_has_pole(collection, poles, size)) /* pole found in list */
  {
    return;
  }
  else
  {
    tower_of_hanoi_buffer_poles_add(collection, poles); /* store pole in list */
    printf("\t added pole\n");
    print_tower(poles, size);
    printf("\t added pole end \n");
  }

  if ( c->size == size ) {
    printf("COMPLETE  %d  %d \n ", iteration, *search_count);
    *search_count = iteration;
    print_tower(poles, size);
    return;
  }

  /* pop  A pole */
  if (a->size > 0 ) {
    for (int sel = 0; sel < 3; sel++)
    {
      clone_pole = (struct pole *) malloc( sizeof( struct pole) * 3) ;
      tower_of_hanoi_copy_tower_state(clone_pole, poles, size);
      clone_ptr = clone_pole + sel;

      if ( tower_of_hanoi_move_disk(clone_pole, sel, 0)) {
        tower_of_hanoi_helper(size, search_count, iteration + 1, clone_pole, collection);
      }
    }
  }

  /* pop  B pole */
  if (b->size > 0) {
    for (int sel = 0; sel < 3; sel++)
    {
      clone_pole = (struct pole *) malloc( sizeof( struct pole) * 3);
      tower_of_hanoi_copy_tower_state(clone_pole, poles, size);
      clone_ptr = clone_pole + sel;

      if ( tower_of_hanoi_move_disk(clone_pole, sel, 1)) {
        tower_of_hanoi_helper(size, search_count, iteration + 1, clone_pole, collection);
      }
    }
  }

  /* pop C pole */
  if (c->size > 0 ) {
    for (int sel = 0; sel < 3; sel++)
    {
      clone_pole = (struct pole *) malloc( sizeof( struct pole) * 3) ;
      tower_of_hanoi_copy_tower_state(clone_pole, poles, size);
      clone_ptr = clone_pole + sel;

      if ( tower_of_hanoi_move_disk(clone_pole, sel, 2) ) {
        tower_of_hanoi_helper(size, search_count, iteration + 1, clone_pole, collection);
      }
    }
  }
}

int tower_of_hanoi (const unsigned size)
{
  struct pole *poles = (struct pole *) malloc ( sizeof (struct pole) * size);

  int count = 0;
  unsigned steps_to_solve = 0 ;
  struct pole_list *ptr_pole_list = NULL;

  for (int i = 0; i < size; i++) {
    (poles + i )->disk_list = NULL;
    (poles + i )->size = 0;
  }

  for (int i = size; i > 0; i--) {
    tower_of_hanoi_insert(poles, i);
  }

  tower_of_hanoi_helper(size, &steps_to_solve, count, poles, &ptr_pole_list);
  return steps_to_solve;
}

int tower_of_hanoi_test ()
{
  int total_steps = tower_of_hanoi(3);
  printf("total steps to move disk to far-right pole  = %d\n", total_steps);
}

void ip_address_buffer_deep_copy(int * dest, int * src)
{
  if (dest == NULL)
  {
    return;
  }

  for (int i = 0; i < IP_ADDRESS_BUFFER_SIZE; i++)
  {
    if (src == NULL)
    {
      dest[i] = 0;
    }
    else
    {
      dest[i] = src[i];
    }
  }
}
boolean ip_address_add(char * address, struct ip_address_list **collection)
{
  struct ip_address_list *list = (struct ip_address_list*) malloc (sizeof(struct ip_address_list));

  list->addr = address;
  list->next = NULL;

  if (*collection == NULL)
  {
    *collection = list;
  }
  else
  {
    list->next = *collection;
    *collection = list;
  }
}

unsigned ip_address_buffer_sum (int *buffer)
{
  unsigned sum = 0;

  if (buffer == NULL)
  {
    return sum;
  }

  for (int i = 0; i < IP_ADDRESS_BUFFER_SIZE; i++)
  {
    sum += buffer[i];
  }
  return sum;
}

char *ip_address_construct(const char *digits, const unsigned size, int *buffer)
{
  int len = size + 3 + 1; /* size +  {dots} + {"\0"}*/
  char * ip_address  = ( char *) malloc(sizeof( char) * (len)  );
  unsigned ip_address_pos = 0;
  unsigned digits_pos = 0;

  for (int buffer_index = 0; buffer_index < IP_ADDRESS_BUFFER_SIZE; buffer_index++)
  {
    while (buffer[buffer_index])
    {
      ip_address[ip_address_pos++] = digits[digits_pos++];
      --buffer[buffer_index];
    }
    if (buffer_index < IP_ADDRESS_BUFFER_SIZE - 1)
    {
      ip_address[ip_address_pos++] =  '.' ;
    }
  }
  return ip_address;
}

void ip_address_helper ( const char * digits, const unsigned size, struct ip_address_list **collection, int *buffer, unsigned index)
{
  int *clone_buffer;
  unsigned curr_sum = ip_address_buffer_sum(buffer);
  char * addr;

  if (index == 4)
  {
    if (curr_sum == size)
    {
      addr = ip_address_construct(digits, size, buffer);
      ip_address_add(addr, collection);
    }
    return;
  }
  else if (curr_sum > size)
  {
    return;
  }

  for (int i = 1; i <= 3; i++)
  {
    clone_buffer = (int *) malloc(sizeof(int) *IP_ADDRESS_BUFFER_SIZE);
    ip_address_buffer_deep_copy(clone_buffer, buffer);
    clone_buffer[index] = i;
    ip_address_helper(digits, size, collection, clone_buffer, index + 1);
  }
}

struct ip_address_list * ip_address (char * digits )
{
  struct ip_address_list *collection = NULL;
  unsigned string_count = 0;
  const int data[3] = {1, 2, 3};
  char *ptr;


  ptr = digits;

  while (*ptr != 0)
  {
    string_count++;
    ptr++;
  }

  ip_address_helper ( digits, string_count, &collection, NULL, 0);
  return collection;
}

void ip_address_test()
{
  struct ip_address_list *runner;
  /* print results */
  runner = ip_address("255255255");
  while (runner)
  {
    printf( " [ %s] \n", runner->addr );
    runner = runner->next;
  }
}

int uneven_digits_helper( int number,  boolean is_neg,  int index)
{
  int digit;
  int factor;
  int data = 0;

  if (index == 0 && number < 0)
  {
    is_neg = False;
    number = number * -1;
  }

  if (number <= 0)
  {
    return 0;
  }

  digit =  number % 10;

  if (digit % 2 == 0)
  {
    data =   0 + uneven_digits_helper( number / 10, is_neg, index + 1);
  }
  else
  {
    data =  digit*pow(10, index) + uneven_digits_helper(number / 10, is_neg, index + 1);
  }

  if (index == 0 && is_neg)
  {
    data = data * -1;
  }

  
  printf("data %d", data);

  return data;
}

int uneven_digits(int number)
{
  return uneven_digits_helper(number, -1, 0);
}

void uneven_digits_test()

{
  int data = uneven_digits(79);
  printf("[data %d]\n", data);
}

int main()
{
  uneven_digits_test();
}