import sys

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

  def contains (self, key, node = None ) :
    node = self.root if not node else node

    if not node:
      return None

    if node.key == key:
      return node.value

    for child in node.children:
      if key.find(child.key) == 0:
        return self.contains(key, child)

    return None
  def size (self, node = None ):
    count = 0
    node = self.root if not node else node

    for child in node.children:
      count += 1 + self.size(child)
    return count

  def first (self):
    node = self.root
    curr = None
    pos = -1
    currChar = minChar = None

    while node != curr:
      curr = node
      pos += 1
      for child in node.children:
        currChar = child.value

        if minChar == None or currChar <= minChar:
          node = child
          minChar = currChar

    return {'key': node.key, 'value': node.value}

  def last(self) :
    node = self.root
    curr = None
    currString = maxString = None
    pos = 0

    while curr != node:
      curr = node
      pos += 1
      for child in node.children:
        currString = child.key
        if maxString == None or currString >= maxString:
          maxString = currString
          node = child
    return {'key' : node.key , 'value': node.value}

trie = TrieMap()
x = trie.add( "start" , "hector")
x = trie.add( "start" , "hector")

print(trie.last())

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