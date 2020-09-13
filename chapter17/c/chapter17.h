#include <stdio.h>
#include <stdlib.h>

enum boolean
{
  false,
  true
} boolean;

struct ELEdge
{
  int src_id;
  int dest_id;
  int value;
  struct ELEdge *next;
};

struct ELVertex
{
  int id;
  int value;
  struct ELVertex *next;
};

struct ELGraph
{
  struct ELVertex *vertexList;
  struct ELEdge *edgeList;
};

struct ELEdge * el_edge ( int dest_id,  int src_id,  const int value);
struct ELVertex * el_vertex (int value, int id);
struct ELGraph * el_graph ();

unsigned ELGraph_add_vertex( struct ELGraph **collection, int value);
enum boolean ELGraph_remove_vertex(struct ELGraph **graph, int id);
void display_vertices (struct ELGraph *graph ) ;
struct pair ELGraph_getVertexValue (struct ELGraph *graph, int id);
enum boolean ELGraph_setVertexValue(struct ELGraph *graph, int id, int value);
enum boolean ELGraph_addEdge (struct ELGraph *graph, int src_id, int dest_id, int value);
void ELGraph_removeEdges(struct ELGraph *graph, int id);
struct pair ELGraph_getEdgeValue(struct ELGraph *graph, int id1, int id2);
enum boolean setEdgeValue(struct ELGraph *graph, int id1, int id2, int value);
enum boolean ELGraph_adjacent (struct ELGraph *graph, int id1, int id2);
struct intlist * ELGraph_neighbors(struct ELGraph *graph, int id);

struct intlist
{
  int *value;
  struct intlist *next;
};

struct llist
{
  int value;
  struct llist *next;
};

struct pair
{
  enum boolean valid;
  int value;
};

struct AMGraph
{
  unsigned n;
  int * array;
};

int AMGraph_addVertex (struct AMGraph ** graph);
enum boolean AMGraph_removeVertex(struct AMGraph *graph, unsigned id );
enum boolean AMGraph_addEdge(struct AMGraph *graph, const int id1, const int id2, const int value);
void AMGraph_removeEdges (struct AMGraph *graph, const int id);
enum boolean AMGraph_removeEdge (struct AMGraph *graph, const int id1, const int id2);
struct pair AMGraph_getEdgeValue (struct AMGraph *graph, const unsigned id1, const unsigned id2);
enum boolean AMGraph_setEdgeValue (struct AMGraph *graph, const unsigned id1, const unsigned id2, const int edgeValue);
enum boolean AMGraph_adjacent(struct AMGraph *graph, const unsigned id1, const unsigned id2);
struct llist * AMGraph_neighbors(struct AMGraph *graph, int id);

struct ALGraphMeta
{
  struct ALGraphMeta *next;
  int from_id;
  int edge;
};

struct ALGraph
{
  struct  ALGraph *next;
  int value;
  int vertex_id;
  struct  ALGraphMeta *meta;   // [dest_id, edge, dest_id, edge...]

};

void ALGraph_display (struct ALGraph * graph);
int ALGraph_addVertex (struct ALGraph ** graph, int value);
enum boolean ALGraph_removeVertex (struct ALGraph ** graph, const int vertexID);

struct pair ALGraph_getVertexValue(struct ALGraph *graph, int id);
enum boolean ALGraph_addEdge(struct ALGraph *graph, int id1, int id2, int edge);
