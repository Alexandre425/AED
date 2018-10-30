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
  char c;
  int i = 0, j = 0;
  short validity;
  puzzleInfo *puzzle = NULL; 
  puzzlesBox *box =NULL;

  fp = fopen(argv[1], "r");
  if (fp == NULL){
    printf("Cannot open file!\n");
    exit(0);
  }
  box = puzzle_initPuzzlesBox();
  puzzle = puzzle_initPuzzle();

  while (fgets(buffer, 64, fp) != NULL){
    int x = -1, y = -1, nPoints = -1;
    char problemType = '\0';
    int digitCount = 0;
    sscanf(buffer,"%d %d %c %d", &x, &y, &problemType, &nPoints);
    memset(buffer, 0, 64);
    puzzle_setCityDimensions(puzzle, x, y);
    puzzle_setProblemType(puzzle, problemType);
    puzzle_setNPoints(puzzle, nPoints);
    validity = puzzle_paremetersCheck(puzzle);
    if (0 == validity){
      i = 0;
      x = -1;
      y = -1;
      while (i < puzzle_getNPoints(puzzle)){
        c = fgetc(fp);
        if (c >= '0' && c <= '9'){
            digitCount = 0;
            while (c >= '0' && c <= '9'){
              buffer[digitCount++] = c;
              c = fgetc(fp);
            }
            if (x == -1)
              sscanf(buffer, "%d", &x);
            else{
              sscanf(buffer, "%d", &y);
              puzzle_setTouristicPoint(puzzle, i, x, y);
              x = -1;
              y = -1;
              i++;
            }
            memset(buffer, 0, 64);
        }
      }
        
        i = 0;
        while (i < vec_x(puzzle_getCityDimensions(puzzle))){
          j = 0;
          while (j < vec_y(puzzle_getCityDimensions(puzzle))){
            c = fgetc(fp);
            if (c >= '0' && c <= '9'){
              digitCount = 0;
              while (c >= '0' && c <= '9'){
                buffer[digitCount++] = c;
                c = fgetc(fp);
              }
              sscanf(buffer, "%d", &x);
              puzzle_setCityMapTile(puzzle, i, j, x);
              memset(buffer, 0, 64);
              j++;
            }
          }
          i++;
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