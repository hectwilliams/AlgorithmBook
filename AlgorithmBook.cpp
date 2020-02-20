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
#include <sstream>
#include <tuple>
#include <deque>
bool isPrime(const int& num) {
	for (int i = 2; i <= std::floor(std::sqrt(num)); i++) 
		if (num % i == 0) return false;
	return true;
}

namespace chapter9
{	

	void rgcf_helper_findPrimeSubsets(const int &target, std::set<int>& array) {

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
		std::set<int> primeFactors1{ num1 }, primeFactors2{num2};
		std::set<int>::const_iterator it; 
		chapter9::rgcf_helper_findPrimeSubsets(num1, primeFactors1);
		chapter9::rgcf_helper_findPrimeSubsets(num2, primeFactors2);
		int result = 1; 

		for (auto element: primeFactors1) {
			it = primeFactors2.find(element);	// common prime factor found
			if (it != primeFactors2.end())
				result *= element;
		}

		return result;
	}

	int floodFill_helper_pixel( int x, int y, int canvas2D[5][5]) {
		return canvas2D[y][x];
	}
	bool floodFill_helper_inRange(const int& val, const int &limit) {
		return  val >= 0 && val < limit;
	}
	int floodFill_helper_getIndex(const int xy[2], const int& move, const int& limit) {
		return limit * xy[1]  + xy[0] - move;
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
		int  moveBy[4] = { 1,- 1, 5, -5 };
		int x = 0;
		int y = 0;
		int tempXY[2];
		int index; 

		if (target == -1)
			target = canvas2D[startxy[1]][startxy[1]];

		for (int i = 0; i < 4; i++) {

			index = floodFill_helper_getIndex(startxy, moveBy[i], limit);
			y = (int) std::floor(index / limit);
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

	int rFib(int num, int a , int b , int counter ) {
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
		int mid = std::floor(array.size()/2);
		auto left = std::vector<int>(array.begin(), array.begin() + mid);
		auto right = std::vector<int>(array.begin() + mid + 1, array.begin() + array.size() );
		
	
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
			tarai(tarai(x-1, y, z), tarai(y-1, z, x), tarai(z - 1, x ,y));
	}


	void inOrderSubsets_helper_branch(std::string header, std::string str) {
		std::cout << header << " |";
		for (int i = 0; i < str.length() && !str.empty() ; i++) {
			inOrderSubsets_helper_branch(header + str.at(i), str.substr(i + 1, std::string::npos));
		}
	}

	// subset 
	void inOrderSubsets(std::string str) {
		std::string bufferString;
		for (int i = 0; i < str.length(); i += 1) {
			bufferString = str.substr(i, std::string::npos);
			inOrderSubsets_helper_branch(bufferString.substr(0, 1 ) , bufferString.substr(1, std::string::npos));
		}
	}



	std::vector<int> removeBags(std::vector<int> grapeBags, int start, int end) {
		grapeBags.erase( grapeBags.begin() + start, grapeBags.begin() + end);
		return grapeBags;
	}

	int GotAnyGrapes(std::vector<int> grapeBags, int & memo, int && max) {
		int value;
		std::vector<int> buffer;

		if (max == 0 || max > memo)
			memo = max;

		for (int i = 0; i < grapeBags.size() && grapeBags.size() ; i++) {

			if (i == grapeBags.size() - 1) 
				buffer = removeBags(grapeBags, 0, grapeBags.size());
			else if (i == 0) 
				buffer = removeBags(grapeBags, 0, 2);
			else 
				buffer = removeBags(grapeBags , i - 1, i + 2);

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

		return Collatz_apalooza ( (num % 2 == 0) ? num / 2: 3 * num + 1, occurence, count );
	}

	void TelephoneWords(std::string telephoneNumber, std::string &&buffer, std::map <int, std::string> mapper ) {
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
				TelephoneWords( telephoneNumber.substr(1, std::string::npos) , buffer + c, mapper);
			}
		}

	}

	std::string RisingSquares(int num, int count ) {
		std::string left, right, result;

		if (count > num)
			return "";

		if (count <= num)
			left += std::to_string(count * count) + " ";
		
		if (count + 1 <= num)
			right += std::to_string( (count + 1) * (count + 1)) + " ";
		
		result =  left  +  RisingSquares(5, count + 2)  + right;
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

			} else {

				buffer += str[i];

			}

		}
	}


	void StringAnagrams(std::string && str, std::string buffer) {
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
			return ;
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


	void SumOfSquares(int num, std::vector<std::vector<int>> &combinations, std::vector<int> buffer, double && count) {
		
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
				} else {
					return false;
				}
			}
		}
		

		return data.length() == 0 && str.length() ;

	}

	void AllValidNPairsOfParens(int num, std::vector<std::string> &array, std::string buffer) {
		
		if (AllValidNPairsOfParens_helper_isBalanced(buffer)  &&  buffer.length() == 2 * num) {
			std::cout << "balanced" << buffer << " " << '\n';
			array.push_back(buffer);
			return;
		}
		 
		if (buffer.length() > 2 * num)
			return;
		 
		for (auto& paren: {'(', ')'}) {
			buffer.push_back(paren);
			AllValidNPairsOfParens(num, array, buffer);
			buffer.pop_back();
		}	
	}



	bool TowersofHanoi_helper_moveTopStackValue(int diskCount, int pIndex, int stackValue, std::vector<std::vector<int>> &poles) {
		bool ready = false;
		int index; 

		for (int i = 1; i <=2; i++) {

			index = (pIndex + i) % 3;  
			std::vector<int>& pole = poles[index];


			if (pole.empty()) {
				ready = true;

			} else if (pole.front() > stackValue)
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
	    
	void TowersofHanoi(int numOfDisks, std::vector<std::vector<int>> poles, int value, int &&depth) {
		TowersofHanoi_helper_printValues(poles);

		if (TowersofHanoi_helper_monotonic(numOfDisks, poles[2])) {
			TowersofHanoi_helper_printValues(poles); 
			std::cout << " DEPTH " << depth << '\n';
			return;
		}

		for (int pindex = 0; pindex < poles.size(); pindex++ ) {  //pindex - Pole index 
			if (!poles[pindex].empty()) {
				if (poles[pindex].front() == value) {

					if (TowersofHanoi_helper_moveTopStackValue(numOfDisks, pindex, value, poles)) {
						poles[pindex].erase(poles[pindex].begin());
					}
					break;
				}

			}
		}
		return TowersofHanoi(numOfDisks, poles, (value + 1) % numOfDisks, depth + 1 );

	}

	void  IPAddresses( std::string digits, std::vector<int> buffer) {
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
			return ;
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
				data.erase(data.begin() + index-- );
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

	int GenerateAllPossibleCoinChange_helper_coinSum(std::map<std::string, int> mapCents, int && sum = 0) {
		for (auto obj : mapCents)
			sum += obj.second * GenerateAllPossibleCoinChange_coinType(obj.first);
		return sum;
	}

	void GenerateAllPossibleCoinChange(int cents, std::vector< std::map<std::string, int> >& results, std::map<std::string, int> mapCents ) {
		int sum = GenerateAllPossibleCoinChange_helper_coinSum(mapCents);

		if ( sum == cents) {
			results.push_back(mapCents);
			return;
		}

		if (sum < cents) {

			for (auto &obj : mapCents) {
				obj.second++;
				GenerateAllPossibleCoinChange(cents, results, mapCents);
				--obj.second;
			}

		}

	}



	bool operator == ( array2_t a,  array2_t b) {
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
			|| ( (queen[0] + queen[1]) == (moveTo[0] + moveTo[1]));  // right diag

		return pathConflict == false;
	}
	 
	bool Chess::isChessMoveSafe(array2_t moveTo, std::vector<array2_t> queens) {
		bool pathsOK = true;

		if (queens.empty())
			return true;

		for (auto queen : queens) {
			pathsOK &= isChessMoveSafe(moveTo, queen);
		}
		return pathsOK ;
	}

	 std::vector<array2_t> Chess::allSafeChessSquares(array2_t queen, std::vector<array2_t> list) {
		array2_t runner; 
		
		if (list.size() == 0)
			list = this->getFreeBlocks();
		
		for (int i = 0; i < list.size(); i++) {	// open board region
			runner = list[i];
			if (!Chess::isChessMoveSafe(runner, queen) ) { 
				list.erase(list.begin() + i);
				--i;
			}
		}
		return list;
	 }
	 
	 std::vector<array2_t> Chess::allSafeChessSquares (std::vector<array2_t> queens) {
		 std::vector<array2_t> list;

		 if (queens.size() == 0)
			 return this->getFreeBlocks();

		 for (auto queen : queens) {
			 list = allSafeChessSquares(queen, list);
		 }
		 return list; 
	 }

	  std::vector<array2_t> Chess::allSafeChessSquares (const int rLen, const int cLen) {
		return this->getFreeBlocks();
	 }


	 void Queens_helper_printQueens (std::vector<array2_t> queens) {
		for (auto q : queens)
			std::cout << "| " << q;
		std::cout << "|\t\n";

		return ;
	 }
	 
	 bool Queens_helper_find (std::vector<array2_t> list, array2_t element) {
		 bool result = true; 
		 for (auto val: list)
			result &=  (element == val);
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

	 bool findPosition(const array2_t &pos, const std::vector<array2_t> &collection) {
		 for (auto& ele : collection) {
			 if (ele == pos) return true;
		 }
		 return false;
	 }

	 std::vector<array2_t> Chess::possiblePaths (std::vector<array2_t> list,  int NQueens, std::vector<array2_t> queens, std::vector<array2_t> skip ) {
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
				possiblePaths( andGateList(list,  allSafeChessSquares(queens)) , NQueens,  queens, skip);
				queens.pop_back();
			 }
		 }

		 return list; 
	 }

	 void Chess::Queens(std::vector<array2_t> list, std::vector<array2_t> queens, int n) {		
		 initBoard();
		 std::vector<array2_t> skip;
		 possiblePaths( allSafeChessSquares(queens) , n, queens, skip);
	 }

	 void Chess::NQueens(const int n, const int rLen, const int cLen) {
		 changeXY(rLen, cLen);
		 std::vector<array2_t> queens;
		 std::vector<array2_t> list = allSafeChessSquares(rLen, cLen);
		 Queens(list, queens, n);

	 }
}


  
namespace chapter10 {

	 std::ostream& operator << (std::ostream &out, const std::vector<std::string> &strArray) {
		for (auto str: strArray) {
			out << str << " ";
		}
		return out;
	}

	 static void StringToWordArray_helper_handlePunctuation(std::string &s) {
		std::string plist = ",'-.!?";
		bool charPmark, pmarkChar;

		for (int i = 0; i < s.length() ; i++) {
			pmarkChar = plist.find(s[i]) != std::string::npos && std::isalpha(s[i + 1]); 
			charPmark = plist.find(s[i + 1]) != std::string::npos && std::isalpha(s[i]); 

			if (plist.find(s[i]) != std::string::npos && plist.find(s[i + 1]) != std::string::npos)
				continue; 

			if ( pmarkChar || charPmark) {
				s.insert(s.begin() + i + 1, ' ');
				i++;
			}

		}


	}


	std::vector<std::string> StringToWordArray(std::string s, bool handlePunctuation ) {
		std::stringstream streamData;
		std::string stringBuffer;
		std::vector<std::string> result;
		

		if (handlePunctuation ) {
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

	static void ReverseWordOrder_findNextWord(int& idx, const int &step, const std::vector<std::string> &collection) {
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
		} while ( posDown >= 0);

		for (auto& ele : array) {

			if (std::isalpha(ele[0])) {
				std::tie(int_buffer, str_buffer) = downArray.front();

				if (std::isupper(ele[0])) {
					str_buffer[0] = std::toupper(str_buffer[0]);
				} else {
					for (auto &c : str_buffer) {
						c = std::tolower(c);
					}
				}

				ele = str_buffer;
				downArray.erase(downArray.begin());
			}

		}

		return computeMessage(array);
	}


	static void lowerCaseString(std::string &str) {
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

	bool isRotation( std::string  s1,  std::string s2) {
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


	std::string Censor( std::string s,  std::vector<std::string> list) {
		const std::string censorWord = "xxxx";
		int index = 0;

		while (!list.empty()) {
			index = s.find(list.front());
			s = s.substr(0, index) + censorWord + s.substr(index + list.front().length() );
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
			} else {
			index++;

			}
		}
	}

	std::string BadCharacters( std::string s, const char  c[]) {
		auto *ptr = c;
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

	
	std::string Dedupe( const std::string s) {
		std::map<char, int> map;
		std::map<char, int>::iterator it;
		std::string result;
		int i = 0;
		for (int k = 0; k < s.length(); k++) {
			it = map.find(s[k]);
			if (it == map.end()) {

				map.insert(std::make_pair(s[k], i));
			} else {
				it->second = i;
			}
			i++;
		}

		for (int k = 0; k < s.length(); k++) {
			it = map.find(s[k]);
			if (it!=map.end() && it->second == k ) {
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
			} else { 
				if (stuple == c )
					buffer = std::make_tuple('\0', -1);
				it->second++;
			}
			i++;
		}
		
		std::tie(stuple, ituple) = buffer;
		return ituple;
	}

	std::string NumToString( int number) {
		std::string result; 
		while (number >= 1) {
			result = char( (number % 10) + 48) + result;
			number = number / 10;
		}
		std::cout << result << '\n';
			return result;;
	}

	std::string  NumToString(double fraction) {
		std::string f;
		std::string whole = NumToString((int)fraction);
		fraction =   fraction - (static_cast<int>(fraction));
		int digit;

		while (fraction  > 0.0) {
			fraction = (fraction * 10);
			digit = std::round(fraction);
			f +=  static_cast<char>(48 + digit);
			fraction -= digit;
		}

		return whole + '.' + f;
	}

	static std::vector<std::string> NumToText_helper_digitToText( char curr , const int &index, int &depth) {
		static std::vector<std::string> buffer;
		static int prev = -1;
		int tmp  = static_cast<int>(curr) - 48;
		std::map<int, std::array<std::string, 2>>::iterator it;
		
		if (illions.find(depth) != illions.end()) {
			buffer.insert(buffer.begin(), illions.find(depth)->second);
		}


		if (index == 0 && tmp != 0) {
			prev = tmp;
			buffer.insert( buffer.begin() , NumToTextMap.find(tmp)->second[0] );
		} 
		
		if (index == 1) {
			if (tmp == 1 && prev != 0 ) 
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
		return NumToText(number, (index3 + 1) % 3, s.substr(0, s.length() - 1) , depth + 1, result);
	
	}

	bool isPermutation( std::string s1,  std::string s2, const char index ) {
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
		char c ;

		if (s.empty()) {
			if (count == 26)
				return true;
			else
				return false;
		}

		c = std::tolower(s.front());
		code = static_cast<int>(c);

		if ( (histo.find(c) == histo.end()) && (code >= 97 && code <= 122) ) {
			histo.insert(std::make_pair(c, 1) ) ;
			count++;
		}

		return IsPangram(s.substr(1), histo, count);
	}

	int factorial(int number ) {
		if (number <= 0)
			return 1;
		return number * factorial(number - 1);
	}

	void AllPermutations(std::string s, std::vector<std::string> &collection, std::string buffer, int max) {

		if (buffer.empty())
			max = s.length();
		else if (buffer.length() == max) {
			std::cout << s << " " << buffer << max << "\n";
			collection.push_back(buffer);
			return ;
		}

		for (int i = 0; i < s.length(); i++) {
			AllPermutations(s.substr(0, i) + s.substr(i + 1), collection, buffer + s[i], max);
		}
	}


	bool PerfectPangram(std::string s, int count, std::map <char,int> mapper) {
		int code;
		char c;

		if (s.empty())
			return true;
		
		c = std::tolower(s.front());
		code = static_cast<int>(c);

		if ( (code >=97 && code <= 122) ) {
			if (mapper.find(c) == mapper.end()) {
				mapper.insert(std::make_pair(c, 1));
				count++;
			} else {
				return false;
			}
		}

		return PerfectPangram(s.substr(1), count + 1, mapper);
	}

	static int bestSingleBuySell_helper_addprices(int& low, int& high, std::vector<std::array<int, 2>> &array) {
		array.push_back({low, high});
		return -1;
	}
	
	static int maxProfit_SinglePurchase(std::vector<std::array<int, 2>> &collection) {
		int profit, max = 0;
		for (auto ele : collection) {
			profit = ele[1] - ele[0];	
			if (profit > max)
				max = profit;
		}
		return max;

	}

	static int maxProfit_ManyPurchase(std::vector<std::array<int, 2>> &collection) {
		int profit, max = 0;
		for (auto ele : collection) {
			profit = ele[1] - ele[0];
				max += profit;
		}
		return max; 
	}

	static void maxProfit_Purchase_TwoTransactions_helper(std::vector<std::array<int, 2>> collection, int &profit, int& max, int depth = 0, int transaction = 2) {
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
			profit += sell-buy; 
			if (collection.size() > 1  )
				maxProfit_Purchase_TwoTransactions_helper(std::vector<std::array<int, 2>>(collection.begin() + i + 1, collection.begin() + collection.size()) , profit, max, depth + 1, transaction);
		}
	}

	static int maxProfit_Purchase_TwoTransactions(std::vector<std::array<int, 2>> &collection) {
		int max = 0;
		int profit = 0;
		maxProfit_Purchase_TwoTransactions_helper(collection, profit, max);
		return max; 
	}

	static int functionSelect(const int& mode, std::vector<std::array<int, 2>> array) {
		int (*funcptr) (std::vector<std::array<int, 2>> &) = nullptr;

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

	int bestSingleBuySell(const std::vector<int> arr, int mode, std::vector<std::array<int, 2>> array, int low, int high ) {
		int currValue;
		
		if (arr.empty())  {
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
		else if ( (low != -1 && currValue > low ))
			high = currValue;

		return bestSingleBuySell( std::vector<int>(arr.begin() + 1, arr.begin() + arr.size()) , mode , array, low, high);
	}

	bool StringsLooselyInterleaved( std::string s0,  std::string s1, const std::string s2 ) {
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

			return StringsLooselyInterleaved(s0,s1, s2.substr(0, index) + s2.substr(index + 1));
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
			} else {
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

	std::string StringEncode(std::string s, int index, int count, char curr, std::string result ) {
		char currentChar = s[index];

		if (currentChar != curr) {
			if (index != 0) 
				result += curr + std::to_string(count);
			if (index >= s.size())
				return result;
			count = 1;
		} else {
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
			for (int i = 0; i < repeatCount ; i++)
				result += c;
		}
		return StringDecode(s, result, index + 1);
	}



}
