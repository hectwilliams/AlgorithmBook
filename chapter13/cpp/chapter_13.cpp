#include "chapter_13.h"

std::ostream& operator << (std::ostream &out, const std::vector<int> &vect)
{
  out << '[';
  for (int i = 0; i < vect.size(); i++)
  {
    out << vect[i] << ",";
  }
  out << ']';
  return out;
}

std::vector<int> interleave_arrays (std::vector<int> a, std::vector<int> b)
{
  int index[2] = {0,0};
  std::vector<int> result;

  while (index[0] + index[1] < a.size() + b.size())
  {
    if ( index[0] < a.size() )
    {
      result.push_back(a[index[0]++ ]);
    }
    if (index[1] < b.size())
    {
      result.push_back(b[index[1]++]);
    }
  }

  std::cout << result << '\n';

  return result;

}

int main()
{
  int arr[] = {1, 3, 5, 6};
  int arr2[] = {8, 9, 10, 11};

  std::vector<int> v(arr, arr + sizeof(arr)/sizeof(arr[0]));
  std::vector<int> v2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));

  interleave_arrays(v, v2);
}
