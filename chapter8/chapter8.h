
#ifndef CHAPTER8_H
#define CHAPTER8_H

namespace chapter8
{
	typedef struct SLNode_t {
		int value;
		SLNode_t* next;
		SLNode_t* child;
	};

	typedef struct SList_t {
		SLNode_t* head;
		SLNode_t* back;
		void (*push_back)(struct SList_t* list, int value);
		void (*print)( SList_t* list);
		void (*push_front)( SList_t* list, int value);
		bool (*contains)( SList_t* list, int value);
		int (*pop_back)( SList_t* list);
		int (*pop_front)( SList_t* list);
		bool (*remove)(SList_t* list, int value);
		void (*reverse)(SList_t* list);
		bool (*is_palindrome)(SList_t* list);
		int (*kth_last_node)(SList_t* list, unsigned n);
		void (*shift_right)(SList_t* list, unsigned shiftBy);
		void (*shift_left)(SList_t* list, unsigned shiftBy);
		int (*sum_numerals)(SList_t *a, SList_t *b);
		void (*flatten_children)(SList_t* list);
		void (*unflatten_children)(SList_t* list);
		SLNode_t*(*setup_loop)(unsigned node_count, unsigned num);
		SLNode_t* (*allocate_slnode)(int value);
		bool (*has_loop)(SList_t* list);
		SLNode_t* (*loop_start)(SList_t* list);
		void (*break_loop)(SList_t* list);
		int (*number_of_nodes)(SList_t* list);
		void (*swap_pairs) (SList_t* list);
	};

	/* allocate new list*/
	SList_t* slist();
	/* allocate new node*/
	SLNode_t* slnode(int value);
	/* append value to end*/
	void slist_push_back( SList_t* list, int value);
	/* append value to front*/
	void slist_push_front( SList_t* list, int value);
	/* print list */
	void slist_print( SList_t* list);
	/*pop front */
	int slist_pop_front( SList_t* list);
	/*pop back*/
	int slist_pop_back( SList_t* list);
	/*contains value*/
	bool slist_contains(SList_t *list, int value);
	/*remove node */
	bool slist_remove(SList_t* list, int value);
	/*reverse list*/
	void slist_reverse(SList_t* list);
	/* palindrome*/
	bool slist_palindrome(SList_t* list);
	/*K-th last node*/
	int kth_last_node(SList_t* list, unsigned n);
	/*shift right*/
	void shift_right(SList_t* list, unsigned shiftBy);
	/*shift left*/
	void shift_left(SList_t* list, unsigned shiftBy);
	/* sum  numerals */
	int sum_numerals(SList_t *list_a, SList_t *list_b);
	/* flatten children */
	void flatten_children(SList_t* list);
	/* unflatten children */
	void unflatten_children(SList_t* list);
	/*setup loop*/
	SLNode_t* setup_loop(unsigned node_count, unsigned num);
	/* has loop*/
	bool has_loop(SList_t* list);
	/* loop start*/
	SLNode_t* loop_start (SList_t* list);
	/* break loop*/
	void break_loop (SList_t* list);
	/* number of nodes */
	int number_of_nodes(SList_t* list);
	/* swap pairs*/
	void swap_pairs (SList_t* list);
 /* basic configuration*/
	void basic_config_setup(SList_t *list);

}

#endif