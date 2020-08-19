
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

def intersect_sorted_array (a, b):
  result = []
  pos = [0,0]

  while 1:
    if pos[0] < len(a) and pos[1] < len(b):
      if a[pos[0]] < b[pos[1]] :
        pos[0] += 1
      elif b[pos[1]] < a[pos[0]] :
        pos[1] += 1
      else :
         result.append(a[pos[0]])
         pos[0] += 1
         pos[1] += 1
    else:
      break
  return result

def test():
  a = [1,2,3,4]
  b = [4,6,7,8]
  x = intersect_sorted_array(a,b)
  print(x)
test()