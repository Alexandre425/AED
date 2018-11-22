#include "graph.h"

static int nodeNum;

typedef struct _graph
{
  int node;
  int cost;
} _graph;

LinkedList **graph_readGraph(FILE *fp)
{

  int num = 0;
  int a, b, cost;

  // read node number
  while (fscanf(fp, "%d", &nodeNum) != 1);
  // ignoring the edge number (removing from the stream)
  while (fscanf(fp, "%d", &num) != 1);

  _graph *temp;
  // allocate the list array
  LinkedList **graph = calloc(nodeNum, sizeof(LinkedList*)); if (graph == NULL) exit (-1);

  while (fscanf(fp, "%d %d %d", &a, &b, &cost) == 3){
    // a -> b connection
    temp = calloc(1, sizeof(_graph)); if (temp == NULL) exit (-1);
    temp->node = b;
    temp->cost = cost;
    graph[a] = insertUnsortedLinkedList(graph[a], (Item)temp);
    // b -> a connection
    temp = calloc(1, sizeof(_graph)); if (temp == NULL) exit (-1);
    temp->node = a;
    temp->cost = cost;
    graph[b] = insertUnsortedLinkedList(graph[b], (Item)temp);
  }

  return graph;
}

void graph_writeEdges(LinkedList **graph, char *file)
{
  // generating file name
  file = strtok(file, ".");
  file = strcat(file, ".ladj");
  // creating output file
  FILE *fp = fopen(file, "w");

  // printing the header
  fprintf(fp, "%d\n", nodeNum);
  // printing the edges
  LinkedList *aux;
 
  for (int i = 0; i < nodeNum; i++)
  {
    aux = graph[i];
    while(aux != NULL){
      fprintf(fp, "%d:%d ", ((_graph*)getItemLinkedList(aux))->node, ((_graph*)getItemLinkedList(aux))->cost);
      aux =  getNextNodeLinkedList(aux);
    }              
    fprintf(fp, "-1\n");
  }
  fclose(fp);
}

void item_free(Item graph){
  free((_graph*)graph);
}

void graph_free(LinkedList** graph){
  for (int i = 0; i < nodeNum; i++)
    freeLinkedList(graph[i], item_free);
  free(graph);
}
