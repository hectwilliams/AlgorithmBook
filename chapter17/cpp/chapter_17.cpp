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



int main()
{
  ELGraph graph;
  graph.addVertex(100);
  graph.addVertex(1001);
  graph.addEdge(0,1);
  std::cout << graph.getVertexValue(0).first << '\n';
  std::cout << graph << '\n';

}
