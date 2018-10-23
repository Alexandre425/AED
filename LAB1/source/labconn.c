/******************************************************************************
 * (c) 2010 AED
 * File Name: labconn.c
 * Author: AED Team
 * Last modified: lms 2018-09-18
 * Revision:  v20180918
 *
 * NAME
 *     labconn - test algorithms for solving the connectivity problem
 *
 * DESCRIPTION
 *     Main program to call the different connectivity algorithms.  Requires
 *     file name as argument.  If argument "-q" is used output is reduced.
 *
 * COMMENTS
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "connectivity.h"

void usage(char *);

int quietOut = 0;

int main(int argc, char *argv[])
{

  int N, *id, choice = 0;
  int opt, find = 1;
  char line[32];
  FILE *fp;

  /* must have at least one argument besides the exec name */
  if (argc < 2) {
    usage(argv[0]);
    exit(0);
  }

  while ((opt = getopt(argc, argv, "q")) != -1) {
    switch (opt) {
    case 'q':  /* quiet on the output */
      quietOut = 1;
      find++;
      break;
    default: /* '?' */
      usage(argv[0]);
      exit(0);
    }
  }

  /* open file and read array size */
  fp = (FILE *) fopen(argv[find], "r");
  if (fp == (FILE *) NULL) {
    fprintf(stderr, "File %s cannot be read.  Please correct.\n", argv[1]);
    exit(0);
  }
  if (fscanf(fp, "%d", &N) != 1) {
    fprintf(stderr,
            "Need to get N (number of elements) from first line of file\n");
    exit(0);
  }
  if (N > 0) {
    id = (int *) calloc(N, sizeof(int));
  }

  /* query which algorithm to use */
  while (choice >= 0) {

    fprintf(stdout, "\tConnectivity Problem\n\nChoose an algorithm:\n");
    fprintf(stdout, "\t1 - Quick Find\n");
    fprintf(stdout, "\t2 - Quick Union\n");
    fprintf(stdout, "\t3 - Weighted Quick Union\n");
    fprintf(stdout, "\t4 - Weighted Quick Union with Compression\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "\t0 - Exit\n");

    do {
      choice = -1;
      fprintf(stdout, "\nYour choice: (1,2,3,4,0) ");
      if (fscanf(stdin, "%d", &choice) != 1) {
        continue;
      }
    } while (choice < 0 || choice > 4);

    if (choice == 0)
      break;

    switch (choice) {
    case 1:
      quick_find(id, N, fp, quietOut);
      break;
    case 2:
      quick_union(id, N, fp, quietOut);
      break;
    case 3:
      weighted_quick_union(id, N, fp, quietOut);
      break;
    case 4:
      compressed_weighted_quick_union(id, N, fp, quietOut);
      break;
    default:
      fprintf(stderr, "Yikes\n");
      exit(1);
    }
    /* rewind the file; reread size (not needed but must consume input) */
    rewind(fp);
    fscanf(fp, "%d", &N);
  }

  exit(0);
}


void usage(char *prog)
{

  fprintf(stdout, "usage: %s [-q] filename\n", prog);
  return;
}
