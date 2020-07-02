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
  bool rslt = false; 

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
      rslt = true;
    } else {
      runner_prev = runner;
      runner = runner->next;
    }
  }
  return rslt;
}

template<typename T>
void SList_t<T>::reverse (SList_t<T> *list)
{
  
  SLNode_t<T> *tmp_node = sl_node<T>(0), *tmp_node_next = NULL;

  if (list == NULL) 
    list = this;
  
  if (list->head == NULL) 
    return;
  
  while (list->head) {
    tmp_node->next = list->head;
    list->head = list->head->next;
    tmp_node->next->next = tmp_node_next;
    tmp_node_next = tmp_node->next;
  }

  if (tmp_node->next) 
    list->head = tmp_node->next;
  
  free(tmp_node);
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
ret_obj<T> SList_t<T>::kthLastNode(SList_t *list, unsigned int k)
{
  SLNode_t<T> *runner = NULL;
  ret_obj<T> data{false};
  int count = 0;

  if (list == NULL) 
    runner = head;
  
	/* count number of nodes */
  while (runner)  {
    runner = runner->next;
    count++;
  }
  
  count -= k;
  /* point runner to kth node  */
  if (count > 0) {
    runner = head;
    while (count--) 
      runner = runner->next;
  }

  if (runner) {
    data.valid = true;
    data.value = runner->value;
  }

  return data;
}

template <class T>
void SList_t<T>::shiftRight(int n)
{
  SLNode_t<T> *runner = head;
	SLNode_t<T> *newHead = NULL, *oldHead = NULL;
  int count = 0;

  if (head == NULL)
    return; 
  
	while (runner) {
		runner = runner->next;
		count += 1;
	}

	if (n > 0 && count > 1) {
		runner = list->head;
		for (int i = 0; i < abs(n - count); i++) {
			runner = runner->next;
		}

		/* break list */
		newHead = runner->next;
		runner->next = NULL;

    runner = newHead;
    
    /* connect new head's tail to old head*/
    while (runner->next) 
      runner = runner->next;
    runner->next = head;
    head = newHead;
	}

	if (n < 0) {
		return shift_left( abs(n));
	}

}

template <class T>
void SList_t<T>::shiftLeft(int n)
{
  SLNode_t<T> *runner = head;
	SLNode_t<T> *newHead = NULL;
	int count = 0;
  
	while (runner) {
		count += 1;
		
		if (count == n) {
		
		/* break link */
			newHead = runner->next;
			runner->next = NULL;
		
		/*new Head must be NULL*/
			if (newHead == NULL) 
				break;
			
		/* point runner to tail of newHead */
			runner = newHead;
			while (runner->next) 
				runner = runner->next;
			
		/* link new list with new Head*/
			runner->next = list->head;
		
		/* update head */
			list->head = newHead;

			break;
		}
		runner = runner->next;
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
  SLNode_t<T> *slow =, *fast;
  bool hasLoop = false;

  if (head == NULL)
    return hasLoop;
  slow = fast = head; 
  while (slow && !hasLoop) {
    slow = slow->next;
    for (int i = 2; i-- && fast ;)
      fast = fast.next;
    hasLoop = fast == slow;
  }
  return hasLoop;
}

template <class T>
SLNode_t<T> *SList_t<T>::loopStart()
{
  SLNode_t<T> *slow, *fast, *collision = NULL, *loopHead, *runner = NULL;
  unsigned int n = 0;

  if (head == NULL)
    return runner;

  slow = fast = head;
  
  while (slow) {
    slow = slow->next;
    
    for (int i = 2; i-- && fast ;) 
      fast = fast->next;
    
    if (fast == slow)
      collision = slow; 
  }

  /* number of nodes in loop  */
  if (collision) {
    runner = collision->next;
    while (runner != collision) {
      n++;
      runner = runner->next;
    }

    /* move loop head n-1 after LL Head */
    loopHead = head;
    for (int i = n-1; i-- ;) 
      loopHead = loopHead->next;

    runner = loopHead;
    /* set runner to feedback node */
    while (runner->next != loopHead) 
      runner = runner->next;
  }

  return runner; 
}

template <class T>
void SList_t<T>::breakLoop()
{
  SLNode_t<T> *feedback = loopStart();
  if (feedback)
    feedback->next = NULL;
}

template <class T>
unsigned int SList_t<T>::nodeCount()
{
  SLNode_t<T> *feedback = loopStart(), *node = head;
	unsigned int count = 0;

	if (node == NULL) {
    return count;
  }

	while (node->next != feedback) {
		count++;
		node = node->next;
  }

	return count;
}

template <class T>
void SList_t<T>::swapPairs()
{
  SLNode_t<T> *runner = head, *runner_prev;
  while (runner) {
    if (runner_prev) {
      if (head == runner_prev)
        head = runner;
      if (tail == runner)
        tail = runner_prev;
      
    	runner_prev->next = runner->next;
			runner->next = runner_prev;

      runner = runner_prev;
      runner_prev = NULL;

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