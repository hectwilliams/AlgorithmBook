#include <utility>
#include <math.h>
#include "chapter6.h"

template <typename T>
SLNode<T>* slnode(const T& value)
{
	SLNode<T>* node = new SLNode<T>;
	node->next = NULL;
	node->val = value;
	return node;
}

template <typename T>
void SLQueue<T>::enqueue(const T& value)
{
	SLNode<T>* tail_node = slnode(value);
	if (this->head == NULL) {
		this->head = tail_node;
		this->tail = tail_node;
	} else {
		this->tail->next = tail_node;
		this->tail = tail_node;
	}
	++this->counter;
}

template <typename T>
std::pair <bool, T> SLQueue<T>::dequeue()
{
	std::pair<bool ,T> rslt;
	SLNode<T>* tmp;

	if (this->head == NULL) {
		rslt = { NULL, NULL };
	} else {
		tmp = this->head;
		rslt = {true, tmp->val};
		this->head = this->head->next;
		if (this->head == NULL)
			this->tail = NULL;
		free(tmp);
		--this->counter;
	}
	return rslt;
}

template <typename T>
std::pair<bool, T> SLQueue<T>::front()
{
	if (!!this->head)
		return { true, this->head->val };
	else 
		return {false, NULL};
}

template <typename T>
bool SLQueue<T>::contains(const T& value)
{
	SLNode<T>* runner = this->head;
	while (runner) {
		if (runner->val == value)
			return true;
		runner = runner->next;
	}
	return false; 
}

template <typename T>
bool SLQueue<T>::is_empty()
{
	return (!!this->head) ? false : true;
}

template <typename T>
unsigned SLQueue<T>::size()
{
	return this->counter;
}

template <typename T>
bool SLQueue<T>::compare_queue(SLQueue<T> &a, SLQueue<T> &b)
{
	if (a.size() != b.size())
		return false; 
	
	for (int i = 0; i < a.size(); i++) {
		if (a.front.second != b.front.second)
			return false;
		a.enqueue(a.dequeue().second);
		b.enqueue(b.dequeue().second);
	}
}

template <typename T>
void SLQueue<T>::remove_minimums()
{
	std::pair<bool, T> obj = { false, NULL };
	T data;

	unsigned size = this->size();
	for (int i = 0; i < size; i++) {
		if (obj.first == false)
			obj.second = this->front().second;
		if (this->front().second > obj.second)
			obj.second = this->front().second;
		this->enqueue(this->dequeue());
	}

	for (int i = 0; i < size; i++) {
		data = this->dequeue().second;
		if (data != obj.second)
			this->enqueue(data);
	}
}

template <typename T>
void SLQueue<T>::display()
{
	for (int i = 0; i < this->size(); i++) {
		printf("[%d]", this->front().second);
		this->enqueue(this->dequeue().second);
	}
}

template <typename T>
bool SLQueue<T>::is_palindrome()
{
	SLStack<T> stack;
	std::pair<bool, T> data; 
	bool result = true; 

	for (int i = 0; i < this->size(); i++) {
		stack.push(this->front().second);
		this->enqueue(this->dequeue().second);
	}

	for (int i = 0; i < this->size(); i++) {
		data = stack.pop();
		result &= (data.second == this->front().second);
		this->enqueue(this->dequeue().second);
	}
	return result;
}

template <typename T>
void SLQueue<T>::reorder_absolute_queue()
{
	SLStack<T> stack;
	std::pair<bool, T> obj; 

	while (this->counter) {
		obj = this->dequeue(); 
		while (stack.top().second < obj.second && stack.size ) {
			this->enqueue(stack.pop().second);
		}
		stack.push(obj.second);
	}

	while (stack.size) {
		this->enqueue(stack.pop().second);
	}

}

template <typename T>
void SLQueue<T>::interleave_queue()
{
	T data; 
	SLQueue<T> queue;
	unsigned mid = std::floor(this->size() / 2) + +(this->size() % 2 == 1);
	unsigned size = this->size();
	
	/* move second half to local queue */
	for (int i = 0; i <= this->size(); i++) {
		data = this->dequeue().second;
		if (i < mid)
			this->enqueue(data);
		else
			queue.enqueue(data);
	}

	/* interleave base queue and inner queue */
	size = queue.size();
	for (int i = 0; i < size + 1; i++) {
		this->enqueue(this->dequeue().second);
		if (queue.size())
			this->enqueue(queue.dequeue().second);
	}

}

template <typename T>
void ArrStack<T>::push(const T& value)
{
	if (this->collection == NULL)
		this->collection = new std::vector<T>;
	collection->push_back(value);
	this->size++;
}

template <typename T>
std::pair<bool, T> ArrStack<T>::pop()
{
	std::pair<bool, T> result_pair = {NULL, NULL};

	if (this->collection == NULL)
		return result_pair;
	if (this->size) {
		std::get<0>(result_pair) = true;
		std::get<1>(result_pair) = this->collection->at(this->size - 1);
		this->collection->pop_back();
		this->size--;
	}
	return result_pair;
}

template <typename T>
std::pair<bool, T> ArrStack<T>::top()
{
	std::pair<bool, T> result_pair = { NULL, NULL };
	unsigned size = this->size;

	if (this->collection == NULL)
		return result_pair;
	if (size)
		result_pair = { true, this->collection->at(size - 1) };
	return result_pair;
}

template <typename T>
bool ArrStack<T>::contains(const T &value)
{
	bool result = false;
	T data;

	for (int i = 0; i < this->size; i++) {
		data = this->pop().second;
		result |= (data == value);
		this->push(data);
	}
	
	return result;
}

template <typename T>
bool ArrStack<T>::is_empty()
{
	if (this->size == 0)
		return true;
	else
		return false; 
}

template <typename T>
void ArrStack<T>::display()
{
	T data;
	ArrStack stack;
	unsigned length = this->size;

	while (this->size) {
		data = this->pop().second;
		printf("%d", data);
		stack->push(data);
	}

	while (stack->size) {
		this->push(stack->pop().second);
	}		

}

template <typename T>
void SLStack<T>::push(const T &value) {
	SLNode<T>* node = slnode(value);

	if (this->head == NULL) {
		this->head = node;
		this->tail = node;
	} else {
		node->next = this->head;
		this->head = node; 
	}
	this->size++;
}

template <typename T>
std::pair<bool, T> SLStack<T>::pop()
{
	std::pair<bool, T> result;
	
	result.first = false;
	result.second = NULL;

	if (this->size) {
		result.first = true;
		result.second = this->head->val;
		this->head = this->head->next;
		this->size--;
	}
	return result;
}

template <typename T>
std::pair<bool, T> SLStack<T>::top()
{
	std::pair <bool, T> result;

	result.first = false;

	if (this->size)
		result.second = this->head->val;
	return result;
}

template <typename T>
void SLStack<T>::display() {
	std::pair<bool, T> pair;
	SLStack stack;
	int sizee = this->size;

	while (this->size) {
		pair = this->pop();
		printf("[%d]-\n", pair.second);
		stack.push(pair.second);
	}

	for (int i = 0; i < sizee; i++) {
		this->push(stack.pop().second);
	}

}

template <typename T>
bool SLStack<T>::contains(const T& value)
{
	std::pair < bool, T> data_pair;
	SLStack stack;

	while (this->size) {
		if (this->top().second == value)
			return true;
		stack.push(this->pop().second);
	}

	while (stack.size)
		this->push(stack.pop().second);
	
	return false;
}

template <typename T>
bool SLStack<T>::is_empty() 
{
	if (this->size == 0)
		return true;
	else
		return false; 
}

template <typename T>
bool compare_stacks( SLStack<T>& a,  SLStack<T>& b)
{
	bool result = false;
	SLStack<T> loc_stack;
	unsigned int size = a.size;
	
	if (a.size != b.size)
		return result;

	result = true; 

	for (int i = 0; i < size; i++) {
		result &= (a.top().second == b.top().second);
		loc_stack.push(a.pop().second);
		loc_stack.push(b.pop().second);
	}
	
	for (int i = 0; i < size; i++) {
		a.push(loc_stack.pop().second);
		b.push(loc_stack.pop().second);
	}

	return result;
}

template <typename  T>
SLStack<T> SLStack<T>::copy()
{
	SLStack<T> stack;
	SLQueue<T> buffer_queue;
	std::pair<bool, T> data_pair;

	if (this->size == 0)
		return stack;

	while (this->size) {
		buffer_queue.enqueue(this->pop().second);
	}

	for (int i = buffer_queue.size(); i-- ; ) {
		/* rotate moving tail element to front*/
		for (int j = 0; j < i; j++) {
			buffer_queue.enqueue(buffer_queue.dequeue().second);
		}
		/*write to both stacks*/
		data_pair = buffer_queue.dequeue();
		this->push(data_pair.second);
		stack.push(data_pair.second);
	}

	stack.display();
}

template <typename T>
void SLStack<T>::remove_stack_min()
{
	
	SLQueue<T> queue;
	std::pair <bool, T> min_obj = {false, NULL};
	T value;

	while (this->size) {
		value = this->pop().second;
		if (min_obj.first == false || value < min_obj.second) {
			min_obj = { true,  value };
		}
		queue->enqueue(value);
	}
	
	for (int rot = queue->size() - 1; rot > 0 ; rot--) {
		for (int j = 0; j < rot; j++) {
			queue->enqueue(queue->dequeue().second);
		}
		value = queue->dequeue().second;
		if (value != min_obj.second) {
			this->push(value);
		}
	}
}

template <typename T>
void SLStack<T>::partition()
{
	unsigned cnt = 0;
	SLQueue<T> queue;
	std::pair<bool,T>  data;

	while (this->size) {
		queue.enqueue(this->pop().second);
		cnt++;
	}

	while (cnt--) {
		data = queue.dequeue();
		if (data.second >= 0) {
			this->push(data.second);
		} else {
			queue.enqueue(data.second);
		}
	}

	while (queue.size()) {
		this->push(queue.dequeue().second);
	}
}

template <typename T>
void SLStack<T>::switch_pairs()
{
	SLQueue<T> queue;
	int rotate = 0;
	
	while (this->size) {
		queue.enqueue(this->pop().second);
	}

	while (1) {
		rotate = queue.size() - 2;

		if (rotate > 0) {
			for (int i = 0; i < rotate; i++) {
				queue.enqueue(queue.dequeue().second);
			}
		}

		if (queue.size())
			this->push(queue.dequeue().second);
		if (queue.size())
			this->push(queue.dequeue().second);
		if (rotate <= 0)
			break;
	}
}

template <typename T>
void SLStack<T>::mirror()
{
	SLStack<T> stack;
	std::pair<bool, T> tmp;
	int count = 0;

	while (this->size)
		stack.push(this->pop().second);
	
	while (stack.size) {
		count = 0;
		tmp = stack.pop();
		
		while (this->size) {
			count++;
			stack.push(this->pop().second);
		}
		
		this->push(tmp.second);
		while (count--) {
			this->push(stack.pop().second);
		}
		this->push(tmp.second);
	}

}


template <typename T>
void SLStack<T>::is_sorted()
{
	SLStack<T> stack;
	bool result = true;

	while (this->size) {
		if (stack.size) {
			result &= (this->top().second < stack.top().second);
		}
		stack.push(this->pop().second);
	}
	while (stack.size) {
		this->push(stack.pop().second);
	}

	return result;
}

template <typename  T>
void Queue_Two_Stacks<T>::push(const T &value)
{
	while (b->size)
		a->push(b->pop().second);
	
	a->push(value);

	while (a->size)
		b->push(a->pop().second);
}

template <typename  T>
std::pair<bool, T> Queue_Two_Stacks<T>::pop()
{
	std::pair<bool, T> result; 

	result.first = false;
	result.second = NULL;

	while (b->size) {
		a->push(b->pop().second);
	}

	if (a->size) {
		result = a->pop();
	}

	while (a->size)
		b->push(a->pop().second);
	
	return result;
}

template <typename T>
std::pair<bool, T> Queue_Two_Stacks<T>::top() {

	std::pair<bool, T> result;
	result.first = false;
	result.second = NULL;

	while (b->size) {
		a->push(b->pop().second);
	}

	result = a->top();

	while (a->size)
		b->push(a->pop().second);

	return result;
}

template <typename T>
bool Queue_Two_Stacks<T>::contains(const T& value) 
{
	bool boolean = false;

	while (b->size) {
		if (b->top().second == value) {
			boolean = true;
		}
		a->push(b->pop().second);
	}

	while (a->size)
		b->push(a->pop().second);
}


template <typename T>
bool  SLQueueStackBase<T>::is_empty()
{
	return this->size == 0;
}

template <typename T>
bool  SLQueueStackBase<T>::contains(const T& value)
{
	SLNode<T> *node = this->head;
	while (node) {
		if (node->val == value)
			return true;
		node = node->next;
	}
	return false;
}

template <typename T>
void  SLQueue2<T>::enqueue(const T& value)
{
	SLNode<T>* node = slnode(value);
	if (this->head == NULL) {
		this->head = node;
		this->tail = node;
	} else {
		this->tail->next = node;
		this->next = node;
	}
	this->size++;
}

template <typename T>
std::pair<bool, T>  SLQueue2<T>::dequeue()
{
	std::pair<bool, T> pair_result;
	pair_result.first = false;

	if (this->head) {
		if (this->head == this->tail)
			this->tail = NULL;
		pair_result.second = this->head->val;
		pair_result.first = true;
		this->head = this->head->next;
		this->size--;
	}
	return pair_result;
}

template <typename T>
void SLStack2<T>::push(const T& value)
{
	SLNode<T>* node = slnode(value);
	if (this->head == NULL) {
		this->head = node;
		this->tail = node;
	}else {
		node->next = this->head;
		this->head = node;
	}
	this->size++;
}

template <typename T>
std::pair<bool, T> SLStack2<T>::pop()
{
	std::pair<bool, T> pair_result;
	pair_result.first = false;
	
	if (this->head) {
		if (this->head == this->tail)
			this->tail = NULL;
		pair_result.first = true;
		pair_result.second = this->head->val;
		this->head = this->head->next;
		this->size--;
	}
	return pair_result;
}

template <typename T>
void Dequeue<T>::push_front(const T& value)
{
	this->push(value);
}

template <typename T>
void Dequeue<T>::push_back(const T& value)
{
	this->enqueue(value);
}

template <typename T>
std::pair<bool, T> Dequeue<T>::pop_front()
{
	return this->pop();
}

template <typename T>
std::pair<bool, T> Dequeue<T>::pop_back()
{
	SLQueueStackBase<T>* base = this;		// downcasting
	
	for (int i = 1; i < base->size; i++) {
		this->enqueue(this->dequeue().second);
	}
	return this->pop();
}

template <typename T>
std::pair<bool, T> Dequeue<T>::front()
{
	SLQueueStackBase<T>* base = this;		// downcasting
	std::pair<bool, T> pair_result = {false, NULL};
	
	if (base->head) {
		pair_result.first = true;
		pair_result.second = base->head->val;
	}
	return pair_result;
}

template <typename T>
std::pair<bool, T> Dequeue<T>::back()
{
	SLQueueStackBase<T>* base = this;		// downcasting
	std::pair<bool, T> pair_result = { false, NULL };

	if (base->tail) {
		pair_result.first = true;
		pair_result.second = base->tail->val;
	}
	return pair_result;
}

template <typename T>
bool Dequeue<T>::contains(const T& value)
{
	SLQueueStackBase<T>* base = this;		
	return base->contains(value);
}

template <typename T>
bool Dequeue<T>::is_empty()
{
	SLQueueStackBase<T>* base = this;		
	return base->is_empty();
}


template <typename T>
std::pair<bool, T> CirQueue<T>::front()
{
	std::pair<bool, T> result = { false, NULL };
	
	if (this->head) {
		result.first = true;
		result.second = this->head->val;
	}
	return result;
}

template <typename T>
bool CirQueue<T>::is_empty()
{
	return this->size == 0;
}

template <typename T>
bool CirQueue<T>::enqueue(const T &value)
{
	SLNode *node;

	if (size < capacity) {
		size++;
		node = slnode(value);
		if (this->head == NULL) {
			this->head = node;
			this->tail = node;
		} else {
			this->tail->next;
			this->tail = node;
		}
		return true;
	}

	return false;
}

template <typename T>
std::pair <bool, T> CirQueue<T>::dequeue()
{
	std::pair<bool, T> data_out = {false, NULL};

	if (this->head) {
		if (this->head == this->tail) {
			this->tail = NULL;
		}
		data_out.first = true;
		data_out.second = this->head->val;
		this->head = this->head->next;
		this->size--;
	}
	return data_out;
}

template <typename T>
bool CirQueue<T>::contains()
{
	std::pair <bool, T> data_obj;
	bool result = false;

	for (int i = 0; i < this->size; i++) {
		data_obj = this->dequeue();
		result |= data_obj.second();
		this->enqueue(data_obj.second());
	}
	return result;
}

template <typename T>
void CirQueue<T>::grow(unsigned int cap)
{
	int count = 0;
	SLNode<T>* node;

	if (cap <= 0)
		return;

	if (cap < capacity) {
		while (count < cap) {
			node = (count == 0) ? this->head : node->next;
			count++;
		}
	}

	capacity = cap;
}

int main (int argv, int **argc) {
	SLStack<int> stack;
	stack.push(7);
	stack.push(5);
	stack.push(3);
	stack.push(1);
	stack.mirror();
	stack.display();
}