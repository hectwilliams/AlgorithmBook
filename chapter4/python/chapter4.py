def remove_blanks(str):
  index = 0
  while index < len(str):
    if str[index] == ' ':
      str = str[0 : index] + str[index + 1: :]
    else:
      index += 1
  return str

def get_digits(str):
  code = None
  result = ''
  for c in str:
    code= ord(c)
    #if (code >=  65 and code <= 90) ^ (code >= 97 and code <= 122):
    if code >= 48 and code <= 57:
      result += c
  return result

def acroynyms(str):
  state  = -1
  result = ''
  code = None

  for c in str:
    code = ord(c)
    if state == 0  and code == 32:
      state = -1

    if state == -1:
      if (code == 45) or  (code >=  65 and code <= 90) ^ (code >= 97 and code <= 122):
        state = 1

    if state == 1:
      result += c.capitalize()
      state = 0

  return result

def count_non_spaces (str):
  result = ''
  for c in str:
    if ord(c) is not 32:
      result += 1
  return result

def remove_shorter_string(str, length):
  words = str.split()
  result = ''
  for word in words:
    if len(word)  >=  length:
      result += word + ' '
  return result
      
def reverse_str(string):
  max = len(string)
  pos = 0
  rev_string= ''

  while pos < max:
    rev_string += string[max - pos - 1]
    pos += 1
  return rev_string 

def remove_even_strings(list_of_strings):
  index = 0
  while index < len(list_of_strings):
    if not (len(list_of_strings[index]) % 2):
      list_of_strings = list_of_strings[0 : index] + list_of_strings[index + 1: :]
    else:
      index += 1
  return list_of_strings




def integer_to_roman_numerals(number):
  numerals = {1: 'I', 5: 'V', 10: 'X', 50: 'L', 100: 'C', 500: 'D', 1000: 'M'}
  result = ''
  data = [] 
  list1 = sorted(numerals.keys())

  def double_digit_mode(a, number):
    data = None
    
    for num in list1: 
      if (num < a)  and (a - num <= number):
        data = [a, num] 
        break
    return data 

  while number > 0:
    data = [] 

    if number >= 1000:
      data = [1000]

    elif number >= 500:
      data = double_digit_mode(1000, number)
      data =  [500] if  data is None else data

    elif number >= 100:
      data = double_digit_mode(500, number)
      data =  [100] if data is None else data

    elif number >= 50: 
      data = double_digit_mode(100, number)
      data =  [50] if  data is None else data

    elif number >= 10:
      data = double_digit_mode(50, number)
      data =  [10] if  data is None else data

    elif number >= 5: 
      data = double_digit_mode(10, number)
      data =  [5] if data is None else data

    else:
      data = double_digit_mode(5, number)
      data =  [1] if data is None else data

    if len(data) == 2:
      result += numerals[data[1]] + numerals[data[0]]
      number -= data[0] - data[1]
    else:
      result += numerals[data[0]]
      number -= data[0]
    
  return result 

def roman_to_numerals (roman_numeral):
  numerals = {
    'I': 1, 
    'V': 5,
    'X': 10, 
    'L': 50,
    'C': 100,
    'D': 500,
    'M': 1000
  }
  
  index = 0
  result = ''
  length = len (roman_numeral) 
  sum = 0

  while index < length:
    curr = roman_numeral[index] 
    if index + 1 < length:
      next = roman_numeral[index + 1]        
    if next:
      if numerals[curr] < numerals[next]:
        sum +=  numerals[next] - numerals[curr]
        index += 2
        continue  
    sum += numerals[curr]
    index  += 1   
  return sum

def paren_valid(message):
  marker = { ')' : '('}
  open_brace = '('
  buffer = []

  for c in message:

    if c in open_brace:
      buffer.append(c)
    elif c in marker:
      if not len(buffer): 
        return False
      if buffer[-1] == marker[c]:
        buffer.pop()
      else:
        return False
  return True

def braces_valid(message):
  marker = {
    ')': '(',
    '}': '{',
    ']': '[',
    '<': '>',
  }
  opens = '({[<'
  buffer = [] 
  for c in message:

    if c in opens:
      buffer.append(c)
    elif c in marker:
      if not len(buffer): 
        return False
      if buffer[-1] == marker[c]:
        buffer.pop()
      else:
        return False
  return True

def is_palindrome(msg):
  index = 0 
  for i in range(len(msg) - 1, -1, -1):
    if msg[i] != msg[index]:
      return False 
    index += 1     
  return True

def is_palindrome_2(msg):
  index_left = 0
  index_right = len(msg) - 1
  
  while index_left <= index_right:

    if msg[index_left] == ' ':
      index_left += 1

    elif msg[index_right] == ' ':
      index_right -= 1
    
    else:

      if msg[index_left] != msg[index_right]:
        return False

      index_left += 1
      index_right -= 1
  return True

def longest_palindrome(msg):
  start_index = 0
  result = ''

  while start_index < len(msg):
    start_char = msg[start_index] 
    for end_index in range(len(msg) - 1, start_index - 1 , -1):
      end_char = msg [end_index] 
      if end_char == start_char:
        data = msg[start_index : end_index + 1]
        if is_palindrome(data):
          if len(result)  < len(data):
            result = data
    start_index += 1
  return result             

def is_word_alphabetical(msg):
  for i in range(1, len(msg)):
    if msg[i] != ' ' and msg[i-1] != ' ':
      if msg[i -1] > msg[i]:
        return False
  return True    

def d_gets_jiggy(name):
  if len(name) > 1:
    return name[1].capitalize() + name[2::] + ' ' + 'to the' + ' ' + name[0].capitalize() + '!'     
def common_suffix( word_list):
  result = ''
  index = 0 
 
  while True:
    for word in word_list:
      if index < len(word):
        c = word[len(word) -1 - index]
        if len(result) == index:
          result = c + result
        if result[0] != c :
          return result[1:]
      else:
        return result 
    index += 1

def book_index (pages): 
  buffer = []
  curr = []
  for i in range(0, len(pages) - 1):
    curr.append(pages[i])
    if pages[i] + 1 != pages[i + 1]:
      buffer.append(curr)
      curr = []
  if not curr:
    buffer.append([pages[-1]])
  return buffer    
  
 
def drop_the_mike(string):
  string = string.strip()
  result = ''

  for word in string.split():

    if word == 'Mike':
      return 'stunning violence'

    if len(word):
      a = word[0].capitalize() 
      b = word [1:] if len(word) > 1 else ''
      result += a + b + ' '
    
    return result 

def avg_of_obj(arr):
  obj = {
    'max': None,
    'min': None,
    'avg': 0
  }
  
  for num in arr:
    obj['avg'] += num 
  
    if obj['max'] == None or num > max:
      obj['max'] = num
 
    if obj['min'] == None or num < min:
      obj['min'] = num

  if len(arr):
    obj['avg'] = obj['avg'] / len(arr)  

  return obj  

def zip_arrays_to_map(a,b):
  result = {}

  if len(a) != len(b):
    return None
  
  for i in range(0, len(a)):
     result [a[i]] = b[i]
  
  return result 

def invert_hash(obj):
  for key in obj:
    obj[obj[key]] = key
    del obj[key] 
  return obj

def number_of_kv(obj):
  count = 0
  for ele in obj:
    count += 1
  return count
 
x =number_of_kv( {'od': 22, 'paul': 'moon'  } )
print(x)



