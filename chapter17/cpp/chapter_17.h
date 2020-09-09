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

class ELGraph
{
  public:
    std::vector< ELVertex *> vertexList;
    std::vector<std::pair<int, int> > edgeList;
    int addVertex(const int &value);
    bool removeVertex(const int &id);
    std::pair<std::string, int> getVertexValue(const int &id);
    bool setVertexValue(int id, int value);
};

std::ostream &operator << (std::ostream &stream, const ELGraph &graph);
