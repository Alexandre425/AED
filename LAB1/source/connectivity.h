/******************************************************************************
 * (c) 2010 AED
 * File Name: connectivity.h
 * Author:    AED Team
 * Last modified: lms 2018-09-18
 * Revision:  v20180918
 *
 * NAME
 *      class2 - test algorithms for solving the connectivity problem
 *
 * DESCRIPTION
 *      Functions declarations for solving the connectivity problem
 *
 * COMMENTS
 *
 *****************************************************************************/

#ifndef __connectivity__
#define __connectivity__

void link_print(int *id, int N);
void quick_find(int *id, int N, FILE * fp, int quietOut);
void quick_union(int *id, int N, FILE * fp, int quietOut);
void weighted_quick_union(int *id, int N, FILE * fp, int quietOut);
void compressed_weighted_quick_union(int *id, int N, FILE * fp, int quietOut);


#endif                          /* __connectivity__ */

/*****************************************************************************/
