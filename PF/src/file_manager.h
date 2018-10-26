#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "puzzle.h"

puzzlesBox* file_readPuzzles(char *argv[]);

void file_writeSolution(char* solutionString, FILE* fp);