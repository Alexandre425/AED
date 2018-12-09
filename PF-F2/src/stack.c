/******************************************************************************
 *
 * File Name: stack.c
 *
 * Authors:    Alexandre Rodrigues
 *             Aprígio Malveiro
 *
 *  NAME
 *    stack - stack implementation
 *
 *  DESCRIPTION
 *		Implements functions to create and manipulate (FILO) stacks of pointers
 *
 *****************************************************************************/


#include "stack.h"

typedef struct _stack
{
  Item thing;
  stack_t *next;
} stack;

/******************************************************************************
 * stack_init()
 *
 * Returns: a new stack
 * 
 * Description: initializes a new stack
 *
 *****************************************************************************/
stack_t *stack_init(void)
{
  return NULL;
}

/******************************************************************************
 * arguments_check()
 *
 * Arguments:   argc - argument count
 *              argv - argument vector
 *
 * Description: check if the program was ran correctly
 *
 *****************************************************************************/
void stack_free(stack_t *stack, void (*free_function)(Item))
{
  stack_t *aux;
  while (stack != NULL)
  {
    aux = stack;
    stack = stack->next;
    free_function(aux->thing);
    free(aux);
  }
}

/******************************************************************************
 * arguments_check()
 *
 * Arguments:   argc - argument count
 *              argv - argument vector
 *
 * Description: check if the program was ran correctly
 *
 *****************************************************************************/
stack_t *stack_put(stack_t *stack, Item thing)
{
  stack_t *new = calloc_check(1, sizeof(stack_t));

  new->next = stack;
  new->thing = thing;
  return new;
}

/******************************************************************************
 * arguments_check()
 *
 * Arguments:   argc - argument count
 *              argv - argument vector
 *
 * Description: check if the program was ran correctly
 *
 *****************************************************************************/
stack_t *stack_get(stack_t *stack, Item *thing)
{
  if (stack != NULL)
  {
    *thing = stack->thing;
    stack_t *newStack = stack->next;
    free(stack);
    return newStack;
  }
  else
  {
    return NULL;
  }
}