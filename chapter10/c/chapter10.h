
typedef unsigned  uint32_t;
uint32_t string_len (const char * string);

char * rotate_string(char *string, unsigned n);

typedef enum boolean
{
  False,
  True
} boolean;

boolean ionis_rotate(char* str1, char * str2);
void bad_characters(char * str, char *bad_chars);
void censor_string (char * string, char  ** naughty_list, uint32_t size);
boolean genetic_marker (char *string, char **string_list, uint32_t size);
boolean genetic_marker_compare_string(char *str, char *marker, uint32_t size);

struct optimal_seq {
  boolean done;
  char ** data;
  uint32_t size;
};
struct optimal_seq optimal_sequence(char ** list, uint32_t list_size, uint32_t word_size);
void optimal_sequence_helper(char **list, const uint32_t list_size, uint32_t word_size, char **buffer, uint32_t col, struct optimal_seq  *obj);
void optimal_sequence_helper_helper_sort(char **list, char **buffer, uint32_t list_size, uint32_t word_size, uint32_t col);
boolean optimal_sequence_helper_helper_col_is_sorted(char **list, uint32_t list_size, uint32_t word_size, uint32_t col);
void optimal_sequence_helper_helper_sort_by_column(char **list, char **buffer, uint32_t list_size, uint32_t word_size, uint32_t col);
char ** optimal_sequence_helper_clone_list(char **list, uint32_t list_size, uint32_t word_size, boolean has_data);
void optimal_sequence_helper_swap( char **collection, int src_pos, int dest_pos , uint32_t length);
void optimal_sequence_helper_cpy(char ** dest, char ** src, uint32_t list_size, uint32_t word_size);

char * dedupe (const char * string);

int first_unique_letter_index (const char * msg);
char * unique_letters (const char * str);

char * num_to_string(double number);
void num_to_string_helper(double number, int k, char *buffer);


struct NumToTextStruct
{
  char decimals[25];
  char whole [16];
};

char * num_to_text(double number);
void num_to_text_helper(double number, struct NumToTextStruct *obj, int pos );
void num_to_text_helper_parser_natural(char * string, char *text );
void num_to_text_helper_parser_decimal(char * string, char *text );
void num_to_text_helper_translate(char *data,  unsigned width,  char *text);

boolean is_permtutaoin(const char *string, const char *perm);

void is_permtutaoin_helper ( char *string,  const char *perm,  char *buffer, boolean *done);

boolean is_pangram(const char *str);
int is_pangram_helper(const char *str, char * array);

struct str_permutations {
  char *data;
  struct str_permutations *next;
};

struct str_permutations all_string_permutations (const char *string);
void all_string_permutations_helper(const char *string, unsigned size, struct str_permutations **llist, char *buffer);

int perfect_pangram_helper(const char *str, char * alpha);
boolean perfect_pangram (const char *str);

int best_single_buy_sell (int *array, int size);
void best_single_buy_sell_helper  (int *array, int array_size, int *buffer, int buffer_size, int *max);

int best_single_buy_sell_second (int *array, int size);
void best_single_buy_sell_helper_second  (int *array, int array_size, int *buffer, int buffer_size, int *data);


boolean loosely_interleaved(const char * a, const char *b , const char *c);
boolean loosely_interleaved_helper(const char * a, const char *b, const char *c, char *buffer);


struct str_llist {
  char *data;
  struct str_llist *next;
};

struct str_llist *all_loosely_interleaved(const char *a, const char *b);
void all_loosely_interleaved_helper (const char *a, const char *b, char * buffer, struct str_llist **llist );
void all_loosely_interleaved_helper_clone(char *dest, char *src, int length);
void all_loosely_interleaved_helper_branch_search(char *a, int a_len,  char *b, char *buffer, int buffer_len, struct str_llist **llist);
void all_loosely_interleaved_helper_insert_interleave_data(char *data, struct str_llist **llist);

int make_string_palindrome_remove(const char * string);
int make_string_palindrome_remove_helper(const char *string, int exclude_index);