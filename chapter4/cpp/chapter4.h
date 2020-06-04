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

#ifndef CHAPTER4_H
#define CHAPTER4_H

namespace chapter4
{
	char * remove_blanks(char* msg);
	std::string get_digits(std::string digits);
	std::string acronyms(std::string str);
	unsigned count_non_spaces(std::string str);
	std::string remove_shorter_strings(std::string str, unsigned n);
	std::string reverse(std::string str);
	void remove_even_lengths(std::vector< std::string> arr);
	std::string integer_to_roman_numeral(unsigned number);
	unsigned roman_numeral_to_integer(std::string arr);
	bool parens_valid(std::string str);
	bool braces_valid(std::string str);
	bool is_palindrome_strict(std::string str);
	bool is_palindrome_not_strict(std::string str, std::string& data);
	std::string longest_palindrome_strict(std::string str);
	std::string longest_palindrome_not_strict(std::string str);
	bool is_alphabetical(std::string str);
	std::string d_gets_jiggy(std::string name);
	std::string common_suffix(std::vector<std::string> arr);
	std::string book_index(std::vector<unsigned> arr);
	std::string drop_the_mike(std::string str);
}


#endif