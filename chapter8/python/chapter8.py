
class SLNode:
  def __init__(self, value):
    self.val = value
    self.next = None 

class SList:
  def __init__(self):
    self.head = None 
  
  @property
  def tail(self):
    runner = self.head
    if (runner == None):
      return runner
    while runner.next:
      runner = runner.next
    return runner

  def pushFront(self, value):
    node = SLNode(value)
    node.next = self.head
    self.head = node
  
  def popFront(self):
    retValue = None 
    if self.head:
      retValue = self.val
    return retValue
  
  def pushBack(self, value):
    node = None
    runner = None  
    if (self.head == None):
      self.pushFront(value)
    else:
      node = SLNode(value)
      runner = self.head 
      while runner.next:
        runner = runner.next 
      runner.next = node 
    
  def contains (self,value):
    runner = this.head 
    while runner:
      if runner.val == value:
        return True
    return False 

  def popBack(self):
    retValue = None 
    runner = self.head
    newTail = None 
    
    if self.head == None :
      return retValue
    
    while runner.next:
      newTail = runner 
      runner = runner.next 
    retValue = runner.val
    
    if runner == self.head:
      self.head = None 
    
    if newTail:
      newTail.next = None 
    
    del runner 
    return retValue

  def removeVal (self, value):
    runner = self.head
    runner_prev = None
    del_node = None   
    rslt = false 
    while (runner):
      if (runner.val == value):
        rslt |= True
        del_node = runner 
        if ( runner == self.head):
          self.head = self.head.next
          runner = self.head
        else:
          runner_prev.next = runner.next
          runner = runner_prev
        del del_node
    runner_prev = runner
    runner = runner.next

  def reverse(self):
    tmp_node  = SLNode(0)
    tmp_node_next = None 
 
    if (self.head == None):
      return None 
    
    while self.head:
      tmp_node.next = self.head 
      self.head = self.head.next
      tmp_node.next.next = tmp_node_next
      tmp_node_next = tmp_node.next
    
    if (tmp_node.next):
      self.head = tmp_node.next
    
    del tmp_node
  
  def isPalindrome(self):
    runner = None 
    start = self.head 
    end = None 

    if start == None:
      return False

    while 1 :
      runner = start 
      while runner.next != end:
        runner = runner.next
      end = runner;  
      if start.val != end.val:
        return False
      if end.next == start or start != end:
        break
      start = start.next
    return True
  
  def kthLastNode(self, k):
    runner = None 
    count = None 
    start = self.head

    while start:
      runner = start
      count = 0  
      
      while runner:
        count += 1
        runner = runner.next
      
      if count == k:
        return start.val
      
      start = start.next
    return None 
  
  def shiftRight(self, n):
    runner = None
    runner_prev = None  
    
    if n < 0:
      return shiftLeft(n * -1)
      
    for i in range(0, n):
      runner = self.head 
      while runner.next:
        runner_prev = runner
        runner = runner.next
      runner.next = self.head
      self.head = runner
      runner_prev.next = None 

  def shiftLeft (self, n):
    newTail = None 
    runner = None 

    if (self.head):
      for i in range(0, n):
        newTail = self.head
        self.head = self.head.next
        runner  = self.head
        while runner.next:
          runner = runner.next
        runner.next = newTail
        newTail.next = None 

  def display(self):
    runner = self.head 
    while runner:
      print(runner.val, end='')
      runner = runner.next 
    print()

llist = SList()
llist.pushBack(2)
llist.pushFront(4)
llist.pushFront(6)


llist.shiftLeft(1)
llist.display()
