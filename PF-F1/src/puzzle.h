#ifndef _PUZZLE
#define _PUZZLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

typedef struct _puzzleInfo puzzleInfo;
typedef struct _puzzlesBox puzzlesBox;

/* init */
puzzlesBox *puzzle_initPuzzlesBox();
puzzleInfo *puzzle_initPuzzle();

/* free */
puzzlesBox *puzzle_freePuzzlesBox(puzzlesBox *box);
puzzleInfo *puzzle_freePuzzle(puzzleInfo *puzzle);

/* utils */
void puzzle_storePuzzle(puzzleInfo *puzzle, puzzlesBox *box);
int puzzle_paremetersCheck(puzzleInfo *puzzle);

/* set */
void puzzle_setProblemType(puzzleInfo *puzzle, char type);
void puzzle_setNPoints(puzzleInfo *puzzle, int nPoints);
void puzzle_setCityDimensions(puzzleInfo *puzzle, int x_coord, int y_coord);
void puzzle_setTouristicPoint(puzzleInfo *puzzle, int index, int x, int y);
void puzzle_setCityMapTile(puzzleInfo *puzzle, int x_coord, int y_coord, short tileCost);
void puzzle_setValidity(puzzleInfo *puzzle, short validity);

/* get */
char puzzle_getProblemType(puzzleInfo *puzzle);
int puzzle_getNPoints(puzzleInfo *puzzle);
vec *puzzle_getCityDimensions(puzzleInfo *puzzle);
vec *puzzle_getTouristicPoint(puzzleInfo *puzzle, int index);
int puzzle_getTileCost(puzzleInfo *puzzle, vec *position);
int puzzle_getNPuzzles(puzzlesBox *box);
puzzleInfo *puzzle_getPuzzleFromBox(puzzlesBox *box, int index);
short puzzle_getValidity(puzzleInfo *puzzle);

#endif