#ifndef CHAPTER_6_H
#define CHAPTER_6_H

#include <iostream>  // std cout|cin 
#include <stdio.h>  //printf 
#include <utility> // make_pair 
#include <vector>

template <typename T>
struct SLNode {
	T val;
	SLNode<T> *next;
};

template <typename T>
SLNode<T>* slnode(const T & value);

template <typename T>
class SLQueue 
{
private:
	SLNode<T> *head;
	SLNode<T> *tail;

public: 
	unsigned counter;

	SLQueue<T>() : head{ NULL }, tail{ NULL }, counter{0}
	{}
	void enqueue(const T& value);
	std::pair<bool, T> dequeue();
	std::pair<bool, T> front();
	bool contains(const T &value);
	bool is_empty();
	unsigned size();
	bool compare_queue(SLQueue<T>& a, SLQueue<T>& b);
	void remove_minimums();
	void interleave_queue();
	void display();
	bool is_palindrome();
	void reorder_absolute_queue();
	void is_sorted();
};

template <typename T>
class ArrStack {
private:
	std::vector<T> *collection;
	unsigned size;
public: 
	ArrStack<T>() : collection{ NULL }, size{0}
	{}
	void push(const T &value);
	std::pair<bool, T> pop();
	std::pair<bool, T> top();
	bool contains(const T& value);
	bool is_empty();
	void display();
};

template <typename T>
class SLStack {

private:
	SLNode<T>* head;
	SLNode<T>* tail;

public:
	unsigned size;
	SLStack<T>() : head{ NULL }, tail{ NULL }, size{0}
	{}
	void push(const T& value);
	std::pair<bool, T> pop();
	std::pair<bool, T> top();
	bool contains(const T& value);
	bool is_empty();
	void display();
	SLStack<T> copy();
	void remove_stack_min();
	void partition();
	void switch_pairs();
	void is_sorted();
	void mirror();
};

template <typename T>
bool compare_stacks( SLStack<T> &a,  SLStack<T> &b);

template <typename T>
class Queue_Two_Stacks {

private:
	SLStack<T> *a;
	SLStack<T> *b; 

public:
	Queue_Two_Stacks<T>() :  a{new SLStack<T>}, b{ new SLStack<T> }
	{}

	void push(const T& value);
	std::pair<bool, T> pop();
	std::pair<bool, T> top();
	bool contains(const T& value);

};

template <typename T>
class SLQueueStackBase {
protected:
	unsigned size;
	SLNode<T>* head;
	SLNode<T>* tail;
public:
	SLQueueStackBase<T>(): size { 0 }, head{ NULL }, tail{ NULL }
	{}
	bool is_empty();
	bool contains(const T& value);
};

template <typename T>
class SLQueue2: virtual public SLQueueStackBase<T> {  // base class shared
protected:
	SLQueue2<T>()
	{}
	void enqueue(const T &value);
	std::pair<bool, T>  dequeue();
};

template <typename T>
class SLStack2: virtual public SLQueueStackBase<T> {  // base class shared
protected:
	SLStack2<T>()
	{}
	void push(const T &value);
	std::pair<bool, T> pop();
};

template <typename T>
class Dequeue : public SLStack2<T>, public SLQueue2<T> {
public:
	Dequeue<T>()
	{}
	void push_front(const T&value);
	void push_back(const T& value);
	std::pair<bool, T> pop_front();
	std::pair<bool, T> pop_back();
	std::pair<bool, T> front();
	std::pair<bool, T> back();
	bool contains(const T& value);
	bool is_empty();
};

template <typename T>
class CirQueue {
private:
	SLNode<T>* head;
	SLNode<T>* tail;
	unsigned capacity;
	unsigned size;

public:
	CirQueue<T>(unsigned size_in = 10) : head{ NULL }, tail{ NULL }, capacity{ (size_in <=0) ? 10 : size_in }, size { 0 }
	{}
	std::pair<bool, T> front();
	bool enqueue(const T& value);
	std::pair <bool, T> dequeue();
	bool is_empty();
	bool contains();
	void grow(unsigned int cap);

};

#endif