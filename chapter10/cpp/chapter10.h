#include <string>
#include <vector>

std::string  rotateString(std::string str, unsigned n);
bool ionisRotate(std::string &str1, std::string str2);

void censor(std::string &str, std::vector<std::string> naughty_list);
bool geneticMarker (const std::string &str, const std::vector<std::string> &collection, unsigned index = 0);

std::vector<std::string> optimumSequence(std::vector<std::string> collection);
void optimumSSequenceHelper(  std::vector<std::string> collection, std::vector<std::string> buffer, std::vector<std::string> &result,  unsigned col = 0);
void optimumSequenceSortColumn(std::vector<std::string> &collection, std::vector<std::string> &buffer, unsigned col);
bool optimumSequenceIsSorted(std::vector<std::string> buffer, unsigned col);
void optimumDisplay(std::vector<std::string> buffer);