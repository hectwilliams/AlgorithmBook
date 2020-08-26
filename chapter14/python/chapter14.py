def hashCode(key):
  hash = 0
  code = None
  for character in list(key):
    code = ord(character)
    hash += code
  return hash

class HashMap :
  def __init__(self, cap = 10) :
    self.capacity = cap
    self.size = 0
    self.table = []
    for i in range(0, cap):
      self.table.append([])

  def empty(self):
    return self.size == 0

  def add (self, key, value) :
    index = hashCode(key) % self.capacity
    collection = self.table[index]
    pair = {'key': key, 'value': value}

    if not collection:
      collection.append( pair)
    else:
      for obj in collection:
        if obj['key'] == key and obj['value'] == value:
          return
      collection.append(pair)

  def find (self, key) :
    index = hashCode(key) % self.capacity
    collection = self.table[index]
    result = []
    for obj in collection:
      result.append(obj['value' ])
    return result

  def remove(self, key) :
    index = hashCode(key) % self.capacity
    collection = self.table[index]
    pos = 0
    result = None
    while pos < collection.__len__():
      if collection[pos]['key'] == key:
        result = collection[pos]['value']
        break
      pos += 1
    if pos < collection.__len__():
      self.size -= 1
      collection.pop(pos)
    return result

  def loadFactor(self, key):
    return self.size / self.capacity

  def grow (self):
    increase = self.capacity - int(self.capacity * 0.50)
    bucket_index = None
    code = None
    obj = None

    self.capacity += increase

    while increase:
      self.table.append([])
      increase -= 1

    for i in range (0, self.capacity):
      bucket_index = 0
      while bucket_index < self.table[i].__len__():
        obj = self.table[i][bucket_index]
        code  = hashCode(obj['key'])
        if code % self.capacity != i:
          self.table[i].pop(bucket_index)
          self.add(obj['key'] , obj['value'])
        else :
          bucket_index += 1

hash = HashMap()
hash.add("hello", 222)
print(hash.table)

hash.grow()
print(hash.table)
