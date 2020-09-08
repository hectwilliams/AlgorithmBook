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

class TrieNode:
  def __init__(self, value):
    self.string = value.lower()
    self.children = []
    self.count = 0

class Trie:
  def __init__(self):
    self.root = TrieNode("")
  def add(self, strData):
    pos = inserted = 0
    curr = None
    node = self.root

    while node.string.__len__() != strData.__len__():
      curr = node
      pos += 1
      for child in node.children:
        if child.string == strData[0 : pos] :
          inserted |= 1
          node = child
      if curr == node:
        node.children.append( TrieNode(strData[0 :pos]) )
        node = node.children[node.children.__len__() - 1]
    return inserted == 0

  def contains (self, strData):
    node = self.root
    curr = None
    pos = 0

    while curr != node :
      curr = node
      for child in node.children:
        if child.string == strData[0 : pos + 1]:
          pos += 1
          node  = child

    return pos == strData.__len__()

  def first (self, node= None):
    curr = None
    minChar = currChar = None
    pos = 0
    node = self.root if not node else node

    while node != curr:
      curr = node
      for child in node.children:
        currChar =  child.string[pos]
        if minChar == None or currChar <= minChar:
          node = child
          minChar = node.string
      pos += 1
    return node.string

  def last (self, node = None ):
    curr = None
    maxString  = currString = None
    pos = 0

    node = self.root if not node  else node

    while node !=  curr:
      curr = node
      pos += 1
      for child in node.children:
        currString = child.string
        if maxString == None or currString >= maxString:
          node = child
          maxString = node.string
    return node.string

  def remove (self, word = "", node = None ):
    found = False
    node = self.root if not node else node

    if node == None :
      return False

    if word  == node.string:
      return True

    for i in range(0, node.children.__len__()):
      if word.find(node.children[i].string ) == 0:
        found = self.remove(word, node.children[i])
        if found:
          if node.children[i].string == word:
            node.children.pop(i)
          elif node.children.__len__() == 1 :
            if node.children[0].children.__len__() == 0:
              node.children = []
          break
    return found

  def size (self, node = None):
    node = self.root if not node else node
    count = 0

    if node.children.__len__() == 0:
      return  0

    for i in range(0, node.children.__len__()):
      count += +(node.string.__len__() > 0)  + self.size(node.children[i])

    return count

  def next (self,string, node = None) :
    result = None
    node = self.root if not node else node

    if node:
      for i in range(0, node.children.__len__()):
        if string.find(node.children[i].string) == 0:
          return self.next(string, node.children[i])
      for i in range(0, node.children.__len__()) :
        if result == None or node.children[i].string < result :
          result = node.children[i].string
    return result


    # pos = inserted = 0
    # curr = None
    # node = self.root



class TrieMulti(Trie):
  def add(self, data, node = None ):
    node = self.root if not node else node
    pos = 0

    if node:
      while node.string.__len__() != data.__len__():
        curr = node
        pos += 1
        for child in node.children:
          if child.string == data[0 : pos] :
            node = child
            node.count += 1
            print(node.string, node.count)
        if curr == node:
          node.children.append( TrieNode(data[0 :pos]) )
          node = node.children[node.children.__len__() - 1]
          node.count += 1
    return True

  def remove(self, targetString, node = None):
    node = self.root if not node else node
    stringFound  = False

    if not node:
      return False

    if node.string == targetString:
      return True

    for i in range(0, node.children.__len__()):

      if targetString.find(node.children[i].string) == 0 :
        stringFound = self.remove(targetString, node.children[i])
        print(stringFound, node.string)
        if stringFound:
          if node.count > 1:
            node.count -= 1
          elif node.count == 1:
            if targetString.find(node.children[i].string) == 0:
              node.children.pop(i)
            elif node.children[0].children.__len__() == 0 :
              node.children.pop(0)
              node.children = []

    return stringFound

  def size (self, node = None):
    count = 0
    node = self.root if not node else node

    if not node:
      return 0

    if node:
      count += node.count

    for i in range(0, node.children.__len__()):
      count += self.size(node.children[i])

    return count

  def contains(self,string, node = None):
    node = self.root if not node else node
    if node:
      if string == node.string:
        return node.count
      for i in range(0, node.children.__len__()) :
        if string.find(node.children[i].string ) == 0:
          return self.contains(string, node.children[i])
    return 0

class TrieMapNode:
  def __init__(self, key, value):
    self.key = key
    self.value = value
    self.children = []

class TrieMap:
  def __init__(self):
    self.root = TrieMapNode("","")

  def add(self, key, value):
    curr = None
    node = self.root
    pos = 0
    result = None

    while pos < key.__len__() :
      curr = node
      pos += 1

      for i in range(0, node.children.__len__() ):
        if key.find(node.children[i].key[0 : pos]  ) == 0:
          node = node.children[i]
          break

      if node.key == key:
        result = node.value
        node.value = value
        return result

      if curr == node :
        node.children.append( TrieMapNode( key[0 : pos] , "")  )
        node = node.children[-1]

        if node.key == key:
          node.value = value
    return result

  def remove(self, key, node = None):
    found = False

    node = self.root if not node else node

    if not node:
      return found

    if node.key == key:
      return True

    for i in range(0, node.children.__len__()):
      if key.find(node.children[i].key ) == 0:
        found |= self.remove(key, node.children[i] )
        if found :
          if node.children[i].key == key:
            node.children.pop(i)
          elif node.children.__len__() == 1:
            if node.children[0].children.__len__() == 0 and node.children[0].value.__len__() == 0:
              node.children = []

    return bool(found)

trie = TrieMap()
x = trie.add( "start" , "hector")
print(x)
x = trie.add( "start" , "hector")
print(x)

print(trie.remove("start"))
print(trie.remove("start"))

# tree = BST()
# tree.add(32)
# tree.add(17)
# tree.add(28)
# tree.add(23)
# tree.add(29)
# tree.add(49)
# tree.add(2)

# tree.display()
# tree.root.left.right.value = 1
# tree.repair()
# tree.display()
# print()
# # print(tree.closestValue(31))
# print(tree.layerArrays())