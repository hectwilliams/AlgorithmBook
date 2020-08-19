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

std::vector<int> interleaveArrays (std::vector<int> a, std::vector<int> b)
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

std::vector<int> merge_sorted_arrays(std::vector<int> a, std::vector<int> b)
{
  std::vector<int> result;
  int idx_a = 0; int idx_b = 0;

  while (idx_a + idx_b < a.size() + b.size())
  {
    if (idx_a < a.size() && idx_b < b.size())
    {
      if ( a[idx_a] < b[idx_b] )
      {
        result.push_back(a[idx_a++]);
      }
      else if ( b[idx_b] < a[idx_a] )
      {
        result.push_back(b[idx_b++]);
      }
      else
      {
        result.push_back(b[idx_b++]);
        result.push_back(a[idx_a++]);
      }
    }
    else if (idx_a < a.size())
    {
      result.push_back(a[idx_a++]);
    }
    else if (idx_b < b.size())
    {
      result.push_back(b[idx_b++]);
    }
  }
    std::cout << result << '\n';

  return result;
}

std::vector<int> intersect_sorted_arrays(std::vector<int> a, std::vector<int> b)
{
  std::vector<int> result;
  int index[2] = {0,0};

  while (1)
  {
    if (index[0] < a.size() && index[1] < b.size())
    {
      if (a[index[0]] < b[index[1]])
      {
        index[0]++;
      }
      else if(b[index[1]] < a[index[0]])
      {
        index[1]++;
      }
      else
      {
        result.push_back(a[index[0]]);
        index[0]++;
        index[1]++;
      }
    }
    else
    {
      break;
    }

  }
  std::cout << result;
  return result;
}


std::vector<int> intersect_sorted_arrays_dedupe(std::vector<int> a, std::vector<int> b)
{
  std::vector<int> result;
  int index[2] = {0,0};

  while (1)
  {
    if (result.size())
    {
      if (index[0] < a.size())
      {
        if (result.back() == a[index[0]])
        {
          index[0]++;
          continue;
        }
      }

      if (index[1] < b.size())
      {
        if (result.back() == b[index[1]])
        {
          index[1]++;
          continue;
        }
      }

    }

    if (index[0] < a.size() && index[1] < b.size())
    {
      if (a[index[0]] < b[index[1]])
      {
        index[0]++;
      }
      else if(b[index[1]] < a[index[0]])
      {
        index[1]++;
      }
      else
      {
        result.push_back(a[index[0]]);
        index[0]++;
        index[1]++;
      }
    }
    else
    {
      break;
    }

  }
  std::cout << result;
  return result;
}

int main()
{
  int arr[] = {1, 3, 5, 6};
  int arr2[] = {6, 6,9, 10, 11};
  std::vector<int> v(arr, arr + sizeof(arr)/sizeof(arr[0]));
  std::vector<int> v2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
  intersect_sorted_arrays_dedupe(v, v2);
}
