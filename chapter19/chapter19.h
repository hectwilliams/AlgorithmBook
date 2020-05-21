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

#ifndef CHAPTER19_H
#define CHAPTER19_H


namespace chapter19 {
	using avl_funct_pts = bool (*)(); // or typedef bool (*avl_funct_pts)();

	template <typename T>
	struct AVLNode {
		T val;
		signed balance;
		AVLNode* left;
		AVLNode* right;
		unsigned count;

		bool isBalanced () {
			return [this]()->bool  { 
				return std::abs(this->balance) < 2;
			}();
		}

		unsigned height() {
			return [ runner = this, count = 0]() mutable ->unsigned {
				
				for (count; runner; count++) {

					if (runner->left == nullptr && runner->right == nullptr)
							break;
					
					else if (runner->balance == 0 && runner->right)
						runner = runner->right;

					else if (runner->balance == 0 && runner->left)
						runner = runner->left;

					else if (runner->balance > 0)
						runner = runner->left;

					else if (runner->balance < 0)
						runner = runner->right;
				}
			
				return count;
			}();
		}
	};
	
	template <class T>
	class AVLTree {
	
	private:
		AVLNode<T> *head;
		unsigned h{};
		std::vector<std::vector<std::string>*> *collection;
		
		AVLNode<T>* avl_node(T value) {
			return new AVLNode<T> { value, 0, nullptr, nullptr, 1};
		};

		void remove_op(AVLNode<T>* node = nullptr, AVLNode<T> * parent = nullptr, AVLNode<T>* root_node = nullptr);
		void connect_parent_of_target_to_element(AVLNode<T>* target= nullptr, AVLNode<T>* subtree= nullptr, AVLNode<T>* parent = nullptr);
		std::array < AVLNode<T> *, 3> successor(AVLNode<T>* node = nullptr);
		void balance_path_decrement(AVLNode<T>* target, AVLNode<T>* node = nullptr);


		bool trace_left(const T value, const bool &is_mutable = true,  AVLNode<T>* node = nullptr);
		bool trace_right(const T value, const bool &is_mutable = true, AVLNode<T>* node = nullptr);
		bool insert_right(const T value, AVLNode<T>* node = nullptr);
		bool insert_left(const T value, AVLNode<T>* node = nullptr);
		bool insert_equal(const T value, AVLNode<T>* node = nullptr);

		void rotate_left_rot(AVLNode<T>* p, AVLNode<T>* gp = nullptr); 
		void rotate_right_rot(AVLNode<T>* p, AVLNode<T>* gp = nullptr);

		void updateBalance(AVLNode<T>* p);
		void update_balance_increment(AVLNode<T>* node = nullptr, AVLNode<T>* leaf = nullptr);
		void update_balance_decrement(AVLNode<T>* node = nullptr, AVLNode<T>* leaf = nullptr);

		void rebalance_tree_rotate( AVLNode<T>* p = nullptr);
		std::string rotate_code(AVLNode<T>* node);
		void rotate (AVLNode<T>* node = nullptr);

	public:
		
		signed height();
		signed isBalanced();
		AVLNode<T>* get_root();
		T sum_node(AVLNode<T> *node = nullptr);

		void balance_add_review(AVLNode<T>* start, AVLNode<T>* end, AVLNode<T>* parent_of_end, bool rotate_en = false);
		
		void add(T value, AVLNode<T>* node = nullptr, AVLNode<T>* parent = nullptr, AVLNode<T>* start = nullptr);
		bool remove(T value, AVLNode<T>* node = nullptr, AVLNode<T>* parent = nullptr, AVLNode<T>* start = nullptr);
		
		void printTree(AVLNode<T>* node = nullptr, const unsigned& depth = 0, const unsigned& index = 0);

		void rotate_left(AVLNode<T>* target_node, AVLNode<T>* curr = nullptr, AVLNode<T>* prev = nullptr);  
		void rotate_right(AVLNode<T>* target_node, AVLNode<T>* curr = nullptr, AVLNode<T>* prev = nullptr);

		void balance_add(T value, AVLNode<T>* node = nullptr, AVLNode<T>* parent = nullptr, AVLNode<T>* start = nullptr);
		bool balance_remove(T value, AVLNode<T>* node = nullptr, AVLNode<T>* parent = nullptr, AVLNode<T>* start = nullptr);
		void rebalance_target(AVLNode<T>* target = nullptr, AVLNode<T>* runner = nullptr);


		AVLTree() : head{ nullptr }, collection{new std::vector<std::vector<std::string>*> } {
			collection->resize(100);
			for (int i = 0; i < 100; i++) {
				collection->at(i) = new std::vector<std::string>{};
			}
		};

		~AVLTree () {
			std::deque<AVLNode<T>*> queue;
			AVLNode<T>* node;

			for (int i = 10; i--; ) {
				delete collection->at(i);
			}
			delete collection;

			while (queue.size()) {
			  node = queue.front();
			  queue.erase(queue.begin());

			  if (node->left)
				  queue.push_back(node->left);
			  if (node->right)
				  queue.push_back(node->right);

			  delete node;
			}
			head = nullptr;
			collection = nullptr;
		};


	};

	enum Color { BLACK, RED };

	template <typename T>
	struct RBNode {
		T value;
		unsigned count;
		RBNode<T>* left;
		RBNode<T>* right;
		Color color;
	};

	template <class T>
	class RBTree {
	
	private:
		RBNode<T>* rb_node(T value) {
			return new RBNode<T>{ value, 1, nullptr, nullptr, Color::RED };
		}
		void rotate_op( const std::string& op_code, RBNode<T>* target_node, bool update_obj = true, RBNode<T>* curr = nullptr, RBNode<T>* prev = nullptr);
		void rotate_right (RBNode<T>* p, RBNode<T>* c,  RBNode<T>* gp );
		void rotate_left (RBNode<T>* p , RBNode<T>* c , RBNode<T>* gp);
		void hasEqualBlackNodePaths_helper (std::vector<unsigned> &sumList, RBNode<T>* node = nullptr, unsigned sum = 0, RBNode<T>* prev = nullptr);
		bool tree_validate (const T &value, RBNode<T> *runner = nullptr, RBNode<T> *runner_prev = nullptr, unsigned rr_count = 0);
		void rr_op (RBNode<T>* p, RBNode<T>* gp, RBNode<T>* c); 
		std::array<RBNode<T>*, 2> successor (RBNode<T>* node);
		void remove_op(RBNode<T>* node = nullptr, RBNode<T>* parent = nullptr, const bool &sticky_node = false);
		void remove_op( const std::string &code, RBNode<T> *c, RBNode<T> *p);
		void connect_parent_of_target_to_element(RBNode<T>* target, RBNode<T>* element, RBNode<T>* parent);
		RBNode<T>* getSibling (RBNode<T> *parent, RBNode<T> *child);  //^
		bool sibling_has_red_children(RBNode<T>* s);  //^
		void paint_node(RBNode<T>* node, const Color & color);  //^
		void paint_node_toggle(RBNode<T>* node);
		void red_sibling_rotate_op(RBNode<T>* p, RBNode<T>* s);
		void black_sibling_rotate_op(RBNode<T>* p, RBNode<T>* s);

	public:
		RBNode<T>* root;
		void add (T value, RBNode<T>* node = nullptr, RBNode<T>* prev = nullptr);
		bool hasEqualBlackNodePaths ();
		void getValues  (RBNode<T>* node = nullptr);
		void remove(const T& value, RBNode<T>* node = nullptr, RBNode<T>* prev = nullptr);
		bool contains(const T& value, RBNode<T>* node = nullptr);
		RBTree() : root{nullptr}
		{}
	};

	template <typename T>
	struct SplayNode {
		T value;
		unsigned count;
		SplayNode<T>* left;
		SplayNode<T>* right;
	}; 

	template <class T>
	class SplayTree {
	private:
		SplayNode<T> *root;
		SplayNode<T>* splay_node(const T& value) {
			return new SplayNode<T>{ value, 1, nullptr, nullptr};
		} 

		void connect_parent_of_target_to_element(SplayNode<T>* target, SplayNode<T>* element, SplayNode<T>* parent);
		void rotate_op(std::string code);
		void splay(std::string sequence, const T& target_value);
		void rotate_left (SplayNode<T>* p, SplayNode<T>* gp, SplayNode<T>* c);
		void rotate_right (SplayNode<T>* p, SplayNode<T>* gp, SplayNode<T>* c);
		void seq_parser(std::string& seq);
		SplayNode<T>* predecessor(SplayNode<T>* node);

	public:
		void show(SplayNode<T> *node = nullptr, unsigned && depth = 0);
		void add(const T& value, SplayNode <T>* node = nullptr, std::string && sequence = "");
		bool contains(const T& value, SplayNode<T> *node = nullptr, std::string && sequence = "");
		bool remove(const T& value);
		T get_root_value();
		SplayTree() : root {nullptr}
		{}

		~SplayTree() 
		{
			SplayNode <T>* node = root;
			if (node) {
				std::deque<SplayNode<T>*> dq{root};
				while (dq.size()) {
					if (dq.front()->left) {
						dq.push_back(dq.front()->left);
					}
					if (dq.front()->right) {
						dq.push_back(dq.front()->right);
					}
					delete dq.front();
					dq.pop_front();
				}
			}
		};

	};

}


#endif