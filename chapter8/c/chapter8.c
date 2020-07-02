#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "chapter8.h"
#include <errno.h>
#include <string.h>

extern int errno;

int main(int argv, char **argc) {  	//entry 
	DList_t * dlist = dlist_malloc();
	dlist_push( dlist, 0);
	dlist_push( dlist, 2);
	dlist_push( dlist, 0);
	dlist_push( dlist, 1);
	dlist_push( dlist, 4);
	dlist_push( dlist, 6);
	dlist_partition(dlist, 1);
	dlist_reverse(dlist);
	dlist_display(dlist);
	// destruct_list();
}

SLNode_t *sl_node(int value)
{
	SLNode_t *node = (SLNode_t*) malloc(sizeof(SLNode_t));
	node->child = node->next = NULL;
	node->value = value;
	return node; 
}

SList_t *slist_malloc(void) 
{
	// TODO : BUFFER LISTS 
	SList_t *newList;
	newList = (SList_t*) malloc( sizeof(SList_t) );
	newList->head = NULL;
	newList->tail = NULL;
	return newList;
}

/* destruct linked list */
void slist_destruct_list(void) 
{
	// TODO : REMOVE BUFFERED LISTS  
}

void slist_enqueue (void *data, int value)
{
	SList_t *list = (SList_t *) data;
	SLNode_t *runner = list->head;
	SLNode_t *node = sl_node(value);

	if (runner == NULL) {
		list->head = list->tail= node; 
	} else {
		list->tail->next = node;
		list->tail = node; 
	}
}


return_data slist_dequeue (void *data)
{
	SList_t *list = (SList_t *) data;
	return_data result = {.valid = False}; 
	SLNode_t *node = list->head;

	if (!node)
		return result; 
	
	result.valid = True;
	result.value = list->head->value;
	
	if (node == list->tail) 
		list->tail = NULL;
	
	list->head = list->head->next;
	free(node);
	return result;
}

void  slist_display(void *data)
{
	SList_t *list = (SList_t *) data;
	SLNode_t *runner = list->head;
	while (runner) {
		printf("data:%d \n", runner->value);
		runner = runner->next;
	}
}

SLNode_t *reverse (SList_t *list) {
	SLNode_t *runner = list->head;
	SLNode_t *tmp = sl_node(2);
	SLNode_t *tmp_node = NULL;

	while (runner) {
		tmp->next = list->head;
		list->head = list->head->next;
		tmp->next->next = tmp_node;
		tmp_node = tmp->next;
	}
	
	list->head = tmp->next;
	free(tmp);
	return list->head;
} 

boolean is_palindrome (SList_t *list) 
{
	SLNode_t *runner, *start, *end = NULL;
	
	if (list->head == NULL)
		return False;

	start = list->head;
	
	while (start) {
		runner = start;
		while (runner != end) {
			runner = runner->next;
		}
		end = runner;
		if (end->value != start->value)
			return False; 
		start = start->next;
	}

	return True;
}

return_data kthLastNode(SList_t *list, unsigned int k)
{
	SLNode_t *runner, *start, *end = NULL;
	unsigned int count = 0;
	return_data data =  {.valid = False};

	if (list->head == NULL)
		return data;
	
	runner = list->head;

	/* count number of nodes */
	while (runner) {
		count += 1;
		runner = runner->next;
	}

	count -= k;

		/* point runner to kth node  */
	if (count > 0) {
		runner = list->head;
		while (count--) 
			runner = runner->next;
	}

	if (runner) {
		data.valid = True;
		data.value = runner->value;
	}

	return data; 

}

void shift_left (SList_t *list, int n)
{
	SLNode_t *runner = list->head;
	SLNode_t *newHead = NULL;
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

void shift_right (SList_t *list, int n)
{
  
	SLNode_t *runner;
	SLNode_t  *newHead = NULL, *oldHead = NULL;
	int count = 0;

	if (list == NULL)
		return;

	if (list->head == NULL)
		return;

	oldHead = list->head;
	runner = oldHead;
	
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
		runner->next = oldHead;
		list->head = newHead;
	}

	if (n < 0) {
		return shift_left(list, abs(n));
	}

}



SList_t * slist_sum_numerals ( SList_t *a,  SList_t *b)
{
	unsigned sum_a = 0, sum_b = 0 , sum;
	float counter = 0;
	float factor;
	
	SList_t *curr_list = slist_malloc(); 
	SLNode_t *runner_a = (a)->head , *runner_b = (b)->head;
	
	while (runner_a || runner_b ) {
		factor = pow(10, counter++);
		if (runner_a) {
			sum_a += factor * runner_a->value;
			runner_a = runner_a->next;
		}
		if (runner_b) {
			sum_b += factor * runner_b->value;
			runner_b = runner_b->next;
		}
	}

	sum =  sum_a + sum_b;
	for ( int i = 0; i < counter; i++) {
		/*first node is least significant*/ 
		slist_enqueue(curr_list, sum % 10 );
		sum/=10;
	}
	/*first node is most significant 
		curr_list->methods->enqueue(curr_list, ((int) (sum / pow(10, counter - i - 1))  )%10 ); 
	*/
	return curr_list;
}

void slist_flatten_children(SList_t *list) {

	int size;
	int offset;
	SLNode_t *runner = list->head, *runner_prev, *curr_head;
	SLNode_t** dynamic_array;   /* array of [SLNode_t*] */

	if (list->head == NULL)
		return;

	size = 1;
	offset = size - 1; 
 	runner = list->head;
	dynamic_array = malloc(sizeof(SLNode_t*) * size);
	*(dynamic_array + offset) = list->head; 

	while (size) {
		curr_head = *(dynamic_array);  
		runner = curr_head; 
		while (runner) {
			if (runner->child != NULL) {
				++size;
				offset = size - 1;
				dynamic_array = realloc(dynamic_array, sizeof(SLNode_t*) * size ); /* expansion  */
				*(dynamic_array + offset) = runner->child; /* assign child to array */
			}
			runner_prev = runner;
			runner = runner->next;
		}

		if (curr_head != list->head) {  
			list->tail->next = curr_head; /* link parent tail to child's head  */
			list->tail = runner_prev;  /* update parent tail to child's tail */
		}

		if (size-- > 0 )  
			memmove(dynamic_array, dynamic_array + 1, sizeof(SLNode_t*) *size); /* remove first element */
		dynamic_array = realloc(dynamic_array, sizeof(SLNode_t*) * size ); /* reduction  */
	}

}

void slist_unflatten_children(SList_t *list) {
	int size;
	int offset;
	SLNode_t *runner, *runner_prev;
	SLNode_t** runner_table;
	SLNode_t** children_array;

	if (list->head == NULL)
		return;
	
	size = 1;
	runner_table = malloc(sizeof(SLNode_t*) * size);
	children_array = malloc(sizeof(SLNode_t*) * size);
	offset = size - 1;
	*(runner_table + offset) = list->head; /* set first table element */
	runner = *(runner_table + offset); /* move table pointer  */ 
		
	while (*runner_table != *children_array && *runner_table) {
		runner = *(runner_table + offset); /*move table pointer*/
		if (runner->child != NULL) {
			*(runner_table + offset) = runner->next; /* update runner at offset */
			offset = ++size - 1; 
			runner_table = realloc(runner_table, sizeof(SLNode_t*) * size ); /*table  expansion  */
			children_array = realloc(children_array, sizeof(SLNode_t*) * size ); /* array expansion  */
			*(runner_table + offset) = runner->child; /* set runner in table */
			*(children_array + offset) = runner->child; 
			runner = (*runner_table + offset); /* move runner pointer down  */ 
		} else {
			runner_prev = runner;
			*(runner_table + offset) = runner->next; /* update table runner entry */
		}
		while ( *(runner_table + offset)  == NULL) { /* find most recent valid runner  */
			offset--;
		}
	}

	runner = *runner_table; 
	list->tail = runner_prev; /* update tail for parent list */

	while (runner) {
		if (runner == *children_array) { /* child node found in parent list */
			size--;
			runner_prev->next = NULL; /* break  connection to child  */
			if (size > 0) 
				memmove(children_array, children_array + 1, sizeof(SLNode_t*)* size);
		}
		runner_prev = runner;
		runner = runner->next;
	}
 }

struct SList_t *slist_setup_loop(unsigned int count, unsigned int repeat_n)
{
	SList_t * list = slist_malloc();
	SLNode_t *feedback;
	
	for (int i = 1 ; i <= count; i++) {
		slist_enqueue(list, i);
		if (repeat_n == i ) {
			feedback = list->tail;
		}
	}
	list->tail->next = feedback;
	return list;   
}

boolean slist_has_loop (SLNode_t *node)
{
	SLNode_t *slow, *fast;
	boolean hasLoop = False; 

	if (node == NULL)
		return hasLoop;
	slow = fast = node;
	while (slow && !hasLoop) {
		slow = slow->next;
		for (int i = 0; i < 2 && fast; i++) 
			fast = fast->next; 
		hasLoop = (fast == slow);
	} 
	return hasLoop;
}

SLNode_t*  slist_loop_start (SLNode_t *node)
{
  SLNode_t *slow, *fast, *collision = NULL, *loopHead, *runner = NULL;
	unsigned int n = 0;

	if (node == NULL)
		return runner;

	slow = fast = node; 

  while (slow) {
    slow = slow->next;
    for (int i = 2; i-- && fast ;) 
      fast = fast->next;
    if (fast == slow)
      collision = slow; 
  }

  if (collision) {
    runner = collision->next;
    while (runner != collision) {
      n++;
      runner = runner->next;
    }

    /* move loop head n-1 after LL Head */
    loopHead = node;
    for (int i = n-1; i-- ;) 
      loopHead = loopHead->next;

    runner = loopHead;
    /* set runner to feedback node */
    while (runner->next != loopHead) 
      runner = runner->next;
  }
	
	return runner; 

}

void slist_break_loop(SLNode_t *node) {
	SLNode_t *feedback = slist_loop_start(node);
	if (feedback)
		feedback->next = NULL; 
}

unsigned int slist_number_of_nodes (SLNode_t *node)
{
	SLNode_t *feedback = slist_loop_start(node);
	unsigned int count = 0;

	if (node == NULL)
		return count;

	while (node->next != feedback) {
		count++;
		node = node->next;
	}

	return count;
}

void slist_swap_pairs(SList_t *list) 
{
	SLNode_t *runner, *runner_prev = NULL, *runner_next, *buffer;

	if (list->head == NULL) 
		runner = list->head;; 

	while (runner) {
		if (runner_prev) {
			if (list->head == runner_prev)
				list->head = runner;
			if (list->tail == runner) 
				list->head = runner_prev;
		/* [runner_prev] -->  [ runner] --> [runner_next] */			                   
			runner_prev->next = runner->next;
			runner->next = runner_prev;
		/* move runner forward and initialize prev ptr */			
			runner = runner_prev;
			runner_prev = NULL;
		} else {
			runner_prev = runner;
			runner = runner->next;
		}
	} 
}




DList_t *dlist_malloc(void) 
{
	// TODO LOGIC TO STORE LINKEDLIST IN BUFFER 
	DList_t *new_DList;
	new_DList = (DList_t*) malloc( sizeof(DList_t) );
	new_DList->head = NULL;
	new_DList->tail = NULL;
	return new_DList;
}

/* destruct linked list */
void dlist_destruct(void) 
{
	// TODO 
}



DLNode_t *dl_node(int value) {
	DLNode_t * node = (DLNode_t *) malloc(sizeof(DLNode_t));
	node->next = node->prev = NULL;
	node->value = value;
}

void dlist_push(DList_t *list, int value)
{
	DLNode_t *node = dl_node(value);

	if (list->head == NULL) {
		list->head = list->tail =  node;
	} else {
		list->head->prev = node;
		node->next = list->head;
		list->head = node;
	}
}

return_data dlist_pop(DList_t *list)
{
	return_data result = {.valid = False}; 
	DLNode_t *del_node;

	if (list->head == NULL) 
		return result;
	
	result.valid = True;
	result.value = list->head->value;

	del_node = list->head;
	list->head = list->head->next;
	
	if (list->head)
		list->head->prev = NULL;
	
	free(del_node);
}

void dlist_display(struct  DList_t *list)
{
	DLNode_t *node = list->head;
	while (node) {
		printf("node: %d\n" , node->value);
		node = node->next;
	}
}

return_data dlist_front(struct DList_t *list)
{
	return_data data = {.valid = False};
	if (list->head == NULL)
		return data;
	data.value = list->head->value;
	data.valid = True;
	return data;
}

return_data dlist_back(struct DList_t *list)
{
	return_data data = {.valid = False};
	if (list->tail == NULL)
		return data;
	data.value = list->tail->value;
	data.valid = True;
	return data;
}

boolean dlist_contains(struct DList_t *list, int value) 
{
	DLNode_t *dnode = list->head;
	
	if (dnode == NULL) 
		return False;
	
	while (dnode) {
		if (dnode->value == value)
			return True;
		dnode = dnode->next;
	}

	return False; 
}


unsigned int dlist_size(struct DList_t *list) 
{
	unsigned int count = 0;
	DLNode_t *dnode = list->head;
	
	if (dnode == NULL) 
		return count;

	while (dnode) {
		count += 1;
		dnode = dnode->next;
	}
	return count;
}

void dlist_prepend_value(struct DList_t *list, int new_value, int existing_value)
{
	DLNode_t *runner = list->head;
	DLNode_t *node;
	
	if (list->head == NULL)
		return;
	
	if (list->head->value = existing_value) {
		node == dl_node(new_value);
		list->head->prev = node;
		node->next = list->head;
		list->head = node;
		node->prev = NULL;
	} else {
		while (runner->next) {
			if (runner->next->value == existing_value) {
				node == dl_node(new_value);
				runner->next->prev = node;
				node->next = runner->next;
				runner->next = node;
				node->prev = runner;
				runner = node; /* set runner to prepended node */ 
			}
			runner = runner->next;
		}
	}
}

void dlist_append_value(struct DList_t *list, int new_value, int existing_value)
{
	DLNode_t *runner = list->head;
	DLNode_t *node;

	if (list->head == NULL)
		return;
	
	if (list->head->value == existing_value) {
		node = dl_node(new_value);
		node->next = list->head->next;
		if (list->head->next != NULL) { 
			 list->head->next->prev = node;
		}
		list->head->next = node;	
	} else {
		while(runner->next) {
			if (runner->next->value == existing_value) {
				node = dl_node(new_value);
				node->next = runner->next->next;
				if (runner->next->next) {
					runner->next->next->prev = node; 
				}
				runner->next->next = node; 
				node->prev = runner->next;
			}
		}
	}
}

return_data dlist_kth_to_last_value(struct DList_t *list, unsigned int k) {
	DLNode_t *runner = list->tail;
	return_data data = {.valid = False};

	if (runner == NULL)
		return data;

	while (k-- > 0 && runner != NULL) 
		runner = runner->prev; 

	if (runner) {
		data.valid = True;
		data.value = runner->value;
	}

	return data;
}

void dlist_delete_middle_node(DLNode_t *dnode)
{
	DLNode_t *tmp_dnode;
	if (dnode->prev && dnode->next) {
		tmp_dnode = dnode;
		dnode->prev->next = dnode->next;
		dnode->next->prev = dnode->prev;
		free(tmp_dnode);
	}
}

boolean dlist_is_valid(struct DList_t *list)
{
	unsigned int count_forward, count_back;
	DLNode_t *runner_forward, *runner_back;

	if (list->head == NULL) 
		return False;

	count_back = 0;
	count_forward = 0;
	runner_forward = list->head;
	runner_back = list->tail;

	while (runner_back || runner_forward) {
		count_forward += +(runner_forward == list->head);
		count_back += +(runner_back == list->tail);

		if (count_back == 2 || count_forward == 2) 
			return False; 
		
		if (runner_forward) 
			runner_forward = runner_forward->next;
		
		if (runner_back) 
			runner_back = runner_back->prev;
	}

	return True;
}

void dlist_partition(struct DList_t *list, int value)
{

	DLNode_t *dnode = list->head;
	DLNode_t *tmp;

	if (dnode->next == NULL && dnode->prev == NULL) /* single dnode return */
		return;

	while (dnode) {

		if (dnode->value < value) { 
			tmp = dnode;

			if (dnode->next) 
				dnode->next->prev = dnode->prev;
			dnode->prev->next = dnode->next;

			if (dnode == list->tail)
				list->tail = list->tail->prev;  /* update tail  */
			
			dnode = dnode->prev; /* update walker( i.e. runner i.e. dnode )*/

			/* move dnode to head of list  */
			tmp->next = list->head; 
			list->head->prev =  tmp;
			tmp->prev = NULL;
			list->head = tmp;
		}

		dnode = dnode->next;
	}
}

boolean dlist_palindrome(struct DList_t *list)
{
	DLNode_t *runner_forward, *runner_back;

	if (list->head == NULL) 
		return False; 

	runner_forward = list->head;
	runner_back = list->tail;

	while (runner_forward && runner_back) {
		if (runner_forward->value != runner_back->value) 
			return False;
		runner_forward = runner_forward->next;
		runner_back = runner_back->next;
	}

	return True;
}

void dlist_reverse(struct DList_t *list)
{
	DLNode_t *runner;
	DLNode_t *dnode;
	DLNode_t *oldHead = list->head;

	if (oldHead == NULL) 
		return ; 
	
	runner = list->tail;

	while (runner->prev != NULL && oldHead != list->tail) {
		dnode = runner->prev;
		runner->prev = dnode->prev;		

		if (dnode->prev) 
			dnode->prev->next = dnode->next;

		if (dnode == oldHead) 
			list->head = runner;

		list->tail->next = dnode; /* update tail */
		dnode->prev = list->tail;
		list->tail = dnode;
		dnode->next = NULL;
	}
}

DLNode_t* dlist_loop_start(struct DList_t *list)
{
	DLNode_t *runner_a = list->head, *runner_b; //b leads 
	DLNode_t * prev; 

	if (runner_a == NULL) 
		return NULL;

	runner_b = runner_a->next;
	
	while (runner_a && runner_b) {

		if (runner_b->next == runner_a ) {
			return prev;
		}

		prev = runner_b;
		runner_a = runner_a->next;
		runner_b = runner_b->next;
 	}
	return NULL;
}

void dlist_break_loop(struct DList_t *list)
{
	DLNode_t* node = dlist_loop_start(list);
	node->next = NULL;
	list->tail = node; 
}

void dlist_repair(struct DList_t *list)
{
	while (dlist_is_valid(list) == False) {
		dlist_break_loop(list);
	}
}
