def bubbleSort(array):
  size = len(array)
  for i in range(0, size - 1):
    for k in range(0, size - i - 1):
      if array[k] > array[k + 1]:
        array[k], array[k + 1] = array[k+ 1], array[k]

def bubbleSortTest():
  collection = [5,4,3,2,1]
  bubbleSort(collection)
  print(collection)

bubbleSortTest()