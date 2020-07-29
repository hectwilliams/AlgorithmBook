import copy
def rotate_string(string, n):
  head = ""
  back = ""
  c = None
  size = len(string)

  for i in range(0, len(string)):
    c = string[i]
    if i >= size - n:
      head += c
    else:
      back += c
  return head + back

def rotate_string_test():
  n = 5
  data = rotate_string ("Boris Godunov" , n)
  print(data)

def ionis_rotate(str1, str2):
  if len(str1) != len(str2):
    return False

  for i in range(0, len(str1) ):
    if str2 == rotate_string(str1, 1):
      return True
  return False

def ionis_rotate_test():
  test = ionis_rotate ("abcd", "bc")
  print(test)

def bad_character (string, bad):
  index = 0
  while index < len(string):
    if string[index] in bad:
      string = string.replace(string[index], '', 1)
    else:
      index += 1
  return string

def bad_character_test():
  string = "abcdef"
  bad = "ab"
  print(bad_character(string, bad))

def censor (string, naughty_list):
  for word in naughty_list:
    index = string.find(word)
    string = string.replace(word, 'x'* len(word))
  return string

def censor_test():
  string = "hector_williams_abc_def"
  censor(string, ['abc', 'ee', 'def'])

def genetic_marker (string, collection, index = 0):
  if index == len(collection):
    return False
  if string in collection[index]:
    return True
  else:
    return genetic_marker(string, collection, index + 1)

def genetic_marker_test():
  string = "abc"
  collection  = ["abc?r", "jeff", "kiki"]
  print(genetic_marker(string, collection))


def optimal_sequence(collection):
  buffer = []
  max_len = None
  i = 0
  state = { 'done': False, 'seq': [] }

  for word in collection:
    buffer.append('')
    if max_len == None:
      max_len = len(word)
    i += 1
  optimal_sequence_helper(collection, buffer, max_len, state)

  return state['seq']

def optimal_sequence_helper_is_sorted(collection, max_index):
  result = True
  list_len = len(collection)

  for i in range(0, list_len - 1):
    for c_index in range(0, max_index + 1):
      result = result and  collection[i][c_index] <= collection[i+1][c_index]
  return result

def optimal_sequence_helper_sort_via_column (collection, buffer, index):
  obj = { "min": None, "pos": 0}
  c = None

  #insertion sort
  for curr_index in range( 0, len(buffer) ):

    obj['min'] = buffer[curr_index][index]
    obj['pos'] = curr_index

    for search_index in range (curr_index + 1, len(buffer) ):
      c = buffer[search_index][index]
      if obj['min'] == None or c < obj['min']:
        obj['min'] = c
        obj['pos'] = search_index

    if obj["pos"] != curr_index:
      buffer[curr_index], buffer[  obj["pos"] ] = buffer[  obj["pos"] ], buffer[curr_index] # swap
      collection[curr_index], collection[  obj["pos"]] = collection[  obj["pos"]], collection[curr_index] # swap


def optimal_sequence_helper(collection, buffer, threshold, state, col_index = 0):
  clone_buffer = []
  clone_collection = []

  if state['done']:
    return

  # clone buffer
  for word in buffer:
    clone_buffer.append(word)

  # clone collection
  for word in collection:
    clone_collection.append(word)

  if col_index >= threshold  :
    state['done'] = 1
    state['seq'] = clone_buffer
    return

  for code in range(65, 91):  #possible chars

    for k in range(0, len(collection)):
      if collection[ k ] [col_index] == '?':
        clone_buffer[k] += chr(code)
      else:
        clone_buffer[k] += collection[ k ] [col_index]

    #update sort
    optimal_sequence_helper_sort_via_column(clone_collection, clone_buffer, col_index)

    if optimal_sequence_helper_is_sorted(clone_buffer, col_index):
      optimal_sequence_helper(clone_collection, clone_buffer, threshold, state,  col_index + 1)  # recursive search

    ##reset clones

    # remove appended chars
    for i in range( 0, len(clone_buffer) ):
      clone_buffer[i] = buffer[i]

    # remove appended
    for i in range( 0, len(clone_collection) ):
      clone_collection[i] = collection[i]

def optimal_sequence_test():
  collection = ["EA?K","?RX?","GAG?"]

  result = optimal_sequence(collection)
  print(result)

def dedupe(string):
  if not string:
    return ''
  return  ('' if (string.rfind(string[0]) != 0) else string[0] ) + dedupe(string[1: :])

def dedupe_test():
  msg = "Snaps! crackles! pops!"
  test = dedupe(msg)
  print(test)

def dedupe(string, index = 0) :
  if index >= len(string):
    return -1

  if string.count(string[index]) == 1:
    return index

  return dedupe(string, index + 1)

def dedupe_test():
  msg = "empathetic monarch meets primo stinker"
  x = dedupe(msg)
  print(x)

def uniqueLetters(string, index = 0):
  if index >= len(string):
    return ''
  return string[index] + uniqueLetters(string, index + 1) if string.count(string[index]) == 1 else uniqueLetters(string, index + 1)

def unqiueLetters_test():
  msg = "Snap! Crackle! Poop!"
  print(uniqueLetters(msg))

def num_to_string(num):
  return num_to_string_helper(num,0) + "." + num_to_string_helper(num * 10.0, -1)

def num_to_string_helper (num, dir):
  digit = int(num) % 10

  if dir >= 0  and int(num) > 0:
    return str(digit) + num_to_string_helper(num / 10, dir + 1)

  if dir < 0:
    if (num_to_string_zeros(num) or digit):
      return str(digit) + num_to_string_helper(num * 10, dir - 1)

  return ''

def num_to_string_zeros (number, count = 0):
  if count == 5:
    return True

  if number % 10 != 0:
    return False

  return num_to_string_zeros(number * 10, count + 1)


def num_to_string_test():
  test = num_to_string(11.2051)
  print(test)

def num_to_text(number):
  base = num_to_string(number)
  whole = ""
  decimal = ""
  point_pos = base.find('.')

  text_map = {
    0: {
      1: "One Hundred ",
      2: "Two Hundred ",
      3: "Three Hundred ",
      4: "Four Hundred",
      5: "Five Hundred",
      6: "Six Hundred",
      7: "Seven Hundred",
      8: "Eight Hundred",
      9: "Nine Hundred"
    },

    1: {
      2: "Twenty ",
      3: "Thirty ",
      4: "Fourty ",
      5: "Fifty ",
      6: "Sixty ",
      7: "Seventy ",
      8: "Eighty ",
      9: "Ninety "
    },

    2: {
      0: "zero",
      1: "one ",
      2: "two ",
      3: "three ",
      4: "four ",
      5: "five ",
      6: "six ",
      7: "seven ",
      8: "eight ",
      9: "nine "
    },

    3: {
      1: "Thousand ",
      2: "Million ",
      3: "Billion ",
      4: "Trillion ",
      5: "Quadrillion",
      6: "Quintillion"
      # ...
    }
  }

  if point_pos > 0:
    whole = base[0 : point_pos]
    decimal = base [point_pos + 1 : :]

  return num_to_text_parser_whole(whole, text_map) +  num_to_text_parser_decimal(decimal, text_map)

def num_to_text_parser_whole(string, obj, level = 0):
  buffer = ['', '', '']
  text = ""
  length = len(string)

  for i in range(0, 3):
    if length:
      buffer [3 - 1 - i] = string[i]
    length -= 1

  text = num_to_text_translate(buffer, obj)

  if level in obj[3]:
    text += obj[3][level]

  if len(string) >= 3:
    return num_to_text_parser_whole(string[3 : :], obj,  level + 1) + text

  return text

def num_to_text_translate(array, obj ):
  buffer = ""
  digit = 0

  for i in range(0, 3) :
    if array[i] != '' :
      digit = ord(array[i]) - 48
      if i == 2 and digit == 0:
        continue
      if digit in obj[i]:
        buffer += obj[i][digit]
  return buffer

def num_to_text_parser_decimal(string, obj, index = 0):
  digit = None

  if not string:
    return ""

  digit = ord(string[0]) - 48

  if digit in obj[2]:
    return  ("point " if index == 0 else "")  +  obj[2][digit] + num_to_text_parser_decimal(string[1 : :], obj, index + 1)

  return ""


def num_to_text_test():
  test = num_to_text(40213.23)
  print(test)

def isPermtutaoin (string, perm, buffer = "") :
  state = False

  if len(buffer) == len(perm) :
    if buffer == perm:
      return True
    return False

  for i in range(0, len(string)):
    state = isPermtutaoin(string[0 : i] + string[i + 1 : :], perm, buffer + string[i])
    if state:
      break
  return state

def isPermtutaoin_test():
  state = isPermtutaoin("mister", "timer")
  print(state)

def is_pangram_helper(string, obj = {}):
  c = ''
  bit = 0

  if not string:
    return 0

  c = string[0].lower()

  if c.isalpha() and c not in obj:
    obj[c] = 1
    bit = 1

  return bit + is_pangram_helper(string[1 : : ], obj)

def is_pangram (string):
  return is_pangram_helper(string) == 26

def is_pangram_test():
  msg = "How quickly daft jumping zebras vex!"
  answer = is_pangram(msg)
  print(answer) # true
  msg2 = "abcdef ghijkl mno pqrs tuv wxy, not so fast!"
  answer = is_pangram(msg)  # false
  print(answer)

is_pangram_test()
