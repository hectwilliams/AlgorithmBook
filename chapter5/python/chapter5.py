class LLNode:
  def __init__(self, val):
    self.value = val
    self.next = None

class LList:
  def __init__(self):
    self.head = None 

  def addFront(self,value, node = None):
    if node == None:
      node = self.head
    new_node = LLNode(value)
    if node:
      new_node.next = node
    self.head = new_node
    return self.head

  def contains(self, val, node):
    if node == None:
      node = self.head
    while node != None:
      if node.value == val:
        return True 
    return False 

  def removeFront(self, node = None):
    if node:
      tmp = node
      node  = node.next
      del tmp
      return tmp

  @property
  def front(self):
    return self.head

  @property 
  def length(self, node = None ):
    count = 0
    if node == None:
      node = self.head
    while node:
      node = node.next
      count = count + 1
    return count 
  
  def display(self, node = None):
    if not node:
      node = self.head 
    while node:
      print(node.value , end =' ')
      node = node.next
  
  def max(self, node = None):
    max = None
    while node:
      if max == None or node.value > max:
        max = node.value
    node = node.next 
    return max 

  def min(self, node = None):
    min = None
    while node:
      if min == None or node.value < min:
        min = node.value
    node = node.next 
    return min

  def average(self, node = None):
    avg = 0
    count = 0
    while node:
      avg += node.value
      count += 1
      node = node.next
    if count :
      return avg / count
    else :
      return None 

  def prependVal(self, val, before, node = None):
    new_node = LLNode(val)

    if node == None:
      node = self.head
    
    if node.value == before:
      new_node.next = self.head 
      self.head = new_node
    else:
      while node.next:
        if node.next.value == before:
          new_node.next = node.next
          node.next = new_node
          break
        node = node.next
    return self.head 
   
  def appendVal(self, val, after, node = None):
    new_node = LLNode(val)

    if node == None:
      node = self.head

    while node:
      if node.value == after:
        new_node.next = node.next
        node.next = new_node
        node = new_node.next 
      else:
        node = node.next

  def removeVal(self, val, node = None):
    prev = None 
    tmp = None 
    
    if node == None:
      node = self.head
    
    while node:
      if node.value == val:
        tmp = node 
        node = node.next
        if prev == None:
          if tmp == self.head:
            self.head = node 
        else:
          prev.next = node
      else:
        prev = node 
        node = node.next 

  def splitOnValue(self, llist = None, num = None):
    resultList = LList()
    node = None
    prev = None 

    if llist == None:
      node = self.head
    else:
      node = llist.head
    
    while node:
      if node.value == num:
        resultList.head = node
        if prev == None:
          llist.head = None 
        else:
          prev.next = None 
      prev = node
      node = node.next
    return resultList

  def concat(self, nodeA, nodeB):
    node = None 

    if not nodeA or not nodeB:
      return None 
    
    node = nodeA
    while node.next:
      node = node.next
    node.next = nodeB
    return nodeA

  def removeNegatives(self, node = None):
    tmp = None
    prev = None 
    head = self.head 
    node = head 

    while node:
      if node.value < 0:
        tmp = node
        node = node.next
        if prev == None:
          head = head.next
        else:
          prev.next = node
      else:
        prev = node 
        node = node.next 
    return head

  def partition(self, value, node = None):
    prev = None 
    new_head = None 
    head = node 

    if node == None:
      node = self.head
      head = node 

    while node:
      if node.value <= value and prev:
        new_head = node
        prev.next = new_head.next
        node = new_head.next
        new_head.next = head
        head = new_head
      else:
        prev = node       
        node = node.next
    return head

  def secondToLastValue(self, node = None):
    buffer = [None, None]
    if node == None:
      node = self.head

    while node:
      buffer[0], buffer[1] = buffer[1], buffer[0]
      buffer[1] = node.value
      node = node.next 
    return buffer[0]
  
  def deleteGivenNode(self, node = None):
    tmp = None 

    if node == None:
      node = self.head
    
    if node.next:
      tmp = node
      node.value = node.next.value
      node.next = node.next.next
      del tmp

  def copy(self, node = None):
    head = None
    runner = None
    new_node = None

    if node == None:
      node = self.head 
    
    while node:
      new_node = LLNode(node.value)
      if head == None:
        head = new_node
        runner = head 
      else:
        runner.next = new_node
        runner = runner.next
      node = node.next  
    return head

  def filter(self, low, high, node = None):
    tmp = None 
    prev = None 
    head = node 
    
    if node == None:
      node = self.head
      head = node 

    while node:
      if (node.value < low or node.value > high):
        tmp = node 
        node = node.next 
        if prev == None:
          head = node 
        else:
          prev.next = node 
        del tmp 
      else:
        prev = node 
        node = node.nex 
    return head

  def secondLargestValue (self, node = None):
    buffer = [None, None]
    
    if node == None:
      node = self.head 
    
    while node:
      if buffer[1] == None:
        buffer[1] = node.value
      elif buffer[0] == None:
        buffer[0] = node.value
      else:
        if node.value > buffer[1]:
          buffer[1] = node.value 
      if buffer[1] > buffer[0]:
        buffer[0], buffer[1] = buffer[1], buffer[0]
      node = node.next
    return buffer[0]

  def dedupe(self, node):
    runner = None 
    head = None 
    prev = None 
    tmp = None 

    if node == None:
      node = self.head 
    
    head = node
    
    while node:
      prev = runner 
      runner = node.next
      while runner:
        if runner.value == node.value:
          tmp = runner
          prev.next = tmp.next
          del tmp
        prev = runner  
        runner = runner.next 
      node = node.next 
    self.display(head)


  def zip(self, nodeA, nodeB):
    cntA = 0
    cntB = 0
    head = None 
    runner = None 

    if not nodeA or not nodeB:
      return None
    
    while nodeA or nodeB:
      if head == None and nodeA:
        head = nodeA
        runner = nodeA
        nodeA = nodeA.next 
        cntA += 1

      elif head == None and nodeB:
        head = nodeB
        runner = nodeB
        nodeB = nodeB.next
        cntB += 1

      elif cntA == cntB and nodeA:
        runner.next = nodeA
        runner = runner.next
        nodeA = nodeA.next 
        cntA += 1

      elif cntA > cntB and nodeB:
        runner.next = nodeB
        runner = runner.next
        nodeB = nodeB.next 
        cntB += 1

      elif not nodeA:
        runner.next = nodeB
        break

      elif not nodeB:
        runner.next = nodeA
        break

    self.display(head)
    return head

