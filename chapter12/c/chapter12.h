

struct SList
{
  int value;
  struct SList *next;
};

struct SList *allocate_slist(int value);
void SList_add(int value, struct SList **node);
void SList_display();

/* LIST COMPONENTS ABOVE */


void bubbleSort_array(int *array, int size);
