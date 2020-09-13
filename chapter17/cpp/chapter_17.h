#include <vector>
#include <utility> //pair
#include <iostream>
#include <string>     // std::string, std::to_string

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
  bool removeVertex(const unsigned &id);
  bool addEdge (const unsigned &id1, const unsigned &id2, int value);
  void removeEdges(const unsigned id);
  bool removeEdge (const unsigned id1, const unsigned id2);
  std::pair<std::string, int>  getEdgeValue (const unsigned id1, const unsigned id2);
  bool setEdgeValue (const unsigned id1, const unsigned id2, const int edgValue);
  bool adjacent(const unsigned id1, const unsigned id2);
  std::vector<int> neighbors (const unsigned id);
};

std::ostream &operator << (std::ostream &stream, const AMGraph &graph);

class ALVertex
{
  public:
  int vertex_id;
  std::string value;
  std::vector<int> ids;
  std::vector<int> edges;

  ALVertex(const std::string &value, const int &id)
  {
    this->value = value;
    this->vertex_id = id;
  }
};

class ALGraph
{
  public:
    unsigned id_counter;
    std::vector< ALVertex *> adjacentList;
    ALGraph ()
    {
      id_counter = 0;
    }
    int addVertex(std::string value);
    bool removeVertex (int vertexID);
    std::pair<std::string, std::string> getVertexValue(int vertexID);
    bool setVertexValue (int vertexID, std::string value);
    bool addEdge (int id1, int id2, int edge) ;
    void removeEdges(int id);
    bool removeEgde(int id1, int id2);
    std::pair<std::string, int> getEdgeValue(int id1, int id2) ;
    bool setEdgeValue(int id1, int id2, int edgeValue);
    bool adjacent(int id1, int id2);


};

std::ostream &operator << (std::ostream &stream, const ALGraph &graph);



