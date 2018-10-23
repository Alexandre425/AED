#include "puzzle.h"


typedef struct _puzzleInfo{
    char problemType;
    int nPoints;
    vec *cityDimensions;
    vec **touristicPoints;
    short **cityMap;
}puzzleInfo;

typedef struct _puzzlesBox{
    int nPuzzles;
    puzzleInfo **puzzles;
}puzzlesBox;

/******************************************************************************
 * puzzle_initPuzzlesBox()
 *
 * Arguments:
 * Returns: puzzlesBox* 
 * Side-Effects:
 *
 * Description: initializes the puzzle box
 *
 *****************************************************************************/
puzzlesBox* puzzle_initPuzzlesBox(){
    puzzlesBox *box = NULL;

    box = calloc(1,sizeof(puzzlesBox));
    if (box == NULL )
        printf("Memory allocation error!\n");
        exit(0);

    box->nPuzzles = 0;
    box->puzzles = NULL;

    return box;
}

/******************************************************************************
 * puzzle_initPuzzle()
 *
 * Arguments:
 * Returns: puzzleInfo* 
 * Side-Effects:
 *
 * Description:
 *
 *****************************************************************************/
puzzleInfo* puzzle_initPuzzle(){
    puzzleInfo *puzzle = NULL;
   
    puzzle = calloc(1,sizeof(puzzleInfo));
    if (puzzle == NULL)
        printf("Memory allocation error!\n");
        exit(0);
    
    return puzzle;
} 

/******************************************************************************
 * puzzle_storePuzzle()
 *
 * Arguments: puzzleInfo* puzzle ; puzzlesBox* box
 * Returns: 
 * Side-Effects: reallocates box->puzzle 
 *               puzzles become null 
 *
 * Description: store a puzzle in the box
 *
 *****************************************************************************/
void puzzle_storePuzzle(puzzleInfo* puzzle, puzzlesBox* box){

    box->nPuzzles++;

    box->puzzles = realloc(box->puzzles,(box->nPuzzles)*sizeof(puzzleInfo*));
    if (box->puzzles == NULL )
        printf("Memory allocation error!\n");
        exit(0);
    box->puzzles[box->nPuzzles-1] = puzzle;
}

/******************************************************************************
 * puzzle_freePuzzle()
 *
 * Arguments:puzzleInfo* puzzle
 * Returns: puzzleInfo* 
 * Side-Effects: return NULL
 *
 * Description: free all the information in the Puzzles
 *
 *****************************************************************************/
puzzleInfo* puzzle_freePuzzle(puzzleInfo* puzzle){
    int i = 0;
    if (puzzle->touristicPoints != NULL){
        for(i = 0; i < puzzle->nPoints; i++){
        free(puzzle->touristicPoints[i]);
        }
        free(puzzle->touristicPoints);
    }
    if (puzzle->cityMap != NULL){
        for(i = 0; i < vec_x(puzzle->cityDimensions); i++){
            free(puzzle->cityMap[i]);
        }
        free(puzzle->cityMap);
    }
    free(puzzle);
    return NULL;
}

/******************************************************************************
 * puzzle_freePuzzlesBox()
 *
 * Arguments:puzzlesBox* box
 * Returns: puzzlesBox* 
 * Side-Effects: return NULL
 *               free all the puzzles inside
 *
 * Description: free all the information in the BoX
 *
 *****************************************************************************/
puzzlesBox* puzzle_freePuzzlesBox(puzzlesBox* box){
    int i = 0;
    if(box == NULL)
        return NULL;
    if (box->puzzles != NULL){
        for(i = 0; i < box->nPuzzles; i++ ){
            box->puzzles[i]=free_puzzle(box->puzzles[i]);
        }
        free(box->puzzles);
    }
    free(box);
    return NULL;
}

/******************************************************************************
 * SETTING FUNCTIONS
 *
 * Arguments: variable to be set
 * Returns: 
 *
 * Description: sets a variable in a structure to the 
 *
 *****************************************************************************/

