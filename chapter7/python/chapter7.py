import math
def average(numbers):
  avg = 0
  if len(numbers):
    return None
  for element in numbers:
    avg += element
  return avg / numbers.size() 
   
def balance_point(collection):
  left = 0
  right = 0
  
  for i in range(0, len(collection) - 1 ):
    left = 0
    right = 0

    for l in range(0, i+1):
      left += collection[l]
    
    for r in range(i + 1, len(collection)):
      right += collection[r]
    
    print(left, "\t", right)
    
    if left == right:
      return True
  
  return False 

def balance_index(collection):
  left = 0
  right = 0
  
  for i in range(0, len(collection) - 1 ):
    left = 0
    right = 0

    for l in range(0, i+1):
      left += collection[l]
    for r in range(i, len(collection)):
      right += collection[r]
    if left == right:
      return i

class taco_truck_plane:
  def __init__(self):
    self.xmin = None
    self.xmax = None 
    self.ymin = None 
    self.ymax = None 

def taco_truck(coordinate_array):
  limits =  taco_truck_plane()
  manhattan_distance = None 
  min_manhattan_distance = None

  for array_element in coordinate_array:
    
    if limits.xmin == None:
      limits.xmin = array_element[0]
      limits.xmax = array_element[0]
      limits.ymin = array_element[1]
      limits.ymax = array_element[1]

    if array_element[0] < limits.xmin:
      limits.xmin = array_element[0]
    
    if array_element[0] > limits.xmax:
      limits.xmax = array_element[0]

    if array_element[1] < limits.ymin:
      limits.ymin = array_element[1]

    if array_element[1] > limits.ymax:
      limits.ymax = array_element[1]

  for x in range(limits.xmin, limits.xmax + 1):
    for y in range(limits.ymin, limits.ymax + 1):
      manhattan_distance = 0

      for element in coordinate_array:
        manhattan_distance += abs(x - element[0]) + abs(y - element[1]) 
      
      if min_manhattan_distance == None or manhattan_distance < min_manhattan_distance:
        min_manhattan_distance = manhattan_distance
        
  return min_manhattan_distance

def binary_search(sorted_array, target):
  mid = math.floor(len(sorted_array)/2)
  
  if not sorted_array:
    return False  
  
  if sorted_array[mid] == target :
    return True 
  elif target < sorted_array[mid]:
    return binary_search( sorted_array[0:mid] ,target)   
  else:
    return binary_search( sorted_array[mid+1 : : ] ,target)   

def min_sorted_rotated(string_list):
  mid = math.floor(len(string_list)/2)
  
  if (len(string_list) == 0):
    return None 

  if (len(string_list) == 1):
    return string_list[0]

  if len(string_list) == 2:
    return string_list[ +(string_list[0] > string_list[1]) ]
  
  if len(string_list) >= 3:
    if string_list[mid] < string_list[mid - 1] and string_list[mid] < string_list[mid + 1]:
      return string_list[mid]  
    elif string_list[mid - 1] < string_list[mid + 1]:
      return min_sorted_rotated(string_list[0 : mid])
    else :
      return min_sorted_rotated(string_list[mid + 1 : :])  

def binary_search_string(string_data, target_char):
    mid = math.floor(len(string_data)/2)
    if  len(string_data) == 0:
      return False 
    if string_data[mid] == target_char:
      return True 
    elif ord(target_char) < ord(string_data[mid]):
      return binary_search_string(string_data[0 : mid], target_char)
    else:
      return binary_search_string(string_data[mid + 1: : ], target_char)
    return False 

def flatten (collection, top = None):
  length = len(collection)
  element = None 

  if (length == 0):
    return None 

  for i in range (0, length): 
    element = collection[i]
    if isinstance(element, list) == True :
       flatten(element, collection)
    elif (top):
      if top == None:
        collection.append(element)
      else:
        top.append(element)
  return collection

def remove_dup (collection):
  histo = {}
  index = 0
  element = None 

  while index < len(collection):
    element = collection[index]
    if element not in histo:
      histo[element] = 0
    histo[element] += 1
    if histo[element] > 1:
      collection = collection[0 : index] + collection[index +1: :]
    else:
      index += 1
  return collection

def mode (collection):
  histo = {}
  most_frequent = {'value': None, 'count': None}

  for element in collection:
    if element not in histo:
      histo[element] = 0
    histo[element] +=1 
    if most_frequent['value'] == None or most_frequent['count'] <= histo[element] :
      most_frequent['value'] = element 
      most_frequent['count'] = histo[element]
  return most_frequent

def buffer_copy (source_arr, dest_arr, source_start_index, dest_start_index, n):
  for i in range(0, n):
    if (source_start_index >= len(source_arr)): # wrap around
      source_start_index = 0
    if (dest_start_index >= len(dest_arr)): # wrap around
      dest_start_index = 0
    dest_arr[dest_start_index] = source_arr[source_start_index]
    dest_start_index += 1
    source_start_index += 1

def iSigma(num):
  sum = 0
  for i in range(1, num + 1):
    sum += i
  return sum 

def Factorial(num):
  result = 1
  for i in range(1, num + 1):
    result *= i
  return result  

def iFib(num):
  regs = [0,1]
  for i in range (0, num):
    tmp = regs[0] + regs[1] + regs[2]
    regs[0] = regs[1] 
    regs[1] = tmp
  return regs[0]

def iTrib(num):
  regs = [0,0,1]
  for i in range (0, num):
    tmp = regs[0] + regs[1] + regs[2]
    regs[0] = regs[1] 
    regs[1] = regs[2] 
    regs[2] = tmp 
  return regs[0]

def median_sorted_arrays(a, b):
  length = (len(a) + len(b))
  mid = math.floor( length / 2 )
  buffer_array = []
  idx_a = 0
  idx_b = 0

  while (idx_a + idx_b   < mid  +(length % 2)):

    if idx_a >= len(a):
      buffer_array.append( b[idx_b] )
      idx_b = idx_b + 1

    elif idx_b >= len(b):
      buffer_array.append( a[idx_a] )
      idx_a = idx_a + 1

    elif a[idx_a] <= b[idx_b]:
      buffer_array.append( a[idx_a] )
      idx_a = idx_a + 1
    
    elif b[idx_b] <= a[idx_a]:
      buffer_array.append( b[idx_b] )
      idx_b = idx_b + 1
  
  return buffer_array[len(buffer_array) - 1] if length % 2 == 0 else ( buffer_array[len(buffer_array) - 1] +  buffer_array[len(buffer_array) - 2])/ 2  

def time_to_english (minutes):

  min_z = minutes % 60
  hour_z = math.floor(minutes / 60) % 24
  hour_z_next = (hour_z  + 1) % 24
  result = ''

  curr = {
    'hour': hour_z,
    'meridiem' : 'am' if hour_z < 12 else 'pm',
    'msg': 'midnight' if hour_z == 0 else 'noon' if  hour_z == 12  else  str(hour_z)
  }
  
  next = {
    'hour': hour_z_next,
    'meridiem' : 'am' if hour_z_next < 12 else 'pm',
    'msg': 'midnight' if hour_z_next == 0 else 'noon' if  hour_z_next == 12  else  str(hour_z_next)
  }


  if min_z == 15:
    result +=  'quarter past ' + curr['msg']
  elif min_z < 30:
    result +=  + str(min_z) + ' past ' + curr['msg']
  elif min_z == 30:
    result += 'half past ' + curr['msg']
  elif min_z > 30:
    result += str(60 -min_z)  +  ' til ' + next['msg']
  return result

def missing_value (numbers):
  min = None 
  max = None 
  length = len(numbers) + 1 

  missing_sum = 0 
  real_sum = 0

  for ele in numbers:
    if min == None:
      min = ele
      max = ele 

    if ele < min:
      min = ele 
    
    if ele > max:
      max = ele 

    missing_sum += ele 

  real_sum = 0.5 * ( (length)  * (max + min) ) 
  return  real_sum - missing_sum

def rain_terraces (terraces):
  height = 0 
  curr_sum = 0 
  terrace_height = None 
  units = 0

  for i in range(0, len(terraces)):
    terrace_height = terraces[i]

    if (terrace_height >= height):
      if curr_sum:
        units += curr_sum
        curr_sum = 0
      height = terrace_height 
    
    if (terrace_height < height):
      curr_sum += height - terrace_height 
  return units 

def last_digit_a_to_b(a,b):
  count = 0
  start = b % 10
  end = None 
  cyclic_digits = [] 

  while end != start:
    count += 1
    end  = b**(count+ 1) % 10
    cyclic_digits.append(end)

  return cyclic_digits[ a % count]


def matrix_search(image, sub_image):
  match_found = None

  for r in range(0, len(image)):
    for  c in range(0, len(image[r])):

      if image[r][c] == sub_image[0][0]:
        match_found = True 
        
        for walk_row in range(0, len(sub_image)):
          if walk_row + r >= len(image):
            break

          for walk_col in range(0, len(sub_image[walk_row])):
            if walk_col + c >= len(image[r]):
              break
            
            match_found &= image[r + walk_row][c+walk_col] == sub_image[walk_row][walk_col]

  return match_found

def max_of_subarray (collection):
  curr_sum = 0
  start = 0 
  end = 0 
  branch_0 = None 
  branch_1 = None 
  index = 0
  number = None
  
  while index < len(collection):
    number = collection[index]

    if number >= curr_sum:
      end = index
      curr_sum += number 
    
    elif  index+ 1 < len(collection):
      branch_0 = curr_sum + number + collection[index + 1]
      branch_1 = collection[index + 1]

      if branch_1 > branch_0: # non-contigious sum path larger
        curr_sum = branch_1
        index += 1
        start = index
        end = index 
      else:  # contigious sum path larger 
        curr_sum = branch_0
        end = index + 1 
        index += 2
  
    index +=1 
  
  return[start, end]

