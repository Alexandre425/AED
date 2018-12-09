/******************************************************************************
 *
 * File Name: utils.c
 *
 * Authors:    Alexandre Rodrigues
 *             Aprígio Malveiro
 *
 *  NAME
 *    utils - varied utilities
 *
 *  DESCRIPTION
 *		Implements simple, utilitarian functions like allocation wrappers
 *
 *****************************************************************************/

#include "utils.h"

void *calloc_check(int n_memb, size_t s_memb){
  void *ptr = calloc(n_memb, s_memb);
  if (ptr == NULL)
    exit(0);
  return ptr;
}
void *malloc_check(int n_memb, size_t s_memb){
  void *ptr = malloc(n_memb * s_memb);
  if (ptr == NULL)
    exit(0);

  return ptr;
}