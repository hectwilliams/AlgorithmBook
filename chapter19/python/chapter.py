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
      print( '[', str(node.value) + '- bal  ' + str(node.balance), ']')
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
          if self.add(value, node.left) :
            node.balance += 1
            return 1
        else:
          node.left = AVLNode(value)
          node.balance += 1
          return 1
      if value > node.value:
        if node.right:
          if self.add(value, node.right):
            node.balance -= 1
            return 1
        else:
          node.right = AVLNode(value)
          node.balance -= 1
          return 1
      if value == node.value:
        node.count += 1
    return self

  def __removeHelper(self, parent, node):
    runner = ancestor = None

    if node.count > 1:
      node.count -= 1
    elif node.left == None and node.right == None :
      if parent == None :
        self.head = None
      elif parent.left == node:
        parent.left = None
      elif parent.right == node:
        parent.right = None
    elif bool(node.left) and not bool(node.right):
      if parent == None:
        self.head = node.left
      elif parent.left == node:
        parent.left = node.left
      elif parent.right == node:
        parent.right = node.left
    elif bool(node.right) and not bool(node.left) :
      if parent== None:
        self.head = node.right
      elif parent.left == node:
        parent.left = node.right
      elif parent.right == node:
        parent.right = node.right

    elif bool(node.right) and bool(node.left) :

      if node.right.left == None:
        node.right.left = node.left

        if parent == None :
          self.head = node.right
        elif parent.left == node:
          parent.left = node.right
        elif parent.right == node :
          parent.right = node.right
      else :
        runner = node.right
        while runner.left.left:
          runner = runner.left
        ancestor = runner.left
        runner.left = runner.left.left

        ancestor.left = node.left
        ancestor.right = node.right
        if parent == None :
          self.head = ancestor
        elif parent.left == node:
          parent.left = ancestor
        elif parent.right == node:
          parent.right = ancestor

    return True

  def remove (self, value, node = None):
    if node == None:
      node = self.head
    if node:
      if value == node.value:
        return self.__removeHelper(None, node)
      elif value < node.value:
        if node.left:
          if (node.left.value == value):
            return self.__removeHelper(node, node.left)
          else:
            return self.remove(value, node.left)
      elif value > node.value:
        if node.right:
          if node.right.value == value:
            return self.__removeHelper(node, node.right )
          else:
            return self.remove(value, node.right)
    return False

  def height (self, node = None):
    lheight = rheight = 0

    if node == None:
      node = self.head

    if node:
      if node.left:
        lheight = 1 + self.height(node.left)
      if node.right:
        rheight = 1 + self.height(node.right)

    if rheight > lheight:
        return rheight
    else:
      return lheight


tree = AVLTree()

tree.add(10)
tree.add(8)
tree.add(12)

# tree.remove(10)
# tree.display()
# # expect 8 12

# tree.remove(12)
# tree.display()
# # expect 8 10

# tree.remove(8)
# tree.display()
# # expec 10 12

# tree.add(11)
# tree.add(14)
# tree.add(4)
# tree.add(6)

# tree.remove(8)
# tree.display()
# // 4 6 10 11 12 14

# tree.add(1)

# tree.remove(4)
# tree.display()
# // 1 6 8 10 11 12 14

# tree.remove(10)
tree.display()
print(tree.height())
# // 1 4 6 8 11 12 14

