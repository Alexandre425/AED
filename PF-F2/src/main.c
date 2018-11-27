#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "arguments.h"
#include "puzzle.h"
#include "file_manager.h"
#include "solution.h"

int main(int argc, char *argv[])
{
  arguments_check(argc, argv);
  file_readPuzzles(argv);

  return 0;
}