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

#ifndef CHAPTER13_H
#define CHAPTER13_H


namespace chapter13 {
	template <class T>
	std::vector< T> InterleaveArrays(std::vector<T> a, std::vector<T> b) {
		std::vector<T> result;
		while (!a.empty() || !b.empty()) {
			if (a.size()) {
				result.push_back(a.front());
				a.erase(a.begin());
			}
			else if (b.size()) {
				result.push_back(b.front());
				b.erase(b.begin());
			}
		}
		return result;
	}


	template <class T>
	std::vector<T> MergeSortedArrays(std::vector<T> a, std::vector<T> b) {
		std::vector<T> res;
		int ptrA = 0, ptrB = 0;

		while (true) {
			if (res.size() == a.size() + b.size() ) {
				break;
			} else if (ptrB >= b.size()) {
				res.push_back(a[ptrA++]);
			} else if (ptrA >= a.size()) {
				res.push_back(b[ptrB++]);
			} else if (a[ptrA] <= b[ptrB]) {
				res.push_back(a[ptrA++]);
			} else if ( b[ptrB] <= a[ptrA]) {
				res.push_back(b[ptrB++]);
			}
		}
		return res;
	}

	std::array<int, 2> MinimalThreeArrayRange(std::vector<int> a, std::vector<int> b, std::vector<int> c );
	std::vector<int> IntersectSortedArray(std::vector<int> a, std::vector<int> b);
	std::vector<int> IntersectSortedArrayDedupe(std::vector<int> a, std::vector<int> b);

	std::vector<int> UnionSortedArrays(std::vector<int> a, std::vector<int> b);
	std::vector<int> UnionSortedArraysDedupe(std::vector<int> a, std::vector<int> b);
	std::vector<int> IntersectionUnsortedArrayInPlace(std::vector<int> a, std::vector<int> b);
	std::vector<int> UnionUnsortedArrays(std::vector<int> a, std::vector<int> b);
	std::vector<int> UnionUnsortedArraysInPlace(std::vector<int> &a, std::vector<int> b);
	std::vector<int> UnionUnsortedArraysDedupe(std::vector<int> a, std::vector<int> b);
	bool SubsetSortedArrays(std::vector<int> a, std::vector<int> b);
	bool SubsetUnSortedArrays(std::vector<int> a, std::vector<int> b);

	template<class T_v, class T_p>
	class PriQNode {
	public :
		T_v value;
		T_p pri;
		std::shared_ptr<PriQNode<T_v, T_p>> next;
	public:
		PriQNode(T_v val, T_p priority) : value{ val }, pri{ priority }, next{nullptr}{}
		~PriQNode() {}
		
	};

	template<class T_v, class T_p>   
	class PriQueue {
		std::shared_ptr<PriQNode<T_v, T_p>> head;
	public:		
		PriQueue& push(T_v value, T_p priority) {
			std::shared_ptr<PriQNode<T_v, T_p>> runner[2] = { head, head };
			std::shared_ptr<PriQNode<T_v, T_p>> runner_1_buffer;
			std::shared_ptr<PriQNode<T_v, T_p>> node = std::make_shared<PriQNode<T_v, T_p>>(value, priority);

			if (!head) {
				head = node;
			}
			else {
				while (runner[1]) {
					if (priority < runner[1]->pri) {
						if (head == runner[1]) {
							node->next = head;
							head = node;
							break;
						}
						else {
							runner_1_buffer = runner[1];
							runner[0]->next = node;
							node->next = runner_1_buffer;
							break;
						}
					}
					runner[0] = runner[1];
					runner[1] = runner[1]->next;
				}

				if (!runner[1])
					runner[0]->next = node;
			}
			return *this;
		}

		void printData() {
			auto runner = head;
			while (runner) {
				std::cout << "\t priority \t " << runner->pri << "\t value \t " << runner->value << '\n';
				runner = runner->next;
			}
		}
	};

	template <class T>
	
	class MinHeap {
		std::vector<T> array;
	
	protected:
		virtual void Heapify(std::vector<T> &array, int nodePosition, int maxLength) {
			int left = (nodePosition * 2) + 1;
			int right = left + 1;
			int pos = nodePosition;

			if (nodePosition >= 0) {
				if (left < maxLength) {
					if (array[left] > array[pos]) 
						pos = left; 
				}
				if (right < maxLength) {
					if (array[right] > array[pos])
						pos = right;
				}
				if (pos != nodePosition)
					std::swap(array[pos], array[nodePosition]);
				Heapify(array, nodePosition - 1, maxLength);
			}
		}

		virtual void demoteRoot(std::vector<T> &array) {
			int currPos = 0, left, right;

			while (true) {
				left = currPos + 1;
				right = currPos + 2;

				if (left < array.size()) {
					if (array[currPos] > array[left]) {
						std::swap(array[currPos], array[left]);
						currPos = left;
					}
				}

				if (right < array.size()) {
					if (array[currPos] > array[right]) {
						std::swap(array[currPos], array[right]);
						currPos = right;
					}
				}

				if (currPos != left && currPos != right) {
					break;
				}
			}

		}


	public:

		MinHeap() {}

		T size() const {
			return array.size();
		}

		bool contains(T val) const {
			return std::find(array.begin(), array.end(), val) != array.end();
		}

		bool isEmpty() const {
			return array.empty();
		}
		
		 virtual void insert(T value)  {
			int left, right, currPos = 0;
			array.insert(array.begin(), value);
			demoteRoot(array);
		}
		
		T& top()  {
			return array[0];
		}

		void print() const {
			for (auto ele : array)
				printf(" | %d  ", ele);
			printf("\n");

		}
		
		 T extract() {
			int left, right, currPos = 0;
			T result;
			
			std::swap( array[0], array[array.size() - 1]);
			result = (array[array.size() - 1]);
			array.pop_back();
			demoteRoot(array);
			return result;
		}

		void HeapSort(std::vector<T>& arr)  {
			for (int i = 0; i < arr.size(); i++) {
				Heapify(arr, std::floor(arr.size() / 2) - 1, arr.size() - i);
				std::swap(arr[0], arr[arr.size() - 1 - i]);
			}
			for (auto ele : arr)
				printf(" data: \t %d\n", ele);
			
		}

	};



	template <class T>
	class MaxHeap : public MinHeap<T> {
	public:
		MaxHeap() {}
	protected:
		virtual void Heapify(std::vector<T>& array, int nodePosition, int maxLength) override final {
			int left = (nodePosition * 2) + 1;
			int right = left + 1;
			int pos = nodePosition;

			if (nodePosition >= 0) {
				if (left < maxLength) {
					if (array[left] < array[pos])
						pos = left;
				}
				if (right < maxLength) {
					if (array[right] < array[pos])
						pos = right;
				}
				if (pos != nodePosition)
					std::swap(array[pos], array[nodePosition]);
				Heapify(array, nodePosition - 1, maxLength);
			}
		}

		virtual void demoteRoot(std::vector<T>& array) override final  {
			int currPos = 0, left, right;

			while (true) {
				left = currPos + 1;
				right = currPos + 2;

				if (left < array.size()) {
					if (array[currPos] < array[left]) {
						std::swap(array[currPos], array[left]);
						currPos = left;
					}
				}

				if (right < array.size()) {
					if (array[currPos] < array[right]) {
						std::swap(array[currPos], array[right]);
						currPos = right;
					}
				}

				if (currPos != left && currPos != right) {
					break;
				}
			}

		}
	};

	void Sequencer(std::vector < std::tuple<uint64_t, std::string>> array);

	template <class T>
	double MedianDataStream(std::vector<T> collection) {
		MinHeap<T> minHeap;
		MaxHeap<T> maxHeap;
		bool toggle = 0;
			
		for (auto streamData : collection) {
			
			if (minHeap.isEmpty())
				minHeap.insert(streamData);
			else if (maxHeap.isEmpty())
				maxHeap.insert(streamData);
			else if (streamData < maxHeap.top())
				maxHeap.insert(streamData);
			else
				minHeap.insert(streamData);

			if (std::abs(minHeap.size() - maxHeap.size()) > 1 ) {
				if (minHeap.size() > maxHeap.size()) {
					maxHeap.insert(minHeap.extract());
				} else {
					minHeap.insert(maxHeap.extract());

				}
			}
					
		}

		if (minHeap.size() == maxHeap.size())
			return (minHeap.top() + maxHeap.top()) / 2;
		else if (maxHeap.size() < minHeap.size())
			return minHeap.top();
		else
			return maxHeap.top();
	}


	template <class T>
	class QueueFromTwoStacks {
		std::vector<T> stackA;
		std::vector<T> stackB;

	public:
		QueueFromTwoStacks() 
		{}

		QueueFromTwoStacks insert(T value) {
			while (!stackB.empty()) {
				stackA.push_back(stackB.back());
				stackB.pop_back();
			}
			stackA.push_back(value);
			return *this;
		}

		T pop() {
			T data;
			
			try {
				while (!stackA.empty()) {
					stackB.push_back(stackA.back());
					stackA.pop_back();
				}

				if (!stackB.empty()) {
					data = stackB.back();
					stackB.pop_back();
					return data;
				} else {
					throw "error";
				}
			} catch (...) {
				printf("queue empty \n");
			
			}

		}

	};

	template <class T>
	class PriorityQueueFromTwoStacks {
		std::vector<std::tuple<T, int>> stackA;
		std::vector<std::tuple<T, int>> stackB;

	public:
		PriorityQueueFromTwoStacks()
		{}

		PriorityQueueFromTwoStacks &insert(T value, int priority) {

			while (!stackB.empty()) {
				if (priority >= std::get<1>(stackB.back())) {
					stackA.push_back(stackB.back());
					stackB.pop_back();
				} else {
					break;
				}
			}

			stackB.push_back({ value, priority });

			while (!stackA.empty()) {
				stackB.push_back(stackA.back());
				stackA.pop_back();
			}
			
			return *this;
		}

		T pop() {
			T data;
			int pri = 0;

			try {
				if (!stackB.empty()) {
					std::tie(data, pri) = stackB.back();
					stackB.pop_back();
					printf("priority: %d, \t data: %d \n", pri, data);
					return data;
				} else {
					throw "error";
				}
			}
			catch (...) {
				printf("queue empty \n");

			}

		}

	};

}

#endif