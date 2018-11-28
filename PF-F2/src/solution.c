#include "solution.h"

vec *possibleMoves[8];

/******************************************************************************
 * solution_init()
 *
 * Description: initializes useful resources for puzzle resolution
 *****************************************************************************/
FILE* solution_init(char *argv[])
{
  // vector of all the moves (relative to it's current pos) a horse piece can make
  possibleMoves[0] = vec_create(1, 2);
  possibleMoves[1] = vec_create(1, -2);
  possibleMoves[2] = vec_create(-1, 2);
  possibleMoves[3] = vec_create(-1, -2);
  possibleMoves[4] = vec_create(2, 1);
  possibleMoves[5] = vec_create(2, -1);
  possibleMoves[6] = vec_create(-2, 1);
  possibleMoves[7] = vec_create(-2, -1);

  // creating the output file
  FILE *fp = NULL;
  char *token;
  char *fileName;
  token = strtok(argv[1], ".");
  fileName = strcat(token, ".valid");
  fp = fopen(fileName, "w"); if (fp == NULL) exit(0);

  return fp;
}

/******************************************************************************
 * solution_free()
 *
 * Description: cleans up the allocated resources for puzzle resolution
 *****************************************************************************/
void solution_free(FILE* fp)
{
  for (int i = 0; i < 8; i++)
    free(possibleMoves[i]);

  fclose(fp);
}

/******************************************************************************
 * solution_solvePuzzleBox()
 *
 * Arguments:   box - the puzzle box
 *
 * Description: solves all the puzzles in the puzzle box;
 *****************************************************************************/
void solution_solvePuzzle(puzzleInfo *puzzle, FILE* fpout)
{
  char solution[128];

  if (puzzle_getValidity(puzzle) == 1)
  {
    sprintf(solution, "%d %d %c %d %d %d\n\n",
            vec_x(puzzle_getCityDimensions(puzzle)),
            vec_y(puzzle_getCityDimensions(puzzle)),
            puzzle_getProblemType(puzzle),
            puzzle_getNPoints(puzzle),
            -1, // puzzle is invalid
            0); // cost is zero as a result
    file_writeSolution(solution, fpout);
  }
  else
    switch (puzzle_getProblemType(puzzle))
    {
    case 'A':
      solution_problemA(puzzle, fpout);
      break;
    case 'B':
      solution_problemB(puzzle, fpout);
      break;
    case 'C':
      solution_problemC(puzzle, fpout);
      break;
    }
}

/******************************************************************************
 * solution_checkBounds()
 *
 * Arguments:   puzzle - the puzzle containing the map in question
 *              pos - the position to check
 * Returns:     -1 - position is out of bounds
 *              0 - position is in bounds
 * 
 * Description: verifies if the position vector given is in bounds relative to the city map
 *****************************************************************************/
int solution_checkBounds(puzzleInfo *puzzle, vec *pos)
{
  int x = vec_x(puzzle_getCityDimensions(puzzle));
  int y = vec_y(puzzle_getCityDimensions(puzzle));
  if (vec_x(pos) < x && vec_x(pos) >= 0 && vec_y(pos) < y && vec_y(pos) >= 0)
    return 0;
  else
    return -1;
}

/******************************************************************************
 * solution_problemA()
 *
 * Arguments:   puzzle - puzzle to solve
 * 
 * Description: solves a puzzle of the 'A' problem type
 *****************************************************************************/
void solution_problemA(puzzleInfo *puzzle, FILE *fp)
{
}

/******************************************************************************
 * solution_problemB()
 *
 * Arguments:   puzzle - puzzle to solve
 * 
 * Description: solves a puzzle of the 'B' problem type
 *****************************************************************************/
void solution_problemB(puzzleInfo *puzzle, FILE *fp)
{ 
}
/******************************************************************************
 * solution_problemC()
 *
 * Arguments:   puzzle - puzzle to solve
 * 
 * Description: solves a puzzle of the 'C' problem type
 *****************************************************************************/
void solution_problemC(puzzleInfo *puzzle, FILE *fp)
{ 

}

