#include <stdio.h>
#include <stdlib.h>
#include "chapter6.h"

llnode * ListNode(int value) 
{
  llnode *node = (llnode *) malloc(sizeof(llnode));
  node->val = value;
  node->next = (llnode *) NULL;  
  return node;
}

void sl_display (llnode *node) 
{
  while (node) {
    printf("[%d]", node->val);
    node = node->next;
  }
}

/* Queue */
SLQueue_t *Queue()
{
  SLQueue_t *queue = (SLQueue_t *) malloc(sizeof(SLQueue_t));
  queue->head = NULL;
  queue->tail = NULL;
  return queue;
}

void SLQueue_enqueue(struct SLQueue_t *queue, int val)
{
  llnode *node = ListNode(val);
  if (queue->head == NULL) {
    queue->head = node;
    queue->tail = node;
  } else {
    ((llnode*) queue->tail)->next =  node;
    queue->tail = node;
  }
}

return_data SLQueue_dequeue(struct SLQueue_t *queue) 
{
  return_data result;
  llnode *node = queue->head;
  llnode *buffer = NULL;

  result.valid = False; 
  
  if (node) {
    buffer = node;
    result.data = buffer->val;
    result.valid = True;

    if (buffer == queue->tail)
      queue->tail = NULL;

    queue->head = buffer->next;
    
    free(buffer);
  
  }
  return result;
}

return_data SLQueue_front(struct SLQueue_t *queue)
{
  return_data result;
  result.valid = False;
  if (queue->head) {
    result.data = ((llnode*) queue->head) ->val;
    result.valid = True;
  }
  return result;
}

boolean SLQueue_contains (struct SLQueue_t *queue, int val)
{
  llnode *node = queue->head;
  while (node) {
    if (node->val == val)
      return True;
    node = node->next;
  }
  return False;
}

boolean SLQueue_isEmpty (struct SLQueue_t *queue)
{
  return (queue->head == NULL) ? True : False;
}

int SLQueue_size (struct SLQueue_t *queue)
{
  int count = 0;
  llnode *node = queue->head;
  while (node) {
    count++;
    node = node->next;
  }
  return count;
}

boolean SLQueue_compareQueues(struct SLQueue_t *queueA, struct SLQueue_t *queueB)
{
  llnode *a = queueA->head;
  llnode *b = queueB->head;

  while (a) {
    if (!b) 
      return False;
    if (b->val != a->val)
      return False;
    b = b->next;
    a = a->next;
  }

  /* b should be NULL*/
  if (b) 
    return False;

  return True;
}

void SLQueue_removeMinimums(struct SLQueue_t *queue)
{
  llnode *node = queue->head, *prev= NULL, *tmp;
  llnode *minNode = NULL;

/* FIND MIN */
  while (node) {
    if (minNode == NULL) 
      minNode = node;
    else if (node->val < minNode->val) 
      minNode = node;    
    node = node->next;
  }

/* REMOVE MINS */
    node = queue->head;
    prev = NULL;

  while (node && minNode) {
    if (node->val == minNode->val) {
      tmp = node;
      node = node->next;

      if (prev == NULL) {
        queue->head = node;
      } else {
        prev->next = node;
      }

      if (tmp == queue->tail) {
        queue->tail = prev;
      }

    } else {
      prev = node;
      node = node->next;
    }
  }

}

void SLQueue_interleave_queue(struct SLQueue_t *queue)
{
  llnode *node = queue->head, *prev = NULL;
  llnode *curr = node;
  int count = 0;

  if (node == NULL)
    return;

  while (node) {
    if (count %2 == 0 && count!= 0) 
      curr = curr->next;
    count++;
    prev  = node;
    node = node->next;
  }

  node = queue->head;
  if (count %2 == 1) {
    prev = curr;
    prev->next = NULL;
    curr = curr->next;
  }

  /* Interleave process*/
  while (curr) {
    prev = curr;
    curr = curr->next;
    prev->next = node->next;
    node->next = prev;
    node = prev->next;
  }

}



/* Array */ 
 StackArray_t *Stack()
{
  StackArray_t *stack =  malloc(sizeof(StackArray_t));
  stack->collection = malloc(sizeof(int));
  stack->size = 0;
  return stack;
}

void ArrStack_push(struct StackArray_t *stack, int val) 
{
  realloc(stack->collection ,stack->size + 1);
  *( (int*) stack->collection + stack->size++ ) = val;
}

return_data ArrStack_pop( StackArray_t *stack)
{
  return_data result;
  if (stack->size > 0) {
    result.valid = True;
    result.data =  *((int*) stack->collection + (stack->size--));
    realloc(stack->collection, stack->size);
  }
  return result;
}

boolean ArrStack_contains(StackArray_t *stack, int val)
{
  int data;
  for(int i = 0; i < stack->size; i++) {  
    data = *((int*) stack->collection + i);
    if (data == val) {
      return True;   
    }
  }
  return False; 
}

void ArrStack_display(struct StackArray_t *stack)
{
  for(int i = 0; i < stack->size; i++) {  
    printf("hello world %d",  *((int*) stack->collection + i) );
  }
}

boolean ArrStack_isEmpty(StackArray_t *stack)
{
  return (stack->size == 0) ? True : False;
}

int ArrStack_size(StackArray_t *stack)
{
  return stack->size;
}

SLStack_t *SLStack()
{
  SLStack_t *stack = malloc(sizeof(SLStack_t));
  stack->head = NULL;
  return stack;
}

void SLStack_push(struct SLStack_t *stack, int val)
{
  llnode *node = ListNode(val);
  
  if (stack->head == NULL) {
    stack->head = node;
    stack->tail = node;
  } else {
    ((llnode*)stack->tail)->next = node;
    stack->tail = node;
  }
}

return_data SLStack_pop (struct SLStack_t *stack)
{
  return_data result;
  llnode *node = stack->head, *prev = NULL;
  llnode *buffer = NULL;

  result.valid = False;

  if ( ((llnode *)(stack->head) )->next == NULL) {
    buffer = node;
    stack->head = ((llnode*) stack->head)->next;  
  } else {
    while (node->next != stack->tail ) {
      node = (llnode*) node->next;
    }
    stack->tail = node;
    buffer = node->next;
    node->next = buffer->next;
  }

  if (buffer) {
    result.data = buffer->val;
    result.valid = True;
    if (stack->head == buffer) {
      stack->tail = NULL;
      stack->head = NULL;
    }
  }

  return result;
}

return_data SLStack_top (struct SLStack_t *stack)
{
  return_data result;
  result.valid = False;
  llnode *node = stack->head;
  
  if (!node) {
    return result;
  }

  while (node->next) {
    node = node->next;
  }

  result.data = node->val;
  result.valid = True;

  return result;
}

boolean SLStack_contains(struct SLStack_t *stack, int val)
{
  llnode *node = stack->head;

  while (node) {
    if (node->val == val)
      return True;
    node = node->next;
  }
  return False;
}

boolean SLStack_empty(struct SLStack_t *stack)
{
  return (stack->head == NULL) ? True : False;
}

int SLStack_size(struct SLStack_t *stack)
{
  int count = 0;
  llnode *node = stack->head;
  while (node) {
    count++;
    node = node->next;
  }
  return count;
}

boolean SLStack_compareQueues(struct SLStack_t *stackA, struct SLStack_t *stackB)
{
    
  llnode *a = stackA->head;
  llnode *b = stackB->head;

  while (a) {
    if (!b) 
      return False;
    if (b->val != a->val)
      return False;
    b = b->next;
    a = a->next;
  }

  /* b should be NULL*/
  if (b) 
    return False;

  return True;
}

SLStack_t SLStack_copy(SLStack_t *stack)
{
  SLQueue_t *queue = Queue();
  SLStack_t stack_result;
  return_data plucked_obj;

  stack_result.head = NULL;
  stack_result.tail = NULL;
  int count = 0;

  while (SLStack_size(stack)) {
    count++;
    SLQueue_enqueue(queue, SLStack_pop(stack).data);
  }

  while (SLQueue_size(queue)) {
    for (int i = count; i > 0; i--) {
      /* rotate */
      for (int j = 0; j < count - 1; j++) {
        plucked_obj = SLQueue_dequeue(queue);
        SLQueue_enqueue (queue, plucked_obj.data );
      }
      
      /* pluck front of queue*/
      plucked_obj = SLQueue_dequeue(queue);
      
      /*insert values to stack(s)*/
      SLStack_push(stack, plucked_obj.data);
      SLStack_push(&stack_result, plucked_obj.data);
    }
  }

  return stack_result;
}

SLQueueTwoStacks_t *SLQueueTwoStacks()
{
  SLQueueTwoStacks_t *stack = (SLQueueTwoStacks_t*) malloc(sizeof(SLQueueTwoStacks_t));
  stack->stackA = SLStack();
  stack->stackB = SLStack();
  return stack;
}

void SLQueueTwoStacks_enqueue(SLQueueTwoStacks_t *queue, int val)
{
  return_data retData;

  while (SLStack_size(queue->stackB)) {
    retData = SLStack_pop(queue->stackB);
    SLStack_push(queue->stackA, retData.data);
  }
  SLStack_push(queue->stackA, val);
}

return_data SLQueueTwoStacks_dequeue(SLQueueTwoStacks_t *queue)
{
  return_data retData;
  return_data resultData =  {.valid = False, .data = 0x0};
  
  while (SLStack_size(queue->stackA)) {
    SLStack_push(queue->stackB, SLStack_pop(queue->stackA).data);
  }
  if (SLStack_size(queue->stackB))
    resultData = SLStack_pop(queue->stackB);
  
  return resultData;
}

boolean SLQueue_isPalindrome(struct SLQueue_t *queue)
{
  SLStack_t *stack = SLStack();
  boolean result = True; 
  int queue_length = SLQueue_size(queue);
  int val;
  return_data retData;

  for (int i = 0; i < queue_length; i++) {
    retData = SLQueue_dequeue(queue);
    SLStack_push(stack, retData.data);
    SLQueue_enqueue(queue, retData.data);
  }

  for (int i = 0; i < queue_length; i++) {
    retData = SLQueue_dequeue(queue);
    if (retData.data != SLStack_pop(stack).data) {
      result *= False; 
    }
    SLQueue_enqueue(queue, retData.data);
  }
  return result;
}

void SLQueue_display (struct SLQueue_t *queue)
{
  llnode *node = queue->head;

  while (node) {
    printf("[%d]", node->val);
    node = node->next;
  }
}

void SLQueue_reorderAbsoluteQueue (struct SLQueue_t *queue)
{
  SLStack_t *stack = SLStack();
  return_data stackData, queueData;
  int count = 0;
  int minimum;

  /* queue  using size */
  while (SLQueue_size(queue)) {
    
    /*find min */
    for (int i = 0; i<  SLQueue_size(queue) ;i++) {
      if (i == 0)
        minimum = SLQueue_front(queue).data;
      else if (SLQueue_front(queue).data > minimum)
        minimum = SLQueue_front(queue).data;
      queueData = SLQueue_dequeue(queue);
      SLQueue_enqueue(queue, queueData.data);
    }
    
    /* remove  min */
    while (SLQueue_front(queue).data != minimum) {
      queueData = SLQueue_dequeue(queue);
      SLQueue_enqueue(queue, queueData.data);
    }
    SLStack_push(stack,  SLQueue_dequeue(queue).data);
  }
  
  /* move stack elements to queue*/
  while (SLStack_size(stack)) {
    SLQueue_enqueue(queue, SLStack_pop(stack).data);
  }
}

void SLStack_partition(SLStack_t  *stack)
{
  SLQueue_t *queue = Queue();
  int count = 0;
  return_data queueData;

  /*move stack elements to queue*/
  while (SLStack_size(stack))
    SLQueue_enqueue(queue, SLStack_pop(stack).data);

  count = SLQueue_size(queue);
  /* move positive numbers to Stack*/
  for (int i = 0; i <  count; i++) {
    queueData = SLQueue_dequeue(queue);
    if (queueData.data >= 0) {
      SLStack_push(stack,  queueData.data);
    } else {
      SLQueue_enqueue(queue, queueData.data );
    }
  }  

  /* move remaining negative numbers to Stack*/
  while (SLQueue_size(queue))
    SLStack_push(stack, SLQueue_dequeue(queue).data);
}

void SLStack_switchPairs(SLStack_t *stack)
{
  SLQueue_t *queue = Queue();
  return_data queueData, data1, data2;
  int count = 0;
  
  while (SLStack_size(stack))
    SLQueue_enqueue(queue, SLStack_pop(stack).data);
  
  while (SLQueue_size(queue) ) {
    count = SLQueue_size(queue) - 2;
    for (int i = 0; i < count; i++) {
      queueData = SLQueue_dequeue(queue);
      SLQueue_enqueue(queue, queueData.data);
    }

    data1 = SLQueue_dequeue(queue);
    data2 = SLQueue_dequeue(queue);
    
    if (data1.valid)
      SLStack_push(stack, data1.data);
  
    if (data2.valid)
      SLStack_push(stack, data2.data); 
  }
}

void SLStack_mirror(SLStack_t *stack)
{
  SLQueue_t *queue = Queue();
  int len = 0;
  return_data data; 

  while (SLStack_size(stack)) 
    SLQueue_enqueue(queue, SLStack_pop(stack).data);
  
  len = SLQueue_size(queue);
  
  for (int i = 0; i < len; i++) {
      data = SLQueue_dequeue(queue);
      SLStack_push(stack, data.data);
      SLQueue_enqueue(queue, data.data);
  }

  while (SLStack_size(stack)) 
    SLQueue_enqueue(queue, SLStack_pop(stack).data);

  while (SLQueue_size(queue)) 
    SLStack_push(stack, SLQueue_dequeue(queue).data);

}

boolean SLStack_sorted (SLStack_t *stack)
{
  SLStack_t *stackInner = SLStack();
  return_data retData, tmp;

  while (SLStack_size(stack)) 
  {
    retData = SLStack_pop(stack);
    SLStack_push(stackInner, retData.data);
    if (SLStack_size(stack)) {
      if (SLStack_top(stack).data < SLStack_top(stackInner).data)
        return False;
    }
  }

  while ( SLStack_size(stackInner) ) {
    retData = SLStack_pop(stackInner);
    SLStack_push(stack, retData.data);
  }
  return True;
}

void SLStack_display(SLStack_t  *stack)
{
  llnode *curr_tail = stack->tail;
  llnode *node = stack->head;

  while (1) {
    node = stack->head;
    if (curr_tail != stack->head) {
      while (node->next != curr_tail) {
        node = node->next;
      }
      printf("[%d]", node->next->val);
    } else {
      printf("[%d]", node->val);
      break;
    }
    curr_tail = node;
  }

  
}


void SLStack_removeStackMin(SLStack_t * stack)
{
  SLQueue_t *queue = Queue();
  int len = 0;
  int stack_len = SLStack_size(stack);
  int minimum;
  return_data retData;

  while (SLStack_size(stack)) {
    retData = SLStack_pop(stack);
    if (len == 0)
      minimum = retData.data;
    if (retData.data < minimum)
      minimum = retData.data;
    len++;
    SLQueue_enqueue(queue, retData.data);
  }

  for (int i = stack_len; i > 0; i--) {
    /*rotate*/
    for (int j = 0; j < stack_len - 1; j++) {
      retData = SLQueue_dequeue(queue);
      SLQueue_enqueue(queue, retData.data);
    }
    /*pluck front value - minimums are removed from stack*/
    retData = SLQueue_dequeue(queue);
    if (retData.data  !=  minimum) {
      stack_len--;
      SLStack_push(stack, retData.data);
    }
  }

}

void CirQueue_enqueue(CirQueue_t *queue, int val)
{
  llnode *node;
  
  if (queue->size < queue->capacity) {
    node = ListNode(val);
    if (queue->head == NULL) {
      queue->head = node;
      queue->tail = node;  
      queue->ptr = node;
    } else {
      ((llnode*)queue->tail)->next = node;
      queue->tail = node;
    }
    queue->size++;
  } else {
    if (queue->ptr == NULL)
      queue->ptr = queue->head;
    if (queue->ptr) {
      ((llnode*)queue->ptr)->val = val;
      queue->ptr = ((llnode*)queue->ptr)->next;
    }
  }
}

CirQueue_t *CirQueue(int cap)
{
  CirQueue_t *queue;
  queue->head = NULL;
  queue->tail = NULL;
  queue->capacity = cap;
  queue->size = 0;

  for (int i = 0; i < cap; i++) {
    CirQueue_enqueue(queue, 0);
  }
  return queue;
}

return_data CirQueue_dequeue(CirQueue_t *queue)
{
  return_data result = {.valid = False, .data = 0};
  llnode *node, *tmp; 

  if (queue->size == 0)
    return result;

  if (queue->head) {
    result.data = ((llnode*)queue->head)->val;
    result.valid = True;

    tmp = queue->head;
    node = ((llnode*)queue->head)->next;
    
    if (queue->head == queue->ptr) 
      queue->ptr = node ;
    
    if (node == NULL) {
      queue->tail = NULL;
    }

    queue->head = node;
    queue->size--;
    free(tmp);
  }

  return result;
}



return_data CirQueue_front(CirQueue_t *queue)
{
  return_data result = {.valid = False, .data = 0};
}

void CirQueue_print(CirQueue_t *queue)
{
  llnode* node = queue->head;
  while (node) {
    printf("[%d]", node->val);
    node = node->next;
  }
}

boolean CirQueue_isEmpty(CirQueue_t *queue)
{
  return (queue->head == NULL) ? True : False;
}

boolean CirQueue_contains(CirQueue_t *queue, int val)
{
  llnode *node = queue->head;
  while (node) {
    if (node->val == val) 
      return True;
    node = node->next;
  }
  return False;
}

boolean CirQueue_isFull(CirQueue_t *queue)
{
  return (queue->size == queue->capacity) ? True : False;
}

int CirQueue_size(CirQueue_t *queue)
{
  return queue->size;
}

int CirQueue_grow(CirQueue_t *queue, int size)
{
  llnode *runner = queue->head;
  llnode *node, *tmp;
  int len = 0;

  if (size < queue->capacity) {
    for (int i = 0; i < size - 1; i++) {
      runner = runner->next;
    }
    node = runner->next;
    runner->next = NULL;

    /* remove tmp list*/
    while (node) {
      tmp = node;
      node = node->next;
      free(tmp);
    }
    queue->size = size;
    queue->capacity = size;
  } else if (size > queue->capacity) {
    len = size - queue->capacity;
    queue->capacity = size;
    for (int i = 0; i < len; i++) {
      CirQueue_enqueue(queue, 0);
    }
  }
}


int main(int argv, char **argc) 
{
  
  SLStack_t *stack = SLStack();
  
  SLStack_push(stack, 7);
  SLStack_push(stack, 6);
  SLStack_push(stack, 5);
  SLStack_push(stack, 4);
  SLStack_push(stack, 3);
  SLStack_push(stack, 2);
  SLStack_push(stack, 1);
  
  printf("%d \n \n", SLStack_sorted(stack));
  SLStack_display(stack);

}