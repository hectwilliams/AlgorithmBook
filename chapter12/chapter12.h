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

#ifndef CHAPTER12_H
#define CHAPTER12_H


namespace chapter12 {
	template <typename T> 
	 struct Node {
		T val;
		Node* next;
	};

	template <typename T>
	T* nodealloc(T& value);

	class LinkedList {
	private:
		Node<int>* head;
	public:
		LinkedList(Node<int> *node) : head{node} {}
		Node<int>* BubbleSort();
		Node<int>* SelectionSort();
		Node<int>* InsertionSort();
	};

	std::vector<int> &BubbleSort ( std::vector<int> &array);
	std::vector<int> &SelectionSort (std::vector<int>& array);

	struct NameObject {
		std::string firstName;
		std::string lastName;
	};

	struct KarateStudent {
		std::string Name;
		std::string Belt;
	};

	bool isSwappableCallback(NameObject a, NameObject b);
	std::vector<NameObject> & MultiKeySort(std::vector<NameObject>& array, bool (*isSwappable)(NameObject, NameObject) = isSwappableCallback);
	std::vector<int>& InsertionSort(std::vector<int>& array);
	std::vector<int> CombineArrs(const std::vector<int> &a, const std::vector<int> &b);
	Node<int>* CombineList(Node<int>* a, Node<int>* b);
	Node<int>* MergeSort(Node<int>* list);
	int Partition(std::vector<int> &array, const int& mode = 0, const int &start = 0, const int &end = -1 );
	Node<int>* Partition(Node<int>* node);
	void QuickSort(std::vector<int> &array,  int start = -1,  int end = -1);
	std::vector<int> MergeSort(std::vector<int> collection);
	int Partition3(std::vector<int>& array, int  pivotIndex = 0, int start = 0, int end = -1);
	void QuickSort3(std::vector<int>& array,  int start = -1,  int end = -1);
	
	template <class T>
	void PancakeSort(std::vector<T>& array);

	void RadixSort(std::vector<unsigned long int> &array);
	void BeltSort(std::vector<KarateStudent>& array);

	const std::map< std::string, int> BeltMap = {
	{"none", 0},
	{ "yellow", 1 },
	{ "red", 2 },
	{ "black", 3 },
	{ "double-black", 4 },
	{ "triple-black", 5 },
	{ "triple-black-blue", 6 }
	};

	void WiggleSort(std::vector<int> &array);
}

#endif