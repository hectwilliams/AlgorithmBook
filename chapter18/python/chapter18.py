import math
from functools import reduce
OCTAL = 8
HEXADECIMAL = 16
BINARY = 2
WORD_SIZE = 32

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

def dec2BinStr(value) :
  string = ""
  while value > 0:
    string = str(value % 2) + string
    value = int(value / 2)
  return "0b" + string

def binStr2Val(string):
  sum = 0
  for i in range(string.__len__()):
    sum += int(string[string.__len__() - 1- i]) * pow(BINARY, i)
  return sum


def reorderWordFragment(collection):
  minChar = None
  len = collection[0].__len__()

  for i in range(0, len):
    minChar = 'A'
    for k in range(0, collection.__len__()):
      if i == 0:
        if collection[k][i]  == '?':
          collection[k] = collection[k][0 : i] + minChar + collection[k][i + 1 : :]
        pos = k
        while pos > 0:
          if collection[pos - 1][i] > collection[pos][i]   :
            collection[pos - 1], collection[pos] = collection[pos] , collection[pos  - 1]
          pos -= 1

      else:
        if collection[k][i]  == '?':
          collection[k] = collection[k][0 : i] + minChar + collection[k][i + 1 : :]
        else :
          minChar = collection[k][i]

      if k > 0 :
        if collection[k - 1][i ] > collection[k][i] :
          return None

  return collection

def countInBinary (val) :
  counter = 0
  max = math.pow(2,val)
  while counter < max:
    print(counter , dec2BinStr(counter))
    counter += 1

def countSetBits(value) :
  acc = 0
  while value > 0:
    acc += value % 2
    value = int(value / 2)
  return acc

def reverseBits (value):
  lb = rb = 0
  for i in range(0,WORD_SIZE / 2):
    lb = bool( (1 << WORD_SIZE - i - 1) & value  )
    rb = bool( (1 << i ) & value  )
    value &= ~(1 << (WORD_SIZE - 1 - i) ) & ~(1 << i)
    value |= (lb << i)
    value |= (rb << (WORD_SIZE - 1 - i))
    print(value)
  return value

def encode32(arr):
  sum = 0
  for i in range(0, 4):
    sum |= arr[i] << (4 - 1 - i) * 8
  return hex(sum)

def decode32 (value) :
  arr = []
  for i in range(0, 4):
    arr.insert(0, hex( (value & (0xFF << 8 * i) ) >> 8 * i ))
  return arr

def encodeBit (bit, pos, value):
  if pos >= 0 and pos < 32:
    value =  (value & ~(1 << pos) ) | (bit << pos)
  return value

def decodeBit (pos, value):
  if pos >= 0 and pos < 32:
    return (value & (1 << pos)) >> pos
  return None

def reduceArrays (a = [],b = []):
  return a + b

def radixSort2 (arr = []) :
  collection = []
  bucket = []

  for i in range(0, 32 ):
    collection.append([])
  collection[0] += arr

  for bitPosition in range(0, 32):
    for i in range(0, 32 ):
      bucket.append([])
    for row in range (0, collection.__len__()) :
      for j in range(0, collection[row].__len__()) :
        if  bool(collection[row][j] & (1 << bitPosition) ):
          bucket[bitPosition].append(collection[row][j])
        else:
          bucket[row].append(collection[row][j])
    collection = bucket
    bucket = []

  collection = reduce (reduceArrays, collection, [])

  for i in range(0, arr.__len__()):
    arr[i] = collection[i]

def LED2Numeral(ledByte):
  sevenSegmentSelct = {
    0b01110111: 0,
    0b00100100: 1,
    0b01011101: 2,
    0b01101101: 3,
    0b00101110: 4,
    0b01101011: 5,
    0b01111011: 6,
    0b00100101: 7,
    0b01111111: 8,
    0b00101111: 9
  }
  return sevenSegmentSelct[ledByte]

x = (LED2Numeral(0x7B))
print(x)
