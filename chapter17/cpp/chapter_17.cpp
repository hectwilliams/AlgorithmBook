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
          insider = std::make_pair(currVertex->id, friendVertex->id);
        }
      }
    }
  }
  return insider;
}

std::vector<int> vertexIsReachable (GraphNetwork *graph, int id1, int id2)
{
  std::vector < std::pair<SocialNetworkVertex*, SocialNetworkVertex * > > stack;
  SocialNetworkVertex *currVertex, *vertex;
  std::vector<int> path;
  std::set<int> visited;
  std::pair <SocialNetworkVertex*, SocialNetworkVertex* > obj ;

  for(int i = 0; i < graph->vertex_list.size(); i++)
  {
    vertex = graph->vertex_list[i];

    if (vertex->id == id1)
    {
      stack.push_back( std::make_pair(vertex, nullptr) );
      path.push_back(id1);

      while(stack.size())
      {
        obj = stack.back();
        stack.pop_back();
        visited.insert(obj.first->id);

        if (obj.second == vertex)
        {
          path.clear();
          path.push_back(id1);
        }

        path.push_back(obj.first->id);

        if (path.back() == id2)
        {
          return path;
        }

        for (SocialNetworkVertex *friendVertex: obj.first->friends)
        {
          if (visited.count(friendVertex->id) == 0)
          {
            stack.push_back(std::make_pair(friendVertex, obj.first) );
          }
        }
      }

    }
  }

  return std::vector<int> ();
}

std::vector<std::vector<int> > allPaths (GraphNetwork *graph, int id1, int id2  )
{
  std::vector < std::pair<SocialNetworkVertex*, SocialNetworkVertex * > > stack;
  SocialNetworkVertex *currVertex, *vertex;
  std::vector<int> path;
  std::set<int> visited;
  std::pair <SocialNetworkVertex*, SocialNetworkVertex* > obj ;
  std::vector<std::vector<int> > paths;

  for(int i = 0; i < graph->vertex_list.size(); i++)
  {
    vertex = graph->vertex_list[i];

    if (vertex->id == id1)
    {
      stack.push_back( std::make_pair(vertex, nullptr) );
      path.push_back(id1);

      while(stack.size())
      {
        obj = stack.back();
        stack.pop_back();
        visited.insert(obj.first->id);

        if (obj.second == vertex)
        {
          path.clear();
          path.push_back(id1);
        }

        path.push_back(obj.first->id);

        if (path.back() == id2)
        {
          paths.push_back(path);
        }

        for (SocialNetworkVertex *friendVertex: obj.first->friends)
        {
          if (visited.count(friendVertex->id) == 0)
          {
            stack.push_back(std::make_pair(friendVertex, obj.first) );
          }
        }
      }

    }
  }
  return paths;
}

std::vector<int> shortestPath (GraphNetwork *graph, int id1, int id2 )
{
  std::vector<int> path;
  SocialNetworkVertex *vertex;
  std::map< int, int > table;
  std::vector <SocialNetworkVertex *> queue;

  for(int i = 0; i < graph->vertex_list.size(); i++)
  {
    if (graph->vertex_list[i]->id == id1)
    {
      queue.push_back(graph->vertex_list[i]);

      while (!queue.empty())
      {
        vertex = queue.front();
        queue.erase(queue.begin());

        for (SocialNetworkVertex *friendVertex: vertex->friends)
        {
          if (table.count(friendVertex->id) == 0 )
          {
            queue.push_back(friendVertex);
            table.insert(std::make_pair(friendVertex->id, vertex->id));
          }
        }
      }

      // compute path
      {
        int currID = id2;
        while (table.count(currID))
        {
          path.push_back(currID);
          currID = table.at(currID);
        }

        if (!path.empty())
        {
          path.push_back(id1);
        }
      }
    }
  }
  return path;
}

std::vector<int> gimmieThreeSteps (GraphNetwork *graph, const int id)
{
  std::vector< SocialNetworkVertex * > queue;
  std::map <int, int> table;
  std::vector<int> ids;
  const int MAXSTEP = 3;
  SocialNetworkVertex *vertex;

  for (int i = 0; i < graph->vertex_list.size(); i++)
  {
    if (graph->vertex_list[i]->id == id )
    {
      queue.push_back(graph->vertex_list[i]);
      table.insert(std::make_pair(id, 0));

      while (!queue.empty())
      {
        vertex = queue.front();
        queue.erase(queue.begin());
        for (SocialNetworkVertex * friendVertex: vertex->friends )
        {
          if (table.count(friendVertex->id) == 0)
          {

            table.insert(std::make_pair(friendVertex->id, table.at(vertex->id) + 1 ));
            if (table.at(friendVertex->id) <= MAXSTEP)
            {
              ids.push_back(friendVertex->id);
              queue.push_back(friendVertex);

            }
          }
        }
      }
    }
  }
  return ids;
}

std::vector<int>  easyToGetThere(GraphNetwork *graph )
{
  std::vector< SocialNetworkVertex * > queue;
  std::map <int, std::pair<int,int> > table;
  std::vector<int> ids;
  SocialNetworkVertex *vertex;

  for (int i = 0; i < graph->vertex_list.size(); i++)
  {
    queue.push_back(graph->vertex_list[i]);
    while (!queue.empty())
    {
      vertex =  queue.front();
      queue.erase(queue.begin());

      if (table.count(vertex->id) == 0)
      {
        table.insert(std::make_pair(vertex->id, std::make_pair(0,0)));
      }

      for (SocialNetworkVertex * friendVertex: vertex->friends)
      {
        if (table.count(friendVertex->id) == 0)
        {
          queue.push_back(friendVertex);
          table.insert(std::make_pair(friendVertex->id, std::make_pair(0,0)));
        }
        table.at(friendVertex->id).first++; // in
        table.at(vertex->id).second++; // out

      }
    }
  }

  for(std::map <int, std::pair<int,int> > ::const_iterator it = table.begin(); it != table.end(); it++)
  {
    if (it->second.first > it->second.second)
    {
      ids.push_back(it->first);
    }
  }
  return ids;
}

bool GraphNetwork::isDAG(std::vector<int> *array)
{
  std::vector< SocialNetworkVertex * > queue;
  std::set <int> visited;
  SocialNetworkVertex *vertex;
  bool isvalid;
  bool foundTail;

  for (int i = 0; i < vertex_list.size(); i++)
  {
    queue.clear();
    visited.clear();
    foundTail = false;
    isvalid = true;
    queue.push_back(vertex_list[i]);

    if (array)
    {
      array->clear();
    }

    while (!queue.empty() && isvalid)
    {
      vertex = queue.front();
      queue.erase(queue.begin());
      isvalid &= vertex->friends.size() <= 1 && foundTail == false;
      foundTail = vertex->friends.empty();
      visited.insert(vertex->id);

      if (array)
      {
        array->push_back(vertex->id);
      }

      for (SocialNetworkVertex *friendVertex: vertex->friends)
      {
        if (visited.count(friendVertex->id) == 0)
        {
          queue.push_back(friendVertex);
        }
        else
        {
          isvalid = false;
        }
      }
    }

    if (isvalid)
    {
      return true;
    }
  }

  return false;

}

std::vector<int> GraphNetwork::DAGArray ()
{
  std::vector<int> arr;
  isDAG(&arr);
}

void wordLadder(std::string wordA, std::string wordB, std::vector<std::string> path, std::set<std::string> visited)
{
  std::string newString;

  if (visited.count(wordA) == 0)
  {
    path.push_back(wordA);
  }
  visited.insert(wordA);

  if (path.back() == wordB)
  {
    std::cout << path;
  }

  for (int i = 97; i <= 122; i++)
  {
    for (int j = 0; j < wordA.size(); j++)
    {
      newString = wordA.substr(0, j) + char(i) + wordA.substr(j + 1);
      if ( visited.count(newString) == 0 && std::find(Dictionary::words.begin(), Dictionary::words.end(), newString) !=  Dictionary::words.end() )
      {
        visited.insert(newString);
        path.push_back(newString);
        wordLadder(newString, wordB, std::vector<std::string>(path.begin(), path.end())  , std::set<std::string> (visited.begin(), visited.end()) );
        path.pop_back();
        visited.erase(newString);
      }
    }
  }
}

std::ostream &operator << (std::ostream &stream, const std::vector<std::string> collection)
{
  stream << "[";
  for (const std::string &element: collection)
  {
    stream << element + ", ";
  }
  stream << "]\n";
  return stream;
}

int main()
{
  wordLadder("top", "hip");
}
