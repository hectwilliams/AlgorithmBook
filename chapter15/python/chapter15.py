import sys

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

  def addNode (self,targetNode, node= None) :
    node = self.root if not node else node

    if not node:
      self.root = targetNode
    else:
      if targetNode.value < node.value:
        if node.left:
          self.addNode(targetNode, node.left)
        else:
          node.left = targetNode
      else:
        if node.right:
          self.addNode(targetNode, node.right)
        else:
          node.right = targetNode
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

  def bstRepairReinsert (self, node = None) :
    insertNode = None
    node = self.root if not node else node

    if node:
      if node.left:
        insertNode = node.left
        node.left = None
        self.bstRepairReinsert(insertNode)

      if node.right:
        insertNode = node.right
        node.right = None
        self.bstRepairReinsert(insertNode)
      self.addNode(node, self.root)

  def repair(self, node = None) :
    repaired = False
    subtree = None

    node = self.root if not node else node

    if node:
      if node.left:
        if node.left.value >= node.value:
          repaired = True
          subtree = node.left
          node.left = None
          self.bstRepairReinsert(subtree)
      if node.right:
        if node.right.value < node.value:
          repaired = True
          subtree = node.right
          node.right = None
          self.bstRepairReinsert(subtree)

      if node.left:
        repaired |= self.repair(node.left)
      if node.right:
        repaired |= self.repair(node.right)

    return repaired

  def smallestDifference(self, node = None, minValue = [sys.maxsize] ):
    curr = 0
    node =  self.root if not node else node
    if node:

      if node.left:
        curr = abs(node.left.value  - node.value)
        minValue[0] = minValue[0] if curr > minValue[0] else curr

      if node.right:
        curr = abs(node.right.value - node.value)
        minValue[0] = minValue[0] if curr > minValue[0] else curr

      if node.left:
        self.smallestDifference(node.left, minValue)
      if node.right:
        self.smallestDifference(node.right, minValue)

    return minValue[0]

  def closestValue(self, value, node = None, closest = [None]) :
    diff = None
    node = self.root if not node else node

    if node:
      diff = abs(node.value - value)
      print(diff, node.value, closest)

      if closest[0] == None or ( diff < abs(closest[0] - value) ):
        closest[0] = node.value

      if node.left:
        self.closestValue(value, node.left, closest)

      if node.right:
        self.closestValue(value, node.right, closest)

    return closest[0]

  def partitionAroundValue(self, value, node = None, prev = None) :
    result = None
    node = self.root if not node else node

    if  node:

      if value < node.value:
        if node.left:
          return self.partitionAroundValue(value, node.left, node)
        else:
          result = node

      if value > node.value :
        if node.right:
          return self.partitionAroundValue(value, node.right, node)
        else :
          result = node
    else:

      if prev:
        if prev.left == node:
          result = node
          prev.left = None
        if prev.right == node:
          result = node
      else:
        result = node
        self.root = None

    return result

  def partitionEvenly (self, node = None, partitionA = None, partitionB = None, count = 0):
    node = self.root if not node else node
    if not partitionA:
      partitionA = BST()
      partitionB = BST()
    if node:
      if node.left:
        self.partitionEvenly(node.left, partitionA, partitionB, count + 1)
        node.left = None
      if node.right:
        self.partitionEvenly(node.right , partitionA, partitionB, count + 1)
        node.right = None
      if count % 2 == 0:
        partitionA.addNode(node)
      else:
        partitionB.addNode(node)

    if node == self.root:
      self.root = partitionA.root

    return partitionB

  def reverse (self, node = None):
    left = right = None
    node = self.root if not node else node

    if node:

      left = node.left
      right = node.right

      node.left = right
      node.right = left

      if node.left:
        self.reverse(node.left)
      if node.right:
        self.reverse(node.right)

  def kthBiggest(self, k, node = None, count = [0]):
    result = 0
    node = self.root if not node else node

    if node:
      if node.right:
        result |= self.kthBiggest(k, node.right, count)
      count[0] += 1

      if k == count[0]:
        result |=  node.value

      if node.left:
        result|= self.kthBiggest(k, node.left, count)

    return result

  def valueForLayer(self, layer, node = None):
    res  = []
    queueModel = []
    curr = depth = None

    node = self.root if not node else node
    queueModel.append([node, 0])

    while queueModel:
      curr = queueModel[0][0]
      depth = queueModel[0][1]
      if depth == layer:
        res.append(curr.value)
      if curr.left:
        queueModel.append([curr.left, depth + 1])
      if curr.right:
        queueModel.append([curr.right, depth + 1])
      queueModel.pop(0)
    return res

  def layerArrays(self, node = None):
    result = []
    queueModel = []
    curr = depth = 0

    node = self.root if not node else node

    queueModel.append([node, 0])
    result.append ( [] )

    while queueModel:
      curr = queueModel[0][0]
      depth = queueModel[0][1]

      if depth > result.__len__() :
        result.append([])

      result[depth - 1].append(curr.value)

      if curr.left:
        queueModel.append([curr.left, depth + 1])

      if curr.right:
        queueModel.append([curr.right, depth + 1])

      queueModel.pop(0)

    return result
