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

struct pair
{
  enum boolean valid;
  int value;
};