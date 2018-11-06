/******************************************************************************
 *
 * File Name: word.h
 *	      (c) 2018 AED
 * Authors:    AED Team
 * Revision:  v2.4
 *
 *****************************************************************************/

#ifndef _WORD_H_
#define _WORD_H_

#include "defs.h"

typedef struct t_palavra t_palavra;
typedef struct t_palavra **t_tabela;


char *LePalavra(FILE * f);
FILE *AbreFicheiro(char *nome, char *mode);

void ExitErroMemoria(int k);
int  AllocaTabelaPalavras(t_tabela *t, char *ficheiro);
int  NovaPalavra(t_tabela * t, char *palavra, int n_palavras);
int  PreencheTabelaPalavras(t_tabela *t, char *ficheiro);
void EscreveFicheiro(t_tabela *t, char *ficheiro, int n_palavras);
void LibertaTabelaPalavras(t_tabela t, int nt_palavras);

int  lessAlfabetica(Item a, Item b);
int moreAlfabetica(Item a, Item b);
int lessComprimento(Item a, Item b);
int moreComprimento(Item a, Item b);
int lessOcorrencias(Item a, Item b);
int moreOcorrencias(Item a, Item b);

void sort(Item a[], int l, int r, int (*less) (Item, Item));

#endif
