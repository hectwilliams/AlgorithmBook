
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