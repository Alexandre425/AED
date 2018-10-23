/******************************************************************************
 *
 * File Name: p3-pub.c
 *	      (c) 2018 AED
 * Author:    Luis Miguel Silveira & AED Team
 * Revision:  16 Oct 2018
 *
 * NAME
 *     p3-pub.c - bignum operations
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bignum.h"

#define DEBUG 0

char *DecStr2BinStr ( char *decstr );
char *BinStr2DecStr ( char *binstr );



int main(void)
{
  int ret;
  char *d1str, *d2str, *bn1str, *bn2str;
  BigNum *x, *y, *res;

  d1str = (char*) calloc(1, MAX_STR*sizeof(char));
  d2str = (char*) calloc(1, MAX_STR*sizeof(char));

  /* let us create some bignums using intermediate string representations */
  if (scanf("%s %s", d1str, d2str) != 2) {
    fprintf(stderr, "could not read 2 long integers. exiting.\n");
    exit(1);
  }

  /* convert decimal string to binary string */
  bn1str = DecStr2BinStr ( d1str );
#if DEBUG==1
  printf("%s is %s\n", d1str, bn1str);
#endif
  bn2str = DecStr2BinStr ( d2str );
#if DEBUG==1
  printf("%s is %s\n", d2str, bn2str);
#endif

  /* create bignum representation from binary string representation */
  x = bn_BNfromBinStr(bn1str);
  y = bn_BNfromBinStr(bn2str);
#if DEBUG==1
  printf("%s is %s\n", d1str, bn_BinStrfromBN(x));
  printf("%s is %s\n", d2str, bn_BinStrfromBN(y));
#endif
  printf("%s is %s\n", d1str, BinStr2DecStr(bn_BinStrfromBN(x)));
  printf("%s is %s\n", d2str, BinStr2DecStr(bn_BinStrfromBN(y)));

  /* now do some operations with x and y */

  res = bn_add(x, y);
  printf("%s + %s = \n%s\n\n", BinStr2DecStr(bn_BinStrfromBN(x)), BinStr2DecStr(bn_BinStrfromBN(y)), BinStr2DecStr(bn_BinStrfromBN(res)));

  ret = bn_compare(x, y);
  if (ret == 1) printf("x > y\n\n");
  else if (ret == 0) printf("x = y\n\n");
  else printf("x < y\n\n");

  res = bn_symmetric(x);
  printf("symetric of x: %s\n\n", BinStr2DecStr(bn_BinStrfromBN(res)));

  /* freeing used memory */
  free(d1str);
  free(d2str);
  free(bn1str);
  free(bn2str);
  
  return 0;
}



/******************************************************************************
 * DecStr2BinStr()
 *
 * Arguments: decstr - pointer to decimal number string
 * Returns: pointer to malloc'd buffer with binary number string
 * Side-Effects: to avoid memory leak, buffer should be freed by caller
 *
 * Description: use Unix 'bc' to make decimal to binary string conversion
 *       Note: since 2**10k ~= 2e3010 (i.e. 10k bits need 3010 decimal digits)
 *       the buffer allocated for the binary string is about 4 times the size
 *       of the decimal string (conservative rounding up)
 *****************************************************************************/

char * DecStr2BinStr ( char *decstr )
{
  char *binstr, *cmdstr, *temp;
  FILE *fp;
  int declen, binlen;

  declen = strlen(decstr);

  binstr = (char *) malloc( (declen*4)  * sizeof(char) );  /* returned */
  cmdstr = (char *) malloc( (declen+80) * sizeof(char) );  /* freed */

  /* BC_LINE_LENGTH=0 : do not fold long output lines with backslashes
  - NOTE: MacOS does not honor zero as unlimited, needs large number e.g. 9999 */
  
  temp="BC_LINE_LENGTH=9999\nexport BC_LINE_LENGTH\necho \"obase=2\n%s\n\"| bc";
  sprintf(cmdstr, temp, decstr);
  fp = popen(cmdstr,"r");
  fscanf(fp, "%s", binstr);
  pclose(fp);  /* needed */
  free(cmdstr);

#if DEBUG==1
  fprintf ( stderr, "%s\n", binstr );
#endif

  return(binstr);
}

/******************************************************************************
 * BinStr2DecStr()
 *
 * Arguments: binstr - pointer to binary number string
 * Returns: pointer to malloc'd buffer with decimal number string
 * Side-Effects: to avoid memory leak, buffer should be freed by caller
 *
 * Description: use Unix 'bc' to make decimal to binary string conversion
 *       Note: since 2**10k ~= 2e3010 (i.e. 10k bits need 3010 decimal digits)
 *       the buffer allocated for the decimal string is half the size
 *       of the binary string (plus one, conservative rounding up)
 *****************************************************************************/
char * BinStr2DecStr ( char *binstr )
{
  char *decstr, *cmdstr, *temp;
  FILE *fp;
  int declen, binlen;

  binlen = strlen(binstr);
  /*declen = (1+ binlen)/2;  e.g. (1+1)/2 = 1, (1+2)/2 = 1, (1+3)/2 = 2, etc. */

  decstr = (char *) malloc( ((1+binlen)/2)* sizeof(char) );  /* returned */
  cmdstr = (char *) malloc( (binlen+80)   * sizeof(char) );  /* freed */

  /* BC_LINE_LENGTH=0 : do not fold long output lines with backslashes
  - NOTE: MacOS does not honor zero as unlimited, needs large number e.g. 9999 */
  temp="BC_LINE_LENGTH=9999\nexport BC_LINE_LENGTH\necho \"ibase=2\n%s\n\"| bc";
  sprintf(cmdstr, temp, binstr);
  fp = popen(cmdstr,"r");
  fscanf(fp, "%s", decstr);
  pclose(fp);  /* needed */
  free(cmdstr);

#if DEBUG==1
  fprintf ( stderr, "%s\n", decstr );
#endif

  return(decstr);
}
