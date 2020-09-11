class ELVertex :
  def __init__(self, val, id) :
    self.value = val
    self.id = id
class ELEdge:
  def __init__(self, id1, id2, val = 0):
    self.id1 = id1
    self.id2 = id2
    self.value = val
class ELGraph :
  def __init__(self):
    self.vertexList = []
    self.edgeList = []
  def addVertex (self, value) :
    self.vertexList.append(ELVertex(value, self.vertexList.__len__()))
    return self.vertexList.__len__() - 1
  def display(self):
    string = ""

    for vertex in self.vertexList:
      string += "{" + str(vertex.id) +"-" + str(vertex.value) + "}" + " , "
    print("vertex ", string )

    string = ''
    for edge in self.edgeList:
      string += "{" + str(edge.id1) +"-" + str(edge.id2) + "-" + str(edge.value) +"}" + " , "

    print("edges " , string)

  def removeVertex(self, id):
    index = None
    for  i, vert in enumerate(self.vertexList):
      index = i if vert.id == id else index
    if index != None:
      self.vertexList.pop(index)
    return index != None
  def getVertexValue (self, id):
    result = None
    for vertex in self.vertexList:
      if vertex.id == id:
        result = vertex.value
    return result
  def setVertexValue(self, id, value):
    for vertex in self.vertexList:
      if id == vertex.id :
        vertex.value = value
        return True
    return False

  def addEdge(self, id1, id2, value = 0) :
    count = 0
    for vertex in self.vertexList:
      count += (vertex.id == id1 or vertex.id == id2)
    for edge in self.edgeList:
      if edge.id1 == id1 and edge.id2 == id2:
        return None
    if count == 2:
      self.edgeList.append(ELEdge(id1, id2, value))
      return True
    return False

  def removeEdges(self, id):
    pos = 0

    while pos < self.edgeList.__len__():
      if self.edgeList[pos].id1 == id or self.edgeList[pos].id2 == id:
        self.edgeList.pop(pos)
      else :
        pos += 1

  def removeEdge(self, id1, id2) :
    for i in range(0, self.edgeList.__len__()):
      if self.edgeList[i].id1 == id1 and self.edgeList[i].id2 == id2:
        self.edgeList.pop(i)
        return True
    return False

  def getEdgeValue(self, id1, id2) :
    for edge in self.edgeList:
      if edge.id1 == id1 and edge.id2 == id2:
        return edge.value
    return None

  def setEdgeValue(self, id1, id2, value ):
    for edge in self.edgeList:
      if edge.id1 ==id1 and edge.id2 == id2:
        edge.value = value
        return True
    return False

  def adjacent(self, id1, id2):
    for edge in self.edgeList:
      if edge.id1 == id1 and edge.id2 == id2:
        return True
    return False

  def neighbors (self, id) :
    vertices = []
    for  edge in self.edgeList:
      if edge.id1 == id:
        vertices.append(edge.id2)
    return vertices

class AMGraph:
  def __init__(self):
    self.adjacentMap = []
    self.n = 0

  def addVertex(self):
    self.n += 1
    self.adjacentMap.append([])
    for r in range(0, self.n):
      for c in range(0, self.n):
        if self.adjacentMap[r].__len__() < self.n:
          self.adjacentMap[r].append(-1)

        if r == c and self.adjacentMap[r][c] :
          self.adjacentMap[r][c] = 0

        if r == self.n -1 and r > 0:
          if self.adjacentMap[r - 1] [c] == None:
            self.adjacentMap[r][c] = None

        if c == self.n -1 and c > 0:
          if self.adjacentMap[r ] [c - 1] == None:
            self.adjacentMap[r][c] = None


  def removeVertex(self, id):
    removed = False
    for r in range (0, self.n) :
      for  c in range (0, self.n):
        if self.adjacentMap[r][c] != None and  (r == id or c == id ) :
          self.adjacentMap[r][c] = None
          removed = True
    return removed

  def addEdge (self, id1, id2, value):
    if id1 < self.n and id2 < self.n:
      self.adjacentMap[id1][id2] = value
      return True
    return False

  def deleteEdge (self, id):
      arr = None

      for i in range (0, self.n):

        if i == id:
          continue

        if self.adjacentMap[id] :
          self.adjacentMap[id][i] = -1

        if self.adjacentMap[i] :
          self.adjacentMap[i][id] = -1

  def display(self):
    for arr in self.adjacentMap:
      print(arr)

graph = AMGraph()
graph.addVertex()
graph.addVertex()
graph.addVertex()
graph.addEdge(0 ,1,  22)
graph.removeVertex(1)

graph.display()
