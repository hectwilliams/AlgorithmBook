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
#include "chapter10.h"

extern int errno;


namespace chapter10 {

	std::ostream& operator << (std::ostream& out, const std::vector<std::string>& strArray) {
		for (auto str : strArray) {
			out << str << " ";
		}
		return out;
	}

	static void StringToWordArray_helper_handlePunctuation(std::string& s) {
		std::string plist = ",'-.!?";
		bool charPmark, pmarkChar;

		for (int i = 0; i < s.length(); i++) {
			pmarkChar = plist.find(s[i]) != std::string::npos && std::isalpha(s[i + 1]);
			charPmark = plist.find(s[i + 1]) != std::string::npos && std::isalpha(s[i]);

			if (plist.find(s[i]) != std::string::npos && plist.find(s[i + 1]) != std::string::npos)
				continue;

			if (pmarkChar || charPmark) {
				s.insert(s.begin() + i + 1, ' ');
				i++;
			}

		}


	}


	std::vector<std::string> StringToWordArray(std::string s, bool handlePunctuation) {
		std::stringstream streamData;
		std::string stringBuffer;
		std::vector<std::string> result;


		if (handlePunctuation) {
			StringToWordArray_helper_handlePunctuation(s);
		}

		streamData << s;

		while (std::getline(streamData, stringBuffer, ' ')) {
			result.push_back(stringBuffer);
		}
		return result;
	}

	std::string LongestWord(const std::string& s) {
		std::string longestWord{ "" };
		for (auto word : StringToWordArray(s, true))
			if (word.length() > longestWord.length())
				longestWord = word;
		return longestWord;
	}

	static void ReverseWordOrder_findNextWord(int& idx, const int& step, const std::vector<std::string>& collection) {
		const int prev_idx = idx;
		while ((idx >= 0 && idx < collection.size())) {
			if (!isalpha(collection[idx][0]) || prev_idx == idx) {
				idx += step;
				continue;
			}
			break;
		}
	}

	std::string computeMessage(const std::vector<std::string>& array) {
		bool space = false;
		std::string result;

		for (int i = 0; i < array.size(); i++) {
			if (i + 1 < array.size()) {
				space = std::isalpha(array[i + 1][0]);
			}

			result += array[i] + ((space) ? " " : "");
		}
		return result;
	}

	std::string ReverseWordOrder(std::string s) {
		std::vector<std::string> array = StringToWordArray(s, true);
		std::vector< std::tuple< int, std::string >> downArray;
		std::string str_buffer;
		int int_buffer;
		int posDown = array.size() - 1;

		do {
			if (std::isalpha(array[posDown][0]))
				downArray.push_back(std::make_tuple(posDown, array[posDown]));
			ReverseWordOrder_findNextWord(posDown, -1, array);
		} while (posDown >= 0);

		for (auto& ele : array) {

			if (std::isalpha(ele[0])) {
				std::tie(int_buffer, str_buffer) = downArray.front();

				if (std::isupper(ele[0])) {
					str_buffer[0] = std::toupper(str_buffer[0]);
				}
				else {
					for (auto& c : str_buffer) {
						c = std::tolower(c);
					}
				}

				ele = str_buffer;
				downArray.erase(downArray.begin());
			}

		}

		return computeMessage(array);
	}


	static void lowerCaseString(std::string& str) {
		for (auto& c : str)
			c = std::tolower(c);
	}

	std::string UniqueWords(const std::string& message, bool ignorePunctuation) {
		std::vector<std::string> array = StringToWordArray(message, ignorePunctuation);
		std::map<std::string, int> bucket;
		std::vector<std::string> collection;

		for (auto ele : array) {

			if (ignorePunctuation && !std::isalpha(ele[0]))
				continue;
			if (bucket.find(ele) == bucket.end())
				bucket.insert(std::make_pair(ele, 0));
			++bucket.find(ele)->second;
		}

		for (auto pair : bucket) {
			if (pair.second == 1)
				collection.push_back(pair.first);
		}

		return computeMessage(collection);


	}


	std::string RotateString(std::string str, const int& count) {

		std::string temp{};


		for (int i = 0; i < count; i++) {
			temp = str.back();
			str.insert(0, temp);
			str.pop_back();
		}
		return str;
	}

	bool isRotation(std::string  s1, std::string s2) {
		int length = s1.length() - 1;
		std::string c;
		for (int i = 0; i < length; i++) {
			c = s1.back();
			s1.insert(0, c);
			s1.pop_back();

			if (s1 == s2)
				return true;
		}
		return false;
	}


	std::string Censor(std::string s, std::vector<std::string> list) {
		const std::string censorWord = "xxxx";
		int index = 0;

		while (!list.empty()) {
			index = s.find(list.front());
			s = s.substr(0, index) + censorWord + s.substr(index + list.front().length());
			list.erase(list.begin());
		}
		return s;
	}

	static void  BadCharacters_helpter_removeChar(std::string& string, const char c) {
		int index = 0;

		while (index < string.size()) {
			if (string[index] == c) {
				string = string.substr(0, index) + string.substr(index + 1);
				--index;
			}
			else {
				index++;

			}
		}
	}

	std::string BadCharacters(std::string s, const char  c[]) {
		auto* ptr = c;
		std::cout << s << '\n';

		while (*ptr != '\0') {
			BadCharacters_helpter_removeChar(s, *ptr);
			std::cout << s << '\n';
			ptr++;
		}
		return s;
	}


	bool GeneticMarker(std::vector<std::string> collection, std::string marker) {
		int index, count;

		for (auto s : collection) {
			index = 0;
			count = 0;

			if (s.length() != marker.length())
				continue;

			for (int i = 0; i < s.length(); i++) {
				count += +(s[i] == marker[i] || s[i] == '?');
			}

			if (count == s.length() - 1)
				return true;
		}
		return false;
	}


	std::string Dedupe(const std::string s) {
		std::map<char, int> map;
		std::map<char, int>::iterator it;
		std::string result;
		int i = 0;
		for (int k = 0; k < s.length(); k++) {
			it = map.find(s[k]);
			if (it == map.end()) {

				map.insert(std::make_pair(s[k], i));
			}
			else {
				it->second = i;
			}
			i++;
		}

		for (int k = 0; k < s.length(); k++) {
			it = map.find(s[k]);
			if (it != map.end() && it->second == k) {
				result += s[k];
			}
		}
		return result;
	}


	int IndexFirstUniqueLetter(const std::string s) {
		std::map<char, int> map;
		std::map<char, int>::iterator it;
		std::tuple<char, int> buffer;
		int i = 0;
		int ituple;
		char stuple;

		for (auto c : s) {
			it = map.find(c);
			std::tie(stuple, ituple) = buffer;

			if (it == map.end()) {
				map.insert(std::make_pair(c, 1));
				buffer = std::make_tuple(c, i);
			}
			else {
				if (stuple == c)
					buffer = std::make_tuple('\0', -1);
				it->second++;
			}
			i++;
		}

		std::tie(stuple, ituple) = buffer;
		return ituple;
	}

	std::string NumToString(int number) {
		std::string result;
		while (number >= 1) {
			result = char((number % 10) + 48) + result;
			number = number / 10;
		}
		std::cout << result << '\n';
		return result;;
	}

	std::string  NumToString(double fraction) {
		std::string f;
		std::string whole = NumToString((int)fraction);
		fraction = fraction - (static_cast<int>(fraction));
		int digit;

		while (fraction > 0.0) {
			fraction = (fraction * 10);
			digit = std::round(fraction);
			f += static_cast<char>(48 + digit);
			fraction -= digit;
		}

		return whole + '.' + f;
	}

	static std::vector<std::string> NumToText_helper_digitToText(char curr, const int& index, int& depth) {
		static std::vector<std::string> buffer;
		static int prev = -1;
		int tmp = static_cast<int>(curr) - 48;
		std::map<int, std::array<std::string, 2>>::iterator it;

		if (illions.find(depth) != illions.end()) {
			buffer.insert(buffer.begin(), illions.find(depth)->second);
		}


		if (index == 0 && tmp != 0) {
			prev = tmp;
			buffer.insert(buffer.begin(), NumToTextMap.find(tmp)->second[0]);
		}

		if (index == 1) {
			if (tmp == 1 && prev != 0)
				buffer[buffer.size() - 1] = NumToTextMap.find(prev)->second[1];
			if (tmp > 1)
				buffer.insert(buffer.begin(), NumToTextMap.find(tmp)->second[2]);
		}


		if (index == 2 && tmp != 0) {
			buffer.insert(buffer.begin(), NumToTextMap.find(tmp)->second[0] + " hundred");
		}



		return buffer;
	}


	std::string NumToText(int number, int index3, std::string s, int depth, std::vector<std::string> result) {
		std::string buffer;

		if (index3 == -1) {
			s = NumToString(number);
			index3 = 0;
		}

		if (s.empty()) {
			for (auto str : result)
				buffer += str + " ";
			return buffer;
		}

		result = NumToText_helper_digitToText(s.back(), index3, depth);
		return NumToText(number, (index3 + 1) % 3, s.substr(0, s.length() - 1), depth + 1, result);

	}

	bool isPermutation(std::string s1, std::string s2, const char index) {
		int index_s2;

		if (!s2.length())
			return true;

		index_s2 = s2.find(s1[index]);
		if (index_s2 != std::string::npos)
			return isPermutation(s1, s2.substr(0, index_s2) + s2.substr(index_s2 + 1), index + 1);
		else
			return false;
	}

	bool IsPangram(std::string s, std::map<char, int> histo, int count) {
		int code;
		char c;

		if (s.empty()) {
			if (count == 26)
				return true;
			else
				return false;
		}

		c = std::tolower(s.front());
		code = static_cast<int>(c);

		if ((histo.find(c) == histo.end()) && (code >= 97 && code <= 122)) {
			histo.insert(std::make_pair(c, 1));
			count++;
		}

		return IsPangram(s.substr(1), histo, count);
	}

	int factorial(int number) {
		if (number <= 0)
			return 1;
		return number * factorial(number - 1);
	}

	void AllPermutations(std::string s, std::vector<std::string>& collection, std::string buffer, int max) {

		if (buffer.empty())
			max = s.length();
		else if (buffer.length() == max) {
			std::cout << s << " " << buffer << max << "\n";
			collection.push_back(buffer);
			return;
		}

		for (int i = 0; i < s.length(); i++) {
			AllPermutations(s.substr(0, i) + s.substr(i + 1), collection, buffer + s[i], max);
		}
	}


	bool PerfectPangram(std::string s, int count, std::map <char, int> mapper) {
		int code;
		char c;

		if (s.empty())
			return true;

		c = std::tolower(s.front());
		code = static_cast<int>(c);

		if ((code >= 97 && code <= 122)) {
			if (mapper.find(c) == mapper.end()) {
				mapper.insert(std::make_pair(c, 1));
				count++;
			}
			else {
				return false;
			}
		}

		return PerfectPangram(s.substr(1), count + 1, mapper);
	}

	static int bestSingleBuySell_helper_addprices(int& low, int& high, std::vector<std::array<int, 2>>& array) {
		array.push_back({ low, high });
		return -1;
	}

	static int maxProfit_SinglePurchase(std::vector<std::array<int, 2>>& collection) {
		int profit, max = 0;
		for (auto ele : collection) {
			profit = ele[1] - ele[0];
			if (profit > max)
				max = profit;
		}
		return max;

	}

	static int maxProfit_ManyPurchase(std::vector<std::array<int, 2>>& collection) {
		int profit, max = 0;
		for (auto ele : collection) {
			profit = ele[1] - ele[0];
			max += profit;
		}
		return max;
	}

	static void maxProfit_Purchase_TwoTransactions_helper(std::vector<std::array<int, 2>> collection, int& profit, int& max, int depth = 0, int transaction = 2) {
		int buy = 0, sell = 0;

		if (depth == 2) {
			if (profit > max)
				max = profit;
			profit = 0;
			return;
		}

		if (collection.empty())
			return;

		buy = collection[0][0];
		for (int i = 0; i < collection.size(); i++) {
			sell = collection[i][1];
			profit += sell - buy;
			if (collection.size() > 1)
				maxProfit_Purchase_TwoTransactions_helper(std::vector<std::array<int, 2>>(collection.begin() + i + 1, collection.begin() + collection.size()), profit, max, depth + 1, transaction);
		}
	}

	static int maxProfit_Purchase_TwoTransactions(std::vector<std::array<int, 2>>& collection) {
		int max = 0;
		int profit = 0;
		maxProfit_Purchase_TwoTransactions_helper(collection, profit, max);
		return max;
	}

	static int functionSelect(const int& mode, std::vector<std::array<int, 2>> array) {
		int (*funcptr) (std::vector<std::array<int, 2>>&) = nullptr;

		switch (mode) {
		case 0:
			funcptr = maxProfit_SinglePurchase;
			break;
		case 1:
			funcptr = maxProfit_ManyPurchase;
			break;
		case 2:
			funcptr = maxProfit_Purchase_TwoTransactions;
			break;
		}
		return funcptr(array);
	}

	int bestSingleBuySell(const std::vector<int> arr, int mode, std::vector<std::array<int, 2>> array, int low, int high) {
		int currValue;

		if (arr.empty()) {
			if (high != -1 && low != -1)
				bestSingleBuySell_helper_addprices(low, high, array);
			return functionSelect(mode, array);
		}

		currValue = arr[0];

		if (currValue < high) {
			bestSingleBuySell_helper_addprices(low, high, array);
			high = -1;
			low = high;
		}

		if (low == -1)
			low = currValue;
		else if (currValue < low)
			low = currValue;
		else if ((low != -1 && currValue > low))
			high = currValue;

		return bestSingleBuySell(std::vector<int>(arr.begin() + 1, arr.begin() + arr.size()), mode, array, low, high);
	}

	bool StringsLooselyInterleaved(std::string s0, std::string s1, const std::string s2) {
		int index = -1;

		if (s2.empty()) {
			return true;
		}

		if (s0.length()) {
			index = s2.find(s0[0]);
			s0 = s0.substr(1);
		}

		if (index == std::string::npos && s1.length()) {
			index = s1.find(s1[0]);
			s1 = s1.substr(1);
		}

		if (index != -1) {

			return StringsLooselyInterleaved(s0, s1, s2.substr(0, index) + s2.substr(index + 1));
		}

		return false;
	}

	void allStringsLooselyInterleaved(std::string str1, std::string str2, int index, std::vector<std::string> list) {
		char c;
		std::string buffer;

		if (index == str2.length()) {
			for (auto ele : list) {
				std::cout << ele << '\n';
			}
			return;
		}

		c = str2[index];

		for (int i = 0; i <= str1.length(); i++) {

			if (i < str1.length())
				buffer = str1.substr(0, i) + c + str1.substr(i);
			else
				buffer = str1 + c;

			list.push_back(buffer);

		}

		return allStringsLooselyInterleaved(str1, str2, index + 1, list);
	}


	static bool isPalindrome(std::string s) {
		char a, b;

		while (!s.empty()) {
			a = s.front();
			b = s.back();

			if (a == b) {
				s.pop_back();
				s.erase(s.begin());
			}
			else {
				return false;
			}

		}

		return s.empty();
	}

	int RemoveOneMakePalindrome(std::string s, int index) {
		std::string tmp;

		if (index == s.size())
			return -1;
		tmp = s.substr(0, index) + s.substr(index + 1);

		if (isPalindrome(tmp))
			return index;

		return RemoveOneMakePalindrome(s, index + 1);
	}

	char MakeStringPalindrome(std::string s, int index) {
		char c;

		if (index >= s.length())
			return '!';

		if (index == 0 && isPalindrome(s))
			return '*';

		for (int i = 97; i <= 122; i++) {
			c = static_cast<char>(i);
			s.insert(index, std::string(1, c));
			if (isPalindrome(s))
				return c;
			s = s.substr(0, index) + s.substr(index + 1);
		}

		return MakeStringPalindrome(s, index + 1);
	}

	std::string StringEncode(std::string s, int index, int count, char curr, std::string result) {
		char currentChar = s[index];

		if (currentChar != curr) {
			if (index != 0)
				result += curr + std::to_string(count);
			if (index >= s.size())
				return result;
			count = 1;
		}
		else {
			count++;
		}
		return StringEncode(s, index + 1, count, currentChar, result);
	}

	std::string StringDecode(std::string s, std::string result, int index) {
		char c = s[index];
		int repeatCount = static_cast<int>(c) - 48;

		if (index >= s.length() || s.length() == 0)
			return result;

		if (std::isdigit(c)) {
			c = s[index - 1];
			for (int i = 0; i < repeatCount; i++)
				result += c;
		}
		return StringDecode(s, result, index + 1);
	}



}