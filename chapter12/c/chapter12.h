
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
void bubble_sort_array(int *array, int size);
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
struct SList *mergeSort_list(struct SList *llist);
struct SList *partition_list(struct SList *llist);

int partition_array(int *collection, int size);
int partition_array_second(int *collection, int size);
int partition_array_third(int *collection, int size);
int partition_array_third_helper(int *collection,int start, int  end);

void quickSort(int *collection, int size);
void quickSort_helper(int *collection, int start, int end);

int*  partition_array_3 (int *collection, int size);

void mergeSort_array(int *collection, int size);


struct quicksort3_pivot  partition_array_3_third (int *collection, int size, int start, int end);
int * partition_array_3_second (int *collection, int size);

void quickSort3(int *collection, int size);
void quickSort3_helper(int *collection, int size, int start, int end);
struct quicksort3_pivot
{
  int start_index;
  int end_index;
};

void urbanDictionaryDailyAdd();
void pancakeSort(int *collection, int size);
void pancakeSort_flip(int *collection, int end_pos);

void radixSort(int *collection, int size);