var SLNode = function(data)
{
  if (! (this instanceof(SLNode)))
  {
    return new SLNode(data);
  }
  this.value = data;
  this.next = null;
}

var SList = function()
{
  if (!(this instanceof(SList)))
  {
    return new SList();
  }
  this.head = null;

  this.add = (data) => {
    let runner;

    if (this.head == null)
    {
      this.head = SLNode(data);
    }
    else
    {
      runner = this.head;
      while (runner.next)
      {
        runner = runner.next;
      }
      runner.next = SLNode(data);
    }
    return this;
  };

  this.display = () => {
    let runner= this.head
    while (runner)
    {
      console.log(runner.value);
      runner = runner.next;
    }
  }
}

var swap = function (collection, i, k)
{

  if (i != k)
{

  let tmp = collection[k];
  collection[k] = collection[i];
  collection[i] = tmp;
}
};

var bubbleSort = function(collection = [])
{
  for (let i = 0; i < collection.length - 1; i++)
  {
    for (let k = 0; k < collection.length - i - 1; k++)
    {
      swap(collection, k, k + 1 ) ;
    }
  }
};

var selectionSort = function(collection = [])
{
  let sel_index;
  let size = collection.length;

  for (let i = 0; i < size; i++)
  {
    sel_index = i;

    for (let k = sel_index; k < size; k++)
    {
      if (collection[k] < collection[sel_index])
      {
        sel_index = k;
      }
    }

    if (sel_index != i)
    {
      swap(collection, sel_index, i);
    }
  }
}

var bubbleSort_list = function (llist)
{
  let curr = llist.head;
  let k, kprev, buffer, end;

  k = kprev = buffer = end;


  while (curr != end )
  {
    k = llist.head;
    kprev = null;

    while (k.next)
    {
      if (k.value  > k.next.value)
      {
        buffer = k.next;
        k.next = k.next.next;

        if (curr == k)
        {
          curr = buffer;
        }
        if (k == llist.head)
        {
          buffer.next = llist.head;
          llist.head = buffer;
        }
        else if (kprev)
        {
          kprev.next = buffer;
          buffer.next = k;
        }
        kprev = buffer;
        k = kprev.next;
      }
      else
      {
        kprev = k;
        k = k.next;
      }
    }
    end = k;
    curr = curr.next;
  }
}

var selectionSort_list = function (llist)
{
  let curr, k, kprev, curr_prev, selection_prev, selection;

  curr = k = kprev = curr_prev = selection_prev = selection = null;

  curr = llist.head

  while (curr)
  {
    k = selection = curr;
    while (k.next)
    {
      if (k.next.value < selection.value)
      {
        selection = k.next
;
        selection_prev = k;
      }
      k = k.next;
    }

    if (curr != selection)
    {
      selection_prev.next = selection_prev.next.next;

      selection.next = curr.next;

      if (curr == llist.head)
      {
        llist.head = selection ;
      }
      else
      {
        curr_prev.next = selection;
      }

      curr.next = selection_prev.next;

      if (curr != selection_prev)
      {
        selection_prev.next = curr;
      }
      else
      {
        selection.next = curr;
      }

      curr = selection;
    }

    curr_prev = curr;
    curr = curr_prev.next;
  }

}

var multiSort = function (llist, prio = 0)
{

  let curr, k, k_prev, curr_prev, selection_prev, selection;

  curr = k = kprev = curr_prev = selection_prev = selection = null;

  if (prio == 2)
  {
    return;
  }

  curr = llist.head;

  while (curr)
  {
     k = selection = curr;
     while (k.next)
     {
      if ( (prio == 0 && k.next.value.last < selection.value.last ) || (prio == 1 && k.next.value.first < selection.value.first && k.next.value.last == selection.value.last)     )
      {
        selection_prev = k;
        selection = k.next;
      }
      k = k.next;
     }

     if (curr != selection)
     {
       selection_prev.next = selection_prev.next.next;
       selection.next = curr.next;

       if (curr == llist.head)
       {
         llist.head = selection;
       }
       else
       {
         curr_prev.next = selection;
       }
       curr.next = selection_prev.next;
       if (curr != selection_prev)
       {
         selection_prev.next = curr;
       }
       else
       {
         selection.next = curr;
       }
       curr = selection
     }
     curr_prev = curr;
     curr =  curr.next;
  }
}

var insertionSort = function (collection)
{
  let size = collection.length;

  for (let i = 1; i < size; i++)
  {
    for (let k = i - 1; k >= 0; k++)
    {
      if (collection[k] > collection[k + 1])
      {
        swap(collection, k, k + 1);
      }
    }
  }
}

var insertionSort_list = function(list)
{
  let curr = list.head, buffer = null;

  while(curr.next)
  {
    if (curr.next.value < list.head.value)
    {
      buffer = curr.next;
      curr.next = curr.next.next;
      buffer.next = list.head;
      list.head = buffer;
    }
    else
    {
      curr = curr.next;
    }
  }
}

var combine = function (a, b)
{
  let ptrA, ptrB;
  let collection = [];

  ptrA = ptrB = 0;

  while (ptrA < a.length || ptrB < b.length)
  {
    if (ptrA  < a.length && ptrB < b.length)
    {
      if (a[ptrA] == b[ptrB])
      {
        collection.push(a[ptrA++]);
        collection.push(b[ptrB++]);
      }
      else if (a[ptrA] < b[ptrB])
      {
        collection.push(a[ptrA++]);
      }
      else
      {
        collection.push(b[ptrB++]);
      }
    }
    else if (ptrA < a.length)
    {
      collection.push(a[ptrA++]);
    }
    else
    {
      collection.push(b[ptrB++]);
    }
  }
  return collection;
}


var combine_in_place = function (a, b)
{
  let ptrA = 0;
  let ptrB = 0;

  while (ptrA < a.length)
  {
    ptrB = -1;

    while (ptrB + 1 < b.length)
    {
      if (b[ptrB + 1] < a[ptrA])
      {
        ++ptrB;
      }
      else
      {
        break;
      }
    }

    if (ptrB >= 0 && ptrB < b.length)
    {
      let tmp = a[ptrA];
      a[ptrA] = b[ptrB];
      b[ptrB] = tmp;
    }
    else
    {
      ++ptrA;
    }
  }

  while (b.length)   // flush b array
  {
    a.push(b.shift());
  }
}

var combine_list = function (list_a, list_b)
{
  let head = SLNode(undefined);
  let node = head;
  node.next = null;

  while (list_a && list_b)
  {
    if (list_a.value <= list_b.value)
    {
      node.next = list_a;
      list_a = list_a.next;
    }
    else
    {
      node.next = list_b;
      list_b = list_b.next;
    }
    node = node.next;
  }

  if (list_a)
  {
    node.next = list_a;
  }

  if (list_b)
  {
    node.next = list_b;
  }

  node = head.next;
  delete head;
  return node;
}

var mergeSort_list = function(llist)
{
  let counter = 0;
  let left, right, right_prev;

  right = left = right_prev = llist;

  while(llist.next)
  {
    ++counter;
    if (counter % 2 == 0 && counter > 0)
    {
      right_prev = right;
      right = right.next;
    }
    llist = llist.next;
  }

  if (counter <= 1)
  {
    return llist;
  }
  else if (counter == 2 )
  {
    right = left.next;
    left.next =  null;
    return combine_list(left, right);
  }
  else
  {
    right_prev.next = null;
    left = mergeSort_list(left);
    right = mergeSort_list(right);
  }

  return combine_list(left, right);
}

const partition_list = function(llist)
{
  let curr, pivot, head, pivot_prev, buffer;

  curr = pivot = head = llist;
  pivot_prev = buffer = null;

  while (curr.next)
  {
    if (curr.next.value < pivot.value)
    {
      buffer = curr.next;
      curr.next = curr.next.next;
      if (head == curr)
      {
        head = buffer;
        buffer.next = pivot;
      }
      else
      {
        buffer.next = pivot;
        pivot_prev.next = buffer;
      }
    }
    else
    {
      curr = curr.next;
    }
  }
  return head;
}

const partition_array = function (collection)
{
  let k = 0;

  for (let i = 0; i < collection.length; i++)
  {
    if (collection[i] < collection[k])
    {
      swap(collection, i, k);
      k++;
    }
  }
  return k;
}

const partition_array_second = function(collection)
{
  let size = collection.length;
  let median = [null, null, null];
  let pivot = null;
  let k = 0;

  if (collection.length)
  {
    median[0] = collection[0];
    median[1] = collection[Math.floor(size / 2)];
    median[2] = collection[collection.length - 1];
    pivot = median[1];
    for (let i = 0; i < collection.length; i++)
    {
      if (collection[i] < pivot)
      {
        swap(collection, i, k);
        k++;
      }
    }
  }
  return k;
}

const partition_array_third = function(arr, start = 0, end = 0)
{
  let k = -1;
  end = arr.length;

  for (let i = start; i < end; i++)
  {
    if (k == -1)
    {
      k = start;
    }
    if (arr[i] < arr[k])
    {
      swap(arr, i, k);
      k++;
    }
  }
  return k;
}

const quickSort = function(arr,  start = 0,  end = -1)
{
  let pivot = null;
  if (end == -1)
  {
    end = arr.length;
  }
  if (end - start > 0)
  {
    pivot = partition_array_third(arr, start, end);
    if (pivot >= 0)
    {
      quickSort(arr, 0, pivot);
      quickSort(arr, pivot + 1, end)
    }
  }
}

const partition3  = function (arr)
{
  let result = [];
  let k = 0;
  let pivot = arr[0];


  if (pivot)
  {
    //parition front
    for (let i = 0;i < arr.length; i++)
    {
      if (arr[i] < pivot)
      {
        swap(arr, i, k);
        k += 1;
      }
    }
    result[0] = k;

    // partition end
    k = arr.length - 1;
    for (let i = arr.length; i-- ; )
    {
      if (arr[i] > pivot)
      {
        swap(arr, i, k);
        k--;
      }
    }
    result[1] = k;
  }
  return result;
}

const mergeSort_array = function(collection)
{
  let size = collection.length;
  let mid = Math.floor(size / 2);
  let left, right, merged;

  if (size <=1 )
  {
    return;
  }

  left = collection.slice(0, mid + +(size % 2));
  right = collection.slice(mid + +(size % 2) , size );

  mergeSort_array(left);
  mergeSort_array(right);

  merged = combine(left, right);

  for (let i = 0; i < merged.length; i++)
  {
    collection[i] = merged[i];
  }
}

function test2 ()
{
  let dem = [ 2, 4, 6, 2, 10, 1];
  mergeSort_array(dem);
  console.log(dem);
}

test2();

