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
    std::cout <<  ele.first << " -> " << ele.second <<  " , " ;
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
    }
  }
}


int main()
{
  ELGraph graph;
  graph.addVertex(100);
  std::cout << graph.getVertexValue(0).first << '\n';
}
