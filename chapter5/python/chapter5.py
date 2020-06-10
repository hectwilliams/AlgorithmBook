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
      del tmp;
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

