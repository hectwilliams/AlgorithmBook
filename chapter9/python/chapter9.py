def recursive_sigma(number: int):
  if number <= 0:
    return 0
  return number + recursive_sigma(number - 1)

def recursive_factorial(number:float):
  if number <= 1:
    return 1
  return int(number) * recursive_factorial(number - 1)

def flood_fill(canvas2D, xy: [int, int], newColor: int):
  row = xy[0]
  col = xy[1]
  prevColorState = None 
  newXY = [] 

  if (row < 0 or row >=5) or (col < 0 or col >=5):
    return None  
  
  prevColorState = canvas2D[row][col]

  # fill xy w/ new color
  canvas2D[row][col] = newColor

  #walk up
  if row > 0:
    newXY = [row - 1, col]
    if prevColorState == canvas2D[ newXY[0] ] [ newXY[1] ]:
      flood_fill(canvas2D, newXY, newColor)

  #walk down
  if row < 4:
    newXY = [row + 1, col]
    if prevColorState == canvas2D[newXY[0]][newXY[1]]:
      flood_fill(canvas2D, newXY, newColor)

  #walk left 
  if (col > 0):
    newXY = [row, col - 1]
    if prevColorState == canvas2D[newXY[0]][newXY[1]]:
      flood_fill(canvas2D, newXY, newColor)

 #walk right 
  if (col < 4):
    newXY = [row, col + 1]
    if prevColorState == canvas2D[ newXY[0] ] [ newXY[1] ]:
      flood_fill(canvas2D, newXY, newColor)


def flood_fill_test():
  canvas = [
    [3, 2, 3, 4, 3],
    [2, 3, 3, 4, 0],
    [7, 3, 3, 5, 3],
    [6, 5, 3, 4, 1],
    [1, 2, 3, 3, 3]
  ]
  startXY = [2,2]
  flood_fill(canvas, startXY, 1)
  print(canvas)


flood_fill_test()
