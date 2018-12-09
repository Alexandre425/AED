/******************************************************************************
 *
 * File Name: main.c
 *
 * Authors:    Alexandre Rodrigues
 *             Aprígio Malveiro
 *
 *  NAME
 *    Tourist Knights - pathfinding on a wheighted matrix
 *
 *  DESCRIPTION
 *		AED project for the 2018 first semester. Solves 3 problems related to
 *    pathfinding on a wheighted matrix. 
 *
 *****************************************************************************/

#include "arguments.h"
#include "file_manager.h"


int main(int argc, char *argv[])
{

  arguments_check(argc, argv);
  file_readPuzzles(argv);

  return 0;
}