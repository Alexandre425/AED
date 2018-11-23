#ifndef _FILE_MANAGER
#define _FILE_MANAGER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "puzzle.h"
#include "solution.h"

/* read */
void file_readPuzzles(char *argv[]);

/* write */
void file_writeSolution(char *solutionString, FILE *fp);

#endif