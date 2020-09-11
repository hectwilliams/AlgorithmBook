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


class AMGraph
{
  constructor()
  {
    this.adjacentMap = [];
    this.n = 0;
  }

  addVertex()
  {
    let data;
    this.n++;

    this.adjacentMap.push ([] );

    for (let r  = 0; r < this.n; r++)
    {
      for (let c = 0; c < this.n; c++)
      {
        if (this.adjacentMap[r].length < this.n )
        {
          this.adjacentMap[r].push(-1);
        }

        if ( r == c && this.adjacentMap[r][c])
        {
          this.adjacentMap[r][c] = 0;
        }

        if (r == this.n - 1 && r > 0)
        {
          if (this.adjacentMap[r - 1][c]  == null)
          {
            this.adjacentMap[r ][c]  = null;
          }
        }

        if (c == this.n - 1 && c > 0)
        {
          if (  this.adjacentMap[r][c - 1]  == null  )
          {
            this.adjacentMap[r][c]  = null;
          }
        }

      }
    }
  }

  removeVertex(id)
  {
    let removed = false;
    for (let r = 0; r < this.n; r++)
    {
      for (let c = 0; c < this.n; c++)
      {
        if ( this.adjacentMap[r][c] != null  && (r == id || c == id) )
        {
          this.adjacentMap[r][c] = null;
          removed |= true;
        }
      }
    }
    return removed;
  }

  addEdge(id1, id2, value)
  {
    let arr = this.adjacentMap[id1];
    if (arr)
    {
      if (id2 < this.n)
      {
        arr[id2] = value;
        return true;
      }
    }
    return false;
  }

  deleteEdge (id)
  {
    if ( id < this.n)
    {
      for (let i = 0; i < this.n; i++)
      {

        if (i == id)
        {
          continue;
        }

        if (this.adjacentMap[i] )
        {
          this.adjacentMap[i][id] = -1;
        }

        if (this.adjacentMap[id] )
        {
          this.adjacentMap[id][i] = -1;
        }


      }
    }
  }

  display()
  {
    for (let arr of this.adjacentMap)
    {
      console.log(arr)
    }
  }

}

{
  let graph = new AMGraph ();
  graph.addVertex();
  graph.addVertex();
  graph.addVertex();
  graph.removeVertex(1)
  graph.addVertex();
  // graph.addEdge(0, 1, 222);

  // graph.deleteEdge(1)
  // graph.display()
  // graph.addVertex(200);
  // graph.addVertex(2020);
  // graph.addEdge(0, 1, 223322)
  // graph.setVertexValue(0, 232);
  // console.log(graph.adjacent(0, 1))
  // graph.removeEdges(1);
  graph.display()

}