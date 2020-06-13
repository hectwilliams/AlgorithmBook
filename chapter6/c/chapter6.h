
typedef enum boolean {False, True} boolean;

typedef struct {
  boolean valid;
  int data;
} return_data;


typedef struct llnode{
  int val;
  struct llnode *next;
} llnode;

typedef struct SLQueue_t {
  void *head;
  void *tail;
} SLQueue_t;


llnode * ListNode(int value);
void sl_display (llnode *node);

SLQueue_t *Queue();
void SLQueue_enqueue(struct SLQueue_t *queue, int val);
return_data SLQueue_dequeue(struct SLQueue_t *queue);
return_data SLQueue_front(struct SLQueue_t *Queue);
boolean SLQueue_contains (struct SLQueue_t *queue, int val);
boolean SLQueue_isEmpty (struct SLQueue_t *queue);
int SLQueue_size (struct SLQueue_t *queue);
boolean SLQueue_compareQueues(struct SLQueue_t *queueA, struct SLQueue_t *queueB);
void SLQueue_removeMinimums(struct SLQueue_t *queue);
void SLQueue_interleave_queue(struct SLQueue_t *queue);
SLQueue_t SLQueue_queueUsingTwoStacks(struct SLQueue_t * queue);
boolean SLQueue_isPalindrome(struct SLQueue_t *queue);
void SLQueue_reorderAbsoluteQueue (struct SLQueue_t *queue);
void SLQueue_display (struct SLQueue_t *queue);

typedef struct StackArray_t {
  void * collection;
  int size;
} StackArray_t;

StackArray_t *Stack();
void ArrStack_push( StackArray_t *stack, int val);
return_data ArrStack_pop( StackArray_t *stack);
boolean ArrStack_contains(StackArray_t *stack, int val);
boolean ArrStack_isEmpty(StackArray_t *stack);
void ArrStack_display( StackArray_t *stack);
int ArrStack_size(StackArray_t *stack);

typedef struct SLStack_t {
  void *head;
  void *tail;
} SLStack_t;

SLStack_t *SLStack();
void SLStack_push(struct SLStack_t *stack, int val);
return_data SLStack_pop (struct SLStack_t *stack);
return_data SLStack_top (struct SLStack_t *stack);
boolean SLStack_contains(struct SLStack_t *stack, int val);
boolean SLStack_empty(struct SLStack_t *stack);
int SLStack_size(struct SLStack_t *stack);
boolean SLStack_compareQueues(struct SLStack_t *stackA, struct SLStack_t *stackB);
SLStack_t SLStack_copy(SLStack_t *stack);
void SLStack_removeStackMin(SLStack_t *stack);
void SLStack_partition(SLStack_t  *stack);
void SLStack_display(SLStack_t  *stack);
void SLStack_switchPairs(SLStack_t *stack);
void SLStack_mirror(SLStack_t *stack);
boolean SLStack_sorted (SLStack_t *stack);

typedef struct SLQueueTwoStacks_t {
  SLStack_t *stackA;
  SLStack_t *stackB;
} SLQueueTwoStacks_t;

SLQueueTwoStacks_t *SLQueueTwoStacks();
void SLQueueTwoStacks_enqueue(SLQueueTwoStacks_t *queue, int val);
return_data SLQueueTwoStacks_dequeue(SLQueueTwoStacks_t *queue);
void SLQueueTwoStacks_display(SLQueueTwoStacks_t *queue);

typedef struct CirQueue_t{
  void *head;
  void *tail;
  int capacity;
  int size;
  void *ptr;
} CirQueue_t;

CirQueue_t *CirQueue();
return_data CirQueue_front(CirQueue_t *queue);
void CirQueue_enqueue(CirQueue_t *queue, int val);
return_data CirQueue_dequeue(CirQueue_t *queue);
void CirQueue_print(CirQueue_t *queue);
boolean CirQueue_isEmpty(CirQueue_t *queue);
boolean CirQueue_contains(CirQueue_t *queue, int val);
boolean CirQueue_isFull(CirQueue_t *queue);
int CirQueue_size(CirQueue_t *queue);
int CirQueue_grow(CirQueue_t *queue, int size);
