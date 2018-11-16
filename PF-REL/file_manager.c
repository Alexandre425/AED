#include "file_manager.h"

/******************************************************************************
 * file_readPuzzles()
 *
 * Arguments:   argv - runtime arguments, contains filename
 * Returns:     the newly created puzzle box, filled with all the read puzzles
 * 
 * Description: reads, validates and stores the puzzles in the foo.cities file
 *
 *****************************************************************************/
puzzlesBox* file_readPuzzles(char *argv[])
{
    
  FILE *fp = NULL;
  char buffer[64];
  int num;
  int i = 0, j = 0;
  short validity;
  puzzleInfo *puzzle = NULL; 
  puzzlesBox *box =NULL;

  fp = fopen(argv[1], "r");
  if (fp == NULL){
    exit(0);
  }
  box = puzzle_initPuzzlesBox();
  puzzle = puzzle_initPuzzle();

  while (fgets(buffer, 64, fp) != NULL){
    int x = -1, y = -1, nPoints = -1;
    char problemType = '\0';
    sscanf(buffer,"%d %d %c %d", &x, &y, &problemType, &nPoints);
    memset(buffer, 0, 64);
    puzzle_setCityDimensions(puzzle, x, y);
    puzzle_setProblemType(puzzle, problemType);
    puzzle_setNPoints(puzzle, nPoints);
    validity = puzzle_paremetersCheck(puzzle);
    /* if the puzzle is valid, read the touristic points and tile map */
    if (0 == validity){
      /* reading the touristic points */
      for (i = 0; i < puzzle_getNPoints(puzzle); i++){
        while (fscanf(fp, "%d", &num) != 1);
        x = num;
        while (fscanf(fp, "%d", &num) != 1);
        y = num;
        puzzle_setTouristicPoint(puzzle, i, x, y);
      }

      /* reading the tile map */
      for (i = 0; i < vec_x(puzzle_getCityDimensions(puzzle)); i++){
        for (j = 0; j < vec_y(puzzle_getCityDimensions(puzzle)); j++){
          while (fscanf(fp, "%d", &num) != 1);
          puzzle_setCityMapTile(puzzle, i, j, num);
        }
      }
      
      puzzle_storePuzzle(puzzle, box);
      puzzle = puzzle_initPuzzle();           
    }
    else if (validity == 1){
      puzzle_setValidity(puzzle, -1);
      puzzle_storePuzzle(puzzle, box);
      puzzle = puzzle_initPuzzle();
    }
    memset(buffer, 0, 64);
  }

  fclose(fp);
  puzzle_freePuzzle(puzzle);
  return box;
}

/******************************************************************************
 * file_writeSolution()
 *
 * Arguments:   solution - solution string
 *
 * Description: writes the solution to a puzzle to the solution file
 *
 *****************************************************************************/
void file_writeSolution(char* solution, FILE* fp){
  fprintf(fp, "%s", solution);
}