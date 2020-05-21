#include <iostream>
#include "AlgorithmBook.h"
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


namespace chapter19 {
	/* DEBUG FUNTION TO VIEW CURRENT VALUES IN TREE */
	template <typename T>
	void AVLTree<T>::printTree(AVLNode<T>* node, const unsigned& depth, const unsigned& index ) {
		int shift; 
		char buffer[100];

		if (!node)
			node = head; 
	
		if (!node->left && !node->right)
			return;

		if (depth == 0) {
			for (int i = 0; i < 10; i++) collection->at(i)->clear();
		}

			if (node->left && node->right)
				std::snprintf (buffer, 100, "%d <- %d -> %d   bal: %d  ht: %d", node->left->val, node->val, node->right->val, node->balance , node->height());
			
			else if (node->left && !node->right)
				std::snprintf(buffer, 100, "%d <- %d -> x   bal: %d   ht: %d ",  node->left->val, node->val, node->balance, node->height());
			
			else if (!node->left && node->right)
				std::snprintf(buffer, 100, "x <- %d-> %d   bal: %d   ht: %d ", node->val, node->right->val , node->balance, node->height() );
			
			else if (!node->left && !node->right)
				std::snprintf(buffer, 100,     "x <- x -> x");

			
			collection->at(depth)->push_back (buffer);

		if (node->left) {
			shift = depth * 2 + 1;
			printTree(node->left, depth + 1, shift);
		}
		if (node->right) {
			shift = depth * 2 + 2; 
			printTree(node->right, depth + 1,  shift);
		}

		if (depth == 0) {
			for (auto arr : *collection) {

				if (arr->empty())
					continue;

				for (auto ele : *arr) {
					if (ele.size())
						printf("%s\t", ele.c_str());
				}

				printf("\n");

			}
		}
	}

	template <typename T>
	bool AVLTree<T>::trace_left(const T value, const bool &is_mutable, AVLNode<T> *node) {

		if (node->left) {
			if (value < node->val) {
				return true;
			}
		}
		return false;
	}

	template <typename T>
	bool AVLTree<T>::trace_right(const T value,const  bool &is_mutable, AVLNode<T>* node) {
		if (node->right) {
			if (value > node->val) {
				return true;
			}
		}
		return false;
	}

	template <typename T>
	bool AVLTree<T>::insert_equal(const T value, AVLNode<T>* node) {
		bool state = false;
		if (node->val  == value) {
			node->count++;
			state = true;
		}
		return state;
	}

	template <typename T>
	bool AVLTree<T>::insert_left(const T value, AVLNode<T>* node) {
		if (value < node->val) {
			node->left = avl_node(value);
			return true;
		}
		return false;
	}

	template <typename T>
	bool AVLTree<T>::insert_right(const T value, AVLNode<T>* node) {
		if (value > node->val) {
			node->right = avl_node(value);
			return true;
		}
		return false;
	}

	template <typename T>
	void AVLTree<T>::balance_add_review(AVLNode<T>* start, AVLNode<T>* end, AVLNode<T>* parent_of_end,  bool rotate_en) {

		if (!!parent_of_end->left ^ !!parent_of_end->right) {
			update_balance_increment(start, end);
		}
		else if (!!parent_of_end->left && !!parent_of_end->right) {

			update_balance_increment(parent_of_end, end);
		}
			
		if (rotate_en) 
			rebalance_target(start);
	}

	template <typename T>
	void AVLTree<T>::add(T value, AVLNode<T> *node, AVLNode<T>* parent, AVLNode<T>* start) {

		if (!head) {

			head = avl_node(value);
		
		} else {
			
			if (!node) 
				node = head;

			if (!start)
				start = head;

			if (trace_left(value, true, node)) 
				return add(value, node->left, node, (node->balance < 0) ? node : start);
			
			else if (trace_right(value, true, node)) 
				return add(value, node->right, node, (node->balance > 0) ? node : start);
			
			else if (insert_equal(value, node))
				return;
			
			else if (insert_left(value, node))
				return balance_add_review(start, node->left, node);

			else if (insert_right(value, node))
				return balance_add_review(start, node->right, node);

		}

	}

	template <typename T> 
	void AVLTree<T>::connect_parent_of_target_to_element(AVLNode<T>* target, AVLNode<T>* subtree, AVLNode<T>* parent) {

		if (!parent)
			return; 

		if (parent->left == target)
			parent->left = subtree;

		if (parent->right == target)
			parent->right = subtree;
	}

	template <typename T> 
	std::array<AVLNode<T>*, 3> AVLTree<T>::successor(AVLNode<T>* node) {
		std::array<AVLNode<T>*, 3> array = {node->right, node, node};
		
		try {
			while (array[0]->left) {
				array[2] = (array[0]->balance <= 0) ? array[0] : array[2]; // store node causing tree(subtree) balance change 
				array[1] = array[0];
				array[0] = array[1]->left;
			}
			return array;
		} catch (...) {
			return { nullptr, nullptr };
		}

	}
	
	template <typename T> 
	void AVLTree<T>::remove_op(AVLNode<T>* target, AVLNode<T> *parent, AVLNode<T> * root_node) {
		std::array<AVLNode<T>*, 3> successor_data;

		// single leaf child
		if (!!target->left ^ !!target->right) {
			update_balance_decrement(root_node, target);
			connect_parent_of_target_to_element(target, !!target->left ? target->left : target->right, parent);
		}

		// leaf node 
		else if ((!!target->right || !!target->left) == NULL) {
			if (target == head) {
				head = nullptr;
			} else {
				update_balance_decrement(root_node, target);
				connect_parent_of_target_to_element(target, target->right, parent);
			}
		}

		// full node
		else if (!!target->right && !!target->left) { 
			
			successor_data = successor(target);

			update_balance_decrement(successor_data[2], successor_data[0]);
			std::swap(target->balance, successor_data[0]->balance);

			if (target == head) {
				head = successor_data[0];
			}

			// connect successor's parent to successor subtree 
			connect_parent_of_target_to_element(successor_data[0], successor_data[0]->right, successor_data[1]); 

			// connect successor to target's children
			successor_data[0]->left = target->left;		
			successor_data[0]->right = target->right;

			// connect target's parent to successor  
			connect_parent_of_target_to_element(target, successor_data[0], parent);

		}

		delete target;
	}

	template <typename T > 
	bool AVLTree<T>::remove(T value, AVLNode<T>* node, AVLNode<T>* parent, AVLNode<T>* start) {

		if (!node) 
			node = head;
		
		if (!start)
			start = head; 

		if (value == node->val) {
			remove_op(node, parent, start);
			return true;
		}
		
		if (value < node->val)
			return remove(value, node->left, node, (node->balance <= 0) ? node : start);
		
		if (value > node->val)
			return remove(value, node->right, node, (node->balance >= 0) ? node : start);

		return false;
	}

	template <typename T>
	signed AVLTree<T>::isBalanced() {
		return head->isBalanced();
	}

	template <typename T>
	signed AVLTree<T>::height() {
		return head->height();
	}

	template <typename T>
	AVLNode<T>*AVLTree<T>::get_root() {
		return head;
	}

	template <typename T>
	void AVLTree<T>::rotate_right(AVLNode<T>* target_node, AVLNode<T>* curr, AVLNode<T>* prev) {
		if (!curr)
			curr = head;

		if (target_node->val == curr->val)
			return rotate_right_rot(curr, prev);

		if (!curr->left  && !curr->right)
			return; 

		if (target_node->val < curr->val)
			return rotate_right(target_node, curr->left, curr);
		if (target_node->val > curr->val)
			return rotate_right(target_node, curr->right, curr);

	}

	template <typename T>
	void AVLTree<T>::rotate_left(AVLNode<T>* target_node, AVLNode<T>* curr, AVLNode<T>* prev) {

		if (!curr)
			curr = head;

		if (target_node == curr)
			return rotate_left_rot(curr, prev);

		if (!curr->left && !curr->right)
			return;

		if (target_node->val < curr->val)
			return rotate_left(target_node, curr->left, curr);
		if (target_node->val > curr->val)
			return rotate_left(target_node, curr->right, curr);
	}

	template <typename T>
	void AVLTree<T>::updateBalance(AVLNode<T>* p) {
		if (!p)
			return; 

		if (!p->left && !p->right) {
			p->balance = 0;
		}

		else if (p->left == nullptr && p->right) {
			p->balance = (p->right->height() + 1) * -1;
		}
		
		else if (p->left && p->right == nullptr) {
			p->balance = (p->left->height() + 1);
		}

		else if (p->left != nullptr && p->right != nullptr) {
			p->balance = p->left->height() - p->right->height();
		}

	}


	template <typename T>
	void AVLTree<T>::balance_path_decrement(AVLNode<T>* target, AVLNode<T>* node) {

		if (!node) {
			node = head;
		}

		if (target == node)
			return;

		std::cout << " decrmenet "  << node->val << "\t" << node->balance << '\n';

		if (target->val < node->val) {
			node->balance -= 1;
			return balance_path_decrement(target, node->left);
		}
		
		if (target->val > node->val) {
			node->balance += 1;
			return balance_path_decrement(target, node->right);
		}

	}

	template <typename T> 
	void AVLTree<T>::update_balance_decrement(AVLNode<T>* node, AVLNode<T>* leaf) {
		if (leaf->val < node->val) {
			node->balance -= 1;
			return update_balance_decrement(node->left, leaf);
		}

		if (leaf->val > node->val) {
			node->balance += 1;
			return update_balance_decrement(node->right, leaf);
		}
	}

	template <typename T>
	void AVLTree<T>::update_balance_increment(AVLNode<T>* node, AVLNode<T>* leaf) {
		if (leaf->val < node->val) {
			node->balance += 1;
			update_balance_increment(node->left, leaf);
		}

		if (leaf->val > node->val) {
			node->balance -= 1;
			update_balance_increment(node->right, leaf);
		}
	}

	template <typename T>
	void AVLTree<T>::rotate_right_rot(AVLNode<T>* p, AVLNode<T>* gp) {
		AVLNode<T> *sibling = p->right, *active_child = p->left;

		if (!gp) {
			head = active_child;
		} else {
			connect_parent_of_target_to_element(p, active_child, gp);
		}

		p->left = active_child->right;
		active_child->right = p;

		updateBalance(p);
		updateBalance(active_child);
		updateBalance(gp);

	}

	template <typename T>
	void AVLTree<T>::rotate_left_rot(AVLNode<T>* p, AVLNode<T>* gp) {
		AVLNode<T>* sibling = p->left, * active_child = p->right;

		if (!gp) {
			head = active_child;
		} else {
			connect_parent_of_target_to_element(p, active_child, gp);
		}
		
		p->right = active_child->left;
		active_child->left = p;

		updateBalance(p);
		updateBalance(active_child);
		updateBalance(gp);

	}

	template <typename T>
	std::string AVLTree<T>::rotate_code(AVLNode<T>* node) {
		std::string code;
		for (int i = 2; i--; ) {
			if (node->balance > 0) {
				node = node->left;
				code += 'l';
			} else if (node->balance < 0) {
				node = node->right;
				code += 'r';
			}
		}
		return code;
	}

	template <typename T>
	void AVLTree<T>::balance_add(T value, AVLNode<T>* node, AVLNode<T>* parent, AVLNode<T>* start) {
		std::vector<AVLNode<T>*> nodeList;

		if (!head) {
			head = avl_node(value);
		} else {

			if (!node) {
				node = head;
			}

			if (!start) {
				start = head;
			}

			if (trace_left(value, true, node))
				return balance_add(value, node->left, node, (node->balance < 0) ? node : start);

			else if (trace_right(value, true, node))
				return balance_add(value, node->right, node, (node->balance > 0) ? node : start);

			else if (insert_equal(value, node))
				return;

			else if (insert_left(value, node)) {
				return balance_add_review(start, node->left, node, true);
			}

			else if (insert_right(value, node)) {
				return balance_add_review(start, node->right, node, true);
			}

		}


	}

	template <typename T>
	void AVLTree<T>::rotate( AVLNode<T>* node) {
		std::string code; 
		code = rotate_code(node);
		printf("code  %s\n", code.c_str());
		if (code.length() != 2)
			return; 

		if (code == "rr") {
			printf("left rotation\t %d\n", node->val);
			rotate_left(node);
		}
		
		else if (code == "ll") {
			printf("right rotation\t %d \n", node->val);
			rotate_right(node);
		}
		
		else if (code == "rl") {
			printf("left right rotation \t %d \n", node->val);
			rotate_right(node->right);
			rotate_left(node);
		}
		
		else if (code == "lr") {
			printf("right left rotation \t %d \n", node->val);
			rotate_left(node->left);
			rotate_right(node);
		}
	}



	template <typename T> 
	void AVLTree<T>::rebalance_tree_rotate( AVLNode<T>* p) {
		int num = -1; 
		AVLNode<T>* lc = nullptr, *rc = nullptr;

		if (!p)
			return; 

		if (p->left)
			lc = p->left;
		
		if (p->right)
			rc = p->right;

		if (p->balance > 1) {
			if (lc->balance < 0) {
				rotate_left(lc);
			}
			rotate_right(p);
		}

		if (p->balance < -1) {
			if (rc->balance > 0) {
				rotate_right(rc);
			}
			rotate_left(p);
		}

		if (std::abs(p->balance) > 1) {
			rebalance_tree_rotate(p);
		}

		if (lc) {
			if (std::abs(lc->balance) > 1) {
				rebalance_tree_rotate(lc);
			}
		}

		if (rc) {
			if (std::abs(rc->balance) > 1) {
				rebalance_tree_rotate(rc);
			}
		}
		
	}

	template <typename T>
	T AVLTree<T>::sum_node(AVLNode<T>* node) {
		std::vector<AVLNode<T>*> queue {node};
		AVLNode<T> *buffer_node; 
		T sum = T{ 0 };

		while (!queue.empty()) {
			buffer_node = queue.front();
			queue.erase(queue.begin());

			if (buffer_node->left) {
				queue.push_back(buffer_node->left);
			}

			if (buffer_node->right) {
				queue.push_back(buffer_node->right);
			}
			sum += T{ buffer_node->val };
		}
		return sum ;
	}

	template <typename T>
	bool AVLTree<T>::balance_remove(T value, AVLNode<T> *node, AVLNode<T> * parent, AVLNode<T> * start) {
		bool has_removed_node = false; 

		if (!node) {
			node = head;
		}

		if (!start) {
			start = head;
		}

		if (node->val == value) {
			remove_op(node, parent, start);
			return true;
		}

		if (value < node->val) {
			has_removed_node =  balance_remove(value, node->left, node, (node->balance <= 0) ? node : start);
		}

		if (value > node->val) {
			has_removed_node =  balance_remove(value, node->right, node, (node->balance >= 0) ? node : start);
		}

		if (has_removed_node) {
			if (std::abs(node->balance) > 1) {
				rotate(node);
			}
		}

		return has_removed_node;
	}


	template <typename T>
	void AVLTree<T>::rebalance_target(AVLNode<T> * target, AVLNode<T>* runner) {

		if (!target)
			return; 

		if (!runner) {
			runner = head;
		}

		if (target->val < runner->val) {
			rebalance_target(target, runner->left);
		}

		if (target->val > runner->val) {
			rebalance_target(target, runner->right);
		}

		if (runner) {


			if (runner->left) {
				if (std::abs(runner->left->balance) > 1) {
					rotate(runner->left);
				}
			}

			if (runner->right) {
				if (std::abs(runner->right->balance) > 1) {
					rotate(runner->right);
				}
			}

		}
	

	}

	template class AVLTree<signed>;
	template class AVLTree<unsigned>;
	template class AVLTree<std::string>;


	template <typename T>
	void RBTree<T>::add(T value, RBNode<T> *node, RBNode<T> *prev_node) {
		RBNode<T>* node_ref = nullptr;

		if (!node && !prev_node) {
			node = root;
		}

		if (!root) {
			root = rb_node(value);
		} else {
			if (value == node->value) {
				++node->count;
			} else if (value > node->value  && node->right) {
				add(value, node->right, node);
			} else if (value < node->value && node->left) {
				add(value, node->left, node);
			} else if (value < node->value) {  
				node_ref = rb_node(value);
				node->left = node_ref;
			} else if (value > node->value) {
				node_ref = rb_node(value);
				node->right = node_ref;
			}

			if (!!node_ref) {
				while (tree_validate(node_ref->value));
			}
		}


	}

	template <typename T> 
	bool RBTree<T>::tree_validate(const T &value , RBNode<T> *runner, RBNode<T> *runner_prev, unsigned rr_count) {
		
		if (!runner) {
			runner = root;
		}

		if (value < runner->value && !!runner->left) {  
			if (runner->color == RED && runner->left->color == RED) {		//	red parent and red child
				rr_op(runner, runner_prev, runner->left);
				rr_count++;
			}
			return  tree_validate(value, runner->left, runner, rr_count);
		}

		if (value > runner->value && !!runner->right) {
			if (runner->color == RED && runner->right->color == RED) {		//	red parent and red child
				rr_op(runner, runner_prev, runner->right);
				rr_count++;
			}
			 return tree_validate(value, runner->right, runner, rr_count);
		}

		return rr_count;
	}

	template <typename T> 
	void RBTree<T>::getValues(RBNode<T>* node ) {
		if (!node)
			node = root; 
		printf("VALUE: [%d] COLOR: [%d]\n", node->value, node->color);

		if (node->left)
			 getValues(node->left);
		if (node->right)
			 getValues(node->right);
	}

	template <typename T>
	bool RBTree<T>::contains(const T& value, RBNode<T>* node) {
		if (!node) {
			node = root; 
		}

		if (value == node->value)
			return true; 

		if (value < node->value)
			return contains(value, node->left);

		if (value > node->value)
			return contains(value, node->right);

		return false; 
	}

	template <typename T>
	void RBTree<T>::rr_op(RBNode<T>* p, RBNode<T>* gp, RBNode<T>* c) {
		RBNode<T>* s = nullptr;
		std::string code; 

		if (gp) {
			s = (gp->right == p) ? gp->left : gp->right;
			if (s) {
				if (s->color == BLACK) {
					code += (gp->right == p) ? 'r' : 'l';
					code += (p->right == c) ? 'r' : 'l';
					rotate_op(code, gp);
				} else  if (s->color == RED) {
					paint_node_toggle(s);
					paint_node_toggle(p);
					paint_node_toggle(gp);
				}

			} else if (s == nullptr) {
				code += (gp->right == p) ? 'r' : 'l';
				code += (p->right == c) ? 'r' : 'l';
				rotate_op(code, gp);
			}
		}

		if (root->color == RED) {
			paint_node_toggle(root);
		}

	}

	template <typename T> 
	void RBTree<T>::rotate_op( const std::string& op_code, RBNode<T>* target_node, bool update_obj, RBNode<T>* curr, RBNode<T>* prev) {
		if (!curr) {
			curr = root;
		}  

		if (target_node->value < curr->value)
			return rotate_op(op_code, target_node, update_obj, curr->left, curr);

		if (target_node->value > curr->value)
			return rotate_op(op_code, target_node, update_obj ,curr->right, curr);

		if (target_node->value == curr->value) {
			
			if (op_code == "rl") {
				if (update_obj) {
					
					paint_node(curr, RED) ; //  left
					paint_node(curr->right->left, BLACK); // middle 
					paint_node(curr->right, RED); 
				
				}
				rotate_right(curr->right, curr->right->left, curr);
				rotate_left(curr, curr->right, prev);
			}
			
			if (op_code == "lr") {
				if (update_obj) {

					paint_node(curr, RED);
					paint_node(curr->left->right, BLACK);
					paint_node(curr->left, RED);

				}
				rotate_left(curr->left, curr->left->right, curr);
				rotate_right(curr, curr->left, prev);
			}

			if (op_code == "ll") {       
				if (update_obj) {
					
					paint_node(curr, RED);
					paint_node(curr->left, BLACK);
					paint_node(curr->left->left, RED);

				}
				rotate_right(curr, curr->left, prev);
			}
			
			if (op_code == "rr") {
				if (update_obj) {

					curr->color = RED; 
					curr->right->color = BLACK; 
					curr->right->right->color = RED;
				
					paint_node(curr, RED);
					paint_node(curr->right, BLACK);
					paint_node(curr->right->right, RED);

				}
				rotate_left(curr, curr->right, prev);
			}
		}
	}

	template <typename T>
	void RBTree<T>::rotate_right(RBNode<T> *p, RBNode<T> *c, RBNode<T>* gp) {
		RBNode<T> * c_rc = c->right;

		if (gp) {
			if (gp->right == p) {
				gp->right = c;
			} 
			else {
				gp->left = c;
			}
		} else {
			root = c;
		}

		c->right = p;
		p->left = c_rc;
	}

	template <typename T>
	void RBTree<T>::rotate_left(RBNode<T>* p, RBNode<T>* c, RBNode<T>* gp) {
		RBNode<T>* c_lc = c->left;

		if (gp) {
			if (gp->right == p) {
				gp->right = c;
			}
			else {
				gp->left = c;
			}
		}
		else {
			root = c;
		}
		c->left = p;
		p->right = c_lc; 
	}
	
	template <typename T> 
	void RBTree<T>::remove(const T& value, RBNode<T>* node, RBNode<T> *prev) {
		if (!node)
			node = root; 

		if (value == node->value) 
			remove_op(node, prev);
		
		else if (value > node->value)
			return remove(value, node->right, node);

		else if (value < node->value)
			return remove(value, node->left, node);
	}

	template <typename T>
	void RBTree<T> :: remove_op(RBNode<T>* node, RBNode<T>* parent, const bool &sticky_node) {
		std::array<RBNode<T>*, 2>  successor_node = {};
		std::string code; 

		code += (node->color == RED) ? 'r' : 'b';

		if (!!node->right && !!node->left) { // full node

			successor_node = successor(node);
			remove_op(successor_node[0], successor_node[1], true);
			connect_parent_of_target_to_element(node, successor_node[0], parent);
			successor_node[0]->left = node->left;
			successor_node[0]->right = node->right;
			
			if (node == root) {
				root = successor_node[0];
				paint_node(root, BLACK);
			}

		} else if ((!!node->left || !!node->right) == NULL) {  // empty node 

			code += 'b';
			connect_parent_of_target_to_element(node, nullptr, parent);
			remove_op(code, nullptr, parent);

		} else if (!!node->left) { // one child

			code += (node->left->color == RED) ? 'r' : 'b';
			connect_parent_of_target_to_element(node, node->left, parent);
			remove_op(code, node->left, parent);

		} else if (node->right) { // one child

			code += (node->right->color == RED) ? 'r' : 'b';
			connect_parent_of_target_to_element(node, node->right, parent);
			remove_op(code, node->right, parent);

		}   

		if (!sticky_node) {
			delete node;
		}

	}

	template <typename T>
	void RBTree<T>::remove_op(const std::string &code, RBNode<T>* c, RBNode<T>* p) {
		RBNode<T>* s = nullptr;

		if (code.length() != 2) return;

		s = getSibling(p, c);

		// deleted node and replacement node color's are compliments 
		if (code == "br" || code == "rb") {
			paint_node(c, BLACK);
		}

		// deleted node and replacement node BLACK (double black or imbalanced tree)
		else if (code == "bb") {
			if (!!s) {
				if (s->color == RED) {
					red_sibling_rotate_op(p, s);
				}
				else if (s->color == BLACK) {
					black_sibling_rotate_op(p, s);
				}
			}
		}
	}

	template <typename T>
	RBNode<T>* RBTree<T>::getSibling(RBNode<T>* parent, RBNode<T>* child) {
		if (!parent)
			return nullptr;

		if (parent->left == child)
			return parent->right;
		if (parent->right == child)
			return parent->left;
	}

	template <typename T>
	void RBTree<T> :: red_sibling_rotate_op(RBNode<T>* p, RBNode<T>* s) {
		// toggle color of parent and sibling 
		paint_node_toggle(s);
		paint_node_toggle(p);

		if (p->right == s) {
			rotate_op("rr", p, false); // promote sibling 
			black_sibling_rotate_op(p, p->right); // black sibling trasnlation 
		}
		if (p->left == s) {
			rotate_op("ll", p, false);
			black_sibling_rotate_op(p, p->left);
		}
	}

	template <typename T>
	void RBTree<T> :: black_sibling_rotate_op(RBNode<T>* p, RBNode<T>* s) {
		RBNode<T> *median = s;
		std::string rotate_code;

		if (sibling_has_red_children(s)) {

			rotate_code += (p->left == s) ? 'l' : 'r';
			if (rotate_code == "l") {
				rotate_code += (s->left) ? 'l' : 'r';
			} else if (rotate_code == "r") {
				rotate_code += (s->right) ? 'r' : 'l';
			}

			if (rotate_code[0] == rotate_code[1]) {
				median = s;
			} else {
				if (rotate_code == "lr") {
					median = p->left->right;
					paint_node_toggle(p->left->right);
					paint_node_toggle(p->left);
				}
				if (rotate_code == "rl") {
					median = p->right->left;
					paint_node_toggle(p->right->left);
					paint_node_toggle(p->right);
				}
			}

			rotate_op(rotate_code, p, false);
			
			if (median->left->color == RED && median->right->color == RED) { 
				paint_node(median->left, BLACK);
				paint_node(median->right, BLACK);
				paint_node(median, RED);
			} else if (median->left->color != median->right->color) { 
				paint_node(median->left, BLACK);
				paint_node(median->right, BLACK);
			}

		} else if (!!s) {
			
			if (p->color == RED) { 
				paint_node_toggle(p);
			}

			if (s->color == BLACK && p->color == BLACK ) {
				paint_node_toggle(s);
			} 

		}

	}
	


	template <typename T> 
	void RBTree<T>::paint_node_toggle(RBNode<T>* node) {
		if (node)
			node->color = (node->color == BLACK) ? RED : BLACK;
	}

	template <typename T>
	void RBTree<T>::paint_node(RBNode<T>* node, const Color &color) {
		if (node)
			node->color = color;
	}

	template <typename T> 
	bool RBTree<T>::sibling_has_red_children(RBNode<T>* s) {
		if (!!s) {
			if (!!s->left) {
				if (s->left->color == RED) return true;
			}
		
			if (!!s->right) {
				if (s->right->color == RED) return true;
			}
		}
		return false;
	}

	template <typename T>
	std::array<RBNode<T>*,2> RBTree<T>::successor(RBNode<T>* node) {
		RBNode<T>* prev = node;
		for (node = node->right; node->left; node = node->left) { 
			prev = node;
		} 
		return { node, prev };
	}

	template <typename T>
	void RBTree<T>::connect_parent_of_target_to_element(RBNode<T>* target, RBNode<T>* element, RBNode<T>* parent) {
		if (parent) {
			if (parent->left == target)
				parent->left = element;
			if (parent->right == target)
				parent->right = element;
		}
	}


	template <typename T>
	void RBTree<T>::hasEqualBlackNodePaths_helper(std::vector<unsigned>& sumList, RBNode<T>* node, unsigned sum, RBNode<T>* prev) {
		
		if (!!node == 0 && !!prev == 0 )
			node = root; 
		if (!!node == NULL) {
			sumList.push_back(sum + 1);
			return;
		}
		sum += +(node->color == BLACK);
		if (node)
			hasEqualBlackNodePaths_helper(sumList, node->left, sum, node);

		if (node)
			hasEqualBlackNodePaths_helper(sumList, node->right, sum, node);
	}


	template <typename T>
	bool RBTree<T>::hasEqualBlackNodePaths() {
		std::vector <unsigned> collection;   
		hasEqualBlackNodePaths_helper(collection);

		for (auto totalSum : collection) {
			if (totalSum != collection[0])
				return false;
		}
		 return true;
	}

	template class RBTree <signed>;
	template class RBTree <unsigned>;

	template <typename T>
	void SplayTree<T>::add(const T& value, SplayNode <T>* node, std::string && sequence) {
		
		if (!root) {
			root = splay_node(value);
		} else {
			
			if (!node) {
				node = root;
			}

			if (value == node->value) {
				node->count++;
			} else if (value < node->value) {
				if (!!node->left) {
					return add(value, node->left, sequence + "LL");
				} else {
					node->left = splay_node(value);
					sequence += "LL";
				}
			} else if (value > node->value) {
				if (!!node->right) {
					return add(value, node->right, sequence + "RR");
				} else {
					node->right = splay_node(value);
					sequence += "RR";
				}
			}
			seq_parser(sequence);
			splay(sequence , value);
		}

	}
	template <typename T> 
	T SplayTree<T>:: get_root_value() {
		return root->value;
	}

	template <typename T>
	void SplayTree<T>::rotate_left(SplayNode<T>* p, SplayNode<T>* gp, SplayNode<T>* c) {
		SplayNode<T>* dangling_node = !!c ? c->left : nullptr;

		if (!gp) {
			root = c;
		} else {
			connect_parent_of_target_to_element( p, c , gp);
		}
		c->left = p;
		p->right = dangling_node;
	}

	template <typename T>
	void SplayTree<T>::rotate_right(SplayNode<T>* p, SplayNode<T>* gp, SplayNode<T>* c) {
		SplayNode<T>* dangling_node = !!c ? c->right : nullptr ;

		if (!gp) {
			root = c;
		} else {
			connect_parent_of_target_to_element(p, c, gp);
		}
		c->right = p;
		p->left = dangling_node;
		
	}

	template <typename T>
	void SplayTree<T>::connect_parent_of_target_to_element(SplayNode<T>* target, SplayNode<T>* element, SplayNode<T>* parent) {
		if (parent) {
			if (parent->left == target)
				parent->left = element;
			if (parent->right == target)
				parent->right = element;
		}
	}

	template <typename T>
	void SplayTree<T>::splay(std::string sequence, const T& target_value) {

		while (!sequence.empty()) {
			rotate_op(sequence.substr(0, 2));
			sequence = sequence.substr(2);
		}
		
		if (target_value != root->value) {
			contains(target_value);
		}
	}

	template <typename T>
	void SplayTree<T>::rotate_op(std::string code) {

			if (code == "LR") {
				rotate_left(root->left, root, root->left->right);
				rotate_right(root, nullptr, root->left);
			}

			if (code == "RL") {
				rotate_right(root->right, root, root->right->left);
				rotate_left(root, nullptr, root->right);
			}

			if (code == "RR") {
				rotate_left(root, nullptr, root->right);
			}

			if (code == "LL") {
				rotate_right(root, nullptr, root->left);
			}

	}

	template <typename T>
	void SplayTree<T>::seq_parser(std::string& seq) {
		std::string tail_seq;

		if (seq.length() >= 4) {
			tail_seq = seq.substr(seq.length() - 4, seq.length());
			if (tail_seq == "LLRR") {
				seq.replace(seq.length() - 4, seq.length(), "LR");
			} else if (tail_seq == "RRLL") {
				seq.replace(seq.length() - 4, seq.length(), "RL");
			}
		}
	}

	template <typename T> 
	SplayNode<T>* SplayTree<T>::predecessor(SplayNode<T>* node) {
		
		if (!node->left) return nullptr;
		
		for (node = node->left; node->right; node = node->right) {}
		
		return node; 
	
	}

	template <typename T>
	bool SplayTree<T>::remove(const T& value) {
		SplayNode<T> *left, *right, *predecessor_node;

		if (contains(value)) {
			left = root->left;
			right = root->right;
			delete root; 
			
			if (!left) {
				root = right;
			} else if (!right) {
				root = left;
			} else {
				predecessor_node = predecessor(root);
				predecessor_node->right = right;
				root = left;
			}
			return true;
		}

		return false;
	}

	template <typename T>
	bool SplayTree<T>::contains(const T& value, SplayNode<T>* node, std::string && sequence) {

		if (!node) {
			node = root; 
		}
		
		seq_parser(sequence);

		if (value < node->value && !!node->left) {
			return contains(value, node->left, sequence + "LL" );
		}

		if (value > node->value && !!node->right) {
			return contains(value, node->right, sequence + "RR");
		}

		splay(sequence, node->value);
		return  (value == node->value);
	}

	template <typename T>
	void SplayTree<T>::show(SplayNode<T> *node, unsigned &&depth ) {
		if (!node)
			node = root; 
		
		printf("VALUE: %d\tHEIGHT: %d\n", node->value, depth);

		if (node->left)
			show(node->left, depth + 1);
		if (node->right)
			show(node->right, depth + 1);
	}

	template class SplayTree <unsigned>;
	template class SplayTree <signed>;

}