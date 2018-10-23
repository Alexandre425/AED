/******************************************************************************
 * (c) 2010 AED
 * File Name: connectivity.c
 * Author:    AED Team
 * Last modified: lms 2018-09-18
 * Revision:  v20180918
 *
 * NAME
 *      connectivity - algorithms for solving the connectivity problem
 *
 * DESCRIPTION
 *      QF QU WQU CWQU, counts number of entry pairs and the number of links
 *      for each method.
 *
 * COMMENTS
 *
 *****************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#include "connectivity.h"

/******************************************************************************
 * link_print()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 * Returns: (void)
 * Side-Effects: 
 *
 * Description: prints the linked groups and group count in the id array
 *
 *****************************************************************************/
void link_print(int* id, int N){

  int i = 0, j = 0;
  int groupCount = 0;
  int* groupId = NULL;

  /* count the number of groups */
  for (i = 0; i < N; i++)
    if (id[i] == i)
      groupCount++;

  /*allocate an array with the indexes of the groups*/
  groupId = (int*)calloc(sizeof(int), groupCount+1);
  if (groupId == NULL){
    printf("ERROR: Not enought memmory\n");
    return;
  }

  for ( i = 0, j = 0; i < N; i++)
    if (id[i] == i)
      groupId[j++] = i;

  for ( i = 0; i < groupCount; i++){
    printf("\nID[%d]", groupId[i]);
    for ( j = 0; j < N; j++)
      if (id[j] == groupId[i])
        printf("-%d", j);
  }

  free(groupId);
  printf("\nNumber of groups: %d\n", groupCount);

}


/******************************************************************************
 * quick_find()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Find algorithm
 *
 *****************************************************************************/

void quick_find(int *id, int N, FILE * fp, int quietOut)
{
  int i, p, q, t;
  int pairs_cnt = 0;            /* connection pairs counter */
  int links_cnt = 0;            /* number of links counter */
  int findCount = 0, unionCount = 0;

  /* initialize; all disconnected */
  for (i = 0; i < N; i++)
    id[i] = i;

  /* read while there is data */
  while (fscanf(fp, "%d %d", &p, &q) == 2) {
    pairs_cnt++;
    /* do search first */
    findCount += 2;
    if (id[p] == id[q]) {
      /* already in the same set; discard */
      if (!quietOut)
        printf("\t%d %d\n", p, q);
      continue;
    }
    
    /* pair has new info; must perform union */
    unionCount++;
    for (t = id[p], i = 0; i < N; i++){
      unionCount++;
      if (id[i] == t){
        id[i] = id[q];
        unionCount += 2;
      }
  }
    links_cnt++;
    if (!quietOut)
      printf(" %d %d\n", p, q);
  }
  printf("QF: The number of links performed is %d for %d input pairs.\n",
         links_cnt, pairs_cnt);
  printf("PERF: Performed %d unions for %d finds. %d total.\n", unionCount, findCount, unionCount + findCount);

  if (quietOut == 0)
    link_print(id, N);
}


/******************************************************************************
 * quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Union algorithm
 *
 *****************************************************************************/

void quick_union(int *id, int N, FILE * fp, int quietOut)
{

  int i, j, p, q;
  int pairs_cnt = 0;            /* connection pairs counter */
  int links_cnt = 0;            /* number of links counter */
  long int findCount = 0, unionCount = 0;

  /* initialize; all disconnected */
  for (i = 0; i < N; i++)
    id[i] = i;

  /* read while there is data */
  while (fscanf(fp, "%d %d", &p, &q) == 2) {
    pairs_cnt++;
    i = p;
    j = q;

    /* do search first */
    findCount++;
    while (i != id[i]){
      i = id[i];
      findCount += 2;
    }
    findCount++;
    while (j != id[j]){
      j = id[j];
      findCount += 2;
    }

    if (i == j) {
      /* already in the same set; discard */
      if (!quietOut)
        printf("\t%d %d\n", p, q);
      continue;
    }

    /* pair has new info; must perform union */
    id[i] = j;
    links_cnt++;
    unionCount++;

    if (!quietOut)
      printf(" %d %d\n", p, q);
  }
  printf("QU: The number of links performed is %d for %d input pairs.\n",
         links_cnt, pairs_cnt);
  printf("PERF: Performed %ld unions for %ld finds. %ld total.\n", unionCount, findCount,(findCount+unionCount));
}


/******************************************************************************
 * weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Weighted Quick Union algorithm
 *
 *****************************************************************************/

void weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{

  int i, j, p, q;
  int *sz = (int *) malloc(N * sizeof(int));
  int pairs_cnt = 0;            /* connection pairs counter */
  int links_cnt = 0;            /* number of links counter */
  int findCount = 0, unionCount = 0;

  /* initialize; all disconnected */
  for (i = 0; i < N; i++) {
    id[i] = i;
    sz[i] = 1;
  }

  /* read while there is data */
  while (fscanf(fp, "%d %d", &p, &q) == 2) {
    pairs_cnt++;

    /* do search first */
    
    findCount++;
    for (i = p; i != id[i]; i = id[i])
      findCount += 2;
    findCount++;
    for (j = q; j != id[j]; j = id[j])
      findCount += 2;

    if (i == j) {
      /* already in the same set; discard */
      if (!quietOut)
        printf("\t%d %d\n", p, q);
      continue;
    }

    /* pair has new info; must perform union; pick right direction */
    unionCount += 2;
    if (sz[i] < sz[j]) {
      id[i] = j;
      unionCount += 3;
      sz[j] += sz[i];
    }
    else {
      id[j] = i;
      unionCount += 3;
      sz[i] += sz[j];
    }
    links_cnt++;

    if (!quietOut)
      printf(" %d %d\n", p, q);
  }
  printf("WQU: The number of links performed is %d for %d input pairs.\n",
         links_cnt, pairs_cnt);
  printf("PERF: Performed %d unions for %d finds. %d total.\n", unionCount, findCount, unionCount + findCount);

}


/******************************************************************************
 * compressed_weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
* Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Compressed Weighted Quick Union algorithm
 *
 *****************************************************************************/

void compressed_weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{

  int i, j, p, q, t, x;
  int *sz = (int *) malloc(N * sizeof(int));
  int pairs_cnt = 0;            /* connection pairs counter */
  int links_cnt = 0;            /* number of links counter */
  int findCount = 0, unionCount = 0;

  /* initialize; all disconnected */
  for (i = 0; i < N; i++) {
    id[i] = i;
    sz[i] = 1;
  }

  /* read while there is data */
  while (fscanf(fp, "%d %d", &p, &q) == 2) {
    pairs_cnt++;

    /* do search first */
    findCount++;
    for (i = p; i != id[i]; i = id[i]) 
      findCount += 2;
    findCount++;
    for (j = q; j != id[j]; j = id[j])
      findCount += 2;
    if (i == j) {
      /* already in the same set; discard */
      if (!quietOut)
        printf("\t%d %d\n", p, q);
      continue;
    }

    /* pair has new info; must perform union; pick right direction */
    unionCount += 2;
    if (sz[i] < sz[j]) {
      id[i] = j;
      sz[j] += sz[i];
      t = j;
      unionCount += 3;
    }
    else {
      id[j] = i;
      sz[i] += sz[j];
      t = i;
      unionCount += 3;
    }
    links_cnt++;

    /* retrace the path and compress to the top */
    for (i = p; i != id[i]; i = x) {
      x = id[i];
      id[i] = t;
      unionCount += 3;
    }
    for (j = q; j != id[j]; j = x) {
      x = id[j];
      id[j] = t;
      unionCount += 3;
    }
    if (!quietOut)
      printf(" %d %d\n", p, q);
  }
  printf("CWQU: The number of links performed is %d for %d input pairs.\n",
         links_cnt, pairs_cnt);
  printf("PERF: Performed %d unions for %d finds. %d total.\n", unionCount, findCount, unionCount + findCount);

}
