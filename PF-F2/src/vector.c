#include "vector.h"

typedef struct _vec
{
  int x;
  int y;
} vec;

#define sqr(a) ((a) * (a))

/******************************************************************************
 * vec_x()
 *
 * Arguments:   v - vector
 * Returns: the x coordinate of the vector 
 *****************************************************************************/
int vec_x(vec *v)
{
  return v->x;
}

/******************************************************************************
 * vec_y()
 *
 * Arguments:   v - vector
 * Returns: the y coordinate of the vector 
 *****************************************************************************/
int vec_y(vec *v)
{
  return v->y;
}

/******************************************************************************
 * vec_sum()
 *
 * Arguments:   s - the sum vector (a + b)
 *              a - vector
 *              b - vector
 * Side-Effects: changes the values of s
 *
 * Description: calculates the sum of the vectors a and b. puts the result in s
 *
 *****************************************************************************/
void vec_sum(vec *s, vec *a, vec *b)
{
  s->x = a->x + b->x;
  s->y = a->y + b->y;
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
vec *vec_create(int x, int y)
{
  vec *v = NULL;
  v = calloc(1, sizeof(vec));
  if (v == NULL)
  {
    exit(0);
  }
  v->x = x;
  v->y = y;
  return v;
}

/******************************************************************************
 * vec_set()
 *
 * Arguments:   v - vector
 *              x - x coordinate
 *              y - y coordinate
 *
 * Description: sets a vector's coordinates to the given coordinates
 *
 *****************************************************************************/
void vec_set(vec *v, int x, int y)
{
  v->x = x;
  v->y = y;
}

/******************************************************************************
 * vec_dist_squared()
 *
 * Arguments:   v - vector
 *              u - vector
 * Returns: squared distance between vectors
 *
 * Description: gets the squared distance between two vectors
 *
 *****************************************************************************/
int vec_dist_squared(vec *v, vec *u)
{
  return (sqr(v->x - u->x) + sqr(v->y - u->y));
}

/******************************************************************************
 * vec_cmp()
 *
 * Arguments:   v - vector
 *              u - vector
 * Returns: 0 - vectors are equal
 *          -1 - vectors are not equal
 *
 * Description: compares two vectors to determine if they are equal
 *
 *****************************************************************************/
int vec_cmp(vec *v, vec *u)
{
  if (v->x == u->x && v->y == u->y)
    return 0;
  else
    return -1;
}
/******************************************************************************
 * vec_idxToVec
 *
 * Arguments:   dim - dimension vector
 *              idx - node index
 * Returns:     v - position vector
 *
 * Description: translates a node index to a position vector
 *
 *****************************************************************************/
vec* vec_idxToVec(vec *dim, int idx)
{
  return vec_create(idx/dim->y, idx%dim->y);
}

/******************************************************************************
 * vec_vecToIdx
 *
 * Arguments:   dim - dimension vector
 *              v - position vector
 * Returns:     idx - node index
 *
 * Description: translates a position vector to a node index
 *
 *****************************************************************************/
int vec_vecToIdx(vec *dim, vec *v)
{
  return ((v->x * dim->y) + v->y);
}