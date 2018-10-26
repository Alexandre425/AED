#include "solution.h"

vec* possibleMoves[8];

/******************************************************************************
 * solution_solvePuzzleBox()
 *
 * Arguments:   box - the puzzle box
 *
 * Description: solves all the puzzles in the puzzle box;
 *****************************************************************************/
void solution_solvePuzzleBox(puzzlesBox* box, char* argv[]){
    int i;

    puzzleInfo* puzzle = NULL;
    possibleMoves[0] = vec_create( 1, 2);
    possibleMoves[1] = vec_create( 1,-2);
    possibleMoves[2] = vec_create(-1, 2);
    possibleMoves[3] = vec_create(-1,-2);
    possibleMoves[4] = vec_create( 2, 1);
    possibleMoves[5] = vec_create( 2,-1);
    possibleMoves[6] = vec_create(-2, 1);
    possibleMoves[7] = vec_create(-2,-1);

    FILE* fp = NULL;
    char* token;
    char* fileName;
    token = strtok(argv[1], ".");
    fileName = strcat(token, ".valid");
    fp = fopen(fileName, "w");
    if (fp == NULL){
        printf("File could not be opened\n");
        exit(-1);
    }

    for (i = 0; i < puzzle_getNPuzzles(box); i++){
        puzzle = puzzle_getPuzzleFromBox(box, i);
        switch (puzzle_getProblemType(puzzle)){
            case 'A':
                solution_problemA(puzzle, fp);
                break;
            case 'B':
                solution_problemB(puzzle, fp);
                break;
        }
    }

    for (i = 0; i < 8; i++)
        free(possibleMoves[i]);
    fclose(fp);
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
int solution_checkBounds(puzzleInfo* puzzle, vec* pos){
    int x = vec_x(puzzle_getCityDimensions(puzzle)) - 1;
    int y = vec_y(puzzle_getCityDimensions(puzzle)) - 1;
    if (vec_x(pos) <= x && vec_x(pos) >= 0 && vec_y(pos) <= y && vec_y(pos) >= 0)
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
void solution_problemA(puzzleInfo* puzzle, FILE* fp){
    char solution[64];
    int i = 0;
    int bestCost = 0, cost = 0;
    int solutionExists = -1;

    vec* sum = vec_create(0, 0);

    for (i = 0; i < 8; i++){
        vec_sum(sum, puzzle_getTouristicPoint(puzzle, 0), possibleMoves[i]);
        if (0 == solution_checkBounds(puzzle, sum)){
            cost = puzzle_getTileCost(puzzle, sum);
            if (cost != 0){
                if (bestCost == 0)
                    bestCost = cost;
                else if (bestCost > cost)
                    bestCost = cost;
            }                
        }     
    } 

    if (bestCost != 0)
        solutionExists = 1;

    sprintf(solution, "%d %d %c %d %d %d\n\n", 
        vec_x(puzzle_getCityDimensions(puzzle)),
        vec_y(puzzle_getCityDimensions(puzzle)),
        puzzle_getProblemType(puzzle),
        puzzle_getNPoints(puzzle),
        solutionExists,
        bestCost
        );

    file_writeSolution(solution, fp);
}

/******************************************************************************
 * solution_problemB()
 *
 * Arguments:   puzzle - puzzle to solve
 * 
 * Description: solves a puzzle of the 'B' problem type
 *****************************************************************************/
void solution_problemB(puzzleInfo* puzzle, FILE* fp){

}
/******************************************************************************
 * solution_convertIntChar()
 *
 * Arguments:   number and a string pointer 
 * 
 * Description: turn an int into a string
 *****************************************************************************/
char* solution_convertIntChar(int number){
    int strSize = 0;
    int i = 0;
    char* nstring = NULL;
    while(number/10 !=0){
        strSize++;
    }
    if(strSize != 0);
    nstring = calloc(strSize+1,sizeof(char));
    nstring[strSize] = '\0';
    for(i = strSize-1; i >= 0; i++){
        nstring[i] = number % 10;
        number = number / 10;
    }
    return nstring; 
}
