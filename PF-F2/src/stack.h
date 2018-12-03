#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

typedef void *Item;
typedef struct _stack stack_t;

// init and free
stack_t *stack_init(void);
void stack_free(stack_t *stack, void (*free_function)(Item));

// put and get
stack_t *stack_put(stack_t *stack, Item thing);
stack_t *stack_get(stack_t *stack, Item *thing);