/******************************************************************************
 *
 * File Name: word.c
 *	      (c) 2018 AED
 * Authors:    AED Team
 * Revision:  v2.4
 *
 * NAME
 *		Auxiliary functions to read and write text files
 *		functions to allocate and manipulate structures
 *		functions to sort abstract structures
 *		functions implementing the "less" functions for the specific
 *              structure using different criteria
 *
 * COMMENTS
 *		Version with function for structure allocation
 *		More compact test for EOF
 *
 *****************************************************************************/

#define MAX_CHARS 100
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "word.h"

struct t_palavra {              /* structure for word */
  char *nome;
  int ocorrencias;
};



/******************************************************************************
 * ExitErrorMemoria ()
 *
 * Arguments: k - exit status to use
 * Returns: (void)
 * Side-Effects: executions ends
 *
 * Description: general function for memory allocation error and exit
 *
 *****************************************************************************/

void ExitErroMemoria(int k)
{

  fprintf(stderr, "ERROR: Not enough memory.\n");
  exit(k);
}


/******************************************************************************
 * LePalavra ()
 *
 * Arguments: f - file pointer to read from
 * Returns: char * - pointer to word read
 * Side-Effects: none
 *
 * Description: Reads a word from open file
 *
 *****************************************************************************/

char *LePalavra(FILE * f)
{
  static char palavra[MAX_CHARS];
  /* It is assumed that the words present in the text files do not
     exceed 100 characters in length and the variable palavra is
     declared as "static"  */

  if (fscanf(f, "%s", palavra) == 1)
    return palavra;
  else
    return NULL;
}


/******************************************************************************
 * AbreFicheiro ()
 *
 * Arguments: nome - pointer to string containing name of file to open
 *            mode - mode to use to open the file
 * Returns: FILE * - handle to file opened
 * Side-Effects: input file is opened
 *
 * Description: Open file for reading, returns handle
 *
 *****************************************************************************/

FILE *AbreFicheiro(char *nome, char *mode)
{
  FILE *f;

  f = fopen(nome, mode);
  if (f == NULL) {
    fprintf(stderr, "Error: Unable to open file %s\n.", nome);
    exit(1);
  }
  return f;
}


/******************************************************************************
 * AllocaTabelaPalavras ()
 *
 * Arguments: t - pointer to word table
 *            ficheiro - handle for input file
 * Returns: int - number of words read
 * Side-Effects: words are read, word table is allocated; input file is closed
 *
 * Description: Reads the input file, counts the total number of words and
 *		allocates the memory for the table structure
 *
 *****************************************************************************/

int AllocaTabelaPalavras(t_tabela * t, char *ficheiro)
{
  FILE *f;
  char *palavra;

  int nt_palavras = 0;

  f = AbreFicheiro(ficheiro, "r");
  while ((palavra = LePalavra(f)) != NULL)
    nt_palavras++;

  fclose(f);

  printf("Total number of words: %d\n", nt_palavras);
  (*t) = (t_tabela) calloc(nt_palavras, sizeof(t_palavra *));

  if (*t == NULL)
    ExitErroMemoria(2);

  return nt_palavras;
}


/******************************************************************************
 * NovaPalavra ()
 *
 * Arguments: t - pointer to word table
 *            palavra - pointer to string containing word
 *            n_palavras - number of distinct words found so far
 * Returns: int - status regarding word being new
 * Side-Effects: none
 *
 * Description: Check for same word in table, returns table position or
 *              -1 if not found
 *
 *****************************************************************************/

int NovaPalavra(t_tabela * t, char *palavra, int n_palavras)
{
  int i = 0;

  while (i < n_palavras) {
    if (strcasecmp((*t)[i]->nome, palavra) == 0)
      return i;
    i++;
  }

  return -1;
}


/******************************************************************************
 * PreenchePalavra ()
 *
 * Arguments: t - pointer to word table
 *            ficheiro - handle for input file
 * Returns: int - number of distinct words in file
 * Side-Effects: none
 *
 * Description: Fills table with distinct words in file
 *
 *****************************************************************************/

int PreencheTabelaPalavras(t_tabela * t, char *ficheiro)
{
  FILE *f;
  int n;
  char *palavra;
  int n_palavras = 0;

  f = AbreFicheiro(ficheiro, "r");
  while ((palavra = LePalavra(f)) != NULL) {
    if ((n = NovaPalavra(&(*t), palavra, n_palavras)) == -1) {
      /* word has not been seen; add to table */
      (*t)[n_palavras] = (t_palavra *) malloc(sizeof(t_palavra));

      if ((*t)[n_palavras] == NULL)
        ExitErroMemoria(3);
      (*t)[n_palavras]->nome =
          (char *) malloc(sizeof(char) * (strlen(palavra) + 1));

      if ((*t)[n_palavras]->nome == NULL)
        ExitErroMemoria(4);
      strcpy((*t)[n_palavras]->nome, palavra);
      (*t)[n_palavras]->ocorrencias = 1;
      n_palavras++;
    }
    else {
      /* word is not new; new occurrence */
      (*t)[n]->ocorrencias++;
    }
  }

  fclose(f);

  printf("Number of different words = %d\n", n_palavras);

  return n_palavras;
}


/******************************************************************************
 * EscreveFicheiro ()
 *
 * Arguments: t - pointer to word table
 *            ficheiro - handle for output file
 *            n_palavras - number of distinct words seen
 * Returns: (void)
 * Side-Effects: output file is written
 *
 * Description: Writes table to file
 *
 *****************************************************************************/

void EscreveFicheiro(t_tabela * t, char *ficheiro, int n_palavras)
{
  FILE *f;
  char *nome;
  int i = 0;

  nome = (char *) malloc((strlen(ficheiro) + strlen(".palavras") + 1)
                         * sizeof(char));
  if (nome == NULL) {
    fprintf(stderr,
            "ERROR: allocation of output filename. Not enough memory.\n");
    exit(2);
  }

  strcpy(nome, ficheiro);
  strcat(nome, ".palavras");

  f = AbreFicheiro(nome, "w");
  for (i = 0; i < n_palavras; i++) {
    fprintf(f, "%d: %s\n", (*t)[i]->ocorrencias, (*t)[i]->nome);
  }

  fclose(f);

  free(nome);

  return;
}


/******************************************************************************
 * LibertaTabelaPalavras ()
 *
 * Arguments: t_tabela - pointer to word table
 *            nt_palavras - total number of words
 * Returns: (void)
 * Side-Effects: free memory allocated for word table
 *
 * Description: Frees the memory allocated in t_tabela
 *
 *****************************************************************************/

void LibertaTabelaPalavras(t_tabela t, int nt_palavras)
{
  int i;

  for (i = 0; i < nt_palavras; i++){
    if(t[i] != NULL){
      free(((t_palavra*) t[i])->nome);
      free(t[i]);
    }
  }

  free(t);
}


/******************************************************************************
 * LessAlfabetica ()
 *
 * Arguments: a, b - items to be compared
 * Returns: int - result of comparison
 * Side-Effects: none
 *
 * Description: Implements the comparation for alfabetic ordering
 *****************************************************************************/

int lessAlfabetica(Item a, Item b)
{
  if (strcasecmp(((t_palavra *) a)->nome, ((t_palavra *) b)->nome) < 0)
    return 1;
  else
    return 0;
}


/*************************************************************************
 **  -- Add comparison functions for the remaining criteria --
 *************************************************************************/

int moreAlfabetica(Item a, Item b)
{
  return (lessAlfabetica(b, a));
}

int lessOcorrencias(Item a, Item b)
{
  if (((t_palavra *)a)->ocorrencias > ((t_palavra *)b)->ocorrencias)
    return 1;
  else 
    return 0;
}

int moreOcorrencias(Item a, Item b)
{
  return (lessOcorrencias(b, a));
}


int lessComprimento(Item a, Item b)
{
  if (strlen( ((t_palavra *)a)->nome ) < strlen( ((t_palavra *)b)->nome ) )
    return 1;
  else 
    return 0;
}
int moreComprimento(Item a, Item b)
{
  return lessComprimento(b, a);
}

/******************************************************************************
 * sort ()
 *
 * Arguments: a - table of items to sort
 *            l, r - limits on table to consider
 *            less - item comparison function
 * Returns: (void)
 * Side-Effects: table is sorted in place
 *
 * Description: implements "some" abstract type (Item) sorting algorithm,
 *		using also an abstract type comparison function (*less)
 *		   a[] - array of abstract type Item to be sorted
 *		   l - index of first element in the array to be sorted
 *		   r  -last element of the array to be sorted
 *		   (*less)(Item,Item) - abstract type comparison function
 *
 *****************************************************************************/

void sort(Item a[], int l, int r, int (*less) (Item, Item))
{
  int i, j;
  int opCount = 0;

  /* insert sort */
  for (i = l + 1; i < r; i++) {
    Item v = a[i];
    j = i;
    opCount++;

    while (j > l && less(v, a[j - 1])) {
      a[j] = a[j - 1];
      j--;
      opCount++;
    }
    a[j] = v;
  }

  printf("Operation cound: %d\nConstante: %f \n", opCount , opCount/(float)((r+1)*(r+1)*0.215));

  return;
}
 

