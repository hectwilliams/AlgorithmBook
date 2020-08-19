
def interleave_arrays(a, b):
  result =  []
  index = [0,0]

  while sum(index) < len(a) + len(b):

    if index[0] < len(a):
      result.append(a[index[0]])
      index[0] += 1

    if index[1] < len(b):
      result.append(b[index[1]])
      index[1] += 1

  print(result)
  return result

def merge_sorted_arrays (a, b):
  result = []
  currA = currB = 0

  while currA + currB < len(a) + len(b):

    if currA < len(a) and currB < len(b):

      if a[currA] < b[currB]:
        result.append(a[currA])
        currA += 1
      elif b[currB]  < a[currA]:
        result.append(b[currB])
        currB += 1
      else :
        result.append(a[currA])
        result.append(b[currB])
        currA += 1
        currB += 1
    elif currA < len(a):
      result.append(a[currA])
      currA += 1
    elif currB < len(b) :
      result.append(b[currB])
      currB += 1
  return result

def min_three_way_range(collection):
  mins = [None, None, None]
  result  = None
  for i, arr in enumerate(collection):
    for k in range(0, len(arr)):
      if mins[i] == None or arr[k] < mins[i]:
        mins[i] = arr[k]

  for i in range(0, 3):
    tmp = collection[i]
    min_subset = mins[0: i] + mins[i + 1: :]
    for curr in tmp:
      if (curr > min_subset[0] and curr < min_subset[1]):
        if result == None:
          result = min_subset
        if  min_subset[1] - min_subset[0] < result[1] - result[0]:
          result = min_subset
  return result



def test():
  a = [1,2,3,4]
  b = [5,6,7,8]
  c =[ [1,2,4,15],[3,10,12],[5,10,13,17,23] ]
  x = min_three_way_range(c)
  print(x)
test()