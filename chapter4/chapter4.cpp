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
#include "chapter4.h"

extern int errno;



namespace chapter4
{
	char* remove_blanks(char* msg) 
	{
		const char *delim = " ";
		char* next_token;
		const char* ptr;
		static char concat_buffer[5000] = "";

		ptr = strtok_s(msg, delim, &next_token); // point to first subset  
		while (ptr) {
			strcat_s(concat_buffer, sizeof(concat_buffer), ptr);
			ptr = strtok_s(NULL, delim, &next_token);
		}
		return concat_buffer;
	}

	std::string get_digits(std::string digits)
	{
		std::string result = "";
		for (auto c : digits) {
			if (std::isdigit(c))
				result += c;
		}
		return result;
	}

	std::string acronyms(std::string str) 
	{
		std::string result;
		bool rd_en = true;
		for (int i = 0; i < str.size(); i++) {
			if (std::isspace(str[i])) {
				rd_en = true;
			} else if (rd_en && str[i]) {
				result += str[i];
				rd_en = false;
			}
		}
		return result;
	}

	unsigned count_non_spaces(std::string str)
	{
		unsigned count = 0;
		for (int i = 0; i < str.size(); i++) {
			count += +(std::isspace(str[i]));
		}
		return count; 
	}

	std::string remove_shorter_strings(std::string str, unsigned n)
	{

		std::string result;
		std::string buffer = "";

		for (int i = 0; i < str.size(); i++) {
			if (std::isspace(str[i])) {
				result += buffer + (buffer.size() ? " " : "");
				buffer = "";
			} else {
				buffer += str[i];
			}
		}
		
		if (!buffer.empty()) {
			result += buffer;
		}

		return result;
	}

	std::string reverse(std::string str)
	{
		for (int i = 0; i < std::floor(str.size() / 2); i++) {
			std::swap(str[i], str[ str.size() - 1 - i]);
		}
		return str;
	}

	void remove_even_lengths(std::vector<std::string> arr)
	{
		unsigned index = 0;
		while (index < arr.size()) {
			if (arr[index].size() % 2 == 0) {
				arr.erase(arr.begin() + index);
			} else {
				index++;
			}
		}
	}

	unsigned roman_numeral_to_integer(std::string arr)
	{
		unsigned prev = 0, curr = 0; 
		unsigned result = 0; 
		
		for (int i = 0; i < arr.size(); i++ ) {
			if (std::tolower(arr[i]) == 'i') 
				curr = 1;
			if (std::tolower(arr[i]) == 'v') 
				curr = 5;
			if (std::tolower(arr[i]) == 'x') 
				curr = 10;
			if (std::tolower(arr[i]) == 'l') 
				curr = 50;
			if (std::tolower(arr[i]) == 'c') 
				curr = 100;
			if (std::tolower(arr[i]) == 'd') 
				curr = 500;
			if (std::tolower(arr[i]) == 'm') 
				curr = 1000;

			if (!!i && (prev < curr))
				result -= (2 * prev);

			result += curr;
			prev = curr;
		}

		return result;
	}

	std::string integer_to_roman_numeral (unsigned number)
	{
		std::string result; 

		while (number > 0) {
			if (number >= 1 && number < 5) {
				if (number + 1 >= 5) {
					result += "IV";
					number = number + 1 - 5 ;
				} 
				else {
					result += 'I';
					number -= 1;
				}
			} 
			
			else if (number >= 5 && number < 10) {
				if (number + 1 >= 10) {
					result += "IX";
					number = number + 1 - 10;
				} 
				else {
					result += 'V';
					number -= 5;
				}
			}
			
			else if (number >= 10 && number < 50) {
				if (number + 10 >= 50) {
					result += "XL";
					number = number + 10 - 50 ;
				} 
				else {
					result += 'X';
					number -= 10;
				}
			}
			
			else if (number >= 50 && number < 100) {
				if (number + 10 >= 100) {
					result += "XC";
					number = number + 10 - 100;
				} 
				else {
					result += 'L';
					number -= 50;
				}
			}
			
			else if (number >= 100 && number < 500) {
				if (number + 10 >= 500) {
					result += "XD";
					number = number + 10 - 500;
				}
				else if (number + 100 >= 500) {
					result += "CD";
					number = number + 100 - 500;
				} 
				else {
					result += 'C';
					number -= 100;
				}
			}
			
			else if (number >= 500 && number < 1000) {

				if (number + 10 >= 1000) {
					result += "XM";
					number = number + 10 - 1000;
				}
				else if (number + 100 >= 1000) {
					result += "CM";
					number = number + 100 - 1000;
				} 
				else {
					result += 'D';
					number -= 500;
				}
			}
			
			else if (number >= 1000) {
				result += 'M';
				number -= 1000;
			}

		}
		
		return result; 
	}

	bool parens_valid(std::string str)
	{
		char c;
		std::deque<char> dqueue;
		std::map <const char, const char> map = { {')',  '('} };
		std::string headers = "(";

		for (int i = 0; i < str.size(); i++) {
			c = str[i];
			if (headers.find(c) != std::string::npos) {  /* open paren push to array */
				dqueue.push_back(c);
			}  
			if (map.find(c) != map.end()) {    /* close paren found  */
				if (dqueue.empty())
					return false;
				if (dqueue.front() != map.at(c))
					return false; 
				dqueue.pop_front();
			}

		}

		return dqueue.empty();
	}


	bool braces_valid(std::string str)
	{
		char c;
		std::deque<char> dqueue;
		std::map <const char, const char> map = { 
			{')',  '('},
			{'}',  '{'},
			{']',  '['}
		};
		std::string headers = "([{";

		for (int i = 0; i < str.size(); i++) {
			c = str[i];
			if (headers.find(c) != std::string::npos) { /* open brace push to array */
				dqueue.push_back(c);
			}
			if (map.find(c) != map.end()) {  /* close brace found  */
				if (dqueue.empty())
					return false;
				if (dqueue.front() != map.at(c))
					return false;
				dqueue.pop_front();
			}

		}

		return dqueue.empty();
	}

	bool is_palindrome_strict(std::string str)
	{
		for (int i = 0; i < std::floor(str.size()/2); i++) {
	
			if (str[i] != str[str.size() - 1 - i])
				return false;
		}
		return true; 
	}

	bool is_palindrome_not_strict(std::string str, std::string &data)
	{
		unsigned index_a = 0, index_b = str.size() - 1;
		std::string a, b;

		if (str.empty())
			return false;

		data.clear();
		while ((index_a != index_b) && (index_b > index_a)) {
			if (std::isspace(str[index_a])) {
				index_a++;
			} else if (std::isspace(str[index_b])) {
				index_b--;
			} else if (str[index_a] != str[index_b]) {
				return false;
			} else {
				a += str[index_a];
				b += str[index_b];
				index_a++;
				index_b--;
			}
		}

		if (index_a == index_b) {
			a += str[index_a];
			a += b;
			data += a;
		}
		return true;

	}

	std::string longest_palindrome_strict(std::string str)
	{
		std::string curr_palindrome, test_string;
		for (int start = 0; start < str.size(); start++) {
			for (int end = str.size(); end-- ; ) {
				test_string = str.substr(start, end - 1);
				if (is_palindrome_strict(test_string) && test_string.size() > curr_palindrome.size()) {
					curr_palindrome = test_string;
				}
			}
		}
		return curr_palindrome;
	}

	std::string longest_palindrome_not_strict(std::string str)
	{
		std::string curr_palindrome, test_string, buffer, result;
		for (int start = 0; start < str.size(); start++) {
			for (int end = str.size(); end--; ) {
				test_string = str.substr(start, end + 1);
				if (is_palindrome_not_strict(test_string, buffer)) {
					if (buffer.size() > result.size())
						result = buffer;
				}
			}
		}
		return result;
	}

	bool is_alphabetical(std::string str)
	{
		for (int i = 0; i < str.size() - 1; i++) {
			std::cout << static_cast<int>(str[i]) << std::endl;
			if (static_cast<int>(str[i]) > static_cast<int>(str[i + 1])) {
				return false;
			}
		}
		return true;
	}

	std::string d_gets_jiggy(std::string name) 
	{
		char c1 = name[0];
		name = name.substr(1);
		name[0] = std::toupper(name[0]);
		return name + " To The " + c1 + '!';
	}

	std::string common_suffix(std::vector<std::string> arr)
	{
		unsigned word_length = 0, curr_index_word = 0;
		unsigned index = 0;
		std::string result;
		char c = '\0', curr_c;


		while (result.length() == index) {
			for (int i = 0; i < arr.size(); i++) {
				word_length = arr[i].size();
				curr_index_word = arr[i].size() - 1 - index;
				curr_c = arr[i][curr_index_word];
				if (index < word_length) {
					if (c == '\0') {
						c = curr_c;
					} else if (c != curr_c ) {
						return "";
					}
				} else {
					index++;
					break;
				}
			}
			index++;
			result = c + result;
			c = '\0';
		}

		return result;

	}

	std::string book_index(std::vector<unsigned> arr)
	{
		unsigned edge_index_s = 0;
		std::string result;

		for (int i = 1; i < arr.size(); i++) {
			if (arr[i] != arr[i - 1] + 1) {				
				if (edge_index_s == i - 1) {
					result += std::to_string(arr[edge_index_s]) + ", ";
				} else {
					result += std::to_string(arr[edge_index_s]) + "-" + std::to_string(arr[i - 1 ]) + ", ";
				}
				edge_index_s = i;
			}
		}

		if (edge_index_s == arr.size() - 1)
			result += std::to_string(arr[edge_index_s]);
		else
			result += std::to_string(arr[edge_index_s]) + "," + std::to_string(arr[arr.size() - 1]);

		return result;
	}

	std::string drop_the_mike(std::string str)
	{
		unsigned ptr_a = 0, ptr_b = str.length() - 1;
		bool first_char = 1;

		while (std::isspace(str[ptr_a])) {
			++ptr_a;
		}

		while (std::isspace(str[ptr_b])) {
			--ptr_b;
		}

		for (int i = ptr_a; i <= ptr_b; i++) {
			if (first_char) {
				str[i] = std::toupper(str[i]);
				first_char = 0;
			}
			
			if (std::isspace(str[i]) && !std::isspace(str[i + 1])) {
				first_char = 1;
			}
		}

		return str.substr(ptr_a, ptr_b +1);

	}

}