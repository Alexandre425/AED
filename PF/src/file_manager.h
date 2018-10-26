#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "puzzle.h"

puzzlesBox* file_readPuzzles(char *argv[]);

FILE *file_writeSolution(FILE* fp, char* solutionString, char* argv[]);