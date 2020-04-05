#include <vector>
#include <string>
#include <map>
#include <array>
#include <string_view>
#include <tuple>
#include <memory>
#ifndef AALGO_H
#define ALGO_H

namespace chapter9
{
	int rgcf(int num1, int num2);
	void floodFill(int canvas2D[5][5], int startxy[2], const int& newColor, int target = -1);
	void floodFill_helper_printCanvas(const int canvas[5][5]);
	int rFib(int num, int a = 1, int b = 1, int counter = 0);
	bool rBinarySearch(std::vector<int> array, int target);
	int tarai(const int& x, const int& y, const int& z);
	void inOrderSubsets(std::string str);
	int GotAnyGrapes(std::vector<int> grapeBags, int& memo, int&& max = 0);
	int Collatz_apalooza(int num, int occurence = 1, int count = 0);
	void TelephoneWords(std::string telephoneNumber, std::string&& buffer = "", std::map <int, std::string> mapper = { {0, "O"},  {1, "I"}, {2, "ABC"}, {3, "DEF"}, {4, "GHI"}, {5, "JKL"}, {6,"MNO"}, {7,"PQRS"}, {8, "TUV"}, {9, "WXYZ"} });
	std::string RisingSquares(int num, int count = 1);
	void BinaryStringExpansion(std::string str, std::string buffer = "");
	void StringAnagrams(std::string&& str, std::string buffer = "");
	void climbingStairs(int footsteps, std::vector<std::vector<int>>& data, std::vector<int> buffer = {});
	void SumOfSquares(int num, std::vector<std::vector<int>>& combinations, std::vector<int> buffer = {}, double&& count = 1.0);
	void AllValidNPairsOfParens(int num, std::vector<std::string>& array, std::string buffer = "");
	void TowersofHanoi(int numOfDisks = -1, std::vector<std::vector<int>> poles = { {0,1,2}, {}, {} }, int value = 0, int&& depth = 0);
	void IPAddresses(std::string digits, std::vector<int> buffer = {});
	void UnevenDigits(const int& num, std::string data = "", int index = 0);
	void GenerateAllPossibleCoinChange(int cents, std::vector< std::map<std::string, int>>& results, std::map<std::string, int> mapCents = { {"dimes", 0}, {"nickels", 0}, {"pennies", 0}, {"quarters", 0} });


	using array2_t = std::array<int, 2>;


	class Chess {

	private:

		int** board;
		int rowMax = 8;
		int colMax = 8;
		std::vector<array2_t>* freeblocks;

		void changeXY(int r, int c) {
			colMax = c;
			rowMax = r;
		}

		void initBoard() {
			if (board)
				boardRelease();

			board = new int* [rowMax];	// (row) of 8 int pointers 
			for (int i = 0; i < colMax; i++)
				board[i] = new int[colMax] {};	// (columns ) int pointer
		}

		void clearBoard() {
			freeblocks->clear();

			if (!board)
				return;

			for (int r{ 0 }; r < rowMax; r++) {
				for (int c{ 0 }; c < colMax; c++) {
					board[r][c] = 0;
					freeblocks->push_back({ r,c });
				}
			}
		}

		void boardRelease() {
			if (!board)
				return;
			for (int i = rowMax; i--; ) {
				delete[] board[i];
			}
			delete[] board;
		}

		void insert(const array2_t& pos, const int& value) {
			this->board[pos[0]][pos[1]] = value;
		}

		int& read(const array2_t& pos) {
			return this->board[pos[0]][pos[1]];
		}

		void boardFill(std::vector<array2_t> list) {
			clearBoard();
			for (auto pos : list)
				insert(pos, 1);
		}


		std::vector<array2_t> possiblePaths(std::vector<array2_t> list, int NQueens = 8, std::vector<array2_t> queens = {}, std::vector<array2_t> skip = {});

	public:
		Chess() : freeblocks{ new std::vector<array2_t>{} } {
			clearBoard();
		}

		~Chess() {
			boardRelease();
			delete freeblocks;
		}

		friend std::ostream& operator << (std::ostream& out, const Chess& chess) {
			out << '\n' << '[' << "\t\n\t";
			for (int r{ 0 }; r < chess.rowMax; r++) {
				for (int c{ 0 }; c < chess.colMax; c++) {
					std::cout << '|' << chess.board[r][c];
				}
				std::cout << "|\n\t";
			}
			out << "\n]";
			return out;
		}

		std::vector<array2_t> getFreeBlocks() {
			std::vector<array2_t> result;
			for (int r = 0; r < rowMax; r++) {
				for (int c = 0; c < colMax; c++) {
					result.push_back({ r, c });
				}
			}
			return result;
		};

		bool isChessMoveSafe(array2_t moveTo, array2_t queen);
		bool isChessMoveSafe(array2_t moveTo, std::vector<array2_t> queens);

		std::vector<array2_t> allSafeChessSquares(array2_t queen, std::vector<array2_t> list);
		std::vector<array2_t>  allSafeChessSquares(std::vector<array2_t> queens);
		std::vector<array2_t>  allSafeChessSquares(const int x, const int y);

		void Queens(std::vector<array2_t> list = {}, std::vector<array2_t> queens = {}, int n = 8);
		void NQueens(const int n, const int rLen, const int cLen);  // n = 13 rLen  = 13 cLen =13 largest N queens size to produce data

	};
}


namespace chapter10 {

	std::vector<std::string> StringToWordArray(std::string s, bool handlePunctuation = false);
	static void StringToWordArray_helper_handlePunctuation(std::string& s);
	std::string LongestWord(const std::string& s);
	std::string ReverseWordOrder(std::string s);
	std::string UniqueWords(const std::string& message, bool ignorePunctuation = false);
	std::string RotateString(std::string str, const int& count);
	bool isRotation(std::string s1, std::string s2);
	std::string Censor(std::string s, std::vector<std::string> list);
	std::string BadCharacters(std::string s, const char c[]);
	bool GeneticMarker(std::vector<std::string> collection, std::string marker);
	std::string Dedupe(const std::string s);
	int IndexFirstUniqueLetter(const std::string s);
	std::string NumToString(int number);
	std::string NumToString(double fraction);

	const std::map<int, std::string> illions = {
		{3, "thousand"},
		{6, "million"},
		{9, "billion"},
		{12, "trillion"},
		{15, "quadrillion"},
		{18, "quintillion"}
	};

	const  std::map<int, std::array<std::string, 3>> NumToTextMap = {
		{0, {"zero",	"ten"} },
		{1, {"one",		"eleven"} },
		{2, {"two",		"twelve",		"twenty"} },
		{3, {"three",	"thirteen",		"thirty"} },
		{4, {"four",	"fourteen",		"fourty"} },
		{5, {"five",	"fifteen",		"fifty"} },
		{6, {"six",		"sixteen",		"sixty"} },
		{7, {"seven",	"seventeen",	"seventy"} },
		{8, {"eight",	"eighteen",		"eighty"} },
		{9, {"nine" ,	"nineteen",		"ninety"} }
	};

	std::string NumToText(int number, int index3 = -1, std::string s = "", int depth = 0, std::vector<std::string>  result = {});
	bool isPermutation(std::string s1, std::string s2, const char index = 0);
	bool IsPangram(std::string s, std::map<char, int> histo = {}, int count = 0);
	void AllPermutations(std::string s, std::vector<std::string>& collection, std::string buffer = "", int max = 0);
	bool PerfectPangram(std::string s, int count = 0, std::map<char, int> map = {});
	int bestSingleBuySell(const std::vector<int> arr, int mode = 0, std::vector<std::array<int, 2>> array = {}, int low = -1, int high = -1);
	bool StringsLooselyInterleaved(std::string s0, std::string s1, const std::string s2);
	void allStringsLooselyInterleaved(std::string str1, std::string str2, int index = 0, std::vector<std::string> list = {});
	int RemoveOneMakePalindrome(std::string s, int index = 0);
	char MakeStringPalindrome(std::string s, int index = 0);
	std::string StringEncode(std::string s, int index = 0, int count = 0, char curr = '\0', std::string result = "");
	std::string StringDecode(std::string s, std::string result = "", int index = 0);

}

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

	public:

		// constructor 
		BST() : root{ nullptr }, treeNodeCount{ 0 }, uniqueCount{0}
		{};

		// Move constructor (yes!)
		BST( BST&& curr_bst_obj)  {
			root = curr_bst_obj.root;
			curr_bst_obj.root = nullptr;
		}

		// Move Assignment (!yes)
		BST& operator = (BST&& curr_bst_obj) {
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
		bool Remove(int val, nodeBT* node = nullptr);
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



namespace chapter14 {

	template <class T>
	class HashMap {	
		int capacity;

	protected:
		int numKeys;
		 std::vector<std::vector<std::tuple< std::string, T>>> table;

		 virtual const  int& HashCode(std::string key) {
			uint32_t&& result = 0;
			for (auto c : key) {
				result += static_cast<int>(c);
			}
			return result % capacity;
		 }

	public:

		HashMap(int cap) :capacity{ cap }, numKeys{ 0 }, table{} {
			table.resize(cap, {});
		}

		void insertHashTable(std::string key, T val, std::vector<std::tuple< std::string, int>>  & bucket) {
			numKeys++;
			bucket.push_back(std::tuple<std::string, int> (key, val) );
		}

		 HashMap& Add(std::string key, T val) {
			int code = HashCode(key);
			auto& arr = table[code];
			int i = 0;
			
			for (auto tuple : arr) {
				if (std::get<0>(tuple) == key && std::get<1>(tuple) == val) {
					arr[i] = std::make_tuple(key, val);		// " key/value found in table, overwriting ... ";
					return *this;
				}
			}
			insertHashTable(key, val, arr);
			return *this;
		}

		std::tuple<T, bool> find(std::string key) {
			int code = HashCode(key);
			for (auto tuple : table[code]) {
				if (std::get<0>(tuple) == key) {
					return std::make_tuple(std::get<1>(tuple), true);
				}
			}
			return std::make_tuple(NULL, false);
		}

		 std::tuple<T, bool> remove(std::string key) {
			int code = HashCode(key);
			std::vector<std::tuple< std::string, T> >& arr = table[code];
			std::tuple<int, bool> result;

			for (int i = 0; i < arr.size(); i++) {
				if (std::get<0>(arr[i]) == key) {
					result = std::make_tuple(std::get<1>(std::move(arr[i])), true);
					arr.erase(arr.begin() + i);
					numKeys--;
					return result;
				}
			}
			return std::make_tuple(NULL, false);
		}

		std::map<std::string, T> SelectKeys(std::vector<std::string> keyArray) {
			std::map<std::string, T> result;
			T val_buffer;
			bool boolean;
			for (auto key : keyArray) {
				std::tie(val_buffer, boolean) = find(key);
				if (boolean)
					result.insert(std::make_pair(key, val_buffer));
			}

			return result;
		}

		
		void grow(uint32_t newCap = 0) {
			table.resize(newCap == 0 ? (capacity * .5) + capacity : newCap);
			for (auto& array : table) {
				int max = array.size();
				T value;
				std::string key;

				while (max > 0) {
					value = std::get<1>(array.front());
					key = std::get<0>(array.front());
					array.erase(array.begin());
					numKeys--;

					Add(std::move(key), std::move(value));
					max--;
				}
			}
		}

		bool isEmpty() {
			return numKeys == 0;
		}

		void printHashMap() {
			for (int i = 0; i < table.size(); i++) {
				printf(" bucket: %d \n", i);
				for (auto& tuple : table[i]) {
					printf("\t\t %s \t | %d \n\n", std::get<0>(tuple).c_str(), std::get<1>(tuple));
				}
			}
		}

		const double& LoadFactor() {
			return numKeys / static_cast<double>(table.size());
		}

		void SetSize(int cap) {
			grow(cap);
		}


		void addMap(HashMap hashMap_in) {
			std::tuple<std::string, T> tuple_buffer, curr_buffer;
			T internal_val;
			bool internal_bool;

			for (auto &bucket_in : hashMap_in.table) {
				for (auto &tuple_in : bucket_in) {
					std::tie(internal_val, internal_bool) = this->find(std::get<0>(tuple_in));  
					if (internal_bool)  // duplicate key   remove current key pair
						this->remove(std::get<0>(tuple_in));
					this->Add(std::get<0>(tuple_in), std::get<1>(tuple_in));
				}
			}
		}
		

	};

	template <class T> 
	class HashMultiMap : public HashMap<T> {
	
	public:

		HashMultiMap(int cap) : HashMap<T>(cap) {}

		  HashMultiMap& Add(std::string key, T val)   {
			int code = this->HashCode(key);
			auto &arr = this->table[code];
			for (auto curr_tuple : arr) {
				if (std::get<0>(curr_tuple) == key && std::get<1>(curr_tuple) == val)
					return *this;
			}
			this->insertHashTable(key, val, arr);
			return *this;
		}

		std::tuple< std::vector<T>, bool> find(std::string key) {
			int code = this->HashCode(key);
			auto& arr = this->table[code];
			std::vector<T> valueList;

			for (auto curr_tuple : arr) {
				if (std::get<0>(curr_tuple) == key) {
					valueList.push_back(std::get<1>(curr_tuple));
				}
			}
			 
			if (valueList.empty())
				return std::make_tuple(valueList, false);
			else
				return std::make_tuple(valueList, true);
		}

		std::tuple<std::vector<T>, bool> remove(std::string key) {
			int code = this->HashCode(key);
			auto& arr = this->table[code];
			std::vector<T> listValues;
			uint32_t start = -1;
			 
			for (int i = 0; i < arr.size(); i++) {
				 
				if (std::get<0>(arr[i]) == key) {
					if (start == -1)
						start = i;
					listValues.push_back(std::get<1>(arr[i]));
				}
			}
			 
			if (listValues.size()) {
				arr.erase(arr.begin() + start, arr.begin() + start + listValues.size());
				return std::make_tuple(listValues, true);
			} else {
				return std::make_tuple(listValues, false);
			}
		  
		}
	};

	template <class T>
	class HashSet : public HashMap<T> {
	public:
		HashSet(int cap) : HashMap<T>(cap)  {}

		HashSet& Add(std::string key)   {
			int code = this->HashCode(key);
			auto& arr = this->table[code];
			 
			for (int i = 0; i < arr.size(); i++) {
				if (key == std::get<0>(arr[i]))
					return *this;
			}

			this->insertHashTable(key, 1, arr);
			return *this;
		}
		   
		bool find(std::string key) {
			for (auto& tuple : this->table[this->HashCode(key)]) {
				if (std::get<0>(tuple) == key) {
					return true;
				}
			}
			return false;
		}

		 bool  remove(std::string key) {
			 int code = this->HashCode(key);
			 auto& arr = this->table[code];
			 
			 if (!arr.empty()) {
				 for (int i = 0; i < arr.size() ; i++) {
					 if (key == std::get<0>(arr[i])) {
						 arr.erase(arr.begin() + i);
						 return true;
					 }
				 }
			 } 
			 
			 return false;
		 }

	};


	template <class T>
	class HashMultiSet : public HashSet<T> {

	public:
		HashMultiSet (int cap) : HashSet<T>(cap) {}

		 HashMultiSet& Add(std::string key) {
			int code = this->HashCode(key);
			auto& arr = this->table[code];
			for (auto& tuple : arr) {
				if (std::get<0>(tuple) == key) {
					++std::get<1>(tuple);
					return *this;
				}
			}
			this->insertHashTable(key, 1, arr);
			return *this;
		}


		 int find(std::string key) {
			 for (auto& tuple : this->table[this->HashCode(key)]) {
				 if (std::get<0>(tuple) == key) {
					 return std::get<1>(tuple);
				 }
			 }
			 return 0;
		 }

		 bool remove(std::string key) {
			 for (auto& tuple : this->table[this->HashCode(key)]) {
				if (std::get<0>(tuple) == key) {
					--std::get<1>(tuple);
					return true;
				}
			 }
			 return false; 
		 }

	};
}

namespace chapter15 {
	/* 
		refer to chapter 11 -> SECTION: PART II 
	*/
}

namespace chapter16 {

	struct nodeTrie {
		int count;
		std::string val;
		std::vector<nodeTrie *> children;
	};

	nodeTrie* TrieNode(std::string s);

	class Trie {
		
	protected:
		nodeTrie* root;
		int node_count;

	public:	
		Trie() : root{ TrieNode("") }, node_count{1}
		{}
		
		bool Insert(const std::string &string_in, const int&index = 0, bool isNewEntry = false, nodeTrie* node = nullptr);
		bool Contains(const std::string& string_in, const int index = 0, nodeTrie* node = nullptr);
		bool Remove(const std::string& string_in, const int index = 0, nodeTrie* node = nullptr);
		std::string First( nodeTrie *node= nullptr);
		std::string Last(nodeTrie* node = nullptr);
		int Size();
		std::string Next(const std::string& str, int index = 0, nodeTrie* node = nullptr);
		void AutoComplete( nodeTrie *node = nullptr);
	};

	class TrieMultiSet : public Trie {
	public:
		TrieMultiSet() : Trie{} 
		{}

		bool Insert(const std::string& string_in, const int& index = 0, nodeTrie* node = nullptr);
		int Remove(const std::string& string_in, const int& index = 0, nodeTrie* node = nullptr);
		int Contains(const std::string& string_in, const int& index = 0, nodeTrie* node = nullptr);
		void AutoComplete();
	};

	struct TrieMapNode {
		std::string key;
		std::string value;
		int count;
		std::vector<TrieMapNode*> children;
	};

	class TrieMap {
		TrieMapNode* root;
		 int count;

	public:
		TrieMap() : root{ new TrieMapNode{"", "", 1} }, count{1}
		{}

		std::string Insert(const std::string &key, const std::string &value = "", const int& index = 0, std::string buffer = "", const int& matching_char_count = 0, TrieMapNode* node = nullptr);
		std::string Contains(const std::string& key, int index = 0, TrieMapNode* node = nullptr);
		bool Remove(const std::string& key, const int& index = 0, TrieMapNode* node = nullptr);
		int Size();
		std::string Next(const std::string& key,  int index = 0 , std::string buffer = "", TrieMapNode *node = nullptr);
		std::string First(std::string buffer = "",  TrieMapNode* node = nullptr);
		std::string Last(std::string buffer = "", TrieMapNode* node = nullptr);
	};
}

namespace chapter17 {
	
	template <typename T>
	struct EL_Node {
		std::string src;
		std::string dest;
		T value;
	};

	template <class T, class E_v>
	class ELGraph {

	private:
		int n = 0;
		int size = 0; 
		std::map<std::string, T> vertex_map;
		std::vector<EL_Node<E_v>*> el_node_list;

		EL_Node<E_v>* el_node(std::string src, std::string dest, E_v val);
	public:
		ELGraph()
		{}
		~ELGraph()
		{
			while (el_node_list.size()) {
				delete el_node_list.front();
				el_node_list.erase(el_node_list.begin());
			}
		}
		std::string AddVertex(T value);
		bool RemoveVertex(std::string id);
		std::tuple<T, bool> GetVertexValue(std::string id);
		bool SetVertexValue(std::string id, int value);
		bool AddEdge(std::string id1, std::string id2, E_v value);
		void RemoveEdges(std::string id);
		bool RemoveEdge(std::string id1, std::string id2);
		std::tuple<E_v, bool> GetEdgeValue(std::string id1, std::string id2);
		bool SetEdgeValue(std::string id1, std::string id2, E_v value);
		bool Adjacent(std::string id1, std::string id2);
		std::vector<std::string> Neighbors(std::string id);
	};

	template <class T, class E>
	struct AM_Node_Vertex {
		std::string id;
		T value;
		std::map<std::string, E> neighbors;
	};

	template <class T, class E>
	class AMGraph {

	private:
		AM_Node_Vertex<T, E>* am_node(std::string id, T value) {
			return new AM_Node_Vertex<T, E>{ id, value };
		}

	protected:
		int n = 0;  
		int size = 0; 
		bool matrix_en; 
		std::map<std::string, AM_Node_Vertex<T, E>*> map;

	public:
		AMGraph(): matrix_en{true}
		{}
		
		~AMGraph() 
		{
			while (map.size()) {
				delete map.begin()->second;
				map.erase(map.begin());
			}
		}

		void Grid();
		std::string AddVertex(T value);
		bool RemoveVertex(std::string id);
		std::tuple<T, bool> GetVertexValue(std::string id);
		bool SetVertexValue(std::string id, T value);
		bool AddEdge(std::string id1, std::string id2, E value);
		void RemoveEdges(std::string id);
		bool RemoveEdge(std::string id1, std::string id2);
		std::tuple<E, bool> GetEdgeValue(std::string id1, std::string id2);
		bool SetEdgeValue(std::string id1, std::string id2, E value);
		bool Adjacent(std::string id1, std::string id2);
		std::vector<std::string> Neighbors(std::string id);

	};

	template <class T, class E>
	class ALGraph: public AMGraph<T, E> {

	public:
		ALGraph() {
			this->matrix_en = false;
		}

		bool AddEdge(std::string id1, std::string id2, E value);
		void RemoveEdges(std::string id);
		bool RemoveEdge(std::string id1, std::string id2);
		std::tuple<E, bool> GetEdgeValue(std::string id1, std::string id2);
		bool SetEdgeValue(std::string id1, std::string id2, E value);
		bool Adjacent(std::string id1, std::string id2);
		std::vector<std::string> Neighbors(std::string id);
		std::vector <std::string> EasyToGetThere();
		bool IsDAG(void *ptr = nullptr);
		std::vector<std::string> DAGToArray();
	};

	template <class T, class E>
	class ALGraph_UnDir : public AMGraph<T, E> {

	public:
		ALGraph_UnDir() {
			this->matrix_en = false;
		}

		bool AddEdge(std::string id1, std::string id2, E value);
		void RemoveEdges(std::string id);
		bool RemoveEdge(std::string id1, std::string id2);
		std::tuple<E, bool> GetEdgeValue(std::string id1, std::string id2);
		bool SetEdgeValue(std::string id1, std::string id2, E value);
		bool Adjacent(std::string id1, std::string id2);
		std::vector<std::string> Neighbors(std::string id);
		bool SomeoneOntheInside(std::string my_id, std::vector<std::string> employees_ids);  // Stack [Depth First]
		std::string SomeoneOntheInside(std::vector<std::string> employees_ids);  
		std::vector<std::string> VertexIsReachable(const std::string& id1, const std::string& id2);  // recursion instead of Stack [Depth First]
		std::vector<std::vector<std::string>> AllPaths(const std::string& id1, const std::string& id2);  
		std::vector<std::string> ShortestPath(const std::string id1, const std::string id2);
		std::vector<std::string> GimmieNSteps(const std::string id1, const std::string id2, int n = 0);
	
	private:
		void  VertexIsReachable(std::string id1, std::string id2, std::vector<std::string> &path_list, std::map<std::string, bool> &visited, AM_Node_Vertex<T, E> *node = nullptr);
		void  AllPaths(const std::string& target, std::vector<std::vector<std::string>> &paths, std::vector<std::string> path, std::set<std::string> &visited, AM_Node_Vertex<T, E>* node = nullptr);

	};
	void SocialNetwork_ALGraph_UnDir_Test();
}
#endif 

