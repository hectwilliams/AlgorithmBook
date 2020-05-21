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
#include "chapter16.h"
extern int errno;


namespace chapter16 {

	nodeTrie* TrieNode(std::string s) {
		std::string loc_c;
		return new nodeTrie{ 1, s };
	}


	bool static Insert_helper_valid_str_input(const std::string& s) {
		int code = 0;
		for (auto ch : s) {
			code = static_cast<int>(ch);
			if (!(code >= 32 && code < 128))
				return  false;
		}
		return true;
	}

	bool Trie::Insert(const std::string& string_in, const int& index, bool isNewEntry, nodeTrie* node) {
		try {
			if (!Insert_helper_valid_str_input(string_in))
				throw "error";

			if (node == nullptr)
				node = root;

			if (index == string_in.size())
				return isNewEntry;


			for (auto trie_child_node: node->children) {
				if (trie_child_node->val.back() == string_in[index]) {
					trie_child_node->count++;
					return Insert(string_in, index + 1, isNewEntry, trie_child_node);
				}
			}

			node->children.push_back(TrieNode(string_in.substr(0, index + 1)));				// TODO (insert in order)
			return Insert(string_in, index + 1, true, node->children.back());
		}
		catch (...) {
			return false;
		}

	}

	bool Trie::Contains(const std::string& string_in, const int index, nodeTrie* node) {
	
		if (!node)
			node = root;

		if (index == string_in.size())
			return true;

		if (node->children.size()) {
			for (auto trie_child_node : node->children) {
				if (trie_child_node->val.back() ==  string_in[index])
					return Contains(string_in, index + 1, trie_child_node);
			}
		}

		return false;
	}


	bool Trie::Remove(const std::string& string_in, const int index, nodeTrie* node) {
		bool state = false;
		nodeTrie* trie_child_node = nullptr;

		if (index == string_in.size())
			return true;

		if (!node)
			node = root;

		if (node->children.size()) {
			for (int i = 0; i < node->children.size(); i++) {
				trie_child_node = node->children[i];
				if (trie_child_node->val.back() == string_in[index]) {
					state = Remove(string_in, index + 1, trie_child_node);
					if (state) {
						trimChildren(trie_child_node, this->node_count);
						node->children.erase(node->children.begin() + i);
						return state;
					}
				}
			}
		}
		return false;
	}

	std::string Trie::First( nodeTrie* node) {
		nodeTrie* minNode = nullptr;

		if (!node)
			node = root;

		if (node->children.size()) {
			for (auto trie_child : node->children) {
				if (minNode == nullptr ||  trie_child->val.back() < minNode->val.back())
					minNode = trie_child;
			}
			return First( minNode);
		}

		return node->val;
	}

	std::string Trie::Last(nodeTrie* node) {
		nodeTrie* maxNode = nullptr;

		if (!node)
			node = root;

		if (node->children.size()) {
			for (auto trie_child : node->children) {
				if (maxNode == nullptr || trie_child->val.back() > maxNode->val.back())
					maxNode = trie_child;
			}
			return Last(maxNode);
		}
		return node->val;
	}

	int Trie::Size() {
		return node_count;
	}

	std::string Trie::Next(const std::string & str, int index, nodeTrie * node) {
		if (!node)
			node = root;

		if (index == str.size()) {
			if (!node->children.empty())
				return node->children.front()->val.c_str();
		} else {
			for (auto child : node->children) {
				if (child->val.back() == str[index]) {
					return Next(str, index + 1, child);
				}
			}
		}
		return "";
	}


	static void AutoComplete_Trie_permutation(nodeTrie* node, std::vector<std::string>& array) {
		array.push_back(node->val);
		for (auto child : node->children)
			AutoComplete_Trie_permutation(child, array);
	}

	static void AutoComplete_Trie_getWords(const std::string str, nodeTrie* node, std::vector<std::string>& array, int index = 0) {
		if (index == str.size())
			return AutoComplete_Trie_permutation(node, array);

		for (int i = 0; i < node->children.size(); i++) {
			if (node->children[i]->val.back() == str[index]) {
				return AutoComplete_Trie_getWords(str, node->children[i], array, index + 1);
			}
		}
	}

	void Trie::AutoComplete(nodeTrie* node) { //terminal i/o fun!
		std::string buffer{};
		std::vector <std::string> collection;
		int maxResults = -1;

		if (!node)
			node = root;

		while (true) {
			collection.clear();
			buffer.clear();

			printf("Enter characters and press enter to return list of possible words** \n");
			printf("Enter \"00\" and press enter to exit\n");

			std::getline(std::cin, buffer);

			if (buffer == "00")
				break;

			if (buffer.empty())
				continue;

			while (true) {
				printf("Number of auto completed results to display \nNOTE * \"0\" for complete list: ");
				std::cin >> maxResults;
				std::cin.ignore(INT16_MAX, '\n');
				std::cin.clear();
				if (!std::cin.fail())
					break;
			}

			AutoComplete_Trie_getWords(buffer, root, collection);

			if (maxResults == 0) {
				for (int i = 0; i < collection.size(); i++)
					printf(" [%d]: \t %s \n", i, collection[i].c_str());
			}

			if (maxResults > 0) {
				for (int i = 0; (i < maxResults) && (collection.size() > i); i++)
					printf(" [%d]: \t %s \n", i, collection[i].c_str());
			}

			
		}

	}


	bool TrieMultiSet::Insert(const std::string& string_in, const int& index, nodeTrie* node) {
		nodeTrie* childNode = nullptr;

		if (!node)
			node = root;

		if (index >= string_in.size())
			return true;

		for (int i = 0; i < node->children.size(); i++) {
			childNode = node->children[i];
			if (node->children[i]->val.back() == string_in[index]) {
				++childNode->count;
				return Insert(string_in, index + 1, childNode);
			}
		}

		childNode = TrieNode(string_in.substr(0, index + 1));
		node->children.push_back(childNode);
		return Insert(string_in, index + 1, childNode);
	}



	int TrieMultiSet::Remove(const std::string& string_in, const int& index, nodeTrie* node) {
		nodeTrie *buffer_child_node = nullptr, *child_node = nullptr;
		int cnt = 0;

		if (!node)
			node = root;

		if (string_in.size() == 0)
			return cnt;

		if (string_in.size() == index)
			return node->count;

		for (int i = 0; i < node->children.size(); i++) {
			child_node = node->children[i];
			
			if (child_node->val.back() == string_in[index]) {
				cnt = Remove(string_in, index + 1, child_node);
				
				if (cnt) {
					--child_node->count;
					--this->node_count;
				}

				if (child_node->count == 0) {
					trimChildren<nodeTrie>(child_node, this->node_count);		// delete current node from array and all children or current node element
					node->children.erase(node->children.begin() + i);
				}
				
				return child_node->count;
			}
		}
		return cnt;
	}

	int TrieMultiSet::Contains(const std::string& string_in, const int& index, nodeTrie* node) {

		if (!node)
			node = root; 
		
		if (index >= string_in.size())
			return node->count;

		for (auto child_node : node->children) {
			if (child_node->val.back() == string_in[index]) {
				return Contains(string_in, index + 1, child_node);
			}
		}

		return 0;
	}

	static void AutoComplete_TrieMulti_permutation(nodeTrie* node,  std::map<std::string, int> & mapper) {
		mapper.insert(std::make_pair(node->val, node->count));
		for (auto child : node->children) {
			AutoComplete_TrieMulti_permutation(child, mapper);
		}
	}

	static void AutoComplete_TrieMulti_getWords(const std::string str, nodeTrie* node, std::map<std::string, int>& mapper, int index = 0) {
		if (index == str.size())
			return AutoComplete_TrieMulti_permutation(node, mapper);

		for (int i = 0; i < node->children.size(); i++) {
			if (node->children[i]->val.back() == str[index]) {
				return AutoComplete_TrieMulti_getWords(str, node->children[i], mapper, index + 1);
			}
		}
	}
	
	void TrieMultiSet::AutoComplete() {
		std::tuple<std::string, int> maxWordFreq;
		std::map<std::string, int> mapper;
		std::string buffer;

		while (true) {
			buffer.clear();

			printf("To Exit:  \tEnter \"00\" and press enter\n");
			printf("Enter char(s) and press enter to auto complete dictionary: ");
			
			std::getline(std::cin, buffer);
			
			if (buffer == "00")
				break;
			
			AutoComplete_TrieMulti_getWords(buffer, root, mapper);

			while (!mapper.empty()) {
				maxWordFreq = {"NULL", -1};
				for (auto element : mapper) {
					if (std::get<0>(maxWordFreq) == "NULL" || std::get<1>(maxWordFreq) < element.second) {
						maxWordFreq = { element.first, element.second };
					}
				}
				std::cout << std::get<0>(maxWordFreq) << "\t" << std::get<1>(maxWordFreq) << '\t' << "register" << "\n";
				mapper.erase(std::get<0>(maxWordFreq));
			}
			printf("\n\n");
		}

	}

	std::string TrieMap::Insert(const std::string& key, const std::string& value, const int& index, std::string buffer,  const int& matching_char_count, TrieMapNode* node) {
		std::string str_buffer;

		if (!node)
			node = root; 

		if (matching_char_count == key.size()) {
			str_buffer = node->value;
			node->value = value;
			return str_buffer;
		}

		if (buffer == key) {
			node->value = value;
			return "";
		}

		for (auto child: node->children) {
			if ( child->key.substr(0, index + 1) == buffer + key[index] ) {
				return Insert(key, value, index + 1, buffer + key[index], matching_char_count + 1, child);
			}
		}

		this->count++;
		node->children.push_back(new TrieMapNode{ buffer + key[index], "", 1});
		return Insert(key, value, index + 1, buffer + key[index], matching_char_count, node->children.back());
	}

	std::string TrieMap::Contains(const std::string& key, int index, TrieMapNode* node) {
		if (!node)
			node = root; 

		if (index == key.size())
			return node->value;

		for (auto child : node->children) {
			if (child->key.back() == key[index] )
				return Contains(key, index + 1, child);
		}

		return "";
	}


	bool TrieMap::Remove(const std::string& key, const int& index, TrieMapNode* node) {
		bool state = false;
		TrieMapNode* child = nullptr; 

		if (!node)
			node = root;

		if (index == key.size()) 
			return true;

		for (int i = 0; i < node->children.size(); i++) {
			child = node->children[i];

			if (child->key.back() == key[index]) {
				state =  Remove(key, index + 1, child);
				if (state) {
					--this->count;
					--child->count;
					if (child->count == 0) {
						trimChildren<TrieMapNode>(child, this->count); // remove child's children 
						node->children.erase(node->children.begin() + i ); // erase children array element 
					}
				}

				return state; 
			}
		}
		return false;
	}


	std::string TrieMap::Next (const std::string& key, int index, std::string buffer, TrieMapNode *node) {
		
		if (node == nullptr)
			node = root; 
		
		if (index == key.size()) {
			if (!node->children.empty())
				return node->children.front()->key;
			else
				return "";
		}

		for (auto child : node->children) {
			if (child->key.back() == key[index]) {
				return Next (key, index + 1, buffer + key[index], child);
			}
		}

		return "";
	}


	int TrieMap::Size() {
		return this->count;
	}


	std::string TrieMap::First( std::string buffer, TrieMapNode* node) {
		char min_char = NULL; 
		int index = 0;

		if (node == nullptr)
			node = root; 

		if ( !buffer.empty() && !node->value.empty())
			return buffer;

		if (node->children.size()) {
			for (int i = 0; i < node->children.size(); i++) {
				if (!min_char || node->children[i]->key.back() < min_char) {
					min_char =  node->children[i]->key.back();
					index = i;
				}
			}
			return First( buffer + min_char, node->children[index]);
		}

		return buffer;
	}


	std::string TrieMap::Last(std::string buffer, TrieMapNode* node) {
		char max_char = NULL;
		int index = 0;

		if (node == nullptr)
			node = root;

		if (node->children.size()) {
			for (int i = 0; i < node->children.size(); i++) {
				if (!max_char ||  node->children[i]->key.back() > max_char  ) {
					max_char = node->children[i]->key.back();
					index = i;
				}
			}
			return Last(buffer + max_char, node->children[index]);
		}

		return buffer;
	}
}