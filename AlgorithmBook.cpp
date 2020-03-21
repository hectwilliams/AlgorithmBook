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

bool isPrime(const int& num) {
	for (int i = 2; i <= std::floor(std::sqrt(num)); i++)
		if (num % i == 0) return false;
	return true;
}

namespace chapter9
{

	void rgcf_helper_findPrimeSubsets(const int& target, std::set<int>& array) {

		for (auto i = 2; i <= std::floor(std::sqrt(target)); i++) {
			if (isPrime(i) && (target % i == 0)) {	// valid prime factor & divides
				array.insert(i);
				return rgcf_helper_findPrimeSubsets(target / i, array); // recursive call reducing target value
			}
		}

		if (isPrime(target)) {
			array.insert(target);  // lowest factor added to array is prime 
		}

	}

	// GCF

	int rgcf(int num1, int num2) {
		std::set<int> primeFactors1{ num1 }, primeFactors2{ num2 };
		std::set<int>::const_iterator it;
		chapter9::rgcf_helper_findPrimeSubsets(num1, primeFactors1);
		chapter9::rgcf_helper_findPrimeSubsets(num2, primeFactors2);
		int result = 1;

		for (auto element : primeFactors1) {
			it = primeFactors2.find(element);	// common prime factor found
			if (it != primeFactors2.end())
				result *= element;
		}

		return result;
	}

	int floodFill_helper_pixel(int x, int y, int canvas2D[5][5]) {
		return canvas2D[y][x];
	}
	bool floodFill_helper_inRange(const int& val, const int& limit) {
		return  val >= 0 && val < limit;
	}
	int floodFill_helper_getIndex(const int xy[2], const int& move, const int& limit) {
		return limit * xy[1] + xy[0] - move;
	}
	void floodFill_helper_printCanvas(const int canvas[5][5]) {
		for (auto r = 0; r < 5; r++) {
			for (auto c = 0; c < 5; c++) {
				std::cout << canvas[r][c] << " |";
			}
			std::cout << '\n';
		}
	}
	// Flood Fill Canvas
	void floodFill(int canvas2D[5][5], int startxy[2], const int& newColor, int target) {
		int limit = 5;
		int  moveBy[4] = { 1,-1, 5, -5 };
		int x = 0;
		int y = 0;
		int tempXY[2];
		int index;

		if (target == -1)
			target = canvas2D[startxy[1]][startxy[1]];

		for (int i = 0; i < 4; i++) {

			index = floodFill_helper_getIndex(startxy, moveBy[i], limit);
			y = (int)std::floor(index / limit);
			x = index % limit;

			if (floodFill_helper_inRange(y, limit) && floodFill_helper_inRange(x, limit)) {

				if (canvas2D[y][x] == target) {

					// update pixel 
					canvas2D[y][x] = newColor;

					// recursive call 
					tempXY[0] = x;
					tempXY[1] = y;
					floodFill(canvas2D, tempXY, newColor, target);

				}
			}
		}

	}

	// recursive Fib

	int rFib(int num, int a, int b, int counter) {
		if (counter >= 2) {
			std::swap(a, b);
			b += a;
		}

		if (num == 1 || num == 0 || num == counter) {
			return b;
		}

		return rFib(num, a, b, counter + 1);
	}

	// recursive binary search 

	bool rBinarySearch(std::vector<int> array, int target) {
		int mid = std::floor(array.size() / 2);
		auto left = std::vector<int>(array.begin(), array.begin() + mid);
		auto right = std::vector<int>(array.begin() + mid + 1, array.begin() + array.size());


		if (array[mid] == target)
			return true;

		if (mid == 0)
			return false;

		if (array[mid] > target)
			return rBinarySearch(left, target);
		else
			return rBinarySearch(right, target);

	}

	// Tarai (i.e. japanese to pass around)
	int tarai(const int& x, const int& y, const int& z) {

		std::cout << x << "-" << y << "-" << z << "-" << '\n';

		if (x <= y)
			return y;
		else
			tarai(tarai(x - 1, y, z), tarai(y - 1, z, x), tarai(z - 1, x, y));
	}


	void inOrderSubsets_helper_branch(std::string header, std::string str) {
		std::cout << header << " |";
		for (int i = 0; i < str.length() && !str.empty(); i++) {
			inOrderSubsets_helper_branch(header + str.at(i), str.substr(i + 1, std::string::npos));
		}
	}

	// subset 
	void inOrderSubsets(std::string str) {
		std::string bufferString;
		for (int i = 0; i < str.length(); i += 1) {
			bufferString = str.substr(i, std::string::npos);
			inOrderSubsets_helper_branch(bufferString.substr(0, 1), bufferString.substr(1, std::string::npos));
		}
	}



	std::vector<int> removeBags(std::vector<int> grapeBags, int start, int end) {
		grapeBags.erase(grapeBags.begin() + start, grapeBags.begin() + end);
		return grapeBags;
	}

	int GotAnyGrapes(std::vector<int> grapeBags, int& memo, int&& max) {
		int value;
		std::vector<int> buffer;

		if (max == 0 || max > memo)
			memo = max;

		for (int i = 0; i < grapeBags.size() && grapeBags.size(); i++) {

			if (i == grapeBags.size() - 1)
				buffer = removeBags(grapeBags, 0, grapeBags.size());
			else if (i == 0)
				buffer = removeBags(grapeBags, 0, 2);
			else
				buffer = removeBags(grapeBags, i - 1, i + 2);

			GotAnyGrapes(buffer, memo, max + grapeBags[i]);

		}
		std::cout << "current max = " << max << "\n";

		return memo;
	}

	// Collatz 

	int Collatz_apalooza(int num, int occurence, int count) {
		std::cout << num << '\n';

		if (num == 1) {
			++count;

			if (count == occurence)
				return count;
		}

		return Collatz_apalooza((num % 2 == 0) ? num / 2 : 3 * num + 1, occurence, count);
	}

	void TelephoneWords(std::string telephoneNumber, std::string&& buffer, std::map <int, std::string> mapper) {
		char code;
		std::map<int, std::string>::iterator it;

		if (buffer.size() == 7) {
			std::cout << buffer << '\n';
			return;
		}

		if (telephoneNumber.front() == '-')
			telephoneNumber = telephoneNumber.substr(1, std::string::npos);

		code = telephoneNumber[0];

		code = static_cast<int>(code) - 48;
		it = mapper.find(code);  // key in map

		if (it != mapper.end()) {
			for (auto c : it->second) { // loop possible characters in key-value
				TelephoneWords(telephoneNumber.substr(1, std::string::npos), buffer + c, mapper);
			}
		}

	}

	std::string RisingSquares(int num, int count) {
		std::string left, right, result;

		if (count > num)
			return "";

		if (count <= num)
			left += std::to_string(count * count) + " ";

		if (count + 1 <= num)
			right += std::to_string((count + 1) * (count + 1)) + " ";

		result = left + RisingSquares(5, count + 2) + right;
		for (auto c : result) {
			std::cout << result << '\n';
		}
		return result;
	}

	void  BinaryStringExpansion(std::string str, std::string buffer) {
		if (buffer.size() == 4) {
			std::cout << buffer << '\n';
			return;
		}

		for (int i = 0; i < str.size(); i++) {

			if (str[i] == '?') {

				for (auto newchar : { '1', '0' }) {
					BinaryStringExpansion(str.substr(i + 1, std::string::npos), buffer + newchar);
				}

			}
			else {

				buffer += str[i];

			}

		}
	}


	void StringAnagrams(std::string&& str, std::string buffer) {
		if (str.empty())
			std::cout << buffer << '\n';
		for (int i = 0; i < str.size(); i++) {
			StringAnagrams(str.substr(0, i) + str.substr(i + 1, std::string::npos), buffer + str[i]);
		}
	}

	void climbingStairs(int footsteps, std::vector<std::vector<int>>& data, std::vector<int> buffer) {
		int currSum = std::accumulate(buffer.begin(), buffer.end(), 0);

		if (currSum == footsteps) {
			data.push_back(buffer);
			return;
		}

		if (currSum > footsteps)
			return;

		for (auto possibleSteps : { 1, 2 }) {	// take 1 stair or 2
			buffer.push_back(possibleSteps);
			climbingStairs(footsteps, data, buffer);
			buffer.pop_back();

		}


		return;
	}


	void SumOfSquares(int num, std::vector<std::vector<int>>& combinations, std::vector<int> buffer, double&& count) {

		int sum = std::accumulate(buffer.begin(), buffer.end(), 0);

		if (sum > num)
			return;

		if (sum == num) {
			combinations.push_back(buffer);
			return;
		}

		for (auto n = count; n <= std::floor(std::sqrt(num)); n++) {
			buffer.push_back(n * n);
			SumOfSquares(num, combinations, buffer, count + 1);
			buffer.pop_back();
		}

	}

	bool AllValidNPairsOfParens_helper_isBalanced(std::string str) {
		std::string data;
		bool errorFound = false;
		int length;

		for (auto c : str) {
			length = data.length();

			if (c == '(')
				data += '(';

			if (c == ')') {
				if (data.length()) {
					if (data[length - 1] == '(')
						data.pop_back();
				}
				else {
					return false;
				}
			}
		}


		return data.length() == 0 && str.length();

	}

	void AllValidNPairsOfParens(int num, std::vector<std::string>& array, std::string buffer) {

		if (AllValidNPairsOfParens_helper_isBalanced(buffer) && buffer.length() == 2 * num) {
			std::cout << "balanced" << buffer << " " << '\n';
			array.push_back(buffer);
			return;
		}

		if (buffer.length() > 2 * num)
			return;

		for (auto& paren : { '(', ')' }) {
			buffer.push_back(paren);
			AllValidNPairsOfParens(num, array, buffer);
			buffer.pop_back();
		}
	}



	bool TowersofHanoi_helper_moveTopStackValue(int diskCount, int pIndex, int stackValue, std::vector<std::vector<int>>& poles) {
		bool ready = false;
		int index;

		for (int i = 1; i <= 2; i++) {

			index = (pIndex + i) % 3;
			std::vector<int>& pole = poles[index];


			if (pole.empty()) {
				ready = true;

			}
			else if (pole.front() > stackValue)
				ready = true;

			if (ready == true) {
				pole.insert(pole.begin(), stackValue);
				return true;
			}

		}
		return false;
	}

	void TowersofHanoi_helper_printValues(std::vector<std::vector<int>> poles) {
		for (auto p : poles) {
			for (auto data : p) {
				std::cout << data << " |";
			}
			std::cout << " -- \n";
		}
	}
	bool TowersofHanoi_helper_monotonic(int length, const std::vector<int>& pole) {
		int count = 0;
		for (auto num : pole) {
			count += +(count == num);
		}
		return (count == length);
	}

	void TowersofHanoi(int numOfDisks, std::vector<std::vector<int>> poles, int value, int&& depth) {
		TowersofHanoi_helper_printValues(poles);

		if (TowersofHanoi_helper_monotonic(numOfDisks, poles[2])) {
			TowersofHanoi_helper_printValues(poles);
			std::cout << " DEPTH " << depth << '\n';
			return;
		}

		for (int pindex = 0; pindex < poles.size(); pindex++) {  //pindex - Pole index 
			if (!poles[pindex].empty()) {
				if (poles[pindex].front() == value) {

					if (TowersofHanoi_helper_moveTopStackValue(numOfDisks, pindex, value, poles)) {
						poles[pindex].erase(poles[pindex].begin());
					}
					break;
				}

			}
		}
		return TowersofHanoi(numOfDisks, poles, (value + 1) % numOfDisks, depth + 1);

	}

	void  IPAddresses(std::string digits, std::vector<int> buffer) {
		std::string result = "";
		int count = 0;
		int sum = std::accumulate(buffer.begin(), buffer.end(), 0);

		if (sum == digits.size()) {

			for (int num : buffer) {
				result += digits.substr(0, num) + ".";
				digits = digits.substr(num, std::string::npos);
				++count;
			}

			result = result.substr(0, result.length() - 1);
			std::cout << result << '\n';
			return;
		}


		for (int i = 1; i <= 3 && buffer.size() < 4; i++) {
			buffer.push_back(i);
			IPAddresses(digits, buffer);
			buffer.pop_back();
		}
	}

	void UnevenDigits(const int& num, std::string data, int index) {
		int code;

		if (data.empty())
			data = std::to_string(num);

		code = static_cast<int>(data[index]);

		if (code >= 48 && code < 58) {
			if (code % 2 == 0)
				data.erase(data.begin() + index--);
		}

		if (index < data.length())
			return UnevenDigits(num, data, index + 1);
		else
			std::cout << data << "\n";
	}

	int GenerateAllPossibleCoinChange_coinType(const std::string str) {
		if (str == "dimes")
			return 10;
		else if (str == "nickels")
			return 5;
		else if (str == "pennies")
			return 1;
		else if (str == "quarters")
			return 25;
		return 0;
	}

	int GenerateAllPossibleCoinChange_helper_coinSum(std::map<std::string, int> mapCents, int&& sum = 0) {
		for (auto obj : mapCents)
			sum += obj.second * GenerateAllPossibleCoinChange_coinType(obj.first);
		return sum;
	}

	void GenerateAllPossibleCoinChange(int cents, std::vector< std::map<std::string, int> >& results, std::map<std::string, int> mapCents) {
		int sum = GenerateAllPossibleCoinChange_helper_coinSum(mapCents);

		if (sum == cents) {
			results.push_back(mapCents);
			return;
		}

		if (sum < cents) {

			for (auto& obj : mapCents) {
				obj.second++;
				GenerateAllPossibleCoinChange(cents, results, mapCents);
				--obj.second;
			}

		}

	}



	bool operator == (array2_t a, array2_t b) {
		return (a[0] == b[0]) && (a[1] == b[1]);
	}

	std::ostream& operator <<(std::ostream& out, const array2_t& arr) {
		out << " (" << arr[0] << ", " << arr[1] << ") ";
		return out;
	}

	bool Chess::isChessMoveSafe(array2_t moveTo, array2_t queen) {  // move placement does not conflict with queen
		if (queen == moveTo)
			return false;

		bool pathConflict = (queen[1] == moveTo[1])
			|| (queen[0] == moveTo[0])
			|| ((queen[0] - queen[1]) == (moveTo[0] - moveTo[1])) // left diag
			|| ((queen[0] + queen[1]) == (moveTo[0] + moveTo[1]));  // right diag

		return pathConflict == false;
	}

	bool Chess::isChessMoveSafe(array2_t moveTo, std::vector<array2_t> queens) {
		bool pathsOK = true;

		if (queens.empty())
			return true;

		for (auto queen : queens) {
			pathsOK &= isChessMoveSafe(moveTo, queen);
		}
		return pathsOK;
	}

	std::vector<array2_t> Chess::allSafeChessSquares(array2_t queen, std::vector<array2_t> list) {
		array2_t runner;

		if (list.size() == 0)
			list = this->getFreeBlocks();

		for (int i = 0; i < list.size(); i++) {	// open board region
			runner = list[i];
			if (!Chess::isChessMoveSafe(runner, queen)) {
				list.erase(list.begin() + i);
				--i;
			}
		}
		return list;
	}

	std::vector<array2_t> Chess::allSafeChessSquares(std::vector<array2_t> queens) {
		std::vector<array2_t> list;

		if (queens.size() == 0)
			return this->getFreeBlocks();

		for (auto queen : queens) {
			list = allSafeChessSquares(queen, list);
		}
		return list;
	}

	std::vector<array2_t> Chess::allSafeChessSquares(const int rLen, const int cLen) {
		return this->getFreeBlocks();
	}


	void Queens_helper_printQueens(std::vector<array2_t> queens) {
		for (auto q : queens)
			std::cout << "| " << q;
		std::cout << "|\t\n";

		return;
	}

	bool Queens_helper_find(std::vector<array2_t> list, array2_t element) {
		bool result = true;
		for (auto val : list)
			result &= (element == val);
		return false;
	}

	std::vector<array2_t> andGateList(std::vector<array2_t> a, std::vector<array2_t> b) {
		std::vector<array2_t> result;
		std::map<array2_t, int> mapper;

		for (auto ele_a : a) {
			for (auto ele_b : b) {
				if (ele_a == ele_b)
					result.push_back(ele_a);
			}
		}
		return result;
	}

	bool findPosition(const array2_t& pos, const std::vector<array2_t>& collection) {
		for (auto& ele : collection) {
			if (ele == pos) return true;
		}
		return false;
	}

	std::vector<array2_t> Chess::possiblePaths(std::vector<array2_t> list, int NQueens, std::vector<array2_t> queens, std::vector<array2_t> skip) {
		array2_t move;

		if (queens.size() == NQueens) {
			std::cout << " QUEENS ";  Queens_helper_printQueens(queens);
			clearBoard();
			boardFill(queens);
			std::cout << *this << '\n';
			return list;
		}

		for (int i = 0; i < list.size(); i++) {
			move = list[i];
			skip.push_back(move); //  add recent move to buffer( if valid move)

			if (findPosition(move, skip))  continue;

			if (isChessMoveSafe(move, queens)) {

				queens.push_back(move);
				possiblePaths(andGateList(list, allSafeChessSquares(queens)), NQueens, queens, skip);
				queens.pop_back();
			}
		}

		return list;
	}

	void Chess::Queens(std::vector<array2_t> list, std::vector<array2_t> queens, int n) {
		initBoard();
		std::vector<array2_t> skip;
		possiblePaths(allSafeChessSquares(queens), n, queens, skip);
	}

	void Chess::NQueens(const int n, const int rLen, const int cLen) {
		changeXY(rLen, cLen);
		std::vector<array2_t> queens;
		std::vector<array2_t> list = allSafeChessSquares(rLen, cLen);
		Queens(list, queens, n);

	}
}



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
			//std::cout << '\t' << node->val << '\n';
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

	static void Remove_helper_leftRotate(nodeBT* node) {
		nodeBT* gp = node->parent;
		nodeBT* lc = node->left;
		nodeBT* rc = node->right;
		nodeBT* tmp = node;
		nodeBT* gc = nullptr;
		nodeBT* runner;

		gp->right = rc;

		if (rc) {
			gc = rc->left;
			rc->left = lc;
		}

		if (lc) {
			runner = lc;
			while (runner->right)
				runner = runner->right;
			runner->right = gc;
		}
		else if (gc) {
			lc->left = gc;
		}

		delete tmp;
	}

	static void Remove_helper_rightRotate(nodeBT* node) {
		nodeBT* gp = node->parent;
		nodeBT* lc = node->left;
		nodeBT* rc = node->right;
		nodeBT* tmp = node;
		nodeBT* gc = nullptr;
		nodeBT* runner;

		gp->left = lc;

		if (lc) {
			gc = lc->right;
			lc->right = rc;
		}

		if (rc) {
			runner = rc;
			while (runner->left)
				runner = runner->left;
			runner->left = gc;
		}
		else if (gc) {
			lc->right = gc;
		}
		delete tmp;
	}

	static void writeNode(nodeBT* source, nodeBT* destination) {
		destination->count = source->count;
		destination->parent = source->parent;
		destination->val = source->val;
	}

	static void Remove_helper(nodeBT* node) {

		/* root node removal */
		if (!node->parent && node->left) {
			writeNode(node->left, node);
			Remove_helper_rightRotate(node->left);
			node->parent = nullptr;
		}
		else if (!node->parent && node->right) {
			writeNode(node->right, node);
			Remove_helper_leftRotate(node->right);
			node->parent = nullptr;
		}
		else if (node->parent->left == node) {
			Remove_helper_rightRotate(node);
		}
		else if (node->parent->right == node) {
			Remove_helper_leftRotate(node);
		}
	}

	bool BST::Remove(int val, nodeBT* node) {
		if (!node)
			node = root;

		if (node->val == val) {
			treeNodeCount--;
			node->count--;

			if (node->count == 0) {
				Remove_helper(node);
				uniqueCount--;
			}
			return true;
		}

		if (node->left && val < node->val)
			return Remove(val, node->left);

		if (node->right && val > node->val)
			return Remove(val, node->right);

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
			printf("hello");
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

	std::vector<std::shared_ptr<std::vector<int>>> BST::LayerArrays() {
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

namespace chapter12 {
	template <typename T> void swapper( T &a, T& b) {
		b = std::exchange(a, b);
	}

	std::vector<int>& BubbleSort(std::vector<int> &array) {
		for (int start = 0; start < array.size() - 1 ; start++) {
			for (int i = start + 1; i < array.size(); i++) {
				if ( array[i] < array[start]) {
					swapper(array[i], array[start]);
				}
			}
		}
		return array;
	}

	std::vector<int>& SelectionSort(std::vector<int>& array) {
		int minIndex;

		for (int i = 0; i < array.size(); i++) {
			minIndex = i;
			for (int p = minIndex; p < array.size(); p++) {
				if (array[p] < array[minIndex])
					minIndex = p;
			}

			if (minIndex != i) // indices data swap
				swapper(array[minIndex], array[i]);
		}
		return array;
	}

	template <typename T>
	T* nodealloc(T& value) {
		return Node<T> {value, nullptr};
	}

	static void  printLinkedList(Node<int> *node) {
		Node<int>* runner = node;
		while (runner) {
			printf("\tnode value: %d \n", runner->val);
			runner = runner->next;
		}
	}

	template <typename T>
	static void printArray(std::vector<T> array) {
		for (auto number : array)
			printf("\t [%12d]\n ", number);
		printf("\n\n");
	}

	static void LinkedListSwapNode(Node<int>* a_prev, Node<int> *a, Node<int>* b_prev, Node<int>* b) {
		auto buffer = b->next;
		
		if (a_prev)
			a_prev->next = b;

		if (b_prev == a) {
			b->next = a;
		}  else {
			b->next = a->next;
			b_prev->next = a;
		}

		a->next = buffer; 
	}

	Node<int>*  LinkedList::BubbleSort() {
		Node<int> *runner_prev = nullptr, * runner = head;
		Node<int>  *start_prev = nullptr, *start = head;
		
		while (start->next) {
			runner = start->next;
			runner_prev = start;
			while (runner) {
				if (runner->val < start->val) {
					if (start == head) {
						head = runner;
					}
					LinkedListSwapNode(start_prev, start, runner_prev, runner);
					swapper(start, runner);
				}
				runner_prev = runner;
				runner = runner->next;
			}

			start_prev = start;
			start = start->next;
		}
		printLinkedList(head);
		return head;
	}


	Node<int> *LinkedList::SelectionSort() {
		Node<int> *minNode, *minNode_prev = nullptr;
		Node<int>* runner_prev = nullptr, *runner = head;
		Node<int>* start_prev = nullptr, *start = head;
		std::vector<Node<int>*> test{ head, head }; 

		while (start->next) {
			runner = start->next;
			runner_prev = start;
			minNode = runner;

			while (runner) {
				if (runner->val < minNode->val) {
					head = (start == head) ? runner : head;
					minNode = runner;
					minNode_prev = runner_prev;
				}
				runner_prev = runner;
				runner = runner->next;
			}

			if (minNode != start->next) {
				LinkedListSwapNode(start_prev, start, minNode_prev, minNode);
				swapper(start, minNode);
			}

			start_prev = start;
			start = start->next;
		}
		printLinkedList(head);
		return head;
	}


	bool isSwappableCallback(NameObject a, NameObject b) {
		
		if ( b.lastName.compare(a.lastName) == 0 && b.firstName.compare(a.firstName) < 0)
			return true;
	
		if (b.lastName.compare(a.lastName) < 0)
			return true;
		
		return false;
	}

	std::vector<NameObject>& MultiKeySort(std::vector<NameObject>& array, bool (*isSwappable)(NameObject, NameObject)) {
		for (int i = 0; i < array.size() - 1; i++) {  //bubble it !
			for (int k = i + 1; k < array.size(); k++) {
				if (isSwappable(array[i], array[k])) {
					swapper(array[i], array[k]);
				}
			}
		}
		return array;
	}

	std::vector<int>& InsertionSort(std::vector<int>& array) {
		int Idx;
		for (int p = 1; p < array.size(); p++) {
			for (int i = 0; i < p; i++) {
				if ( array[i] > array[p] ) {  // insertion (sub-array rotate )
					for (int k = p; k > (p - (p-i)); k-- ) {
						swapper(array[k-1], array[k]);
					}
					break;
				}
			}
		}
		return array;
	}
	
	static void insertB_FRONT_A(Node<int> *b, Node<int> *b_prev, Node<int> *a, Node<int> *a_prev) {
		Node<int> *buffer = b->next;
		b->next = a;
		if (a_prev)
			a_prev->next = b;
		if (b_prev == a)
			a->next = buffer;
		else
			b_prev->next = buffer;
	}

	Node<int> *LinkedList::InsertionSort() {
		Node<int> *runner = head->next, *runner_prev = head;
		Node<int> *curr = head, *curr_prev = head;
		while (runner) {
			curr = head; 
			curr_prev = nullptr;
			while (curr != runner) {
				if (curr->val > runner->val) {
					head = (curr == head) ? runner : head;
					insertB_FRONT_A(runner, runner_prev, curr, curr_prev);
					runner = runner_prev;
					break;
				}
				curr_prev = curr;
				curr = curr->next;
			}
			runner_prev = runner; 
			runner = runner->next;
		}
		printLinkedList(head);
		return head;
	}

	 std::vector<int> CombineArrs( const std::vector<int> &a, const std::vector<int> &b) {
		int value, aIndex = 0, bIndex = 0;
		std::vector<int> result;

		while (aIndex < a.size() || bIndex < b.size() ) {

			if (aIndex >= a.size()) {
				value = b[bIndex];
				bIndex++;
			} else if (bIndex >= b.size()) {
				value = a[aIndex];
				aIndex++;
			} else if (b[bIndex] < a[aIndex]) {
				value = b[bIndex];
				bIndex++;
			} else {
				value = a[aIndex];
				aIndex++;
			}

			result.push_back(value);

		}

		return result;
	}

	Node<int>* MaxNode(Node<int>* a, Node<int>* b) {
		if (!a)
			return b;
		else if (!b)
			return a;
		else if (a->val > b->val)
			return b;
		else
			return a;
	}

	Node<int>* CombineList(Node<int>* a, Node<int>* b) {  // a and b are sored linked List
		Node<int>* result = nullptr, *buffer = nullptr,* head = nullptr;

		while (a || b) {

			buffer = MaxNode(a, b);
			
			if (a == buffer)
				a = a->next;

			if (b == buffer)
				b = b->next;

			if (!result) {
				head = buffer;
				head->next = nullptr;
				result = head;
			} else {
				result->next = buffer;
				result = result->next;
			}
			result->next = nullptr;

		}

		return head;
	}

	Node<int>* MergeSort(Node<int>* list) {
		Node<int> *result = nullptr, *runner = list, *buffer = nullptr;
		while (runner) {
			buffer = runner;
			runner = runner->next;
			buffer->next = nullptr; 
			result = CombineList(result, buffer);
		}
		printLinkedList(result);
		return result;
	}

	int Partition(std::vector<int> &array, const int &mode, const int & start, const int &end) {
		int pIndex = (mode == 0) ? start : (mode == 1) ? (std::floor( end-start / 2)) : end;  // select mode [0-zero, 1-mid, 2 last] pivot
		int j = start - 1;
		int currPIndex;
		int pivot = array[pIndex];

		try {
			for (int r = start; r  <=  ((end == -1) ? (array.size() - 1): end) ; r++) {					
				if (array[r] < pivot) {
					j++;
					pIndex = (j == pIndex) ? r : pIndex;
					swapper(array[r], array[j]);
				}
			}
			currPIndex = j + 1;
			if (array[currPIndex] != array[pIndex]) {
				swapper(array[currPIndex], array[pIndex]);
				pIndex = currPIndex;
			}

		} catch (std::exception &exception) {
			printf("error msg:  \t%s", exception.what());
		}

		
		return pIndex;
	}

	Node<int>* Partition(Node<int>* node) {
		Node<int> *runner_prev = nullptr, *runner = node;
		Node<int> *ptr = node, *ptr_prev = nullptr, *head = node;
		Node<int> *piv = node, *piv_prev = node;
	
		while (runner) {

			if (runner->val < piv->val) {

				if (ptr == head) 
					head = runner;

				if (piv == ptr) {
					piv = ptr;
					piv_prev = runner_prev;
				}
				LinkedListSwapNode(ptr_prev, ptr, runner_prev, runner);

				ptr = runner->next;
				ptr_prev = runner;
							
			}

			runner_prev = runner;
			runner = runner->next;

		}

		if (ptr != piv) {  // partition node must be in middle
			LinkedListSwapNode(ptr_prev, ptr, piv_prev, piv);
		}
		
		printLinkedList(head);
		return head;
	}

	void QuickSort(std::vector<int> &array, int start,  int end) {
		int p = 0;

		if (start == -1 && end == -1) {
			start = 0;
			end = array.size() - 1;
		}

		if ( (end - start) > 0) {
			p = Partition(array, 0, start, end);
			QuickSort(array, 0, p - 1 );
			QuickSort(array, p + 1, end);
		}

	}

	std::vector<int> MergeSort(std::vector<int> collection) {
		int mid = std::floor(collection.size() / 2);
		std::vector<int> buffer;
		std::vector<int> left, right; 

		if (collection.size() == 2) {
			if (collection[0] > collection[1])
				swapper(collection[0], collection[1]);
			return collection;
		}

		left = std::vector<int>(collection.begin(), collection.begin() + mid );
		left = MergeSort(left);

		right = std::vector<int>(collection.begin() + mid, collection.begin() + collection.size());
		right = MergeSort(right);

		collection = CombineArrs(left, right);
		return collection;
	}

	int Partition3(std::vector<int>& array, int pivotIndex, int start , int end) {
		std::map<int, std::vector<int>> pMap;
		std::map<int, std::vector<int>>::iterator it ;
		end = (end == -1) ? array.size() - 1 : end;
		int j = start - 1, pivot, currIndex = pivotIndex;
		
		try {
			
			if ( !(pivotIndex >= 0 && pivotIndex < array.size() - 1) )
				throw;
			pivot = array[pivotIndex];

			for (int i = start; i <= end; i++) {
				
				if (pivot == array[i]) {
					it = pMap.find(array[i]);
					if (it == pMap.end()) {
						pMap.insert(std::make_pair(array[i], std::vector<int>{i} ));
					} else if (std::find(it->second.begin(), it->second.end(), i) == it->second.end()) { // index not found in prop value list
						pMap.find(array[i])->second.push_back(i);
					}
				}
				
				if (array[i] < pivot) {
					++j;
					pivotIndex = (j == pivotIndex) ? i : pivotIndex;
					
					it = pMap.find(array[j]);  // found pivot twin/clone!
					
					if (it != pMap.end()) {  
						printf("moved data %d  index %d\n", array[i], i);

						if (std::find(it->second.begin(), it->second.end(), j) != it->second.end()) {  // swap value is indeed a twin 
							for (int n = 0; n < it->second.size();  n++) {
								if (it->second[n] == j) {  // update  index  of twin index;
									it->second[n] = i;
								}
								break;
							}
						}
					}

					swapper(array[i], array[j]);
				}
			}
			printArray(array);  // :) 
			if (j + 1 != pivotIndex) {
				swapper(array[j + 1], array[pivotIndex]); // pivot value should split numbers
				pivotIndex = j + 1;
			}
			
			it = pMap.find(array[currIndex]);
			if (it != pMap.end()  ) {
				if (it->second.size() > 1) {


					while (it->second.size() ) {
						if (it->second.front() != pivotIndex) {  
							swapper(array[++currIndex], array[it->second.front()]);  // swap twin/clone immediately after pivot
						}
						it->second.erase(it->second.begin());
					}
				}
			}

		} catch (std::exception & exception) {
			printf("error msg: %s", exception.what());
		}
		return pivotIndex;
	}


	void QuickSort3(std::vector<int>& array,  int start,  int end) {
		int p = 0;

		if (start == -1 && end == -1) {
			start = 0;
			end = array.size() - 1;
		}

		if ( (end -  start) > 0 ) {
			p = Partition3(array, start, start, end);
			QuickSort3(array, 0, p - 1);
			QuickSort3(array, p + 1, end);
		}

		printArray(array);
	}


	

	template <class T>
	bool heapifyCaller (std::vector<T>& arr, int l, int r) {
		return false;
	}
	template <>
	bool heapifyCaller(std::vector<int>& arr, int leaf_pos, int curr_pos) {
		return arr[leaf_pos] > arr[curr_pos];
	}
	template <>
	bool heapifyCaller(std::vector<KarateStudent>& arr, int leaf_pos, int curr_pos) {
		std::vector<KarateStudent>::iterator it;

		if (BeltMap.find(arr[leaf_pos].Belt) == BeltMap.end() || BeltMap.find(arr[curr_pos].Belt) == BeltMap.end()) {
			return false;
		}

		if (BeltMap.find(arr[leaf_pos].Belt)->second > BeltMap.find(arr[curr_pos].Belt)->second) {
			return true;
		}

		if (BeltMap.find(arr[leaf_pos].Belt)->second == BeltMap.find(arr[curr_pos].Belt)->second && BeltMap.find(arr[leaf_pos].Belt)->first.compare(BeltMap.find(arr[curr_pos].Belt)->first) > 0  ) {

			return true;
		}
	}

	template <class T>								
	static void Heapify(std::vector<T>& array, const int pos, const int n , bool (*cb)(std::vector<T>&, int, int) = heapifyCaller) {
		int currPos = pos, left, right;
		left = (2 * pos) + 1;
		right = left + 1;

		if (pos < 0)
			return;

		if (left < n) {
			if (heapifyCaller(array, left, currPos) /*(array[left] > array[currPos]) */ )  {
				currPos = left;
			}
		}

		if (right < n) {
			if (heapifyCaller(array, right, currPos)  /*array[right] > array[currPos]*/ ) {
				currPos = right;
			}
		}

		if (currPos != pos)
			swapper( array[pos], array[currPos] );

		Heapify(array, pos - 1, n);
	
	}

	template <class T>
	void PancakeSort(std::vector<T>& array ) {
		int nodePos = std::floor(array.size() / 2) - 1;
		int k = 0;
		for (int i = array.size(); --i ;) {
			Heapify(array, nodePos, array.size() - k++ );
			swapper(array[i], array[0]);
		}
		printArray(array);
	}

	static int RadixSort_helper_find_bucket_index( unsigned long int data, const int &pos) {
		unsigned long int val = data / ( (pos == 0) ? 1 : std::pow( 10, pos) );
		val = val % 10;
		return val;
	}

	void RadixSort( std::vector <unsigned long int> &array) {
		std::array< std::vector<unsigned long int> , 10> collection;
		int p;
		int index;

		for (int i = 0; i < 10; i++) {
			for (auto ele : array) {
				p = RadixSort_helper_find_bucket_index(ele, i);
				collection[p].push_back(ele);
			}

			index = 0;
			for (auto& arr: collection) {
				if (!arr.empty()) {
					for (auto ele : arr) {
						array[index++] = ele;
					}
				}
				arr.clear();
			}
		}
		printArray(array);

	}

	

	void BeltSort(std::vector<KarateStudent>& array) {
		PancakeSort<KarateStudent>(array);

		for (auto obj : array)
			printf("name %s  \t belt %s\n" , obj.Name.c_str(), obj.Belt.c_str());
	}

	void WiggleSort(std::vector<int> &array) {
		int mid = (int)std::floor(array.size() / 2);
		QuickSort(array);
		int median = array[mid];
		int low = 1, high = array.size() - 1;
		
		while (low < array.size()) {
			if (array[mid] > array[low])
				swapper(array[mid++], array[low]);
			low += 2;
		}

		printArray(array);      
	}

}

namespace chapter13 {

	std::array<int, 2> MinimalThreeArrayRange(std::vector<int> a, std::vector<int> b, std::vector<int> c ) {
		int currIndex;
		int min = INT_MIN, tupleIndex;
		std::vector<int> array, tupleBuffer;
		int a_int = 0, b_int = 0, c_int = 0;
		std::array<bool, 3> boolean = { false, false, false };
		std::vector < std::tuple< std::vector<int>, int>> tupleMap = {
			{a, a_int},
			{b, b_int},
			{c, c_int}
		};
		std::array<int, 2> result{};


		while (true) {
			min = INT_MIN;
			currIndex = -1;

			for (int i = 0; i < tupleMap.size(); i++) {	
				std::tie(array, tupleIndex) = tupleMap[i];
				if (tupleIndex < array.size()) {
					if (array[tupleIndex] < min || min == INT_MIN) {
						min = array[tupleIndex];
						currIndex = i;
					}
				}
			}

			if (currIndex != -1) {
				boolean[currIndex] = true;
				tupleBuffer.push_back(min);
				++std::get<1>(tupleMap[currIndex]);
			}

			if (boolean[0] && boolean[1] && boolean[2]) {
				result = { tupleBuffer[tupleBuffer.size() - 3] ,  tupleBuffer[tupleBuffer.size() - 1] };
				break;
			}

			if (std::get<1>(tupleMap[0]) == a.size() && std::get<1>(tupleMap[1]) == b.size() && std::get<1>(tupleMap[2]) == c.size() )
				break;
		}
		return result;
	}

	std::vector<int> IntersectSortedArray(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;
		int aa = 0, bb = 0;

		while (1) {
			
			if (aa >= a.size() || bb >= b.size())
			 break;
			else if (a[aa] < b[bb])
				aa++;
			else if (b[bb] < a[aa])
				bb++;
			else if (b[bb] == a[aa]) {
				result.push_back(a[aa]);
				bb++;
				aa++;
			}

		}

		printf("size \t%d", result.size());
		return result;
	}

	std::vector<int> IntersectSortedArrayDedupe(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;
		int aa = 0, bb = 0;

		while (1) {

			if (aa >= a.size() || bb >= b.size())
				break;
			
			if (!result.empty()) {  
				if (result.back() == a[aa]) {
					aa++;
					continue;
				}

				if (result.back() == b[bb]) {
					bb++;
					continue;
				}
			}

			 if (a[aa] < b[bb])
				aa++;
			else if (b[bb] < a[aa])
				bb++;
			else if (b[bb] == a[aa]) {
				result.push_back(a[aa]);
				bb++;
				aa++;
			}

		}

		printf("size \t%d", result.size());
		return result;
	}
	std::vector<int> UnionSortedArrays(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;
		int aa = 0, bb = 0;

		while (1) {
			if (aa >= a.size() && bb >= b.size())
				break;

			if (bb >= b.size())
				result.push_back(a[aa++]);

			else if (aa >= a.size())
				result.push_back(b[bb++]);

			else if (b[bb] < a[aa])
				result.push_back(b[bb++]);

			else if (a[aa] < b[bb])
				result.push_back(a[aa++]);

			else if (a[aa] == b[bb]) {
				result.push_back(a[aa]);
				bb++;
				aa++;
			}

		}

		return result;
	}


	std::vector<int> UnionSortedArraysDedupe(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;
		int aa = 0, bb = 0;
		
		while (1) {

			if (aa >= a.size() && bb >= b.size())
				break;

			if (result.size()) {
				if (result.back() == a[aa]) {
					aa++;
					continue;
				} else if (result.back() == b[bb]) {
					bb++;
					continue;
				}
			}


			if (bb >= b.size())
				result.push_back(a[aa++]);

			else if (aa >= a.size())
				result.push_back(b[bb++]);

			else if (b[bb] < a[aa])
				result.push_back(b[bb++]);

			else if (a[aa] < b[bb])
				result.push_back(a[aa++]);

			else if (a[aa] == b[bb]) {
				result.push_back(a[aa]);
				bb++;
				aa++;
			}

		}
		for (auto x : result)
			printf(" values %d \n", x);

		return result;
	}


	std::vector<int> IntersectionUnsortedArrayInPlace(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;

		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < b.size(); j++) {
				if (a[i] == b[j] && std::find(result.begin(), result.end(), j) == result.end()) {
					result.push_back(j);
					break;
				}
			}
		}

		for (auto &ele : result) {
			ele = b[ele];
		}
		
		return result;
	}


	std::vector<int> UnionUnsortedArrays(std::vector<int> a, std::vector<int> b) {
		std::map<int, int> a_map, b_map;
		std::map<int, int>::iterator it, prev_it;
		std::vector<int> result; 


		for (auto ele : a) {
			it = a_map.find(ele);

			if (it == a_map.end()) {
				a_map.insert(std::make_pair(ele, 1));
			} else {
				it->second++;
			}
			
			result.push_back(ele);
		}

		for (auto ele : b) {
			it = b_map.find(ele);
			prev_it = a_map.find(ele);

			if (it == b_map.end()) {
				b_map.insert(std::make_pair(ele, 1));

				if (prev_it == a_map.end())
					result.push_back(ele);
				
			} else {
				it->second++;
				
				if (prev_it != a_map.end()) {
					if (prev_it->second < it->second) 
						result.push_back(ele);
				} else {
					result.push_back(ele);
				}
			}
		}
		return result; 
	}

	std::vector<int> UnionUnsortedArraysInPlace(std::vector<int> &a, std::vector<int> b) {
		std::map<int, int> a_map, b_map;
		std::map<int, int>::iterator it, prev_it;

		for (auto ele : a) {
			it = a_map.find(ele);

			if (it == a_map.end()) 
				a_map.insert(std::make_pair(ele, 1));
			else 
				it->second++;
		}

		for (auto ele : b) {
			it = b_map.find(ele);
			prev_it = a_map.find(ele);

			if (it == b_map.end()) {
				b_map.insert(std::make_pair(ele, 1));

				if (prev_it == a_map.end())
					a.push_back(ele);
			} else {
				it->second++;

				if (prev_it != a_map.end()) {
					if (prev_it->second < it->second)
						a.push_back(ele);
				}
				else {
					a.push_back(ele);
				}
			}
		}
		return a;
	}


	std::vector<int> UnionUnsortedArraysDedupe(std::vector<int> a, std::vector<int> b) {
		std::vector<int> result;
		std::map<int, int> map;
		std::map<int, int>::iterator it;

		for (auto ele : a) {
			it = map.find(ele);
			if (it == map.end()) {
				map.insert(std::make_pair(ele, 1));
				result.push_back(ele);
			}
		}

		for (auto ele : b) {
			it = map.find(ele);
			if (it == map.end()) {
				map.insert(std::make_pair(ele, 1));
				result.push_back(ele);
			}
		}

		return result;
	}

	bool SubsetSortedArrays (std::vector<int> a, std::vector<int> b) {
		int index = -1; 
		std::map <int, int> map;
		std::vector<int> result; 
		
		for (int i = 0; i < a.size(); i++) {
			if (map.find(a[i]) == map.end())
				map.insert(std::make_pair(a[i], i));
		}
	
		for (auto ele : b) {
			if (map.find(ele) != map.end()) {
				if (index == -1)
					index = map.find(ele)->second;
				else if (a[++index] != ele)
					return false;
			} 
		}
		return true;
	}

	bool SubsetUnSortedArrays (std::vector<int> a, std::vector<int> b) {
		int tail = a.size() - 1;
		int head = 0;
		std::map <int, int> map;

		while (tail >= head) {
			if (map.find(a[head]) == map.end()) {
				map.insert(std::make_pair(a[head], 1));
			}
			if (map.find(a[tail]) == map.end()) {
				map.insert(std::make_pair(a[tail], 1));
			}
			tail--;
			head++;
		}

		tail = b.size() - 1;
		head = 0;
		while (tail >= head) {
			if (map.find(b[tail--]) == map.end() || map.find(b[head++]) == map.end())
				return false;
		}
		return true;
	}

	
	void Sequencer(std::vector < std::tuple<uint64_t, std::string>> array ) {
		uint64_t num;
		std::string str; 
		PriQueue<std::string, uint64_t> queue;

		for (int i = 0; i < array.size(); i++) {
			std::tie(num, str) = array[i];
			queue.push(str, num);
		}
	}

}

namespace chapter14 {
	//refer to AlgorithmBook.h file
}

namespace chapter15 {
	//refer to AlgorithmBook.h file
}