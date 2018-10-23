/******************************************************************************
 *
 * File Name: p2-pub.c
 *	      (c) 2018 AED
 * Author:    Luis Miguel Silveira & AED Team
 * Revision:  14 Oct 2018
 *
 * NAME
 *     p2-pub.c - testing basic functionaloty
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int func(int *data, int N)
{
  int res;
  int carryAdder = 0;
  int i;

  for (i = 0; i < N; i++)
    carryAdder += data[i];

  res = carryAdder / N;

  return(res);
}


int main(int argc, char *argv[])
{
  int i, N, result=0, *data;
  FILE *fp;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    exit(1);
  }

  fp = fopen(argv[1], "r");
  if (fp == (FILE*) NULL) {
    fprintf(stderr, "Could not open filename %s.  Exiting...\n", argv[1]);
    exit(1);
  }

  /* read N */
  fscanf(fp, "%d", &N);

  if (N <= 0) {
    fprintf(stderr, "N must be positive (%d).  Existing...\n", N);
    exit(1);
  }

  /* allocate memory for N additional numbers */
  data = malloc(N * sizeof(int));

  /* now read the numbers from the file */
  for (i = 0; i < N; i++) {
    fscanf(fp, "%d", &(data[i]));
  }

  /* Now call func(...) to determine ... */
  result = func(data, N);

  /* print the computed result */
  printf("result:  %d \n", result);

  /* free memory */
  fclose(fp);
  free(data);
  
  exit(0);
}
