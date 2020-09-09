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

struct ELVertex * el_vertex (int value, int id)
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

struct pair ELGraph_getVertexValue (struct ELGraph *graph, int id)
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

void display_edges(struct ELGraph *graph)
{
  struct ELEdge *edge ;

  if (!graph)
  {
    return;
  }

  if (!graph->edgeList)
  {
    return;
  }

  edge = graph->edgeList;

  while (edge)
  {
    printf(" {src %d dest %d value %d}, ", edge->src_id, edge->dest_id, edge->value);
    edge = edge->next;
  }
  printf ("\n");
}

enum boolean ELGraph_setVertexValue(struct ELGraph *graph, int id, int value)
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

enum boolean ELGraph_addEdge (struct ELGraph *graph, int src_id, int dest_id, int value)
{
  int count = 0;
  struct ELEdge *edge;
  struct ELVertex *vertex_runner;
  struct ELEdge *edge_runner;

  vertex_runner = graph->vertexList;
  edge_runner = graph->edgeList;

  // do vertices exist ?
  while (vertex_runner)
  {
    count += (src_id == vertex_runner->id || dest_id == vertex_runner->id);
    vertex_runner = vertex_runner->next ;
  }

  // edge exist ?
  while (edge_runner)
  {
    if (edge_runner->dest_id == dest_id && edge_runner->src_id == src_id)
    {
      printf("\nreturning\n");
      return false;
    }
    edge_runner = edge_runner->next;
  }

  if (count == 2)
  {
    edge = el_edge(dest_id, src_id, value);
    edge->next = graph->edgeList;
    graph->edgeList = edge;
  }

  return +(count == 2);
}

void ELGraph_removeEdges(struct ELGraph *graph, int id)
{
  struct ELEdge *edge;
  struct ELEdge *release_edge;

  if (graph)
  {
    if (graph->edgeList)
    {
      edge = graph->edgeList;
      while (edge->next)
      {
        if (edge->next->src_id == id || edge->next->dest_id == id)
        {
          release_edge = edge->next;
          edge->next = edge->next->next;
          free(release_edge);
        }
        else
        {
          edge = edge->next;
        }
      }

      if (graph->edgeList->src_id == id || graph->edgeList->dest_id == id)
      {
        release_edge = graph->edgeList;
        graph->edgeList = graph->edgeList->next;
        free(release_edge);
      }
    }
  }
}

enum boolean ELGraph_removeEdge(struct ELGraph *graph, int id1, int id2)
{
  struct ELEdge *release_edge = NULL;
  struct ELEdge *edge;

  if (graph)
  {
    if (graph->edgeList)
    {
      edge = graph->edgeList;
      while (edge->next)
      {
        if (edge->next->src_id == id1 && edge->next->dest_id == id2)
        {
          release_edge = edge->next;
          edge->next = edge->next->next;
          free(release_edge);
        }
        else
        {
          edge = edge->next;
        }
      }

      if (graph->edgeList->src_id == id1 && graph->edgeList->dest_id == id2)
      {
        release_edge = graph->edgeList;
        graph->edgeList = graph->edgeList->next;
        free(release_edge);
      }
    }
  }

  return !!release_edge;
}


struct pair ELGraph_getEdgeValue(struct ELGraph *graph, int id1, int id2)
{
  struct pair result = {.value = -1, .valid = false};
  struct ELEdge *edge;

  if (graph)
  {
    if (graph->edgeList)
    {
      edge = graph->edgeList;
      while (edge &&  !result.valid )
      {
        if (edge->dest_id == id2 && edge->src_id == id1)
        {
          result.value = edge->value;
          result.valid = true;
        }
        edge = edge->next;
      }
    }
  }
  return result;
}

enum boolean setEdgeValue(struct ELGraph *graph, int id1, int id2, int value)
{
  struct ELEdge *edge;
  enum boolean result = false;

  if (graph )
  {
    if (graph->edgeList)
    {
      edge = graph->edgeList;
      while (edge)
      {
        if (edge->src_id ==id1 && edge->dest_id == id2)
        {
          result = true;
          edge->value = value;
        }
      }
    }
  }
  return result;
}


int main()
{
  time_t t;
  // srand((unsigned) time(&t));  // fixed pseudo random
  struct ELGraph *graph = NULL;
  ELGraph_add_vertex(&graph, rand() % 100);
  // ELGraph_remove_vertex(&graph, 1);
  ELGraph_add_vertex(&graph, rand() % 100);

  ELGraph_setVertexValue(graph, 0, 1000);

  ELGraph_addEdge(graph, 0, 1, 0);
  ELGraph_addEdge(graph,1, 0, 0);


  ELGraph_removeEdge(graph, 1, 0);

  display_edges(graph);
  // struct pair pair =  getVertexValue(graph, 0);
  // printf("  %d   %d \n", pair.valid, pair.value);
  // printf("[ vertex %d  %d]\n", graph->vertexList->value, graph->vertexList->id);
}