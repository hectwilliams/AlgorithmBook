class LLNode:
  def __init__(self, val):
    self.value = val
    self.next = None

class LList:
  def __init__(self):
    self.head = None 

  def addFront(self, node, value):
    new_node = LLNode(value)
    if node:
      new_node.next = node
    self.head = new_node
    return self.head

  def contains(self, node, val):
    if node == None:
      node = self.head
    while node != None:
      if node.value == val:
        return True 
    return False 

  def removeFront(self, node):
    if node:
      tmp = node
      node  = node.next
      del tmp;
      return tmp

  def front(self):
    self.head
