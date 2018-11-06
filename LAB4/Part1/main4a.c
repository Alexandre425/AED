/******************************************************************************
 *
 * File Name: main4a.c
 *	      (c) 2018 AED
 * Author:    AED Team
 * Revision:  v2.4
 *
 * NAME
 *     main4a - Sorting arrays
 *
 * SYNOPSIS
 *		#include <stdlib.h>
 *		#include <stdio.h>
 *		#include <string.h>
 *		#include "word.h"
 *
 * DESCRIPTION
 *
 * DIAGNOSTICS
 *          tested
 *****************************************************************************/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "word.h"

enum sort_order {ascending, descending};

enum sort_criteria {alphabetic, length, occurrences};


int main(int argc, char **argv)
{
  int nt_palavras;              /* total number of words in input file */
  int n_palavras;               /* number of distint words in input file */
  t_tabela tabela;              /* table holding the structure */

  /* default initialization for alfabetic order and ascending */
  enum sort_criteria criterio = alphabetic;
  enum sort_order sentido  = ascending;
  char *ficheiro = argv[1];

  nt_palavras = AllocaTabelaPalavras(&tabela, ficheiro);
  n_palavras = PreencheTabelaPalavras(&tabela, ficheiro);

  argv++;                       /* increments index of argv to point to the
                                   second argument */
  while (*(++argv)) {
    if (strcmp(*argv, "-alfabetica") == 0)
      criterio = alphabetic;
    else if (strcmp(*argv, "-ocorrencias") == 0)
      criterio = occurrences;
    else if (strcmp(*argv, "-comprimento") == 0)
      criterio = length;
    else if (strcmp(*argv, "-a") == 0)
      sentido = ascending;
    else if (strcmp(*argv, "-d") == 0)
      sentido = descending;
    else {
      fprintf(stderr, "Wrong arguments\n");
      exit(3);
    }
  }

  if ((criterio == alphabetic)  && (sentido == ascending))
    sort((Item*)tabela, 0, n_palavras, lessAlfabetica);
  if ((criterio == alphabetic)  && (sentido == descending))
    sort((Item*)tabela, 0, n_palavras, moreAlfabetica);
  if ((criterio == occurrences) && (sentido == ascending))
    sort((Item*)tabela, 0, n_palavras, lessOcorrencias);
  if ((criterio == occurrences) && (sentido == descending))
    sort((Item*)tabela, 0, n_palavras, moreOcorrencias);
  if ((criterio == length)      && (sentido == ascending))
    sort((Item*)tabela, 0, n_palavras, lessComprimento);
  if ((criterio == length)      && (sentido == descending))
    sort((Item*)tabela, 0, n_palavras, moreComprimento);


  EscreveFicheiro(&tabela, ficheiro, n_palavras);
  printf("Number of different words: %d\n", n_palavras);

  LibertaTabelaPalavras(tabela, nt_palavras);
  return 0;
}
