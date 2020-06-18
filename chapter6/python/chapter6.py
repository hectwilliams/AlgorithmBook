from typing import NewType
import math 

class SLQueue():
  pass

class SLStack():
  pass 

SLQueue_t = NewType('SLQueue_t', SLQueue)
SLStack_t = NewType('SLStack_t', SLStack)

class SLNode:
  def __init__(self, value):
    self.val = value
    self.next = None 

class SLQueue:

  def __init__(self):
    self.head = None 
    self.tail = None

  def enqueue(self, val):
    node = SLNode(val) 
    if (self.head == None):
      self.head = node 
      self.tail = node 
    else:
      self.tail.next = node 
      self.tail = node
  
  def dequeue(self):
    node = self.head
    self.head = self.head.next
    if node == self.tail:
      self.tail = self.head
    return node.val
  
  @property
  def front(self):
    if self.head:
      return self.head.val
    else: 
      return None 
  
  def contains(self, value):
    runner = self.head 
    while runner:
      if runner.val == value:
        return True 
      runner = runner.next 
    return False 

  def is_empty(self):
    return True if not self.head else  False
  
  @property
  def size(self):
    count = 0  
    runner = self.head 
    while runner:
      count += 1
      runner = runner.next    
    return count 

  def compare_queues(self, a: SLQueue_t, b: SLQueue_t):
    size_a = a.size
    size_b = b.size
    
    if size_a != size_b:
      return False

    for i in range(0, size_a):
      if a.front != b.front:
        return False
      a.enqueue(a.dequeue())
      b.enqueue(b.dequeue())
    return True 
  
  def remove_min(self):
    min = None
    tmp = None 

    for i in range(0 , self.size):
      if min == None or self.front < min:
        min  = self.front
      self.enqueue(self.dequeue()) 
     
    for i in range(0 , self.size):
      tmp = self.dequeue()    
      if  tmp  != min:
        self.enqueue(tmp) 
  
  def interleave_queue(self):
    length = self.size
    mid  = math.floor (length  / 2) +  +(length % 2 == 1)
    tmp_queue = SLQueue()
    
    for i in range (0, length):
      if i < mid:
        self.enqueue(self.dequeue())
      else: 
        tmp_queue.enqueue(self.dequeue())
    
    length = self.size
    
    for i in range (0, length):
      self.enqueue(self.dequeue())
      if tmp_queue.front:
        self.enqueue(tmp_queue.dequeue())

  def display(self):
    runner = self.head
    if not runner:
      return None 

    while runner:
      print(runner.val)
      runner = runner.next
  
  def palindrome(self):
    stack = SLStack()
    result = True 

    while self.size:
      stack.push(self.front())
      self.enqueue(self.dequeue())
    while stack.size:
      result &= stack.top() == self.front()
      self.enqueue(self.dequeue())
    return result 

class ArrStack:
  def __init__(self):
    self.__collection = []
    self.size = 0
  
  def push(self, value):
    self.__collection = self.__collection + [value]
    self.size += 1

  def pop(self):
    result = None 
    if self.size:
      self.size -= 1
      result = self.__collection[self.size]
      self.__collection = self.__collection[0: self.size]
    return result
  
  def top(self):
    return self.__collection[0]
  
  def contains(self, value):
    return value in self.__collection
  
  def is_empty(self):
    return self.size == 0

  def display(self):
    print(self.__collection)

class SLStack:
  def __init__(self):
    self.head = None 
    self.tail = None 
    self.size = 0

  def top(self):
    return self.head.val

  def push(self, value):
    node = SLNode(value)
    if self.head == None:
      self.head = node
      self.tail = node 
    else:
      node.next = self.head 
      self.head = node 
    self.size += 1

  def pop(self):
    result = None 
    if self.head == None:
      return result  
    if self.head == self.tail:
      self.tail = None 
    result = self.head.val
    self.head = self.head.next 
    self.size -= 1
    return result 
  
  def contains(self, value):
    node = self.head
    while (node):
      if (node.val == value):
        return True
      node = node.next 
  
  def is_empty(self):
    return self.size == 0
  
  def remove_stack_min (self):
    queue = SLQueue()
    min_val = None  
    count = 0 
    data = None 

    while self.size:
      if min_val == None or self.top() < min_val:
        min_val = self.top()
        count += 1
      queue.enqueue(self.pop()) 
    
    while count:
      for i in range(0, count - 1):
        queue.enqueue(queue.dequeue())
      data = queue.dequeue()
      if (data != min_val):
        self.push(data)
      count -= 1  
       
  def display(self):
    runner = self.head 
    while runner:
      print(runner.val)
      runner = runner.next 


def compare_stacks(a: SLStack_t, b: SLStack_t):
  cmpr = True 
  length = None 

  stack = SLStack_t() 

  if a.size != b.size:
    return False 
  
  length = a.size

  for i in range (0, length):
      cmpr &= a.top == b.top
      stack.push(a.pop())
      stack.push(b.pop())
   
  for i in range (0, length):
     a.push(stack.pop())
     b.push(stack.pop())
  
  return cmpr

def copy_stack(stack: SLStack_t):
  queue = SLQueue()
  data = None 
  while stack.size:
    queue.enqueue(stack.pop())
  
  for i in range (queue.size - 1, -1, -1):
    for j in range (0, i):
      queue.enqueue(queue.dequeue())
    stack.push(queue.dequeue())

    

class Queue_Two_Stacks:
  def __init__(self):
    self.a = SLStack()
    self.b = SLStack()

  def push(self, value):
    while self.b.size:
     self.a.push(self.b.pop()) 
    self.a.push(value)
    while self.a.size:
      self.b.push(self.a.pop())
  
  def pop(self):
    result = None 
    
    while self.b.size:
      self.a.push(self.b.pop())
    
    result = self.a.pop()

    while self.a.size:
      self.b.push(self.a.pop())
  
    return result 


class StackQueueBase:
  def __init__(self):
    self._head = None 
    self._tail = None 
    self.size = 0

  def is_empty(self):
    return self.size == 0
  
  def contains(self, value):
    runner = self._head
    while runner:
      if runner.val == value:
        return True 
      runner = runner.next
    return False  

class SLQueue2(StackQueueBase):
  def __init__(self):
    super().__init__()

  def enqueue(self, value):
    node = SLNode(value)
    self.size += 1
    if self._head == None:
      self._head = node
      self.tail = node  
    else:
      self.tail.next = node
      self.tail = node 
  
  def dequeue(self):
    result = None
    if self.size:
      self.size -= 1
      result = self.head.val 
      if self.head == self.tail:
        self.tail = None 
      self.head = self.head.next  
    return result   

class SLStack2(StackQueueBase):
  def __init__(self):
    super().__init__()

  def push(self, value):
    node = SLNode(value)
    self.size += 1
    if self._head == None:
      self._head = node
      self._tail = node 
    else:
      node.next = self._head
      self._head = node 
  
  def pop (self):
    result = None 
    if self.size:
      if self._head == self._tail:
        self._tail = None 
      result = self._head.val
      self._head = self._head.next 
  

class Dequeue(SLStack2, SLQueue2):
  def __init__(self):
    super().__init__()
  
  def push_front(self, value):
    self.push(value)
  
  def pop_front(self):
    return self.pop()

  def push_back(self, value):
    self.enqueue(value)
  
  def pop_back(self):
    for i in range(0, self.size - 1):
      self.enqueue(self.dequeue())
    return self.pop()
  
  def front(self):
    return self._head.val

  def back(self):
    return self._tail.val
  
  def contains(self, value):
    return self.contains(value)

  def is_empty(self):
    return self.is_empty()

class CirQueue():
  def __init__(self, size = 10):
    self.head = None
    self.tail = None 
    self.capacity = size
    self.size = 0

  def front(self):
    return self.head.val
  
  def is_empty(self):
    return self.size == 0

  def is_full(self):
    return self.size == self.capacity 
  
  def contains(self, value):
    runner = self.head
    while runner:
      if value == runner.val:
        return True 
      runner = runner.next
    return False 
  
  def enqueue(self, value):
    if self.size < self.capcity:
      node = SLNode(value)
      if self.head == None:
        self.head = node 
        self.tail = node 
      else:
        self.tail.next = node 
        self.tail = node 
      self.size += 1

  def dequeue(self):
    result = None 
    if self.size:
      if (self.tail == self.head):
        self.tail = None 
      result = self.head.val
      self.head = self.head.next
      self.size -= 1
    return result 
  
  def grow (self, size):
    runner = None 
    count = 0 
    if (size < self.capacity and  size > 0):
      while runner and count < size :
        if count == 0:
          runner = self.head
        else:
          runner = runner.next 
        count += 1
      runner.next = None # break chain
    self.capacity = size 

def reorder_absolute_queue(queue: SLQueue_t):
  stack = SLStack()
  data = None 

  while queue.size:
    data = queue.dequeue()
    while stack.size > 0 and stack.top() < data:
      queue.enqueue(stack.pop())
    stack.push(data)
  while stack.size:
    queue.enqueue(stack.pop())

def partition(stack: SLStack_t):
  queue = SLQueue()
  count = 0

  while stack.size:
    queue.enqueue(stack.pop())
    count += 1
  
  for i in range (0, count):
    data = queue.dequeue()
    if data >= 0:
      stack.push(data)
    else:
      queue.enqueue(data)
    
    while queue.size:
      stack.push(queue.dequeue())

def switch_pairs(stack: SLStack_t):
  queue = SLQueue()
  count = 0

  while stack.size:
    queue.enqueue(stack.pop())
    count += 1

  while count > 0:
    rot = count -2
    for i in range (0, rot):
      queue.enqueue(queue.dequeue())
    
    if queue.size:
      stack.push(queue.dequeue())
    if queue.size:
      stack.push(queue.dequeue())
    count -= 2
  while queue.size:
    stack.push(queue.dequeue())
 
def is_sorted(stack:SLStack_t):
  stack2 = SLStack()
  sorted_stack = True
  count = 0 

  while stack.size:
    if stack2.size:
      sorted_stack &= stack.top() < stack2.top()
    stack2.push(stack.pop())
  return sorted_stack

def mirror(stack: SLStack_t):
  stack_tmp = SLStack()
  count = 0
  data = None 

  while stack.size:
    stack_tmp.push(stack.pop())

  while (stack_tmp.size):
    data = stack_tmp.pop()
    count = 0
    
    while stack.size:
      count += 1
      stack_tmp.push(stack.pop())
    
    stack.push(data)
    while count > 0:
      stack.push(stack_tmp.pop())
      count -= 1
    stack.push(data)






