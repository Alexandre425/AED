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

  int i = 0;
  puzzlesBox *box = NULL;

  arguments_check(argc, argv);
  for (i = 0; i < argc; i++)
    printf("%s\n", argv[i]);

  box = file_readPuzzles(argv);

  solution_solvePuzzleBox(box, argv);

  box = puzzle_freePuzzlesBox(box);

  return 0;
}