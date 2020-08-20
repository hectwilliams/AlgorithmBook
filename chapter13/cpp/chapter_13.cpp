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

std::vector<int> union_sorted_array (std::vector<int> a, std::vector<int> b , bool (*cb)(int, std::vector<int>, std::vector<int>, int&, int&)  )
{
  std::vector<int> result;
  int aa , bb;

  aa = bb = 0;

  while (aa < a.size() || bb < b.size())
  {

    if (cb)
    {
      if (! result.empty())
      {

        if (cb(result.back(), a,b,aa, bb))
        {
          continue;
        }
      }
    }

    if (aa < a.size() && bb < b.size())
    {
      if (a[aa] < b[bb])
      {
        result.push_back(a[aa++]);
      }
      else if(a[aa] > b[bb])
      {
        result.push_back(b[bb++]);
      }
      else
      {
        result.push_back(a[aa]);
        aa++;
        bb++;
      }
    }
    else if (aa < a.size())
    {
      result.push_back(a[aa++]);
    }
    else if(bb < b.size())
    {
      result.push_back(b[bb++]);
    }
    else
    {
      break;
    }
  }
  std::cout << result << '\n';
  return result;
}

bool function_ptr (int target, std::vector<int> a, std::vector<int> b, int &aa, int &bb)
{
  if (aa < a.size())
  {
    if (target == a[aa])
    {
      aa++;
      return true;
    }
  }

  if (bb < b.size())
  {
    if (target == b[bb] )
    {
      bb++;
      return true;
    }
  }

  return false;
}

std::vector<int> union_sorted_array_dedupe (std::vector<int> a, std::vector<int> b )
{
  return union_sorted_array(a, b, function_ptr);
}

std::vector<int> intersect_unsorted_array_in_place(std::vector<int> a, std::vector<int> b)
{
  int k = 0;
  int aa = 0;
  int bb = 0;

  while (aa < a.size() && bb < b.size())
  {
    for (int i = bb; i < b.size(); i++)
    {
      if (a[aa] == b[i])
      {
        std::swap(b[i] , b[bb++]);
        std::swap(a[aa], a[k++]);
        break;
      }
    }
    aa++;
  }
  return std::vector<int>(a.begin(), a.begin() + k);
}

int main()
{
  int arr[] = {1,2,2,2,7};
  int arr2[] = {2,2,6,6,7};
  std::vector<int> v(arr, arr + sizeof(arr)/sizeof(arr[0]));
  std::vector<int> v2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
 auto x =  intersect_unsorted_array_in_place(v, v2);
 std::cout << x << '\n';
}
