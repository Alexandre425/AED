/*
 *  File name: Entry.h
 *
 *  Author: 2018 Fall Semester AED Team
 *
 *  Release date: 2018/10/24
 *
 *  Description: Header file for type Entry, definition and
 * functions.
 *
 *  Version: 1.1
 *
 *  Change log: N/A
 *
 */


/* Prevent multiple inclusions                                      */
#ifndef EntryHeader
#define EntryHeader


/*
 *  Data type: Entry
 *
 *  Description: Entry data type. Contains id, age, height, an
 * weight.
 */
typedef struct EntryStruct Entry;



/*
 *  Function:
 *    newEntry
 *
 *  Description:
 *    Initializes a new entry.
 *
 *  Arguments:
 *    Identification number:
 *      (int) id
 *    Age:
 *     (int) age
 *    Heigth:
 *     (int) Height
 *    Weight:
 *     (int) weight
 *
 *  Return value:
 *    Returns the pointer to the new entry in case of success, NULL
 *   otherwise.
 */
Entry * newEntry(int id, int age, int height, int weight);



/*
 *  Function:
 *    getIdEntry
 *
 *  Description:
 *    Returns the id of an entry.
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *
 *  Return value:
 *    Entry id.
 */
int getIdEntry(Entry * entry);



/*
 *  Function:
 *    getAgeEntry
 *
 *  Description:
 *    Returns the age in the entry.
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *
 *  Return value:
 *    Age stored in the entry.
 */
int getAgeEntry(Entry * entry);


/*
 *  Function:
 *    getHeightEntry
 *
 *  Description:
 *    Returns the age in the entry.
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *
 *  Return value:
 *    Height stored in the entry.
 */
int getHeightEntry(Entry * entry);



/*
 *  Function:
 *    getWeightEntry
 *
 *  Description:
 *    Returns the age in the entry.
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *
 *  Return value:
 *    Weight stored in the entry.
 */
int getWeightEntry(Entry * entry);



/*
 *  Function:
 *    printEntry
 *
 *  Description:
 *    Prints an entry in a file.
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *    Pointer to stream:
 *      (FILE *) fp;
 *
 *  Return value:
 *    None.
 */
void printEntry(Entry * entry, FILE * fp);



/*
 *  Function:
 *    freeEntry
 *
 *  Description:
 *    Frees the memory allocated to an entry
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *
 *  Return value:
 *    None.
 */
void freeEntry(Entry * entry);

int lessId(Entry* a, Entry* b);

int moreId(Entry* a, Entry* b);

int lessAge(Entry* a, Entry* b);

int moreAge(Entry* a, Entry* b);

int lessHeight(Entry* a, Entry* b);

int moreHeight(Entry* a, Entry* b);

int lessWeight(Entry* a, Entry* b);

int moreWeight(Entry* a, Entry* b);

/* End of: Protect multiple inclusions                              */
#endif
