
struct SList
{
  int value;
  struct SList *next;
};

struct SList *allocate_slist(int value);
void SList_add(int value, struct SList **node);
void SList_display(struct SList **node);

/* LIST COMPONENTS ABOVE */

void swap(int *array, int i, int k);
void array_display(int *array, int size) ;
void bubbleSort_array(int *array, int size);
void selectionSort_array(int *array, int size);
void bubbleSort_list(struct SList ** head);

struct NameList
{
  const char * firstName;
  const char * lastName;
  struct NameList *next;
};

void multikey_sort (struct NameList **head);
void NameList_display(struct NameList **node);
void NameList_add(const char *firstName, const char *lastName, struct NameList **node);
struct NameList *allocate_namelist(const char *firstName, const char *lastName);



void insertionSort_array (int * array, unsigned size);
struct array_obj  combine_array(int * a, int a_size, int *b, int b_size);

struct array_obj
{
  int *array;
  int size ;
};


struct SList *combine_list  (struct SList *a, struct SList *b);
