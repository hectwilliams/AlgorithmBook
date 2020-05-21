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

#ifndef CHAPTER10_H
#define CHAPTER10_H


namespace chapter10 {

	std::vector<std::string> StringToWordArray(std::string s, bool handlePunctuation = false);
	static void StringToWordArray_helper_handlePunctuation(std::string& s);
	std::string LongestWord(const std::string& s);
	std::string ReverseWordOrder(std::string s);
	std::string UniqueWords(const std::string& message, bool ignorePunctuation = false);
	std::string RotateString(std::string str, const int& count);
	bool isRotation(std::string s1, std::string s2);
	std::string Censor(std::string s, std::vector<std::string> list);
	std::string BadCharacters(std::string s, const char c[]);
	bool GeneticMarker(std::vector<std::string> collection, std::string marker);
	std::string Dedupe(const std::string s);
	int IndexFirstUniqueLetter(const std::string s);
	std::string NumToString(int number);
	std::string NumToString(double fraction);

	const std::map<int, std::string> illions = {
		{3, "thousand"},
		{6, "million"},
		{9, "billion"},
		{12, "trillion"},
		{15, "quadrillion"},
		{18, "quintillion"}
	};

	const  std::map<int, std::array<std::string, 3>> NumToTextMap = {
		{0, {"zero",	"ten"} },
		{1, {"one",		"eleven"} },
		{2, {"two",		"twelve",		"twenty"} },
		{3, {"three",	"thirteen",		"thirty"} },
		{4, {"four",	"fourteen",		"fourty"} },
		{5, {"five",	"fifteen",		"fifty"} },
		{6, {"six",		"sixteen",		"sixty"} },
		{7, {"seven",	"seventeen",	"seventy"} },
		{8, {"eight",	"eighteen",		"eighty"} },
		{9, {"nine" ,	"nineteen",		"ninety"} }
	};

	std::string NumToText(int number, int index3 = -1, std::string s = "", int depth = 0, std::vector<std::string>  result = {});
	bool isPermutation(std::string s1, std::string s2, const char index = 0);
	bool IsPangram(std::string s, std::map<char, int> histo = {}, int count = 0);
	void AllPermutations(std::string s, std::vector<std::string>& collection, std::string buffer = "", int max = 0);
	bool PerfectPangram(std::string s, int count = 0, std::map<char, int> map = {});
	int bestSingleBuySell(const std::vector<int> arr, int mode = 0, std::vector<std::array<int, 2>> array = {}, int low = -1, int high = -1);
	bool StringsLooselyInterleaved(std::string s0, std::string s1, const std::string s2);
	void allStringsLooselyInterleaved(std::string str1, std::string str2, int index = 0, std::vector<std::string> list = {});
	int RemoveOneMakePalindrome(std::string s, int index = 0);
	char MakeStringPalindrome(std::string s, int index = 0);
	std::string StringEncode(std::string s, int index = 0, int count = 0, char curr = '\0', std::string result = "");
	std::string StringDecode(std::string s, std::string result = "", int index = 0);

}

#endif