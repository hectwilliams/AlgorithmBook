#include <vector>
#include <utility> //pair
#include <iostream>

class ELVertex
{
  public:
    int value;
    int id;
    ELVertex (const int &value, const int &id)
    {
      this->value = value;
      this->id = id;
    }
};

class ELEdge
{
  public:
    int vert_id1;
    int vert_id2;
    int value;
    ELEdge(int id1, int id2, int val)
    {
      vert_id1 = id1;
      vert_id2 = id2;
      value = val;
    }
};


class ELGraph
{
  public:
    std::vector< ELVertex *> vertexList;
    std::vector< ELEdge*> edgeList;

    int addVertex(const int &value);
    bool removeVertex(const int &id);
    std::pair<std::string, int> getVertexValue(const int &id);
    bool setVertexValue(int id, int value);
    bool addEdge(int vert_id1, int vert_id2, int value = 0);
    void removeEdges( int id);
    bool removeEdge(int id1, int id2);
    std::pair<std::string, int> getEdgeValue (const int &id1, const int &id2);
    bool setEdgeValue (const int &id1, const int &id2, int value);
    bool adjacent (const int &id1, const int &id2);
    std::vector<int> neighbors(const int &id);
};

std::ostream &operator << (std::ostream &stream, const ELGraph &graph);


class AMGraph
{
  public:
    std::vector< std::vector<int> > adjacentMap;
    int n;

  AMGraph()
  {
    n = 0;
  }
  int addVertex();
};

std::ostream &operator << (std::ostream &stream, const AMGraph &graph);
