#include "vector.h"

typedef struct _vec{
    int x;
    int y;
};

/******************************************************************************
 * vec_x()
 *
 * Arguments:   v - vector
 * Returns: the x coordinate of the vector 
 *****************************************************************************/
int vec_x(vec *v){
    return v->x;
}

/******************************************************************************
 * vec_y()
 *
 * Arguments:   v - vector
 * Returns: the y coordinate of the vector 
 *****************************************************************************/
int vec_y(vec *v){
    return v->y;
}

/******************************************************************************
 * vec_create()
 *
 * Arguments:   x - x coordinate
 *              y - y coordinate
 * Returns: the (x, y) vector
 * Side-Effects: allocates a new vector
 *
 * Description: creates a new vector with the given coordinates
 *
 *****************************************************************************/
vec* vec_create(int x, int y){
    vec* v = NULL;
    v = calloc(1, sizeof(vec));
    if (v == NULL){
        printf("Memory allocation error!\n");
        exit(0);
    }
    v->x = x;
    v->y = y;
    return v;
}