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
    if (id1 < this.n && id2 < this.n)
    {
      this.adjacentMap [id1][id2]  = value;
      return true;
    }
    return false;
  }


  removeEdges (id)
  {
    for (let r = 0 ; r < this.n; r++)
    {
      for (let c = 0; c < this.n; c++)
      {
        if (this.adjacentMap[r][c] != null &&  (id == r || id == c ) )
        {
          this.adjacentMap[r][c] = -1;
        }
      }
    }
  }

  removeEdge (id1, id2)
  {
    if (id1 < this.n && id2 < this.n)
    {
      if (this.adjacentMap[id1][id2] != null )
      {
        this.adjacentMap[id1][id2]  = -1;
        return true;
      }
    }
    return false;
  }

  getEdgeValue (id1, id2)
  {
    if ( (id1 >=0 && id1 < this.n)  && (id2 >=0 && id2 < this.n) )
    {
      if (this.adjacentMap[id1][id2] != null)
      {
        return this.adjacentMap[id1][id2];
      }
    }
    return null;
  }

  setEdgeValue (id1, id2, edgeValue)
  {
    if ( (id1 >=0 && id1 < this.n)  && (id2 >=0 && id2 < this.n) )
    {
      if (this.adjacentMap[id1][id2] != null)
      {
       this.adjacentMap[id1][id2] = edgeValue;
       return true;
      }
    }
    return null;
  }

  adjacent (id1, id2)
  {
    if ( (id1 >=0 && id1 < this.n)  && (id2 >=0 && id2 < this.n) )
    {
      if (this.adjacentMap[id1][id2] > 0)
      {
        return true;
      }
    }
    return false;
  }

  neighbors (id)
  {
    let ids = [];

    if (id >=0 && id < this.n)
    {
      for (let i = 0; i < this.n ; i++)
      {
        if (this.adjacentMap[id][i] > 0)
        {
          ids.push(i)
        }
      }
    }
    return ids;
  }

  display()
  {
    for (let arr of this.adjacentMap)
    {
      console.log(arr)
    }
  }

}

class ALVertex
{
  constructor(value, id)
  {
    this.id = id;
    this.value = value;
    this.adjacent = [];
  }
}

class ALGraph
{
  constructor()
  {
    this.counter = 0;
    this.adjacentList = [];
  }

  display()
  {
    this.adjacentList.forEach((obj) => {
      console.log(obj);
    });
  }

  addVertex (value)
  {
    this.adjacentList.push( new ALVertex(value, this.counter));
    return this.counter++;
  }

  removeVertex (id)
  {
    for (let i = 0; i < this.adjacentList.length; i++)
    {
      if (this.adjacentList[i].id == id)
      {
        this.adjacentList.splice(i, 1);
        return true;
      }
    }
    return false;
  }

  getVertexValue(id)
  {
    for (let vertex of this.adjacentList)
    {
      if (vertex.id == id)
      {
        return vertex.value;
      }
    }
    return null;
  }

  setVertexValue (id, value)
  {
    for (let vertex of this.adjacentList)
    {
      if (vertex.id == id)
      {
        vertex.value = value;
        return true;
      }
    }
    return false;
  }

  addEdge(id1, id2, edge)
  {
    let vertex1 = this.adjacentList.find(  (ele) => ele.id == id1 );
    let vertex2 = this.adjacentList.find(  (ele) => ele.id == id2 );

    if (vertex1 && vertex2)
    {
      vertex1.adjacent.push( {id: id2, edge} );
      return true;
    }

    return false;
  }

  removeEdges (id)
  {
    for (let vertex of this.adjacentList)
    {
      if (vertex.id == id)
        //to edge (id-TX)
      {
        vertex.adjacent = [];
      }
      else
      {
        for (let i = 0; i < vertex.adjacent.length; i++)
        {
          if (vertex.adjacent[i].id == id)
            // from edges (id- RX)
          {
            vertex.adjacent.splice(i--, 1);
          }
        }
      }
    }
  }

  removeEdge (id1, id2)
  {
    let removed = false;

    for (let vertex of this.adjacentList)
    {
      if (vertex.id == id1)
      {
        for (let i = 0; i < vertex.adjacent.length; i++)
        {
          if ( vertex.adjacent[i].id == id2)
          {
            vertex.adjacent.splice(i--, 1);
            removed |= true;
          }
        }
      }
    }
    return removed;
  }

};


class SocialNetworkVertex
{
  constructor(id, name)
  {
    this.id = 0;
    this.name = name;
    this.friends = [];
  }
};

const someoneOnInside = function(vertex, srcID, employeeIDs = [])
{
  let stack = [];
  let visited = [];
  let currVertex = null;

  stack.push(vertex);

  while (stack.length)
  {

    currVertex = stack.pop();

    if ( visited.includes(currVertex.id) )
    {
      continue;
    }
    else
    {
      visited.push(currVertex.id);

      if (srcID == currVertex.id)
      {
        for (let srcFriend of currVertex.friends)
        {
          for (let employeeID of employeeIDs)
          {
            if (srcFriend.id == employeeID)
            {
              return true;
            }
          }
        }
        return false;
      }

      for (let friend of currVertex.friends)
      {
        stack.push(friend);
      }
    }

  }

  return false;
}

const someoneOnInsideNoReference = function (srcVertex)
{
  let stack = [] ;
  let popularMap = {};
  let insiderData = {contactID: null, insiderID: null};
  let vertex;
  let maxFriendCount = 0;

  stack.push(srcVertex);
  while (stack.length)
  {
    vertex = stack.pop();
    for (let friendVertex of vertex.friends)
    {
      popularMap[friendVertex.id] = !popularMap[friendVertex.id] && 1 || popularMap[friendVertex.id] + 1;
      if (insiderData.contactID == null || maxFriendCount <=  popularMap[friendVertex.id] )
      {
        maxFriendCount = popularMap[friendVertex.id];
        insiderData.contactID = vertex.id;
        insiderData.insiderID = friendVertex.id;
      }

      if (popularMap[friendVertex.id] == undefined)
      {
        stack.push(friendVertex);
      }

    }
  }
  return insiderData;
}

class GenericGraph
{
  constructor(id)
  {
    this.id = id;
    this.friends = [];
  }
};

const vertexIsReachable = function (srcVertex = new GenericGraph(), id1 = null, id2 = null, visited = {},  path = [], meta = {done: false, path: []})
{
  let stack = [];
  let vertex = null;

  stack.push(srcVertex);

  while (stack.length)
  {

    vertex = stack.pop();
    visited[vertex.id] = true;

    // path created
    if (vertex.id === id1 || path.length)
    {
      path.push(vertex.id);
      if (path[path.length - 1] == id2)
      {
        meta.path = path;
        meta.done = true;
      }
    }

    for (let friendVertex of vertex.friends)
    {
      if (visited[friendVertex.id] == undefined)
      {
        stack.push(friendVertex);
        vertexIsReachable(friendVertex, id1, id2, visited, path.slice(), meta);
      }
    }
  }
  return meta;
}

const allPaths = function (srcVertex = new GenericGraph(), srcID = null, destID = null, excludeID = {},  paths = [], currPath = [])
{
  let stack = [];
  let vertex;

  stack.push(srcVertex);

  while (stack.length)
  {
    vertex = stack.pop();
    excludeID.push(vertex.id);

    if (vertex.id === srcID || currPath.length)
    {
      currPath.push(vertex.id);
      if (currPath[currPath.length - 1] == destID)
      {
        paths.push(currPath);
      }
    }

    for (let friendVertex of vertex.friends)
    {
      if (excludeID[friendVertex.id] == undefined)
      {
        stack.push(friendVertex);
        allPaths(friendVertex, srcID, destID, paths, currPath.slice());
      }
    }
  }

  return paths;
}

const shortestPath = function (srcVertex = new GenericGraph(), srcID = null, destID = null, visited = {},  shortPath = [], currPath = [])
{
  let queue = [];
  let vertex;

  queue.push(srcVertex);

  while (queue.length)
  {
    vertex = queue.shift();
    visited[vertex.id] = true;

    if (srcID == vertex.id || currPath.length)
    {
      currPath.push(vertex.id);
      if (currPath[currPath.length - 1 ] == destID )
      {
        if (shortPath.length == 0 || currPath.length < shortPath.length)
        {
          // clear short path array
          while(shortPath.length) {shortPath.pop()};

          // mutate short path array
          for (let currPathElement of currPath)
          {
            shortPath.push(currPathElement);
          }
        }
      }
    }
    for (let friendVertex of vertex.friends)
    {
      if ( visited [ friendVertex.id ] == undefined )
      {
        queue.push(friendVertex);
        shortestPath(friendVertex, srcID, destID, visited, shortPath, currPath.slice());
      }
    }

  }

}

const gimmieThreeSteps = function(srcVertex = new GenericGraph(), srcID, visited = {}, ids = [], currPath = [])
{
  let queue = [];
  let vertex;

  if (currPath.length >= 4)
  {
    return;
  }

  queue.push(srcVertex);

  while (queue.length)
  {
    vertex = queue.shift();
    visited[vertex.id] = true;

    if (srcID == vertex.id || currPath.length)
    {
      currPath.push(vertex.id);
      ids.push(vertex.id);
    }

    for (let friendVertex of vertex.friends)
    {
      if (visited[friendVertex.id] == undefined)
      {
        queue.push(friendVertex);
        gimmieThreeSteps(friendVertex, srcID, visited, ids, currPath.slice());
      }
    }

  }
}

const easyToGetThere = function ( srcVertex = new GenericGraph() , data = {} , ids = [])
{
  let queue = [];
  let vertex;

  if (data[srcVertex.id])
  {
    data[srcVertex.id].in++ ;

    if (data[srcVertex.id].in - data[srcVertex.id].out == 1)   // easier to get to vertex
    {
      ids.push(srcVertex.id);
    }
    return;
  }

  queue.push(srcVertex);

  while (queue.length)
  {
    vertex = queue.shift();

    if (data[vertex.id] == undefined)
    {
      data[vertex.id] = { in: 0, out: vertex.friends.length} ;
    }
    for (let friendVertex of vertex.friends)
    {
      easyToGetThere(friendVertex, data, ids);
    }
  }

  return ids;
}

ALGraph.prototype.isDAG = function (srcVertex = null, visited = {}, path = [])
{
  let queue, head;
  let collection = (!srcVertex) ? this.adjacentList : [srcVertex] ;

  for (let vertex of collection)
  {
    queue = [];
    queue.push(vertex);

    while (queue.length)
    {
      head = queue[0];
      visited[head.id] = true;
      queue.shift();

      for (let currVertexFriends of head.friends)
      {
        if ( !visited[currVertexFriends.id] )
        {
          queue.push(currVertexFriends);
          this.isDAG( currVertexFriends , JSON.parse(JSON.stringify(visited)),  path.concat(currVertexFriends.id) );
        }
      }

    }
  }
}

{
  let graph = new ALGraph ();
  graph.addVertex('A');
  graph.addVertex('B');
  graph.addVertex('C');
  graph.removeVertex(1);
  graph.display()

  // console.log(graph.setVertexValue (1, '80') );
  // graph.addEdge(0, 1,131 );
  // graph.removeEdge(0, 1);
  // console.log(graph.neighbors(0))

  // console.log( graph.isDAG())
  // graph.deleteEdge(1)
  // graph.display()
  // graph.addVertex(200);
  // graph.addVertex(2020);
  // graph.addEdge(0, 1, 223322)
  // graph.setVertexValue(0, 232);
  // console.log(graph.adjacent(0, 1))
  // graph.removeEdges(1);
}