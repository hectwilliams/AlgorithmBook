#include <iostream>
#include <vector>
#include <queue>
#include <map>

#include "chapter8.h"

template <class T>
SLNode_t<T> *sl_node(const T &value)
{
  SLNode_t<T> *node = new SLNode_t<T>(value);
  return node;
}

template <class T>
SList_t <T> *sl_list()
{
  SList_t <T> *list = new SList_t <T> ();
  return list;
}

template <class T>
void SList_t<T>::pushFront(const T &value) 
{
  SLNode_t<T> *node = sl_node<T>(value);

  if (head == NULL) {
    head = tail = node;
  } else {
    node->next = head;
    head = node;
  }
}



template <class T>
ret_obj<T> SList_t<T>::popFront()
{
  ret_obj<T> data{false};
  SLNode_t<T> *node; 
  
  if (head == NULL) 
    return data;

  data.valid = true;
  data.value = head->value;
  node = head;
  
  if (head == tail  && tail == node) 
    tail = head = NULL;
  else 
    head = head->next;

  free(node); 
  return data;
}

template <class T>
void SList_t<T>::pushBack(const T &value)
{
  SLNode_t<T> *node = sl_node<T>(value);

  if (head == NULL) {
    head = tail = node;
  } else {
    tail->next = node; 
    tail = node;
  }
}

template <class T>
ret_obj<T> SList_t<T>::popBack()
{
  ret_obj<T> data {false};
  SLNode_t<T> *runner, *runner_prev;

  if (head == tail) 
    return data; 
  
  runner = head;
  data.valid = true;

  if (head == tail) {
    head = tail = NULL;
    data.value = runner->value; 
    delete(runner);
  } else {
    while (runner->next) {
      runner_prev = runner;
      runner = runner->next;
    }
    data.valid = runner->value;  
    free(runner);
    tail = runner_prev;
    runner_prev->next = NULL;
  }

  return data;
}


template <class T>
bool SList_t<T>::removeValue(const T &value)
{
  SLNode_t<T> *runner = head, *runner_prev = NULL, *tmp_node;

  while (runner) {
    if (runner->value == value) {
      tmp_node = runner;
      if (head == runner) {
        head = head->next;
        runner = head;
        runner_prev = NULL;
      } else {
        runner_prev ->next = runner->next;
        runner = runner_prev->next;
      } 

      if (tmp_node == tail) {
        tail = runner_prev;
      }
      free(tmp_node);
    } else {
      runner_prev = runner;
      runner = runner->next;
    }
  }
}

template<typename T>
void SList_t<T>::reverse (SList_t<T> *list)
{
  
  SLNode_t<T> *runner, *insertion_after_node = NULL, *oldHead, *curr_tail; 

  if (list == NULL) 
    list = this;
  
  oldHead = list->head;
  
  if (list->head == NULL) 
    return;
  
  while (list->tail != oldHead) {
    runner = list->head;
    
    while (runner->next != list->tail) 
      runner = runner->next;
  
    curr_tail = runner->next;
 
    if (insertion_after_node == NULL) { /* new head */
      curr_tail->next = list->head; 
      list->head = curr_tail;
    } else {
      curr_tail->next = insertion_after_node->next;
      insertion_after_node->next = curr_tail;
    }

    insertion_after_node = curr_tail; /* update insertion after pointer */
    list->tail = runner;  /* update tail*/
    list->tail->next = NULL; /* nullify tail's next node */
  }
}

template <typename T>
bool SList_t<T>::isPalindrome() {
  SLNode_t<T> *runner = head, *runner_end = tail, *runner_start = head;

  if (runner_start == NULL)
    return false; 

  while (runner_start != runner_end && runner_end->next != runner_start) {
    runner = runner_start;
    
    while (runner->next != runner_end) 
      runner = runner->next;
    
    if (runner_start->value != runner_end->value )
      return false;

    runner_start = runner_start->next; /* update start */
    runner_end = runner; /* update end */
  }

  return true;
}

template <class T>
ret_obj<T> SList_t<T>::kthLastNode(SList_t *list, unsigned int n)
{
  SLNode_t<T> *runner, *runner_start;
  ret_obj<T> data{false};
  int count;

  if (list == NULL)
    list = this;
  
  if (list->head == NULL)
    return data; 

  runner_start = list->head;

  while (runner_start) {
    runner = runner_start; 
    count = 0;
    while (runner) {
      count++;
      runner = runner->next;
    }
    if (n == count) {
      data.valid = true;
      data.value = runner_start->value; 
      return data;
    }
    runner_start = runner_start->next;
  } 
  return data; 
}

template <class T>
void SList_t<T>::shiftRight(int n)
{
  SLNode_t<T> *runner;

  if (head == NULL)
    return; 
  
  if (head->next == NULL)
    return;
  
  if (n < 0) 
    return this->shiftLeft(-1 * n);

  for (int i = 0 ; i < n; i++) {
    runner = head;
    while (runner->next != tail) {
      runner = runner->next;
    }
    runner->next->next = head;
    head = runner->next;
    tail = runner;
    tail->next = NULL;
  }
}

template <class T>
void SList_t<T>::shiftLeft(int n) {
  SLNode_t<T> *runner, *tail;
  
  if (head == NULL)
    return; 

  if (head->next == NULL)
    return;
    
  for (int i = 0 ; i < n; i ++) {
    tail->next = head;
    head = head->next;
    tail = tail->next;
    tail->next = NULL;
  }  
}

template <class T>
void  SList_t<T>::display()
{
  SLNode_t<T> *runner = head;
  while (runner) {
    std::cout <<  "[" << runner->value << "]";
    runner = runner->next;
  }
}

template <class T>
SList_t<T>  *SList_t<T>::sum_numerals (SList_t<T> *list_a, SList_t<T> *list_b, bool least_sig_digit_first)
{
  SList_t<T> *newList = sl_list<T>();
  SLNode_t<T> *a = list_a->head;
  SLNode_t<T> *b = list_b->head;
  T sum[3] = {0,0,0};
  int factor  = 1;
  int count = 0;
  int temp;

  while (a || b ) {
    if (a) {
      sum[0] += a->value%10 * factor;
      a = a->next;
    }
    if (b) {
      sum[1] += b->value%10 * factor;
      b = b->next;
    }
    factor *= 10;
    count++;
  }
  sum[2] = sum[0] + sum[1];
  
  while (count--) {
    if (least_sig_digit_first) {
      newList->pushBack(sum[2] % 10);
      sum[2] /= 10;
    } else {
      factor/=10;
      newList->pushBack(sum[2] / factor);
      sum[2] -= (sum[2] / factor)*factor;
    }
  }
  newList->display();
  return newList;
}

template <class T>
SList_t<T> *SList_t<T>::setupLoop(unsigned int count, unsigned int loop_pos)
{
  SList_t<T> *circularList = sl_list<T>();
  SLNode_t<T> *ref;
  for (int i = 1; i <= count; i++) {
    circularList->pushBack(i);
    if (i == loop_pos)
      ref = circularList->tail;
  }
  tail->next = ref;
}


template <class T>
bool SList_t<T>::hasLoop()
{
  SLNode_t<T> *runner_lag;
  SLNode_t<T> *runner_lead;
  bool result = false;

  if (head == NULL)
    return false; 

  runner_lag = head;
  runner_lead = head->next;
  
  while (runner_lag) {
    result |= (runner_lead->next == runner_lag);
    if (result)
      break;
    if (runner_lag)
      runner_lag = runner_lag->next;
    if (runner_lead)
      runner_lead = runner_lead->next;
  }
  return result;
}

template <class T>
SLNode_t<T> *SList_t<T>::loopStart()
{
  SLNode_t<T> *runner_lag;
  SLNode_t<T> *runner_lead;
  SLNode_t<T> *prev;
  bool result = false; 

  if (head == NULL)
    return false; 

  runner_lag = head;
  runner_lead = head->next;
  
  while (runner_lag && !result) {
    prev = runner_lag;
    runner_lag = runner_lag->next;
    runner_lead = runner_lead->next;
    result |= (runner_lead->next == runner_lag);
  }

  if (result)
    return prev;
  else 
    return NULL;
}

template <class T>
void SList_t<T>::breakLoop()
{
  SLNode_t<T> *tail_of_loop = loopStart();
  tail_of_loop->next = NULL;
}

template <class T>
unsigned int SList_t<T>::nodeCount()
{
  unsigned count = 0;
  SLNode_t<T> *tail_of_loop = loopStart();
  SLNode_t<T> *runner = head; 

  while (runner) {
    count++;
    if (runner == tail_of_loop)
      break;
    runner = runner->next;
  }
  return count;
}

template <class T>
void SList_t<T>::swapPairs()
{
  SLNode_t<T> *runner = head, *runner_prev;
  while (runner) {
    if (runner_prev == head)
      head = runner;
    if (runner == tail)
      tail = runner_prev;
    if (runner_prev) {
      runner_prev->next = runner_prev->next->next;
      runner->next = runner_prev;
      runner = runner_prev;
    }
    runner_prev = runner;
    runner = runner->next;
  }
}

template <class T>
void SList_t<T>::flattenChildren()
{
  std::queue<SLNode_t<T>*> collection;
  bool parent_list_done = false;
  SLNode_t<T> *runner; 
  
  if (head == NULL)
    return;

  collection.push_back(head);
  
  while (collection.size()) {
    runner = collection.front();
    collection.pop();

    if (parent_list_done) 
      tail->next = runner; /*connect previous tail to child */

    while (runner) {
      if (runner->child)
        collection.push(runner->child);

      if (runner == tail)  /* parent list traversal complete */
        parent_list_done = true;

      if (parent_list_done) /* update tail */
        tail = runner;

      runner = runner->next;
    }
  }
}

template <class T>
void SList_t<T>::unflattenChildren()
{
  SLNode_t<T> *runner = head, *runner_prev = NULL; 
  std::map<SLNode_t<T>*, unsigned int> histo;
  bool first_child_removed = false;

  if (runner == NULL)
    return;

  while (runner) {
    if (runner->child) {
      if (!histo.count(runner->child)) {
        histo.insert({runner->child, 0});
      } else {
        histo.at(runner->child)++;
      } 
      if ( (first_child_removed == false && histo.at(runner->child) == 2) || first_child_removed == true) {  /* children found after histo == 2 are unlinked*/
        runner_prev->next = NULL; 
      }
    }
    runner_prev = runner; 
    runner = runner->next;
  }
}



int main() {
  SList_t<int> *list_a = sl_list<int>();
  SList_t<int> *list_b = sl_list<int>();

  list_a->pushFront(1);
  list_a->pushFront(0);
  list_a->pushFront(2);

  list_b->pushFront(4);
  list_b->pushFront(8);
  
  list_a->sum_numerals(list_a, list_b,false);
}