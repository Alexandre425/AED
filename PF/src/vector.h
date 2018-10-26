#include <stdio.h>
#include <stdlib.h>


typedef struct _vec vec;

/* get */
int vec_x(vec *vector);
int vec_y(vec *vector);
int vec_dist_squared(vec *vector_a, vec *vector_b);

/* operate */
void vec_sum(vec *vector_s, vec *vector_a, vec *vector_b);

/* set */
void vec_set(vec* vector, int x_coord, int y_coord);

/* init */
vec* vec_create(int x_coord, int y_coord);

