#include <vector>
#include <utility> //pair
#include <iostream>
#include <string>     // std::string, std::to_string
#include <set>
#include <map>

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
  std::vector<std::pair<int, int> > adjacent;  // [id|edge..id|edge]

  ALVertex(const std::string &value, const int &id)
  {
    this->vertex_id = id;
    this->value = value;
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
    // void removeEdges(int id);
    // bool removeEgde(int id1, int id2);
    // std::pair<std::string, int> getEdgeValue(int id1, int id2) ;
    // bool setEdgeValue(int id1, int id2, int edgeValue);
    // bool adjacent(int id1, int id2);
    // const std::vector<int> &neighbors(int id);
};

std::ostream &operator << (std::ostream &stream, const ALGraph &graph);

class SocialNetworkVertex
{
  public:
  int id;
  std::string name;
  std::vector<SocialNetworkVertex * > friends;

  SocialNetworkVertex(int id, std::string)
  {
    this->id = id;
    this->name = name;
  }
};

bool someoneOnInside (SocialNetworkVertex *vertex, const int srcID, std::vector<int> companyIDs);


class GenericGraph
{
  public:
    int id;
    std::vector<GenericGraph*> frieends;
};


void vertexIsReachable (GenericGraph *graph, int id1, int id2 , std::set<int> &excludeID ,std::vector<int> &path , std::vector<int> currPath = std::vector<int>() );
void allPaths (GenericGraph *graph, int id1, int id2 ,  std::set<int> &excludeID, std::vector<std::vector<int> > &paths , std::vector<int> currPath = std::vector<int>() );

void shortestPath (GenericGraph *graph, int id1, int id2, std::set<int> &excludeID, std::vector<int>  &path , std::vector<int> currPath = std::vector<int>() );
void gimmieThreeSteps (GenericGraph *graph, const int id, std::set<int> &excludeID, std::vector<int> &ids, std::vector<int> path = std::vector<int> () ) ;

void easyToGetThere(GenericGraph *graph,  std::vector<int> &ids, std::map<int, std::pair<int, int> > data = std::map<int, std::pair<int, int> > ()  );
