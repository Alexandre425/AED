/*
 *  File name: lab04b.c
 *
 *  Author: 2018 Fall Semester AED Team
 *
 *  Release date: 2018/10/24
 *
 *  Description: See the handout for Lab 04.
 *
 *  Version: 1.1
 *
 *  Change log: N/A
 *
 */



/* Header Inclusions                                              */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LinkedList.h"
#include"Entry.h"



/*
 *  Function:
 *    readEntryFile2LinkedList
 *
 *  Description:
 *    Reads the entries from a file and creates a linked list with
 *   these entries in the inverse order.
 *
 *  Arguments:
 *    Pointer to the file stream:
 *        FILE * fp
 *
 *  Return value:
 *    Pointer to the first node of the linked list.
 */
LinkedList * readEntryFile2LinkedList(FILE * fp, int (*cmp)(Entry *a, Entry *b))
{
  int id;
  int age;
  int height;
  int weight;
  LinkedList * lp;
  Entry * entry;

  /* Initialize linked list                                       */
  lp = initLinkedList();

  /* Cycle through file rows                                      */
  while(fscanf(fp, "%d %d %d %d", &id, &age, &height, &weight) == 4)
  {
    /* Create new entry                                           */
    entry = newEntry(id, age, height, weight);

    /* Store entry in the linked list                             */
    lp = insertSortedLinkedList(lp, entry, cmp, NULL);

  }

  return lp;
}



/*
 *  Function:
 *    writeEntryFile
 *
 *  Description:
 *    Writes the entries from a linked list to a file.
 *
 *  Arguments:
 *    Pointer to the first node of the linked list:
 *      LinkedList * lp
 *    Pointer to the file stream:
 *      FILE * fp
 *
 *  Return value:
 *    None.
 */
void writeEntryFile(LinkedList * lp, FILE *fp)
{
  LinkedList * aux;

  aux = lp;
  while(aux != NULL)
  {
    printEntry((Entry *) getItemLinkedList(aux), fp);
    aux = getNextNodeLinkedList(aux);
  }
}



/*
 *  Function:
 *    freeEntryItem
 *
 *  Description:
 *    Frees the memory allocated to an Item of the type Entry
 *
 *  Arguments:
 *    Pointer to the item
 *      Item item
 *
 *  Return value:
 *    None.
 */
void freeEntryItem(Item item)
{
  freeEntry((Entry *) item);
}


enum sort_order {ascending, descending};
enum sort_criteria {id, age, height, weight};

/*
 * Function:
 *   main
 */
int main(int argc, char *argv[])
{
  FILE * fp;
  LinkedList * lp;
  char extOut[] = ".sort";
  char * fileNameIn;
  char * fileNameOut;
  int criterio = id;
  int sentido = ascending;

  /* Check number of arguments                                    */
  if(argc < 2)
  {
    printf("Usage: ./lab04b [filename] [arguments options]\n");
    exit(1);
  }



  /* Open input file                                              */
  fileNameIn = argv[1];

  fp  = fopen(fileNameIn, "r");
  if(fp == NULL)
  {
    printf("Open error of input file.\n");
    exit(2);
  }

  argv++;
  while (*(++argv)) {
    if (strcmp(*argv, "-id") == 0)
      criterio = id;
    else if (strcmp(*argv, "-age") == 0)
      criterio = age;
    else if (strcmp(*argv, "-height") == 0)
      criterio = height;
    else if (strcmp(*argv, "-weight") == 0)
      criterio = weight;

    else if (strcmp(*argv, "-a") == 0)
      sentido = ascending;
    else if (strcmp(*argv, "-d") == 0)
      sentido = descending;
    else {
      fprintf(stderr, "Wrong arguments\n");
      exit(3);
    }
  }

  /* Read input file and construct linked list with entries       */
  if (     criterio == id     && sentido == ascending)
    lp = readEntryFile2LinkedList(fp, lessId);
  else if (criterio == id     && sentido == descending)
    lp = readEntryFile2LinkedList(fp, moreId);
  else if (criterio == age    && sentido == ascending)
    lp = readEntryFile2LinkedList(fp, lessAge);
  else if (criterio == age    && sentido == descending)
    lp = readEntryFile2LinkedList(fp, moreAge);
  else if (criterio == height && sentido == ascending)
    lp = readEntryFile2LinkedList(fp, lessHeight);
  else if (criterio == height && sentido == descending)
    lp = readEntryFile2LinkedList(fp, moreHeight);
  else if (criterio == weight && sentido == ascending)
    lp = readEntryFile2LinkedList(fp, lessWeight);
  else if (criterio == weight && sentido == descending)
    lp = readEntryFile2LinkedList(fp, moreWeight);


  /* Close input file                                             */
  fclose(fp);


  /* Determine output filename                                    */
  fileNameOut = (char *) malloc(sizeof(char) *
                                 (strlen(fileNameIn) +
                                  strlen(extOut) + 1));
  if(fileNameOut == NULL)
  {
    printf("Memory allocation error for fileNameOut.\n");
    exit(1);
  }

  strcpy(fileNameOut, fileNameIn);
  strcat(fileNameOut, extOut);


  /* Open output file                                             */
  fp  = fopen(fileNameOut, "w");

  if(fp == NULL)
  {
    printf("Open error of input file.\n");
    exit(2);
  }


  /* Write entries to output file                                 */
  writeEntryFile(lp, fp);


  /* Free space allocated to fileNameOut                          */
  free(fileNameOut);


  /* Close output file                                            */
  fclose(fp);


  /* Free linked list with entries                                */
  freeLinkedList(lp, freeEntryItem);


  return 0;
}
