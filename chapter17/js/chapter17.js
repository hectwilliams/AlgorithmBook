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

  getEdgeValue (id1, id2)
  {
    for (let vertex1 of this.adjacentList)
    {
      if (vertex1.id == id1)
      {
        for (let adj of this.adjacent )
        {
          if (adj.id == id2)
          {
            return adj.edge;
          }
        }
      }
    }

    return false;
  }

  setEdgeValue (id1, id2, value)
  {
    for (let v1 of this.adjacentList)
    {
      if (v1.id == id1)
      {
        for (let adj of v1.adjacent)
        {
          if (adj.id)
          {
            return adj.edge;
            return true;
          }
        }
      }
    }
    return false;
  }

  adjacent(id1, id2)
  {
    for (let v1 of this.adjacentList)
    {
      if (v1.id == id1)
      {
        for (let adj of v1.adjacent)
        {
          if (adj.id == id2)
          {
            return true;
          }
        }
      }
    }
    return false;
  }

  neighbors (id)
  {
    let res = [];

    for (let vertex of this.adjacentList)
    {

      for (let adj of v.adjacent)
      {
        if (vertex.id == id)  // FROM
        {
          res.push(adj[0]);
        }
        else if (adj[0] == id)  // TO
        {
          res.push(vertex.id);
        }
      }
    }
  }
};


class SocialNetworkVertex
{
  constructor(id, name)
  {
    this.id = id;
    this.name = name;
    this.friends = [];
  }
};

class Graph  // undirected
{
  constructor()
  {
    this.vertexList = [];
  }
};

const someoneOnInside = function(UndirGraph = new Graph(), srcID, employeeIDs = [])
{
  let stack = [];
  let visited = {};
  let currVertex = null;

  for (let vertex of UndirGraph.vertexList)
  {
    stack.push(vertex);

    while (stack.length)
    {
      currVertex = stack.pop();
      visited[currVertex.id] = true;
      for (let friendVertex of currVertex.friends)
      {
        if (friendVertex.id == srcID)
        {
          if (employeeIDs.findIndex( (employee) => employee == currVertex.id ) != -1)
          {
            return true;
          }
        }

        if (visited[friendVertex.id]  == undefined)
        {
          stack.push(friendVertex);
        }
      }
    }
  }
  return false;
}

const someoneOnInsideNoReference = function (UndirGraph = new Graph())
{
  let stack = [];
  let visited = {};
  let currVertex = null;
  let data = {maxFollower: 0, contact: '', id: ''};
  let table =  {}

  for (let vertex of UndirGraph.vertexList)
  {
    stack.push(vertex);

    while (stack.length)
    {
      currVertex = stack.pop();

      for (let friendVertex of currVertex.friends)
      {
        if (table[friendVertex.id]  == undefined)
        {
          stack.push(friendVertex);
          table[friendVertex.id] = {contact: currVertex.id, id: friendVertex.id, followers: 1};
        }
        else
        {
          table[friendVertex.id].followers++;
        }
        if (data.maxFollower < table[friendVertex.id].followers )
        {
          data.maxFollower = table[friendVertex.id].followers;
          data.id = friendVertex.id;
          data.contact = currVertex.id;
        }
      }
    }
  }
  return data;
}

class GenericGraph
{
  constructor(id)
  {
    this.id = id;
    this.friends = [];
  }
};

const vertex_Is_Reachable = function (dirGraph = new Graph(), id1, id2)
{
  let stack = [];
  let obj = null;
  let visited = {};
  let path = [];

  for (let vertex of dirGraph.vertexList)
  {
    if (vertex.id == id1)
    {
      stack.push( {curr: vertex, prev: undefined} );
      path = [id];

      while ( stack.length )
      {
        obj = stack.pop();
        visited [currVertex.curr.id] = true; // visited marker

        if (obj.prev == vertex)  //search returned back to source node
        {
          path = [id];
        }

        path.push(obj.curr.id);    // add step to path

        if (path[path.length - 1] == id2)   // path complete
        {
          return path;
        }

        for (let friendVertex of obj.curr.friends)
        {
          if (!visited[friendVertex.id])
          {
            stack.push( {curr: friendVertex, prev: obj.curr} );
          }
        }
      }
    }
  }
  return [];
}

const allPaths = function (dirGraph = new Graph(), id1, id2)
{
  let stack = [];
  let obj = null;
  let visited = {};
  let path = [], paths =  [];

  for (let vertex of dirGraph.vertexList)
  {
    if (vertex.id == id1)
    {
      stack.push( {curr: vertex, prev: undefined} );
      path = [id];

      while ( stack.length )
      {
        obj = stack.pop();
        visited [currVertex.curr.id] = true; // visited marker

        if (obj.prev == vertex)  //search returned back to source node
        {
          path = [id];
        }

        path.push(obj.curr.id);    // add step to path

        if (path[path.length - 1] == id2)   // path complete
        {
          paths.push(  path ) ;
        }

        for (let friendVertex of obj.curr.friends)
        {
          if (!visited[friendVertex.id])
          {
            stack.push( {curr: friendVertex, prev: obj.curr} );
          }
        }
      }
    }
  }
  return paths;
}

const shortestPath = function (dirGraph = new Graph(), id1, id2)
{
  let queue = [];
  let table = {};
  let path = [];
  let currVertex;


  for (let vertex of dirGraph.vertexList)
  {
    if (vertex.id == id1)
    {
      table [vertex.id] = null;
      queue.push(vertex);

      while ( queue.length  && !table[id2] )
      {
        currVertex = queue.shift();

        for (let friendVertex of currVertex.friends)
        {
          if (!table[friendVertex.id])
          {
            table [friendVertex.id] = currVertex.id;
            queue.push(friendVertex);
          }
        }
      }

      // compute path (via back propagation)
      {
        let currID = id2;
        while ( currID != null)
        {
          path.unshift( currID );
          currID = table[currID];
        }
      }
    }
  }
  return path;
}

const gimmieThreeSteps = function ( dirGraph = new Graph(), id1, id2 )
{
  let queue = [];
  let visited = {};
  let ids = [];
  let currVertex;
  let MAXSTEP = 3;

  for (let vertex of dirGraph.vertexList)
  {
    if (vertex.id == id1)
    {
      visited [vertex.id] = 0;
      queue.push(vertex);
      while (queue.length)
      {
        currVertex = queue.shift();
        for (let friendVertex of currVertex.friends)
        {
          if ( visited[friendVertex.id] == undefined)
          {
            visited[friendVertex.id] =  visited[currVertex.id] + 1
            if (visited[friendVertex.id]  <= MAXSTEP)
            {
              ids.push(friendVertex.id);
              queue.push(friendVertex);
            }
          }
        }
      }
    }
  }
  return ids;
}

const easyToGetThere = function ( dirGraph = new Graph() )
{
  let queue = [];
  let table = {};
  let ids = [];
  let vertex;

  for (let i = 0; i < dirGraph.vertexList.length; i++)
  {
    queue.push(dirGraph.vertexList[i]);

    while (queue.length)
    {
      vertex = queue.shift();

      if (!table[vertex.id])
      {
        table[vertex.id] = {in: 0, out: 0 };
      }

      for (let friendVertex of vertex.friends)
      {
        if (!table[friendVertex.id])
        {
          queue.push(friendVertex);
          table[friendVertex.id] = {in: 0, out: 0 };
        }
        table[vertex.id].out++;
        table[friendVertex.id].in++;
      }
    }
  }

  for (let key in table )
  {
    if (table[key].in > table[key].out)
    {
      ids.push(parseInt(key));
    }
  }

  return ids;
}

ALGraph.prototype.isDAG = function (dirGraph = new ALGraph(), array)
{
  let queue;
  let visited;
  let foundTail;
  let vertex;
  let valid_graph;

  for (let i = 0; i < dirGraph.vertexList.length; i++)
  {
    queue = []
    visited = {};
    foundTail = false;
    valid_graph = true;
    queue.push (dirGraph.vertexList[i]);
    array.splice(0, array.length);

    while (queue.length && valid_graph)
    {
      vertex = queue.shift();
      valid_graph &= (vertex.friends.length <= 1) && (foundTail == false );
      foundTail = (vertex.friends.length == 0);
      visited[vertex.id] = true;
      array.push(vertex.id);

      for (let friendVertex of vertex.friends)
      {
        if (!visited[friendVertex.id])
        {
          queue.push(friendVertex);
        }
        else
        {
          valid = false;
        }
      }
    }

    if (valid_graph == true)
    {
      return true;
    }
  }
  return false;
}


ALGraph.prototype.arrayDAG = function (dirGraph = new ALGraph())
{
  let array = [];
  this.isDAG(dirGraph, array);
  return array;
}

let json = require('./dict.json');

const wordLadder = function (wordA = '', wordB = '', path = [], visited = {}, paths = [])
{
  let newStr;

  if (visited[wordA] === undefined)
  {
    path.push(wordA);
  }
  visited[wordA] = true;

  if (path.slice(-1) == wordB)
  {
    paths.push(path.slice());
  }

  for (let i = 97; i <= 122; i++)
  {
    for (let j = 0; j < wordA.length; j++)
    {
      newStr = wordA.slice(0,j) + String.fromCharCode(i) + wordA.slice(j+1); // change one letter

      if (json.words.includes(newStr) && !visited[newStr] )  // new word
      {
        visited[newStr] = true;
        wordLadder(newStr, wordB, path.concat(newStr).slice(), JSON.parse(JSON.stringify(visited)) , paths);
        visited[newStr] = false;
      }
    }
  }
  return paths;
}

{
  console.log(wordLadder('top', 'hip'));
}


// cat -> cut -> cap

// cat -> ... -> cap

// cat -> cap -> cop