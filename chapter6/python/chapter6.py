from typing import NewType
import math 

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

  def compare_queues(self, queue_a, queue_b):
    size_a = queue_a.size
    size_b = queue_b.size
    
    if size_a != size_b:
      return False

    for i in range(0, size_a):
      if queue_a.front != queue_b.front:
        return False
      queue_a.enqueue(queue_a.dequeue())
      queue_b.enqueue(queue_b.dequeue())
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
    

queue = SLQueue()
queue.enqueue(1)
queue.enqueue(2)
queue.enqueue(3)
queue.enqueue(4)
queue.enqueue(5)

queue.interleave_queue()