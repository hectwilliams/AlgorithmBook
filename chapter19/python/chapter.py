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

      if (node.balance > 0) or (node.balance == 0 and node.left):
        return 1 + self.height(node.left)

      if (node.balance < 0) or (node.balance == 0 and node.right):
        return 1 + self.height(node.right)

    return 0

  def isBalanced (self):
    return abs(self.balance) <= 1

  def setBalance(self):

    if bool(self.left) and bool(self.right) :
      self.balance = self.left.height() - self.right.height()

    elif bool(self.left) :
      self.balance = (1 + self.left.height())

    elif bool(self.right) :
      self.balance = -(1 + self.right.height())

    elif not bool(self.left) and not bool(self.right) :
      self.balance = 0

  def grandchildPromote(self):
    c, gc, tree  = None

    if self.balance > 0 : # PARENT -> LEFT
      if self.left.balance > 0 :  # PARENT -> LEFT  -> LEFT
        pass
      elif self.left.balance < 0 : # PARENT -> LEFT -> RIGHT
        c = self.left
        gc = c.right
        tree = gc.left

        gc.left = c
        c.right = tree
        self.left = gc

        c.setBalance()
        gc.setBalance()
        self.setBalance()

    elif self.balance < 0 : # PARENT -> RIGHT
      if self.right.balance > 0 : # PARENT -> RIGHT -> LEFT
        c = self.right
        gc = c.left
        tree = gc.right

        gc.right = c
        c.left = tree
        self.right = gc

        c.setBalance()
        gc.setBalance()
        self.setBalance()
      elif self.right.balance < 0 : # PARENT -> RIGHT -> RIGHT
        pass

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

  def __removeHelper(self, parent, node):
    successor = None
    parentOfSuccessor = None

    if node.count > 1:
      node.count -= 1

    elif not bool(node.left) and not bool(node.right):
      successor = None
      if parent == None :
        self.head = successor
      elif parent.left == node:
        parent.left = successor
      elif parent.right == node:
        parent.right = successor
      return bool(parent)

    elif bool(node.left) and not bool(node.right):
      successor = node.left

      if parent == None:
        self.head = successor
      elif parent.left == node:
        parent.left = successor
      elif parent.right == node:
        parent.right = successor
      return bool(parent)

    elif bool(node.right) and not bool(node.left):
      successor = node.right
      if parent == None:
        self.head = successor
      elif parent.left == node:
        parent.left = successor
      elif parent.right == node:
        parent.right = successor
      return bool(parent)

    elif bool(node.right) and bool(node.left) :
      if node.right.left == None:
        # NOTE successor is connected to predecessor

        # find successor
        successor = node.right

        # update successsor's parent's balance
        node.balance += 1

        # promote successor
        if parent == None :
          self.head = successor
        elif parent.left == node:
          parent.left = successor
        elif parent.right == node:
          parent.right = successor

        # copy predecessors
        successor.left = node.left
        successor.balance = node.balance

        if successor.balance == 0:
          return True   # update upstream nodes

      else :

        # NOTE successor is a leaf node

        # find successor
        parentOfSuccessor = node.right
        while parentOfSuccessor.left.left:
          parentOfSuccessor = parentOfSuccessor.left
        successor = parentOfSuccessor.left

        # update successor's parent's balance
        if parentOfSuccessor.left == successor:
          parentOfSuccessor.balance -= 1
        if parentOfSuccessor.right == successor:
          parentOfSuccessor.balance += 1

        #update path balance (from: predecessor(include) -> to: successor's parent(exclude)  )
        if not bool(parentOfSuccessor.right) :
          self.__updateBalancePath(node, parentOfSuccessor)

        #remove successor from success's parent
        parentOfSuccessor.left = parentOfSuccessor.left.left

        # promote successsor
        if parent == None :
          self.head = successor
        elif parent.left == node:
          parent.left = successor
        elif parent.right == node:
          parent.right = successor

        # copy attributes (omit value attribute)
        successor.right = node.right
        successor.left = node.left
        successor.balance = node.balance
        successor.count = node.balance

        # tree balance update ?
        if parentOfSuccessor.balance == 0:
          return True

    return False

  def __updateBalancePath (self, node, stop):
    if node and stop:
      while node != stop:
        if stop.value < node.value:
          node.balance -= 1
          return self.__updateBalancePath(node.left, stop)
        else:
          node.balance += 1
          return self.__updateBalancePath(node.right, stop)

  def remove (self, value, node = None):
    balanceFeedback = None

    if node == None:
      node = self.head

    if node:

      if value == node.value:
        balanceFeedback = self.__removeHelper(None, node)

      elif value < node.value:
        if node.left:
          if (node.left.value == value):
            balanceFeedback =  self.__removeHelper(node, node.left)
          else:
            balanceFeedback =  self.remove(value, node.left)
          if balanceFeedback:
            node.balance -= 1

      elif value > node.value:
        if node.right:
          if node.right.value == value:
            balanceFeedback =  self.__removeHelper(node, node.right )
          else:
            balanceFeedback =  self.remove(value, node.right)
          if balanceFeedback:
            node.balance += 1

    return balanceFeedback

  def height (self):
    self.head.height()

  def isBalanced (self):
    return self.head.isBalanced()

  def leftRotate(self, target, node = None):
    node = None
    parentOfTarget = None
    targetRef = None
    tree = None
    child = None

    if not node:
      node = self.head

    if node:
      if node == target:
        targetRef = node
      elif node.left == target:
        parentOfTarget = node
        targetRef = node.left
      elif node.right == target:
        parentOfTarget = node
        targetRef = node.right
      elif target.value < node.value:
        return self.leftRotate(target, node.left)
      elif target.value > node.value:
        return self.leftRotate(target, node.right)

    if targetRef:
      targetRef.grandchildPromote()

      child = targetRef.right
      tree = child.left

      child.left = targetRef
      targetRef.right = tree

      targetRef.setBalance()
      child.setBalance()

      if parentOfTarget == None:
        self.head = child
      elif parentOfTarget.left == targetRef:
        parentOfTarget.left = child
        parentOfTarget.setBalance()
      elif parentOfTarget.right == targetRef :
        parentOfTarget.right  = child
        parentOfTarget.setBalance()

  def rightRotate(self, target, node = None):
    node = None
    parentOfTarget = None
    targetRef = None
    tree = None
    child = None

    if node == None :
      node = self.head

    if node:
      if node == target:
        targetRef = node
      elif node.left == target:
        parentOfTarget = node
        targetRef = node.left
      elif node.right == target :
        parentOfTarget = node
        targetRef = node.right
      elif target.value < node.value:
        return self.rightRotate(target, node.left)
      elif target.value > node.value:
        return self.rightRotate(target , node.right)

    if targetRef:
      targetRef.grandchildPromote()

      child = targetRef.left
      tree = child.right

      child.right = targetRef
      targetRef.left = tree

      targetRef.setBalance()
      child.setBalance()

      if parentOfTarget == None :
        self.head = child
      elif parentOfTarget.left == targetRef:
        parentOfTarget.left = child
        parentOfTarget.setBalance()
      elif parentOfTarget.right == targetRef:
        parentOfTarget.right = child
        parentOfTarget.setBalance()

  def balancedAdd(self, value, node = None) :
    if node == None:
      node = self.head

    if node == None:
      self.head = AVLNode(value)
    else:

      if value < node.value:
        if node.left:
          if self.balancedAdd(value, node.left) :
            if node.left.balance < -1:
              self.leftRotate(node.left)
              node.setBalance()
            elif node.left.balance > 1:
              self.rightRotate(node.left)
              node.setBalance()
            else:
              node.balance += 1
            return (node.balance != 0)
        else:
          node.left = AVLNode(value)
          node.balance += 1
          return (node.balance != 0)

      if value > node.value:
        if node.right:
          if self.balancedAdd(value, node.right):
            if node.right.balance < -1:
              self.leftRotate(node.right)
              node.setBalance()
            elif node.right.balance > 1:
              self.rightRotate(node.right)
              node.setBalance()
            else:
              node.balance -= 1
            return (node.balance != 0)
        else:
          node.right = AVLNode(value)
          node.balance -= 1
          return (node.balance != 0)

      if value == node.value:
        node.count += 1

      # ROOT NODE CHECK
      if node.balance < -1:
        self.leftRotate(node)
      elif node.balance > 1:
        self.rightRotate(node)

    return 0

  def balancedRemove (self, value, node = None):
    balanceFeedback = None

    if node == None:
      node = self.head

    if node:

      if value == node.value:
        balanceFeedback = self.__removeHelper(None, node)

      elif value < node.value:
        if node.left:
          if (node.left.value == value):
            balanceFeedback =  self.__removeHelper(node, node.left)
          else:
            balanceFeedback =  self.balancedRemove(value, node.left)
          if balanceFeedback:
            if node.left:
              if node.left.balance > 1:
                self.rightRotate(node.left)
                node.setBalance()
              elif node.left.balance < -1:
                self.leftRotate(node.left)
                node.setBalance()
              else:
                node.balance -= 1
            else:
              node.balance -= 1

      elif value > node.value:
        if node.right:
          if node.right.value == value:
            balanceFeedback =  self.__removeHelper(node, node.right )
          else:
            balanceFeedback =  self.balancedRemove(value, node.right)
          if balanceFeedback:
            if node.right:
              if node.right.balance > 1:
                self.rightRotate(node.right)
                node.setBalance()
              elif node.right.balance < -1:
                self.leftRotate(node.right)
                node.setBalance()
              else:
                node.balance += 1
            else:
              node.balance += 1

    if node == self.head:
      if node.balance > 1:
        self.rightRotate(node)
      elif node.balance < -1:
        self.leftRotate(node)

    return balanceFeedback
tree = AVLTree()
tree.add(200)
tree.add(100)
tree.add(25)
tree.add(120)
tree.add(110)
tree.add(140)
tree.add(105)
tree.display()
tree.remove(100)
print()
tree.display()


