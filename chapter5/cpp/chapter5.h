#include <vector>
#include <string>
#include <map>
#include <set>
#include <deque>
#include <array>
#include <string_view>
#include <tuple>
#include <memory>
#include <mutex>
#include <future>

#ifndef CHAPTER5_H
#define CHAPTER5_H

namespace chapter5
{
	template <typename T>
	struct ListNode {
		T value;
		ListNode<T> *next;
	};

	template <class T>
	class List {
	private:
		ListNode<T>* head;
		ListNode<T>* listnode(const T& value) {
			return new ListNode<T>{ value, nullptr };
		}

	public:
		List<T>() : head{nullptr} {}
		ListNode<T> * add_front(const T &value);
		bool contains(const T &value);
		ListNode<T>* remove_front();
		ListNode<T>* front();
		void print();
	};

	template <class T>
	class SList {
	private:
		ListNode<T>* head;
		ListNode<T>* listnode(const T& value) {
			return new ListNode<T>{ value, nullptr };
		}

	public:
		SList<T>(): head{ nullptr } {}

		ListNode<T>* get_root();
		ListNode<T>* add_front(const T& value);
		void add_back(const T& value);

		unsigned length(ListNode<T>* node);
		T Max(ListNode<T>* node);
		T Min(ListNode<T>* node);
		std::string display(ListNode<T>* node);
		double average(ListNode<T>* node);
		T back(ListNode<T>* node);
		ListNode<T>* move_min_to_front();
		ListNode<T>* move_max_to_front();
		ListNode<T>* move_value_to_front(T value);
		ListNode<T> * prepend_val(ListNode<T>* node, const T& value, const T&  before);
		ListNode<T>* append_val(ListNode<T>* node, const T& value, const T& after);
		ListNode<T>* remove_val(ListNode<T>* node, const T& value);
		ListNode<T>* split_on_value(ListNode<T>* node , const T& value);
		ListNode<T>* concat(ListNode<T>* node_a , ListNode<T> *node_b);
		ListNode<T>* remove_negatives(ListNode<T>* node = NULL);
		ListNode<T>* partition(const T &value, ListNode<T>* node = NULL);
		std::tuple<bool,T>second_to_last_value(ListNode<T>* node = NULL);
		ListNode<T>* remove_self(ListNode<T>* node = NULL);
		ListNode<T>* copy(ListNode<T>* node = NULL);
		ListNode<T>* filter(T low_val, T high_val, ListNode<T>* node = NULL);
		std::tuple<bool, T> second_largest_value(ListNode<T>* node = NULL);
		ListNode<T>* zip(ListNode<T>* a, ListNode<T>* b);
		ListNode<T>* dedupe(ListNode<T>* node = NULL);

	};

}

#endif