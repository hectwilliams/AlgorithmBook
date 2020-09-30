class AVLNode :
  def __init__(self, value) :
    self.value = value
    self.left = None
    self.right = None
    self.balance = 0
    self.count = 1

class AVLTree:
  def __init__(self):
    self.head = None

  def display(self, node = None):
    if node == None:
      node = self.head

    if node:
      if node.left:
        self.display(node.left)
      print(node.value)
      if node.right:
        self.display(node.right)

  def add (self, value, node = None ):
    if node == None:
      node = self.head

    if node == None:
      self.head = AVLNode(value)
    else:
      if value < node.value:
        if node.left:
          return self.add(value, node.left)
        else:
          node.left = AVLNode(value)
      if value > node.value:
        if node.right:
          return self.add(value, node.right)
        else:
          node.right = AVLNode(value)
      if value == node.value:
        node.count += 1
    return self

tree = AVLTree()
tree.add(8).add(10).add(12)
tree.display()