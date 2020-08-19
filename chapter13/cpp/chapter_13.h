#include <vector>
#include <iostream>

std::ostream& operator << (std::ostream &out, const std::vector<int> &vect);
std::vector<int> interleaveArrays (std::vector<int> a, std::vector<int> b);
std::vector<int> intersect_sorted_arrays(std::vector<int> a, std::vector<int> b);
