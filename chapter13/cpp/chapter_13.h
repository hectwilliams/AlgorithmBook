#include <utility>
#include <vector>
#include <iostream>
#include <string>
std::ostream& operator << (std::ostream &out, const std::vector<int> &vect);
std::vector<int> interleaveArrays (std::vector<int> a, std::vector<int> b);
std::vector<int> intersect_sorted_arrays(std::vector<int> a, std::vector<int> b);
std::vector<int> union_sorted_array (std::vector<int> a, std::vector<int> b , bool (*cb)(int, std::vector<int>, std::vector<int>, int&, int&) = NULL );
bool function_ptr (int target, std::vector<int> a, std::vector<int> b, int &aa, int &bb);


struct minRangeData
{
  int min;
  int max;
  int range;
};

class MinHeap
{
  private:
  public:
    int size;
    std::vector<int> array;
    void heapify(std::vector<int> & collection, int maxLength = 0);

    bool empty();
    int top();
    void insert(const int &data);
    bool contains(const int &data);
    void display ();
    int extract();

  MinHeap(std::vector<int> collection = std::vector<int>() )
  {
    size = 0;
    array.push_back(0xDEADBEEF);

    for (int i = 0; i < collection.size(); i++)
    {
      array.push_back(collection[i]);
      size++;
    }
    heapify(array);
  }
};

bool heapify_MaxHeap_cb (std::vector<int> &collection, int childIndex, int parentIndex);
bool heapify_MinHeap_cb (std::vector<int> &collection, int childIndex, int parentIndex);

void heapSort(std::vector<int> &collection);
void heapifyMax(std::vector<int> &collection, int maxLength, int currPos, bool (*callback) (std::vector<int>&, int childIndex, int parentIndex)  = heapify_MaxHeap_cb );
