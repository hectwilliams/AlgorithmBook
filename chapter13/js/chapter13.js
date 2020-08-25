const interleaveArrays = function (a,b)
{
  let result = [];
  let index = [0, 0] ;

  while (index[0] + index[1] < a.length + b.length)
  {
    if (index[0] < a.length)
    {
      result.push(a[index[0]++ ]);
    }
    if (index[1] < b.length)
    {
      result.push(b[index[1]++ ]);
    }
  }

  console.log(result);
  return result;
}

const mergeSortedArrays = function (a, b)
{
  let result = [];
  let idx_a = 0, idx_b = 0;

  while (idx_a + idx_b < a.length + b.length)
  {
    if (idx_a  < a.length && idx_b < b.length)
    {
      if (a[idx_a] < b[idx_b ])
      {
        result.push(a[idx_a++]);
      }
      else if (b[idx_b] < a[idx_a ])
      {
        result.push(b[idx_b++]);
      }
      else
      {
        result.push(b[idx_b++]);
        result.push(a[idx_a++]);
      }
    }
    else if (idx_a < a.length)
    {
      result.push(a[idx_a++]);
    }
    else if (idx_b < b.length)
    {
      result.push(b[idx_b++]);
    }
  }
}

const minThreeWayRange = function(collection)
{
  let mins = [null, null, null];
  let result = null;

  for (let i = 0; i< collection.length; i++)
  {
    for (let k = 0; k < collection[i].length; k++)
    {
      if (mins[i] == null || collection[i][k] < mins[i])
      {
        mins[i] = collection[i][k]
      }
    }
  }

  for (let i = 0; i < 3; i++) {
    let arr = collection[i];
    let min_set = mins.slice(0, i).concat(mins.slice(i + 1))

    arr.forEach( (num, index) =>{
      if (num > min_set[0] && num < min_set[1])
      {
        if (result == null)
        {
          result = min_set;
        }

        if (min_set[1] - min_set[0] < result[1] - result[1])
        {
          result = min_set;
        }
      }
    });
  }
  return result;
}

const intersectSortedArray = function(a,b, cb = ()=>{})
{
  let result = [];
  let pos = [0, 0];

  while (1)
  {

    cb (result, pos);
    if (pos[0] < a.length && pos[1] < b.length)
    {
      if ( a[pos[0]]  < b[pos[1]] )
      {
        pos[0] += 1;
      }
      else if ( b[pos[1]] < a[pos[0]] )
      {
        pos[1] += 1;
      }
      else
      {
        result.push(a[pos[0]]);
        pos[0] += 1;
        pos[1] += 1;
      }
    }
    else
    {
      break;
    }
  }

  return result;
}

const intersectSortedArrayDedupe = function(a,b)
{
  function callback(arr, pos)
  {
    if (arr.length)
    {
      if (pos[0] < a.length)
      {
        if (arr[arr.length - 1] == a[pos[0]] )
        {
          pos[0]++;
        }
      }

      if (pos[1] < b.length)
      {
        if (arr[arr.length - 1] == b[pos[1]] )
        {
          pos[1]++;
        }
      }
    }
  }

  return intersectSortedArray(a, b, callback);
}

const unionSortedArray = function(a, b, callback = undefined)
{
  let result = [];
  let aa = 0, bb = 0;

  while (aa < a.length || bb < b.length)
  {

    if (result.length > 0 && callback)
    {
      let pos = callback(result[result.length - 1] , a,b, aa,bb );

      console.log(pos);

      if (pos == 0)
      {
        ++aa;
        continue;
      }
      else if (pos == 1)
      {
        ++bb;
        continue;
      }
    }

    if (aa < a.length && bb < b.length)
    {
      if (a[aa] < b[bb])
      {
        result.push(a[aa++]);
      }
      else if (a[aa] > b[bb] )
      {
        result.push(b[bb++]);
      }
      else
      {
        result.push(a[aa]);
        aa++;
        bb++;
      }
    }
    else if (aa < a.length)
    {
      result.push(a[aa++]);
    }
    else if (bb < b.length)
    {
      result.push(b[bb++]);
    }
    else
    {
      break;
    }
  }
  return result;
}

const unionSortedArrayDedupe = function (a, b)
{
  function callback (target, a, b, aa,bb)
  {
    if (aa < a.length)
    {
      if (target == a[aa])
      {
        return 0;
      }
    }

    if (bb < b.length)
    {
      if (target == b[bb])
      {
        return 1;
      }
    }

    return -1;

  }
  return unionSortedArray(a,b,callback);
}

const swap = function(collection, i,j)
{
  let tmp = collection[i];
  collection[i] = collection[j];
  collection[j] = tmp;
}

const interssectUnsortedArrayInPlace = function (a, b)
{
  let aa  = 0;
  let bb = 0;
  let k = 0;

  while (aa < a.length && bb < b.length)
  {
    for (let i = bb; i < b.length; i++)
    {
      if (a[aa] == b[i])
      {

        swap(b, i, bb++);
        swap(a, aa, k++);
        break;
      }
    }
    aa++;
  }
  return a.slice(0, k);
}

const interssectUnsortedArray = function (a ,b)
{
  let result = [];
  let curr = null;
  let left = null;
  let right = null;

  for (let aa = 0; aa < a.length; aa++)
  {
    curr = a[aa];
    left = a.reduce( (acc, element, index )=>{
      return acc + ( (index < aa + 1 ) &&  +(curr == element))  || 0 ;
    }, 0 );

    right = b.reduce( (acc, element, index )=>{
      return acc +(curr == element)  ;
    }, 0 );

    if (!(right == 0 || right < left))
    {
      result.push(curr);
    }
  }
  return result;
}

const unionUnsortedArray = function (a, b)
{
  let result = [];
  let count = 0;

  for (let i = 0; i < a.length; i++)
  {
    result.push(a[i]);
  }
  for (let i = 0; i < b.length ; i++ )
  {
    count = 0;
    for (let k = 0; k < b.length; k++)
    {
      count += b[i] == b[k];
    }
    for (let j = 0; j < result.length; j++)
    {
      count -= b[i] == result[j];
    }
    if (count > 0)
    {
      result.push(b[i]);
    }
  }
  return result;
}

const unionUnsortedArrayInPlace = function (  a, b )
{
  let count;
  let size = a.length;
  let ele;

  for (let i = 0; i < size; i++ )
  {
    count = 0;
    ele = b[i];

    for (let i = 0; i < a.length; i++)
    {
      count += +(a[i] == ele);
    }

    for (let i = 0; i < b.length; i++)
    {
      count -= +(ele == b[i]);
    }

    if (count < 0)
    {
      a.push( ele );
    }
  }

  return a;
}

const unionUnsortedArrayNoDupes = function (  a, b , cb = (arr = [], target) => {
  let k = 0;
  let count = 0;

  for (let i = 0; i < arr.length; i++)
  {
    count += +(arr[i] == target);
    if (arr[i] != target)
    {
      swap(arr, i , k++);
    }
  }
  while (count > 1)
  {
    arr.pop();
    count--;
  }
})
{
  let result = [];
  [a, b].forEach((collection) => {
    collection.forEach((ele) => {
      result.push(ele);
      cb(result, ele );
    });
  });

  return result;
}

const subsetSortedArray = function(a,b)
{
  let count = 0;
  let bb = 0;

  for (let i = 0; i < a.length; i++)
  {
    if (a[i] != b[bb])
    {
      count = 0;
      bb = 0;
    }

    if (a[i] == b[bb])
    {
      count++;
      bb++;
    }

    if (count == b.length )
    {
      return true;
    }
  }

  return false;
}

const subset_unsorted_array = function(a ,b)
{
  let endA = a.length - 1;
  let endB = b.length - 1;
  let aa = 0;
  let bb = 0;
  let count = 0;

  while (aa < a.length && bb < b.length )
  {
    if (a[aa] != b[bb])
    {
      if (a[aa] == b[endB])
      {
        swap(b, bb, endB--);
      }
      else if (b[bb] == a[endA])
      {
        swap(a, aa, endA--);
      }
      else
      {
        aa++;
      }

    }
    else
    {
      count++;
      bb++;
      aa++;
    }

    if (count == b.length)
    {
      return true;
    }
  }
  return false ;
}


var MinHeap = function(arr = [])
{
  this.size = 0;
  this.array = [undefined]
  this.array = this.array.concat(arr);
  this.size += arr.length

  this.heapify  = () => {
    let parentIndex, left, right, pos;

    for (let i = this.size; i > 0; i--)
    {
      parentIndex = Math.floor( i / 2);
      while (parentIndex > 0)
      {
        pos = parentIndex;
        left = pos * 2 ;
        right = left + 1;
        if (left <= this.size && this.array[left] <= this.array[pos])
        {
          pos = left;
        }
        if (right <= this.size && this.array[right] <= this.array[pos])
        {
          pos = right;
        }
        if (pos != parentIndex)
        {
          swap(this.array, pos, parentIndex) ;
          parentIndex = Math.floor(parentIndex / 2);
        }
        else
        {
          break;
        }
      }
    }

  }
  this.heapify ();

  console.log(this.array)
  this.top = () => {
    return this.array[1];
  };

  this.empty = () =>{
    return this.size == 0;
  }

  this.insert = (value) => {
    let parentIndex;
    let right, left, currPos;

    this.array.push(value);
    this.size++;

    parentIndex = Math.floor(this.size / 2);

    while (parentIndex > 0)
    {
      currPos = parentIndex;
      left = currPos * 2;
      right  = left + 1;

      if (left <= this.size && this.array[left] <= this.array[currPos])
      {
        currPos = left;
      }
      if (right <= this.size && this.array[right] <= this.array[currPos] )
      {
        currPos = right;
      }
      if (currPos != parentIndex)
      {
        swap(this.array, currPos, parentIndex);
        parentIndex = Math.floor(parentIndex / 2);
      }
      else
      {
        parentIndex = 0;
      }
    }
  }

  this.extract  = () => {
    let result = undefined;
    let pos;
    let right;
    let left;
    let parentIndex = 1;

    if (this.size > 0)
    {
      swap(this.array, 1, this.size);
      result = this.array.pop();
      this.size--;
      while (parentIndex < this.size)
      {
        pos = parentIndex;
        left = pos * 2;
        right = left + 1

        if (left <= this.size && this.array[left] <= this.array[pos])
        {
          pos = left;
        }
        if (right <= this.size && this.array[right] <= this.array[pos])
        {
          pos = right;
        }

        if (pos != parentIndex)
        {
          swap(this.array, pos, parentIndex);
          parentIndex = pos;
        }
        else
        {
          break;
        }
      }
    }
    return result;
  }
}

const heapifyMax = function(collection, length, currPos, callback = (array, childIndex, parentIndex) => array[childIndex] > array[parentIndex] )
{
  let left, right, pos;

  if (currPos < 0)
  {
    return
  }
  pos = currPos;
  left = pos* 2 + 1;
  right = pos * 2 + 2;

  if (left < length && callback(collection, left, pos ))
  {
    pos = left;
  }
  if (right < length && callback(collection, right, pos) )
  {
    pos = right;
  }
  if (pos != currPos )
  {
    swap(collection, pos, currPos);
  }
  heapifyMax(collection, length, currPos - 1, callback);
}

const heapSort = function (collection)
{
  let count = 0;
  for (let i = collection.length - 1; i >= 0 ; i-- )
  {
    heapifyMax(collection, collection.length - count++, i);
    swap(collection, i, 0);
  }
}

const median_data_stream = function ()
{
  let median  = 0;
  let maxHeap = []
  let minHeap = []


  return  function (inData)
  {

    if (maxHeap.length == minHeap.length)
    {
      if (inData <= median)
      {
        maxHeap.push(inData);
        heapifyMax(maxHeap, maxHeap.length, maxHeap.length - 1);
        median = maxHeap[0];
      }
      else
      {
        minHeap.push(inData);
        heapifyMax(minHeap, minHeap.length, minHeap.length - 1, (array, childIndex, parentIndex) => array[childIndex] <= array[parentIndex]);
        median = minHeap[0];
      }
    }

    else if (maxHeap.length > minHeap.length)
    {
      if (inData <= median)  // insert to maxheap (reduce size of maxHeap)
      {
        swap(maxHeap, 0, maxHeap.length - 1);
        minHeap.push(maxHeap.pop());  // extract maxHeap top into minHeap
        maxHeap.push(inData);
      }
      else
      {
        minHeap.push(inData);
      }
      heapifyMax(minHeap, minHeap.length, minHeap.length - 1, (array, childIndex, parentIndex) => array[childIndex] <= array[parentIndex]);
      heapifyMax(maxHeap, maxHeap.length, maxHeap.length - 1);
      median = (minHeap[0] + maxHeap[0]) / 2;
    }

    else if (minHeap.length > maxHeap.length)
    {
      if (inData > median)  // insert to minheap (reduce size of minHeap )
      {
        swap(minHeap, 0, minHeap.length - 1);
        maxHeap.push(minHeap.pop()); // extract maxHeap top into minHeap
        minHeap.push(inData);
      }
      else
      {
        maxHeap.push(inData);
      }
      heapifyMax(maxHeap, maxHeap.length, maxHeap.length - 1);
      heapifyMax(minHeap, minHeap.length, minHeap.length - 1, (array, childIndex, parentIndex) => array[childIndex] <= array[parentIndex]);
      median = (minHeap[0] + maxHeap[0]) / 2;
    }
    return median;
  }

}
const median_data_stream_driver = median_data_stream();

const test = function()
{
  let heap ;
  let data = [] ;
  let data2 = [];
  for (let i = 0; i< 9 ; i++)
  {
    let dataIn = (Math.floor(Math.random() * 100));
    data2.push(dataIn);
    let x = median_data_stream_driver(dataIn);
  }
  heapSort(data2)
  console.log(data2)

}

test();