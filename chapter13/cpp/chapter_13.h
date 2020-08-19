#include <vector>
#include <iostream>

std::ostream& operator << (std::ostream &out, const std::vector<int> &vect);
std::vector<int> interleave_arrays (std::vector<int> a, std::vector<int> b);