#include "puzzle.h"

typedef struct _puzzleInfo{
    char problemType;
    int nPoints;
    vec *cityDimensions;
    vec **touristicPoints;
    short **cityMap;
    char* solution;
}puzzleInfo;

typedef struct _puzzlesBox{
    int nPuzzles;
    puzzleInfo **puzzles;
    vec* possibleMoves[8]
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
    if (box == NULL ){
        printf("Memory allocation error!\n");
        exit(0);
    }



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
    if (puzzle == NULL){
        printf("Memory allocation error!\n");
        exit(0);
    }
    puzzle->cityDimensions = vec_create(-1, -1);
    
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
    if (box->puzzles == NULL ){
        printf("Memory allocation error!\n");
        exit(0);
    }
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
    if (puzzle->cityMap != NULL){
        for(i = 0; i < vec_x(puzzle->cityDimensions); i++){
            free(puzzle->cityMap[i]);
        }
        free(puzzle->cityMap);
    }
    if(puzzle->cityDimensions != NULL){
        free(puzzle->cityDimensions);
    }
    if (puzzle->touristicPoints != NULL){
        for(i = 0; i < puzzle->nPoints; i++){
            free(puzzle->touristicPoints[i]);
        }
        free(puzzle->touristicPoints);
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
            box->puzzles[i]=puzzle_freePuzzle(box->puzzles[i]);
        }
        free(box->puzzles);
    }
    free(box);
    return NULL;
}
/******************************************************************************
 * puzzle_paremetersCheck()
 *
 * Arguments: puzzleInfo* puzzle
 * Returns: int
 * Side-Effects: allocates memory for the city and the touristic points of the puzzle
 *
 * Description: decide if the data stored inside the puzzle is valid
 *
 *****************************************************************************/
int puzzle_paremetersCheck(puzzleInfo* puzzle){
    int validation = 0;
    int i = 0;
    /*se os parametros da estrutura forem validos retorna 0 
    se invalidos, limpa os dados inseridos e retorna -1  */
    if(( puzzle->problemType!= 'A') && (puzzle->problemType!= 'B'))
        validation = -1;
    else if( puzzle->problemType == 'A'){
        if(puzzle->nPoints != 1)
            validation = -1;
    }
    else if( puzzle->problemType == 'B'){
        if( puzzle->nPoints < 2)
            validation = -1;
    }
    if(validation != -1){
        puzzle->touristicPoints = calloc(puzzle->nPoints,sizeof(vec**));
        if(puzzle->touristicPoints == NULL){
            printf("Memory allocation error!\n");
            exit(0);
        }
        for(i = 0; i < puzzle->nPoints; i++)
            puzzle->touristicPoints[i] = vec_create(-1,-1);
        
        puzzle->cityMap = calloc(vec_x(puzzle->cityDimensions),sizeof(short*));
        if( puzzle->cityMap == NULL){
            printf("Memory allocation error!\n");
            exit(0);
        }
        for(i = 0; i < vec_x(puzzle->cityDimensions); i++){
            puzzle->cityMap[i] = calloc(vec_y(puzzle->cityDimensions),sizeof(short));
            if(puzzle->cityMap[i] == NULL){
                printf("Memory allocation error!\n");
                exit(0);
            }
        }
        return 0;
    }
    puzzle->problemType = '\0';
    puzzle->nPoints = -1;
    vec_set(puzzle->cityDimensions, -1, -1);
    return -1;
}

/******************************************************************************
 * SETTING FUNCTIONS
 *
 * Arguments: variable to be set
 * Returns: 
 *
 * Description: sets a variable in a structure to the argument variable
 *
 *****************************************************************************/

void puzzle_setProblemType(puzzleInfo* puzzle, char type){
    puzzle->problemType = type;
}

void puzzle_setNPoints(puzzleInfo* puzzle, int n){
    puzzle->nPoints = n;
}

void puzzle_setCityDimensions(puzzleInfo* puzzle, int x, int y){
    vec_set(puzzle->cityDimensions, x, y);
}

void puzzle_setTouristicPoint(puzzleInfo* puzzle, int i, int x, int y){
    vec_set(puzzle->touristicPoints[i], x, y);
}

void puzzle_setCityMapTile(puzzleInfo* puzzle, int x, int y, short t){
    puzzle->cityMap[x][y] = t;
}

/******************************************************************************
 * GETTING FUNCTIONS
 *
 * Arguments: structure to get from
 * Returns: member from the structure
 *
 * Description: returns a member from the structure
 *
 *****************************************************************************/

char puzzle_getProblemType(puzzleInfo* puzzle){
    return puzzle->problemType;
}

int puzzle_getNPoints(puzzleInfo* puzzle){
    return puzzle->nPoints;
}

vec* puzzle_getCityDimensions(puzzleInfo* puzzle){
    return puzzle->cityDimensions;
}

vec* puzzle_getTouristicPoint(puzzleInfo* puzzle, int i){
    return puzzle->touristicPoints[i];
}

int puzzle_getTileCost(puzzleInfo* puzzle, vec* pos){
    return puzzle->cityMap[vec_x(pos)][vec_y(pos)];
}