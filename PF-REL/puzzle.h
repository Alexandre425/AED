#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "utils.h"

typedef struct _puzzleInfo puzzleInfo;

/* init */
puzzleInfo *puzzle_initPuzzle();

/* free */
puzzleInfo *puzzle_freePuzzle(puzzleInfo *puzzle);

/* utils */
int puzzle_paremetersCheck(puzzleInfo *puzzle);

/* set */
void puzzle_setProblemType(puzzleInfo *puzzle, char type);
void puzzle_setNPoints(puzzleInfo *puzzle, int nPoints);
void puzzle_setCityDimensions(puzzleInfo *puzzle, int x_coord, int y_coord);
void puzzle_setTouristicPoint(puzzleInfo *puzzle, int index, int x, int y);
void puzzle_setCityMapTile(puzzleInfo *puzzle, int x_coord, int y_coord, short tileCost);
void puzzle_setValidity(puzzleInfo *puzzle, short validity);
void puzzle_setPathSteps(puzzleInfo *puzzle, short pathSteps);


/* get */
char puzzle_getProblemType(puzzleInfo *puzzle);
int puzzle_getNPoints(puzzleInfo *puzzle);
vec *puzzle_getCityDimensions(puzzleInfo *puzzle);
vec *puzzle_getTouristicPoint(puzzleInfo *puzzle, int index);
int puzzle_getTileCost(puzzleInfo *puzzle, vec *position);
short puzzle_getPathSteps(puzzleInfo *puzzle);


short puzzle_getValidity(puzzleInfo *puzzle);
