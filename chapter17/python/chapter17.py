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
    self.adjacent = []

class ALGraph:
  def __init__(self):
    self.__counter = -1
    self.adjacentList = []

  def display (self) :
    for vertex in self.adjacentList:
      print(vertex.__dict__)

  def addVertex(self, value) :
    self.__counter += 1
    self.adjacentList.append (ALVertex(value, self.__counter))
    return id

  def removeVertex (self, id):
    for i, vertex in enumerate(self.adjacentList):
      if vertex.id == id :
        self.adjacentList.pop(i)
        return True
    return False

  def getVertexValue(self, id) :
    for vertex in self.adjacentList:
      if vertex.id == id:
        return vertex.value
    return None

  def setVertexValue(self, id, value ):
    for vertex in self.adjacentList:
      if vertex.id == id:
        vertex.value = value
        return True
    return False

  def addEdge(self, id1, id2, edge):
    v1 = v2 = None

    for vertex in self.adjacentList:
      if vertex.id == id1:
        v1 = vertex

      if vertex.id == id2:
        v2 = vertex

      if v1 and v2:
        v1 .adjacent.append([id2, edge])
        return True
    return False

  def removeEdges(self, id) :
    index_adj = None

    for vertex in self.adjacentList:
      if vertex.id == id:
        vertex.adjacent = []
      else:
        index_adj = 0
        while index_adj < vertex.adjacent.__len__():
          if vertex.adjacent[index_adj][0]   == id:
            vertex.adjacent.pop(index_adj)
          else :
            index_adj += 1

  def removeEdge (self, id1, id2) :
    removed = False
    for vertex in self.adjacentList:
      if vertex.id == id1:
        index = 0
        while index < vertex.adjacent.__len__():
          if vertex.adjacent[index][0] == id2 :
            vertex.adjacent.pop(index)
            removed |= True
          else :
            index += 1
    return removed

  def getEdgeValue(self, id1, id2):
    for v1 in self.adjacentList:
      if v1.id == id1:
        for adj in v1.adjacent:
          if adj[0] == id2:
            return adj[1]
    return None

class SocialNetworkVertex :
  def __init__(self, name= None, id = None):
    self.name = name
    self.id = id
    self.friends = []

def someoneOnInside (vertex, srcID, employeeIDs = []) :
  stack = []
  visited = []
  bufferVertex = SocialNetworkVertex()

  stack.append(vertex)

  while stack:
    bufferVertex = stack.pop()
    if bufferVertex.id in visited:
      continue
    else:
      visited.append(bufferVertex.id)
      if srcID == bufferVertex.id:
        for srcFriend in bufferVertex.friends:
          for employeeID in employeeIDs:
            if employeeID == srcFriend.id:
              return True
        return False
      for friend in bufferVertex.friends:
        stack.append(friend )

  return False

def someoneOnInsideNoReference(srcVertex):
  stack = []
  popularMapCount = {}
  insiderObj = {'contactID': None , 'insiderID' : None}
  vertex = None
  maxCount = 0

  stack.append(srcVertex)

  while stack:
    vertex = stack.pop()
    for friendVertex in vertex.friends:
      key = str(friendVertex.id)

      if not (key in popularMapCount) :
        popularMapCount[key] = 1
      else:
        popularMapCount[key] += 1

      if insiderObj['contactID'] == None or popularMapCount[key] > maxCount:
        insiderObj = {'contactID': vertex.id , 'insiderID' : friendVertex.id}
      stack.append(friendVertex)

  return insiderObj


def vertexIsReachable(srcVertex, id1, id2, visited = {} , path = [], meta = {'done': False, 'path': [] }  ) :
  stack = []
  vertex = None

  if meta['done'] or (id1 in path) or (id2 in path) or (srcVertex.id in path):
    return

  stack.append(srcVertex)

  while stack:
    vertex = stack.pop()
    visited [ str(srcVertex.id) ]  = True

    if vertex.id == id1 and path.__len__():
      path.append(vertex.id)
      if path[-1] == id2:
        meta['done'] = True
        meta['path'] = path[:]

    for friendVertex in vertex:
      if visited[str(friendVertex.id)] == None :
        stack.append(friendVertex)
        vertexIsReachable(friendVertex, id1, id2, visited, path[:], meta)

  return meta

def allPaths (srcVertex, source_id , destination_id, visited = {}, paths = [], currPath = []):
  stack = []
  vertex = None

  stack.append(srcVertex)

  while stack:
    vertex = stack.pop()
    visited[vertex.id] = True

    if vertex.id == source_id or currPath.__len__():
      currPath.append(vertex.id)

    if currPath[-1] == destination_id:
        paths.append(currPath[:])

    for friendVertex in vertex.friends:
      if visited[str(friendVertex.id)] == None :
        stack.append(friendVertex)
        allPaths(friendVertex, source_id, destination_id, visited, paths, currPath[:])

  return paths

def shortestPath (srcVertex, id1, id2, visited = {}, path = [], currPath = []) :
  queue = []
  vertex = None

  queue.append(srcVertex)

  while queue:
    vertex = queue.pop(0)
    visited[str(vertex.id)] = True

    if id1 == vertex.id or currPath.__len__() > 0:
      currPath.append(vertex.id)
      if currPath[currPath.__len__() - 1] == id2:
        if not path or currPath.__len__() < path.__len__():
          for ele in currPath:
            path.append(ele)

    for friendVertex in vertex.friends:
      if visited[str(friendVertex.id) ] == None:
        queue.append(friendVertex)
        shortestPath(friendVertex, id1 , id2, visited, path, currPath[:] )

def gimmieThreeSteps (srcVertex, id , visited = {}, ids = [], currPath = []) :
  queue = []
  vertex = None

  if currPath.__len__() >= 4:
    return

  queue.append(srcVertex)

  while queue:
    vertex = queue.pop(0)
    visited [ str(vertex.id) ] = True

    if id == vertex.id or currPath.__len__():
      currPath.append(vertex.id)
      ids.append(vertex.id)

    for friendVertex in vertex.friends:
      if visited [ str(friendVertex.id) ] == None:
        queue.append(friendVertex)
        gimmieThreeSteps(friendVertex, id, visited, ids, currPath[:])


graph = ALGraph()
graph.addVertex('a')
graph.addVertex('b')
# print(graph.setVertexValue(1,122))
graph.addEdge(0, 1 , 900)
# print(graph.setEdgeValue(0, 1, 404))
# graph.removeEdges(1)
# graph.removeEdges(0)
graph.display()
