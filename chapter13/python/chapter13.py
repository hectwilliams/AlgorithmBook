
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

def test():
  a = [1,2,3,4]
  b = [5,6,7,8]

  interleave_arrays(a ,b)

test()