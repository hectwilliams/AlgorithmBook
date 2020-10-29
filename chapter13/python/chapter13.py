
import math
import random
def interleave_arrays(a, b):
  result =  []
  index = [0,0]

  while sum(index) < len(a) + len(b):

    if index[0] < len(a):
      result.append(a[index[0]])
      index[0] += 1

    if index[1] < len(b):
      result.append(b[index[1]])
      index[1] += 1

  print(result)
  return result

def merge_sorted_arrays (a, b):
  result = []
  currA = currB = 0

  while currA + currB < len(a) + len(b):

    if currA < len(a) and currB < len(b):

      if a[currA] < b[currB]:
        result.append(a[currA])
        currA += 1
      elif b[currB]  < a[currA]:
        result.append(b[currB])
        currB += 1
      else :
        result.append(a[currA])
        result.append(b[currB])
        currA += 1
        currB += 1
    elif currA < len(a):
      result.append(a[currA])
      currA += 1
    elif currB < len(b) :
      result.append(b[currB])
      currB += 1
  return result

def min_three_way_range(sorted_arrays):
  rangeResult = {'min': None, 'max': None, 'range': None}
  ordered_map = []
  runner = {}

  # init  runners for each array
  for i in range(0, sorted_arrays.__len__()):
    runner[i] = 0

  # create ordered map list from sorted arrays
  while (1) :
    minObject = {}

    for id in runner:

      arrayPos = runner[id]

      if arrayPos < sorted_arrays[id].__len__():
        value = sorted_arrays[id][arrayPos]

        if not bool(minObject)  or value < minObject['val'] :
          minObject = {  'id': id , 'val' :  value }

    if bool(minObject):
      ordered_map.append( {'key': minObject['id'], 'val': minObject['val'] } )
      runner [ minObject['id'] ] += 1
    else:
      break


  # find min range(s)

  for startIndex, element in enumerate (ordered_map):

    for key in runner:
      runner[key] = None

    for i in range(startIndex, ordered_map.__len__() ):

      # store range of values
      runner[ordered_map[i]['key']] = ordered_map[i]['val']

      if all(  map( lambda sel : runner[sel] != None , runner.keys() )  ) :
        # sort ranges of values
        sortedValues = sorted(runner.values())
        currRange =  sortedValues[-1] - sortedValues[0]

        # store min range
        if rangeResult['range'] == None or currRange < rangeResult['range'] :
          rangeResult['min'] = sortedValues[0]
          rangeResult['max'] = sortedValues[-1]
          rangeResult['range'] = currRange

  return rangeResult

def intersect_sorted_array (a, b):
  result = []
  pos = [0,0]

  while 1:
    if pos[0] < len(a) and pos[1] < len(b):
      if a[pos[0]] < b[pos[1]] :
        pos[0] += 1
      elif b[pos[1]] < a[pos[0]] :
        pos[1] += 1
      else :
         result.append(a[pos[0]])
         pos[0] += 1
         pos[1] += 1
    else:
      break
  return result

def intersect_sorted_array_dedupe (a, b):
  result = []
  pos = [0,0]

  while 1:
    if result:
      if pos[0] < len(a) :
        if result[-1] == a[pos[0]] :
          pos[0] += 1
      if pos[1] < len(b):
        if result[-1] == b[pos[1]]:
          pos[1] += 1
    if pos[0] < len(a) and pos[1] < len(b):
      if a[pos[0]] < b[pos[1]] :
        pos[0] += 1
      elif b[pos[1]] < a[pos[0]] :
        pos[1] += 1
      else :
         result.append(a[pos[0]])
         pos[0] += 1
         pos[1] += 1
    else:
      break
  return result

def union_sorted_array(a, b, callback = None):
  result = []
  aa = bb = 0

  while aa < len(a) or bb < len(b) :

    if result :
      if callback:
        index = callback( result[-1], a,b, aa, bb)
        if index == -1:
          pass
        else:
          if index == 0:
            aa += 1
          elif index == 1:
            bb += 1
          continue

    if aa < len(a) and bb < len(b):
      if a[aa] < b[bb] :
        result.append(a[aa])
        aa += 1
      elif a[aa] > b[bb]:
        result.append(b[bb])
        bb += 1
      else:
        result.append(a[aa])
        aa += 1
        bb += 1

    elif aa < len(a):
      result.append(a[aa])
      aa += 1

    elif bb < len(b) :
      result.append(b[bb])
      bb += 1
  return result

def union_sorted_array_dedupe(a, b):
  def callback(target, a, b, aa, bb):
    if aa < len(a):
      if target == a[aa] :
        return 0
    if bb < len(b) :
      if target == b[bb] :
        return 1
    return -1
  return union_sorted_array(a,b, callback)

def intersect_unsorted_array_in_place(a,b):
  aa = bb  = 0
  k = 0
  while aa < len(a) and bb < len(b):
    for i in range(bb, len(b)) :
      if a[aa] == b[i]:
        b[i], b[bb] = b[bb] , b[i]
        a[k], a[aa] = a[aa] , a[k]
        bb += 1
        k += 1
        break
    aa += 1
  return a[0 : k]

def intersect_unsorted_array(a,b):
  result = []
  left = right = 0
  curr = None

  for aa in range(0, len(a)):
    curr = a[aa]
    left = right = 0

    left = (a[0: aa + 1]).count(curr)
    right = b.count(curr)

    if not (right == 0 or right < left):
      result.append(curr)

def union_unsorted_arrays(a,b) :
  result = []
  count = None

  for i in range(0, len(a)) :
    result.append(a[i])

  for i in range(0, len(b)) :
    count = 0

    for k in range(0, len(b)):
      count += +(b[i] == b[k])

    for j in range (0, len(result)) :
      count -= +(b[i] == result[j])

    if count > 0:
      result.append(b[i])

  return result

def union_unsorted_arrays_in_place(a, b):
  count = 0

  for ele in b:

    count = 0

    for i in range(0, len(a)):
      count += +(a[i] == ele)

    for i in range(0, len(b)):
      count -= +(ele == b[i])

    print(ele, count)
    if count < 0:
      a.append(ele)
  return a

def union_unsorted_array_no_dupes (a, b):
  result = []

  def removeDupes(arr = [], target = None ):
    k  = count = 0

    for i in range(0, len(arr)) :

      count += +(arr[i] == target)
      if arr[i] != target:
        arr[i], arr[k] = arr[k], arr[i]
        k += 1
    while count > 1:
      arr.pop()
      count -= 1

  for array in [a,b]:
    for ele in array:
      result.append(ele)
      removeDupes(result, ele)

  return result

def subset_sorted_array (a, b) :
  bb = 0
  count = 0

  for i in range(0, len(a)) :

    if a[i] != b[bb] :
      count = 0
      bb = 0

    if a[i] == b[bb] :
      count += 1
      bb += 1

    if count == len(b) :
      return True
  return False

def subset_unsorted_array(a, b) :
  endA = len(a) - 1
  endB = len(b) - 1
  aa = bb = 0
  count = 0

  while aa < len(a) and bb < len(b) :
    if a[aa] != b[bb] :
      if a[aa] == b[endB]:
        b[bb] , b[endB] = b[endB], b[bb]
        endB -= 1
      elif b[bb] == a[endA]:
        a[aa], a[endA] = a[endA] , a[aa]
        endA -= 1
      else :
        aa += 1

    else:
      count += 1
      aa += 1
      bb += 1

    if count == len(b) :
      return True
  return False

class MinHeap:
  def __init__(self, array = []):
     self.size = 0
     self.array = [None]
     self.array += array

     self.size += len(array)
     self.heapify()

  @property
  def top(self):
    return self.array[1]

  @property
  def empty(self):
    return self.size == 0

  def contains(self, value):
    return value in self.array

  def insert(self, value) :
    parentIndex = None
    currPos = left = right = None
    self.array.append(value)
    self.size += 1

    parentIndex = int(self.size / 2)

    while parentIndex  > 0:
      currPos = parentIndex
      left = parentIndex * 2
      right = left + 1

      if left <= self.size and self.array[left] <= self.array[currPos]   :
        currPos = left

      if right <= self.size and self.array[right] <= self.array[currPos] :
        currPos = right

      if currPos != parentIndex:
        self.array[currPos] , self.array[parentIndex]  = self.array[parentIndex] , self.array[currPos]
        parentIndex =  int(parentIndex / 2)
      else:
        parentIndex = 0

  def extract (self) :
    result = None
    parentIndex = pos = left = right = 1

    if self.size > 0:
      self.array[1] , self.array[self.size] = self.array[self.size] , self.array[1]
      result = self.array.pop()
      self.size -= 1

      while parentIndex < self.size:
        pos = parentIndex
        left = parentIndex * 2
        right = left + 1

        if left <= self.size and self.array[left] <= self.array[pos] :
          pos = left

        if right <= self.size and self.array[right] <= self.array[pos] :
          pos = right

        if pos != parentIndex: #demote node
          self.array[pos] , self.array[parentIndex]  = self.array[parentIndex] , self.array[pos]
          parentIndex = pos
        else :
          break

    return result

  def  heapify (self) :
    parentIndex = left = right = pos = 0

    for i in range(self.size, 0 , -1) :
      parentIndex = int(i / 2)
      # demote
      while (parentIndex > 0):
        pos = parentIndex
        left = pos * 2
        right = left + 1
        if left <= self.size  and self.array[left] <= self.array[pos] :
          pos = left
        if right <=  self.size  and self.array[right] <= self.array[pos] :
          pos = right
        if pos != parentIndex:
          self.array[pos], self.array[parentIndex] = self.array[parentIndex] , self.array[pos]
          parentIndex = int(parentIndex / 2)
        else:
          break
  def display(self):
    print(self.array)


def heapifyMax(collection, length, currPos, callback =lambda array, childIndex, parentIndex, data = None: array[childIndex] > array[parentIndex] ):
  left = right = pos = 0

  if currPos < 0:
    return

  pos = currPos
  left = currPos * 2 + 1
  right = currPos * 2 + 2

  if left < length and callback(collection,left, pos ):
    pos = left
  if right < length and callback(collection,right, pos ) :
    pos = right
  if pos != currPos:
    collection[pos], collection[currPos] = collection[currPos], collection[pos]

  heapifyMax(collection, length, pos - 1, callback)

def heapSort (collection):
  count = 0
  for i in range( len(collection)  - 1, 0, -1):
    heapifyMax(collection, len(collection) - count , i)
    collection[0] , collection[i] = collection[i] , collection[0]
    count += 1



def test():
  collection = [ [1,2,4,15],[3,10,12],[5,10,13,17,23] ]
  min_three_way_range(collection)

test()