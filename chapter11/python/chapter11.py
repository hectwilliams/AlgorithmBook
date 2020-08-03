
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


bst_empty_test()