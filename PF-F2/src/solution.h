#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "vector.h"
#include "heap.h"
#include "puzzle.h"
#include "file_manager.h"
#include "stack.h"
#include "utils.h"

typedef struct vertex vertex_t;

#define NOT_IN_QUEUE NULL
#define MADE_NO_CHANGE (void *)0x1

#define PATH_EXISTS true
#define PATH_DOESNT_EXIST false

/* operate */
void solution_updateQueue(puzzleInfo *puzzle, int idx, vertex_t **dij, heap_t **h);
void solution_solvePuzzle(puzzleInfo *puzzle, FILE *fpout);
bool solution_dijkstra(puzzleInfo *puzzle, vec *start, vec *end, vertex_t **dij);
stack_t *solution_storePath(puzzleInfo *puzzle, vertex_t **dij, int idx);
void solution_pathTraceback(puzzleInfo *puzzle, vertex_t *dij, int child, FILE *fp);
bool solution_findBestCombination(puzzleInfo *puzzle, int visiting);
void solution_problemA(puzzleInfo *puzzle, FILE *solutionFile);
void solution_problemB(puzzleInfo *puzzle, FILE *solutionFile);
void solution_problemC(puzzleInfo *puzzle, FILE *solutionFile);

/* utils */
int solution_checkBounds(puzzleInfo *puzzle, vec *position);

/* init */
FILE *solution_init(char *argv[]);

/* free */
void solution_free(FILE *fp);
