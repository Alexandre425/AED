#include "solution.h"

vec* possibleMoves[8];

/******************************************************************************
 * solution_solvePuzzleBox()
 *
 * Arguments:   box - the puzzle box
 *
 * Description: solves all the puzzles in the puzzle box;
 *****************************************************************************/
void solution_solvePuzzleBox(puzzlesBox* box){
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

    for (i = 0; i < puzzle_getNPuzzles(box); i++){
        puzzle = puzzle_getPuzzleFromBox(box, i);
        switch (puzzle_getProblemType(puzzle)){
            case 'A':
                solution_problemA(puzzle);
                break;
            case 'B':
                solution_problemB(puzzle);
                break;
        }
    }

    for (i = 0; i < 8; i++)
        free(possibleMoves[i]);
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
void solution_problemA(puzzleInfo* puzzle){
    char* solution;
    int i = 0;
    vec* sum = vec_create(0, 0);

    for(i = 0; i < 8; i++){
        vec_sum(sum, puzzle_getTouristicPoints(puzzle), possibleMoves[i]);
        if(1 == /*por criar*/puzzle_validatePoint(puzzle, sum)){
            puzzle_getTileCost(puzzle, sum);
        }                     
    }        

    
}

/******************************************************************************
 * solution_problemB()
 *
 * Arguments:   puzzle - puzzle to solve
 * 
 * Description: solves a puzzle of the 'B' problem type
 *****************************************************************************/
void solution_problemB(puzzleInfo* puzzle){

}

