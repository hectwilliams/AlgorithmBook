import math
import copy
import random

class Arrays():
  def __init__(self):
    self.array = []
    self.check = lambda arr, pos: pos < 0 or pos >= len(self.array) 

  def push_front(self, value):  
    self.array = [value] + self.array
    self.insert_at(0, value)
    return self

  def pop_front(self):
    return self.remove_at(0);
  
  def insert_at(self, pos, val):
    if not self.check(self.array, pos):
      self.array[pos] = val
    return self 

  def remove_at(self, pos):
    value = None
    if self.check(self.array, pos):
      return None
    value = self.array[pos]
    self.array = self.array[0:pos] + self.array[pos + 1: :] 
    return value

  def swap_pairs(self):
    for i in range (0, int(math.floor( len(self.array) / 2))):
      self.array[i], self.array[len(self.array) - 1 -  i] = self.array[len(self.array) - 1 - i], self.array[i]  
  
  def remove_dup_order(self):
    index = 0
    dupping_mode = False
    while index < len(self.array):
      if self.array[index - 1] == self.array[index]:
        self.remove_at(index)
      else:
        index += 1 
  
  def min_to_front(self):
    obj = [None, None]
    for i in range(0, len(self.array)):
      if obj[0] == None or self.array[i] < obj[0]:
        obj[0] = self.array[i]
        obj[1] = i
    if obj[0]:
      self.push_front( self.remove_at(obj[1]))
  
  def reverse(self):
    index = 0
    mid =  int (math.floor( len(self.array)/2))
    size = len(self.array)
    for i in range (0, mid):
      self.array[i],  self.array[ size - i - 1] = self.array[size - i - 1], self.array[i]   
    return self.array

  def rotate(self, shift_by):
    arr = self.array
    left_rot_en = shift_by < 0
    
    if left_rot_en:
      shift_by *= -1

    for i in range(0, shift_by):
      if shift_by <  0:
        for k in range(0,len(arr) - 1):
          arr[k + 1], arr[k] = arr[k] , arr[k + 1] 
      else:
        for k in range( len(self.array) - 2 ,-1, -1 ):
          arr[k + 1], arr[k] = arr[k] , arr[k + 1] 
  
  def filter_range(self, min, max):
    result = []
    arr =  self.array  
    for i, c in enumerate(self.array):
      if  c >min and c < max:
        result.append(c)    
    return result

  def concat(self,a,b):
    result = []
    index_a = 0
    index_b = 0

    while index_a< len(a)  or  index_b < len(b):

      if index_a < len(a):
        result.append(a[index_a])
        index_a+= 1

      elif index_b < len(b):
        result.append(b[index_b])
        index_b += 1
    return result
     
  def remove_negative(self):
    index = 0

    while index < len(self.array):
      if self.array[index] < 0 :
        self.remove_at(index)
      else :
        index += 1

  def second_to_last(self):
    count = 0
    for i in range(len(self.array) - 1, -1, -1):
      count += 1
      if count == 2:
        return self.array[i]
    return None


  def second_largest(self):
    buffer = [None, None]
    for i in range(0, len(self.array)):
      data = self.array[i]
      if i < 2:
        buffer[i] = data
      elif data > buffer[0] or data > buffer[1]:
        if buffer[0] > buffer[1]:
          buffer[0], buffer[1] = buffer[1], buffer[0]
        if data > buffer[0]:
          buffer[1] = buffer[0] 
          buffer[0] = data         
        elif data > buffer[1]:
          buffer[1]  = data 
    return buffer[0]       
      
  def nth_to_last(self, n):
    result  = None 
    for i in range(len(self.array) - 1, len(self.array) - 1 - n, -1):  
      result = self.array[i]
    return result 
  
  def nth_largest(self, n):
    buffer = copy.deepcopy(self.array)
    index = None
    
    if n >= len(buffer):
      return None

    for i in range(0, len(buffer) - 1):
      index = 0
      for k in range(0, len(buffer)):
        if buffer[k] < buffer[index] :
          buffer[k], buffer[index] = buffer[index] , buffer[k] 
          index += 1 
    return buffer[len(buffer) - n]      

  def shuffle(self):
    index = 0
    r = None 
    for i in range(0, len(self.array)):
      r = int(math.floor(random.random() * len(self.array))) 
      self.array[index], self.array[r] = self.array[r], self.array[index]
      index += 1
    return self.array
  
  def remove_range(self, start, end):
    index = 0
    while start or end:
      print([start, end, self.array])
      if start:
        self.array = self.array[0 : index] + self.array[index + 1: :] 
        start -= 1 
        end -= 1
      elif end:
        self.array = self.array[0 : end + 1]
        end = 0
    return self.array
  
  
  def print_me(self):
    print(self.array)


def skyline_heights(arr):
  result = [] 
  for val in arr:
    if val > 0 and ((not result)  ^   (val > arr[-1]) ):
      result.append(val)
  return result 


def is_credit_card_valid( collection):
  last_digit = collection[-1] 
  data = 0
  digit = None 
  for i in range ( len(collection) - 2, -1, -1):
    digit = collection[i] 
    if i % 2 == 1:
      digit  *= 2
    if digit > 9:
      digit -= 9
    data +=  digit
  data += last_digit
  return data % 10 
 
def intermediate_sums( arr):
  count = 0
  curr_sum = 0
  index = 0
  
  while index < len(arr):
    curr_sum += arr[index]
    count += 1
    index += 1
    if count == 10:
      count = 0
      arr = arr[0 : index - 1] + [curr_sum] + arr[index: :]
      curr_sum = arr[index]      
      index += 1
  if count:
    arr = arr + [curr_sum]
  return arr 
     
def double_trouble(arr):
  index = 0

  while index < len(arr):
    arr = arr[0: index + 1 ] +    [arr[index]] + arr[index+ 1: :]
    index += 2 
  return arr 

def zip_it (array_a, array_b):
  ptr_a = 0
  ptr_b = 0
  result = []

  while ptr_a < len(array_a) or  ptr_b < len(array_b):

    if ptr_a == len(array_a):
      result += array_b[ptr_b ::]
      break

    elif ptr_b == len(array_b):
      result += array_a[ptr_a ::] 
      break
    
    elif ptr_a == ptr_b:
      result += [array_a[ptr_a]]
      ptr_a += 1

    elif ptr_a > ptr_b:
      result += [array_b[ptr_b]]
      ptr_b += 1

  return result




