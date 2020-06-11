#ifndef CHAPTER3_H
#define CHAPTER3_H

#define display_data(obj) \
  printf("\t valid:%d  data: %d", obj.valid, obj.value)

typedef enum boolean {False, True} boolean;

typedef struct SLNode{
  int value;
  struct SLNode *next;
} SLNode;

typedef struct SLQueue {
  void* head;
  void* tail;
  unsigned int size;
} SLQueue;

typedef struct {
  boolean valid;
  int value; 
} data_ret;

SLQueue *slQueue ();
SLNode *slNode(int val);

void display(SLQueue *queue);
void enqueue(SLQueue *queue, int val);
data_ret dequeue(SLQueue *queue);
boolean contains(SLQueue *queue, int value);
data_ret front(SLQueue *queue);
boolean empty(SLQueue *queue);
unsigned int size(SLQueue *queue);
boolean compareQueues(SLQueue *queueA, SLQueue *queueB);
void removeMinimum(SLQueue *queue);
void removeMinimumLastMin(SLQueue *queue);
void interleaveQueue (SLQueue *queue);

#endif
