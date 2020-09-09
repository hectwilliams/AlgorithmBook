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



unsigned ELGraph_add_vertex( struct ELGraph **collection, int value);
enum boolean ELGraph_remove_vertex(struct ELGraph **graph, int id);
void display_vertices (struct ELGraph *graph ) ;
struct pair getVertexValue (struct ELGraph *graph, int id);




struct pair
{
  enum boolean valid;
  int value;
};