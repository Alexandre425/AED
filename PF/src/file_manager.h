#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "puzzle.h"

/* read */
puzzlesBox *file_readPuzzles(char *argv[]);

/* write */
void file_writeSolution(char *solutionString, FILE *fp);