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

hash = HashMap()
hash.add("hello", 222)
