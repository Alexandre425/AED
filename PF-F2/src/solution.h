
#ifndef _SOLUTION
#define _SOLUTION


#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "puzzle.h"
#include "file_manager.h"

/* operate */
void solution_solvePuzzle(puzzleInfo *puzzle, FILE* fpout);
void solution_problemA(puzzleInfo *puzzle, FILE *solutionFile);
void solution_problemB(puzzleInfo *puzzle, FILE *solutionFile);
void solution_problemC(puzzleInfo *puzzle, FILE *solutionFile);

/* utils */
int solution_checkBounds(puzzleInfo *puzzle, vec *position);

/* init */
FILE* solution_init(char *argv[]);

/* free */
void solution_free(FILE* fp);


#endif