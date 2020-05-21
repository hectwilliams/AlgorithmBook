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

#ifndef CHAPTER16_H
#define CHAPTER16_H

namespace chapter16 {



	struct nodeTrie {
		int count;
		std::string val;
		std::vector<nodeTrie *> children;
	};

	nodeTrie* TrieNode(std::string s);

	template <class T>
	void static trimChildren(T* root, int& counter) {
		for (auto node : root->children) {
			trimChildren(node, counter);
		}

		if (counter) {
			counter -= root->count;
		}
		root->children.clear();
		delete root;
	}

	class Trie {
		
	protected:
		nodeTrie* root;
		int node_count;

	public:	
		Trie() : root{ TrieNode("") }, node_count{1}
		{}

		~Trie() {
			trimChildren<nodeTrie>(root, node_count);
		}
		
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

		~TrieMap () {
			trimChildren<TrieMapNode>(root, count);
		}
		std::string Insert(const std::string &key, const std::string &value = "", const int& index = 0, std::string buffer = "", const int& matching_char_count = 0, TrieMapNode* node = nullptr);
		std::string Contains(const std::string& key, int index = 0, TrieMapNode* node = nullptr);
		bool Remove(const std::string& key, const int& index = 0, TrieMapNode* node = nullptr);
		int Size();
		std::string Next(const std::string& key,  int index = 0 , std::string buffer = "", TrieMapNode *node = nullptr);
		std::string First(std::string buffer = "",  TrieMapNode* node = nullptr);
		std::string Last(std::string buffer = "", TrieMapNode* node = nullptr);

	};

}

#endif