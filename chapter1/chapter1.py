import copy
import math
import random 

def setme():
  myNumber = 42
  myName = 'Hector'
  myNumber, myName = myName, myNumber
  print(myNumber)

def print_neg_52_to_1066():
  start = -52
  stop = 1066
  for count in range(start, stop):
    print( '[' + str(count) + ']')

def be_cheerful():
  for count in range(1, 98 + 1):
    print(str(count) + '\t' + 'good morning')

def mult_of_three():
  for count in range(-300, 1):
    if not (count == -3 or count == -6) and (count % 3 == 0):
      print('[' + str(count) + ']')

def print_with_while():
  start = 2000
  end = 5280
  for count in range(start, end + 1):
    print('[' + str(count) + ']')

def my_birthday(*args):
  if len(args) == 2 and (args == (11, 1) or  args == (1, 11)):
    print('how did you know')
  else:
    print('Just another day...')

def leap_year(year):
  if (year % 4 == 0 and year % 100 == 1) or (year == 400):
    return True
  return False

def print_and_count():
  start = 512
  end = 4096
  for count in range(start, end + 1):
    if count % 5 == 0:
      print(str(count))
def mult_of_six():
  count = 0
  while count < end:
    if count % 6 == 0:
      print(count)
    count = count + 1
def counting_dojo_way ():
  for i in range(1, 101):
    if not i % 5  == 0:
      print('Coding')
    elif not i % 10:
      print('Dojo')

def log_input(data):
  print(data)

def suckers_huge():
  #start = -5
  #end = start * -1
  #sum = 0
  #for i in range(start, end + 1):
  #  print(i)
   # sum = sum + i;
  return 0

def countdown_by_fours():
  start = 2016
  list1 = []
  for val in range(start, 0, -4):
    list1.append(val)
  return list1

def flexible_countdown(lowNum, highNum, mult):
  list1 = []
  for value in range (highNum , lowNum,  -mult):
    list1.append(value)
  return list1

def final_countdown(p1, p2, p3, p4):
  while (p2 < p3):
    if not p2 % p1 and p2 % p1 is not p4 :
      print (p2)
    p2 = p2 + 1

def countdown(number):
  list1 = []
  if number <= 0:
    return list1
  while number:
    list1.append(number)
    number = number - 1
  return list1

def print_return(arr):
  if not isinstance(arr, list):
    return False
  elif not len(arr):
    return False
  print(arr[0])
  return (arr[1])

def first_plus_length(arr):
  sum = 0
  if not isinstance(arr, list):
    return sum
  elif not len(arr):
    return sum
  for i in range (0, len(arr)):
    sum = sum + +(not not arr[i])
  return sum

def value_gt_than_2nd(arr):
  count = 0
  if not isinstance(arr, list):
    return count
  elif len(arr) < 2:
    return count
  for val in arr:
    if val > arr[1]:
      count = count + 1  
  return count

def values_greather_than_second (*list_of_arrays):
  result = []
  if len(list_of_arrays) < 2 :
    return result
  for i, ele in enumerate(list_of_arrays[0]):
    if ele > list_of_arrays[0][1]:
      result.append(ele)
  return result 

def this_len_that_value (num1, num2):
  res = []
  for i in range (0, num1):
    res.append(num2)
  if num1 == num2:
    print('Jinx')
  return res

def fit_value(*collection):
  length = len(collection) 
  if length > 0:
    if collection[0] > length:
      print('Too Big')
    if collection[0] < length:
      print('Too Small')
    if collection[0] == length:
      print('Just Right')

def fahrenheit_to_celcius(f):
  return (f - 32) * (5/9) 

def fahrenheit_to_celcius(c):
  return ((9/5) * c) + 32

def biggie_size(arr):
  for i, ele in enumerate(arr):
    if ele >= 0:
      arr[i] = 'Big'
  return arr; 

def previous_lengths (strings):
  for i in range(len(strings) - 1, 0, -1):
    strings[i] = len(strings[i - 1])
  return strings

def print_low_return_high (arr):
  res = [None, None]
  for val in arr:
    if (val < arr[0]  or arr[0] == None):
      arr[0] = val
    if (val < arr[1] or arr[1] == None):
      arr[1] = val
  print(arr[0])
  return arr[1]

def add_seven_to_most (arr):
  result = []
  if not arr:
    return []
  result.append(arr[0])
  for i  in range(1, len(arr)):
    result.append(arr[i] + 7)
  return result 

def print_one_return_another(arr):
  firstOddValue = None
  buffer = [None, None]
  
  for i in range (0, len(arr) - 1 ):
    buffer = arr[i : i + 2]
    for val in arr:
      if firstOddValue is None:
        if buffer[0] % 2:
          firstOddValue = buffer[0] 
        elif buffer[1] % 2:
          firstOddValue = buffer[1]
  print(buffer[0])
  return firstOddValue

def reverse_array (arr):
  result = []
  for i in range(len(arr) - 1, -1, -1):
    result.append(arr[i]) 
  return result 

def double_vision(arr):
  deepCopyArr = copy.deepcopy(arr)
  for i in range(0, len(deepCopyArr)):
    deepCopyArr[i] = 2 * deepCopyArr[i]
  return deepCopyArr

def outlook_negative(arr):
  result = copy.deepcopy(arr)
  for i, ele in enumerate(arr):
    result[i] = (-1 * ele if (ele > 0) else  ele)
  return result 

def count_positives(arr):
  count = 0
  length = len(arr)
  for i in range (0, len(arr)) :
   count = +( arr[i] > 0) + count;
   if (length - 1 == i) :
     arr[i] = count 
     return arr

def always_hungry(arr):
  count = 0
  for val in arr:
    if val is 'food':
      count = count + 1
      print('yummy')
  if not count:
    print('I\'m Hungry')

def even_and_odds(arr):
  oddCounter = 0
  evenCounter = 0

  for val in arr:
    oddCounter = oddCounter + (val % 2 is 1)
    evenCounter = evenCounter + (val % 2 is 0)
    if oddCounter == 3:
      print('That\'s odd!')
      oddCounter = 0
    if evenCounter == 3:
      print('Even more so!')
      evenCounter = 0
    if oddCounter > 0 and evenCounter > 0 : 
       evenCounter = 0
       oddCounter = 0;   

def swap_towards_center (arr):
  length = len(arr)
  for i in range (0, int(math.floor(length/2))):
    if (i + 1 % 2):
      tmp = arr[i] 
      arr[i] = arr[length - 1 - i ]
      arr[length - 1 - i] = tmp
  return arr 

def incr_seconds(arr):
  for i in range(0, len(arr)):
    arr[i]  = arr[i] + 1 if (arr[i]% 2) else arr[i]
  return arr

def scale_array (arr):
  arr = map(lambda x: x * 2, arr)
  return arr

def only_keep_last_few(arr, x):
  if x >= len(arr):
    return arr
  arr = arr[len(arr) - x: len(arr) ]
  return arr

def math_help(m, b):
  return -b/m

def whatHappensToday ():
  n  = 100 * (random.random()) 
  if n  <= 10 :
    print('volcanos')
  if n >  10 and n <= 25:
    print('tsunamis')
  if n > 25 and n <= 45:
    print('eathquakes')
  if n > 45 and n < 70:
    print('blizzards')
  if n > 70 and n <= 100:
    print('meteors')
    
def what_really_happened_today ():
  index = 0
  disaster_test = {
    "volcanos": False,
    "tsunamis":False,
    "earthquakes": False,
    "blizzards": False,
    "meteors": False
  }
  
  probablities = [10, 15, 20, 25, 30]
  for key, value in disaster_test.items():
    if random.random()* 100  <= probablities[index]:  
      disaster_test[key] = True
    index = index + 1
  print(disaster_test)

def soaring_iq():
  result = 0.01
  while (result <= .98):
    result = result + 0.01
  return result

def letter_grade(grade):
  if grade < 60:
    return ['Score:', (grade), 'Grade', 'F' ]
  if grade >= 60 and grade <= 69:
    return [ 'Score', (grade), 'Grade', 'D']
  if grade >= 70 and grade <= 79:
    return [ 'Score', (grade), 'Grade', 'C']
  if grade >= 80 and grade <= 89:
    return ['Score', (grade), 'Grade', 'B']
  if grade >= 90:
    return [ 'Score', (grade), 'Grade', 'A' ]

def letter_grade_accurate(grade):
  data = letter_grade(grade)
  if data[1] < 95:
    if data[1] % 10 < 3:
      data[3] = '-' + data[3]
    if data[1] % 10 > 7: 
      data[3] = '+' + data[3] 
  return data

print( letter_grade_accurate(78))
