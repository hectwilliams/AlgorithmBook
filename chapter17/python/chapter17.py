import copy

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

  def setEdgeValue (self, id1, id2, edge) :
    for v1 in self.adjacentList:
      if v1.id == id1:
        for adj in v1.adjacent:  # adj = array
          if adj[0] == id2:
            adj[1] = edge
            return True
    return False

  def adjacent (self, id1, id2) :
    currID = None
    for vertex in self.adjacentList:
      if vertex.id == id1 or vertex.id == id2:
        currID = vertex.id
        for adj in vertex.adjacent:   # adj  = array
          if (currID == id1 or  adj[0] == id2) or (currID == id2 or  adj[0] == id1) :
            return False
    return True

  def neighbors (self, id) :
    result = []

    for vertex in self.adjacentList:
      for adj in vertex.adjacent:
        if vertex.id == id :  # FROM
          result.append(adj[0])
        elif adj[0] == id:   # TO
          result.append( vertex.id)
    return result

class GraphNetwork:
  def __init__(self):
    self.vertexList = []

class SocialNetworkVertex :
  def __init__(self, name= None, id = None):
    self.name = name
    self.id = id
    self.friends = []

def someoneOnInside (graph , srcID, employeeIDs = []) :
  stack = []
  visited = {}
  currVertex = None

  for vertex in graph.vertexList:
    stack.append(vertex)

    while stack :
      currVertex = stack.pop()
      visited [str(currVertex.id)] = True

      for friendVertex in currVertex.friends:
        if friendVertex.id == srcID:
          if currVertex.id in employeeIDs:
            return True
        if visited [str(friendVertex.id)] == None :
          stack.append(friendVertex)

  return False


def someoneOnInsideNoReference(graph):
  stack = []
  visited = {}
  data = {'count': 0, 'insider': None }

  for vertex in graph.vertexList:
    stack.append(vertex)

    while stack:
      currVertex = stack.pop()

      for friendVertex in currVertex.friends:

        if visited[ str(friendVertex.id) ]:
          visited[ str(friendVertex.id) ]['followers'] += 1
        else:
          stack.append(friendVertex)
          visited[str(friendVertex.id)] = {'contact': currVertex.id, 'employeeID': friendVertex.id, 'followers': 1}

        if data['count'] < visited[str(friendVertex.id)]['followers']:
          data['insider'] =  visited[str(friendVertex.id)]
          data['count'] = visited[str(friendVertex.id)]['followers']

  return data['insider']

def vertexIsReachable(graph , id1, id2) :
  stack = []
  path = []
  visited = {}

  for vertex in graph.vertexList:
    if vertex.id == id1:
      stack.append([vertex, None])
      path.append(id1)
      while stack:
        arr = stack.pop()
        visited[arr[0].id] = True

        if arr[1] == vertex :
          path = [id1]

        path.append(arr[0].id)

        if path[-1] == id2:
          return path

        for friendVertex in arr[0].friends:
          if not ( friendVertex.id in visited) :
            stack.append([ friendVertex, arr[0]])

  return path

def allPaths (graph , source_id , id1, id2):
  stack = []
  path = []
  visited = {}
  paths = []

  for vertex in graph.vertexList:
    if vertex.id == id1:
      stack.append([vertex, None])
      path.append(id1)
      while stack:
        arr = stack.pop()
        visited[arr[0].id] = True

        if arr[1] == vertex :
          path = [id1]

        path.append(arr[0].id)

        if path[-1] == id2:
          paths.append(path)

        for friendVertex in arr[0].friends:
          if not ( friendVertex.id in visited) :
            stack.append([ friendVertex, arr[0]])

  return paths

def shortestPath (graph , id1, id2) :
  queue = []
  currVertex = None
  table = {}
  path = []

  for vertex in graph.vertexList:
    if vertex.id == id1:
      table[vertex.id] = None
      queue.append(vertex)
      while queue and not table[id2] :
        currVertex = queue.pop(0)
        for friendVertex in currVertex.friends:
          if not table[friendVertex.id] :
            table[friendVertex.id] = currVertex.id
            queue.append(friendVertex)
      currID = id2
      while currID != None:
        path.append(currID)
        currID = table[currID]
      break
  return path

def gimmieThreeSteps (graph , id) :
  queue = []
  vertex = None
  visited = {}
  ids = []
  MAXSTEP = 3

  for i in range(0, graph.vertexList ):
    if graph.vertexList[i].id == id:
      visited[graph.vertexList[i].id] = 0
      queue.append(graph.vertexList[i])
      while queue:
        vertex = queue.pop(0)
        for friendVertex in vertex.friends:
          if not (friendVertex.id in visited):
            if visited[vertex.id] + 1 <= MAXSTEP:
              visited[friendVertex.id] = visited[vertex.id] + 1
              queue.append(friendVertex)
              ids.append(friendVertex.id)
  return ids

def easyToGetThere (graph = GraphNetwork()) :
  queue = []
  table = {}
  ids = []

  for i in range(0, graph.vertexList ):
    queue.append( graph.vertexList[i] )

    while queue:

      vertex = queue.pop(0)

      if not (vertex.id in table) :
        table[vertex.id] = {'in': 0, 'out': 0}

      for friendVertex in vertex.friends:

        if not (friendVertex.id in table):
          queue.append(friendVertex)
          table[friendVertex.id] = {'in': 0, 'out': 0}

        table[vertex.id]['out'] += 1
        table[friendVertex.id]['in'] += 1

    for key in table:
      if table[key]['in'] > table[key]['out']:
        ids.append(key)

  return ids

def isDaG (graph = GraphNetwork(), array= []) :
  queue = visited = foundTail = vertex = isvalid = None

  for i in range (0, graph.vertexList.__len__()):
    queue = []
    visited = {}
    foundTail = False
    isvalid = true
    queue.append(graph.vertexList[i])
    array.clear()

    while queue.__len__() and isvalid:
      vertex = queue.pop(0)
      isvalid = vertex.friends.__len__() <= 1 and foundTail == False
      foundTail = vertex.friends.__len__() == 0
      visited[vertex.id] = True
      array.append(vertex.id)

      for friendVertex in vertex.friends:
        if not (friendVertex.id in visited) :
          visited[friendVertex.id] = True
        else:
          isvalid = False

    if isvalid:
      return True

  array.clear()
  return False

def DAG_to_Array(graph = GraphNetwork()):
  array = []
  isDaG(graph, array)
  return array

words= [
  "cup",
  "dog",
  "dig",
  "top",
  "mop",
  "cop",
  "cap",
  "lap",
  "lip",
  "hip",
  "cat"
]

def wordLadder (wordA, wordB, path = [], visited = {}, paths = []) :
  strBuffer = ""

  if not  ( wordA in visited):
    path.append(wordA)
  visited[wordA] = True

  if path[-1] == wordB:
    paths.append(path)

  for i in range(97, 123) :
    for j in range(0, 3):
      strBuffer = wordA[0 : j] + chr(i) + wordA[j + 1: :]
      if (strBuffer in words) and   not (strBuffer in visited):
        visited[strBuffer] = True
        wordLadder(strBuffer, wordB, path + [strBuffer], copy.deepcopy(visited))
        del visited[strBuffer]

  return paths


print (wordLadder("top", "hip") )
