
import math
import queue 

class SLNode:
  def __init__(self, value):
    self.val = value
    self.next = None 
    self.child = None 

class SList:
  def __init__(self):
    self.head = None 
  
  @property
  def tail(self):
    runner = self.head
    if (runner == None):
      return runner
    while runner.next:
      runner = runner.next
    return runner

  def pushFront(self, value):
    node = SLNode(value)
    node.next = self.head
    self.head = node
  
  def popFront(self):
    retValue = None 
    if self.head:
      retValue = self.val
    return retValue
  
  def pushBack(self, value):
    node = None
    runner = None  
    if (self.head == None):
      self.pushFront(value)
    else:
      node = SLNode(value)
      runner = self.head 
      while runner.next:
        runner = runner.next 
      runner.next = node 
    
  def contains (self,value):
    runner = this.head 
    while runner:
      if runner.val == value:
        return True
    return False 

  def popBack(self):
    retValue = None 
    runner = self.head
    newTail = None 
    
    if self.head == None :
      return retValue
    
    while runner.next:
      newTail = runner 
      runner = runner.next 
    retValue = runner.val
    
    if runner == self.head:
      self.head = None 
    
    if newTail:
      newTail.next = None 
    
    del runner 
    return retValue

  def removeVal (self, value):
    runner = self.head
    runner_prev = None
    del_node = None   
    rslt = false 
    while (runner):
      if (runner.val == value):
        rslt |= True
        del_node = runner 
        if ( runner == self.head):
          self.head = self.head.next
          runner = self.head
        else:
          runner_prev.next = runner.next
          runner = runner_prev
        del del_node
    runner_prev = runner
    runner = runner.next

  def reverse(self):
    tmp_node  = SLNode(0)
    tmp_node_next = None 
 
    if (self.head == None):
      return None 
    
    while self.head:
      tmp_node.next = self.head 
      self.head = self.head.next
      tmp_node.next.next = tmp_node_next
      tmp_node_next = tmp_node.next
    
    if (tmp_node.next):
      self.head = tmp_node.next
    
    del tmp_node
  
  def isPalindrome(self):
    runner = None 
    start = self.head 
    end = None 

    if start == None:
      return False

    while 1 :
      runner = start 
      while runner.next != end:
        runner = runner.next
      end = runner;  
      if start.val != end.val:
        return False
      if end.next == start or start != end:
        break
      start = start.next
    return True
  
  def kthLastNode(self, k):
    count = 0 
    runner = self.head

    #count 
    while runner:
      runner = runner.next
      count += 1
    
    # count - k
    count -= k 
    if count > 0:
      runner = self.head
      while count > 0:
        runner = runner.next
        count -= 1
    return runner           
  
  def shiftRight(self, n):
    runner = self.head
    newHead = None 
    node = None 
    count = 0

    if n == 0 or runner== None:
      return None 
    
    while runner:
      runnner = runner.next
      count += 1
    
    if n > 0:
      runner = self.head
      for i in range(0, abs(count - n) ):
        runner = runner.next

      #break list 
      newHead = runner.next
      runner.next = None 

      #connect trailing nodes to front 
      runner = newHead
      while runner.next:
        runner = runner.next
      runner.next = self.head
      self.head = newHead

    else:
      return self.shiftLeft(n)
  
  def shiftLeft (self, n):
    runner = self.head
    newHead = None 
    count = 0 

    while runner:
      count += 1
      if count == n:
        #break link 
        newHead = runner.next
        runner.next = None 
        
        #newHead must not be NULL
        if newHead == None:
          break 

        # point runner to tail of new HEAD 
        runner = newHead
        while runner.next:
          runner = runner.next 

        # link new list  with previous  HEAD 
        runner.next = self.head
        
        # update head 
        self.head = newHead  

        break
      runner = runner.next
  
  def sumNumerals (self, lista, listb):
    a = lista.head 
    b = listb.head 
    sum = [0,0, 0] 
    resultList = SList()
    digit = None 
    factor = 1

    # pluck digits into sum array
    while a or b:
      if a:
        sum[0] += a.val * factor
        a = a.next
      if b:
        sum[1] += b.val * factor
        b = b.next
      factor += 10

    #sum accumlators 
    sum[2] = sum[0] + sum[1]
    
    #pluck least sig. digit into list queue  

    while (sum[2] > 0):
      digit = sum[2] % 10
      resultList.pushBack(digit)
      sum[2] = int(sum[2] / 10)
    
    return resultList
  
  def setupLoop (numberOfNodes, loopback_pos):
    myList = SList()
    feedback_node = None 

    for i in range(1, numberOfNodes + 1):
      myList.pushBack(i)
      if loopback_pos == i:
        feedback_node = myList.tail
    
    #feedback
    if feedback_node:
      myList.tail.next = feedback_node

    return myList
  
  def flattenChildren(self):
    runner = None 
    d_queue = queue.Queue()
    children = []
    currTail = None 
    
    if self.head != None :
      d_queue.put(self.head)

    while not d_queue.empty():
      runner = d_queue.get() # pop front of queue 
      while runner:
        if runner.child: # store child node 
          d_queue.put(runner.child)
          static_array_children.append(runner.child)
        runner = runner.next
    
    # append children list to list  (update tail property)
    for child in children:
      self.tail.next = child
      runner = child 
      while runner.next:
        runner = runner.next 
      self.tail = runner 

  def unflattenChildren(self):
    histo = {}
    runner = self.head 
    runner_prev = None 
    tailSet = False 

    while runner:
      if runner.child:
        # hashMap frequency of child node in LL 
        if histo.get(runner.child) == None:
          histo[runner.child] = 0
        histo[runner.child] += 1

        #break if repeat  found 
        if histo[runner.child] == 2:

          if tailSet == False: # set tail  (first unlink) 
            tail = runner_prev
          
          if runner_prev:
            runner_prev.next = None 
          
      runner_prev = runner      
      runner = runner.next

  def hasLoop(self):
    slow = self.head 
    fast = self.head  
    
    while slow:
      if fast:
        fast = fast.next
      if fast:
        fast = fast.next
      slow = slow.next
      if fast == slow:
        return true

  def loopStart(self):
    slow = self.head 
    fast = self.head  
    collision = None 
    loopHead = None 
    runner = None 
    n = 0

    while slow:
      if fast:
        fast = fast.next
      if fast:
        fast = fast.next
      slow = slow.next
      if fast == slow:
        collision = slow 
        break
    
    # n number of nodes in loop
    if collision:
      runner = collision.next 
      while runner != collision:
        n += 1
        runner = runner.next 

      # move loopHead  n-1 nodes from LL Head 
      loopHead = self.head
      for i in range(0, n-1):
        loopHead = loopHead.next 

      #break loop at feeback linking loopHead 
      runner = loopHead
      while runner.next != loopHead:
        runner = runner.next
    
    return runner 
  
  def breakLoop (self):
    feedback = self.loopStart()
    if feedback:
      feedback.next = None 
  
  def numberOfNodes(self):
    feedback = self.loopStart()
    runner = self.head 
    count = 0 

    if runner == None :
      return count
    while runner.next != feedback:
      runner = runner.next 
      count += 1
    return count 
  
  def swapPairs(self):
    runner = self.head 
    runner_prev = None

    while runner:

      if runner_prev:
        
        if self.head == runner_prev:
          self.head = runner
        
        if self.tail == runner:
          self.tail = runner_prev
        
        runner_prev.next = runner.next
        runner.next = runner_prev

        runner = runner_prev
        runner_prev = None 
      
      else:
        runner_prev = runner 
        runner = runner.next


  def display(self):
    runner = self.head 
    while runner:
      print(runner.val, end='')
      runner = runner.next 
    print()



class DLNode:
  def __init__(self, value):
    self.val = value
    self.prev = None 
    self.next = None 

class DList:
  def __init__(self):
    self.head = None
    self.tail = None 

  def push(self, value):
    node = DLNode(value)
    if self.head == None:
      self.head = self.tail = node 
    else:
      self.head.prev = node 
      node.next = self.head 
      self.head = node 

  def pop (self):
    data = None 
    if self.head:
      data = self.head.val
      self.head = self.head.next 
      if self.head:
        del self.head.prev
        self.head.prev = None 
    return data 

  def front (self):
    if (self.head == None):
      return None
    else:
      return self.head.val

  def back (self):
    if (self.tail == None):
      return None 
    else:
      return self.tail.val

  def contains(self, value):
    runner_front = self.head
    runner_back = self.tail
    hasValue = false 
    
    while runner_front or runner_back:
      hasValue |= runner_front.val == value or runner_back.val == value

      if runner_back:
        runner_back = runner_back.prev
      
      if runner_front:
        runner_front = runner_front.next
    
    return hasValue 

  def size(self, value):
    runner_front = self.head
    runner_back = self.tail
    count = 0
    
    while (runner_back or runner_front):
      if runner_back == runner_front: 
        count += 1
      else:
        count += 2
      
      if runner_back:
        runner_back = runner_back.prev
      
      if runner_front:
        runner_front = runner_front.next
    return count 
  
  def prependValue(self, newValue, existingValue):
    runner = self.head
    node = None
    newNode = None  
    while runner:
      if runner.val == existingValue:
        if self.head == runner:
          self.push(newValue)
        else:
          newNode = DLNode(newValue)
          runner.prev.next = newNode
          newNode.prev = runner.prev
          newNode.next = runner
          runner.prev = newNode
      runner = runner.next
  
  def appendValue(self, newValue, existingValue):
    runner = self.head 
    node = None 
    newNode = None 
    while runner:
      if runner.val == existingValue:
        newNode = DLNode(newValue)
        newNode.next = runner.next
        if runner.next:
          runner.next.prev = newNode
        newNode.prev = runner
        runner.next = newNode
      runner = runner.next 
  
  def kthLastNode (self, k):
    runner = self.tail
    data = None 
    
    for i in range(0, k):
      if runner:
        runner = runner.prev
      else:
        return None 
    if runner:
      data = runner.val
    return data
  
  def deleteMiddleNode (self, node):
    node.prev.next = node.next 
    node.next.prev = node.prev 
    del node 

  def isValid(self) :
    slow = None 
    fast = None 

    if self.head:
      slow = self.head
      fast = slow.next 
    else:
      return false

    while fast:

      if fast.prev != slow:
        return False 
      
      if slow:
        slow = slow.next 
      
      if fast:
        fast = fast.next 
    
    return True 

  def partition(self, val):
    node = None 
    runner = self.head 
    
    while runner:
      if (runner.val < val):
        node = runner
        if runner.prev:
          runner.prev.next = runner.next 
        if runner.next:
          runner.next.prev = runner.prev 
        #move node to front 
        node.next = self.head 
        self.head.prev = node 
        self.head = node 
      runner =  runner.next
    
  def isPalindrome(self):
    end = self.tail
    front = self.head 

    while end or front:
      if (end.val != front.val):
        return False 
      if end:
        end = end.prev
      if front:
        front = front.next

      if (end== front or end.next == front):
        break
    return True
  
  def reverse (self):
    back = self.tail
    runner = None 
    if self.tail:
      back = self.tail.prev 
      self.tail.prev = NULL
      self.head = self.tail 
      self.tail = self.head
      runner = self.head 
    while back:
      self.tail = back
      runner.next = back 
      back = back.next 
      runner = runner.next 
      runner.next = None 

  def loopStart(self):
    back = None  
    front = None 

    if self.head == None:
      return None 
      
    back = self.head
    front = self.head.next

    while front:
      
      if front.prev != back:
        break

      if back:
        back = back.next

      if front:
        front = front.next 
    return back

  def breakLoop (self):
    feedback = self.loopStart()
    if feedback:
      feedback.next = None 
  
  def repair(self):
    while not self.isValid:
      self.breakLoop()

  def display(self):
    runner = self.head 
    while  runner:
      print ("[" , runner.val,"]", end='')
      runner = runner.next

dlist = DList()
dlist.push(22)
dlist.push(23)
dlist.appendValue(51, 22)
dlist.display()
