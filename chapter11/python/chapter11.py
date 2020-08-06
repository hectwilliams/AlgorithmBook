
class BST_LLNode:
  def __init__(self, value):
    self.data = value
    self.next = None

def bst_to_list_insert(node, data):
  if node.data == None:
    node.data = data
  else:
    while node.next:
      node = node.next
    node.next = BST_LLNode(data)

class BTNode:
  def __init__(self, value):
    self.value  = value
    self.left = None
    self.right = None

class BST:
  def __init__(self):
    self.root = None

  def add(self, value, node = None):
    if node == None:
      node = self.root

    if self.root == None:
      self.root = BTNode(value)
    else:
      if value < node.value:
        if node.left == None:
          node.left = BTNode(value)
        else:
          return self.add(value, node.left)
      else:
        if node.right == None:
          node.right = BTNode(value)
        else:
          return self.add(value, node.right)

  def display(self, node = None):
    if node == None:
      node = self.root

    if node.left:
      self.display(node.left)

    print(node.value)

    if node.right:
      self.display(node.right)

  def contains(self, value, node = None):
    result = False

    if node == None:
      node = self.root

    if node:
      result = (node.value == value)

      if  node.left:
        result |= self.contains(value, node.left)

      if node.right:
        result |= self.contains(value, node.right)

    return result

  def minimum (self, node = None) :

    if node == None:
      node = self.root

    if node:
      if node.left:
        return self.minimum(node.left)
      else:
        return node.value

    return None

  def maximum (self, node = None) :

    if node == None:
      node = self.root

    if node:
      if node.right:
        return self.minimum(node.right)
      else:
        return node.value

    return None

  def size(self, node = None):
    sum = 0
    if node == None:
      node = self.root
    if node:
      sum += 1
      if node.left:
        sum += self.size(node.left)
      if node.right:
        sum += self.size(node.right)
    return sum

  def empty(self):
    return self.root == None

  def height(self, node = None) :
    left = 0
    right = 0

    if node == None:
      node = self.root

    if node:
      if node.left:
        left += 1 + self.height(node.left)
      if node.right:
        right += 1 + self.height(node.right)

    if left == right:
      return left

    if left > right:
      return left
    else:
      return right

  def bst_is_balanced(self, node = None, prev = None ):
    left = 0
    right = 0

    if (prev == None and node == None):
      node = self.root

    if node == None:
      return 1

    if node:
      left  = self.height(node.left)
      right = self.height(node.right)
      return abs(left - right) <= 1 and self.bst_is_balanced(node.left, node) and self.bst_is_balanced(node.right, node)

  @staticmethod
  def array_to_bst( collection):
    tree = BST()
    lpos = int( len(collection) / 2)
    rpos = lpos + 1

    while 1:
      if lpos >= 0:
        tree.add(collection[lpos])
        lpos -= 1
      if rpos < len(collection):
        tree.add(collection[rpos])
        rpos += 1
      if lpos < 0 and rpos >= len(collection):
        break
    return tree

  def common_ancestor(self, a,b, node = None):
    if node == None:
      node = self.root

    if a < node.value and b < node.value and node.left:
      if node.left.value != a and node.right.value != b:
        return self.common_ancestor(a,b, node.left)

    if a > node.value and b > node.value  and node.right:
      if node.left.value != a and node.right.value != b:
        return self.common_ancestor(a,b, node.right)

    return node.value

  def preOrder(self, node = None):

    if node == None:
      node = self.root


    if node:
      print( "[" + str(node.value) + "]" ,   end ='')
      if node.left:
        self.preOrder(node.left)
      if node.right:
        self.preOrder(node.right)


  def postOrder(self, node = None):

    if node == None:
      node = self.root

    if node:
      if node.left:
        self.preOrder(node.left)
      if node.right:
        self.preOrder(node.right)
      print( "[" + str(node.value) + "]" ,   end ='')

  def inOrder(self, node = None):

    if node == None:
      node = self.root

    if node:
      if node.left:
        self.preOrder(node.left)

      print( "[" + str(node.value) + "]" ,   end ='')

      if node.right:
        self.preOrder(node.right)

  def bst_to_array(self, node = None, mode = 0):
    collection = []

    if node == None:
      node = self.root

    if node:

      if mode == 0:
        collection.append(node.value)

      if node.left:
        collection += self.bst_to_array(node.left, mode)

      if node.right:
        collection += self.bst_to_array(node.right, mode)

    return collection

  def bst_to_array_pre(self, node = None, mode = 1):
    return self.bst_to_array(None, mode)

  def bst_to_array_post(self, node = None, mode = 2):
    return self.bst_to_array(None, mode)


  def bst_to_list(self, node = None, mode = 0, llist = None):

    if node == None:
      node = self.root

    if llist == None:
      llist = BST_LLNode(None)

    if node:

      if mode == 1:
        bst_to_list_insert(llist, node.value)

      if node.left:
        self.bst_to_list(node.left, mode, llist)

      if mode == 0:
        bst_to_list_insert(llist, node.value)

      if node.right:
        self.bst_to_list(node.right, mode, llist)

      if mode == 2:
        bst_to_list_insert(llist, node.value)

    return llist

  def bst_to_list_pre(self, llist = None):
    return self.bst_to_list(None, 1, llist)

  def bst_to_list_post(self, llist = None):
    return self.bst_to_list(None, 2, llist)


  def min_height(self):
    obj = {'height': 0}

    def min_height_helper(obj , node = None, depth = 0):
      if node:
        if node.left:
          min_height_helper(obj, node.left, depth + 1)

        if  node.right:
          min_height_helper(obj, node.right, depth + 1)

        if node.right == None and node.left == None:
          if obj['min'] == 0 or depth < obj['min']:
            obj['min'] = depth

    min_height_helper(obj, self.root)
    return obj

  def preOrder_no_recursion_traverse(self):
    nodeList = []
    node = self.root

    while node:
      print(node.value)
      if node.right:
        nodeList.append(node.right)
      if node.left:
        node = node.left
      elif nodeList:
        node = nodeList.pop()
      else:
        break
    return

  @staticmethod
  def successor_promote (node):
    prev = None

    if node:
      if node.right:
        prev = node
        node = node.right
        while node.left:
          prev = node
          node  = node.left
      if prev:
        if prev.left == node:
          prev.left = node.right
        else:
          prev.right = node.left
    return node

  def remove(self, value, node = None, prev = None ):
    if node == None:
      node = self.root

    if node:
      if node.value == value:

        if bool(node.left) and bool(node.right):
          tmp = self.successor_promote(node)
          tmp.left = node.left
          tmp.right = node.right

          if prev == None:
            self.root = tmp
          elif prev.left == node:
            prev.left = tmp
          elif prev.right == node :
            prev.right = tmp

        elif bool(node.left) ^ bool(node.right):
          if prev == None:
            if node.left:
              self.root = node.left
            else:
              self.root = node.right

          elif prev.left == node:
            if node.right:
              prev.left = node.right
            else:
              prev.left = node.left

          elif prev.right == node:
            if node.right:
              prev.right = node.right
            else:
              prev.right = node.left

        elif bool(node.left) == 0  and  bool(node.right) == 0:
          if prev == None:
            self.root = None
          elif prev.left == node:
            prev.left = None
          elif prev.right == node:
            prev.right = None

    if node.left:
      self.remove(value, node.left, node)

    if node.right:
      self.remove(value, node.right, node)

  def remove_all(self, node = None, prev = None):
    if node == None:
      node = self.root

    if node:

      if node.left :
        self.remove_all (node.left, node)

      if node.right :
        self.remove_all (node.right, node)

      if prev:
        if prev.left == node:
          prev.left =  None
        if prev.right == node:
          prev.right = None
        del node
      else:
        self.root = None

  def isValid(self, node = None):
    result = True
    branch_list = ['left', 'right']
    next = None

    if node == None:
      node = self.root
    for dir in branch_list:
      next = node.__dict__[dir]
      if next:
        if dir == 'left':
          if next.value < node.value  and next != node:
            result &= self.isValid(next)
        if dir == 'right':
          if next.value >= node.value and node != next :
            result &= self.isValid(next)
    return result

  def add_no_dupes(self,value, node = None):
    if node == None:
      node = self.root

    if self.root == None:
      self.root = BTNode(value)

    elif value < node.value:
      if node.left:
        self.add_no_dupes(value, node.left)
      else:
        node.left = BTNode(value)

    elif value > node.value:
      if node.right:
        self.add_no_dupes(value, node.right)
      else:
        node.right = BTNode(value)

  def bstReverseOrder(self, node = None):
    if node == None:
      node = self.root

    if node:

      if node.right:
        self.bstReverseOrder(node.right)

      print(node.value)

      if node.left:
        self.bstReverseOrder(node.left)

# TESTS

def bst_min_test():
  """
  create tree
     5
    / \
  1    100
  """
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(1)
  print(tree.minimum())


def bst_max_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(1)
  print(tree.maximum())

def bst_size_test():

  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(1)
  print(tree.size())

def bst_empty_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(1)
  print(tree.empty())

  empty_tree = BST()
  print(empty_tree.empty())

def bst_height_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(1)
  tree.add(0)

  print("height", tree.height())

def bst_is_balanced_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(1)

  print("is balanced", tree.bst_is_balanced())

def array_to_bst_test():
  tree = BST.array_to_bst([1,2,3,4,5])
  tree.display()

def common_ancestor_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(2)
  tree.add(1)
  tree.add(0)
  sol = tree.common_ancestor(1,0)
  print("common ancestor " + str(sol))

def preOrder_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(2)
  tree.add(1)
  tree.add(0)
  tree.preOrder()
  print()

def bst_to_array_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(2)
  tree.add(1)
  tree.add(0)
  collection  = tree.bst_to_array()
  print(collection)

def bst_to_list_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(2)
  tree.add(1)
  tree.add(0)

  llist =  tree.bst_to_list_pre()
  runner = llist
  while runner:
    print(runner.data)
    runner = runner.next

def min_height_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(2)
  tree.add(1)
  tree.add(0)
  print( "min height" , tree.min_height())

def preOrder_no_recursion_traverse_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(2)
  tree.add(1)
  tree.add(0)
  tree.preOrder_no_recursion_traverse()

def remove_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(2)
  tree.add(1)
  tree.add(0)
  tree.remove_all()
  tree.inOrder() #nothing

def isValid_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(1)
  tree.isValid()

def no_dupes_test():
  tree = BST()
  tree.add_no_dupes(5)
  tree.add_no_dupes(100)
  tree.add_no_dupes(1)
  tree.add_no_dupes(1)
  tree.inOrder()



def bstReverseOrder_test():
  tree = BST()
  tree.add(5)
  tree.add(100)
  tree.add(2)
  tree.add(1)
  tree.add(0)
  tree.bstReverseOrder() #nothing

bstReverseOrder_test()