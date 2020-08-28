class BSTNode:
  def __init__(self, value):
    self.value = value
    self.parent = None
    self.left = None
    self.right = None
class BST:
  def __init__(self):
    self.root = None
  def display(self, node = None ):
    node = self.root if not node else node
    if node:
      if node.left:
        self.display(node.left)
      print(node.value)
      if node.right:
        self.display(node.right)
  def add(self, value, node = None ):
    node = self.root if not node else node

    if not node:
      self.root = BSTNode(value)

    else:
      if value < node.value:
        if node.left:
          self.add(value, node.left)
        else:
          node.left = BSTNode(value )
      else:
        if node.right:
          self.add(value, node.right)
        else:
          node.right = BSTNode(value)

  @staticmethod
  def remove_successor (node):
    prev = node
    if node.right:
      node = node.right
      while node.left:
        prev = node
        node = node.left

      if prev.left == node:
        prev.left = None
      else:
        prev.right = None
    return node

  def remove(self, value, node = None, prev = None):
    successor = None
    node = self.root if not node else node
    if node == None :
      return
    if node.value == value :
      if bool(node.left) and bool(node.right) :
        successor = BST.remove_successor(node)
        successor.left = node.left
        successor.right = node.right

        if prev == None:
          self.root = successor
        else:
          if prev.left == node:
            prev.left = successor
          else:
            prev.right = successor
      elif bool(node.left) ^ bool( node.right):
        if prev == None :
          self.root = node.right if not node.left else node.left
        else:
          if prev.left == node:
            prev.left = node.right if not node.left else node.left
          else:
            prev.right = node.right if not node.left else node.left
      elif bool(not node.left) and bool(not node.right) :
        if prev == None:
          self.root = None
        else:
          if prev.left == node:
            prev.left = None
          else:
            prev.right = None
    else:
      if node.left and value < node.value:
        self.remove(value, node.left, node)
      elif node.right:
        self.remove(value, node.right, node)

  def height (self, node = None):
    left = right = 0
    if node.left:
      left = 1 + self.height(node.left)
    if node.right:
      right = 1 + self.height(node.right)

    return  (right if right > left else left)

  def isFull (self, node= None):
    isfull = False
    node = self.root if not node else node

    if node:
      isfull = bool(node.right and node.left) ^ bool(not node.right and not node.left)
      if node.left:
        isfull &= self.isFull(node.left)
      if node.right:
        isfull &= self.isFull(node.right)
    return isfull

  def isComplete(self, node = None):
    node = self.root if not node else node
    left = right = 0
    iscomplete = False

    if node:
      if node.left:
        left = self.height(node.left)
      if node.right:
        right = self.height(node.right)

      iscomplete = left >= right

      if node.left:
        iscomplete &= self.isComplete(node.left)

      if node.right:
        iscomplete &= self.isComplete(node.right)

    return iscomplete