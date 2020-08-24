
struct array_obj
{
  int *data;
  int size;
};

int * interleave_arrays(int * a, const int a_size, int *b, const int b_size);
int * merge_sorted_arrays (int *a, const int a_size, int *b, const int b_size);
struct array_obj intersect_sorted_arrays(int *a, const int sizeA, int *b, const int sizeB);
struct array_obj intersect_sorted_arrays_dedupe(int *a, const int sizeA, int *b, const int sizeB);
struct array_obj union_sorted_array (int *a, const int sizeA, int *b, const int sizeB, int (*callback)(int, int*, int, int*,int, int * )  );

struct array_obj union_sorted_array_dedupe (int *a, const int sizeA, int *b, const int sizeB);

struct array_obj intersect_unsorted_array_in_place (int *a, const int sizeA, int *b, const int sizeB);

struct array_obj intersect_unsorted_array (int *a, const int sizeA, int *b, const int sizeB);

struct array_obj union_unsorted_arrays  (int *a, const int sizeA, int *b, const int sizeB);

struct array_obj union_unsorted_arrays_in_place  (int *a, const int sizeA, int *b, const int sizeB);

struct PriQNode
{
  int value;
  int pri;
  struct PriQNode *next;
};

void PriQueue_display(struct  PriQNode **node);
void PriQueue_push(struct  PriQNode **node, int priority, int value);
struct  PriQNode *PriQueue_pop(struct  PriQNode **node);
