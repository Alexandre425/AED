#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "arguments.h"
#include "puzzle.h"
#include "file_manager.h"
#include "solution.h"
#include "heap.h"

int main(int argc, char *argv[])
{

  heap_t* h = heap_initHeap();
  h = heap_put(h, NULL, 7);
  h = heap_put(h, NULL, 1);
  h = heap_put(h, NULL, 2);
  h = heap_put(h, NULL, 6);
  h = heap_put(h, NULL, 5);
  h = heap_put(h, NULL, 2);
  h = heap_put(h, NULL, 1);
  h = heap_put(h, NULL, 9);
  h = heap_put(h, NULL, 8);
  h = heap_put(h, NULL, 1);

  heap_get(h);
  heap_get(h);
  heap_get(h);

  heap_debugPrint(h);

  heap_free(h);

  arguments_check(argc, argv);
  file_readPuzzles(argv);

  return 0;
}