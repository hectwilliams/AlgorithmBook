#include <stdio.h>
#include <errno.h>
#include <math.h>
extern int errno;


namespace chapter8
{

	SLNode_t* slnode(int value) {
		 SLNode_t* new_node = (SLNode_t*)malloc( sizeof(SLNode_t));
		(*new_node).value = value;
		(*new_node).next = NULL;
		return new_node;  
	}

	SList_t* slist()
	{
		SList_t* new_list = (SList_t*)malloc(sizeof(SList_t));
		new_list->head = NULL;
		new_list->back = NULL;
		new_list->push_back = slist_push_back;
		new_list->push_front = slist_push_front;
		new_list->print = slist_print;
		new_list->contains = slist_contains;
		new_list->pop_front = slist_pop_front;
		new_list->pop_back = slist_pop_front;
		new_list->remove = slist_remove;
		new_list->reverse = slist_reverse;
		new_list->is_palindrome = slist_palindrome;
		new_list->kth_last_node = kth_last_node;
		new_list->shift_left = shift_left;
		new_list->shift_right= shift_right;
		new_list->sum_numerals = sum_numerals;
		new_list->flatten_children = flatten_children;
		new_list->unflatten_children = unflatten_children;
		new_list->setup_loop = setup_loop;
		new_list->allocate_slnode = slnode;
		new_list->has_loop = has_loop;
		new_list->loop_start = loop_start;
		new_list->break_loop = break_loop;
		new_list->number_of_nodes = number_of_nodes;
		new_list->swap_pairs = swap_pairs;
		return new_list;
	}

	void slist_push_back(struct SList_t* list, int value)
	{
		SLNode_t* node = list->allocate_slnode(value);
		if (list->head == NULL) {
			list->head = node;
			list->back = list->head;
		} else {
			list->back->next = node;
			list->back = node;
		}
	}

	void slist_push_front(struct SList_t* list, int value)
	{
		SLNode_t* node;
		if (!list->head)
			return slist_push_back(list, value);
		node = slnode(value);
		node->next = list->head;
		list->head = node; 
	}
	int slist_pop_front(struct SList_t* list)
	{
		int returnVal = -1;
		if (!list->head) {
			perror("head is null, returning -1");
			fprintf(stderr, NULL);
			return returnVal;
		}
		returnVal = list->head->value;
		list->back = (list->head == list->back) ? NULL : list->back;
		list->head = list->head->next;
		return returnVal;
	}

	int slist_pop_back(struct SList_t* list)
	{
		int returnVal = -1;
		if (!list->back) {
			perror("tail is null, returning -1");
			fprintf(stderr, NULL);
			return returnVal;
		}
		returnVal = list->back->value;
		list->head = (list->head == list->back) ? NULL : list->head;
		list->back = list->back->next;
	}

	bool slist_contains(SList_t *list, int value)
	{
		for (SLNode_t* runner = list->head; runner; runner = runner->next) {
			if (runner->value == value)
				return true;
		}
		return false;
	}

	void slist_print(struct SList_t* list)
	{
		for (SLNode_t* ptr = list->head; ptr; ptr = ptr->next) {
			printf("[%d]", ptr->value);
		}
	}
	
	bool slist_remove(SList_t* list, int value)
	{
		SLNode_t* runner = NULL, *plucked_node = NULL;

		if (!list->head)
			return false;

		if (list->head->value == value) {   
			plucked_node = list->head;
			list->head = list->head->next;
		} else {
			runner = list->head;
			while (runner->next) {
				if (runner->next->value == value) {
					plucked_node = runner->next;
					runner->next = runner->next->next;
				}
			}
		}
		free(plucked_node);
		return true;
	}

	void slist_reverse(SList_t* list)
	{
		SLNode_t* plucked_node = NULL;

		if (list->head == list->back)
			return; 

		while (list->head != list->back) {
			plucked_node = list->head;
			list->head = list->head->next;
			plucked_node->next = list->back->next;
			list->back->next = plucked_node;
		}
	}

	bool slist_palindrome(SList_t* list)
	{
		SLNode_t* h , *t, *runner;

		if (list->head == NULL)
			return false;

		t = list->back;
		h = list->head;
		runner = h;

		while (runner->next) {
			
			if (t->value != h->value)
				return false;
			
			if (h->next == t || t == h)
				break;

			if (runner->next == t) {
				t = runner;
				h = h->next;
				runner = h;
			}

			runner = runner->next;
		
		}
		return true;
	}

	int kth_last_node(SList_t* list, unsigned n)
	{
		/* buffer of size n*/
		int* buffer;
		int resultVal = 0, i = 0;
		SLNode_t* runner;

		if (n <= 0) {
			perror("n must be greater than 0, returning -1");
			fprintf(stderr, NULL);
			return -1;
		} else {
			buffer = (int*) malloc(n* sizeof(int));
			runner = list->head;
			while (runner) {
				printf("[%d]", runner->value);
				buffer[i++ % n] = runner->value;
				runner = runner->next;
			}
			resultVal = buffer[n - 1];
		}
		free(buffer);
		return resultVal;
		
	}

	void shift_left (SList_t* list, unsigned shiftBy)
	{
		for (int i = 0; i < shiftBy; i++) {
			list->back->next = list->head;
			list->head = list->head->next;
			list->back = list->back->next;
			list->back->next = NULL;
		}
	}

	void shift_right (SList_t* list, unsigned shiftBy)
	{
		SLNode_t *prev_tail;
		
		for (int i = 0; i < shiftBy; i++) {
			prev_tail = list->back;
			while (prev_tail != list->head) {
				list->back->next = list->head;
				list->head = list->head->next;
				list->back = list->back->next;
				list->back->next = NULL;
			}
		}

	}

	int sum_numerals(SList_t* list_a, SList_t* list_b)
	{
	
		SLNode_t* runners[2] = {list_a->head, list_b->head};
		bool boolean = false;
		unsigned e = 0;
		unsigned val = 0;
		int sum_a = 0, sum_b = 0;

		for (; runners[0] || runners[1]; boolean = !boolean) {
			e += +(boolean == 0);
			val = std::pow(10, e - 1);

			if (!!runners[+boolean]) {
				if (!boolean) {
					sum_a += runners[0]->value * val;
				}
				else {
					sum_b += runners[1]->value * val;
				}
				runners[+boolean] = runners[+boolean]->next;
			}
		}
		return sum_a + sum_b;
	}

	void flatten_children(SList_t* list)
	{
		SLNode_t** child_list = (SLNode_t**) malloc(1* (sizeof(SLNode_t*)));
		SLNode_t* runner = list->head;

		int size = 0;
		int index = 0;

		/* append children to child list*/
		while (runner) {
			if (!!runner->child) {
				size++;
				realloc(child_list, size);
				child_list[size - 1] = runner->child; 
			}
			
			if (!(runner->next) && (index < size)) {
				runner = child_list[index++];
			} else {
				runner = runner->next;
			}
		}

		/*  flatten buffered list  */
		runner = list->head;
		index = 0;
		while (runner) {
			if (!(runner->next)) {
				if ((index < size))
					runner->next = child_list[index++];
				else
					list->back = runner;
			}
			runner = runner->next;
		}

		free(child_list);
	}

	void unflatten_children(SList_t* list)
	{
		SLNode_t* runner = list->head;
		SLNode_t* child;
		SLNode_t* new_back = NULL;
		SLNode_t** child_list = (SLNode_t**)malloc(1 * (sizeof(SLNode_t*)));
		int size = 0;
		int index = 0;

		while (runner->next) {
			if (runner->next->child) {
				size++;
				realloc(child_list, size);
				child_list[size - 1] = runner->next->child;
			}
			
			if (runner->next == child_list[index]) {
				if (index == 0)
					list->back = runner;
				child = runner->next;
				runner->next = NULL;
				runner = child;
				index++;
			}

			free(child_list);

		}
	}

	void basic_config_setup(SList_t* list)
	{
		/* basic configuration*/
		list->push_back = slist_push_back;
		list->push_front = slist_push_front;
		list->allocate_slnode = slnode;
	}

	SLNode_t* setup_loop(unsigned node_count, unsigned num)
	{
		static SList_t loopy_list;;
		SLNode_t *tmp = NULL;
		
		basic_config_setup(&loopy_list);

		if (num == 0)
			return loopy_list.head;

		for (int i = 1; i <= node_count; i++) {
			loopy_list.push_back(&loopy_list, i);
			if (i == num) {
				tmp = loopy_list.back;
			}
		}

		loopy_list.back->next = tmp;
		return loopy_list.head;
	}

	bool has_loop(SList_t *list)
	{
		SLNode_t* front, *back;
		
		if (!list->head) 
			return false;
		
		front = list->head->next;
		back = list->head;
		
		while (!!front && !!back) {
			
			if ( front->next == back) { /*adjacent*/
				return true;
			}

			if (front->next) {
				if (front->next->next == back) { /* feeback */
					return true;
				}
			}

			back = back->next;
			front = front->next;
		}
		return false;
	}

	SLNode_t* loop_start(SList_t* list)
	{
		SLNode_t* front, * back;

		if (!list->head)
			return NULL;

		front = list->head->next;
		back = list->head;

		while (!!front && !!back) {
			if ( front->next == back) {
				return front;
			}
			if (front->next) {
				if (front->next->next == back) {
					return front->next;
				}
			}
			back = back->next;
			front = front->next;
		}
		return NULL;
	}

	void break_loop(SList_t* list)
	{
		SLNode_t * node = loop_start(list);
		if (!!node) {
			node->next = NULL;
		}
	}

	int number_of_nodes (SList_t* list)
	{
		int counter = 0;
		SLNode_t* node = list->head;
		
		break_loop(list);
		while (node) {
			counter++;
			node = node->next;
		}
		return counter;
	}

	void swap_pairs(SList_t* list)
	{
		SLNode_t* runner;
		SLNode_t* node, * stop;

		if (list->head == NULL)
			return;
	
		stop = list->head->next;
		runner = list->head;

		while (runner->next) {
			node = list->head;
			list->head = list->head->next;
			node->next = list->head->next;
			list->head->next = node;
			shift_left(list, 2);
			runner = list->head;

			if (runner->next == stop) {
				shift_left(list, 1);
				break;
			}
			if (runner == stop) {
				break;
			}
		}
		
	}

}