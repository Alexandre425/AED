#include "arguments.h"

/******************************************************************************
 * arguments_check()
 *
 * Arguments:   argc - argument count
 *              argv - argument vector
 *
 * Description: check if the program was ran correctly
 *
 *****************************************************************************/

void arguments_check(int argc, char *argv[])
{

  char arguments[2][10] = {"/tuktuk\0", ".cities\0"};

  if (argc != 2) 
    exit(0);
  if (NULL == strstr(argv[0], arguments[0]))
    exit(0);
  if (NULL == strstr(argv[1], arguments[1]))
    exit(0);
}
