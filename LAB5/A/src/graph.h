#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _graph graph_t;

graph_t* graph_readGraph(FILE *fp);
int graph_maxDegree(graph_t *graph);
float graph_density(graph_t *graph);
int graph_edges(graph_t* graph);
void graph_writeEdges(graph_t *graph, char* file);
void graph_print(graph_t *graph);
void graph_free(graph_t *graph);
