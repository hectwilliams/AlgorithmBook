import copy

def recursive_sigma(number):
  if number <= 0:
    return 0
  return number + recursive_sigma(number - 1)

def recursive_factorial(number):
  if number <= 1:
    return 1
  return int(number) * recursive_factorial(number - 1)

def flood_fill(canvas2D, xy, newColor):
  row = xy[0]
  col = xy[1]
  prevColorState = None
  newXY = []

  if (row < 0 or row >=5) or (col < 0 or col >=5):
    return None

  prevColorState = canvas2D[row][col]

  # fill xy w/ new color
  canvas2D[row][col] = newColor

  #walk up
  if row > 0:
    newXY = [row - 1, col]
    if prevColorState == canvas2D[ newXY[0] ] [ newXY[1] ]:
      flood_fill(canvas2D, newXY, newColor)

  #walk down
  if row < 4:
    newXY = [row + 1, col]
    if prevColorState == canvas2D[newXY[0]][newXY[1]]:
      flood_fill(canvas2D, newXY, newColor)

  #walk left
  if (col > 0):
    newXY = [row, col - 1]
    if prevColorState == canvas2D[newXY[0]][newXY[1]]:
      flood_fill(canvas2D, newXY, newColor)

 #walk right
  if (col < 4):
    newXY = [row, col + 1]
    if prevColorState == canvas2D[ newXY[0] ] [ newXY[1] ]:
      flood_fill(canvas2D, newXY, newColor)


def flood_fill_test():
  canvas = [
    [3, 2, 3, 4, 3],
    [2, 3, 3, 4, 0],
    [7, 3, 3, 5, 3],
    [6, 5, 3, 4, 1],
    [1, 2, 3, 3, 3]
  ]
  startXY = [2, 2]
  flood_fill(canvas, startXY, 1)
  print(canvas)


def recursive_fibonacci(num):
  if num <=0:
    return 0
  elif num == 1:
    return 1
  else :
    return recursive_fibonacci(num - 2) + recursive_fibonacci(num - 1)

def recursive_fibonacci_test():
  for i in range(0, 5):
    x = recursive_fibonacci(i)
    print(i,"-->", x)

def recursive_tribonacci(num):
  if num <= 1:
    return 0
  elif num == 2:
    return 1
  else:
    return recursive_tribonacci(num  - 3)  + recursive_tribonacci(num - 2) + recursive_tribonacci(num - 1)

def recursive_tribonacci_test():
  for i in range(0, 5):
    x = recursive_tribonacci(i)
    print(i,"-->", x)

def paging_ackerman(a ,b ):
  print(a,b)
  if a == 0:
    return b + 1
  elif b == 0:
    if (a > 0):
      return paging_ackerman(a - 1, paging_ackerman(a, b-1))
    else:
      return b + 1
  else:
    return paging_ackerman(a-1, paging_ackerman(a, b-1))

def paging_ackerman_test():
  paging_ackerman(1,1)

def Zibonacci(num):
  if num <=1:
    return 1
  if num == 2:
    return 2
  if num % 2 == 1:
    n = (num - 1) / 2
    return Zibonacci(n) + Zibonacci(n - 1) + 1
  if num % 2 == 0:
    n = num / 2
    return Zibonacci(n) + Zibonacci(n + 1) + 1

def Zibonacci_test():
  for i in range(0, 10):
    x = Zibonacci(i)
    print(i , "--> ", x)

def bestZibNum (value):
  curr = None
  result = None

  for i in range (value, value/2, -1):
    curr = Zibonacci(i)
    result = i
    if value == curr:
      break
  return result

def recursive_search(collection, target):
  mid = None
  sample = None

  if not collection:
    return False

  mid = int (len(collection) / 2)
  sample = collection[mid]
  print(collection, sample)
  if sample == target:
    return True
  elif target < sample  :
    return recursive_search(collection[0 : mid], target)
  elif  target > sample:
    return recursive_search(collection[mid + 1: :], target)

def recursive_search_test():
  collection = [1,2,3,6]
  answer = recursive_search(collection, 4)
  print(answer) #False
  collection = [4,5,6,8,12]
  answer = recursive_search(collection, 5)
  print(answer) # True

def rGCF(num1, num2):
  if num1 == 0:
    return num2
  return rGCF(num2 % num1, num1)

def rGCF_test():
  a = 10
  b = 15
  print( rGCF(a,b))

def tarai (x, y, z):
  if x <= y:
    return y
  return tarai(tarai(x-1, y, z), tarai(y - 1, z, x), tarai(z-1, x, y))

def tarai_test():
 answer = tarai(10, 2, 9)
 print(answer)

def in_order_subset_remove_string(str, index, remove_count):
  substr = ''
  counter = 0
  size = len(str)

  while (counter != size ):
    if remove_count <= 0:
      substr += str[index]
    if index + 1 >= size:
      index = 0
    else:
      index += 1
    remove_count -= 1
    counter += 1
  return substr

def in_order_subsets (string):
  collection = []
  size = len(string)

  for rcount in range (0, size + 1):
    if (rcount == 0):
      collection.append(string)
    elif (rcount == size):
      collection.append([])
    else:
    #remove rcount chars from string starting at index k
      for k in range(0, size):
        collection.append(in_order_subset_remove_string(string, k, rcount))
  return collection

def in_order_subsets_test():
  answer = in_order_subsets('abcd')
  print(answer)

def recursive_list_length (node):
  if node == None:
    return 0
  return 1 + recursive_list_length(node.next)

def got_any_grapes_helper(collection, n, obj, curr_sum):
  even = 2*n
  odd = 2*n + 1

  if obj['max'] == None or curr_sum >=  obj['max'] :
    obj['max'] = curr_sum

  if even < len(collection):
    got_any_grapes_helper(collection, n + 1, obj, curr_sum + collection[even])

  if odd < len(collection):
    got_any_grapes_helper(collection, n + 1, obj, curr_sum + collection[odd])


def got_any_grapes(collection):
  obj = {'max': None }
  got_any_grapes_helper(collection, 0, obj, 0)
  print(obj)

def got_any_grapes_test():
  collection  = [1,2,3,4]
  answer = got_any_grapes(collection)
  print(answer)

def collatz_apalooza(num):
  if num >= 0:
    if num % 2 == 0:
      return int( num / 2)
    else:
      return  3* num + 1

def collatz_apalooza_test():
  count = 5
  num = 5
  while count:
    num = collatz_apalooza(num)
    count -= 1

telephone_words_mapping = {
  '0': 'O',
  '1': 'I'   ,
  '2': 'ABC' ,
  '3': 'DEF' ,
  '4': 'GHI' ,
  '5': 'JKL' ,
  '6': 'MNO' ,
  '7': 'PQRS',
  '8': 'TUV'  ,
  '9': 'WXYZ' ,
  '-': '-'
}

def telephone_words(memo, phone_number, index = 0, code = ""):
  digit = None

  if index == len(phone_number):
    memo.append(code)
    return

  digit = phone_number[index]

  if digit in telephone_words_mapping:
    for c in list(telephone_words_mapping[digit]):
      telephone_words (memo, phone_number, index + 1, code + c)

def telephone_words_test():
  number = "818-2612"
  collection = []
  telephone_words(collection, number)
  print(len(collection))

def rising_squares(num, string = ""):
  data = str(pow(num, 2))

  if num == 0:
    return string

  if num % 2 == 0:
    string = " " + string + data + " "
  else:
    string = " " + data + string + " "
  return rising_squares(num - 1, string)

def rising_squares_test():
  answer = rising_squares(5)
  print(answer)

def string_expansion(bin_string, str_buffer = "", collection = []):
  c = None

  if len(bin_string) == 0:
    collection.append(str_buffer)
    return

  c = bin_string[0]

  if c == '?':
    for i in range(0, 2):
      string_expansion(bin_string[1: :] , str_buffer + str(i), collection)
  else :
    return string_expansion(bin_string[1: :], str_buffer + c, collection)

  return collection

def string_expansion_test():
  function_data = '1?0?'
  answer = string_expansion(function_data)
  print(answer)

def anagram(string, str_buffer = "", collection = []):

  if len (string) == 0:
    collection.append(str_buffer)

  for i in range(0, len(string)):
    anagram (string[ 1: :], str_buffer + string[i], collection)

def climbing_stairs(collection, step_count, steps = []):
  curr_sum = sum (steps)

  if curr_sum >= step_count:
    if curr_sum == step_count:
      collection.append( copy.deepcopy(steps) )
    return

  for i in range(1, 3):
    steps.append(i)
    climbing_stairs( collection, step_count, steps) # deep copy
    steps.pop()

  return collection

def climbing_stairs_test():
  collection = []
  climbing_stairs(collection,4)
  print(collection)

def perfect_squares (collection, num, start = 1, buffer = [] ):
  if sum(buffer) >= num:
    if sum(buffer) == num:
      collection.append( copy.deepcopy(buffer))
    return

  for i in range(start, num) :
    perfect_squares(collection, num, start + 1, buffer + [i * i] )

def perfect_squares_test():
  collection = []
  perfect_squares(collection, 30)
  print(collection)

def valid_paren(str):
  stack = []
  for c in str:
    if (c == '('):
      stack.append(stack)
    if (c == ')'):
      if len(stack) == 0:
        return False
      stack.pop()
  return len(stack) == 0



def n_valid_pairs(num, collection, buffer = "") :
  pairs = ['(', ')']

  if len(buffer)  >= pow(2,num):
    if valid_paren(buffer) and pow(2,num) == len(buffer):
      collection.append(copy.deepcopy(buffer))
    return

  for i in range(0, 2):
    n_valid_pairs(num, collection, buffer + pairs[i] )

def n_valid_pairs_tesst():
  collection = []
  n_valid_pairs(2, collection)
  print( collection)

class Tower_of_Hanoi:

  def __solve(self, curr_tower_state, tower_states = [], curr_tower = []):
      pass
  def __get_init_pole (self, len):
    poles = []
    for i in range (0, len):
      poles.append([])
      if i == 0:
        for k in range(len,  0 , -1):
          poles[0].append(len + 1 - k)
    return poles

  def __init__(self, len):
    self.__POLE_COUNT = 3
    self.__init_tower_state = self.__get_init_pole(len)
    self.__len = len
    self.iterations = None
    self.__solve(self.__init_tower_state, 0)

  def __move_src_to_dest(self, src_index, dest_index, curr_tower_state):

    src_pole = curr_tower_state[src_index]
    dest_pole = curr_tower_state[dest_index]

    if (src_pole == None or dest_pole == None):
      return 0

    if src_index == dest_index:
      return 0

    # empty source (not permitted )
    if not src_pole:
      return 0

    # (permitted moves)
    if not dest_pole:
      dest_pole.insert(0, src_pole.pop())
      return 1

    if dest_pole[0] > src_pole[0]:
      dest_pole.insert(0, src_pole.pop())
      return 1

    return 0

  def __collection_compare (self, collection_a, collection_b):
    a = None
    b = None

    for row in range(0, self.__len):
      a = collection_a[row]
      b = collection_b[row]

      if len(a) != len(b):
        return 0

      for col in range(0, len(a)):
        if collection_a[row][col] != collection_b[row][col]:
          return 0

    return 1

  def __collection_has_pole (self, tower_collection, curr_tower):

    for tower in tower_collection:
      if self.__collection_compare(tower, curr_tower):
        return 1
    return 0

  def __collection_add_pole(self, tower_collection, curr_tower):
    tower_collection.append(curr_tower)

  def __solve(self, curr_tower_state, iteration,  tower_states = []):
    clone_tower_state = None
    sel = None

    if self.iterations != None:
      del curr_tower_state
      return

    if len(curr_tower_state[self.__POLE_COUNT - 1]) == self.__len and self.iterations == None :
      print(curr_tower_state, iteration)
      self.iterations = iteration
      return

    if self.__collection_has_pole (tower_states, curr_tower_state) :
      return
    else:
      self.__collection_add_pole(tower_states, curr_tower_state)

    for pole_index in range (0, self.__POLE_COUNT ) : # src pole
      for k in range (1, self.__POLE_COUNT ):
        sel = (pole_index + k) % self.__POLE_COUNT  # possible dest pole
        clone_tower_state = copy.deepcopy(curr_tower_state) # clone tower
        if (self.__move_src_to_dest(pole_index, sel, clone_tower_state)): # disk move permitted?
          self.__solve(clone_tower_state, iteration + 1, tower_states)
        else:
          del clone_tower_state

def Tower_of_Hanoi_test():
  iterations = Tower_of_Hanoi(5).iterations
  print(iterations)

Tower_of_Hanoi_test()