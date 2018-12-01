#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "vector.h"
#include "heap.h"
#include "puzzle.h"
#include "file_manager.h"

typedef struct vertex vertex_t;

#define NOT_IN_QUEUE NULL

/* operate */
void solution_updateQueue(puzzleInfo *puzzle, int idx, vertex_t** dij, heap_t **h);
void solution_solvePuzzle(puzzleInfo *puzzle, FILE* fpout);
void solution_dijkstra(puzzleInfo *puzzle, vec *start, vec *end, vertex_t** dij);
void solution_problemA(puzzleInfo *puzzle, FILE *solutionFile);
void solution_problemB(puzzleInfo *puzzle, FILE *solutionFile);
void solution_problemC(puzzleInfo *puzzle, FILE *solutionFile);

/* utils */
int solution_checkBounds(puzzleInfo *puzzle, vec *position);

/* init */
FILE* solution_init(char *argv[]);

/* free */
void solution_free(FILE* fp);
