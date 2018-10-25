#include "file_manager.h"

puzzlesBox* file_readPuzzles(char *argv[]){
    
    FILE *fp = NULL;
    char buffer[1024];
    int i = 0, j = 0;
    puzzleInfo *puzzle = NULL; 
    puzzlesBox *box =NULL;
    
    fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("Cannot open file!\n");
        exit(0);
    }
    box = puzzle_initPuzzlesBox();
    puzzle = puzzle_initPuzzle();

    while (fgets(buffer, 1024, fp) != NULL){
        int x = -1, y = -1, nPoints = -1;
        char problemType = '\0';
        sscanf(buffer,"%d %d %c %d", &x, &y, &problemType, &nPoints);
        puzzle_setCityDimensions(puzzle, x, y);
        puzzle_setProblemType(puzzle, problemType);
        puzzle_setNPoints(puzzle, nPoints);
        
        if (0 == puzzle_paremetersCheck(puzzle)){
            
            for (i = 0; i < puzzle_getNPoints(puzzle); i++){
                fgets(buffer, 1024, fp);
                sscanf(buffer,"%d %d", &x, &y);
                puzzle_setTouristicPoint(puzzle, i, x, y);
            }
            for (i = 0; i < vec_x(puzzle_getCityDimensions(puzzle)); i++){
                char* token = NULL;
                fgets(buffer, 1024, fp);
                token = strtok(buffer, " ");
                for (j = 0; token != NULL; j++){
                    puzzle_setCityMapTile(puzzle, i, j, (short)atoi(token));
                    token = strtok(NULL, " ");
                }
            }
            
            puzzle_storePuzzle(puzzle,box);
            puzzle = puzzle_initPuzzle();           
        }
    }

    fclose(fp);
    puzzle_freePuzzle(puzzle);
    return box;
}

void file_writeSolution(FILE *fp, puzzlesBox* box){


}