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


def test():
  collection = [5,4,3,2,1]
  selectionSort(collection)
  print(collection)

def test2():
  collection = [5,4,3,2,1]
  ll = SList()
  for ele in collection:
    ll.add(ele)
  bubbleSort_list(ll)
  ll.display()

test2()