#include <vector>
#include <iostream>

std::ostream& operator << (std::ostream &out, const std::vector<int> &vect);
std::vector<int> interleaveArrays (std::vector<int> a, std::vector<int> b);
std::vector<int> intersect_sorted_arrays(std::vector<int> a, std::vector<int> b);
std::vector<int> union_sorted_array (std::vector<int> a, std::vector<int> b , bool (*cb)(int, std::vector<int>, std::vector<int>, int&, int&) = NULL );
bool function_ptr (int target, std::vector<int> a, std::vector<int> b, int &aa, int &bb);