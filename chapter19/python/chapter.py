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

  def successor (self):
    runner = self.right
    while runner.left:
      runner = runner.left
    return runner.value

  def copy(self, src):
    if src:
      self.left = src.left
      self.right = src.right
      self.count = src.count
      self.value = src.value


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

  def findParent (self, target, node = None):
    a = b = None

    if not node :
      node = self.root

    if node:

      if node.left:
        a = self.findParent(target, node.left)

      if node.right:
        b = self.findParent(target, node.right)

      if node.right == target:
        return node

      if node.left == target:
        return node

    if a:
      return a

    return b


  def remove (self, value, node = None, parent = None):
    if not node:
      parent = node = self.root

    if node:

      if value == node.value :

        if node.count > 1:
          node.count -= 1
        else:
          self.removeHelper(node, parent)

      elif value < node.value and node.left:
        self.remove(value, node.left, node)

      elif value > node.value and node.right:
        self.remove (value, node.right, node)

  def removeHelper (self, target, parent) :
    isDoubleBlack = None
    successor = None

    if target.left != None and target.right != None :

      successor = target.successor()
      self.remove(successor)
      target.value  = successor

    elif target.left:
      isDoubleBlack = (target.color  or target.left.color)  == 0

      target.copy(target.left)

      if not isDoubleBlack:
        target.color = 0
      else:
        self.removeHelperBalance(target, 1, parent)

    elif target.right:
      isDoubleBlack = (target.color  or target.right.color)  == 0

      target.copy(target.right)

      if not isDoubleBlack:
        target.color = 0
      else:
        self.removeHelperBalance(target, -1, parent)

    elif (not target.left) and (not target.right):

      isDoubleBlack = target.color == 0

      if self.root == target:
        self.root = None

      elif parent.left == target:
        parent.left = None

        if isDoubleBlack:
          self.removeHelperBalance(None, 1, parent)

      elif parent.right == target:
        parent.right = None

        if isDoubleBlack:
          self.removeHelperBalance(None, -1, parent)

  def removeHelperBalance (self, u, dir, p) :

    s = sibColorLeft = sibColorRight = sibColor = None

    if self.root == u:
      if self.root:
        self.root.color = 0
      return

    if dir == -1:
      s = p.left

    if dir == 1:
      s = p.right

    if s:

      sibColor = s.color

      if s.left:
        sibColorLeft = s.left.color
      else:
        sibColorLeft = 0

      if s.right:
        sibColorRight = s.right.color
      else:
        sibColorRight = 0


    if sibColor == 0:

      if sibColorLeft == 0 and sibColorRight == 0: # CASE: SIBLING BLACK WITH BLACK CHILDREN

        # recolor sibling red
        s.color  = 1

        # recolor  parent
        if p.color == 1:

          p.color = 0

        elif p.color == 0:

          u = p

          p = self.findParent(p)

          if p.left == u:
            dir = 1

          if p.right == u:
            dir = -1

          return self.removeHelperBalance(u, dir, p)

      elif sibColorLeft == 1 and sibColorRight == 1:
        if dir == -1:

          # SWAP COLORS OF PARENT AND SIBLING
          s.color, p.color = p.color, s.color

          # SET SIBLING CHILD BLACK
          s.left.color = 0

          # RIGHT ROTATE PARENT
          p.rightRotate(self.findParent(p), self)

        if dir == 1:

          # SWAP COLORS OF PARENT AND SIBLING
          s.color, p.color = p.color, s.color

          #SET SIBLING CHILD BLACK
          s.right.color = 0

          #LEFT ROTATE PARENT
          p.leftRotate(self.findParent(p), self)

      elif sibColorLeft == 1:  # CASE: SIBLING BLACK WITH RED CHILD

        if dir == -1: # left left case

          # SET SIBLING CHILD BLACK
          s.left.color = 0

          # EXCHANGE COLOR BETWEEN PARENT AND SIBLING
          s.color, p.color = p.color, s.color

          # RIGHT ROTATE PARENT
          p.rightRotate(self.findParent(p), self)

        if dir == 1:  # right left case

          # SET SIBLING RED
          s.color = 1

          # SET SIBLING CHILD BLACK
          s.left.color = 0

          # RIGHT ROTATE SIBLING
          s.rightRotate(p, self)

          # case recursion
          self.removeHelperBalance(u, dir, p)

      elif sibColorRight == 1:  # CASE: SIBLING BLACK WITH RED CHILD

        if dir == 1:  # RIGHT RIGHT CASE

          # SET SIBLING BLACK
          s.right.color = 0

          # EXCHANGE COLOR BETWEEN SIBLING AND PARENT
          s.color, p.color = p.color, s.color

          #LEFT ROTATE PARENT
          p.leftRotate( self.findParent(p) , self)

        if dir == -1 :  # LEFT RIGHT CASE

          # SET SIBLING RED
          s.color = 1

          # SET SIBLING CHILD BLACK
          s.right.color = 0

          # LEFT ROTATE SIBLING
          s.leftRotate(p, self)

          #recursion
          self.removeHelperBalance(u, dir, p)

    if sibColor == 1:  # CASE: SIBLING RED

      # EXCHANGE PARENT AND SIBLING COLOR
      s.color, p.color = p.color, s.color

      if dir == 1:

        # LEFT ROTATE PARENT
        p.leftRotate( self.findParent(p), self)

        # RECURSION
        return self.removeHelperBalance(p.left, 1, p)

      if dir == -1:

        # RIGHT ROTATE PARENT
        p.rightRotate(self.findParent(p), self)

        # RECURSION
        return self.removeHelperBalance(p.right, -1, p)


class SplayNode:

  def __init__(self, value):
    self.left = self.right = None
    self.value = value

  def display(self):
    if self.left:
      self.left.display()

    print("tree value" , self.value)

    if self.right:
      self.right.display()

  def successor(self):
    runner  = self.right
    while runner.left:
      runner = runner.left
    return runner.value

  def copy (self, src):
    if src:
      self.right = src.right
      self.left = src.left
      self.value = src.value

  def leftRotate(self, parent, SplayTreeClass):
    c = self.right
    t = c.left

    c.left = self
    self.right = t

    if not parent:
      SplayTreeClass.root = c

    elif parent.left == self:
      parent.left = c

    elif parent.right == self:
      parent.right = c

  def rightRotate (self, parent, SplayTreeClass):
    c = self.left
    t = c.right

    c.right = self
    self.left = t

    if not parent:
      SplayTreeClass.root = c

    elif parent.left == self:
      parent.left = c

    elif parent.right == self:
      parent.right = c

class SplayTree:

  def __init__(self):
    self.root = None

  def display(self):
    if self.root:
      self.root.display()

  def add(self, value):

    newRoot = SplayNode(value)

    if not self.root:
      self.root = newRoot

    elif self.root.value < value :
      newRoot.left = self.root

    else:
      newRoot.right = self.root

    self.root = newRoot

  def __splay(self, value, node , parent ):

    if value == node.value:
      return

    elif value < node.value and node.left:
      self.__splay(value, node.left, node)

      if node.left.value != value:
        node.rightRotate(parent, self)

    elif value > node.value and node.right:
      self.__splay(value, node.right, node)

      if node.right.value != value:
        node.leftRotate(parent, self)

  def __removeTarget(self, target, parent):

    if target.right and target.left:
      successor = target.successor()
      self.remove(successor)
      target.value = successor

    elif target.right:
      target.copy(target.right)

    elif target.left:
      target.copy(target.left)

    elif not target.right and not target.left:

      if not parent:
        self.root = None

      elif parent.left == target :
        parent.left = None

      elif parent.right == target :
        parent.right = None

  def __remove(self, value, node, parent):

    if node:

      if value == node.value:
        self.__removeTarget(  node, parent)

      elif value < node.value and node.left:
        self.__remove(value, node.left, node)

      elif value > node.value and node.right:
        self.__remove(value, node.right, node)

  def remove (self, value, node = None, parent = None):

    self.__splay(value, self.root, None)
    self.__remove(value, self.root, None )



tree = SplayTree()

tree.add(1)
tree.add(2)
tree.add(3)
tree.add(1)
tree.add(6)

tree.remove(1)
tree.display()