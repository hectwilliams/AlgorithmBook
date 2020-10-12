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

  def repair(self, node = None) :
    if node == None:
      node = self.head

    if node:

      if node.balance > 0:
        self.repair(node.left)
        if node.left.balance > 1:
          self.rightRotate(node.left)
          node.setBalance()
        elif node.left.balance < -1:
          self.leftRotate(node.left)
          node.setBalance()
      elif node.balance < 0:
        self.repair(node.right)
        if node.right.balance > 1:
          self.rightRotate(node.right)
          node.setBalance()
        elif node.right.balance < -1:
          self.leftRotate(node.right)
          node.setBalance()
      elif node.balance == 0:
        return

      if node == self.head:
        if node.balance < 1:
          self.rightRotate(node)
        elif node.balance < -1:
          self.leftRotate(node)

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


tree =  RBTree()
tree.add(3)
tree.add(1)
tree.add(5)
tree.add(7)
tree.add(6)
tree.add(8)
tree.add(9)
tree.add(10)

tree.display()