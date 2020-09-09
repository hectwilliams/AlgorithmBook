class ELEdge :
  def __init__(self, val, id) :
    self.value = val
    self.id = id
class ELGraph :
  def __init__(self):
    self.vertexList = []
    self.edgeList = []
  def addVertex (self, value) :
    self.vertexList.append(ELEdge(value, self.vertexList.__len__()))
    return self.vertexList.__len__() - 1
  def display(self):
    string = ""
    for vertex in self.vertexList:
      string += "{" + str(vertex.id) +"-" + str(vertex.value) + "}" + " , "
    print("vertex ", string )
    print("edges " , self.edgeList)
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

graph = ELGraph()
graph.addVertex(22)
graph.setVertexValue(0, 299)
print(graph.getVertexValue(0))
graph.display()