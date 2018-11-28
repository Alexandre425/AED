#include "heap.h"

typedef struct{
  Item thing;
  short priority;
}node;

typedef struct _heap{
  node *array;
  int heapSize;
  int heapCount;
}heap;

/******************************************************************************
 * heap_initHeap()
 *
 * Returns:     the newly allocated heap
 * 
 * Description: allocates a new heap
 *
 *****************************************************************************/
heap* heap_initHeap(void){
  heap *h = calloc(1, sizeof(heap)); if (h == NULL) exit(0);
  h->array = calloc(HEAP_SIZE, sizeof(node)); if (h->array == NULL) exit(0);
  h->heapSize = HEAP_SIZE;
  return h;
}

/******************************************************************************
 * heap_put()
 *
 * Arguments:   h - the heap to put the thing in
 *              thing - the thing to put in the heap
 * 
 * Description: puts the thing in the heap and fixes it
 *
 *****************************************************************************/
heap* heap_put(heap* h, Item thing, short priority){
  // putting and fixing
  h->array[h->heapCount].thing = thing;
  h->array[h->heapCount].priority = priority;
  heap_fixUp(h, h->heapCount);
  h->heapCount++;

  // checking the heap size
  return heap_checkSize(h);
}

/******************************************************************************
 * heap_get()
 *
 * Arguments:   h - the heap to put the thing in
 * Returns:     
 * 
 * Description: puts the thing in the heap and fixes it
 *
 *****************************************************************************/
Item heap_get(heap* h){
  Item thing = h->array[--h->heapCount].thing;
  heap_exch(h, 0, h->heapCount);
  heap_fixDown(h, 0);
  return thing;
}

/******************************************************************************
 * heap_checkSize()
 *
 * Arguments:   h - the heap
 *              
 * Description: reallocates the heap with 100 extra spaces if they are all
 *              in use (the item count equals the size)
 *
 *****************************************************************************/
heap* heap_checkSize(heap* h){
  if (h->heapCount == h->heapSize){
    h->heapSize += HEAP_SIZE;
    h->array = realloc(h->array, h->heapSize * sizeof(node)); if (h->array == NULL) exit(0);
  }
  return h;
}

/******************************************************************************
 * heap_exch()
 *
 * Arguments:   h - the heap
 *              i - index of the first node
 *              j - index of the second node
 *              
 * Description: exchanges two nodes in the heap
 *
 *****************************************************************************/

void heap_exch(heap* h, int i, int j){
  node tmp = h->array[i];
  h->array[i] = h->array[j];
  h->array[j] = tmp;
}

/******************************************************************************
 * heap_fixUp()
 *
 * Arguments:   h - the heap
 *              i - index of the node to start the fixing 
 *              
 * Description: fixes the heap going up from the supplied index
 *
 *****************************************************************************/
void heap_fixUp(heap* h, int i){
  while (i > 0 && !less(h->array[parent(i)].priority, h->array[i].priority)){
    heap_exch(h, parent(i), i);
    i = parent(i);
  }
}

/******************************************************************************
 * heap_fixDown()
 *
 * Arguments:   h - the heap
 *              i - index of the node to start the fixing 
 *              
 * Description: fixes the heap going up from the supplied index
 *
 *****************************************************************************/
void heap_fixDown(heap* h, int i){
  int idx = i;
  int child;
  while (idx * 2 < h->heapCount - 1){
    child = childL(idx);
    // if the right child has higher priority
    // ensures the highest priority node will ascend to the local root
    if (child < h->heapCount - 1 && less(h->array[child+1].priority, h->array[child].priority))
      child++;
    // if the heap condition is verified (parent has higher priority)
    if (less(h->array[idx].priority, h->array[child].priority))
      break;  // fix down is complete
    heap_exch(h, child, parent(child));
    idx = child;
  }
}

/******************************************************************************
 * heap_free()
 *
 * Arguments:   h - the heap
 *              
 * Description: frees the heap
 *
 *****************************************************************************/
void heap_free(heap* h){
  for (int i = 0; i < h->heapSize; i++)
    if (h->array[i].thing != NULL)
      free(h->array[i].thing);
  free(h->array);
  free(h);
}


void heap_debugPrint(heap* h){
  printf("Size:  %d\n", h->heapSize);
  printf("Count: %d\n", h->heapCount);
  for (int i = 0; i < h->heapCount; i++)
    printf("%d ", h->array[i].priority);
  printf("\n");
}