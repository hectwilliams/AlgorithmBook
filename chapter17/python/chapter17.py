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

  def removeEdges (self, id):
    for r in range (0, self.n) :
      for  c in range (0, self.n):
        if self.adjacentMap[r][c] != None and (r == id or c == id) :
          self.adjacentMap[r][c] = -1

  def removeEdge (self, id1, id2) :
    if id1 < self.n and id2 < self.n:
      if self.adjacentMap[id1][id2] != None:
        self.adjacentMap[id2][id2] = -1

  def getEdgeValue (self, id1, id2) :
    if  id1 >=0  and id1 < self.n and id2 < self.n and id2 >= 0:
      if self.adjacentMap[id1][id2] != None:
        return self.adjacentMap[id1][id2]
    return None

  def setEdgeValue(self, id1, id2 , value):
    if  id1 >=0  and id1 < self.n and id2 < self.n and id2 >= 0:
      if self.adjacentMap[id1][id2] != None:
        self.adjacentMap[id1][id2] = value
        return True
    return None

  def adjacent (self, id1, id2) :
    if  id1 >=0  and id1 < self.n and id2 < self.n and id2 >= 0:
      if self.adjacentMap[id1][id2] > 0:
        return True
    return False

  def neighbors(self, id):
    ids = []
    if id >= 0 and id < self.n:
      for i in range(0, self.n):
        if self.adjacentMap[id][i] > 0:
          ids.append(i)
    return ids

  def display(self):
    for arr in self.adjacentMap:
      print(arr)

class ALVertex :
  def __init__(self, value, id) :
    self.value = value
    self.id = id
    self.ids = []
    self.edges = []
class ALGraph:
  def __init__(self):
    self.counter = 0
    self.adjacentList = []
  def display (self) :
    for vertex in self.adjacentList:
      print(vertex.__dict__)
  def addVertex (self, value) :
    self.adjacentList.append( ALVertex(value, self.counter))
    self.counter += 1
    return self.counter - 1
  def removeVertex(self, id):
    removed = False
    pos = 0
    while pos < self.adjacentList.__len__():
      if self.adjacentList[pos].id == id:
        if self.adjacentList[pos].id == id:
          self.adjacentList.pop(pos)
      else:
        index = None
        for i in range(0, self.adjacentList[pos].ids.__len__()):
          index = i if self.adjacentList[pos].ids[i] == id else index
        if index >=0:
          self.adjacentList[pos].ids.pop(index)
          self.adjacentList[pos].edges.pop(index)

        pos += 1
    return removed
  def getVertexValue(self,id) :
    for vertex in self.adjacentList:
      if vertex.id == id:
        return vertex.value
    return None
  def setVertexValue (self, id, value) :
    for vertex in self.adjacentList:
      if vertex.id == id:
        vertex.value = value
    return False
  def addEdge (self, id1, id2, edgeValue) :
    vertexA = vertexB = None

    for vertex in self.adjacentList:
      if id1 == vertex.id:
        vertexA = vertex
      if id2 == vertex.id:
        vertexB = vertex

    if vertexB and vertexA:
      vertexA.ids.append(id2)
      vertexA.edges.append(edgeValue)
      return True

    return False
  def removeEdges (self, id) :
    for vertex in self.adjacentList:
      i = 0
      while i < vertex.ids.__len__():
        if vertex.ids[i] == id:
          vertex.ids.pop(i)
          vertex.edges.pop(i)

        else :
          i += 1


graph = ALGraph()
graph.addVertex('a')
graph.addVertex('b')
print(graph.setVertexValue(1,122))
graph.addEdge(0, 1 , 900)
graph.removeEdges(1)
# graph.removeEdges(0)
graph.display()
