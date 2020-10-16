class AVLNode :

  def __init__(self, value) :
    self.value = value
    self.left = None
    self.right = None
    self.balance = 0
    self.count = 1

  def height (self, node = None):
    if not bool(node):
      node = self

    if node:
      if node.left == None and node.right == None:
        return 0
      if (node.balance > 0) :
        return 1 + self.height(node.left)

      if (node.balance < 0) :
        return 1 + self.height(node.right)

    return 0

  def isBalanced (self):
    return abs(self.balance) <= 1

  def inOrderSuccessor (self):
    runner = self.right
    while runner.left:
      runner = runner.left
    return runner.value

  def copyAttributes(self, src):
    self.balance = src.balance
    self.left = src.left
    self.right = src.right
    self.count = src.count
    self.value = src.value

  def updateBalanceAck(self, isValid, level):
    prevBal = self.balance

    if isValid:
      self.balance += level
      if prevBal == 0:
        isValid = 0
    return isValid

  def removeHelper(self, parent, updateRootCallback, removeCallback):
    isRoot = (self == parent)
    successor = None
    flag = True

    if self.left != None and self.right != None :
      successor = self.inOrderSuccessor()
      flag = removeCallback(successor, self)
      flag = self.updateBalanceAck(flag , 1)
      self.value = successor

    elif self.right:
      self.copyAttributes(self.right)
      if not bool(isRoot):
        parent.balance += 1

    elif self.left:
      self.copyAttributes(self.left)
      if not (isRoot):
        parent.balance -= 1

    elif self.left == None and self.right == None :

      if isRoot:
        updateRootCallback(None)

      elif parent.right == self:
        parent.balance += 1
        parent.right = None
        if parent.left:
          flag = False

      elif parent.left == self:
        parent.balance -= 1
        parent.left = None
        if parent.right:
          flag = False

    return flag

  def calculateBalance(self):
    self.balance = (1 + self.left.height()) - (1 + self.right.height())

class AVLTree:
  def __init__(self):
    self.head = None

  def display(self, node = None):
    if node == None:
      node = self.head

    if node:
      if node.left:
        self.display(node.left)
      print ("value: ", node.value, " ", "balance: ", node.balance, sep="")
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
            return (node.balance != 0)
        else:
          node.left = AVLNode(value)
          node.balance += 1
          return (node.balance != 0)

      if value > node.value:
        if node.right:
          if self.add(value, node.right):
            node.balance -= 1
            return (node.balance != 0)
        else:
          node.right = AVLNode(value)
          node.balance -= 1
          return (node.balance != 0)

      if value == node.value:
        node.count += 1

    return 0

  def remove(self, value, node = None):
    flag = False

    def setRoot(val):
      self.head = val

    if node == None:
      node = self.head
      if not node:
        return

    if node.value == value:
      flag = node.removeHelper(node, setRoot, self.remove)

    elif value < node.value:
      if node.left:
        if node.left.value == value:
          flag = node.left.removeHelper(node, setRoot, self.remove)
        else:
          flag = self.remove(value, node.left)
          flag = node.updateBalanceAck(flag , -1)

    elif value > node.value:
      if node.right:
        if node.right.value == value:
          flag = node.right.removeHelper(node, setRoot, self.remove)
        else:
          flag = self.remove(value, node.right)
          flag = node.updateBalanceAck(flag ,  1)

    print(node.value, node.balance)

    return flag

class RBNode:
  def __init__(self, value):
    self.color = 1
    self.left = None
    self.right = None
    self.value = value
    self.count = 1

class RBTree:
  def __init__(self):
    self.root = None
  def contains(self, value, node = None ):
    if node == None:
      node = self.root
    if node:
      if node.value == value:
        return True
      elif value < node.value:
        return self.contains(value, node.left)
      elif value > node.value :
        return self.contains(value, node.right)
    return False

  def __translate (self, node, parent = None, code = -1):
    c = gc = gc_l = gc_r = tree = None

    #/ function
    def paint():
      node.color = 1
      node.left.color = node.right.color = 0

    def ll (): # left left
      c = node.left
      tree = c.right

      c.right = node
      node.left = tree

      c.color = 0
      c.left.color = c.right.color = 1

      if parent == None:
        self.root = c
      elif parent.left == node:
        parent.left = c
      elif parent.right == node:
        parent.right = c

    def lr ():  # left right
      c = node.left
      gc = node.left.right
      gc_l = gc.left
      gc_r = gc.right

      gc.left = c
      gc.right = node
      node.left = gc_r
      c.right = gc_l

      gc.color = 0
      gc.left.color = gc.right.color = 1

      if parent == None:
        self.root = gc
      elif parent.left == node:
        parent.left = gc
      elif parent.right == node:
        parent.right = gc

    def rr ():
      c = node.right
      tree = c.left

      c.left = node
      node.right = tree

      c.color = 0
      c.left.color = c.right.color = 1

      if parent == None:
        self.root = c
      elif parent.left == node:
        parent.left = c
      elif parent.right == node:
        parent.right = c


    def rl ():
      c = node.right
      gc = node.right.left
      gc_l = gc.left
      gc_r = gc.right

      gc.right = c
      gc.left = node
      node.right = gc_l
      c.left = gc_r

      gc.color = 0
      gc.left.color = gc.right.color = 1

      if parent == None:
        self.root = gc
      elif parent.left == node :
        parent.left = gc
      elif parent.right == node :
        parent.right = gc


  # select function
    case = {
      0: paint,
      1: ll,
      2: lr,
      3: rr,
      4: rl
    }

  # swtich
    def switcher (arg):
      func = case.get(arg)  # get callback and call function
      func()
  # execute
    switcher(code)

  # root node must be black
    if self.root.color:
      self.root.color = 0

  def add(self, value, node = None , parent = None):
    acc  = 0

    if self.root == None :
      self.root = RBNode(value)
      self.root.color = 0
    else:
      if node == None:
        node  = self.root

      if value < node.value:
        if node.left:
          acc = self.add(value, node.left, node)
          acc += (node.left.color)

          if acc == 2:
            acc = 0
            if node.right == None:
              if node.left and node.left.left:
                self.__translate(node, parent, 1)
              elif node.left and node.left.right:
                self.__translate(node.parent, 2)
            elif node.right.color == 0  :
              if node.left and node.left.left:
                self.__translate(node, parent, 1)
              elif node.left and node.left.right:
                self.__translate(node, parent, 2)
            elif node.right.color:
              self.__translate(node, parent , 0)
        else:
          node.left = RBNode(value)
          acc = 1

      elif value > node.value:
        if node.right:
          acc = self.add(value, node.right, node)
          acc += (node.right.color)
          if acc == 2:
            acc = 0
            if node.left == None:
              if node.right and node.right.right:
                self.__translate(node, parent , 3)
              elif node.right and node.right.left:
                self.__translate(node, parent, 4)
            elif node.left.color == 0:
              if node.right and node.right.right:
                self.__translate(node, parent ,3)
              elif node.right and node.right.left:
                self.__translate(node, parent, 4)
            elif node.left.color :
              self.__translate(node, parent, 0)
        else:
          node.right = RBNode(value)
          acc = 1

      elif value == node.value:
        node.count += 1
        acc = 0

      if node.color == 0  :
        acc = 0

    return acc


  def display(self, node = None):
    if node == None:
      node = self.root
    if node :
      if node.left:
        self.display(node.left)
      print ("value: ", node.value, " ", "color: ", node.color, sep="")
      if node.right:
        self.display(node.right)

  def __removeHelper(self, parent = None, node = None) :
    successor = None
    parentOfSuccessor = None

    if node.count > 1:
      node.count -= 1
    elif not bool(node.right) and not bool(node.left):
      successor = None
    elif bool(node.left) and not bool(node.right):
      successor = node.left
    elif bool(node.right) and not bool(node.left) :
      successor = node.right
    elif bool(node.left) and bool(node.right):
      if node.right.left == None:
        successor = node.right
        successor.left = node.left
      else:
        parentOfSuccessor = node.right
        while parentOfSuccessor.left.left:
          parentOfSuccessor = parentOfSuccessor.left

        successor = parentOfSuccessor.left
        parentOfSuccessor.left = parentOfSuccessor.left.left

        successor.left = node.left
        successor.right = node.right
        successor.count = node.count

    if parent == None:
      self.root = successor
    elif parent.left == node:
      parent.left = successor
    elif parent.right == node:
      parent.right = successor

  def remove(self, value, node = None) :
    if node == None:
      node = self.root

    if node:
      if node.value == value:
        self.__removeHelper(None, node)
      elif value < node.value:
        if node.left:
          if node.left.value == value:
            self.__removeHelper(node, node.left)
          else:
            self.remove(value, node.left)
      elif value > node.value:
        if node.right:
          if node.right.value == value:
            self.__removeHelper(node, node.right)
          else:
            self.remove(value, node.right)


# tree =  RBTree()
# tree.add(3)
# tree.add(1)
# tree.add(5)
# tree.add(7)
# tree.add(6)
# tree.add(8)
# tree.add(9)
# tree.add(10)

# tree.remove(6)

# tree.display()


tree = AVLTree()
data = [
100,
50,       500,
25,      450,        1000,
20,     300,  480,   900,   2000,
15,    200,          800
]

for ele in data:
  tree.add(ele)

tree.remove(450)
tree.display()
