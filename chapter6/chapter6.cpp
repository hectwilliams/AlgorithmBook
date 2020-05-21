#include <iostream>
#include <math.h>
#include <set>
#include <vector>
#include <array>
#include <algorithm>
#include <string.h>
#include <cstdlib>
#include <numeric> // accumulate
#include <stdio.h> 
#include <stdlib.h>
#include <sstream>
#include <tuple>
#include <deque>
#include <exception>
#include <memory>
#include <chrono>
#include <mutex>
#include <future>
#include <iomanip>
#include <errno.h>
#include <string.h>
#include "chapter6.h"
extern int errno;


namespace chapter6
{
	template <typename T>
	void SLQueue<T>::enqueue(const T& value)
	{
		SLNode<T> *node = this->slnode(value);
		if (!head) {
			head = node;
		} else {
			tail->next = node;
		}
		tail = node;
	}

	template <typename T>
	void SLQueue<T>::print(SLNode<T> *node)
	{
		for (SLNode<T> *ptr = (!!node) ? node: head ; ptr; ptr = ptr->next) {
			std::cout << ptr->val << '\n';
		}
	}

	template <typename T>
	std::tuple <T, bool> SLQueue<T>::dequeue()
	{
		SLNode<T>* target; 
		T node_value;
		if (head) {
			target = head;
			head = head->next;
			node_value = target->val;
			if (head == NULL) {
				head = NULL;
				tail = NULL;
			}
			delete target;
			return { node_value, true};
		}
		return {NULL, false};
	}

	template <typename T>
	bool SLQueue<T>::contains(const T& value)
	{
		for (SLNode<T>* ptr = head; ptr; ptr = ptr = ptr->next) {
			if (ptr->val == value) {
				return true;
			}
		}
		return false;
	}

	template <typename T>
	bool SLQueue<T>::is_empty()
	{
		return head == NULL;
	}

	template <typename T>
	unsigned SLQueue<T>::size()
	{
		unsigned count = 0;
		for (SLNode<T>* ptr = head; ptr; ptr = ptr->next) {
			++count;
		}
		return count;
	}


	template <typename T>
	SLNode<T> *SLQueue<T>::front () 
	{
		return head;
	}

	template <typename T>
	SLNode<T>* SLQueue<T>::back()
	{
		return tail;
	}

	template <typename T>
	bool SLQueue<T>::compare_queues(SLNode<T>* a, SLNode<T>* b)
	{
		SLNode<T>* ptr_a = a, *ptr_b = b;
		
		while (!!ptr_a || !!ptr_b) {
			
			if (!ptr_a ^ !ptr_b) 
				return false;
			else if (ptr_a->val != ptr_b->val)
				return false;
			
			if (!!ptr_a)
				ptr_a = ptr_a->next;
			
			if (!!ptr_b)
				ptr_b = ptr_b->next;
		
		}
		return true;
	}

	template <typename T>
	void SLQueue<T>::remove_minimums()
	{
		SLNode<T> *ptr, *min_node = head, *prev = head, *target = NULL;
		T min_value;

		// find min
		for (ptr = head; ptr; ptr = ptr->next) {
			if (ptr->val < min_node->val) {
				min_node = ptr;
			}
		}

		ptr = head; 
		// delete min
		if (!!min_node) {
			min_value = min_node->val;
			while (ptr) {
				if (min_value == ptr->val) {
					target = ptr;
					if (target == head) {
						head = head->next;
						ptr = head;
					}	else {
						prev->next = target->next;
						ptr = prev;
					}
					if (target == tail) 
						tail = prev;
					delete target;
				} else {
					prev = ptr;
					ptr = ptr->next;
				}
			}
		}

	}

	template <typename T>
	void SLQueue<T>::remove_last_minimum()
	{
		SLNode<T> *ptr, *min_node = head, *min_node_prev = NULL, *prev = head;

		// find min
		for (ptr = head; ptr; ptr = ptr->next) {
			if (ptr->val <= min_node->val) {
				min_node = ptr;
				min_node_prev = prev;
			}
			prev = ptr;
		}

		if (tail == min_node) {
			if (tail == head) 
				tail = tail->next;
			else 
				tail = min_node_prev;
		}
		
		if (head == min_node) 
			head = head->next;
		else 
			min_node_prev->next = min_node->next;
		

		delete min_node;
	}

	template <typename T>
	SLNode<T> *SLQueue<T>::interleave_queue()
	{
		SLNode<T> *a_prev = NULL, *a = head;
		SLNode<T> *b = head, *b_prev = NULL, *b_node = NULL;
		bool step_pointer = false;

		for (SLNode<T> *ptr = head; ptr; ptr = ptr->next) {
			step_pointer = !step_pointer;
			if (step_pointer) {
				b_prev = b;
				b = b->next;
			}
		}
		b_prev->next = NULL;

		while (!!b) {
			b_node = b;
			b = b->next;
			if (!!a) {
				b_node->next = a->next;
				a->next = b_node;
				a_prev = b_node;
			} else {
				a_prev->next = b_node;
				b = NULL;
			}
		}
		return a;
	}
	
	template <typename T>
	bool SLQueue<T>::is_palindrome(SLQueue<T> &curr_queue)
	{
		SLStack<T> stack;
		std::tuple <T, bool> x_stack, x_queue; 
		unsigned counter = 0;

		// find size 
		while (!curr_queue.is_empty()) {
			counter++;
			stack.push(std::get<0>(curr_queue.dequeue()));
		}

		// throw back into queue
		while (!stack.is_empty()) {
			curr_queue.enqueue(std::get<0>(stack.pop()));
		}

		// copy values in queue to stack
		for (int i = counter; i-- ;) {
			stack.push(curr_queue.front()->val);
			curr_queue.enqueue(std::get<0>(curr_queue.dequeue()));
		}

		//	compare values
		while ( !stack.is_empty() ) {
			x_stack = stack.pop();
			x_queue = curr_queue.dequeue();

			if (!std::get<1>(x_queue) || (std::get<0>(x_stack) != std::get<0>(x_queue))) {
				return false;
			}

			if (std::get<0>(x_stack) == std::get<0>(x_queue)) {
				curr_queue.enqueue(std::get<0>(x_stack));
			}

		}

		return true;
	
	}

	template <typename T>
	void SLQueue<T>::reorder_absolute_queue(SLQueue<T> &queue)
	{
		SLStack<T> stack;			// max values at bottom
		T queue_data;

		while (!queue.is_empty()) {

			queue_data = std::get<0>(queue.dequeue());

			while (!stack.is_empty()) {
				if (queue_data > stack.top()->val) {
					queue.enqueue(std::get<0>(stack.pop()));
				} else {
					break;
				}
			}
			stack.push(queue_data);
		}
	
		while (!stack.is_empty()) {
			queue.enqueue(std::get<0>(stack.pop()));
		}
	}

	template class SLQueue<unsigned>;
	template class SLQueue<signed>;

	template <typename T>
	void SLStack<T>::push(const T& value)
	{
		SLNode<T> *node = this->slnode(value);
		if (this->head == NULL) {
			this->head = node;
			this->tail = node;
		} else {
			node->next = this->head;
			this->head = node;
		}
	}
	


	template<typename T>
	SLNode<T>* SLStack<T>::top()
	{
		return this->head; 
	}

	template<typename T>
	std::tuple<T, bool>  SLStack<T>::pop()
	{
		SLNode<T>* target = NULL;
		T value;
		bool state;

		if (this->head != NULL) {
			target = this->head;
			value = target->val;
			this->head = this->head->next;
			state = true;
		} else {
			value = NULL;
			state = false;
		}

		if (this->head == NULL) {
			this->head = NULL;
			this->tail = NULL;
		}

		if (!!target) {
			delete target;
		}

		return  { value, state };
	}
	
	template <typename T>
	bool SLStack<T>::compare_stacks(SLNode<T>* a, SLNode<T>* b)
	{
		return  this->compare_queues(a, b);
	}

	template <typename T>
	 SLStack<T> SLStack<T>::copy(const  SLStack<T>&  curr_stack)
	{
		SLStack<T> stack;
		SLQueue<T> queue;
		
		for (auto ptr = curr_stack.head; ptr; ptr = ptr->next) 
			stack.push(ptr->val);
	
		while (!stack.is_empty()) 
			queue.enqueue(std::get<0>(stack.dequeue()));

		while (!queue.is_empty()) 
			stack.push(std::get<0>(queue.dequeue()));
	
		return  stack;
	}

	 template <typename T>
	 void SLStack<T>::remove_stack_min(unsigned mode)
	 {
		 SLQueue<T> queue;
		 T min = NULL, stack_data, queue_data;
		 unsigned count = 0;
		 bool state = false;
		 
		 // write to queue (store min)
		 while (!this->is_empty()) {
			 stack_data = std::get<0>(this->pop());
			 if (count == 0 || stack_data < min) {
				 min = stack_data;
				 ++count;
			 }
			 queue.enqueue(stack_data);
		 }

		 while (!queue.is_empty()) {
			 queue_data = std::get<0>(queue.dequeue());
			 /* remove all mins */
			 if (mode == 0) {
				 if (queue_data != min) {
					 this->push(queue_data);
				 }
			 }

			 /* remove first occurence of min*/
			 if (mode == 1) {
				 if (queue_data != min || (state && (queue_data == min))) {
					this->push(queue_data);
				 }
				 state |= (queue_data == min);
			 }

			 /* remove first occurence of min*/
			 if (mode == 2) {
				 if (queue_data != min || count > 0) {
					 this->push(queue_data);
				 }
				 count -= +(queue_data == min);
			 }

		 }

		 // flip stack 
		 while (!this->is_empty()) {
			 stack_data = std::get<0>(this->pop());
			 queue.enqueue(stack_data);
		 }
		 while (!queue.is_empty()) {
			 queue_data = std::get<0>(queue.dequeue());
				 this->push(queue_data);
		 }

	 }
	 
	 template <typename T>
	 void SLStack<T>::remove_newest_min()
	 {
		 remove_stack_min(1);
	 }

	 template <typename T>
	 void  SLStack<T>::remove_oldest_min()
	 {
		 remove_stack_min(2);
	 }

	 template <typename T>
	 void SLStack<T>::partition()
	 {
		 SLQueue<T> queue;
		 T stack_data;
		 bool has_neg = false, has_pos = false;

		 while (!this->is_empty()) {

			 stack_data = std::get<0>(this->pop());
			 
			 if (stack_data <= 0  && has_pos) {
				 while (queue.front()->val < 0 ) {
					 queue.enqueue(std::get<0>(queue.dequeue()));
				 }
			 } 
			 
			 if (stack_data > 0  && has_neg){
				 while (queue.front()->val > 0) {
					 queue.enqueue(std::get<0>(queue.dequeue()));
				 }
			 }

			 queue.enqueue(stack_data);
			 has_neg |= (stack_data <= 0);
			 has_pos |= (stack_data > 0);
		 }

		 while (!queue.is_empty()) {
			 this->push(std::get<0>(queue.dequeue()));
		 }
	 }

	 template <typename T>
	 void SLStack<T>::switch_pairs()
	 {
		 SLQueue<T> queue;
		 std::tuple<T, bool> a, b, c = {NULL, NULL};
		 unsigned count = 0;

		 while (!this->is_empty() ) {
			 count++;
			 queue.enqueue(std::get<0>(this->pop()));
		 }

		 if (count % 2 == 1) {
			 c = queue.dequeue();
			 count--;
		 }
		 
		 for (count -= 2; !queue.is_empty() ; count -= 2) {
			 for (int i = count; i--; ) 
				 queue.enqueue(std::get<0>(queue.dequeue()));
			 a = queue.dequeue();
			 b = queue.dequeue();
			 if (std::get<1>(a)) 
				 this->push(std::get<0>(a));
			 if (std::get<1>(b))
				 this->push(std::get<0>(b));
		 }
		 
		 if (std::get<1>(c)) 
			 this->push(std::get<0>(c));
	 }

	 template <typename T>
	 bool SLStack<T>::is_sorted(SLStack<T> &stack)
	 {
		 SLQueue<T> queue;
		 T data;
		 while (!stack.is_empty()) {
			 data = std::get<0>(stack.pop());
			 if (!queue.is_empty()) {
				 if (data < queue.front()->val)
					 return false;
			 }
			 queue.enqueue(data);
		 }
		 return true;
	 }

	 template <typename T> 
	 void SLStack<T>::mirror(SLStack<T>& stack)
	 {
		 int count = 0;
		 SLQueue<T> queue;
		 T data; 

		 while ( !stack.is_empty() ) {
			 data = std::get<0>(stack.pop());
			 queue.enqueue(data);

			 for (int i = count; i--;) {
				 queue.enqueue(std::get<0>(queue.dequeue()));
			 }
			 queue.enqueue(data);
			 count += 2;
		 }

		 for (int i = count / 2; i--;) {
			queue.enqueue(std::get<0>(queue.dequeue()));
		 }

		 while (!queue.is_empty()) {
			 this->push(std::get<0>(queue.dequeue()));
		 }

	 }


	template class SLStack<unsigned>;
	template class SLStack<signed>;

	template <typename T>
	std::tuple <T, bool> SLQueue_via_Stacks<T>::dequeue()
	{
		return b.pop();
	}

	template <typename T>
	void SLQueue_via_Stacks<T>::enqueue(const T& value)
	{
		move_src_to_dest(b, a); /* b -> a */
		a.push(value);
		move_src_to_dest(a, b); /* a -> b */
	}

	template <typename T>
	void SLQueue_via_Stacks<T>::move_src_to_dest(SLStack<T>& src, SLStack<T>& dest)
	{
		bool is_valid = false;
		T data;
		while (!src.is_empty()) {
			auto tuple = src.pop();
			if (std::get<1>(tuple)) {
				dest.push(std::get<0>(tuple));
			}
		}
	}

	template <typename T>
	void  SLQueue_via_Stacks<T>::print()
	{
		for (SLNode<T>* ptr = b.top(); ptr; ptr = ptr->next) {
			std::cout << "\t data \t " << ptr->val << '\n';
		}
	}

	template class SLQueue_via_Stacks<unsigned>;
	template class SLQueue_via_Stacks<signed>;

	template <typename T>
	SLNode<T>* Dequeue<T>::front()
	{
		return this->front();
	}

	template <typename T>
	SLNode<T>* Dequeue<T>::back()
	{
		return this->back();
	}

	template <typename T>
	void Dequeue<T>::push_back(const T value)
	{
		this->enqueue(value);
	}

	template <typename T>
	void Dequeue<T>::push_front(const T value)
	{
		this->push(value);
	}

	template <typename T>
	std::tuple<T, bool> Dequeue<T>::pop_front()
	{
		return this->pop();
	}

	template <typename T>
	std::tuple<T, bool> Dequeue<T>::pop_back()
	{
		SLNode<T>* header = this->head, * prev = NULL, *ptr;
		T value;

		for (ptr = this->head; (ptr != this->tail) && (ptr != NULL); ptr = ptr->next) {
			prev = ptr;
		}

		if (!this->head) {
			return { NULL, false };
		}

		if (this->head == this->tail) {
			return pop_front();
		}

		if (!!prev) {
			prev->next = prev->next->next;
			value = ptr->val;
			this->tail = prev;
			delete ptr;
			return { value, true };
		}

	}

	template <typename T>
	void Dequeue<T>::print()
	{
		dynamic_cast<SLQueue<T>*>(this)->print();
	}

	template class Dequeue<unsigned>;
	template class Dequeue<signed>;

	template <typename T>
	void CirQueue<T>::shrink(const unsigned &size)
	{
		SLNode<T>* node = head, * prev = head, *target;
		
		for (int i = size; i--;) {
			prev = node; 
			node = node->next;
		}

		if (!!prev) {
			tail = prev;
			target = node;
			prev->next = NULL;

			while (!!node) {
				target = node ;
				node = node->next;
				delete target;
			}

		}
	}

	template <typename T>
	void CirQueue<T>::grow(const unsigned& size)
	{
		SLNode<T>* node = head, *prev = head; 
		
		if (size < 1)
			return;

		if (size < cap) {
			return shrink(size);
		}

		if (size >= cap)
			cap = size;
	}

	template <typename T>
	void CirQueue<T>::print() {
		unsigned count = 0;
		for (auto ptr = head; ptr; ptr = ptr->next) {
			printf("\t	[%d]\t [%d]	\n", ptr->val, count++);
		}
	}

	template <typename T>
	std::tuple<T, bool>  CirQueue<T>::front()
	{
		if (!!head) {
			return { head->val, true };
		}
		return { 0, NULL };
	}

	template <typename T>
	unsigned CirQueue<T> ::size()
	{
		return curr_size;
	}

	template <typename T>
	bool CirQueue<T>::is_empty()
	{
		return head == NULL;
	}

	template <typename T>
	bool CirQueue<T>::contains(const T& value)
	{
		for (auto ptr = head; ptr; ptr = ptr->next) {
			if (ptr->val == value) {
				return true;
			}
		}
		return false;
	}

	template <typename T>
	void CirQueue<T>::enqueue(const T& value)
	{
		SLNode<T> *tmp, *node = new SLNode<T>{ value, NULL };

		if (curr_size >= cap) {
			tmp = head; 
			head = head->next;
			delete tmp;
		}
	
		if (!head) {
			head = node;
			tail = head;
		} else {
			tail->next = node;
			tail = node; 
		}
		curr_size += +(curr_size < cap);

	}

	template <typename T>
	std::tuple<T, bool>  CirQueue<T>::dequeue()
	{
		SLNode<T> *target; 
		T value;
		
		if (!!head) {
			target = head; 
			value = target->val;
			head = head->next;
			delete target; 
			return { value , true };
			--curr_size;
		}
		return { NULL, false };
	}

	template <typename T>
	bool CirQueue<T>::is_full()
	{
		return curr_size == cap;
	}

	template class CirQueue<unsigned>;
	template class CirQueue<signed>;

	unsigned weak_finger(unsigned weak_finger, unsigned usage_count)
	{
		unsigned curr_finger = 1, tick = 1, counter = 0, weak_finger_count = 0;
		
		if ((weak_finger < 1 && weak_finger > 5)) {
			return 0; 
		}
		
		while (!(weak_finger == curr_finger && weak_finger_count == usage_count)) {
			
			if (curr_finger == 1) {
				tick = 1;
			}

			if (curr_finger == 5) {
				tick = -1;
			}
			
			weak_finger_count += (curr_finger == weak_finger) ? 1: 0;
			curr_finger += tick;
			counter++;
		
		}
		return counter;
	}

}