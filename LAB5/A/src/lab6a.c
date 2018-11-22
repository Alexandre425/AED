#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



int main (int argc, char *argv[]){

  graph_t *graph = NULL;
  
  if (argc != 2){
    printf("Invalid number of arguments\n");
    exit(-1);
  }

  FILE* fp = fopen(argv[1], "r");
  if (fp == NULL)
    exit(-1);
  graph = graph_readGraph(fp);
  fclose(fp);

  graph_print(graph);

  printf("Max degree: %d\n", graph_maxDegree(graph));
  printf("Graph density: %f\n", graph_density(graph));
  graph_writeEdges(graph, argv[1]);

  graph_free(graph);

  return EXIT_SUCCESS;
}