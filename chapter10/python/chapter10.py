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

optimal_sequence_test()