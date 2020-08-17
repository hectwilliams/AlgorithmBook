import random

class SLNode:
  def __init__(self, value):
    self.value = value
    self.next = None

class SList:
  def __init__(self):
    self.head = None
  def add(self, value):
    runner = None
    if self.head == None:
      self.head = SLNode(value)
    else:
      runner = self.head
      while runner.next:
        runner = runner.next
      runner.next = SLNode(value)
    return self
  def display(self):
    runner = self.head
    while runner:
      print(runner.value)
      runner = runner.next

def swap (array, i, k):
  array[i], array[k] = array[k], array[i]

def bubbleSort(array):
  size = len(array)
  for i in range(0, size - 1):
    for k in range(0, size - i - 1):
      if array[k] > array[k + 1]:
        swap(array, k, k+1)

def selectionSort(array):
  size = len(array)
  sel_index  = None
  for i in range(0, size - 1):
    sel_index = i
    for k in range(sel_index + 1, size):
      if array[k] < array[sel_index]:
        sel_index = k
    if sel_index != i:
      swap(array, sel_index, i)

def bubbleSort_list(llist):
  curr = llist.head
  k = None
  kprev = None
  buffer = None
  end = None

  while curr !=end:
    k = llist.head
    kprev = None

    while k.next != end:
      if k.value > k.next.value:
        buffer = k.next
        k.next = k.next.next
        if curr == k:
          curr = buffer
        if k == llist.head:
          buffer.next = llist.head
          llist.head = buffer
        elif kprev:
          kprev.next = buffer
          buffer.next = k
        kprev = buffer
        k = kprev.next
      else:
        kprev = k
        k = k.next
    end = k
    curr = curr.next

def selectionSort_list(llist):
  curr = None
  k = None
  kprev = None
  curr_prev = None
  selection_prev = None
  selection = None

  curr = llist.head

  while curr:

    k = curr
    selection = curr

    while k.next :
      if k.next.value < selection.value :
        selection = k.next
        selection_prev = k
      k = k.next

    if curr != selection:
      selection_prev.next = selection_prev.next.next

      selection.next = curr.next

      if curr == llist.head:
        llist.head = selection
      else:
        curr_prev.next = selection

      curr.next = selection_prev.next

      if curr != selection_prev:
        selection_prev.next = curr
      else:
        selection.next = curr

      curr = selection

    curr_prev = curr
    curr = curr_prev.next




def multiSort(llist , prio = 0) :
  curr = None
  k = None
  curr_prev = None
  selection_prev = None
  selection = None

  if prio >= 2:
    return

  curr = llist.head

  while curr:
    k = curr
    selection = curr

    while k.next:
      if  (prio == 0 and k.next.value['last'] < selection.value['last'] ) or  (prio == 1 and k.next.value['first'] < selection.value['first'] and  k.next.value['last'] == selection.value['last']   ):
        selection = k.next
        selection_prev = k
      k = k.next

    if curr != selection:
      selection_prev.next = selection_prev.next.next
      selection.next = curr.next

      if curr == llist.head :
        llist.head = selection
      else:
        curr_prev.next = selection

      curr.next = selection_prev.next

      if curr != selection_prev:
        selection_prev.next = curr
      else:
        selection.next = curr

      curr = selection

    curr_prev = curr
    curr = curr.next
  return multiSort(llist, prio + 1)

def insertionSort_array(collection):
  size = len(collection)

  for i in range(1, size):
    for k in range(i - 1, -1, -1):
      if collection[k] > collection[ k + 1]:
        collection[k] , collection[k + 1] = collection[k + 1] , collection[k]

def insertionSort_list(llist):
  curr = llist.head
  buffer = None

  while curr.next:
    if curr.next.value < llist.head.value:
      buffer = curr.next
      curr.next = curr.next.next
      buffer.next = llist.head
      llist.head = buffer
    else :
      curr = curr.next

def combine(a, b):
  ptrA = 0
  ptrB  =  0
  collection = []
  while ptrA < len(a) or ptrB < len(b):
    if ptrA < len(a) and ptrB < len(b):
      if a[ptrA] == b[ptrB]:
        collection.append(a[ptrA])
        collection.append(b[ptrB])
        ptrA += 1
        ptrB += 1
      elif a[ptrA] < b[ptrB]:
        collection.append(a[ptrA])
        ptrA += 1
      else:
        collection.append(b[ptrB])
        ptrB += 1
    elif ptrA < len(a) :
      collection.append(a[ptrA])
      ptrA += 1
    elif ptrB < len(b) :
      collection.append(b[ptrB] )
      ptrB += 1

  return collection

def combine_in_place(a, b) :
  ptrA = 0
  ptrB = 0

  while ptrA < len(a):

    ptrB = -1
    while ptrB + 1< len(b):
      if b[ptrB + 1] < a[ptrA]:
        ptrB += 1
      else:
        break

    if ptrB >= 0 and ptrB < len(b):
      a[ptrA], b[ptrB] = b[ptrB], a[ptrA]
    else:
      ptrA += 1

  a += b

def combine_list(listA, listB):
  head  = SLNode(None)
  node = head

  node.next = None

  while listA and listB:
    if listA.value <= listB.value:
      node.next = listA
      listA = listA.next
    else:
      node.next = listB
      listB = listB.next
    node = node.next

  if listA != None:
    node.next = listA

  if listB != None:
    node.next = listB

  node = head.next
  del(head)
  return node

def mergeSort_list (llist):
  counter = 0
  left = llist
  right_prev = llist
  right = llist

  while llist.next:
    counter += 1
    if counter % 2  == 0 and counter > 0:
      right_prev = right
      right = right.next
    llist = llist.next

  if counter <= 1:
    return llist

  elif counter == 2:
    right = left.next
    left.next = None
    return combine_list(left, right)

  else:
    right_prev.next = None
    left = mergeSort_list(left)
    right = mergeSort_list(right)

  return combine_list(left, right)

def partition_list(llist):
  curr = llist
  pivot = llist
  head = llist
  pivot_prev  = None
  buffer = None

  while curr.next:
    if curr.next.value < pivot.value:
      buffer = curr.next
      curr.next = curr.next.next
      if head == curr:
        head = buffer
        buffer.next = pivot
      else:
        buffer.next = pivot
        pivot_prev.next = buffer
      pivot_prev = buffer
    else:
      curr = curr.next
  return head


def partition_array(collection):
  size = len(collection)
  k = 0
  for i in range(0, size):
    if (collection[i] < collection[k]):
      collection[i], collection[k] = collection[k] , collection[i]
      k += 1
  return k
def partition_array_second(collection):
  size = len(collection)
  median = [None, None, None]
  k = 0

  if collection:
    median[0] = collection[0]
    median[1] = collection[ int(size / 2) ]
    median[2] = collection[size - 1]

    pivot = median[1]
    for i in range(0, size):
      if collection[i] < pivot:
        collection[i], collection[k] = collection[k] , collection[i]
        k += 1
  return k

def partition_array_third(collection, start = 0, end = None):
  k = -1

  if end == None:
    end = len(collection)

  for i in range(start, end):
    if k == -1:
      k = start
    if collection[i] < collection[k]:
      collection[i], collection[k] = collection[k] , collection[i]
      k += 1

  return k

def quickSort(collection, start = 0, end = None):
  pivot = None

  if end == None:
    end = len(collection)

  if end - start > 0:
    pivot = partition_array_third(collection, start, end)

    if pivot >= 0:
      quickSort(collection, 0, pivot)
      quickSort(collection, pivot + 1, end)   #right

def partition3(collection, start = 0, end = -1):
  result = [None, None]
  pivot = None
  size = len(collection )
  count = 0
  k = 0
  a = b = c = None

  end = len(collection) if end == -1 else end

  a = collection[start]
  b = collection [ (start + end) / 2]
  c = collection[end - 1]

  if (a > b ) != ( a > c) :
    pivot = a
  elif (b > a) != (b > c) :
    pivot = b
  else:
    pivot = c

  if pivot:
    size = end - start
    for i in range(start, start + size):
      count += +(collection[i] == pivot )
      if collection[i] < pivot:
        collection[i] , collection[k] = collection[k] , collection[i]
        if k < start + size:
          k += 1
    k = start + size - 1
    for i in range(start + size - 1, -1, -1) :
      if collection[i] > pivot:
        collection[i] , collection[k] = collection[k] , collection[i]
        k += -1

  result[0] = k - (count - 1)
  result[1] = k
  return result

def mergeSort_array(collection):
  size = len(collection)
  mid = int(size / 2)
  left = right = data_merge = []

  if size <= 1:
    return

  left = collection[ 0 : mid + +(size % 2) ]
  right = collection [mid + +(size %2): : ]

  mergeSort_array(left)
  mergeSort_array(right)

  data_merge = combine(left, right)

  for i in range(0, len(data_merge)):
    collection[i] = data_merge[i]

def quickSort3(collection, start = 0, end = -1) :
  end  = len(collection) if end == -1 else end
  pivot_arr = None
  if end - start > 0:
    pivot_arr = partition3(collection, start, end)
    if pivot_arr[0] != None:
      quickSort3(collection, 0, pivot_arr[0])
      quickSort3(collection, pivot_arr[1] + 1, end)

def urbanDictionaryDailyAdd():
  """
    Use quickSort instead of selectionSort. Selection Sort would work if the new valuess were greater than
    the largest value in list.

    Model:
    1) insert 1 of remaining new values to end of list  (remove from new data list)
    2) partition using the most recent added value
    3) Order should still be retained '
    4)continue step 1 until 'new data list' array is empty
  """
  pass

def pancakeSort(collection):
  info = {'min': 0, 'index': 0}
  tmp = []
  k = len(collection) - 1

  while k > 0:
    info['min'] = collection[0]
    info['index'] = 0

    for i in range(0, k + 1):
      if collection[i] >= info['min']:
        info['min'] = collection[i]
        info['index'] = i

    tmp = (collection[0 : info['index'] + 1])
    tmp.reverse()
    for i in range(0, len(tmp)):
      collection[i] = tmp[i]

    tmp = collection[0 : k + 1]
    tmp.reverse()
    for i in range(0, len(tmp)):
      collection[i] = tmp[i]
    k += -1

def radixSort(collection, maxValue = 9):
  k = 0
  curr = None
  factor = 1
  counter = 0
  complete = False

  while not complete:
    k = 0
    for i in range(0, maxValue + 1):
      if complete:
        break
      counter = 0
      for j in range(0, len(collection)):
        if complete:
          break
        curr = int(collection[j] / factor) % 10
        counter += +(curr == 0 )
        if curr == i:
          collection[k], collection[j] = collection[j] , collection[k]
          k+= 1
      complete = counter == len(collection) and i == 0
    factor *= 10

def test2():
  arr = [100, 5, 3, 1,100, 9, 10]
  arr= [2, 2, 4, 6, 2, 10, 2, 1]
  radixSort(arr)
  print(arr)
test2()