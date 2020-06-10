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
#include "chapter5.h"

extern int errno;



namespace chapter5
{
	template <typename T>
	ListNode<T> * List<T>::add_front(const T& value)
	{
		ListNode<T>* node = listnode(value);
		if (!!head) {
			node->next = head;
		}
		head = node;
		return head;
	}

	template <typename T>
	void List<T>::print() 
	{
		for (ListNode<T>* runner = head; runner; runner = runner->next) {
			std::cout << runner->value << '\n';
		}
	}

	template <typename T>
	bool List<T>::contains(const T& value)
	{
		for (ListNode<T>* runner = head; runner; runner = runner->next) {
			if (runner->value == value)
				return true;
		}
		return false; 
	}

	template <typename T>
	ListNode<T>* List<T>::remove_front()
	{
		ListNode<T>* node = head;
		if(!!head) {
			head = node->next;
		}
		delete node;
		return head;
	}

	template <typename T>
	ListNode<T>* List<T>::front()
	{
		return head;
	}

	template class List <unsigned>;
	template class List <signed>;


	template <typename T>
	ListNode<T>* SList<T>::get_root()
	{
		return head;
	}

	template <typename T>
	ListNode<T>* SList<T>::add_front(const T& value)
	{
		ListNode<T>* node = listnode(value);
		if (!!head) {
			node->next = head;
		}
		head = node;
		return head;
	}

	template <typename T>
	void SList<T>::add_back(const T& value)
	{
		ListNode<T>* runner;
		if (!head) {
			add_front(value);
		} else {
			for (runner = head; runner->next; runner = runner->next) {}
			runner->next = listnode(value);;
		}
	}

	template <typename T>
	unsigned SList<T>::length(ListNode<T>* node)
	{
		unsigned count = 0;
		ListNode<T>* runner;
		for (runner = node; runner; runner = runner->next)
			count += 1;
		return count;
	}

	template <typename T>
	T SList<T>::Max(ListNode<T>* node)
	{
		T max = node->value;
		ListNode<T>* runner;
		for (runner = node; runner; runner = runner->next) {
			if (runner->value > max) {
				max = runner->value;
			}
		}
		return max;
	}

	template <typename T>
	T SList<T>::Min(ListNode<T>* node)
	{
		T min = node->value;
		ListNode<T>* runner;

		for (runner = node; runner; runner = runner->next) {
			if (runner->value < min) {
				min = runner->value;
			}
		}
		return min;
	}

	template <typename T>
	std::string SList<T>::display(ListNode<T> *node) 
	{
		std::string result;
		for (ListNode<T>* runner = node; runner; runner = runner->next) {
			result += std::to_string(runner->value) + (runner->next ? "," : "");
		}
		return result;
	}

	template <typename T>
	double SList<T>::average(ListNode<T>* node)
	{
		T avg = 0;
		double samples = 0.0;
		for ( ListNode<T> *runner = node ; runner; runner = runner->next) {
			avg += node->value;
			samples += 1.0;
		}
		return (samples != 0 ? avg / samples : samples);
	}

	template <typename T> 
	T SList<T>::back(ListNode<T>* node) 
	{
		ListNode<T>* runner;
		for (runner = node; runner->next; runner = runner->next) {}
		return runner->value;
	}

	template <typename T>
	ListNode<T>* SList<T>::move_value_to_front(T value)
	{
		ListNode<T> *prev = nullptr, *target;

		for (target = head; target; target = target->next) {
			if (target->value == value)
				break;
			prev = target;
		}

		if (target != head) {
			prev->next = target->next;
			target->next = head;
			head = target;
		}

		return head;
	}

	template <typename T>
	ListNode<T>* SList<T>::move_min_to_front()
	{
		ListNode<T> *prev = nullptr, *curr_min = head, *prev_min = nullptr;

		for (ListNode<T>* runner = head; runner; runner = runner->next) {
			if (runner->value < curr_min->value) {
				curr_min = runner;
				prev_min = prev;
			}
			prev = runner;
		}

		if (curr_min != head) {
			prev_min->next = curr_min->next;
			curr_min->next = head;
			head = curr_min;
		}
		
		return head;

	}

	template <typename T>
	ListNode<T>* SList<T>::move_max_to_front()
	{
		ListNode<T>* prev = nullptr, *prev_max = nullptr, * curr_max = head;

		for (ListNode<T>* runner = head; runner; runner = runner->next) {
			if (runner->value  > curr_max->value) {
				curr_max = runner;
				prev_max = prev;
			}
			prev = runner; 
		}

		if (curr_max != head) {
			prev_max->next = curr_max->next;
			curr_max->next = head;
			head = curr_max;
		}

		return head;
	}


	template <typename T>
	ListNode<T> * SList<T>::prepend_val(ListNode<T>* node, const T& value, const T& before)
	{
		ListNode<T>* prev = nullptr;
		ListNode<T>* prepend_node;

		for ((node = (!node) ? head : node ); node; node = node->next) {
			if (node->value == before)
				break;
			prev = node; 
		}

		if (!!node) {
			prepend_node = listnode(value);
			if (node == head) {
				prepend_node->next = head;
				head = prepend_node;
			}
			else if (node != head) {
				prev->next = prepend_node;
				prepend_node->next = node;
			}
		}

		return head;
	}

	template <typename T>
	ListNode<T> * SList<T>::append_val(ListNode<T> *node, const T &value, const T &after)
	{
		ListNode<T> *append_node, *prev;
		for ((node = (!node) ? head : node); node; node = node->next) {
			if (node->value == after)
				break;
			prev = node;
		}

		if (!!node) {
			append_node = listnode(value);
			append_node->next = node->next;
			node->next = append_node;
		}

		return head; 
	}

	template <typename T>
	ListNode<T>* SList<T>::remove_val(ListNode<T>* node, const T &value)
	{
		ListNode<T> *prev = NULL;

		for ( node = ((!node) ? head : node) ; node; node = node->next) {
			if (node->value == value) 
				break;
			prev = node;
		}

		if (!!node) {
			if (node == head) {
				head = head->next;
			} else {
				prev->next = node->next;
			}
			delete node;
		}

		return head;
	}

	template <typename T>
	ListNode<T>* SList<T>::split_on_value(ListNode<T> *node, const T& value)
	{
		ListNode<T>* prev = NULL;
		for ( node = (!node ? head : node) ; node; node = node->next) {
			if (node->value == value) 
				break;
			prev = node; 
		}

		if (node) {
			prev->next = NULL;
		}

		return node; 
	}

	template <typename T>
	ListNode<T>* SList<T>::concat(ListNode<T>* node_a, ListNode<T>* node_b)
	{
		ListNode<T>* runner_a;
		for (runner_a = node_a; runner_a->next; runner_a = runner_a->next) {}

		if (runner_a) {
			runner_a->next = node_b;
		}
		return node_a;
	}

	template <typename T>
	ListNode<T>* SList<T>::remove_negatives(ListNode<T>* node)
	{
		ListNode<T> *neg_node, *prev = NULL;
		node = (!node) ? head : node;

		while (node) {
			if (node->value < 0) {
				neg_node = node;
				if (node == head) {
					head = head->next;
					node = head; 
				} else {
					prev->next = neg_node->next;
					node = prev;
				}
				delete neg_node;
			} else {
				prev = node;
				node = node->next;
			}
		}
		return head;
	}

	template <typename T>
	ListNode<T>* SList<T>::partition(const T& value, ListNode<T>* node)
	{
		ListNode<T>* prev = NULL, *target, *partition = NULL ;
		node = (!node) ? head : node;

		partition = node;

		while (node) {
			if (node->value < value && node != head) { /* move value to right of p*/
				target = node;
				prev->next = target->next;
				target->next = head;
				head = target;
				node = prev;
			} else if (node->value == value && node != head) {
				target = node; 
				if (partition->next == target) { /* update parition */ 
					partition = target;
					node = target;
				} else {	/* move 'real' partition next of previous partition placeholder */
					prev->next = target->next;
					target->next = partition->next;
					partition->next = target;
					node = prev;
				}
			} else {
				prev = node;
				node = node->next;
			}

		}
		return head;
	}

	template <typename T>
	std::tuple<bool, T> SList<T>::second_to_last_value(ListNode<T>* node)
	{
		ListNode<T>* prev = NULL;
		for (node = (!node) ? head : node; node->next ; node = node->next) {
			prev = node;
		}
		if (!!prev) {
			return { true, prev->value };
		}
		return { false, NULL };
	}

	template <typename T>
	ListNode<T>* SList<T>::remove_self(ListNode<T>* node)
	{
		ListNode<T> *tmp = node->next;
		if (!!node) {
			node->value = node->next->value;
			node->next = node->next->next;
		}
		delete tmp;
		return head;
	}

	template <typename T>
	ListNode<T> *SList<T>::copy(ListNode<T>* node)
	{
		ListNode<T>* prev = NULL, *new_head = NULL, *new_node = NULL;
		for (node = (!node) ? head : node; node; node = node->next) {
			new_node = new ListNode<T>{ node->value, nullptr};
			if (prev == NULL) {
				new_head = new_node;
			} else {
				prev->next = new_node;
			}
			prev = new_node;
		}
		return new_head;
	}

	template <typename T>
	ListNode<T>* SList<T>::filter(T low_val, T high_val, ListNode<T>* node)
	{
		ListNode<T>* prev = NULL, * target = NULL, *new_head = NULL;
		node = (!node) ? head : node;

		while (node) {
			if (node->value < low_val || node->value >high_val) {
				target = node;
				if (target == head) {
					head = head->next;
					node = head;
					prev = NULL;
				} else {
					prev->next = target->next;
					node = prev;
				}
				delete target;
			} else {
				 new_head = (!new_head) ? node : new_head;
				prev = node;
				node = node->next;
			}
		}
		return  new_head;
	}

	template <typename T>
	std::tuple<bool, T> SList<T>::second_largest_value(ListNode<T>* node)
	{
		unsigned count = 0;
		T max_1 = NULL, max_2 = NULL;
		for (node = (!node) ? head : node;node; node = node->next) {
			if (count == 0 ) {
				max_1 = node->value;
				max_2 = max_2;
			} else if (node->value > max_1) {
				if (max_1 > max_2) {
					max_2 = max_1;
				}
				max_1 = node->value;
			}
			count++;
		}

		if (count >= 2) {
			return { true, max_2 };
		}

		return { false, NULL };
	}

	template <typename T>
	ListNode<T>* SList<T>::zip(ListNode<T>* a, ListNode<T>* b)
	{
		ListNode<T> *curr_head = a, *prev_a = a, *b_node_copy;

		while (b) {
			b_node_copy = b;
			b = b->next;
			if (a) {
				b_node_copy->next = a->next;
				a->next = b_node_copy;
				prev_a = a->next;
				a = (!!prev_a) ? prev_a->next : prev_a;
			} else if (b_node_copy) {
				prev_a->next = b_node_copy;
				b = NULL;
			}
		}

		return curr_head;
	}

	template <typename T>
	ListNode<T>* SList<T>::dedupe(ListNode<T>* node)
	{
		ListNode<T>* prev = NULL, * target, *curr_head = node;
		std::map<T, bool> histo;

		node = (!node) ? head : node;
		curr_head = node;

		while (node) {
			if (histo.find(node->value) != histo.end() ) {
				target = node;
				prev->next = target->next;
				node = target->next;
				delete target;
			} else {
				histo.insert({node->value, true});
				prev = node;
				node = node->next;
			}
	
		}
		return curr_head;
	}

	template class SList<unsigned>;
	template class SList<signed>;
}