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
void file_readPuzzles(char *argv[])
{
    
  FILE *fpin = NULL, *fpout = NULL;
  char buffer[64];
  int num;
  int i = 0, j = 0;
  puzzleInfo *puzzle = NULL; 

  fpin = fopen(argv[1], "r");
  if (fpin == NULL){
    exit(0);
  }

  fpout = solution_init(argv);
  puzzle = puzzle_initPuzzle();

  while (fgets(buffer, 64, fpin) != NULL){
    int x = -1, y = -1, nPoints = -1;
    char problemType = '\0';
    sscanf(buffer,"%d %d %c %d", &x, &y, &problemType, &nPoints);
    memset(buffer, 0, 64);
    puzzle_setCityDimensions(puzzle, x, y);
    puzzle_setProblemType(puzzle, problemType);
    puzzle_setNPoints(puzzle, nPoints);
    puzzle_setValidity(puzzle, puzzle_paremetersCheck(puzzle));

    /* if the puzzle is valid, read the touristic points and tile map */
    if (puzzle_getValidity(puzzle) == 0){
      /* reading the touristic points */
      for (i = 0; i < puzzle_getNPoints(puzzle); i++){
        while (fscanf(fpin, "%d", &num) != 1);
        x = num;
        while (fscanf(fpin, "%d", &num) != 1);
        y = num;
        puzzle_setTouristicPoint(puzzle, i, x, y);
      }

      /* reading the tile map */
      for (i = 0; i < vec_x(puzzle_getCityDimensions(puzzle)); i++){
        for (j = 0; j < vec_y(puzzle_getCityDimensions(puzzle)); j++){
          while (fscanf(fpin, "%d", &num) != 1);
          puzzle_setCityMapTile(puzzle, i, j, num);
        }
      }

      solution_solvePuzzle(puzzle, fpout);
      puzzle_freePuzzle(puzzle);
      puzzle = puzzle_initPuzzle();
      
    }
    // if the puzzle is invalid, write the solution (no more information needs to be read)
    else if (puzzle_getValidity(puzzle) == 1){
      solution_solvePuzzle(puzzle, fpout);
      puzzle_freePuzzle(puzzle);
      puzzle = puzzle_initPuzzle();
    }
  }

  fclose(fpin);
  puzzle_freePuzzle(puzzle);
  solution_free(fpout);
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