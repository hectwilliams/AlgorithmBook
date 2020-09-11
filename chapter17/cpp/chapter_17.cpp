#include "chapter_17.h"


std::ostream &operator << (std::ostream &stream, const ELGraph &graph)
{
  stream << " vertices [ ";
  for (auto ele: graph.vertexList)
  {
    std::cout <<  "value: " << ele->value << " id " << ele->id  << " , ";
  }
  stream << " ] \n";


    stream << " edges [ ";
  for (auto ele: graph.edgeList)
  {
    std::cout <<  ele->vert_id1 << " -> " << ele->vert_id2 <<  " , " ;
  }
  stream << " ] \n";

  return stream;
}

int ELGraph::addVertex(const int &value)
{
  vertexList.push_back( new ELVertex(value ,vertexList.size()) );
  return vertexList.size() - 1;
}

bool ELGraph::removeVertex(const int &id)
{
  int index = -1;
  ELVertex *vertex = NULL;

  for (int i = 0; i < vertexList.size() && index == -1; i++)
  {
    if (id == vertexList[i]->id)
    {
      index = vertexList[i]->id;
      vertexList.erase(vertexList.begin() + i);
    }
  }

  // TODO REEMOVE id in edge list array
  return index != -1;
}

std::pair<std::string, int> ELGraph::getVertexValue(const int &id)
{
  int result;

  for (ELVertex *vertex: vertexList)
  {
    if (vertex->id == id)
    {
      result = vertex->value;
      return std::make_pair( "valid", result);
    }
  }
  return std::make_pair( "error", NULL);
}

bool ELGraph::setVertexValue(int id, int value)
{
  for ( ELVertex *vertex: vertexList)
  {
    if (vertex->id == id)
    {
      vertex->value = value;
      return true;
    }
  }
  return false;
}

bool ELGraph::addEdge(int vert_id1, int vert_id2, int value)
{
  int count = 0;

  for ( ELVertex *vertex : vertexList)
  {
    count += (vertex->id == vert_id1 || vertex->id == vert_id2);
  }

  for (ELEdge *edge: edgeList )
  {
    if (edge->vert_id1 == vert_id1 && edge->vert_id2 == vert_id2 )
    {
      return false;
    }
  }
  if (count == 2)
  {
    edgeList.push_back(new ELEdge(vert_id1, vert_id2, 1) );
  }
}

void ELGraph::removeEdges(int id)
{
  int pos = 0;

  while (pos < edgeList.size())
  {
    if (edgeList[pos]->vert_id1 == id || edgeList[pos]->vert_id2 == id  )
    {
      free(edgeList[pos]);
      edgeList.erase(edgeList.begin() + pos);
    }
    else
    {
      pos++;
    }
  }
}

bool ELGraph::removeEdge(int id1, int id2)
{
  for (int i = 0; i < edgeList.size(); i++)
  {
    if (edgeList[i]->vert_id1 == id1 && edgeList[i]->vert_id2 == id2 )
    {
      free(edgeList[i]);
      edgeList.erase(edgeList.begin() + i);
      return true;
    }
  }
  return false;
}

  std::pair<std::string, int> ELGraph::getEdgeValue (const int &id1, const int &id2)
  {
    std::pair<std::string, int> result = std::make_pair("invalid", NULL );
    for (int i = 0; i < edgeList.size() && result.first == "invalid"; i++ )
    {
      if (edgeList[i]->vert_id1== id1 && edgeList[i]->vert_id2 == id2)
      {
        result.first = "valid";
        result.second = edgeList[i]->value;
      }
    }
    return result;
  }

  bool ELGraph::setEdgeValue (const int &id1, const int &id2, int value)
  {
    for (ELEdge *edge: edgeList )
    {
      if (edge->vert_id1 == id1 && edge->vert_id2 == id2)
      {
        edge->value = value;
        return true;
      }
    }
    return false;
  }

  bool ELGraph::adjacent (const int &id1, const int &id2)
  {
    for (ELEdge *edge: edgeList )
    {
      if (edge->vert_id1 == id1 && edge->vert_id2 == id2)
      {
        return true;
      }
    }

    return false;

  }

  std::vector<int> ELGraph::neighbors(const int &id)
  {
    std::vector<int> vertices;
    for (ELEdge *edge: edgeList )
    {
      if (id == edge->vert_id1)
      {
        vertices.push_back(edge->vert_id2);
      }
    }
    return vertices;
  }

std::ostream &operator << (std::ostream &stream, const AMGraph &graph)
{
  stream << " start " << '\n';
  for (std::vector<int> arr : graph.adjacentMap )
  {
    for (int element: arr)
    {
      stream << "[" << element << "]" << ',';
    }
   stream << '\n';
  }
    stream << " end " << '\n';

  return stream;
}

int AMGraph::addVertex()
{
  n++;
  for (int r = 0; r < n; r++)
  {
    for (int c = 0; c < n; c++)
    {
      adjacentMap.push_back(std::vector<int> ());
      if (adjacentMap[r].size() < n)
      {
        adjacentMap[r].push_back(-1);
      }

      if (r == c && adjacentMap[r][c] != -2)
      {
        adjacentMap[r][c] = 0;
      }

      if (r == n - 1 && r > 0)
      {
        if (adjacentMap[r - 1][c]  == -2)
        {
          adjacentMap[r ][c]  = -2;
        }
      }

      if (c == n - 1 && c > 0)
      {
        if (adjacentMap[r][c - 1]  == -2)
        {
          adjacentMap[r ][c - 1]  = -2;
        }
      }

     }
  }
}

bool AMGraph::removeVertex(const unsigned &id)
{
  bool removed = false;
 for (int r = 0; r < n; r++)
  {
    for (int c = 0; c < n; c++)
    {
      if ( adjacentMap[r][c] != -2  && (r == id || c == id) )
      {
        adjacentMap[r][c] = -2;
        removed |= true;
      }
    }
  }
    return removed;
}

bool AMGraph::addEdge (const unsigned &id1, const unsigned &id2, int value)
{
  if (id1 < n && id2 < n)
  {
    if (adjacentMap[id1][id2] != -2)
    {
      adjacentMap[id1][id2] = value;
    }
    return true;
  }
  return false;
}

void AMGraph::deleteEdges(const unsigned id)
{
  if (id < n)
  {
    for (int i = 0; i < n; i++ )
    {
      if (i == id)
      {
        continue;
      }

      if (adjacentMap[i][id] != -2)
      {
        adjacentMap[i][id] = -1;
      }

      if (adjacentMap[id][i] != -2)
      {
        adjacentMap[id][i] = -1;
      }
    }
  }
}

int main()
{
  AMGraph graph;
  graph.addVertex();
  graph.addVertex();
  graph.addVertex();

  graph.removeVertex(1);
  // graph.addEdge(0, 1, 21);

  // graph.deleteEdges(1);

  std::cout << graph << '\n';
  // graph.addVertex(100);
  // graph.addVertex(1001);
  // graph.addEdge(0,1);
  // std::cout << graph.getVertexValue(0).first << '\n';
  // // graph.removeEdges(1);

  // std::cout << graph << '\n';

}