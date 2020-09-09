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

  removeEdges(id)
  {
    let pos = 0;
    let edge;

    while (pos < this.edgeList.length)
    {
      edge = this.edgeList[pos];
      if (edge.vert_id1 == id || edge.vert_id2 == id)
      {
        this.edgeList.splice(pos, 1);
      }
      else
      {
        pos++;
      }
    }
  }

  removeEdge (id1, id2)
  {
    for (let i = 0; i < this.edgeList.length; i++)
    {
      if (this.edgeList[i].vert_id1 == id1 && this.edgeList[i].vert_id2 == id2)
      {
        this.edgeList.splice(i, 1)
        return true;
      }
    }
    return false;
  }

  getEdgeValue (id1, id2)
  {
    for (let edge of this.edgeList)
    {
      if (edge.vert_id1 == id1 && edge.vert_id2 == id2)
      {
        return edge.value;
      }
    }
    return null;
  }

  setEdgeValue (id1, id2, value)
  {
    for ( let edge of this.edgeList )
    {
      if (edge.vert_id1 == id1 && edge.vert_id2 == id2)
      {
        edge.value = value;
        return true;
      }
    }
    return false;
  }

  adjacent (id1, id2)
  {
    let index = this.edgeList.findIndex( (edge) => edge.vert_id1 == id1 && edge.vert_id2 == id2 )
    return index != -1;
  }

  neighbors (id)
  {
    let vertices  = [];
    for (let edge of this.edgeList)
    {
      if (edge.vert_id1 == id)
      {
        vertices.push(edge.vert_id2);
      }
    }
    return vertices;
  }

};

{
  let graph = new ELGraph ();
  graph.addVertex(200);
  graph.addVertex(2020);
  graph.addEdge(0, 1, 223322)
  graph.setVertexValue(0, 232);
  console.log(graph.adjacent(0, 1))
  // graph.removeEdges(1);
  // graph.display()

}