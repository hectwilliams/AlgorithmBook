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

#ifndef CHAPTER6_H
#define CHAPTER6_H

namespace chapter6
{
	template <class T>
	class SLQueue;

	template <class T>
	class SLStack;


	template <typename T>
	struct SLNode {
		T val;
		SLNode<T> *next;
	};


	template <class T>
	class SLQueue {
	protected:
		SLNode<T>* slnode(const T& value) {
			return new SLNode<T>{ value, NULL};
		};
		SLNode<T>* head;
		SLNode<T>* tail;
	private:
		
	public:
		SLQueue<T>() : head{ NULL }, tail{ NULL } {}
		void enqueue(const T& value);
		SLNode<T>* front();
		SLNode<T>* back();

		std::tuple <T, bool> dequeue();
		bool contains(const T& value);
		bool is_empty();
		unsigned size();
		bool compare_queues(SLNode<T>* a, SLNode<T>* b);
		void remove_minimums();
		void remove_last_minimum();
		SLNode<T> *interleave_queue();
		bool is_palindrome(SLQueue<T> &curr_queue);
		virtual void print(SLNode<T>* node = NULL);
		void reorder_absolute_queue(SLQueue<T> &queue);
	};

	template <class T>
	class SLStack: virtual  public SLQueue<T> {
	public:
		SLStack<T>() {}
		void push(const T& value);
		SLNode<T> *top();
		std::tuple<T, bool> pop();
		bool compare_stacks(SLNode<T>* a, SLNode<T>* b);
		SLStack<T> copy(const  SLStack<T>& curr_stack);
		void remove_stack_min(unsigned mode = 0);
		void remove_newest_min();
		void remove_oldest_min();
		void partition();
		void switch_pairs();
		bool is_sorted(SLStack<T> &stack);
		void mirror(SLStack<T>& stack);

	};

	template <class T>
	class SLQueue_via_Stacks : public SLQueue<T> {
		SLStack<T> a, b;
		void move_src_to_dest( SLStack<T>& src,  SLStack<T>& dest);
	public:
		SLQueue_via_Stacks() {}
		virtual std::tuple <T, bool> dequeue();
		void print();
		virtual void enqueue(const T& value);
	};

	template <class T>
	class Dequeue : virtual public SLQueue<T>, virtual  public SLStack<T> {
	public:
		virtual SLNode<T>* front();
		virtual SLNode<T>* back();
		void push_back(const T value);
		void push_front(const T value);
		std::tuple<T, bool> pop_front();
		std::tuple<T, bool> pop_back();
		void print();
	};

	template <typename T>
	class CirQueue {
		unsigned cap = 10;
		unsigned curr_size = 0;
		SLNode<T>* head;
		SLNode<T>* tail;
		void shrink(const unsigned & size);
	
	public:
		CirQueue<T>() : head{ NULL }, tail{ NULL }
		{
			grow();
		}
		void grow(const unsigned& size = 10);
		void print();
		
		std::tuple<T, bool> front();
		unsigned size();
		bool is_empty();
		bool contains(const T& value);
		void enqueue(const T &value);
		std::tuple<T, bool> dequeue();
		bool is_full();
	};

	unsigned weak_finger(unsigned weak_finger, unsigned usage_count);
}

#endif