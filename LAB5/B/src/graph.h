#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

typedef struct _graph graph_t;

LinkedList** graph_readGraph(FILE *fp);
void graph_writeEdges(LinkedList **graph, char *file);


