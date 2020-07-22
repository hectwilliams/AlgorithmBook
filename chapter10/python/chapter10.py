
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

bad_character_test()