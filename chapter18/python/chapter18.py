import math

OCTAL = 8

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

test = octStr2Val("37")

print(test)