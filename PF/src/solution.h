#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "puzzle.h"

int solution_checkBounds(puzzleInfo* puzzle, vec* position);

void solution_solvePuzzleBox(puzzlesBox* box);

void solution_problemA(puzzleInfo* puzzle);
void solution_problemB(puzzleInfo* puzzle);

char* solution_convertIntChar(int number);

