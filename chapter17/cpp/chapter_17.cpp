#include <algorithm>    // std::find
#include <map>
#include <set>
#include <iostream>
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

void AMGraph::removeEdges(const unsigned id)
{
  for (int r = 0 ; r < n; r++)
  {
    for (int c = 0; c < n; c++)
    {
      if (adjacentMap[r][c] != -2 &&  (id == r || id == c) )
      {
        adjacentMap[r][c] = -1;
      }
    }
  }
}

bool AMGraph::removeEdge (const unsigned id1, const unsigned id2)
{
  if (id1 < n && id2 < n )
  {
    if (adjacentMap[id1][id2] != -2 )
    {
      adjacentMap[id1][id2] = -1;
      return true;
    }
  }
  return false;
}

std::pair<std::string, int> AMGraph::getEdgeValue (const unsigned id1, const unsigned id2)
{
  std::pair<std::string, int> result;
    if (id1 < n && id2 < n )
    {
      if (adjacentMap[id1][id2] != -2)
      {
        return std::make_pair("valid", adjacentMap[id1][id2]);
      }
    }
    return std::make_pair("error", NULL);
}


bool AMGraph::setEdgeValue (const unsigned id1, const unsigned id2, const int edgValue)
{
  if (id1 < n && id2 < n  && id1 >= 0 && id2 >= 0)
  {
    if (adjacentMap[id1][id2] != -2)
    {
      adjacentMap[id1][id2] = edgValue;
      return true;
    }
  }
  return false;
}

bool AMGraph::adjacent(const unsigned id1, const unsigned id2)
{
  if (id1 < n && id2 < n  && id1 >= 0 && id2 >= 0)
  {
    if (adjacentMap[id1][id2] > 0)
    {
      return true;
    }
  }
  return false;
}


std::vector<int> AMGraph::neighbors (const unsigned id)
{
  std::vector<int> array;

  if (id < n && id >= 0 )
  {
    for (int i = 0; i < n; i++ )
    {
      if (adjacentMap[id][i] > 0)
      {
        array.push_back(i);
      }
    }
  }
  return array;
}

std::ostream &operator << (std::ostream &stream, const ALGraph &graph)
{
  std::string mes;
  for (ALVertex *vertex : graph.adjacentList)
  {
    mes += "Vertex: " + vertex->value + " " +  std::to_string(vertex->vertex_id) + " |";
    for (int i =0; i < vertex->adjacent.size() ; i++)
    {
      mes += "[" + std::to_string(vertex->adjacent[i].first ) + "-" + std::to_string(vertex->adjacent[i].second) +  "] ";
    }
    mes+= "\n";
  }
  stream << mes;
  return stream;
}

int ALGraph::addVertex(std::string value)
{
  ALVertex *vertex = new ALVertex(value, id_counter);
  adjacentList.push_back(vertex);
  return id_counter++;
}

bool ALGraph::removeVertex (int vertexID)
{
  int pos = 0;

  for (ALVertex * vertex: this->adjacentList)
  {
    if (vertex->vertex_id == vertexID)
    {
      this->adjacentList.erase(this->adjacentList.begin() + pos) ;
      return true;
    }
    pos++;
  }
  return false;
}


std::pair<std::string, std::string> ALGraph::getVertexValue(int vertexID)
{
  std::pair<std::string, std::string> res = std::make_pair("error", "");
  for (ALVertex *vertex : this->adjacentList)
  {
    if (vertex->vertex_id == vertexID)
    {
      res.first = "valid";
      res.second = vertex->value;
    }
  }
  return res;
}


bool ALGraph::setVertexValue (int vertexID, std::string value)
{
  for (ALVertex *vertex: this->adjacentList)
  {
    if (vertex->vertex_id == vertexID)
    {
      vertex->value = value;
      return true;
    }
  }
  return false;
}

bool ALGraph::addEdge (int id1, int id2, int edge)
{
  ALVertex *v1 = NULL, *v2 = NULL;

   for (ALVertex *vertex: this->adjacentList)
  {
    if (vertex->vertex_id == id1)
    {
      v1 = vertex;
    }

    if (vertex->vertex_id == id2)
    {
      v2 = vertex;
    }

    if (v1 && v2)
    {
      v1->adjacent.push_back(std::make_pair( id2, edge ));
      return true;
    }

  }
  return false;
}

void ALGraph::removeEdges(int id)
{
  ALVertex *vertex;
  for (int i = 0; i < this->adjacentList.size(); i++)
  {
    if (this->adjacentList[i]->vertex_id == id)
    {
      this->adjacentList[i]->adjacent.clear();
    }
    else
    {
      for (int k = 0; k < this->adjacentList[i]->adjacent.size(); k++)
      {
        if (this->adjacentList[i]->adjacent[k].first == id )
        {
          this->adjacentList[i]->adjacent.erase( this->adjacentList[i]->adjacent.begin() + k--);
        }
      }
    }
  }
}

std::pair<std::string, int> ALGraph::getEdgeValue(int id1, int id2)
{
  ALVertex *vertex;
  std::pair<std::string, int> res = std::make_pair("error", NULL);

  for (int i = 0; i < this->adjacentList.size(); i++)
  {
    vertex = this->adjacentList[i];
    if (vertex->vertex_id == id1)
    {
      for (int k = 0; k < vertex->adjacent.size(); k++)
      {
        if (vertex->adjacent[k].first == id2)
        {
          res.first = "true";
          res.second  = vertex->adjacent[k].second;
        }
      }
    }
  }
  return res;
}

bool ALGraph::setEdgeValue(int id1, int id2, int edgeValue)
{
  ALVertex *vertex;

  for (int i = 0; i < this->adjacentList.size(); i++)
  {
    vertex = this->adjacentList[i];
    if (vertex->vertex_id == id1)
    {
      for (int k = 0; k < vertex->adjacent.size(); k++)
      {
        if (vertex->adjacent[k].first == id2)
        {
          vertex->adjacent[k].second = edgeValue;
          return true;
        }
      }
    }
  }
  return false;
}

bool ALGraph::adjacent(int id1, int id2)
{
  ALVertex *vertex;
  int currID;

  for (int i = 0; i < this->adjacentList.size(); i++)
  {
    vertex = this->adjacentList[i];
    if (vertex->vertex_id == id1 || vertex->vertex_id == id2)
    {
      currID = vertex->vertex_id;
      for (int k = 0; k < vertex->adjacent.size(); k++)
      {
        if ( (currID == id1 && vertex->adjacent[k].second == id2) || (currID == id2 && vertex->adjacent[k].second == id1) )
        {
          return true;
        }
      }
    }
  }
  return false;
}

std::vector<int> ALGraph::neighbors(int id)
{
  ALVertex *vertex;
  std::vector<int> res;

  for (int i = 0; i < this->adjacentList.size(); i++)
  {
    vertex = this->adjacentList[i];
    if (vertex->vertex_id == id)
    { // FROM
      for (int k = 0; k < vertex->adjacent.size(); k++)
      {
        res.push_back(vertex->adjacent[k].first);
      }
    }
    else
    {
      for (int k = 0; k < vertex->adjacent.size(); k++)
      {
        if ( vertex->adjacent[k].first == id )
        {
          res.push_back(vertex->vertex_id);
        }
      }
    }
  }
  return res;
}

bool ALGraph::removeEgde(int id1, int id2)
{
  ALVertex *vertex;
  int index = 0;
  bool removed = false;

  for (int i = 0; i < this->adjacentList.size(); i++)
  {
    vertex = this->adjacentList[i];

    if (vertex->vertex_id == id1)
    {
      for (int k = 0; k < vertex->adjacent.size(); k++)
      {
        if ( vertex->adjacent[k].first == id2 )
        {
          vertex->adjacent.erase(vertex->adjacent.begin() + k-- );
          removed |= true;
        }
      }
    }
  }
  return removed;
}


bool someoneOnInside (GraphNetwork *graph, const int srcID, std::vector<int> companyIDs)
{
  std::vector<SocialNetworkVertex*> stack;
  SocialNetworkVertex *currVertex;
  std::set<int> visited;

  if (!graph)
  {
    return false;
  }

  for (SocialNetworkVertex *srcVertex : graph->vertex_list)
  {
    stack.push_back(srcVertex);
    while (stack.size())
    {
      currVertex = stack.back();
      stack.pop_back();
      visited.insert(currVertex->id);

      for (SocialNetworkVertex *friendVertex: currVertex->friends)
      {
        if (friendVertex->id == srcID)
        {
          for (const int &id: companyIDs )
          {
            if (id == currVertex->id)
            {
              return true;
            }
          }
        }
        if (visited.count(friendVertex->id) == 0)
        {
          stack.push_back(friendVertex);
        }
      }
    }
  }
  return false;
}

std::pair<int, int> someoneOnInside (GraphNetwork *graph)
{
  int maxCount = 0;
  std::set<int> visited;
  std::vector<SocialNetworkVertex *> stack;
  SocialNetworkVertex *currVertex, *vertex;
  std::pair<int, int> insider = std::make_pair(-1, -1);  // [vertex ID Contact] [vertex ID Insider]
  std::map <int, std::pair<int, int> > table;

  for  ( int i = 0; i < graph->vertex_list.size(); i++)
  {
    vertex = graph->vertex_list [i];
    stack.push_back(vertex);

    while (stack.size())
    {
      currVertex = stack.back();
      stack.pop_back();

      for (SocialNetworkVertex * friendVertex: currVertex->friends)
      {
        if (table.count(friendVertex->id) == 0)
        {
          stack.push_back(friendVertex);
          table.insert( std::make_pair(friendVertex->id, std::make_pair(currVertex->id, 1) ) );
        }
        else
        {
          table.at(friendVertex->id ).second += 1;

        }

        if (maxCount < table.at(friendVertex->id ).second )
        {
          maxCount = table.at(friendVertex->id ).second ;
          insider = std::make_pair(currVertex->id, friendVertex.->id);
        }
      }
    }
  }
  return insider;
}

std::vector<int> vertexIsReachable (GraphNetwork *graph, int id1, int id2 )
{
  std::vector<SocialNetworkVertex *> stack;
  SocialNetworkVertex *currVertex, *vertex;
  std::vector<int> path;
  std::map<int, int> table;
  int currID;

  for(int i = 0; i < graph->vertex_list.size(); i++)
  {
    vertex = graph->vertex_list[i]; // found start of path
    if (vertex-> id == id1)
    {
      stack.push_back(vertex)
      while (stack.size() && table.count(id2) == 0 )
      {
        currVertex = stack.back();
        stack.pop_back();

        for (SocialNetworkVertex *friendVertex: currVertex->friends  )
        {
          if (table.count(friendVertex.id) == 0)
          {
            table.insert(std::make_pair(friendVertex.id, currVertex.id));
          }
        }
      }

      currID = id2;
      while (table.count(currID))
      {
        path.push_back(currID);
        currID = table.at(currID);
      }

      if (path.size())
      {
        path.push_back(id1);
      }

    }
    break;
  }

  return path;
}

void allPaths (GenericGraph *graph, int id1, int id2 , std::set<int> &excludeID ,std::vector<std::vector<int> > &paths , std::vector<int> currPath )
{
  std::vector <GenericGraph * > stack;
  GenericGraph *vertex;

  stack.push_back(graph);

  while (!stack.empty())
  {
    vertex = stack.back();
    stack.pop_back();
    excludeID.insert(vertex->id);

    if (vertex->id == id1 || currPath.size())
    {
      currPath.push_back(vertex->id);

      if (currPath[currPath.size() - 1] == id2)
      {
        paths.push_back(std::vector<int>(currPath.begin(), currPath.end()) );
      }
    }

    for (GenericGraph *friendVertex: vertex->frieends )
    {
      if (excludeID.count(friendVertex->id) == 0)
      {
        stack.push_back(friendVertex);
        allPaths(friendVertex, id1 , id2, excludeID, paths, std::vector<int>(currPath.begin(), currPath.end()) );
      }
    }
  }

}

void shortestPath (GenericGraph *graph, int id1, int id2 ,  std::set<int> &excludeID, std::vector < int >  &path , std::vector <int> currPath )
{
  std::vector <GenericGraph * > queue;
  GenericGraph *vertex;

  queue.push_back(graph);

  while (queue.size())
  {
    vertex = queue[0];
    queue.erase(queue.begin());

    if (id1 == vertex->id || currPath.size())
    {
      currPath.push_back(vertex->id);
      if (currPath[currPath.size() - 1] == id2)
      {
        path.clear();
        for (int &ele: currPath)
        {
          path.push_back(ele);
        }
      }
    }

    for (GenericGraph *friendVertex : vertex->frieends)
    {
      if ( excludeID.count(friendVertex->id) == 0 )
      {
        queue.push_back(friendVertex);
        shortestPath (friendVertex, id1, id2, excludeID, path, std::vector<int>(currPath.begin(), currPath.end()) );
      }
    }

  }
}

void gimmieThreeSteps (GenericGraph *graph, const int id, std::set<int> &excludeID, std::vector<int> &ids, std::vector<int> path)
{
  GenericGraph *vertex;
  std::vector <GenericGraph *> queue;

  if (path.size() >4)
  {
    return;
  }

  queue.push_back(graph);
  while (!queue.empty())
  {
    vertex = queue[0];
    queue.erase(queue.begin());
    if (id == vertex->id || path.size())
    {
      path.push_back(vertex->id);
      ids.push_back(vertex->id);
    }
    for (GenericGraph *friendVertex: vertex->frieends)
    {
      if (excludeID.count(vertex->id) == 0)
      {
        queue.push_back(friendVertex);
        gimmieThreeSteps( graph, id, excludeID, ids, std::vector<int>(path.begin(), path.end()) );
      }
    }
  }
}

void easyToGetThere(GenericGraph *graph,  std::vector<int> &ids, std::map<int, std::pair<int, int> > data )
{
  GenericGraph *vertex;
  std::vector <GenericGraph *> queue;

  if (data.size())
  {
    if (data.count(graph->id))
    {
      data.at(graph->id).first++;
      if (data.at(graph->id).first  - data.at(graph->id).second )  // easier to get to vertex
      {
        ids.push_back(graph->id);
        return;
      }
    }
  }

  queue.push_back(graph);

  while (!queue.empty())
  {
    vertex = queue[0];
    queue.erase(queue.begin());
    if (data.count(vertex->id) == 0)
    {
      data.insert(std::make_pair(vertex->id, std::make_pair(0, vertex->frieends.size())));
    }
    for (GenericGraph *friendVertex: graph->frieends)
    {
      easyToGetThere(friendVertex, ids, data);
    }
  }

}

int main()
{
  ALGraph graph;
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  // graph.addEdge(0,1,200);
  // std::cout << graph.neighbors(0).size() << '\n';
  graph.removeVertex(1);
  // graph.removeVertex(1);
  // graph.addEdge(0, 1, 21);
  // graph.deleteEdges(1);
  // graph.addVertex(100);
  // graph.addVertex(1001);
  // graph.addEdge(0,1);
  // std::cout << graph.getVertexValue(0).first << '\n';
  // // graph.removeEdges(1);
  std::cout << graph << '\n';
}
