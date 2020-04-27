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

bool isPrime(const int& num) {
	for (int i = 2; i <= std::floor(std::sqrt(num)); i++)
		if (num % i == 0) return false;
	return true;
}

namespace chapter1
{
	void setting_swapping() 
	{
		std::string myNumber = "42";
		std::string myName = "Zod";
		auto tmp = myName;
		
		myName = myNumber;
		myNumber = tmp;
	}

	void print_and_count() 
	{
		unsigned count = 0;
		for (unsigned i = 512; i = 4096; i++) {
			if (i % 5 == 0)
				printf("[%d]  %d\n", count++, i);
		}
	}

	void print_neg52_1066()
	{
		for (int i = -52; i <= 1066; i++)
			printf("%d\n",i);
	}

	void mult_of_6()
	{
		unsigned count = 6;
		while (count++ <= 60000) {
			if (count % 6 == 0) {
				printf("%d\n", count);
			}
		}
	}

	void dont_worry_be_happy()
	{
		for (int i = 98; i--; ) {
			printf("good morning!");
		}
	}

	void counting_dojo_way()
	{
		for (int i = 1; i <= 100; i++) {
			if (i % 5 == 0)
				printf("Coding\n");
			if (i % 10 == 0)
				printf("Dojo\n");
		}
	}

	void mult_of_three_but_not_all()
	{
		for (int i = -300; i <= 0; i++) {
			if ((i != -3 && i != -6) && (i % 3 == 0)) {
				printf("[%d]-", i);
			}
		}
	}

	void print_int_with_while()
	{
		unsigned count = 0;
		while (count++ <= 5280) {
			printf("[%d]-", count);
		}
	}

	bool leap_year(unsigned year)
	{ 
		if (year % 400 == 0)
			return true; 

		return ((year % 4 == 0) && (year % 100 != 0));
	}

	void flexible_countdown(int lowNum, int highNum, int mult) 
	{
		for (; highNum >= lowNum ; highNum--) {
			if (highNum % mult == 0) {
				printf("[%d]", highNum);
			}
		}
	}

	void final_countdown(int param1, int param2, int param3, int param4)
	{
		while (param3-- >= param2) {
			if (param3 % param1 == 0 && param3 != param4) {
				printf("[%d]", param3);
			}
		}
	}

	void swap_toward_the_center(std::vector<unsigned> &arr) 
	{
		unsigned tmp;
		for (int i = 0; i < std::ceil(arr.size() / 2 ); i++) {
			tmp = arr[i];
			arr[i] = arr[arr.size() - 1 - i];
			arr[arr.size() - 1 - i] = tmp;
		}
	}

	double math_help(double M, double B)
	{
		return  -B / M;
	}

	void whatHappensToday()
	{
		unsigned num = std::rand() % 100;

		if (num <= 10) {
			printf("VOLCANO!\n", num);
		} else if (num >10 && num <= 25) {
			printf("TSUNAMI!\n", num);
		}	else if (num > 25 && num <= 45) {
			printf("EARHTQUAKE!\n", num);
		} else if (num > 45 && num <= 70) {
			printf("BLIZZARD!\n", num);
		} else if (num > 70 && num <= 100) {
			printf("METOER SHOWER !\n", num);
		}
	}

	void what_really_happened_today()
	{
		unsigned v = std::rand() % 100, t =std::rand() % 100, e = std::rand() % 100, b = std::rand() % 100, m= std::rand() % 100;

		printf("volcano[%d]  tsunami[%d]  earthquake[%d] blizzard[%d] meteor[%d]",
			(v <= 10),
			(t > 10 && t <= 25),
			(e > 25 && e <= 45),
			(b > 45 && b <= 70),
			(m > 70 && m <= 100)
		);
	}

	double soaring_IQ(double IQ)
	{
		for (int acc = 0.1; acc <= 0.98;  acc += 0.1) {
			IQ += acc;
		}
		return IQ;
	}

	std::string letter_grade(unsigned grade)
	{
		if (grade < 60)
			return "Score: " + std::to_string(grade) + " Grade: F";
		if (grade >= 60 && grade < 70)
			return "Score: " + std::to_string(grade) + " Grade:D";
		if (grade >= 70 && grade < 80)
			return "Score: " + std::to_string(grade) + " Grade: C";
		if (grade >= 80 && grade < 90)
			return "Score: " + std::to_string(grade) + " Grade: B";
		if (grade >= 90)
			return "Score: " + std::to_string(grade) + " Grade: A";

	}

	std::string more_acccurate_letter_grade(unsigned grade) {
		std::string grade_data = letter_grade(grade);
		unsigned mod;

		if (grade >= 60 && grade < 95) {
			mod = grade % 10;
		
			if (mod <= 1)
				grade_data += '-';
			if (mod >= 8)
				grade_data += '+';
		}

		return grade_data;
	}
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

namespace chapter17 {

	/*Edge List Methods*/

	template <typename T, typename E_v>
	std::string ELGraph<T, E_v>::AddVertex( T value) {
		std::string key = std::to_string(n++);

		if (vertex_map.count(key) == 0)
			vertex_map.insert({key, value});
		return key;
	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::RemoveVertex(std::string id) {
		EL_Node<E_v> *node = nullptr;
		int prev_index = -1;

		try {
			
			if (!vertex_map.count(id))
				throw "vertex not found";

			// remove vertex 
			vertex_map.erase(id);

			// remove links 
			for (int i = 0; i < el_node_list.size(); ) {
				node = el_node_list[i];
				
				//increment
				if (node->src != id && node->dest != id) {
					prev_index = i++;
				}

				//delete node 
				if (node->dest == id || node->src == id) {
					delete node;
					el_node_list.erase(el_node_list.begin() + i);
				} 

			}
			
			return prev_index != -1;
			
		} catch (...) {
			return false;
		}
	}

	template <typename T, typename E_v>
	std::tuple<T, bool> ELGraph<T, E_v>::GetVertexValue(std::string id) {
		try {
			return { vertex_map.at(id), true };
		} catch (...) {
			return { T(NULL), false };
		}
	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::SetVertexValue(std::string id, int value) {
		try {
			vertex_map.at(id) = value;
			return true;
		} catch (...) {
			return false;
		}
	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::AddEdge(std::string id1, std::string id2, E_v value) {
		try {

			if (vertex_map.count(id1) == 0 || vertex_map.count(id2) == 0)
				throw "vertex not found";
			
			for (auto node : el_node_list) {
				if ( node->src == id1 && node->dest == id2) {
					throw "edge found in graph";
				}
			}

			el_node_list.push_back(el_node(id1, id2, value));

			return true;

		} catch (...) {

			return false;

		}
	}

	template <typename T, typename E_v>
	EL_Node<E_v>* ELGraph<T, E_v>::el_node(std::string src, std::string dest, E_v val) {
		return new EL_Node<E_v>{src, dest, val};
	}

	template <typename T, typename E_v>
	void ELGraph<T, E_v>::RemoveEdges(std::string id) {
		EL_Node<E_v> *node;
		bool hasEdge;

		for (int i = 0; i < el_node_list.size(); ) {
			node = el_node_list[i];
			hasEdge = (node->src == id || node->dest == id);

			if (!hasEdge) {
				i++;
			} else {
				delete node; 
				el_node_list.erase(el_node_list.begin() + i);
			}

		}
	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::RemoveEdge(std::string id1, std::string id2) {
		EL_Node<E_v> *node;

		try {
			
			if (vertex_map.count(id1) == 0 || vertex_map.count(id2) == 0)
				throw "vertex not found";

			for (int i = 0; i < el_node_list.size(); i++) {
				node = el_node_list[i];

				if (node->src == id1 && node->dest == id2) {
					delete node; 
					el_node_list.erase(el_node_list.begin() + i);
					return true;
				}

			}

			throw "edge not found";
		
		} catch (...) {

			return false;
		
		}
		
	}

	template <typename T, typename E_v>
	std::tuple<E_v, bool> ELGraph<T, E_v>::GetEdgeValue(std::string id1, std::string id2) {
		EL_Node<E_v>* node;

		try {

			if (vertex_map.count(id1) == 0 || vertex_map.count(id2) == 0)
				throw "vertex not found";

			for (int i = 0; i < el_node_list.size(); i++) {
				node = el_node_list[i];
				if ( node->src == id1 && node->dest == id2 ) {
					return {node->value, true};
				}
			}

			throw "edge not found";
		
		} catch (...) {

			return {E_v(NULL), false};
		
		}

	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::SetEdgeValue(std::string id1, std::string id2, E_v value) {
		EL_Node<E_v>* node = nullptr;
		bool state = false;

		try {

			if (vertex_map.count(id1) == 0 || vertex_map.count(id2) == 0)
				throw "vertex not found";

			for (int i = 0; i < el_node_list.size(); i++) {
				node = el_node_list[i];
				if (node->src == id1 && node->dest == id2) {
					node->value = value;
					return true;
				}
			}

			throw "edge not found";

		} catch (...) {

			return false;

		}

	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::Adjacent(std::string id1, std::string id2) {
		EL_Node<E_v>* node;

		try {
			if (vertex_map.count(id1) == 0 || vertex_map.count(id2) == 0)
				throw "vertex not found";
			
			for (int i = 0; i < el_node_list.size(); i++) {
				node = el_node_list[i];
				if (node->src == id1 && node->dest == id2) {
					return true;
				}
			}

			throw "edge not found";

		} catch (...) {

			return false;

		}
	}

	template <typename T, typename E_v>
	std::vector<std::string> ELGraph<T, E_v>::Neighbors(std::string id) {
		std::vector<std::string> result; 

		for (auto node : el_node_list) {
			if (node->src == id)
				result.push_back(node->dest);
		}
		return result;
	}

	template class ELGraph<int, int>;
	template class ELGraph<int, std::string>;
	template class ELGraph<std::string, std::string>;
	template class ELGraph<std::string, int>;


	/*Adjacency Map Methods*/
	template <typename T, typename E>
	void AMGraph<T, E>::Grid() {
		for (auto collection : map) {
			std::cout <<  "[  "  << "NAME - " << collection.second->value  << "\t ID  " << collection.second->id << "  ]"<< "\n";
			for (auto it = collection.second->neighbors.begin(); it != collection.second->neighbors.end(); it++) {
				std::cout << "\t dest " << it->first << "\t edge value: " << it->second << "\n";
			}
			printf("\n");
		}
	}

	template <typename T, typename E>
	std::string AMGraph<T, E>::AddVertex(T value) {
		std::string key = std::to_string(n++);
		map.insert({key, am_node(key, value)});	 // insert key/node pair

		if (matrix_en) {
			for (auto rev_it = map.rbegin(); rev_it != map.rend(); rev_it++) {
				for (auto obj : map) {
					if (obj.second->neighbors.count(rev_it->first) == 0) {
						obj.second->neighbors.insert({ rev_it->first, E{} });
					}
				}
			}
		}
		return key;
	}

	template <typename T, typename E>
	bool AMGraph<T, E>::RemoveVertex(std::string id) {

		try {
			
			if (map.count(id) == 0)
				throw "vertex not found";

			// remove links to vertex
			for (auto obj : map) {
				if (map.find(obj.first)->second->neighbors.count(id)) {
					map.find(obj.first)->second->neighbors.erase(id);
				}
			}

			// remove vertex
			delete map.find(id)->second;
			map.erase(id);

			return true;
		} catch (...) {
			return false;
		}
	}

	template<typename T, typename E>
	std::tuple<T, bool> AMGraph<T,E>::GetVertexValue(std::string id) {
		try {

			if (!map.count(id))
				throw "vertex not found";

			return { map.find(id)->second->value ,true };
		
		} catch (...) {

			return { T{}, false };

		}

	}


	template <typename T, typename E>
	bool AMGraph<T, E>::SetVertexValue(std::string id, T value) {
		try {

			if (map.count(id) == 0)
				throw "vertex does not exist";

			map.find(id)->second->value = value;
			
			return true;
		}
		catch (...) {
			return false;
		}
	}

	template <typename T, typename E>
	bool AMGraph<T,E>::AddEdge(std::string id1, std::string id2, E value) {
		try {

			if (id1 == id2)
				throw "vertex cannot move back to itself";

			if (!map.count(id1) || !map.count(id2))
				throw "vertex not found";

			map.find(id1)->second->neighbors.at(id2) = value; // valid route
		
			return true;
		}
		catch (...) {
			return false;
		}
	}

	template <typename T, typename E>
	void AMGraph<T,E>::RemoveEdges(std::string id) {
		if (map.count(id) == 0)
			return; 

		
		for (auto obj: map) {

			// clear direct routes to id
			if (obj.second->neighbors.count(id) ) {
				obj.second->neighbors.at(id) = E{};
			}
			
			//clear undirected routes to id
			if (obj.first == id) {
				for (auto it = map.find(obj.first)->second->neighbors.begin(); it != map.find(obj.first)->second->neighbors.end(); it++)
					it->second = E{};
			}
		}
	}


	template <typename T, typename E>
	bool AMGraph<T, E>::RemoveEdge(std::string id1, std::string id2) {
		try {

			if (!map.count(id1) || !map.count(id2))
				throw "vertex not found";

			map.find(id1)->second->neighbors.at(id2) = E{}; 
		} catch (...) {
			return false;
		}
	}


	template <typename T, typename E>
	std::tuple<E, bool> AMGraph<T, E>::GetEdgeValue(std::string id1, std::string id2) {
		try {

			if (!map.count(id1) || !map.count(id2))
				throw "vertex not found";

			return { map.find(id1)->second->neighbors.at(id2), true };

		} catch (...) {

			return std::make_tuple(E{}, false);

		}

	}


	template <typename T, typename E>
	bool AMGraph<T, E>::SetEdgeValue(std::string id1, std::string id2, E value) {
		try {

			if (!map.count(id1) || !map.count(id2))
				throw "vertex not found";

			map.find(id1)->second->neighbors.at(id2) = value;

			return true;

		} catch (...) {

			return false;

		}

	}

	template <typename T, typename E>
	bool AMGraph<T, E>::Adjacent(std::string id1, std::string id2) {
		try {

			if (map.count(id1) == 0 || map.count(id2) == 0)
				throw "vertex not found";

			if (map.find(id1)->second->neighbors.at(id2) == E{})
				throw "edge not found";
			
			return true;

		} catch (...) {

			return false;

		}
	}

	template <typename T, typename E>
	std::vector<std::string> AMGraph<T,E>::Neighbors(std::string id) {
		std::vector<std::string> result; 

		if (map.count(id) == 0)
			return result;

		for (auto it = map.find(id)->second->neighbors.begin(); it != map.find(id)->second->neighbors.end(); it++) {
			if (it->second != E{}) {
				result.push_back(it->first);
			}
		}
	}

	template class AMGraph<int, int>;
	template class AMGraph<int, std::string>;
	template class AMGraph<std::string, std::string>;
	template class AMGraph<std::string, int>;

	template <typename T, typename E>
	bool ALGraph<T, E>::AddEdge(std::string id1, std::string id2, E value) {
		
		try {

			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";

			if (this->map.find(id1)->second->neighbors.count(id2) == 0)
				this->map.find(id1)->second->neighbors.insert({ id2, E{} }); // new directed edge  
			
				this->map.find(id1)->second->neighbors.at(id2) = value;
			return true;
		}
		catch (...) {
			return false;
		}
	}

	template<typename T, typename E>
	void ALGraph<T, E>::RemoveEdges(std::string id) {
		if (this->map.count(id)) {

			for (auto obj : this->map) {
				if (obj.second->neighbors.count(id))
					obj.second->neighbors.erase(id);
			}

		}
	}




	template<typename T, typename E>
	bool ALGraph<T, E>::RemoveEdge(std::string id1, std::string id2) {
		try {
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex does not exist";
			
			if (this->map.find(id1)->second->neighbors.count(id2) == 0)
				throw "edge does not exist";

			this->map.find(id1)->second->neighbors.erase(id2);
			
			return true;
		}
		catch (...) {
			return false;
		}
	}


	template<typename T, typename E>
	std::tuple<E, bool> ALGraph<T, E>::GetEdgeValue(std::string id1, std::string id2) {
		try {
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex does not exist";

			return { this->map.find(id1)->second->neighbors.at(id2), true };
		}
		catch (...) {
			return { NULL, false };
		}
	}


	template<typename T, typename E>
	bool ALGraph<T,E>::SetEdgeValue(std::string id1, std::string id2, E value) {
		try {
			
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex does not exist";
			
			this->map.find(id1)->second->neighbors.at(id2) = value;
			return true;

		} catch (...) {
			
			return false;
		
		}
	}

	template<typename T, typename E>
	bool ALGraph<T, E>::Adjacent(std::string id1, std::string id2) {
		try {
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex does not exist";
			return this->map.find(id1)->second->neighbors.count(id2);
		} catch (...) {
			return false;
		}
	}

	template<typename T, typename E>
	std::vector<std::string> ALGraph<T,E>::Neighbors(std::string id) {
		std::vector<std::string> result;

		if (this->map.count(id) == 0)
			return result;

		for (auto it = this->map.find(id)->second->neighbors.begin(); it != this->map.find(id)->second->neighbors.end(); it++)
			result.push_back(it->first);

		return result;
	}

	template <typename T, typename E>
	std::vector <std::string> ALGraph<T, E>::EasyToGetThere() {
		int in_count, out_count; 
		std::string to_id, from_id;
		std::vector<std::string> IDs;
		std::vector<std::string > result;

		for (auto obj: this->map) {

			in_count = 0;
			out_count = 0;
			from_id = obj.first;

			for (auto obj_neighbor: obj.second->neighbors) {
				to_id = obj_neighbor.first;
				in_count++;
				out_count += this->map.find(from_id)->second->neighbors.count(to_id);

				if (in_count > out_count)
					result.push_back(from_id);
			}

		}

		return result;

	}

	template <typename T, typename E>
	bool ALGraph<T, E>::IsDAG(void *ptr) {
		std::map<std::string, std::string> visited;
		std::string curr_tail;

		try {
			for (auto from_obj : this->map) {
				if (from_obj.second->neighbors.size() > 1) {		// tx edge count > 1 
					throw "more than one edge from vertex";
				} else if (from_obj.second->neighbors.size() == 1) {		// tx edge count  == 1
					visited.insert({ from_obj.second->neighbors.begin()->first , from_obj.first}); 
				} else if (from_obj.second->neighbors.size() == 0) { // no tx edges 
					if (curr_tail.length() == 0) {
						visited.insert({ from_obj.first, "" });
						curr_tail = from_obj.first;
					} else {
						throw "multiple tail nodes";
					}
				}
			}

			//back propagation
			if (ptr) {
				while (curr_tail.length()) {
					((std::vector<std::string>*) ptr)->insert(((std::vector<std::string>*) ptr)->begin(), curr_tail);
					curr_tail = visited.at(curr_tail);
				}
			}
			
			return true;

		} catch (...) {

			return false;
		}
	
	}

	template <typename T, typename E>
	std::vector<std::string>  ALGraph<T,E>::DAGToArray() {
		std::vector<std::string> result;
		IsDAG(&result);
		return result;
	}

	template class ALGraph<int, int>;
	template class ALGraph<int, std::string>;
	template class ALGraph<std::string, std::string>;
	template class ALGraph<std::string, int>;

	template <typename T, typename E>
	bool ALGraph_UnDir<T, E>::AddEdge(std::string id1, std::string id2, E value) {
		try {

			if (id1 == id2)
				throw "vertex cannot point to vertex";
			if ( this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";
			if (value == E{})
				throw "invalid edge value";
			
			if (this->map.find(id1)->second->neighbors.count(id2) == 0) {
				this->map.find(id1)->second->neighbors.insert({ id2, E{} });	// 1 -> 2 
				this->map.find(id2)->second->neighbors.insert({ id1, E{} });	// 2 -> 1
			}

			this->map.find(id1)->second->neighbors.at(id2) = value;
			this->map.find(id2)->second->neighbors.at(id1) = value;

			return true;
		
			} catch (...) {
			
			return false;

		}

	}

	template <typename T, typename E>
	void ALGraph_UnDir<T, E> ::RemoveEdges (std::string id) {
		// remove edges to 
		for (auto obj : this->map) {
			if (obj.second->neighbors.count(id)) {
				obj.second->neighbors.erase(id);
			}
		}

		// remove edges from 
		this->map.find(id)->second->neighbors.clear();
	}


	template <typename T, typename E>
	bool ALGraph_UnDir<T, E> ::RemoveEdge(std::string id1, std::string id2) {
		try {
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";
			if (this->map.find(id1)->second->neighbors.count(id2)) {
				this->map.find(id1)->second->neighbors.erase(id2);
				this->map.find(id2)->second->neighbors.erase(id1);
			}
			return true;
		} catch (...) {
			return false;
		}
	}

	template <typename T, typename E>
	std::tuple<E, bool> ALGraph_UnDir<T,E>::GetEdgeValue(std::string id1, std::string id2) {
		try {
			
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";
			
			if (this->map.find(id1)->second->neighbors.count(id2) == 0)
				throw "edge not found";

			return  { this->map.find(id1)->second->neighbors.at(id2), true };

		} catch (...) {

			return  { E{}, false };

		}

	}

	template <typename T, typename E>
	bool ALGraph_UnDir<T, E>::SetEdgeValue(std::string id1, std::string id2, E value) {
		try {

			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";

			if (this->map.find(id1)->second->neighbors.count(id2) == 0)
				throw "edge not found";

			this->map.find(id1)->second->neighbors.at(id2) = value;

			return  true;

		} catch (...) {

			return  false;

		}

	}

	template <typename T, typename E>
	bool ALGraph_UnDir<T, E>::Adjacent(std::string id1, std::string id2) {
		try {

			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";

			if (this->map.find(id1)->second->neighbors.count(id2) == 0)
				throw "edge not found";

			return true;

		} catch (...) {

			return  false;

		}
	}

	template <typename T, typename E>
	std::vector<std::string> ALGraph_UnDir<T, E>::Neighbors(std::string id) {
		std::vector<std::string> result;

		if (this->map.count(id) == 0)
			return result;
		
		for (auto it = this->map.find(id)->second->neighbors.begin(); it != this->map.find(id)->second->neighbors.end(); it++) {
			result.push_back(it->first);
		}
		return result;
	}

	template <typename T, typename E>
	bool ALGraph_UnDir<T, E>::SomeoneOntheInside (std::string my_id, std::vector<std::string> employees_ids) {
		std::map<std::string, bool> visited;
		std::vector< AM_Node_Vertex<T, E>*> stack;
		AM_Node_Vertex<T, E> *node = nullptr;
		std::string ERROR_MSG = "no friends at company";
		std::string curr_id, manager_id = "10";

		try {

			for (auto id: employees_ids) {
				//stack.clear();

				if (this->map.count(id) == 0) // employee not in my social network
					continue; 

				if (this->map.find(id)->second->neighbors.count(my_id) == 0)  // employee is not my friend 
					continue;

				if (visited.count(id) != 0) // already visited (id) vertex
					continue; 

				visited.insert({ id, true });		// mark visited employee-id


				// search for #10 aka Yoda part of innner circle
				stack.push_back(this->map.find(id)->second);	// add employee-id (i.e. node) to stack
				
				while (stack.size()) {

					node = stack.front();
					std::cout << node->id << " visited new " << "\n";
					stack.erase(stack.begin());

					if (node->id == manager_id) // found "employee"
						return true;


					for (auto obj : node->neighbors) {
						curr_id = obj.first;
						if (visited.count(curr_id) == 0) {	// if not visited add to front of stack
							visited.insert({ curr_id, true });		// mark visited employee-id
							stack.insert(stack.begin(), this->map.find(curr_id)->second);
						}
					}
				}
			}
			throw ERROR_MSG;
		} catch (...) {
			return false;
		}
	}

	template <typename T, typename E>
	std::string ALGraph_UnDir<T, E>::SomeoneOntheInside(std::vector<std::string> employees_ids) {
		
		// search manager id - using two points of reference  

		std::map <std::string, bool> visited;
		std::vector<AM_Node_Vertex<T,E>*> stack_A, stack_B;
		AM_Node_Vertex<T,E> *node_A = nullptr, *node_B = nullptr;
		std::string id_upper, id_lower, curr_id;

		std::string  manager_id = "10";
		std::string ERROR_MSG = "no friends at company";
		int  ptrA = 0, ptrB = employees_ids.size() - 1;

		try {
				
			while (ptrB >= ptrA) {
				id_upper = employees_ids[ptrA++];
				id_lower = employees_ids[ptrB--];

				if (this->map.count(id_upper) ) { // id in graph 
					stack_A.push_back(this->map.find(id_upper)->second);
					visited.insert({ id_upper, true });
				}

				if (this->map.count(id_lower)) {	// id in graph {
					stack_B.push_back(this->map.find(id_lower)->second);
					visited.insert({ id_lower, true });
				}

				while (stack_A.size() || stack_B.size()) {
					node_B = nullptr;
					node_A = nullptr;

					// insert vertex to stack 
					// ..upper
					if (stack_A.size()) {
						node_A = stack_A.front();
						stack_A.erase(stack_A.begin());
					}

					//.. lower
					if (stack_B.size()) {
						node_B = stack_B.front();
						stack_B.erase(stack_B.begin());
					}

					// insert 'non-visited' neighbors of vertcies 
					//..A
					if (node_A) {
						for (auto obj: node_A->neighbors) {
							curr_id = obj.first;
							if (visited.count(curr_id) == 0) {
								visited.insert({ curr_id, true });				// non- visited employee--vertex-id
								if (curr_id == manager_id) {
									throw  "employee " + node_A->id + "\ will recommend you to manager \t \t \n";
								}
								stack_A.insert(stack_A.begin(), this->map.find(curr_id)->second);
							}
						}
					}

					// insert 'non-visited' neighbors of vertcies 
					//..B
					if (node_B) {
						for (auto obj : node_B->neighbors) {
							curr_id = obj.first;
							if (visited.count(curr_id) == 0) {
								visited.insert({ curr_id, true });			// non- visited employee--vertex-id
								if (curr_id == manager_id) {
									throw  "employee " + node_B->id + "\ will recommend you to manager \t \t \n";
								}
								stack_B.insert(stack_B.begin(), this->map.find(curr_id)->second);
							}
						}
					}
					
				}

			}
	
			throw ERROR_MSG;

		} catch (const std::string &msg) {

			return msg;
		
		}

	}

	template <typename T, typename E>
	void  ALGraph_UnDir<T, E>::VertexIsReachable(std::string id1, std::string id2, std::vector<std::string> &path_list, std::map<std::string, bool>& visited, AM_Node_Vertex<T,E> * node ) {

		if (!node) {
			node = this->map.find(id1)->second;
			path_list.push_back(node->id);
		}

		if (visited.count(node->id) || node->id == id2)
			return; 

		visited.insert({ node->id , true });

		for (auto obj : node->neighbors) {
			if (visited.count(obj.first) == 0) {
				path_list.push_back(obj.first);
				VertexIsReachable(id1, id2, path_list, visited, this->map.find(obj.first)->second);

				if (path_list.back() != id2)
					path_list.pop_back();
			}
		}
	}

	template <typename T, typename E>
	std::vector<std::string>  ALGraph_UnDir<T, E>::VertexIsReachable(const std::string &id1, const std::string &id2) {
		std::vector<std::string> pathList; 
		std::map<std::string, bool> visited;
	
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";
			
			 VertexIsReachable(id1, id2, pathList, visited);

			return pathList;
	}


	template <typename T, typename E>
	void ALGraph_UnDir<T, E>::AllPaths(const std::string& target, std::vector<std::vector<std::string>> &paths, std::vector<std::string> path, std::set<std::string>& visited, AM_Node_Vertex<T, E>* node) {
		
		if (node->id == target) { // found target
			printf(" \t how   %s \n", node->id.c_str());
			paths.push_back(path);
			return;
		}

		if (visited.count(node->id))
			return; 

		visited.insert(node->id);

		for (auto obj: node->neighbors) {
			if (visited.count(obj.first) == 0) {
				path.push_back(obj.first);
				AllPaths(target, paths, path, visited, this->map.find(obj.first)->second);
				path.pop_back();
			}
		}

	}


	template <typename T, typename E>
	std::vector<std::vector<std::string>> ALGraph_UnDir<T, E>::AllPaths(const std::string& id1, const std::string& id2) {
		std::vector<std::vector<std::string>> paths;
		std::vector<std::string> currPath;
		std::set<std::string> visited;

		if (this->map.count(id1) == 0)
			return paths;

		currPath.push_back(id1);

		AllPaths(id2, paths, currPath, visited, this->map.find(id1)->second);
		
		return paths;
	}

	template <typename T, typename E>
	std::vector<std::string> ALGraph_UnDir<T,E>::ShortestPath(const std::string id1, const std::string id2) {
		std::vector<std::string> path;
		AM_Node_Vertex<T, E>* node = nullptr; 
		std::vector< AM_Node_Vertex<T, E>*> queue;
		std::map < std::string, std::string> visited;
		std::string vertexID;


		if (this->map.count(id1) && this->map.count(id2)) {
			node = this->map.find(id1)->second;
			queue.push_back(node);
			visited.insert({ node->id, "" });

			while (queue.size()) {
				node = queue.front();
				queue.erase(queue.begin());

				if (node->id == id2) {
					vertexID = node->id;
					break;
				}

				for (auto obj : node->neighbors) {
					if (visited.count(obj.first) == 0) {
						visited.insert({ obj.first, node->id });
						queue.push_back(this->map.find(obj.first)->second);
					}
				}

			}

			while (vertexID.length()) {  // backtrace to vertex-id;
				path.push_back(vertexID);
				vertexID =  visited.at(vertexID);
			}

		}
	
		return path;
	}

	template <typename T, typename E> 
	std::vector<std::string> ALGraph_UnDir<T,E>::GimmieNSteps(const std::string id1, const std::string id2, int n ) {
		std::map<std::string, int> visited;
		AM_Node_Vertex<T, E>* node = nullptr;
		std::vector< AM_Node_Vertex<T, E>*> queue;
		std::vector<std::string> IDs;

		if (!(this->map.count(id1) && this->map.count(id2) )) 
			return IDs;

		node = this->map.find(id1)->second;
		visited.insert({ node->id, 0 });
		queue.push_back(node);

		while (queue.size()) {
			node = queue.front();
			queue.erase(queue.begin());

			if (visited.at(node->id) <= n)
				IDs.push_back(node->id);

			for (auto obj : node->neighbors) {
				if (visited.count(obj.first) == 0) {
					visited.insert({ obj.first, visited.at(node->id) + 1 });
					queue.push_back(this->map.find(obj.first)->second);
				}
			}
		}
		
			return IDs;
	}


	template class ALGraph_UnDir<int, int>;
	template class ALGraph_UnDir<int, std::string>;
	template class ALGraph_UnDir<std::string, std::string>;
	template class ALGraph_UnDir<std::string, int>;

	void SocialNetwork_ALGraph_UnDir_Test() {

		ALGraph_UnDir<std::string, int> graph;    

		{
			graph.AddVertex("Me");	// 0
			graph.AddVertex("A");		// 1
			graph.AddVertex("B");		// 2
			graph.AddVertex("C");		// 3
			graph.AddVertex("F");		// 4

			graph.AddVertex("R");		// 5
			graph.AddVertex("Q");		// 6
			graph.AddVertex("T");		// 7
			graph.AddVertex("Z");		// 8
			graph.AddVertex("O");		// 9

			graph.AddVertex("manager"); // 10  

			graph.AddEdge("0", "1", 1);

			graph.AddEdge("1", "2", 1);
			graph.AddEdge("1", "3", 1);
			graph.AddEdge("1", "4", 1);
			graph.AddEdge("1", "5", 1);

			graph.AddEdge("5", "6", 1);
			graph.AddEdge("5", "7", 1);
			graph.AddEdge("5", "8", 1);
			graph.AddEdge("5", "9", 1);

			graph.AddEdge("9", "10", 1);

			std::cout << graph.SomeoneOntheInside({"1","2","3","4","5","6"}) << '\n';  // found manager
			
			ALGraph<std::string, int> dir_graph;   

			dir_graph.AddVertex("Me");
			dir_graph.AddVertex("a");
			dir_graph.AddVertex("b");
			dir_graph.AddVertex("c");

			dir_graph.AddEdge("0", "1", 1);
			dir_graph.AddEdge("1", "2", 1);
			dir_graph.AddEdge("2", "3", 1);

			dir_graph.IsDAG();  // true
			for (auto x : dir_graph.DAGToArray()) { // print DAG
				std::cout << x << "\t";
			}
		}

	}

}

namespace chapter18 {
	//

	std::string  Octal::dec_to_oct_string(int num) {
		std::string result = "0o_";
		while (num > 0) {
			result.insert(result.begin() + 3, static_cast<char>( 48 + (num % system)) );
			num = num / system ;
		}
		return result;
	
	}

	std::string Octal::oct_to_dec_string(std::string str) {
		std::string head = "0o";
		int data = 0; 
		int pos;
		int power;
		try {
			
			if (str.find(head) != std::string::npos) 
				pos = str.find(head) + 2;
			
			for (char ch : str.substr(pos, str.length())) {
				if (!std::isdigit(ch)) {
					throw " not a number";
				}
			}

			power = str.length() - pos - 1;

			for (int i = pos; i < str.length(); i++ ) {
				data += (static_cast<int>(str[i]) - 48) * std::pow(system, power--);
			}

			return  std::to_string(data);

		} catch (...) {

			return "";
		}

	}

	std::string Hexadecimal::dec_to_hex_string(int num, bool uppercase) {
		std::string result = "0x";
		int hex_value;
		char ch;

		try {
			while (num > 0) {
				hex_value = (num % system);
				switch (hex_value) {
				case 10:
					ch = uppercase ? 'A' : 'a';
					break;
				case 11:
					ch = uppercase ? 'B' : 'b';
					break;
				case 12:
					ch = uppercase ? 'C' : 'c';
					break;
				case 13:
					ch = uppercase ? 'D' : 'd';
					break;
				case 14:
					ch = uppercase ? 'E' : 'e';
					break;
				case 15:
					ch = uppercase ? 'F' : 'f';
					break;
				default:
					ch = static_cast<char>(48 + hex_value);
				}
				
				result.insert(result.begin() + 2, ch);
				num /= system;
			}
			return result;
		} catch (...) {
			return "";
		}
	}


	std::string Hexadecimal::hex_to_dec_string(std::string str) {
		std::string headers[] = { "0x", "0X" };
		std::string hex_chars = "abcdefABCDEF0123456789";
		int pos = 0;
		int data = 0, power = 0, buffer = 0;
		std::string result; 
		char ch;

		try {
			
			// search for headers 
			for (auto header : headers) {
				if (str.find(header) != std::string::npos) {
					pos += 2;
				}
			}
			
			//validate string input
			for (int i = pos; i < str.length(); i++) {
				if (hex_chars.find(str[i]) == std::string::npos)
					throw "error in hexadecimal value";
			}


			power = str.length() - pos - 1;
			
			//compute
			for ( ; pos < str.length(); pos++) {
				ch = str[pos];

				if (ch == 'A' || ch =='a')
					buffer = 10;
				else if (ch == 'B' || ch == 'b')
					buffer = 11;
				else if (ch == 'C' || ch == 'c')
					buffer = 12;
				else if (ch == 'D' || ch == 'd')
					buffer = 13;
				else if (ch == 'E' || ch == 'e')
					buffer = 14;
				else if (ch == 'F' || ch == 'f')
					buffer = 15;
				else
					buffer = static_cast<int>(ch) - 48;
				
				data += buffer * std::pow(system, power--);
			}

			return std::to_string(data);

		} catch (...) {
			
			return "";
		
		}

	}

	std::string Binary::dec_to_bin_string(int num) {
		std::string result = "0b";
		int counter = 0; 
		while (num > 0) {
			result.insert(result.begin() + 2, static_cast<char>(48 + (num % system)));
			num /= system;
		}
		return result;
	}

	std::string Binary::bin_to_dec_string(std::string str) {
		std::string header = "0b";
		int pos = 0, power = 0, data = 0; 
		
		try {
			
			if (str.find(header) != std::string::npos)
				pos += 2;
			
			for (int i = pos; i < str.length(); i++) {
				if (str[i] != '1' && str[i] != '0')
					throw "binary string not valid";
			}

			power = str.length() - pos - 1;

			for ( ; pos < str.length(); pos++) {
				data += (static_cast<int>(str[pos]) - 48) * std::pow(system, power--);
			}

			return std::to_string(data);
		
		} catch (...) {
			
			return "";
		
		}
	
	}

	std::vector<std::string> ReOrderWordFragments(std::vector<std::string> words) {
		unsigned  word_length, index = 0;
		std::vector<std::string> arr = words; 
		unsigned ;
		char earliestChar = 'A';
		int comp_substring_value;
		int comp_char_value;

		try {
			
			word_length = words[0].length();

			while (index < word_length) { 

				for (int n = 0; n < words.size(); n++) {

					if (index == 0)
						earliestChar = 'A';
					
					if (words[n][index] == '?') 
						words[n][index] = earliestChar;
					
					// possible move word up list to order 
					for (int i = n; i > 0 && n > 0; i--) {
						comp_substring_value = words[i].substr(0, index + 1).compare(words[i - 1].substr(0, index + 1));
						comp_char_value = std::string(1, words[i][index]).compare(std::string(1, words[i - 1][index]));
					
						if (comp_substring_value == -1 && comp_char_value == -1)  // x[n] < x[n-1]
							std::swap(words[i], words[i - 1]);
						if (comp_substring_value == 1 && comp_char_value == -1) 
							throw " ordering is impossible";
						if (comp_substring_value == -1 && comp_char_value == 1) 
							throw " ordering is impossible";
						
						earliestChar = words[i][index];
					}
				}
				index++;
			}

			for (auto w : words) {
				printf("%s \n", w.c_str());
			}
			return words;
		} catch (...) {
			return {};
		}

	}

	unsigned Bits::count_set_bits(int number) {
		unsigned count = 0;
		unsigned const_two = 2;

		while (number > 0) {
			count += number % const_two;
			number /= const_two;
		}
		return count;
	}

	unsigned Bits::reverse_bits(unsigned num_32) {
		unsigned data = 0;
		unsigned bit, pos = 0;

		for (unsigned i = std::ceil(std::log2(num_32)); i--; ) {
			bit = (num_32 & (1 << i)) >> i; // find bit and move to right
			data += (bit << pos++);
		}
		return data;
	}

	unsigned Bits::encodeByte32(std::array<unsigned, 4> bytes) {
		unsigned result = 0 ;
		for (int i = 1; i <= bytes.size(); i++) {
			result += (bytes[i- 1] << (32 - 8 * i));
		}
		return result;
	}

	std::array<unsigned, 4> Bits::decodeByte32(unsigned num_32) {
		unsigned mask = UINT8_MAX;
		std::array<unsigned, 4> result; 
		uint8_t pos = 0, shift;

		for (int i = 4; i--; ) {
			shift = 8 * i;
			result[pos++] = ((mask << shift) & num_32) >> shift;
		}

		//for (auto byte : result) {
		//	std::cout << Hexadecimal().dec_to_hex_string(byte) << '\n';
		//}
		return result;
	}


	bool ByteArray::set(const unsigned& index, const unsigned& value) {
		unsigned lane, dword;
		std::array<unsigned, 4> bytes;

		try {

			if (index >= bytes_per_lane * dword_lanes)
				throw "invalid index";

			lane = std::floor(index / dword_lanes);

			dword = array[lane]; // get 32 bit word

			bytes = Bits().decodeByte32(dword); // get 32 bit byte array
			bytes[index % bytes_per_lane] = value; // update bytes
			array[lane] = Bits().encodeByte32(bytes);//update dword lane


			return true;
		} catch (...) {

			return false;
		}
	}

	

	std::tuple<unsigned, bool> ByteArray::get(const unsigned& index) {
		unsigned lane; 
		std::array<unsigned, 4> bytes;

		try {
			if (index >= bytes_per_lane * dword_lanes)
				throw "invalid index";

			lane = std::floor(index / dword_lanes);
			bytes = Bits().decodeByte32(array[lane]);
			return { bytes[index % bytes_per_lane], true };
		} catch (...) {
			return { NULL, false };
		}
	}

	void ByteArray::printByteArray() {
		for (auto dword : array) {
			printf("[ ");
			for (auto byte : Bits().decodeByte32(dword)) {
				printf("\t%d", byte);
			}
			printf("] \n");
		}

	}

	unsigned Bits::encode_bit_num(bool bit, unsigned bit_pos, unsigned value) {
	
		try {

			if (bit_pos >= 32)
				throw "invalid bit position";
			
			if (bit) {
				value =  value | (1 << bit_pos);
			} else if (!bit) {
				value = value & ~(value & (1 << bit_pos));
			}

			return value;

		} catch (...) {

			return value;

		}

	}

	unsigned Bits::decode_bit_num(unsigned bit_pos, unsigned value) {

		try {

			if (bit_pos >= 32)
				throw "invalid bit position";

			return (value & (1 << bit_pos)) >>  bit_pos;

		} catch (...) {

			return -1;

		}
	
	}

	bool BitArray::set(unsigned index, bool val) {
		try {
			if (index >= 32)
				throw "invalid bit position";

			if (val)
				data = (1 << index) | data;

			if (!val)
				data = data & ~(1 << index);

			std::cout << Hexadecimal().dec_to_hex_string(data) << '\n';
			return true;
		} catch (...) {
			return false;
		}
	}

	bool BitArray::get(unsigned index) {
		return true;
	}

	void RadixSort_remove(std::vector<std::vector<unsigned>*> &array,const unsigned &bit_pos, const unsigned& target) {
		std::vector<unsigned>* lane; 

	
	}
	void RadixSort(std::vector<unsigned>& array) {

		const unsigned SIZE = 32;
		unsigned pos;
		std::vector<std::vector<unsigned>*> garage;
		std::vector<unsigned> *lane;
		unsigned len_curr_lane;
		unsigned element; 

		for (int i = 0; i < 32; i++) {
			garage.push_back(new std::vector<unsigned>);
			for (int k = 0; k < array.size() && i == 0 ; k++) {
				garage[i]->push_back(array[k]);
			}
		}

		for (int curr_bit = 0; curr_bit < SIZE; curr_bit++) {  // N

			for (int lane_index = 0; lane_index < curr_bit + 1; lane_index++) {  // range of lanes
				lane = garage[lane_index];
				len_curr_lane = lane->size();
				
				for (int i = 0; i < len_curr_lane; i++) {  //subset of lane elements 
					element = lane->front();
					lane->erase(lane->begin());
					
					if (element & (1 << curr_bit))
						garage[curr_bit]->push_back(element);
					else 
						lane->push_back(element);
				}
			}
		}

		pos = pos = array.size() - 1;

		for (int n = 32; n--;) { // reverse  iterator -overrwrite input array
			lane = garage[n];
			for (int i = lane->size(); i--;)
				array[pos--] = lane->at(i);
		}
	
		for (int i = pos; i > 0; i--)  // insert zeros
			array[pos--] = 0;
		
		for (auto ele : array) {
			std::cout << ele << '\n';
		}

		//delete dyn vectors
		for (auto ele : garage)
			delete ele;
	}


	 void Sprinklers::randomToggleBit() {
		 std::string tmp;
		 while (true) {
			 std::this_thread::sleep_for(std::chrono::seconds(1));
			 sprinkler_system = sprinkler_system & ~(1 << on_pos);
			 on_pos = std::rand() % 28;
			 sprinkler_system = sprinkler_system | ( 1 <<  on_pos);
			 std::cout << *this;
		 }
	}
	 
	void Sprinklers::tasks_run() {
		std::thread th1( &Sprinklers::randomToggleBit, this);
		th1.join();
	}

	std::ostream& operator <<(std::ostream& out, const Sprinklers& obj) {
		for (int i = 0; i < obj.sprinkler_count; i++) {
			if (! (obj.sprinkler_system & (1 << i)) )
				out << ("|_");
			else
				out << ("|^");
		}
		out << ("|");

		printf("\n");
		return out;
	}

	std::string LEDEncoding::led_to_numeral(uint8_t byte) {
		std::string code;
		try {
			
			for (int i = 0; i < 8; i++) {
				if (byte % 2) {
					code += static_cast<char>(48 + i);
				}
			}
			
			if (numeral_code.count(code))
				return static_cast<char>(48 + numeral_code.at(code)) + "";
			
			throw "invalid code";
		} catch (...) {
			return "";
		}
	}

	std::array<unsigned, 5> LEDEncoding::int_to_led(unsigned value) {
		std::array<unsigned, 5> result; 
		unsigned tmp;
		for (int i = 0; i < 5; i++) {
			result[i] = 0;
			for (auto obj : numeral_code) {
				if (value % 10 == obj.second) {
					for (auto c : obj.first) {
						result[i] |= (1 <<  (static_cast<int>(c) - 48 ));
					}
					break;
				}
			}
			value /= 10;
		}
		return result;
	}
}

namespace chapter19 {

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








