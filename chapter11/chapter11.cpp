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
extern int errno;
#include "chapter11.h"



namespace chapter11 {

	nodeBT* BTNode(int value) {
		nodeBT* node = new nodeBT;
		node->val = value;
		node->parent = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		node->count = 1;
		return node;
	}

	llNode* LLNode(int value) {
		llNode* node = new llNode;
		node->value = value;
		node->next = nullptr;
		return node;
	}

	int minF(int a) {
		static int min = a;
		if (a < min)
			min = a;
		return min;
	}

	int maxF(int a) {
		static int min = a;
		if (a > min)
			min = a;
		return min;
	}

	int countF(nodeBT* node) {
		static int counter = 0;
		counter += node->count;
		return counter;
	}

	nodeBT * BST::getRoot() {
		return root;
	}

	BST& BST::add(int value) {
		nodeBT* node = BTNode(value);
		nodeBT* runner = root;
		nodeBT* runner_prev = nullptr;

		treeNodeCount++;
	
		if (root == nullptr) {
			root = node;
		} else {
			while (runner) {
				runner_prev = runner;
				if (runner->val == value)
					runner = nullptr;
				else
					runner = (value >= runner->val) ? runner->right : runner->left;
			}

			if (value < runner_prev->val) {
				runner_prev->left = node;
				uniqueCount++;
			} else if (value > runner_prev->val) {
				runner_prev->right = node;
				uniqueCount++;
			} else {
				runner_prev->count++;
			}

			node->parent = runner_prev;
		}
		return *this;
	}


	BST& BST::add(nodeBT* node) {
		nodeBT* runner = root;
		nodeBT* runner_prev = nullptr;

		if (node) 
			treeNodeCount+= node->count;

		if (root == nullptr) {
			root = node;
		} else {
			while (runner) {
				runner_prev = runner;
				if (runner->val == node->val)
					runner = nullptr;
				else
					runner = (node->val >= runner->val) ? runner->right : runner->left;
			}

			if (node->val < runner_prev->val) {
				runner_prev->left = node;
				uniqueCount++;
			} else if (node->val > runner_prev->val) {
				runner_prev->right = node;
				uniqueCount++;
			} else {
				runner_prev->count++;
			}

			node->parent = runner_prev;
		}
		return *this;
	}
	template <class T> // default 
	static void appendStructure(T* buffer, nodeBT* node) { return; };

	template <> // specilization  template
	static void appendStructure(std::vector<int>* buffer, nodeBT* node) {
		buffer->push_back(node->val);
	}

	template <>
	static void appendStructure(std::vector<nodeBT *>* buffer, nodeBT* node) {
		buffer->push_back(node);
	}

	template <> 
	static void appendStructure(LinkedList* linkedList, nodeBT* node) {
		linkedList->insert(node->val);
	}

	template < class T>
	void BST::nodeValues(int mode, T* buffer, nodeBT* node) {

		if (!node)
			node = root;

		if (node == nullptr)
			return;

		if (mode == 0) {
			std::cout << '\t' << node->val << '\n';
			if (buffer)
				appendStructure(buffer, node);
		}

		if (node->left)
			nodeValues(mode, buffer, node->left);


		if (mode == 1) {
			std::cout << '\t' << node->val << '\n';
			if (buffer)
				appendStructure(buffer, node);
		}

		if (node->right)
			nodeValues(mode, buffer, node->right);

		if (mode == 2) {
			//std::cout << '\t' << node->val << " \t count:" << node->count << '\n';
			if (buffer)
				appendStructure(buffer, node);
		}


	}

	bool BST::contains(int val, nodeBT* node) {
		if (node == nullptr)
			node = root;

		if (node->val == val)
			return true;

		if (val < node->val && node->left)
			return contains(val, node->left);
		else if (node->right)
			return contains(val, node->right);

		return false;

	}

	int BST::min(nodeBT* node, int (*callback)(int)) {
		if (node == nullptr)
			node = root;

		if (node->left)
			min(node->left, callback);

		if (node->right)
			min(node->right, callback);

		return callback(node->val);

	}

	int BST::max(nodeBT* node, int (*callback)(int)) {
		if (node == nullptr)
			node = root;

		if (node->left)
			max(node->left, callback);

		if (node->right)
			max(node->right, callback);

		return callback(node->val);

	}

	int BST::size(nodeBT* node, int (*callback)(nodeBT*)) {
		if (node == nullptr)
			node = root;

		if (node->left)
			size(node->left, callback);

		if (node->right)
			size(node->right, callback);

		return callback(node);

	}

	bool BST::isEmpty() {
		return root == nullptr;
	}

	int BST::Height(nodeBT* node, int depth) {
		int height = depth;

		if (!node)
			node = root;

		std::cout << "  height  " << height << " -- " << node->val << "  --  " << '\n';

		if (node->left)
			height = Height(node->left, depth + 1);

		if (node->right)
			height = Height(node->right, depth + 1);


		return height;
	}

	bool BST::isBalanced(nodeBT* node, int depth) {
		int left = 0, right = 0;
		bool leftBal = true, rightBal = true;

		if (!node)
			node = root;

		if (node->left) {
			left = Height(node->left, depth + 1);
			leftBal = isBalanced(node->left);
		}

		if (node->right) {
			right = Height(node->right, depth + 1);
			rightBal = isBalanced(node->right);
		}

		return (std::abs(left - right) < 2) && rightBal && leftBal;
	}

	BST &BST::ArrayToBST(std::vector<int> arr) {
		int tmp, mid;
		while (!arr.empty()) {
			mid = static_cast<int>(arr.size() / 2);
			tmp = arr[mid];
			add(tmp);
			arr.erase(arr.begin() + mid);
		}
		return *this;
	}

	std::vector<int> CommonAncestor_helper(nodeBT* node, int value) {
		std::vector<int> result;

		while (node) {
			result.push_back(node->val);

			if (value < node->val)
				node = node->left;
			else if (value > node->val)
				node = node->right;
			else {
				node = nullptr;
			}
		}

		return result;
	}

	int BST::CommonAncestor(const int& a, const  int& b) {
		std::vector<int> p1 = CommonAncestor_helper(root, a);
		std::vector<int> p2 = CommonAncestor_helper(root, b);

		if (p1.back() != a || p2.back() != b)
			return -1;

		while (!p2.empty()) {
			if (std::find(p1.begin(), p1.end(), p2.front()) != p1.end())
				return p2.front();
			else
				p2.erase(p2.begin());
		}
		return -1;
	}

	std::vector<int>& BST::bst2Arr(std::vector<int>&& arr) {
		nodeValues(0, &arr);
		return arr;
	}

	std::vector<int>& BST::bst2ArrPre(std::vector<int>&& arr) {
		nodeValues(1, &arr);
		return arr;
	}
	std::vector<int>& BST::bst2ArrPost(std::vector<int>&& arr) {
		nodeValues(2, &arr);
		return arr;
	}

	void  BST::bst2List(int mode) {
		LinkedList linkedList;
		if ((mode >= 0 && mode <= 2)) {
			nodeValues(mode, &linkedList);
		}
		linkedList.print();
	}

	void BST::bst2ListPre(int mode) {
		bst2List(1);

	}
	void BST::bst2ListPost(int mode) {
		bst2List(2);

	}

	int minHeight_helper_min(int depth) {
		static int min = depth;
		if (depth < min)
			min = depth;
		return min;
	}

	int BST::minHeight(nodeBT* node, int depth) {
		int result;

		if (!node) {
			node = root;
		}

		if (!node->right && !node->left) // leaf node 
			result = minHeight_helper_min(depth);

		if (node->left)
			result = minHeight(node->left, depth + 1);
		if (node->right)
			result = minHeight(node->right, depth + 1);

		return result;
	}

	void BST::preOrderNoRecurion(nodeBT* node) {
		std::vector<nodeBT*> stack;
		nodeBT* runner = root;

		while (runner) {

			std::cout << runner->val << '\n';

			if (runner->right)
				stack.insert(stack.begin(), runner->right);

			if (runner->left) {
				runner = runner->left;
			}
			else if (!stack.empty()) {
				runner = stack.front();
				stack.erase(stack.begin());
			}
			else {
				runner = nullptr;
			}
		}
	}

	int BST::ValBefore(int value, nodeBT* node) {
		int resultNodeValue = 0xDEADBEEF;
		nodeBT* resultNode = nullptr;

		if (node == nullptr)
			node = root;

		if (!node)
			return resultNodeValue;

		if (node->val >= value) {
			resultNode = node->parent;
			resultNodeValue = resultNode->val;
		}

		if (node->left && !resultNode)
			resultNodeValue = ValBefore(value, node->left);

		if (node->right && !resultNode)
			resultNodeValue = ValBefore(value, node->right);

		return resultNodeValue;
	}

	int BST::ValAfter(int value, nodeBT* node) {
		int resultNodeValue = 0xDEADBEEF;
		nodeBT* resultNode = nullptr;

		if (node == nullptr)
			node = root;

		if (!node)
			return resultNodeValue;

		if (node->val >= value) {
			resultNode = node;
			resultNodeValue = resultNode->val;
		}

		if (node->left && !resultNode)
			resultNodeValue = ValAfter(value, node->left);

		if (node->right && !resultNode)
			resultNodeValue = ValAfter(value, node->right);

		return resultNodeValue;

	}

	nodeBT* BST::NodeBefore(nodeBT* findNode, nodeBT* node) {
		nodeBT* resultNode = nullptr;
		if (!node)
			node = root;


		if (node == findNode)
			resultNode = node->parent;

		if (node->left)
			resultNode = NodeBefore(findNode, node->left);

		if (node->right && !resultNode)
			resultNode = NodeBefore(findNode, node->right);

		return resultNode;
	}

	nodeBT* BST::NodeAfter(nodeBT* findNode, nodeBT* node) {
		nodeBT* resultNode = nullptr;
		if (!node)
			node = root;

		if (node->parent == findNode)
			resultNode = node;

		if (node->left)
			resultNode = NodeBefore(findNode, node->left);

		if (node->right && !resultNode)
			resultNode = NodeBefore(findNode, node->right);

		return resultNode;
	}


	static int closestValue_helper_min(const int& d0, const int& d1) {
		static int d = d1;
		if (std::abs(d0 - d1) < std::abs(d0 - d))
			d = d1;
		return d;
	}

	int BST::closestValue(const int& value, nodeBT* node) {
		int min;

		if (!node)
			node = root;

		min = closestValue_helper_min(value, node->val);

		if (node->left)
			min = closestValue(value, node->left);

		if (node->right)
			min = closestValue(value, node->right);

		return min;
	}


	bool BST::TreePathContainsSum(const int& sum, int currSum, nodeBT* node) {
		int boolstate = false;

		if (!node)
			node = root;

		if (!node)
			return boolstate;

		currSum += node->val;

		if (currSum > sum)
			return boolstate;

		if (sum == currSum && (!node->left || !node->right))
			boolstate = currSum == sum;

		if (node->left && !boolstate)
			boolstate = TreePathContainsSum(sum, currSum, node->left);
		if (node->right && !boolstate)
			boolstate = TreePathContainsSum(sum, currSum, node->right);

		return boolstate;
	}

	int& TreePathContainsSum_helper(const std::vector<int> list, int&& count = 0) {
		for (auto num : list) { count += num; }
		return count;
	}

	void BST::TreePathContainsSum(const int& sum, std::vector<std::vector<int>>& bucket, std::vector<int>  arr, nodeBT* node) {
		int currSum = TreePathContainsSum_helper(arr);
		bool stateBool = (currSum == sum);

		if (!node)
			node = root;

		if (!node || currSum > sum)
			return;

		if (stateBool) {
			bucket.push_back(arr);
			return;
		}

		arr.push_back(node->val);

		if (node->left)
			TreePathContainsSum(sum, bucket, arr, node->left);
		if (node->right)
			TreePathContainsSum(sum, bucket, arr, node->right);
	}

	static void writeNode(nodeBT* source, nodeBT* destination) {
		destination->count = source->count;
		destination->parent = source->parent;
		destination->val = source->val;
	}


	void connect_parent_of_target_to_element(nodeBT* target_node, nodeBT * replacement_node, nodeBT* parent) {
		if (!parent || !target_node)
			return; 

		if (parent->left == target_node)
			parent->left = replacement_node;
		if (parent->right == target_node)
			parent->right = replacement_node;
	}

	std::array<nodeBT*, 2> BST::get_inOrder_successor(nodeBT* node) {
		nodeBT* prev = node;
		std::array<nodeBT*, 2>  a;

		try {
			a = { node->right, node };

			while (a[0]->left) {
				a[1] = a[0];
				a[0] = a[1]->left;
			}

			return a;

		} catch (...) {

			return { nullptr, nullptr };
		}
	
	}



	void BST::Remove_Op(nodeBT* target_node, nodeBT* parent) {
		nodeBT* buffer = target_node;
		std::array<nodeBT*, 2>  successor_data;

			// single child leaf
		if (!target_node->left && target_node->right && parent) {    
			connect_parent_of_target_to_element(target_node, target_node->right, parent);
		} 

			// single child leaf
		else if (!target_node->right && target_node->left && parent) {  
			connect_parent_of_target_to_element(target_node, target_node->left, parent);
		}

			// leaf 
		else if (!target_node->left && !target_node->right ) { 
			if (!parent) {
				root = nullptr;
			} else if (parent) {
				connect_parent_of_target_to_element(target_node, nullptr, parent);
			}
		}

			// full node
		else if (target_node->left && target_node->right) {				
			successor_data = get_inOrder_successor(target_node);				// [up_insert node, parent]
			connect_parent_of_target_to_element(successor_data[0], successor_data[0]->right, successor_data[1]);  //  parent of successor node (up_inserted node)


			successor_data[0]->left = target_node->left; 
			successor_data[0]->right = target_node->right;
			connect_parent_of_target_to_element(target_node, successor_data[0], parent);  // connect parent of target to up_inserted node 
			
			if (!parent) {
				root = successor_data[0];
			}
		}

		--uniqueCount;
		delete buffer;

	}

	bool BST::Remove(int val, nodeBT* node, nodeBT* prev) {
		if (!node)
			node = root;

		if (node->val == val) {
			treeNodeCount--;
			node->count--;
			if (node->count == 0) {
				Remove_Op(node, prev);
			}
			return true;
		}

		if (val < node->val)
			return Remove(val, node->left, node);

		if (val > node->val)
			return Remove(val, node->right, node);

		return false;
	}

	void BST::RemoveAll(nodeBT* node) {
		if (!node)
			node = root;
		
		if (!node)
			return; 
		if (node->left)
			RemoveAll(node->left);
		if (node->right)
			RemoveAll(node->right);

		if (root == node) {
			root = nullptr;
			treeNodeCount = 0;
		}

		delete node;

	}

	void isValid_helper(nodeBT *node, int & avg, int & countElements, int &cnt) {
		int newAvg;

		if (node->left)
			isValid_helper(node->left, avg, countElements, cnt);
	
		newAvg = ((node->val + avg) / ++countElements) > avg;
		cnt += +(newAvg > avg);
		avg = newAvg;
		
		if (node->right)
			isValid_helper(node->right, avg, countElements, cnt);
	}


	bool BST::IsValid(nodeBT* node) {
		int avg = 0;
		int count = 0; 
		int cnt = 0; 
		isValid_helper(node, avg, count, cnt);
		return cnt == count;
	}

	void BST::TraverseBSTReverseOrder(nodeBT* node) {
		if (!node)
			node = root;
		if (node->right)
			TraverseBSTReverseOrder(node->right);
		std::cout << "\n" << node->val << " \t rev order";
		if (node->left)
			TraverseBSTReverseOrder(node->left);
	}


	void BST::RootLeafNumber(nodeBT* node, std::string&& currStr) {

		if (!node)
			node = root;

		currStr += " -> " + std::to_string(node->val);

		if (!node->left && !node->right) {
			std::cout << currStr << '\n';
		}

		if (node->left)
			RootLeafNumber(node->left, currStr + "");


		if (node->right)
			RootLeafNumber(node->right, currStr + "");

	}

	std::vector<int> BST::LeftSideBinary(std::vector<int> collection) {
		nodeBT* runner = root;
		std::vector<nodeBT*> list;
		bool fallenFromPeak = false;

		while (runner) {
			collection.push_back(runner->val);
			if (runner->right && !fallenFromPeak)
				list.push_back(runner->right);
			if (runner->left) {
				runner = runner->left;
				fallenFromPeak = true;
			}
			else if (!list.empty()) {
				fallenFromPeak = false;
				runner = list[list.size() - 1];
				list.pop_back();
			}
			else
				runner = nullptr;
		}
		return collection;
	}

		// PART II

	bool BST::IsFull(chapter11::nodeBT* btNode) {
		bool right = true, left = right;
		bool parentState = (btNode->left && btNode->right) || (!btNode->left && !btNode->right);

		if (btNode->left)
			left = IsFull(btNode->left);

		if (btNode->right)
			right = IsFull(btNode->right);

		return right && left && parentState;
	}

	static void BST_IsComplete_helper_depthCount(chapter11::nodeBT* btNode, std::vector<int>& arr, int depth = 0) {
		if (btNode->left)
			BST_IsComplete_helper_depthCount(btNode->left, arr, depth + 1);

		if (arr.empty())	// left most value
			arr.push_back(depth);
		else if (btNode->right)
			BST_IsComplete_helper_depthCount(btNode->right, arr, depth + 1);

		if ((arr.back() < depth) && !btNode->right && !btNode->left)
			arr.push_back(depth);
	}

	bool  BST::IsComplete(chapter11::nodeBT* btNode) {
		std::vector<int> arr;
		BST_IsComplete_helper_depthCount(btNode, arr);
		return arr.size() == 1;
	}


	bool BST::Repair(nodeBT* node) {
		std::vector<nodeBT*> *nodeArray;
		nodeBT* bufferNode = nullptr; 

		if (IsValid(node)) {
			return false;
		} else {
			nodeArray = new std::vector<nodeBT*>;
			nodeValues(1, nodeArray);

			for (int i = 0; i < nodeArray->size(); i++) {

				bufferNode = nodeArray->at(i);
				bufferNode->left = nullptr;
				bufferNode->right = nullptr;

				if (i == 0) {
					bufferNode->parent = nullptr;
					root = bufferNode;
				}
				else {
					add(bufferNode);
				}
			}

			delete nodeArray;
			return true;
		}
	}


	int BST::SmallestDifference(BST& bst) {
		std::vector<nodeBT*> *Q = new std::vector<nodeBT*>;
		nodeBT* node; 
		int minDiff, diff = INT32_MAX;
		
		Q->push_back(bst.root);

		while (Q->size()) {
			node = Q->back();
			Q->pop_back();

			if (node->right)
				Q->insert(Q->begin(), node->right);

			if (node->left)
				Q->insert(Q->begin(), node->left);

			if (node->right) {
				minDiff = std::abs(node->right->val - node->val);
				if (minDiff < diff) {
					diff = minDiff;
				}
			}

			if (node->left) {
				minDiff = std::abs(node->left->val - node->val);
				if (minDiff < diff) {
					diff = minDiff;
				}
			}

		}
		delete Q;
		return diff;

	}
	

	BST  BST::PartitionAroundValue(int value, nodeBT* node) {
		BST bst;
		
		if (node == nullptr)
			node = root; 
		
		if ( (node->val == value)  || (!node->right && !node->left)) {  // node match or leaf node 
			bst.root = node;
			if (root == node) 
				root = nullptr;
				
		} else if (node->parent) {  // between parent and child 
			if ((node->parent->val > value && value > node->val)  || (node->parent->val < value && node->val > value ))
				bst.root = node; 
		}

		if (bst.root) {
			if (node->parent) {
				if (node->parent->left == node)
					node->parent->left = nullptr;

				if (node->parent->right == node)
					node->parent->right = nullptr;
			}
			return (bst);
		}

		if (node->left) {
			if (value > node->val) 
				return PartitionAroundValue(value, node->left);
		}

		if (node->right) {
			if (value < node->val)
				return PartitionAroundValue(value, node->right);
		}

		return bst;
	}

	static void PartitionEvenly_Helper(BST &bst_dest, BST & bst_src, const int &max, nodeBT* node, int &cnt ) {
		nodeBT * buffer;

		if (!node || cnt == max)
			return;
		
		if (node->left)
			PartitionEvenly_Helper(bst_dest, bst_src,max,  node->left, ++cnt);

		if (node->right)
			PartitionEvenly_Helper(bst_dest, bst_src,  max, node->right, ++cnt);

		buffer = bst_src.removeLeaf(node);
		
		if (buffer)
			bst_dest.add(buffer);

	}

	BST BST::PartitionEvenly() {
		BST bst;
		int count = 0, maxCount = uniqueCount / 2;

		if (treeNodeCount <= 1) { 	//root only exist 
			bst.root = root;
			root = nullptr;
		} else {
			PartitionEvenly_Helper(bst, *this , maxCount, root, count);
		}

		return bst;
	}

	nodeBT * BST::removeLeaf(nodeBT* leaf) {
		nodeBT* buffer = nullptr;

		if ( leaf  == nullptr || (leaf->right || leaf->left) == true) // not leaf node! 
			return nullptr;

		if (!leaf->parent) { // root node!
			return  leaf;
			root = nullptr;
		}

		if (leaf->parent) {
			buffer = leaf; 

			if (leaf->parent->right == leaf)
				leaf->parent->right = nullptr;

			if (leaf->parent->left == leaf)
				leaf->parent->left = nullptr;

			return buffer;
		}

		treeNodeCount -= buffer->count ;
	}


	static void Reverse_helper_loadArray(nodeBT* root, int num, std::vector<std::tuple <nodeBT*, nodeBT*, std::string>> &nodeArray) {
		nodeBT* node;
		nodeBT* parent = nullptr;
		std::vector < nodeBT*> arr;

		if (num == 1) {
			arr.push_back(root->right);
			nodeArray.push_back(std::make_tuple(root->right, root, "right"));

			while (!arr.empty()) {
				node = arr.front();
				arr.erase(arr.begin());


				if (node->right) {
					arr.push_back(node->right);
					nodeArray.push_back(std::make_tuple(node->right, node, "right"));
				}

				if (node->left) {
					arr.push_back(node->left);
					nodeArray.push_back(std::make_tuple(node->left, node, "left"));
				}

			//
				printf("val \t %d\n", node->val);
			}
		}

		if (num == 0) {
			arr.push_back(root->left);
			nodeArray.push_back(std::make_tuple(root->left, root, "left"));

			while (!arr.empty()) {
				node = arr.front();
				arr.erase(arr.begin());

				if (node->left) {
					arr.push_back(node->left);
					nodeArray.push_back(std::make_tuple(node->left, node, "left"));
				}

				if (node->right) {
					arr.push_back(node->right);
					nodeArray.push_back(std::make_tuple(node->right, node, "right"));
				}
				printf("val \t %d\n", node->val);

			}
		}

	}

	void BST::Reverse(BST& bst) {
		std::vector<std::tuple <nodeBT*, nodeBT *, std::string>> rightArray, leftArray;
		nodeBT* node, * parent, * curr_parent = root;
		std::string dir;

		if (!bst.root)
			return; 

		Reverse_helper_loadArray(bst.root, 1, rightArray);
		Reverse_helper_loadArray(bst.root, 0, leftArray);

		curr_parent->left = nullptr;
		curr_parent->right = nullptr;

		for (auto arr : { leftArray, rightArray  }) {
			curr_parent = root;

			for (auto curr_tuple : arr) {
				std::tie(node, parent, dir) = curr_tuple;
				node->parent = nullptr;
				node->left = nullptr;
				node->right = nullptr;
				
				curr_parent = parent;

				if (dir == "left")					
					curr_parent->right = node;
				if (dir == "right") 
					curr_parent->left = node;
			}
		}



	}


	static void KthBiggest_Unique_helper(int k, int& counter, bool& found_k_value, int& val, nodeBT* node) {
		if (!node)
			return;

		if (node->right)
			KthBiggest_Unique_helper(k, counter, found_k_value, val, node->right);

		if (node && (counter <= k))
			counter++;

		if (counter == k)
			val = node->val;

		std::cout << counter <<  " " << " " << node->val << '\n';
		if (node->left)
			KthBiggest_Unique_helper(k, counter, found_k_value, val, node->left);

	}

	std::tuple<int, bool> BST::KthBiggest_Unique(int k) {
		int val = 0, counter = 0;
		bool found_k_value = false;

		if (k > uniqueCount)
			return std::make_tuple(0, false);

		KthBiggest_Unique_helper(k, counter, found_k_value, val, root);
		return std::make_pair(val, found_k_value);
	}

	static void KthBiggest_helper(int k, int& counter, bool& found_k_value, int& val, nodeBT* node) {
		int curr_node_count = 0;
		
		if (!node)
			return;

		if (node->right)
			KthBiggest_helper(k, counter, found_k_value, val, node->right);

		while ((curr_node_count < node->count) && node && (counter <= k)) {
			curr_node_count++;
			counter++;

			if (counter == k)
				val = node->val;
		}

		if (node->left)
			KthBiggest_helper(k, counter, found_k_value, val, node->left);

	}

	std::tuple<int, bool> BST::KthBiggest(int k) {
		int val = 0, counter = 0;
		bool found_k_value = false;
		 
		if (k > treeNodeCount)
			return std::make_tuple(0, false);

		KthBiggest_helper(k, counter, found_k_value, val, root);
		return std::make_pair(val, found_k_value);
	}

	std::vector<int> BST::ValueForLayer(int n) {
		std::vector<nodeBT*> Q;
		std::vector<int> result; 
		nodeBT *node;
		int counter = 0;
		int rowStart = std::pow(2, n);
		int nextRowStart = std::pow(2, n + 1);

		if (root) {
			Q.push_back(root);
		}

		while (!Q.empty()) {
			
			node = Q.front();
			
			if (node)
				counter++;

			Q.erase(Q.begin());

			if (node->left)
				Q.push_back(node->left);

			if (node->right)
				Q.push_back(node->right);

			if ((counter >= rowStart) && (counter < nextRowStart))
				result.push_back(node->val);
		}

		return result;
	}

	std::vector<std::shared_ptr<std::vector<int>>> BST::LayerArrays () {
		std::vector<nodeBT*> Q;
		std::vector<std::shared_ptr<std::vector<int>>> result;
		nodeBT* node;
		int counter = 0, row = -1, calcRow = 0;

		if (root) 
			Q.push_back(root);
		
		while (!Q.empty()) {
			node = Q.front();

			if (node) {
				counter++;
				calcRow = std::log2(counter);
				
				if (calcRow != row) {
					row = calcRow;
					result.push_back(std::make_shared<std::vector<int>>());
				}
			}

			Q.erase(Q.begin());

			if (node->left)
				Q.push_back(node->left);

			if (node->right)
				Q.push_back(node->right);

			result[row]->push_back(node->val);
		}

		return result;
	}
}
