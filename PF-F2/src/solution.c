#include "solution.h"

vec *possibleMoves[8];

typedef struct vertex
{
  bool outOfQueue;
  int parent;
  int cost;
} vertex_t;

/******************************************************************************
 * solution_init()
 *
 * Description: initializes useful resources for puzzle resolution
 *****************************************************************************/
FILE *solution_init(char *argv[])
{
  // vector of all the moves (relative to it's current pos) a horse piece can make
  possibleMoves[0] = vec_create(1, 2);
  possibleMoves[1] = vec_create(1, -2);
  possibleMoves[2] = vec_create(-1, 2);
  possibleMoves[3] = vec_create(-1, -2);
  possibleMoves[4] = vec_create(2, 1);
  possibleMoves[5] = vec_create(2, -1);
  possibleMoves[6] = vec_create(-2, 1);
  possibleMoves[7] = vec_create(-2, -1);

  // creating the output file
  FILE *fp = NULL;
  char *token;
  char *fileName;
  token = strtok(argv[1], ".");
  fileName = strcat(token, ".walks");
  fp = fopen(fileName, "w");
  if (fp == NULL)
    exit(0);

  return fp;
}

/******************************************************************************
 * solution_free()
 *
 * Description: cleans up the allocated resources for puzzle resolution
 *****************************************************************************/
void solution_free(FILE *fp)
{
  for (int i = 0; i < 8; i++)
    free(possibleMoves[i]);

  fclose(fp);
}

/******************************************************************************
 * solution_solvePuzzleBox()
 *
 * Arguments:   box - the puzzle box
 *
 * Description: solves all the puzzles in the puzzle box;
 *****************************************************************************/
void solution_solvePuzzle(puzzleInfo *puzzle, FILE *fpout)
{
  char solution[128];

  if (puzzle_getValidity(puzzle) == 1)
  {
    sprintf(solution, "%d %d %c %d %d %d\n\n",
            vec_x(puzzle_getCityDimensions(puzzle)),
            vec_y(puzzle_getCityDimensions(puzzle)),
            puzzle_getProblemType(puzzle),
            puzzle_getNPoints(puzzle),
            -1, // puzzle is invalid
            0); // cost is zero as a result
    file_writeSolution(solution, fpout);
  }
  else
    switch (puzzle_getProblemType(puzzle))
    {
    case 'A':
      solution_problemA(puzzle, fpout);
      break;
    case 'B':
      solution_problemB(puzzle, fpout);
      break;
    case 'C':
      solution_problemC(puzzle, fpout);
      break;
    }
}

/******************************************************************************
 * solution_checkBounds()
 *
 * Arguments:   puzzle - the puzzle containing the map in question
 *              pos - the position to check
 * Returns:     -1 - position is out of bounds
 *              0 - position is in bounds
 * 
 * Description: verifies if the position vector given is in bounds relative to the city map
 *****************************************************************************/
int solution_checkBounds(puzzleInfo *puzzle, vec *pos)
{
  int x = vec_x(puzzle_getCityDimensions(puzzle));
  int y = vec_y(puzzle_getCityDimensions(puzzle));
  if (vec_x(pos) < x && vec_x(pos) >= 0 && vec_y(pos) < y && vec_y(pos) >= 0)
    return 0;
  else
    return -1;
}

/******************************************************************************
 * solution_getNeighbours()
 *
 * Arguments:   puzzle - puzzle to solve
 *              idx - index of the node whose neighbours to get
 *              dij - the auxiliary dijkstra struct
 *              h - the priority queue
 * 
 * Description: gets idx's neighbours, puts them in the queue or updates them
 *              with new parents and costs (basically performs part of 
 *              dijkstra's algorithm)
 *****************************************************************************/
void solution_updateQueue(puzzleInfo *puzzle, int idx, vertex_t **dij, heap_t **priorityQueue)
{
  int newCost;
  vec *sum = vec_create(0, 0);
  vec *point = vec_idxToVec(puzzle_getCityDimensions(puzzle), idx);
  vec *dim = puzzle_getCityDimensions(puzzle);

  // if the point is not out of bounds or inaccessible
  if (solution_checkBounds(puzzle, point) == 0 &&
      puzzle_getTileCost(puzzle, point) != 0)
  {
    // get all its neighbours
    for (int i = 0; i < 8; i++)
    {
      vec_sum(sum, point, possibleMoves[i]);
      int sumNode = vec_vecToIdx(dim, sum);
      int pointNode = vec_vecToIdx(dim, point);
      // check their bounds and accesibility again
      if (solution_checkBounds(puzzle, sum) == 0 &&
          (newCost = puzzle_getTileCost(puzzle, sum)) != 0)
      {
        // if the neighbour is not in the queue (pointer is NULL)
        if (dij[sumNode] == NOT_IN_QUEUE)
        {
          dij[sumNode] = calloc(1, sizeof(vertex_t));
          if (dij[sumNode] == NULL)
            exit(0);
          dij[sumNode]->parent = pointNode;                                   // set its parent
          dij[sumNode]->cost = newCost + dij[pointNode]->cost;                // set its cost
          dij[sumNode]->outOfQueue = false;                                   // set the queue condition
          *priorityQueue = heap_put(*priorityQueue, idx, dij[sumNode]->cost); // put it in the queue
        }
        // if it is in the queue already (and hasn't left already)
        // and the cost from the current parent is lower that the registered cost
        else if (dij[sumNode]->outOfQueue == false &&
                 newCost + dij[pointNode]->cost < dij[sumNode]->cost)
        {
          dij[sumNode]->parent = pointNode;                     // set its new parent
          dij[sumNode]->cost = newCost + dij[pointNode]->cost;  // set its new cost
          heap_update(*priorityQueue, idx, dij[sumNode]->cost); // update the queue
        }
      }
    }
  }
  free(sum);
  free(point);
}

/******************************************************************************
 * solution_dijksrta()
 *
 * Arguments:   puzzle - puzzle to solve
 *              cost - cost of each graph node
 *              st - shortest path tree
 * 
 * Description: solves a puzzle of the 'A' problem type
 *****************************************************************************/
void solution_dijkstra(puzzleInfo *puzzle, vec *start, vec *end, vertex_t **dij)
{
  // initializing a priority queue
  heap_t *priorityQueue = heap_initHeap();
  int startNode, endNode, node;

  // initializing the cost array and path tree
  vec *dim = puzzle_getCityDimensions(puzzle);
  startNode = vec_vecToIdx(dim, start);
  endNode = vec_vecToIdx(dim, end);

  dij[startNode] = calloc(1, sizeof(vertex_t));
  if (dij[startNode] == NULL)
    exit(0);

  dij[startNode]->cost = 0;           // set the starting node's cost to zero
  dij[startNode]->outOfQueue = false; // set the queue condition
  dij[startNode]->parent = -1;        // setting it as root
  // put the starting node in the queue
  priorityQueue = heap_put(priorityQueue, startNode, dij[startNode]->cost);
  // while the queue is not empty
  while (heap_getCount(priorityQueue) != 0)
  {
    node = heap_get(priorityQueue); // get the element with highest priority
    dij[node]->outOfQueue = true;   // set it as being out of the queue
    // path found condition
    if (node == endNode)
      break;
    // put its neighbours in the queue and update it
    solution_updateQueue(puzzle, node, dij, &priorityQueue);
  }
}

/******************************************************************************
 * solution_problemA()
 *
 * Arguments:   puzzle - puzzle to solve
 * 
 * Description: solves a puzzle of the 'A' problem type
 *****************************************************************************/
void solution_problemA(puzzleInfo *puzzle, FILE *fp)
{
  vec *start = puzzle_getTouristicPoint(puzzle, 0);
  vec *end = puzzle_getTouristicPoint(puzzle, 1);
  vec *dim = puzzle_getCityDimensions(puzzle);

  vertex_t **dij = calloc(vec_x(dim) * vec_y(dim), sizeof(vertex_t *));
  if (dij == NULL)
    exit(0);

  solution_dijkstra(puzzle, start, end, dij);

  // WRITE SOLUTION HERE

  free(dij);
}

/******************************************************************************
 * solution_problemB()
 *
 * Arguments:   puzzle - puzzle to solve
 * 
 * Description: solves a puzzle of the 'B' problem type
 *****************************************************************************/
void solution_problemB(puzzleInfo *puzzle, FILE *fp)
{
}
/******************************************************************************
 * solution_problemC()
 *
 * Arguments:   puzzle - puzzle to solve
 * 
 * Description: solves a puzzle of the 'C' problem type
 *****************************************************************************/
void solution_problemC(puzzleInfo *puzzle, FILE *fp)
{
}
