#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define HEAP_SIZE 100
#define childL(a) ((a*2)+1)
#define childR(a) ((a*2)+2)
#define parent(a) ((a-1)/2)
#define less(a, b) (a < b)

typedef struct _heap heap_t;
typedef void* Item;

// init and alloc
heap_t* heap_initHeap(void);
heap_t* heap_checkSize(heap_t* h);

// fix
void heap_fixDown(heap_t *h, int idx);
void heap_fixUp(heap_t *h, int idx);

// get
int heap_get(heap_t *h);
int heap_getCount(heap_t* h);

// put
heap_t* heap_put(heap_t *h, int nodeId, short priority);

// update
void heap_update(heap_t* h, int nodeId, short newPriority );

// utils
void heap_exch(heap_t* h, int i, int j);
void heap_debugPrint(heap_t* h);

// free
void heap_free(heap_t* h);
