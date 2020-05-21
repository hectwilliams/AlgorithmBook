#include <vector>
#include <string>
#include <map>
#include <set>
#include <deque>
#include <array>
#include <string_view>
#include <tuple>
#include <memory>
//#include <thread>
#include <mutex>
#include <future>

#ifndef CHAPTER11_H
#define CHAPTER11_H


namespace chapter11 {

	extern struct nodeBT {
		int val;
		int count;
		nodeBT* parent;
		nodeBT* left;
		nodeBT* right;
	};

	extern struct llNode {
		int value;
		llNode* next;
	};

	llNode* LLNode(int value);
	nodeBT* BTNode(int value);
	int minF(int a = 0);
	int maxF(int a = 0);
	int countF(nodeBT* node);

	class LinkedList;

	class BST {

	private:
		nodeBT* root;
		int treeNodeCount;
		int uniqueCount;
		void Remove_Op(nodeBT* target_node, nodeBT* parent); // *
		std::array<nodeBT*, 2> get_inOrder_successor(nodeBT* node); //*

	public:

		// constructor 
		BST() : root{ nullptr }, treeNodeCount{ 0 }, uniqueCount{0}
		{};

		// Move constructor (yes!)
		BST (BST&& curr_bst_obj) noexcept  {
			root = curr_bst_obj.root;
			curr_bst_obj.root = nullptr;
		}

		// Move Assignment (!yes)
		BST& operator = (BST&& curr_bst_obj)  {
			if (&curr_bst_obj == this)
				return *this;
			this->RemoveAll(); // remove current tree 
			root = curr_bst_obj.root; // xfer root pointer to current tree pointer 
			curr_bst_obj.root = nullptr;
			return *this;
		}

		//  Copy constructor (disable)
		BST (const BST& bst) = delete;

		//Copy Assignment (disable) 
		BST& operator=(const BST& bst) = delete;

		// destructor
		~BST() {
			//nodeValues(9); // 9 -delete tree nodes via PostOrder Search
		};

		//methods
		 BST  &add(int value);
		 BST &add(nodeBT* node);

		bool contains(int val, nodeBT* node = nullptr);
		int min(nodeBT* node = nullptr, int (*callback)(int) = minF);
		int max(nodeBT* node = nullptr, int (*callback)(int) = maxF);
		int size(nodeBT* node = nullptr, int (*callback)(nodeBT*) = countF);
		bool isEmpty();
		int Height(nodeBT* node = nullptr, int depth = 0);
		int minHeight(nodeBT* node = nullptr, int depth = 0);
		bool isBalanced(nodeBT* node = nullptr, int depth = 0);
		BST &ArrayToBST(std::vector<int> arr);
		int CommonAncestor(const int& a, const int& b);
		std::vector<int>& bst2Arr(std::vector<int>&& arr = {});
		std::vector<int>& bst2ArrPre(std::vector<int>&& arr = {});
		std::vector<int>& bst2ArrPost(std::vector<int>&& arr = {});
		void bst2List(int mode = 0);
		void bst2ListPre(int mode = 0);
		void bst2ListPost(int mode = 0);
		template <class T>
		void nodeValues(int mode = 0, T* = nullptr, nodeBT* node = nullptr); // 0 PreOrder 1-inOrder 2-PostOrder
		void preOrderNoRecurion(nodeBT* node = nullptr);
		int ValBefore(int value, nodeBT* node = nullptr);
		int ValAfter(int value, nodeBT* node = nullptr);
		nodeBT* NodeBefore(nodeBT* findNode, nodeBT* node);
		nodeBT* NodeAfter(nodeBT* findNode, nodeBT* node);
		int closestValue(const int& value, nodeBT* node = nullptr);
		bool TreePathContainsSum(const int& sum, int currSum = 0, nodeBT* node = nullptr);
		void TreePathContainsSum(const int& sum, std::vector<std::vector<int>>& bucket, std::vector<int> arr = {}, nodeBT* node = nullptr);
		bool Remove(int val, nodeBT* node = nullptr, nodeBT* prev = nullptr);
		void RemoveAll(nodeBT* node = nullptr);
		bool IsValid(nodeBT* node = nullptr);
		void TraverseBSTReverseOrder(nodeBT* node = nullptr);
		void RootLeafNumber(nodeBT* node = nullptr, std::string&& currStr = "");
		std::vector<int> LeftSideBinary(std::vector<int> collection = {});
		nodeBT* getRoot();


		// PART II
		bool IsFull(chapter11::nodeBT* btNode);
		bool IsComplete(nodeBT* btNode);
		bool Repair(nodeBT* btNode);
		int SmallestDifference(BST& bst);
		BST PartitionAroundValue(int value, nodeBT* node = nullptr);
		BST PartitionEvenly();
		nodeBT * removeLeaf(nodeBT* leaf);
		void Reverse(BST &bst);

		std::tuple<int, bool> KthBiggest_Unique(int k);
		std::tuple<int, bool> KthBiggest(int k);
		std::vector<int> ValueForLayer(int n);
		std::vector<std::shared_ptr<std::vector<int>>> LayerArrays();

	};

	class LinkedList {
	private:
		llNode* head = nullptr;

	public:
		friend void BST::bst2List(int mode);
		friend void BST::bst2ListPre(int mode);
		friend void BST::bst2ListPost(int mode);

		LinkedList& insert(int value) {
			llNode* runner = head;

			if (!head) {
				head = LLNode(value);
			}
			else {
				while (runner->next) { runner = runner->next; }
				runner->next = LLNode(value);
			}
			return *this;
		}

		void print() {
			llNode* runner = head;
			while (runner) {
				std::cout << "NODE LIST VALUE " << runner->value << " " << '\n';
				runner = runner->next;
			}
		}

	};

}
#endif