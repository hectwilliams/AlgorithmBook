#include <string>
#include <vector>
#include <map>
#include <array>

std::string  rotateString(std::string str, unsigned n);
bool ionisRotate(std::string &str1, std::string str2);

void censor(std::string &str, std::vector<std::string> naughty_list);
bool geneticMarker (const std::string &str, const std::vector<std::string> &collection, unsigned index = 0);

std::vector<std::string> optimumSequence(std::vector<std::string> collection);
void optimumSSequenceHelper(  std::vector<std::string> collection, std::vector<std::string> buffer, std::vector<std::string> &result,  unsigned col = 0);
void optimumSequenceSortColumn(std::vector<std::string> &collection, std::vector<std::string> &buffer, unsigned col);
bool optimumSequenceIsSorted(std::vector<std::string> buffer, unsigned col);
void optimumDisplay(std::vector<std::string> buffer);

 std::string DedupeStr(const std::string &str);
std::string DedupeTest();

int firstUniqueLetter(const std::string &str, int index = 0);

std::string uniqueLetters (const std::string &str, int index = 0);

std::string numToString(double num, int n = 0);

bool numToStringZeros(double num, int size = 0);

std::string numToText();

std::string numToTextParserWhole( std::string data ,int level = 0);
std::string numToTextTranslate(std::string data, unsigned level);
std::string numToTextParserDecimal( std::string data, int index = 0);
std::string digitToText(int digit, bool en_zero = false);
bool isPermtutaoin(std::string str,const std::string &perm, std::string &&buffer = "");

int isPangram_helper(std::string str, std::map<char, bool> mapper = std::map<char, bool>());
bool isPangram(std::string str);


std::vector<std::string> stringPermutations(const std::string &str);
void stringPermutationsHelper(std::string str, const int &size, std::vector<std::string> &collection, std::string buffer = "");
int perfectPangram_helper(std::string str, std::map<char, bool> &alpha );
bool perfectPangram (std::string str);

void bestSingleBuySell (int &value, std::vector<int> collection, std::vector<int> buffer = std::vector<int>() );

void bestSingleBuySell_2(int &value,   std::vector< std::vector<int> >  &buffer_list , std::vector<int> collection, std::vector<int> buffer =  std::vector<int>() );

bool stringLooselyInterleaved(std::string a, std::string b, std::string c, std::string buffer = "");

int makePalindromeRemove(std::string str, int index = -1);

char makePalindromeAdd( std::string str, int index = 0);

std::string encodeString (std::string str, std::string buffer ="", int count = 0, char active_char = ' ');

std::string decodeString(std::string str, std::string buffer = "");

std::string shortenerString(std::string &str, const  int &expected_length, int mode = 0 );
