
class SLNode:
  def __init__(self, value):
    self.val = value
    self.next = None 

class SList:
  def __init__(self, value):
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
        if ( runner = self.head):
          self.head = self.head.next
          runner = self.head
        else:
          runner_prev.next = runner.next
          runner = runner_prev
        del del_node
    runner_prev = runner
    runner = runner.next
