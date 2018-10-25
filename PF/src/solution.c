#include "solution.h"

#define sum possibleMoves[8]

vec** possibleMoves[9];

vec** solution_allocPossibleMoves(void){
    possibleMoves[0] = vec_create(1, 2);
    possibleMoves[1] = vec_create(1, -2);
    possibleMoves[2] = vec_create(-1, 2);
    possibleMoves[3] = vec_create(-1, -2);
    possibleMoves[4] = vec_create(2, 1);
    possibleMoves[5] = vec_create(2, -1);
    possibleMoves[6] = vec_create(-2, 1);
    possibleMoves[7] = vec_create(-2, -1);
    possibleMoves[8] = vec_create(-1, -1);

}

void solution_problemA(puzzleInfo* puzzle){
    char* solution;
    int i = 0;
/* por inicializar variavel (que indica se a ou nao soluçao) para não haver solução */

    for(i = 0; i < 8; i++){
        vec_sum(sum, puzzle_getTouristicPoints(puzzle),possibleMoves[i]);
        if(1 == /*por criar*/puzzle_validatePoint(puzzle,sum)){
            puzzle_getTileCost(puzzle,sum); 
        }                     
    }        

    
}

void solution_problemB(puzzleInfo* puzzle){

}

