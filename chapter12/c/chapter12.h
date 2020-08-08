
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


/*

      curr             sel
  5    4    3     2    1



  b = 1
  a = 5



  i

  s   sn

  4  5   3 2 1
        sn
*/