#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "chapter5.h"

#define LIST_MAX_LEN 2

llnode * ListNode(int value) 
{
  llnode *node = (llnode *) malloc(sizeof(llnode));
  node->val = value;
  node->next = (llnode *) NULL;  
  return node;
}

llist *LinkedList() 
{
  static llist *list = NULL;
  list = (llist*) malloc(sizeof(llist));
  list->head = NULL;
}

void sl_print_list (llist *llist)
{
  llnode *node = llist->head;
  while (node != NULL) {
    printf("[%d]", node->val);
    node = (llnode*) node->next;
  }
}

void sl_add_front (llist *list, int value)
{
  llnode *runner = list->head;
  llnode *node = ListNode(value); 
  
  if (list->head == NULL) {
    list->head = node;
  } else {
    node->next = list->head;
    list->head = node;
  }
}

boolean sl_contains (llist *list, int value) 
{
    llnode *runner = list->head;
    while (runner)
    {
      if (runner->val == value)
        return True;      
    }
    return False;
}

llnode *sl_remove_front (llist *list)
{
  llnode *node;
  if (list->head == NULL) {
    return NULL;
  } else {
    node = list->head;
    list->head = list->head->next;
    return node;
  }
}

llnode *sl_front (llist *restrict list)
{
  return list->head;
}

unsigned sl_length (llnode *node)
{
  unsigned count = 0;
  while (node) {
    count++;
    node = node->next;
  }
}

void sl_display (llnode *node) 
{
  while (node) {
    printf("[%d]", node->val);
    node = node->next;
  }
}

int sl_max(llnode *restrict node)
{
  llnode *max_node = NULL;
  while (node) {
    if (max_node == NULL) 
      max_node = node;
    if (node->val > max_node->val) 
      max_node = node;
    node = node->next;
  }

  if (max_node)
    return max_node->val;
  else 
    return INT_MAX;
}

int sl_min(llnode *restrict node)
{
  llnode *min_node = NULL;

  while (node) {
    if (min_node == NULL) 
      min_node = node;
    if (node->val < min_node->val) 
      min_node = node;
    node = node->next;
  }

  if (min_node)
    return min_node->val;
  else 
    return INT_MIN;
}

float sl_avg (llnode *restrict node) 
{
  float avg = 0, count = 0;
  while (node) {
    count++;
    avg += node->val;
    node = node->next;
  }
  return avg / ((count == 0) ? 1.0 : count); 
}

llnode *sl_back(llnode *restrict node)
{
  while (node->next) {
    node = node->next;
  }
  return node; 
}

llist *sl_remove_back(llist *list)
{
  llnode *prev = NULL;
  llnode *node = list->head;
  llnode *head = node;

  if (head->next == NULL) {
    head = NULL;
  } else {
    while (node->next) {
      prev = node;
      node = node->next;
    }
    if (prev) {
      prev->next = NULL;
    }
  }
  free(node);
  return list;
}

llist * sl_add_back(llist *list, int value)
{
  llnode *node = list->head;
  llnode *new_node = ListNode(value);

  if (node == NULL) {
    list->head = new_node;
  } else {
    while (node->next)
      node = node->next;
    node->next = new_node;
  }
  
  return list;
}


/* callbacks from move_x_to_front */
compare_state move_n_to_front_helper_cmp(llnode *a, llnode *b) {
  compare_state result = False;
  if (!a || !b)
    return undefined;
  if (a->val < b->val)
    return less;
  if (a->val > b->val)
    return greater;
  if (a->val == b->val) 
    return equal;
}

void move_min_to_front (llist *list)
{
  llnode *runner = list->head;

  struct min_data_t {
    llnode *node;
    llnode *prev;
  } min_data = {list->head, NULL};

  while (runner->next) {
    if ( move_n_to_front_helper_cmp (runner->next, min_data.node) == less) {
      min_data.node = runner->next;
      min_data.prev = runner;
    }
    runner = runner->next;
  }

  if (min_data.prev) {
    min_data.prev->next = min_data.prev->next->next;
    min_data.node->next = list->head;
    list->head = min_data.node;
  }
}


void move_max_to_front (llist *list)
{
  llnode *runner = list->head;

  struct min_data_t {
    llnode *node;
    llnode *prev;
  } min_data = {list->head, NULL};

  while (runner->next) {
    if ( move_n_to_front_helper_cmp (runner->next, min_data.node) == greater) {
      min_data.node = runner->next;
      min_data.prev = runner;
    }
    runner = runner->next;
  }

  if (min_data.prev) {
    min_data.prev->next = min_data.prev->next->next;
    min_data.node->next = list->head;
    list->head = min_data.node;
  }
}

void sl_prepend_val(llist *list, int val, int before)
{
  llnode *runner = list->head;
  llnode *new_node = ListNode(val);

  if (runner->val == before) {
    sl_add_front(list, val);
  } else {
    while (runner->next) {
      if (runner->next->val == before) {
        new_node->next = runner->next;
        runner->next = new_node;
        break;
      }
      runner = runner->next;
    }
    runner->next = new_node;
  }
}

void sl_append_val (llist *list, int val, int after) 
{
  llnode *runner = list->head;
  llnode *new_node = ListNode(val);
  
  if (runner->val == after) {
    new_node->next = runner->next;
    runner->next = new_node;
  } else {
    while (runner) {
      if (runner->val == after) {
        new_node->next = runner->next;
        runner->next = new_node;
      }
      runner = runner->next;
    }
  }
}

void sl_remove_val(llist *list, int val)
{
  llnode *runner = list->head;
  llnode *node;

  if (runner == NULL)
    return;

  if ( list->head->val == val) {
    node =  list->head;
    list->head = list->head->next;
  } else {

    while (runner->next) {

      if (runner->next->val == val) {
        node = runner->next;
        runner->next = runner->next->next;
        break;
      }
      runner = runner->next;
    }
  }

  if (node) {
    free(node);
  }

}

llist split_on_value (llist *list, int val)
{
  llist new_list;
  llnode *runner = list->head;

  assert(list);

  if (list->head->val == val) {
    new_list.head = list->head;
    list->head = NULL;
  } else {
    while (runner->next) {
      if (runner->next->val == val) {
        new_list.head = runner->next;
        runner->next = NULL;
        break;
      }
      runner = runner->next;
    }
  }

  return new_list;

}

llnode *remove_negatives(llnode *node)
{
  llnode *head = node;
  llnode *tmp, *prev = NULL;
  
  assert(head);
  
  while (node) {
    if (node->val < 0) {
      tmp = node;
      if (node == head  && prev == NULL) {
        node = node->next;
        head = node;
        prev = NULL;
      } else {
        prev->next = tmp->next;
        node = prev->next;
      }
      free(tmp);
    } else {
      prev = node;
      node = node->next;
    }
  }
  return head;
}

llnode* concat(llnode *a, llnode *b)
{
  llnode *head = a;
  
  if (!a || !b) {
    return a;
  }

  while (a->next) {
    a = a->next;
  }

  a->next = b;

  return head;
}

llnode *partition(llnode *node, int val)
{
  llnode *head = node, *tmp;
  while (node->next) {
    if (node->next->val < val) {
      tmp = node->next;
      node->next = tmp->next;
      tmp->next = head;
      head = tmp;
    } else {
      node = node->next;
    }
  }
  return head;
}

 return_data second_largest_value (llnode *node)
{
  return_data first = {.valid = False};
  return_data second ={.valid = False};
  int tmp;
  int i = 0;

  while (node) {
    if (i == 0) {
      first.valid = True;
      first.data = node->val;
    }

    if (i == 1) {
      second.valid = True;
      second.data = node->val;
    }

    if (i  > 1) {
      if (node->val > second.data)
        second.data = node->val;
    }

    if (second.data > first.data) {
      tmp = first.data;
      first.data = second.data;
      second.data = tmp;
    }

    i++;
    node = node->next;
  }

  return second;
}

llnode *copy (llnode *node)
{
  llnode *runner;
  llnode *head;
  unsigned count = 0;

  while (node) {
    if (count == 0) {
      head = ListNode(node->val);
      runner = head;
    } else {
      runner->next = ListNode(node->val);
      runner = runner->next;
    }
    count++;
    node = node->next;
  }
  return head;
}

llnode *delete_given_node(llnode *node)
{
  llnode* tmp;
  if (node->next) {
    tmp = node->next;
    node->val = node->next->val;
    node->next = node->next->next;
    free(tmp);
  } 
}

llist *filter(llist *list, int low, int high)
{
  llnode *node = list->head;
  llnode *prev = NULL;
  llnode *tmp; 

  while (node) {
    if (node->val <low || node->val > high) {
      tmp = node;
      node = node->next;
      if (prev == NULL) {
        prev = NULL;
        if (tmp == list->head) {
          list->head = node;
        }
      } else {
        prev->next = tmp->next;
      }
      free(tmp);
    } else {
      prev = node;
      node = node->next;      
    }
  }
  return list;
}

return_data second_to_largest_value(llnode *node)
{
  return_data first, second;
  int count = 0;

  while (node) {

    if (count == 0) {
      first.data = node->val;
      first.valid = True;
    } else if (count == 1) {
      second.data = node->val;
      second.valid = True;
    } else {
      first.data = second.data;
      second.data = node->val;
    }
    node = node->next;
    ++count;
  }
  return second;
}

void dedupe(llist *list)
{
  llnode *node = list->head;
  llnode *runner;  

  while(node) {
    runner = node->next;
    while (runner) {
      if (runner->val == node->val) {
        delete_given_node(runner);
      } else {
        runner = runner->next;
      }
    }
    node = node->next;
  }
}

llnode *zip (llnode *a, llnode *b) 
{
  llnode *head = NULL, *node = head;
  int count_a = 0;
  int count_b = 0;

  if (!a || !b) {
    return NULL;
  }
  

  while (a || b) {
    if (head == NULL && a) {
      head = a;
      node = a;
      a = a->next;
      count_a++;
    } else if (head == NULL && b) {
      head = b;
      node = b;
      b = b->next;
      count_b++;
    } else if (count_a == count_b && a) {
      node->next = a;
      node = node->next;
      a = a->next;      
      ++count_a;
    } else if (count_a > count_b && b) {
      node->next = b;
      node = node->next;
      b = b->next;  
      ++count_b;
    } else if (!a) {
      node->next = b;
      b = b->next;
      break;
    } else if (!b) {
      node->next = a;
      a = a->next;
      break;
    }
  }

  return head;

}



int main () {
  llist *list = LinkedList();


  sl_add_back(list,3);
  sl_add_back(list,22);
  sl_add_back(list,422);
  sl_add_back(list,422);
  sl_add_back(list,-422);
  sl_add_back(list,322);
  sl_add_back(list,-12);

  llnode *a1 = (llnode *) malloc(sizeof(llnode));
  a1->val =1;
  llnode *a2 = (llnode *) malloc(sizeof(llnode));
  a2->val =3;
  llnode *a3 = (llnode *) malloc(sizeof(llnode));
  a3->val =5;


  llnode *b1 = (llnode *) malloc(sizeof(llnode));
  b1->val =5;
  llnode *b2 = (llnode *) malloc(sizeof(llnode));
  b2->val =10;
  llnode *b3 = (llnode *) malloc(sizeof(llnode));
  b3->val =15;

  a1->next = a2;
  a2->next = a3;
  a3 ->next = NULL;

  b1->next = b2;
  b2->next = b3;
  b3->next = NULL;


  sl_display( zip(a1, b1) );
}