#include "solution.h"

vec *possibleMoves[8];

typedef struct vertex
{
  bool outOfQueue;
  int parent;
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
  int changedNothing = 1;
  vec *sum = vec_create(0, 0);
  vec *point = vec_idxToVec(puzzle_getCityDimensions(puzzle), idx);
  vec *dim = puzzle_getCityDimensions(puzzle);
  int pointCost = heap_getPriority(*priorityQueue, idx);

  // if the point is not out of bounds or inaccessible
  if (solution_checkBounds(puzzle, point) == 0 &&
      puzzle_getTileCost(puzzle, point) != 0)
  {
    // get all its neighbours
    for (int i = 0; i < 8; i++)
    {
      vec_sum(sum, point, possibleMoves[i]);
      int sumNode = vec_vecToIdx(dim, sum);
      int pointNode = idx;
      // check their bounds and accesibility again
      if (solution_checkBounds(puzzle, sum) == 0 &&
          (newCost = puzzle_getTileCost(puzzle, sum)) != 0)
      {
        // if the point made no past changes (meaning its a dead end)
        if (dij[sumNode] == MADE_NO_CHANGE)
        {
        }
        // if the neighbour is not in the queue (pointer is NULL)
        else if (dij[sumNode] == NOT_IN_QUEUE)
        {
          changedNothing = 0;
          dij[sumNode] = calloc_check(1, sizeof(vertex_t));

          dij[sumNode]->parent = pointNode;                           // set its parent
          newCost = newCost + pointCost; // set its cost
          dij[sumNode]->outOfQueue = false;                           // set the queue condition

          *priorityQueue = heap_put(*priorityQueue, sumNode, newCost); // put it in the queue
        }
        // if it is in the queue already (and hasn't left already)
        // and the cost from the current parent is lower that the registered cost
        else if (dij[sumNode]->outOfQueue == false &&
                 newCost + pointCost < heap_getPriority(*priorityQueue, sumNode))
        {
          changedNothing = 0;

          dij[sumNode]->parent = pointNode;                    // set its new parent
          newCost = newCost + pointCost;                      // set its new cost

          heap_update(*priorityQueue, sumNode, newCost); // update the queue
        }
      }
    }
    // if a point introduced nothing new to the SPT or queue
    if (changedNothing == 1)
    {
      free(dij[idx]);
      dij[idx] = MADE_NO_CHANGE;
    }
  }

  free(sum);
  free(point);
}

/******************************************************************************
 * solution_storePath()
 *
 * Arguments:   puzzle - puzzle to solve
 *              dij - the dijkstra auxiliary struct
 *              idx - destination node
 *              stack - where the path is stored
 * 
 * Description: store a path between two points
 *****************************************************************************/
stack_t *solution_storePath(puzzleInfo *puzzle, vertex_t **dij, int idx)
{
  vec *dim = puzzle_getCityDimensions(puzzle);
  stack_t *stack = stack_init();
  while (dij[idx]->parent != -1)
  {
    stack = stack_put(stack, vec_idxToVec(dim, idx));
    puzzle_setPathSteps(puzzle, puzzle_getPathSteps(puzzle) + 1);
    idx = dij[idx]->parent;
  }
  return stack;
}

/******************************************************************************
 * solution_printPath()
 *
 * Arguments:   puzzle - puzzle to solve
 *              stack - where the path is stored
 *              fp - the file to print in
 * 
 * Description: prints the shortest path for the problem
 *****************************************************************************/
void solution_printPath(puzzleInfo *puzzle, stack_t *path, FILE *fp)
{
  vec *pathStep;
  while (path != NULL)
  {
    path = stack_get(path, (void *)&pathStep);
    fprintf(fp, "%d %d %d\n",
            vec_x(pathStep),
            vec_y(pathStep),
            puzzle_getTileCost(puzzle, pathStep));

    free(pathStep);
  }
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
bool solution_dijkstra(puzzleInfo *puzzle, vec *start, vec *end, vertex_t **dij)
{
  bool pathExists = false;
  vec *dim = puzzle_getCityDimensions(puzzle);

  // initializing a priority queue
  heap_t *priorityQueue = heap_initHeap(vec_x(dim) * vec_y(dim));
  int startNode, endNode, node, cost;
  // initializing the cost array and path tree
  startNode = vec_vecToIdx(dim, start);
  endNode = vec_vecToIdx(dim, end);

  dij[startNode] = calloc_check(1, sizeof(vertex_t));

  cost = 0;                           // set the starting node's cost to zero
  dij[startNode]->outOfQueue = false; // set the queue condition
  dij[startNode]->parent = -1;        // setting it as root
  // put the starting node in the queue
  priorityQueue = heap_put(priorityQueue, startNode, cost);
  // while the queue is not empty
  while (heap_getCount(priorityQueue) != 0)
  {
    node = heap_get(priorityQueue); // get the element with highest priority
    dij[node]->outOfQueue = true;   // set it as being out of the queue
    // path found condition
    if (node == endNode)
    {
      pathExists = true;
      puzzle_setPathCost(puzzle, puzzle_getPathCost(puzzle)+ heap_getPriority(priorityQueue, node));
      break;
    }
    // put its neighbours in the queue and update it
    solution_updateQueue(puzzle, node, dij, &priorityQueue);
  }

  heap_free(priorityQueue);
  return pathExists;
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

  stack_t *path = NULL;

  vertex_t **dij = calloc_check(vec_x(dim) * vec_y(dim), sizeof(vertex_t *));

  bool pathExists = solution_dijkstra(puzzle, start, end, dij);
  if (pathExists == true)
    path = solution_storePath(puzzle, dij, vec_vecToIdx(dim, end));
  else
  {
    puzzle_setPathCost(puzzle, -1);
    puzzle_setPathSteps(puzzle, 0);
  }

  fprintf(fp, "%d %d %c %d %d %d\n",
          vec_x(puzzle_getCityDimensions(puzzle)),
          vec_y(puzzle_getCityDimensions(puzzle)),
          puzzle_getProblemType(puzzle),
          puzzle_getNPoints(puzzle),
          puzzle_getPathCost(puzzle),
          puzzle_getPathSteps(puzzle));

  if (pathExists == true)
    solution_printPath(puzzle, path, fp);
  fprintf(fp, "\n");

  for (int i = 0; i < vec_x(dim) * vec_y(dim); i++)
    if (dij[i] != NULL && dij[i] != MADE_NO_CHANGE)
      free(dij[i]);

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
  stack_t **path = calloc_check(puzzle_getNPoints(puzzle) - 1, sizeof(stack_t *));

  bool pathExists;

  vec *dim = puzzle_getCityDimensions(puzzle);
  vertex_t **dij = calloc_check(vec_x(dim) * vec_y(dim), sizeof(vertex_t *));
  for (int i = 1; i < puzzle_getNPoints(puzzle); i++)
  {
    vec *start = puzzle_getTouristicPoint(puzzle, i - 1);    // the source
    vec *end = puzzle_getTouristicPoint(puzzle, i);          // the destination
    pathExists = solution_dijkstra(puzzle, start, end, dij); // apply dijkstra from start to end

    if (pathExists == false) // if one of the paths doesn't exist
      break;

    path[i - 1] = solution_storePath(puzzle, dij, vec_vecToIdx(dim, end)); // store the path

    for (int i = 0; i < vec_x(dim) * vec_y(dim); i++)
    {
      if (dij[i] != NULL && dij[i] != MADE_NO_CHANGE)
        free(dij[i]);
      dij[i] = NULL;
    }
  }
  if (pathExists == false)
  {
    for (int i = 1; i < puzzle_getNPoints(puzzle); i++)
      stack_free(path[i - 1], free);
    puzzle_setPathCost(puzzle, -1);
    puzzle_setPathSteps(puzzle, 0);
  }

  fprintf(fp, "%d %d %c %d %d %d\n",
          vec_x(puzzle_getCityDimensions(puzzle)),
          vec_y(puzzle_getCityDimensions(puzzle)),
          puzzle_getProblemType(puzzle),
          puzzle_getNPoints(puzzle),
          puzzle_getPathCost(puzzle),
          puzzle_getPathSteps(puzzle));

  if (pathExists == true)
  {
    for (int i = 1; i < puzzle_getNPoints(puzzle); i++)
      solution_printPath(puzzle, path[i - 1], fp);
  }
  fprintf(fp, "\n");

  free(dij);
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
