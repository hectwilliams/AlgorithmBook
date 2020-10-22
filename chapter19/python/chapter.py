class AVLNode :

  def __init__(self, value) :
    self.value = value
    self.left = None
    self.right = None
    self.balance = 0
    self.count = 1

  def height (self, node = None):

    if node:
      if not bool(node.left) and not bool(node.right):
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

  def removeHelper(self, parent, AVLClass):
    isRoot = (self == parent)
    successor = None
    flag = True

    if self.left != None and self.right != None :
      successor = self.inOrderSuccessor()
      flag = AVLClass.remove(successor, self)
      flag = self.updateBalanceAck(flag , 1)
      self.value = successor

    elif self.right:
      self.copyAttributes(self.right)
      if not bool(isRoot):
        parent.balance += 1

    elif self.left:
      self.copyAttributes(self.left)
      if not bool(isRoot):
        parent.balance -= 1

    elif self.left == None and self.right == None :

      if isRoot:
        AVLClass.head = None

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
    self.balance = (1 + self.height(self.left))   - (1 + self.height(self.right))

  def leftRotateTranslate (self, parent, avlObj) :
    c  = t = promote = None

    promote = self.right

    if self.right.balance > 0:
      promote = self.right.left
      avlObj.rightRotate(self.right, self)   # (target, runnr))

    c = self.right
    t = c.left

    c.left = self
    self.right = t

    self.calculateBalance()
    c.calculateBalance()

    if parent == self:
      avlObj.head = promote

    elif parent.left == self:
      parent.left = promote

    elif parent.right == self:
      parent.right = promote


  def rightRotateTranslate(self, parent, avlObj) :
    c = t = promote = None

    promote = self.left

    if self.left.balance < 0 :
      promote = self.left.right
      avlObj.leftRotate(self.left, self)    # (target, runnr))

    c = self.left
    t = c.right

    c.right = self
    self.left = t

    self.calculateBalance()
    c.calculateBalance()

    if parent == self :
      avlObj.head = promote

    elif parent.left == self:
      parent.left = promote

    elif parent.right == self:
      parent.right = promote

  def balanceCheck (self, avlClass):

    if self.balance > 1:
      avlClass.rightRotate(self)
    elif self.balance < -1:
      avlClass.leftRotate(self)

  def repair (self, avlClass ):

    if self.left:
      self.left.repair(avlClass)

    if self.right:
      self.right.repair(avlClass)

    if self.left:
      while abs(self.left.balance) > 1:
        self.left.balanceCheck(avlClass)
      self.calculateBalance()

    if self.right:
      while abs(self.right.balance) > 1:
        self.right.balanceCheck(avlClass)
      self.calculateBalance()

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

    if node == None:
      node = self.head
      if not node:
        return

    if node.value == value:
      flag = node.removeHelper(node, self)

    elif value < node.value:
      if node.left:
        if node.left.value == value:
          flag = node.left.removeHelper(node, self)
        else:
          flag = self.remove(value, node.left)
          flag = node.updateBalanceAck(flag , -1)

    elif value > node.value:
      if node.right:
        if node.right.value == value:
          flag = node.right.removeHelper(node, self)
        else:
          flag = self.remove(value, node.right)
          flag = node.updateBalanceAck(flag ,  1)

    return flag


  def leftRotate(self, target, node = None) :

    if not node:
      node = self.head
      if not node:
        return

    if target.right:

      if node == target:
        node.leftRotateTranslate(node, self )

      elif target.value < node.value:
        if node.left == target:
          node.left.leftRotateTranslate(node, self )
        else:
          self.leftRotate(target, node.left)

      elif target.value > node.value:
        if node.right == target:
          node.right.leftRotateTranslate(node, self )
        else:
          self.leftRotate(target, node.right)

  def rightRotate(self, target, node = None) :

    if node == None:
      node = self.head
      if not node:
        return

    if target.left:
      if node == target:
        node.rightRotateTranslate(node, self)

      elif target.value < node.value:
        if node.left == target:
          node.left.rightRotateTranslate(node, self)
        else:
          self.rightRotate(target, node.left)

      elif target.value > node.value :
        if node.right == target:
          node.right.rightRotateTranslate(node, self)
        else:
          self.rightRotate(target, node.right)

  def balancedAdd(self, value, node = None) :
    ret = 0

    if not node:
      node = self.head

    if self.head == None:
      self.head = AVLNode(value)

    elif value < node.value:
      if node.left:
        if self.balancedAdd(value, node.left) :
          node.balance += 1

        node.left.balanceCheck(self)

      else:
        node.balance += 1
        node.left = AVLNode(value)

      ret =  node.balance != 0

    elif value > node.value:

      if node.right:

        if self.balancedAdd(value, node.right) :
          node.balance -= 1

        node.right.balanceCheck(self)

      else:
        node.balance -= 1
        node.right = AVLNode(value)

      ret = node.balance != 0

    elif value == node.value:
      node.count += 1


    if node == self.head:
      self.head.balanceCheck(self)

    return ret

  def balancedRemove(self, value, node = None):
    flag = False

    if not node:
      node = self.head
      if not node:
        return

    if node.value == value:
      flag = node.removeHelper(node, self)

    elif value < node.value:

      if node.left:
        if node.left.value == value:
          flag = node.left.removeHelper(node, self)
        else:
          flag = self.remove(value, node.left)
          flag = node.updateBalanceAck(flag , -1)

      node.left.balanceCheck(self)

    elif value > node.value:
      if node.right:
        if node.right.value == value:
          flag = node.right.removeHelper(node, self)
        else:
          flag = self.remove(value, node.right)
          flag = node.updateBalanceAck(flag ,  1)

      node.right.balanceCheck(self)

    if node == self.head:
      node.balanceCheck(self)

    return flag

  def repair(self):
    self.head.repair(self)

class RBNode:
  def __init__(self, value):
    self.color = 1
    self.left = None
    self.right = None
    self.value = value
    self.count = 1

  def display(self):
    if self.left:
      self.left.display()

    print(self.value, self.color)

    if self.right:
      self.right.display()

  def rightRotate(self, parent, rbTreeClass) :
    c = None
    t = None

    c = self.left
    t = c.right

    c.right = self
    self.left = t

    if self == parent:
      rbTreeClass.root = c

    elif parent.left == self:
      parent.left = c

    elif parent.right == self:
      parent.right = c

  def leftRotate(self, parent, rbTreeClass) :
    c = None
    t = None

    c = self.right
    t = c.left

    c.left = self
    self.right = t

    if self == parent:
      rbTreeClass.root = c

    elif parent.left == self:
      parent.left = c

    elif parent.right == self:
      parent.right = c

  def rotationCode(self):
    leftColor = rightColor = 0

    if not self.left :
      leftColor = 0
    elif self.left.color:
      leftColor = 1

    if not self.right :
      rightColor = 0
    elif self.right.color:
      rightColor = 1


    if self.left:

      if self.left.left:
        if self.left.color and self.left.left.color:
          if rightColor:
            return 5
          return 1

      if self.left.right:
        if self.left.color and self.left.right.color:
          if rightColor:
            return 5
          return 2

    if self.right:


      if self.right.right:
        if self.right.color and self.right.right.color:
          if leftColor:
            return 5
          return 3

      if self.right.left:
        if self.right.color and self.right.left.color:
          if leftColor:
            return 5
          return 4

    return 0

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


  def display(self):
    self.root.display()

  def add(self, value, node = None, parent = None):
    count = 0

    if not node :
      parent = node = self.root

    if not self.root :
      self.root = parent = node = RBNode(value)

    elif value < node.value:
      if node.left:
        count += self.add(value, node.left, node)
      else:
        node.left = RBNode(value)
        return 1 + node.color

    elif value > node.value:
      if node.right:
        count += self.add(value, node.right, node)
      else:
        node.right = RBNode(value)
        return 1 + node.color

    elif value == node.value:
      node.count += 1

    self.blackHeightErrorHanlder(count >= 2, node, parent)

    if node.color == 0 or count >= 2:
      count = 0
    else:
      count += node.color

    return count

  def  blackHeightErrorHanlder(self, hasImbalance, target, parentOfTarget):
    op = 0
    promote = None

    if hasImbalance:

      op = target.rotationCode()

      if op == 1:
        promote = target.left
        target.rightRotate(parentOfTarget,self)

      if op == 2:
        promote = target.left.right
        target.left.leftRotate(target, self)
        target.rightRotate(parentOfTarget, self)

      if op == 3:
        promote = target.right
        target.leftRotate(parentOfTarget, self)

      if op == 4:
        promote = target.right.left
        target.right.rightRotate(target, self)
        target.leftRotate(parentOfTarget, self)

      if op == 5:
        target.color ^= 1
        target.left.color ^= 1
        target.right.color ^= 1

    if promote:
      promote.color = 0
      promote.left.color = promote.right.color = 1

    self.root.color = 0

tree =  RBTree()

tree.add(3)
tree.add(1)
tree.add(5)
tree.add(7)
tree.add(6)
tree.add(8)
tree.add(9)
tree.add(10)
tree.add(12)
tree.add(12333)
tree.add(2)

tree.display()