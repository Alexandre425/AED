#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct _vec vec;

/* get */
int vec_x(vec *vector);
int vec_y(vec *vector);

/* operate */
void vec_sum(vec *sum_vector, vec *vector_a, vec *vector_b);
int vec_dist_squared(vec *vector_a, vec *vector_b);
int vec_cmp(vec *vector_a, vec *vector_b);
vec* vec_idxToVec(vec *dim, int idx);
int vec_vecToIdx(vec *dim, vec *v);

/* set */
void vec_set(vec *vector, int x_coord, int y_coord);

/* init */
vec *vec_create(int x_coord, int y_coord);
