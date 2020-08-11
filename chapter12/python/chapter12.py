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

def test2():
  list1 = SList()
  list2 = SList()
  list1.add(2).add(3).add(4)
  list2.add(2).add(3).add(4)
  x = combine_list(list1.head, list2.head)
  while x:
    print(x.value)
    x = x.next
test2()