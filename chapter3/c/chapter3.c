#include <stdio.h>
#include <stdlib.h>
#include "chapter3.h"



SLQueue *slQueue () 
{
  SLQueue *queue = (SLQueue *) malloc(sizeof(SLQueue));
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;
  return queue;
}

SLNode *slNode(int val)
{
  SLNode *node = (SLNode*) malloc(sizeof(SLNode));
  node->next = NULL;
  node->value = val;
  return node; 
}

void enqueue(SLQueue *queue, int val) 
{
  SLNode *node = slNode(val);
  if (queue->size == 0) {
    queue->head = node ;
    queue->tail = node;
    queue->size++;
  } else {
    ((SLNode*)queue->tail)->next = node;
    queue->tail = (SLNode*) node; 
  }
}

data_ret dequeue(SLQueue *queue)
{
  data_ret data;
  data.valid = False;
  SLNode *node = (SLNode*)queue->head; 
  if (node) {
    queue->size--;
    queue->head = node->next;
    data.valid = !data.valid;
    data.value = node->value;
    free(node);
  }
  return data;
}

boolean contains(SLQueue *queue, int value)
{
  SLNode *node = queue->head;
  
  while (node) {
    if (node->value == value)
      return True;
    node = node->next;
  }
  return False;
}

data_ret front(SLQueue *queue) 
{
  data_ret data;
  if (queue->head) {
    data.valid = True;
    data.value = ((SLNode*)queue->head)->value;
  }
  display_data(data);
  return data;
}

boolean empty(SLQueue *queue) 
{
  return (queue->head == NULL) ? True : False;
}

unsigned int size(SLQueue *queue) 
{
  return queue->size;
}

boolean compareQueues(SLQueue *queueA, SLQueue *queueB)
{
  SLNode *a = queueA->head;
  SLNode *b = queueB->head;
  while (a) {
    if (!b) 
      return False;
    if (a->value != b->value) 
      return False;
    a = a->next;
    b = b->next;
  }
  return True;
}

void removeMinimum(SLQueue *queue)
{
  SLNode *node = queue->head;
  SLNode *minNode = NULL;
  SLNode *runner, *runner_prev;
  SLNode *tmp; 
  
  /* Find min */
  while (node) {
    if (minNode == NULL)
      minNode = node;
    if (node->value < minNode->value) 
      minNode = node;
    node = node->next;
  }

/* Remove minimums */
  if (minNode) {
    runner_prev = minNode;
    runner = minNode->next;
    while (runner) {
      if (runner->value == minNode->value) {
        tmp = runner;
        runner_prev->next = tmp->next;
        runner = tmp->next;
        free(tmp);
      } else {
        runner_prev = runner;
        runner = runner->next;
      }
    }
  }
}


void removeMinimumLastMin(SLQueue *queue)
{
  SLNode *node = queue->head, *node_prev;
  SLNode *minNode_prev = NULL;
  SLNode *minNode = NULL;
  SLNode *tmp; 
  
  /* Find min */
  while (node) {
    if (minNode == NULL)
      minNode = node;
    if (node->value <= minNode->value) 
      minNode = node;
      minNode_prev = node_prev;
    node_prev = node; 
    node = node->next;
  }

/* Remove minimums */
  if (minNode) {
    tmp = minNode;
    if (minNode == queue->head) {
      queue->head = ( (SLNode*) queue->head)->next;        
    } else {
      minNode_prev->next = tmp->next;
    }
    free(tmp);
  }
}

void interleaveQueue (SLQueue *queue)
{
  SLNode *node = queue->head, *prev = NULL, *tmp;
  SLNode *curr = queue->head;
  int length = 0;

  /* cycle elements while referencing middle position (curr) */
  while (node) {
    if (length == 0) {
      curr = queue->head;
    } else if (length % 2 == 0) {
      prev = curr;
      curr = curr->next;
    }
    length++;
    node = node->next;
  }

  /* handle odd length */
  if (length %2 == 1) {
    prev = curr;
    curr = curr->next;
  }

  /* split(break) and mid point)*/
  prev->next = NULL;
  node = queue->head;

  while (curr) {
    tmp = curr;
    curr = curr->next;
    tmp->next = node->next;
    node->next = tmp;
    node = node->next->next;
  }
}


void display(SLQueue *queue)
{
  for (SLNode *ptr = (SLNode*)(queue->head); ptr; ptr = ptr->next) {
    printf("[%d]", ptr->value);
  }
  printf("\n");
}

int main(int argv, char **argc) {
  SLQueue *queue = slQueue();
  enqueue(queue, 23);
  enqueue(queue, 26);
  enqueue(queue, 28);
  enqueue(queue, 30);
  enqueue(queue, 2222);
  enqueue(queue, 1000000);
  enqueue(queue, 10100000);

  display(queue);
  interleaveQueue(queue);
  display(queue);

}