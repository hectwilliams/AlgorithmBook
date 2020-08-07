
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
    self.parent = None 

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
          node.left.parent = node 
        else:
          return self.add(value, node.left)
      else:
        if node.right == None:
          node.right = BTNode(value)
          node.right.parent = node 
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
          tmp.parent = prev 

        elif bool(node.left) ^ bool(node.right):
          if prev == None:
            if node.left:
              self.root = node.left
            else:
              self.root = node.right
            self.root.parent = None 
          elif prev.left == node:
            if node.right:
              prev.left = node.right
            else:
              prev.left = node.left
            prev.left.parent = prev 
          elif prev.right == node:
            if node.right:
              prev.right = node.right
            else:
              prev.right = node.left
            prev.right.parent = prev 
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
        node.left.parent = node 
    elif value > node.value:
      if node.right:
        self.add_no_dupes(value, node.right)
      else:
        node.right = BTNode(value)
        node.right.parent = node 

  def bstReverseOrder(self, node = None):
    if node == None:
      node = self.root
    if node:
      if node.right:
        self.bstReverseOrder(node.right)
      print(node.value)
      if node.left:
        self.bstReverseOrder(node.left)

  def valBefore(self,before, node = None):
    if node == None:
      node = self.root 
    if node:
      if before < node.value and node.left:
        return self.valBefore(before, node.left)
      elif before >= node.value and node.right:
        return self.valBefore(before, node.right)
      elif before == node.value:
        return node.parent.value
      else:
        if node.left:
          return node.value
        return None 

  def valAfter(self, after, node = None):
    if node == None:
      node = self.root 
    
    if node:
      if after < node.value and node.left:
        return self.valAfter(after, node.left)
      elif after >= node.value and node.right:
        return self.valAfter(after, node.right)
      elif after == node.value:
        if node.right:
          return node.right.value 
        else:
          return None 
      else:
        if node.parent:
          return node.parent.value
        else:
          return None 

  def node_after(self, node):
    if node:
      if node.parent:
        if node.parent.value > node.value:
          return node.parent 
      if node.right:
        return node.right 
    return None 
  
  def node_before(self, node):
    if node:
      if node.parent:
        if node.parent.value < node.value:
          return node.parent 
      if node.left:
        return node.left 
    return None 
  
  def closest(self, value, node = None ):
    if node == None:
      node = self.root 
    if node:
      if value < node.value and node.left:
        return self.closest(value, node.left)
      elif value >= node.value and node.right:
        return self.closest(value, node.right) 
      else:
        return node.value
    return None 

  def tree_path_contains_sum(self, target, node = None, acc = 0):
    state = False

    if node == None:
      node = self.root 

    if node:
      
      if node.left:
        state |= self.tree_path_contains_sum(target, node.left, acc + node.value)
      
      if node.right:
        state |= self.tree_path_contains_sum(target, node.right, acc + node.value)
      
      if node.right == None and node.left == None:
        acc += node.value 
        state = acc == target

    return state 
  
  def tree_path_contains_sum_root_to_path_list(self, collection = [], buffer= [], node = None ):
    
    if (node == None):
      node = self.root
    
    if node:
      
      if node.left:
        self.tree_path_contains_sum_root_to_path_list(collection, buffer + [node.value], node.left )

      if node.right:
        self.tree_path_contains_sum_root_to_path_list(collection, buffer + [node.value], node.right)

      if node.right == None and node.left == None:
        buffer += [node.value]
        collection.append(buffer)

    return collection

  def root_leaf_numbers(self, node = None, depth = 0, acc = 0):
    if node == None:
      node = self.root
    if node:
      acc =  10 * acc + node.value
      if node.left:
        self.root_leaf_numbers(node.left, depth + 1,acc)
      if  node.right:
        self.root_leaf_numbers(node.right, depth + 1, acc)
      if node.right == None and node.left == None:
        print(acc)
        
  def left_side_binary(self, maxDepth = [-1], collection = [], node = None, depth = 0):
    if node == None:
      node = self.root
    if node:
      if maxDepth[0] < depth:
        collection.append(node.value)
        maxDepth[0] = maxDepth[0] + 1
      if node.left:
        self.left_side_binary(maxDepth, collection, node.left, depth + 1)
      if node.right:
        self.left_side_binary(maxDepth, collection, node.right, depth +1)

    return collection 
    
def tree_path_contains_sum_test():
  tree = BST()
  tree.add_no_dupes(4)
  tree.add_no_dupes(5)
  tree.add_no_dupes(2)
  tree.add_no_dupes(3)
  tree.add_no_dupes(1)
  tree.add_no_dupes(6)
  tree.add_no_dupes(7)
  print(tree.left_side_binary())

tree_path_contains_sum_test()