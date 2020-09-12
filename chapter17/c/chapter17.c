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

enum boolean ELGraph_setEdgeValue(struct ELGraph *graph, int id1, int id2, int value)
{
  struct ELEdge *edge;
  enum boolean result = false;

  if (graph )
  {
    if (graph->edgeList)
    {
      edge = graph->edgeList;
      while (edge && !result)
      {
        if (edge->src_id ==id1 && edge->dest_id == id2)
        {
          result = true;
          edge->value = value;
        }
        edge = edge->next;
      }
    }
  }
  return result;
}

enum boolean ELGraph_adjacent (struct ELGraph *graph, int id1, int id2)
{
  struct ELEdge *edge;

  if (graph )
  {
    if (graph->edgeList)
    {
      edge = graph->edgeList;

      while (edge)
      {
        if (edge->src_id ==id1 && edge->dest_id == id2)
        {
          return true;
        }
        edge = edge->next;
      }
    }
  }
  return false;
}

struct intlist * ELGraph_neighbors(struct ELGraph *graph, int id)
{
  struct intlist *collection = NULL;
  struct ELEdge *edge;
  struct intlist  *tmp;

  if (graph)
  {
    if (graph->edgeList)
    {
      edge = graph->edgeList;
      while (edge)
      {
        if (edge->src_id == id)
        {
          tmp = (  struct intlist  *) malloc(sizeof(  struct intlist ));
          tmp->value = edge->dest_id;
          tmp->next = collection;
          collection = tmp;
        }
        edge = edge->next;
      }
    }
  }
  return collection;
}

void AMGraph_display(struct AMGraph *graph)
{
  int row = -1;

  printf("\n---- start  ---\n", graph->n);

  for (int i = 0; i < graph->n * graph->n; i++)
  {
    if (i  % graph->n == 0)
    {
      row++;
      printf("\n");
    }
    printf("[%d]", graph->array[ row * graph->n +  (i % graph->n) ] );
  }

  printf("\n---- end---\n");

}

int AMGraph_addVertex (struct AMGraph ** graph)
{
  static int k = 0;
  int *newArray ;

  k++;

  if (*graph == NULL)
  {
    *graph = malloc (sizeof (struct AMGraph *));
    (*graph)->n = 1;
    (*graph)->array = (malloc( sizeof(int *)  *  1  ));
    (*graph)->array[0] = 0;
  }
  else
  {
    (*graph)->n = k ;
    newArray =  malloc( sizeof(int *) * ( k * k) );

    for (int r = 0; r  < k; r++)
    {
      for (int c = 0; c < k; c++)
      {
        if ( (r < k - 1)  &&  (c < k - 1 ) )
        {
          newArray[ r * (k) + c ] = (*graph)->array[r * (k - 1) + c];
        }
        else if ( newArray[ r * k + c] != -2)
        {
          newArray[ r * k + c] = -1;
        }

        if (r==c && newArray[ r * k + c]  != -2 )
        {
           newArray[ r * k + c] = 0;
        }

        // contingious nulls row/column
        if (r == k - 1 && r > 0)
        {
          if (newArray[ (r - 1) * k + c ]  == -2 )
          {
            newArray[ (r ) * k + c ]  = -2;
          }
        }

        if (c == k - 1 && c > 0 )
        {
          if (newArray[r * k + (c-1) ]  == -2 )
          {
            newArray[ r  * k + c ]  = -2;
          }
        }
      }
    }

    free((*graph)->array);
    (*graph)-> array = newArray;
  }

  return k;
}

enum boolean AMGraph_removeVertex (struct AMGraph *graph, unsigned id )
{
  enum boolean result = false;

  for (int r = 0; r < graph->n; r++)
  {
    for (int c = 0; c < graph->n; c++)
    {
      if (graph->array[ r * graph->n + c ] != -2 && (r == id || c == id) )
      {
        graph->array[ r * graph->n + c ] = -2;
        result |= true;
      }
    }
  }
  return result;
}

enum boolean AMGraph_addEdge (struct AMGraph *graph, const int id1, const int id2, const int value)
{
  int count = 0;
  int index = graph->n * id1 + id2;

  if (graph)
  {
    if (index >= 0 && index < graph->n * graph->n)
    {
      if (graph->array[graph->n * id1 + id2] != -2)
      {
        graph->array[graph->n * id1 + id2] = value;
      }
      return true;
    }
  }
  return false;
}

void AMGraph_removeEdges (struct AMGraph *graph, const int id)
{
  if (graph)
  {
    for (int r = 0; r < graph->n; r++)
    {
      for (int c = 0; c < graph->n; c++)
      {
        if (graph->array[r * graph->n + c]  == -2)
        {
          continue;
        }
        if (id == r || id == c)
        {
          graph->array[r * graph->n + c] = -1;
        }
      }
    }
  }
}

enum boolean AMGraph_removeEdge (struct AMGraph *graph, const int id1, const int id2)
{
  if (graph)
  {
    if (id1 < graph->n && id2 < graph->n)
    {
      if (graph->array[id1 * graph->n + id2] != -2)
      {
       graph->array[id1 * graph->n + id2]= -1;
        return true;
      }
    }
  }
  return false;
}

struct pair AMGraph_getEdgeValue (struct AMGraph *graph, const unsigned id1, const unsigned id2)
{
  struct pair result = {.valid = false};

  if (graph)
  {
    if ( id1 < graph->n &&  id2 < graph->n)
    {
      if (graph->array[id1 * graph->n + id2] != -2)
      {
        result.value = graph->array[id1 * graph->n + id2];
        result.valid = true;
      }
    }
  }
  return result;
}

enum boolean AMGraph_setEdgeValue (struct AMGraph *graph, const unsigned id1, const unsigned id2, const int edgeValue)
{
  if (graph)
  {
    if (id1 >=0 && id1 < graph->n && id2 >= 0 && id2 < graph->n )
    {
      if (graph->array[id1 * graph->n + id2] != -2)
      {
        graph->array[id1 * graph->n + id2]  = edgeValue;
        return true;
      }
    }
  }
  return false;
}

enum boolean AMGraph_adjacent(struct AMGraph *graph, const unsigned id1, const unsigned id2)
{
  if (graph)
  {
    if (id1 >=0 && id1 < graph->n && id2 >= 0 && id2 < graph->n )
    {
      if (graph->array[id1 * graph->n + id2] > 0 )
      {
        return true;
      }
    }
  }
  return false;
}

struct llist * AMGraph_neighbors(struct AMGraph *graph, int id)
{
  struct llist *llist =  NULL, *tmp = NULL;

  if (graph)
  {
    if (id >= 0 && id < graph->n)
    {
      for (int i = 0; i < graph->n ; i++)
      {
        if (graph->array[id * graph->n + i]  > 0)
        {
          tmp = malloc(sizeof(struct llist *) );
          tmp->value = i;
          tmp->next = llist;
          llist =tmp;
        }
       }
    }
  }
  return llist;
}

void ALGraph_display (struct ALGraph * graph)
{
  printf("\n start \n\n");
  while (graph)
  {
    printf(" %d :  ", graph->value );
    for (int i = 0; i < graph->size; i++)
    {
      printf(" [%d] ", graph->array[i] );
    }
    printf("\n");
    graph = graph->next;
  }
  printf("\n end \n");

}

int ALGraph_addVertex (struct ALGraph ** graph, int value)
{
  static int id = 0;
  struct ALGraph * tmp;

  tmp = malloc( sizeof(struct ALGraph *) );
  tmp->vertex_id = id;
  tmp ->value = value;
  tmp->size = 0;
  tmp->array = malloc (sizeof(int *) *  tmp->size  );
  tmp->next = NULL;

  if ( *graph  == NULL)
  {
    *graph = tmp;
  }
  else
  {
    tmp->next = (*graph);
    (*graph) = tmp;
  }
  return id++;
}

enum boolean ALGraph_removeVertex (struct ALGraph ** graph, const int vertexID)
{
  struct ALGraph * algraph_runner = *graph;
  struct ALGraph *delNode;
  int counter = 0;

  while (algraph_runner->next)
  {
    if (algraph_runner->next->vertex_id == vertexID)
    {
      counter++;
      delNode = algraph_runner->next;
      algraph_runner->next = algraph_runner->next->next;
      free(delNode->array);
      free(delNode);
    }
    else
    {
      //remove id from array (-1 = NULL DATA )
      for (int i = 0; i < algraph_runner->next->size; i++)
      {
        if (algraph_runner->next->array[i] == vertexID)
        {
          algraph_runner->next->array[i] = -1;
        }
      }
      algraph_runner = algraph_runner->next;
    }
  }

  if ((*graph )->vertex_id == vertexID)
  {
    delNode = *graph;
    *graph = delNode->next;
    free(delNode->array);
    free(delNode);
  }

  return counter == 0 ? false : true;
}

struct pair ALGraph_getVertexValue(struct ALGraph *graph, int id)
{
  struct pair result = {.valid = false};

  while (graph)
  {
    if (graph->vertex_id == id)
    {
      result.value = graph->value;
      result.valid = true;
    }
    graph = graph->next;
  }
  return result;
}

enum boolean ALGraph_setVertexValue (struct ALGraph *graph, int id, int value)
{
  while (graph)
  {
    if (graph->vertex_id == id)
    {
      graph->value = value;
      return true;
    }
    graph = graph->next;
  }

  return false;
}

int main()
{
  time_t t;
 // srand((unsigned) time(&t));  // fixed pseudo random

  struct ALGraph *graph = NULL;

  printf ( "[%d]\n", ALGraph_addVertex(&graph, 23));
  printf ( " [%d]\n ", ALGraph_addVertex(&graph,111));
  printf ( "[%d]\n", ALGraph_addVertex(&graph, 34323));
  ALGraph_setVertexValue(graph, 1, 555);
  ALGraph_display(graph);

  // AMGraph_removeEdges(graph, 2);

  // struct ELGraph *graph = NULL;
  // srand((unsigned) time(&t));  // fixed pseudo random
  // struct ELGraph *graph = NULL;
  // ELGraph_add_vertex(&graph, rand() % 100);
  // // ELGraph_remove_vertex(&graph, 1);
  // ELGraph_add_vertex(&graph, rand() % 100);
  // ELGraph_setVertexValue(graph, 0, 1000);
  // ELGraph_addEdge(graph, 0, 1, 0);
  // ELGraph_addEdge(graph,1, 0, 0);
  // ELGraph_removeEdge(graph, 1, 0);
  // display_edges(graph);
  // struct pair pair =  getVertexValue(graph, 0);
  // printf("  %d   %d \n", pair.valid, pair.value);
  // printf("[ vertex %d  %d]\n", graph->vertexList->value, graph->vertexList->id);
}