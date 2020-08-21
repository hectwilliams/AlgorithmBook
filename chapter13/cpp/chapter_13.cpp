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

std::vector<int> intersect_unsorted_array(std::vector<int> a, std::vector<int> b)
{
  std::vector<int> result;
  int curr;
  int left, right;

  for (int aa = 0;  aa < a.size(); aa++)
  {
    curr = a[aa];

    left = std::count(a.begin(), a.begin() + aa + 1 , curr);

    right = std::count(b.begin(), b.end() , curr);

    if (!(right == 0 || right < left))
    {
      result.push_back(curr);
    }
  }

  return result;
}

std::vector<int> union_unsorted_array(std::vector<int> a, std::vector<int> b)
{
  std::vector<int> result;
  int count = 0;

  for (int i = 0; i < a.size(); i++)
  {
    result.push_back(a[i]);
  }
  for (int i = 0; i < b.size(); i++)
  {
    count = 0;
    for (int k = 0; k < b.size(); k++)
    {
      count += b[i] == b[k];
    }
    for (int j = 0; j < result.size(); j++)
    {
      count -= b[i] == result[j];
    }
    if (count > 0)
    {
      result.push_back(b[i]);
    }
  }
  std::cout << result << '\n';
  return result;

}


std::vector<int> union_unsorted_array_in_place(std::vector<int> &a, std::vector<int> b)
{
  int count;
  for (auto ele: b)
  {
    count = 0;
    for (int i = 0; i < a.size(); i++)
    {
      count += +(a[i] == ele);
    }
    for (int i = 0; i < b.size(); i++)
    {
      count -= +(ele == b[i]);
    }
    if (count < 0)
    {
      a.push_back(ele);
    }
  }
  return a;
}

void union_unsorted_array_no_dupes_helper_remove(std::vector<int> &arr, int target)
{
  int k = 0;
  int count = 0;


    for (int j = 0; j < arr.size(); j++)
    {
      if (arr[j] != target )
      {
        std::swap(arr[k++] , arr[j]);
      }
      else
      {
        count++;
      }
    }

    while (count > 1)
    {
      arr.pop_back();
      count--;
    }
}
std::vector<int> union_unsorted_array_no_dupes(std::vector<int> a, std::vector<int> b)
{
  std::vector<int> result;
  int k = 0;
  int curr;
  int count = 0;

  for (int i = 0; i < a.size(); i++)
  {
    result.push_back(a[i]);
    union_unsorted_array_no_dupes_helper_remove(result, a[i]);
  }

  for (int i = 0; i < b.size(); i++)
  {
    result.push_back(b[i]);
    union_unsorted_array_no_dupes_helper_remove(result, b[i]);
  }
  return result;

}

bool subset_sorted_array (std::vector<int> a, std::vector<int> b)
{
  int count = 0;
  int bb = 0;

  for (int j = 0; j < a.size(); j++)
  {
    if (a[j] != b[bb])
    {
      count = 0;
      bb = 0;
    }

    if (a[j] == b[bb])
    {
      count++;
      bb++;
    }

    if (count == b.size())
    {
      return true;
    }
  }

  return false;
}

bool subset_unsorted_array (std::vector<int> a, std::vector<int> b)
{
  int endA = a.size() - 1;
  int endB = b.size() - 1;
  int aa = 0;
  int bb = 0;
  int count = 0;

  while (aa < a.size() && bb < b.size() )
  {
    if (a[aa] != b[bb])
    {
      if (a[aa] == b[endB])
      {
        std::swap(b[bb] , b[endB--]);
      }
      else if (b[bb] == a[endA] )
      {
        std::swap(a[aa] , a[endA--]);
      }
      else
      {
        aa++;
      }
    }
    else
    {
      count++;
      aa++;
      bb++;
    }

    if (count == b.size())
    {
      return true;
    }

  }
  return false;
}

int main()

{
int arr[] = {10, 5, 2, 23, 19}, arr2[] = {19, 5, 3};  // int arr[] = {  2,2,7,7,2,1  };
  // int arr2[] = {7,2 };
  std::vector<int> v(arr, arr + sizeof(arr)/sizeof(arr[0]));
  std::vector<int> v2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
 auto x =  subset_unsorted_array(v, v2);
  std::cout << x << '\n';
}
