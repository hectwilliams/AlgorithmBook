import math

OCTAL = 8
HEXADECIMAL = 16

def dec2OctStr (value):
  string = ""
  while value > 0:
    string = str(value % OCTAL) + string
    value = int(value / OCTAL)
  return "0o" + string

def octStr2Val(string):
  sum = 0
  for i in range(0, string.__len__()):
    sum += int(string[string.__len__() - 1 - i]) *  int(math.pow(OCTAL, i))
  return sum

def dec2HexStr (value):
  string = ""
  tmp = None

  while value > 0 :
    tmp = value % HEXADECIMAL
    if tmp > 9:
      if tmp == 10:
        tmp = 'A'
      if tmp == 11:
        tmp = 'B'
      if tmp == 12:
        tmp = 'C'
      if tmp == 13:
        tmp = 'D'
      if tmp == 14:
        tmp = 'E'
      if tmp == 15:
        tmp = 'F'
    string = str(tmp) + string
    value = int(value / HEXADECIMAL)

  return string

def hexStr2Val (string):
  sum = 0
  c = None
  curr = None

  for i in range(0, string.__len__()):
    c = string[string.__len__() - 1- i].upper()
    if c == 'F' :
      curr = 15
    elif  c == 'E':
      curr = 14
    elif c == 'D':
      curr = 13
    elif c == 'C':
      curr = 12
    elif c == 'B':
      curr = 11
    elif c == 'A':
      curr = 10
    else:
      curr = int(c)
    sum += curr * int(pow(HEXADECIMAL, i))

  return sum

test = hexStr2Val("1F")

print(test)