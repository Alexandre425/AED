#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "puzzle.h"
#include "file_manager.h"

/* operate */
void solution_solvePuzzleBox(puzzlesBox *box, char *argv[]);
void solution_problemA(puzzleInfo *puzzle, FILE *solutionFile);
void solution_problemB(puzzleInfo *puzzle, FILE *solutionFile);

/* utils */
int solution_checkBounds(puzzleInfo *puzzle, vec *position);
