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
#include "chapter12.h"

extern int errno;


namespace chapter12 {
	template <typename T> void swapper( T &a, T& b) {
		b = std::exchange(a, b);
	}

	std::vector<int>& BubbleSort(std::vector<int> &array) {
		for (int start = 0; start < array.size() - 1 ; start++) {
			for (int i = start + 1; i < array.size(); i++) {
				if ( array[i] < array[start]) {
					swapper(array[i], array[start]);
				}
			}
		}
		return array;
	}

	std::vector<int>& SelectionSort(std::vector<int>& array) {
		int minIndex;

		for (int i = 0; i < array.size(); i++) {
			minIndex = i;
			for (int p = minIndex; p < array.size(); p++) {
				if (array[p] < array[minIndex])
					minIndex = p;
			}

			if (minIndex != i) // indices data swap
				swapper(array[minIndex], array[i]);
		}
		return array;
	}

	template <typename T>
	T* nodealloc(T& value) {
		return Node<T> {value, nullptr};
	}

	static void  printLinkedList(Node<int> *node) {
		Node<int>* runner = node;
		while (runner) {
			printf("\tnode value: %d \n", runner->val);
			runner = runner->next;
		}
	}

	template <typename T>
	static void printArray(std::vector<T> array) {
		for (auto number : array)
			printf("\t [%12d]\n ", number);
		printf("\n\n");
	}

	static void LinkedListSwapNode(Node<int>* a_prev, Node<int> *a, Node<int>* b_prev, Node<int>* b) {
		auto buffer = b->next;
		
		if (a_prev)
			a_prev->next = b;

		if (b_prev == a) {
			b->next = a;
		}  else {
			b->next = a->next;
			b_prev->next = a;
		}

		a->next = buffer; 
	}

	Node<int>*  LinkedList::BubbleSort() {
		Node<int> *runner_prev = nullptr, * runner = head;
		Node<int>  *start_prev = nullptr, *start = head;
		
		while (start->next) {
			runner = start->next;
			runner_prev = start;
			while (runner) {
				if (runner->val < start->val) {
					if (start == head) {
						head = runner;
					}
					LinkedListSwapNode(start_prev, start, runner_prev, runner);
					swapper(start, runner);
				}
				runner_prev = runner;
				runner = runner->next;
			}

			start_prev = start;
			start = start->next;
		}
		printLinkedList(head);
		return head;
	}


	Node<int> *LinkedList::SelectionSort() {
		Node<int> *minNode, *minNode_prev = nullptr;
		Node<int>* runner_prev = nullptr, *runner = head;
		Node<int>* start_prev = nullptr, *start = head;
		std::vector<Node<int>*> test{ head, head }; 

		while (start->next) {
			runner = start->next;
			runner_prev = start;
			minNode = runner;

			while (runner) {
				if (runner->val < minNode->val) {
					head = (start == head) ? runner : head;
					minNode = runner;
					minNode_prev = runner_prev;
				}
				runner_prev = runner;
				runner = runner->next;
			}

			if (minNode != start->next) {
				LinkedListSwapNode(start_prev, start, minNode_prev, minNode);
				swapper(start, minNode);
			}

			start_prev = start;
			start = start->next;
		}
		printLinkedList(head);
		return head;
	}


	bool isSwappableCallback(NameObject a, NameObject b) {
		
		if ( b.lastName.compare(a.lastName) == 0 && b.firstName.compare(a.firstName) < 0)
			return true;
	
		if (b.lastName.compare(a.lastName) < 0)
			return true;
		
		return false;
	}

	std::vector<NameObject>& MultiKeySort(std::vector<NameObject>& array, bool (*isSwappable)(NameObject, NameObject)) {
		for (int i = 0; i < array.size() - 1; i++) {  //bubble it !
			for (int k = i + 1; k < array.size(); k++) {
				if (isSwappable(array[i], array[k])) {
					swapper(array[i], array[k]);
				}
			}
		}
		return array;
	}

	std::vector<int>& InsertionSort(std::vector<int>& array) {
		int Idx;
		for (int p = 1; p < array.size(); p++) {
			for (int i = 0; i < p; i++) {
				if ( array[i] > array[p] ) {  // insertion (sub-array rotate )
					for (int k = p; k > (p - (p-i)); k-- ) {
						swapper(array[k-1], array[k]);
					}
					break;
				}
			}
		}
		return array;
	}
	
	static void insertB_FRONT_A(Node<int> *b, Node<int> *b_prev, Node<int> *a, Node<int> *a_prev) {
		Node<int> *buffer = b->next;
		b->next = a;
		if (a_prev)
			a_prev->next = b;
		if (b_prev == a)
			a->next = buffer;
		else
			b_prev->next = buffer;
	}

	Node<int> *LinkedList::InsertionSort() {
		Node<int> *runner = head->next, *runner_prev = head;
		Node<int> *curr = head, *curr_prev = head;
		while (runner) {
			curr = head; 
			curr_prev = nullptr;
			while (curr != runner) {
				if (curr->val > runner->val) {
					head = (curr == head) ? runner : head;
					insertB_FRONT_A(runner, runner_prev, curr, curr_prev);
					runner = runner_prev;
					break;
				}
				curr_prev = curr;
				curr = curr->next;
			}
			runner_prev = runner; 
			runner = runner->next;
		}
		printLinkedList(head);
		return head;
	}

	 std::vector<int> CombineArrs( const std::vector<int> &a, const std::vector<int> &b) {
		int value, aIndex = 0, bIndex = 0;
		std::vector<int> result;

		while (aIndex < a.size() || bIndex < b.size() ) {

			if (aIndex >= a.size()) {
				value = b[bIndex];
				bIndex++;
			} else if (bIndex >= b.size()) {
				value = a[aIndex];
				aIndex++;
			} else if (b[bIndex] < a[aIndex]) {
				value = b[bIndex];
				bIndex++;
			} else {
				value = a[aIndex];
				aIndex++;
			}

			result.push_back(value);

		}

		return result;
	}

	Node<int>* MaxNode(Node<int>* a, Node<int>* b) {
		if (!a)
			return b;
		else if (!b)
			return a;
		else if (a->val > b->val)
			return b;
		else
			return a;
	}

	Node<int>* CombineList(Node<int>* a, Node<int>* b) {  // a and b are sored linked List
		Node<int>* result = nullptr, *buffer = nullptr,* head = nullptr;

		while (a || b) {

			buffer = MaxNode(a, b);
			
			if (a == buffer)
				a = a->next;

			if (b == buffer)
				b = b->next;

			if (!result) {
				head = buffer;
				head->next = nullptr;
				result = head;
			} else {
				result->next = buffer;
				result = result->next;
			}
			result->next = nullptr;

		}

		return head;
	}

	Node<int>* MergeSort(Node<int>* list) {
		Node<int> *result = nullptr, *runner = list, *buffer = nullptr;
		while (runner) {
			buffer = runner;
			runner = runner->next;
			buffer->next = nullptr; 
			result = CombineList(result, buffer);
		}
		printLinkedList(result);
		return result;
	}

	int Partition(std::vector<int> &array, const int &mode, const int & start, const int &end) {
		int pIndex = (mode == 0) ? start : (mode == 1) ? (std::floor( end-start / 2)) : end;  // select mode [0-zero, 1-mid, 2 last] pivot
		int j = start - 1;
		int currPIndex;
		int pivot = array[pIndex];

		try {
			for (int r = start; r  <=  ((end == -1) ? (array.size() - 1): end) ; r++) {					
				if (array[r] < pivot) {
					j++;
					pIndex = (j == pIndex) ? r : pIndex;
					swapper(array[r], array[j]);
				}
			}
			currPIndex = j + 1;
			if (array[currPIndex] != array[pIndex]) {
				swapper(array[currPIndex], array[pIndex]);
				pIndex = currPIndex;
			}

		} catch (std::exception &exception) {
			printf("error msg:  \t%s", exception.what());
		}

		
		return pIndex;
	}

	Node<int>* Partition(Node<int>* node) {
		Node<int> *runner_prev = nullptr, *runner = node;
		Node<int> *ptr = node, *ptr_prev = nullptr, *head = node;
		Node<int> *piv = node, *piv_prev = node;
	
		while (runner) {

			if (runner->val < piv->val) {

				if (ptr == head) 
					head = runner;

				if (piv == ptr) {
					piv = ptr;
					piv_prev = runner_prev;
				}
				LinkedListSwapNode(ptr_prev, ptr, runner_prev, runner);

				ptr = runner->next;
				ptr_prev = runner;
							
			}

			runner_prev = runner;
			runner = runner->next;

		}

		if (ptr != piv) {  // partition node must be in middle
			LinkedListSwapNode(ptr_prev, ptr, piv_prev, piv);
		}
		
		printLinkedList(head);
		return head;
	}

	void QuickSort(std::vector<int> &array, int start,  int end) {
		int p = 0;

		if (start == -1 && end == -1) {
			start = 0;
			end = array.size() - 1;
		}

		if ( (end - start) > 0) {
			p = Partition(array, 0, start, end);
			QuickSort(array, 0, p - 1 );
			QuickSort(array, p + 1, end);
		}

	}

	std::vector<int> MergeSort(std::vector<int> collection) {
		int mid = std::floor(collection.size() / 2);
		std::vector<int> buffer;
		std::vector<int> left, right; 

		if (collection.size() == 2) {
			if (collection[0] > collection[1])
				swapper(collection[0], collection[1]);
			return collection;
		}

		left = std::vector<int>(collection.begin(), collection.begin() + mid );
		left = MergeSort(left);

		right = std::vector<int>(collection.begin() + mid, collection.begin() + collection.size());
		right = MergeSort(right);

		collection = CombineArrs(left, right);
		return collection;
	}

	int Partition3(std::vector<int>& array, int pivotIndex, int start , int end) {
		std::map<int, std::vector<int>> pMap;
		std::map<int, std::vector<int>>::iterator it ;
		end = (end == -1) ? array.size() - 1 : end;
		int j = start - 1, pivot, currIndex = pivotIndex;
		
		try {
			
			if ( !(pivotIndex >= 0 && pivotIndex < array.size() - 1) )
				throw;
			pivot = array[pivotIndex];

			for (int i = start; i <= end; i++) {
				
				if (pivot == array[i]) {
					it = pMap.find(array[i]);
					if (it == pMap.end()) {
						pMap.insert(std::make_pair(array[i], std::vector<int>{i} ));
					} else if (std::find(it->second.begin(), it->second.end(), i) == it->second.end()) { // index not found in prop value list
						pMap.find(array[i])->second.push_back(i);
					}
				}
				
				if (array[i] < pivot) {
					++j;
					pivotIndex = (j == pivotIndex) ? i : pivotIndex;
					
					it = pMap.find(array[j]);  // found pivot twin/clone!
					
					if (it != pMap.end()) {  
						printf("moved data %d  index %d\n", array[i], i);

						if (std::find(it->second.begin(), it->second.end(), j) != it->second.end()) {  // swap value is indeed a twin 
							for (int n = 0; n < it->second.size();  n++) {
								if (it->second[n] == j) {  // update  index  of twin index;
									it->second[n] = i;
								}
								break;
							}
						}
					}

					swapper(array[i], array[j]);
				}
			}
			printArray(array);  // :) 
			if (j + 1 != pivotIndex) {
				swapper(array[j + 1], array[pivotIndex]); // pivot value should split numbers
				pivotIndex = j + 1;
			}
			
			it = pMap.find(array[currIndex]);
			if (it != pMap.end()  ) {
				if (it->second.size() > 1) {


					while (it->second.size() ) {
						if (it->second.front() != pivotIndex) {  
							swapper(array[++currIndex], array[it->second.front()]);  // swap twin/clone immediately after pivot
						}
						it->second.erase(it->second.begin());
					}
				}
			}

		} catch (std::exception & exception) {
			printf("error msg: %s", exception.what());
		}
		return pivotIndex;
	}


	void QuickSort3(std::vector<int>& array,  int start,  int end) {
		int p = 0;

		if (start == -1 && end == -1) {
			start = 0;
			end = array.size() - 1;
		}

		if ( (end -  start) > 0 ) {
			p = Partition3(array, start, start, end);
			QuickSort3(array, 0, p - 1);
			QuickSort3(array, p + 1, end);
		}

		printArray(array);
	}


	

	template <class T>
	bool heapifyCaller (std::vector<T>& arr, int l, int r) {
		return false;
	}
	template <>
	bool heapifyCaller(std::vector<int>& arr, int leaf_pos, int curr_pos) {
		return arr[leaf_pos] > arr[curr_pos];
	}
	template <>
	bool heapifyCaller(std::vector<KarateStudent>& arr, int leaf_pos, int curr_pos) {
		std::vector<KarateStudent>::iterator it;

		if (BeltMap.find(arr[leaf_pos].Belt) == BeltMap.end() || BeltMap.find(arr[curr_pos].Belt) == BeltMap.end()) {
			return false;
		}

		if (BeltMap.find(arr[leaf_pos].Belt)->second > BeltMap.find(arr[curr_pos].Belt)->second) {
			return true;
		}

		if (BeltMap.find(arr[leaf_pos].Belt)->second == BeltMap.find(arr[curr_pos].Belt)->second && BeltMap.find(arr[leaf_pos].Belt)->first.compare(BeltMap.find(arr[curr_pos].Belt)->first) > 0  ) {

			return true;
		}
	}

	template <class T>								
	static void Heapify(std::vector<T>& array, const int pos, const int n , bool (*cb)(std::vector<T>&, int, int) = heapifyCaller) {
		int currPos = pos, left, right;
		left = (2 * pos) + 1;
		right = left + 1;

		if (pos < 0)
			return;

		if (left < n) {
			if (heapifyCaller(array, left, currPos) /*(array[left] > array[currPos]) */ )  {
				currPos = left;
			}
		}

		if (right < n) {
			if (heapifyCaller(array, right, currPos)  /*array[right] > array[currPos]*/ ) {
				currPos = right;
			}
		}

		if (currPos != pos)
			swapper( array[pos], array[currPos] );

		Heapify(array, pos - 1, n);
	
	}

	template <class T>
	void PancakeSort(std::vector<T>& array ) {
		int nodePos = std::floor(array.size() / 2) - 1;
		int k = 0;
		for (int i = array.size(); --i ;) {
			Heapify(array, nodePos, array.size() - k++ );
			swapper(array[i], array[0]);
		}
		printArray(array);
	}

	static int RadixSort_helper_find_bucket_index( unsigned long int data, const int &pos) {
		unsigned long int val = data / ( (pos == 0) ? 1 : std::pow( 10, pos) );
		val = val % 10;
		return val;
	}

	void RadixSort( std::vector <unsigned long int> &array) {
		std::array< std::vector<unsigned long int> , 10> collection;
		int p;
		int index;

		for (int i = 0; i < 10; i++) {
			for (auto ele : array) {
				p = RadixSort_helper_find_bucket_index(ele, i);
				collection[p].push_back(ele);
			}

			index = 0;
			for (auto& arr: collection) {
				if (!arr.empty()) {
					for (auto ele : arr) {
						array[index++] = ele;
					}
				}
				arr.clear();
			}
		}
		printArray(array);

	}

	

	void BeltSort(std::vector<KarateStudent>& array) {
		PancakeSort<KarateStudent>(array);

		for (auto obj : array)
			printf("name %s  \t belt %s\n" , obj.Name.c_str(), obj.Belt.c_str());
	}

	void WiggleSort(std::vector<int> &array) {
		int mid = (int)std::floor(array.size() / 2);
		QuickSort(array);
		int median = array[mid];
		int low = 1, high = array.size() - 1;
		
		while (low < array.size()) {
			if (array[mid] > array[low])
				swapper(array[mid++], array[low]);
			low += 2;
		}

		printArray(array);      
	}

}