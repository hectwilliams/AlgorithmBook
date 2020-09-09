class ELVertex
{
  constructor(value, id)
  {
    this.value = value;
    this.id = id;
  }
};

class ELEdge
{
  constructor(id1, id2, val = 0)
  {
    this.vert_id1 = id1;
    this.vert_id2 = id2;
    this.value = val;
  }
}

class ELGraph
{
  constructor()
  {
    this.vertexList = [];
    this.edgeList = [];
  }

  display()
  {
    console.log( "vertex ", this.vertexList);
    console.log( "edge ",  this.edgeList);
  }

  addVertex (value)
  {
    this.vertexList.push(new ELVertex(value, this.vertexList.length ));
    return this.vertexList.length - 1;
  }

  removeVertex(id)
  {
    let index = this.vertexList.findIndex( (ele) => ele.id == id );

    if (index != -1)
    {
      this.vertexList.splice(index, 1);
    }

    // TODO REEMOVE id in edge list array
    return index != -1;
  }

  getVertexValue (id)
  {
    let result = null;
    for (let vertex of  this.vertexList)
    {
      if (vertex.id == id)
      {
        result = vertex.value;
      }
    }
    return result;
  }

  setVertexValue(id, value)
  {
    for (let vertex of this.vertexList)
    {
      if (vertex.id == id)
      {
        vertex.value = value;
        return true;
      }
    }
    return false;
  }
  addEdge(srcId, destId, value)
  {
    let count = 0;
    for (let vertex of this.vertexList)
    {
      count += (vertex.id == srcId || vertex.id == destId)
    }
    for (let edge of this.edgeList)
    {
      if (edge.vert_id1 == srcId && edge.vert_id2 == destId)
      {
        return null;
      }
    }
    if (count == 2)
    {
      this.edgeList.push(new ELEdge(srcId, destId));
    }
    return count == 2;
  }

};

{
  let graph = new ELGraph ();
  graph.addVertex(200);
  graph.addVertex(2020);
  graph.setVertexValue(0, 232);
  console.log(graph.addEdge(0, 1))
  // graph.display()

}