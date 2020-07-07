
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
  
in_order_subsets_test()