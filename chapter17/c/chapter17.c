#include <time.h>
#include "chapter17.h"

struct ELEdge * el_edge ( int dest_id,  int src_id,  const int value)
{
  struct ELEdge *edge = (struct ELEdge*) malloc( sizeof(struct ELEdge));
  edge->value = value;
  edge->src_id = src_id;
  edge->dest_id = dest_id;
  edge->next = NULL;
  return edge;
}

struct ELVertex * el_vertex (int value, id)
{
  struct ELVertex *vertex = (struct ELVertex *) malloc(sizeof(struct ELVertex));
  vertex->value = value;
  vertex->id = id;
  vertex->next = NULL;
  return vertex;
}

struct ELGraph * el_graph ()
{
  struct ELGraph *graph = (struct ELGraph *) malloc(sizeof(struct ELGraph));
  graph->vertexList = NULL;
  graph->edgeList = NULL;
  return graph;
}

unsigned ELGraph_add_vertex( struct ELGraph **graph, int value)
{
  struct ELVertex *vertex;
  static unsigned int vertex_len = -1;

  if (*graph == NULL)
  {
    *graph = el_graph();
  }
  vertex = el_vertex(value, ++vertex_len);
  vertex->next = (*graph)->vertexList;
  (*graph)->vertexList = vertex;
  return vertex_len;
}

enum boolean ELGraph_remove_vertex(struct ELGraph **graph, int id)
{
  struct ELVertex *vertex_runner = (*graph)->vertexList;
  struct ELVertex *remove_node = NULL;

  if ((*graph)->vertexList)
  {
    if ( (*graph)->vertexList->id == id)
      // root
    {
      remove_node = (*graph)->vertexList;
      (*graph)->vertexList =  (*graph)->vertexList->next;
    }
    else
      //next
    {
      vertex_runner = (*graph)->vertexList;
      while (vertex_runner->next)
      {
        if(vertex_runner->next->id == id)
        {
          remove_node = vertex_runner->next;
          vertex_runner->next = vertex_runner->next->next;
        }
      }
    }
   }

   if (remove_node)
   {
     free(remove_node);
   }

    return (remove_node != NULL);

  // TODO REMOVE EDGES
}

struct pair getVertexValue (struct ELGraph *graph, int id)
{
  struct ELVertex *vertex_runner = graph->vertexList;
  struct pair result = {.valid = false, .value = NULL};


  while (vertex_runner)
  {
    if (vertex_runner->id == id)
    {
      result.value = vertex_runner->value;
      result.valid = true;
      break;
    }
    vertex_runner = vertex_runner->next;
  }
  return result;
}


void display_vertices (struct ELGraph *graph )
{
  struct ELVertex *node = graph->vertexList;
  while (node)
  {
    printf(" {id: %d  value: %d} ", node->id, node->value);
    node = node->next;
  }
  printf("\n");
}

enum boolean setVertexValue(struct ELGraph *graph, int id, int value)
{
  struct ELVertex *vertex = graph->vertexList;

  while (vertex)
  {
    if (vertex->id == id)
    {
      vertex->value = value;
      return true;
    }
    vertex = vertex->next;
  }
  return false;
}

int main()
{
  time_t t;
  // srand((unsigned) time(&t));  // fixed pseudo random
  struct ELGraph *graph = NULL;
  ELGraph_add_vertex(&graph, rand() % 100);
  // ELGraph_remove_vertex(&graph, 1);

  setVertexValue(graph, 0, 1000);

  struct pair pair =  getVertexValue(graph, 0);
  printf("  %d   %d \n", pair.valid, pair.value);
  // printf("[ vertex %d  %d]\n", graph->vertexList->value, graph->vertexList->id);
}