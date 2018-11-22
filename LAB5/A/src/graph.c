#include "graph.h"

typedef struct _graph
{
  int nodeNum;
  short **adjacencyMatrix;
} _graph;

_graph *graph_readGraph(FILE *fp)
{

  int num = 0;
  // allocate graph struct
  _graph *graph = calloc(1, sizeof(_graph));
  if (graph == NULL)
    exit(-1);

  // read node number
  while (fscanf(fp, "%d", &num) != 1);
  graph->nodeNum = num;

  // allocate and read adjancency matrix
  graph->adjacencyMatrix = calloc(num, sizeof(short*));
  if (graph->adjacencyMatrix == NULL)
    exit(-1);
  for (int i = 0; i < num; i++)
  {
    // alloc
    graph->adjacencyMatrix[i] = calloc(num, sizeof(short));
    if (graph->adjacencyMatrix[i] == NULL)
      exit(-1);
    // read
    for (int j = 0; j < num; j++)
      while (fscanf(fp, "%hd", &graph->adjacencyMatrix[i][j]) != 1);
  }

  return graph;
}

int graph_maxDegree(_graph *graph)
{
  int max = 0;

  for (int i = 0; i < graph->nodeNum; i++)
  {
    int edges = 0;
    for (int j = 0; j < graph->nodeNum; j++)
      if (graph->adjacencyMatrix[i][j] != 0)
        edges++;
    if (edges > max)
      max = edges;
  }

  return max;
}

float graph_density(_graph *graph)
{
  float density = 0.0;
  int edges = graph_edges(graph);

  density = (2 * edges) / (float)(graph->nodeNum);
  //density = (float)(edges) / (float)(graph->nodeNum * (graph->nodeNum - 1));  // E / V(V - 1)
  return density;
}

int graph_edges(_graph *graph)
{
  int edges = 0;
  for (int i = 0; i < graph->nodeNum; i++)
    for (int j = i + 1; j < graph->nodeNum; j++)
      if (graph->adjacencyMatrix[i][j] != 0)
        edges++;
  return edges;
}

void graph_writeEdges(_graph *graph, char *file)
{
  // generating file name
  file = strtok(file, ".");
  file = strcat(file, ".ram");
  // creating output file
  FILE *fp = fopen(file, "w");

  // printing the header
  fprintf(fp, "%d\n", graph->nodeNum);
  fprintf(fp, "%d\n", graph_edges(graph));

  // printing the edges
  for (int i = 0; i < graph->nodeNum; i++)
    for (int j = i + 1; j < graph->nodeNum; j++)
    {
      int cost;
      if ((cost = graph->adjacencyMatrix[i][j]) != 0)
        fprintf(fp, "%d %d %d\n", i, j, cost);
    }

  // closing the file
  fclose(fp);
}

void graph_print(_graph *graph)
{
  printf("%d\n", graph->nodeNum);

  for (int i = 0; i < graph->nodeNum; i++)
  {
    for (int j = 0; j < graph->nodeNum; j++)
      printf("%d ", graph->adjacencyMatrix[i][j]);
    printf("\n");
  }
}

void graph_free(_graph *graph){
  for (int i = 0; i < graph->nodeNum; i++)
    free(graph->adjacencyMatrix[i]);
  free(graph->adjacencyMatrix);
  free(graph);
}