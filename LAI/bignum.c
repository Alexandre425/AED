/******************************************************************************
 *
 * File Name: bignum.h
 *	      (c) 2018 AED
 * Author:    Luis Miguel Silveira & AED Team
 * Revision:  16 Oct 2018
 *
 * NAME
 *     bignum.h - implementation library for handling bignums
 *
 * SYNOPSIS
 *     #include "bignum.h"
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignum.h"


typedef struct _bitb {
  short bit;
  struct _bitb *nbit;
} BitB;

typedef struct _bignum {
  short sign;
  BitB *bits;
} BigNum;



/******************************************************************************
 * bn_BNfromBinStr()
 *
 * Arguments: pointer to BigNum structure
 * Returns: binstr - pointer to binary number string
 * Side-Effects: allocates BigNum structure
 *
 * Description:
 *
 *****************************************************************************/

BigNum *bn_BNfromBinStr(char *binstr) {
  BigNum *bn;
  BitB *nb, *aux = (BitB*)NULL;
  int i, st =0;

  bn = (BigNum*) malloc(sizeof(BigNum));
  if (bn == ((BigNum*)NULL)) {
    fprintf(stderr, "error: cannot allocate bignum structure.  exiting.\n");
    exit(1);
  }

  bn->sign = 0;
  bn->bits = (BitB*) NULL;

  if (binstr[0] == '-') {
      bn->sign = 1;
      st = 1;
  }
  for (i = strlen(binstr)-1; i >= st; i--) {
    nb = (BitB*) malloc(sizeof(BitB));
    if (nb == ((BitB*)NULL)) {
      fprintf(stderr,
              "error: cannot allocate bignum bitb structure.  exiting.\n");
      exit(1);
    }
    if (binstr[i] == '1')
      nb->bit = 1;
    else if (binstr[i] == '0')
      nb->bit = 0;
    else {
      fprintf(stderr, "error: found strange char in bit string.  exiting.\n");
      exit(1);
    }
    nb->nbit = (BitB*)NULL;
    if (aux == NULL) {
      bn->bits = nb;  /* defining the head of the linked list */
    } else {  
      aux->nbit = nb; /* linking the list */
    }
    aux = nb;
  }

  return(bn);
}


/******************************************************************************
 * bn_BinStrfromBN()
 *
 * Arguments: pointer to BigNum structure
 * Returns: binstr - pointer to decimal number string
 * Side-Effects: allocates string for conversion
 *
 * Description:
 *
 *****************************************************************************/

char *bn_BinStrfromBN(BigNum *bn) {
  BitB *nb;
  char *binstr, temp;
  int i, neg = 0, st = 0;

  binstr = (char*) malloc(MAX_STR * sizeof(char));
  if (binstr == ((char*)NULL)) {
    fprintf(stderr,
            "error: cannot allocate binary string structure.  exiting.\n");
    exit(1);
  }
  if (bn->sign == 1) {
    binstr[0] = '-';
    st++;
    neg = 1;
  }

  for (i = st, nb = bn->bits; nb != (BitB*)NULL; nb = nb->nbit, i++) {
    if (nb->bit == 0)
      binstr[i] = '0';
    else
      binstr[i] = '1';
  }
  binstr[i] = '\0';

  for (i = 0 + neg; i < strlen(binstr)/2; i++) {
    temp = binstr[i];
    binstr[i] = binstr[strlen(binstr)-1-i+neg];
    binstr[strlen(binstr)-1-i+neg] = temp;
  }

  return(binstr);
}


/******************************************************************************
 * bn_symmetric()
 *
 * Arguments: bn - pointer to a bignum
 * Returns: pointer to the new bignum, symmetric
 * Side-Effects: allocates BigNum structure
 *
 * Description:
 *
 *****************************************************************************/

BigNum *bn_symmetric(BigNum *x) {
  BigNum *bn;

  /* ... */

  return(bn);
}


/******************************************************************************
 * bn_isZero()
 *
 * Arguments: bn - pointer to a bignum
 * Returns: 1 if the bignum is zero, 0 otherwise
 * Side-Effects: (none)
 *
 * Description:
 *
 *****************************************************************************/

int bn_isZero(BigNum *x) {
  BigNum *bn;

  if (x->bits == (BitB*)NULL)
    return 1;
  else
    return(0);
}


/******************************************************************************
 * bn_compare()
 *
 * Arguments: x, y - pointers to two bignums
 * Returns: 1, 0 or -1 if respectively x>y, x==y or x<y
 * Side-Effects: (none)
 *
 * Description:
 *
 *****************************************************************************/

int bn_compare(BigNum *x, BigNum *y) {
  BitB *x_aux, *y_aux;
  int result;
  int equal = 1, more = 1, less = 1;
  int x_count = 0, y_count = 0;

  while (x_aux != NULL){
    
  }

  while (x_aux != NULL || x_aux != NULL){

    

    if (x_aux != NULL)
      x_aux = x_aux->nbit;
    if (y_aux != NULL)
      y_aux = y_aux->nbit;
  }

  return(result);
}


/******************************************************************************
 * bn_add()
 *
 * Arguments: x, y - pointers to two bignums
 * Returns: bignum (x+y)
 * Side-Effects: allocates BigNum structure for result; assumes both
 *               arguments are positive
 *
 * Description:
 *
 *****************************************************************************/

BigNum *bn_add(BigNum *x, BigNum *y) {
  BigNum *bn = NULL;
  BitB *x_aux = x->bits, *y_aux = y->bits, *aux = NULL, *aux2 = NULL, *extraBit = NULL;
  int x_count = 0, y_count = 0;
  int size = 0, i = 0;
  char* bitStr = NULL;
  int carry = 0, carryOut = 0, res = 0;

  while (x_aux != NULL){
    x_count++;
    x_aux = x_aux->nbit;
  }
  while (y_aux != NULL){
    y_count++;
    y_aux = y_aux->nbit;
  }
  x_aux = x->bits;
  y_aux = y->bits;

  if (y_count >= x_count) {size = y_count; bitStr = bn_BinStrfromBN(y); aux2 = x->bits;} else {size = x_count; bitStr = bn_BinStrfromBN(x); aux2 = y->bits;}
  bn = bn_BNfromBinStr(bitStr);

  /* alocating a single extra bit */
  aux = bn->bits;
  while (aux->nbit != NULL)
    aux = aux->nbit;
  extraBit = malloc(sizeof(BitB));
  extraBit->bit = 0;
  extraBit->nbit = NULL;
  aux->nbit = extraBit;

  aux = bn->bits;
  while (aux2 != NULL || carry != 0){
    if (aux2 != NULL){
      res = aux2->bit ^ aux->bit;   /* XOR */
      carryOut = (aux2->bit & aux->bit) | (res & carry);
      res = carry ^ res;
    }
    else{
      carryOut = aux->bit & carry;
      res = carry ^ aux->bit;
    }

    aux->bit = res;
    carry = carryOut;
    aux  = aux ->nbit;
    if (aux2 != NULL)
      aux2 = aux2->nbit;
  }

  return(bn);
}



/******************************************************************************
 * bn_open()
 *
 * Arguments: x, y - pointers to two bignums
 * Returns: bignum
 * Side-Effects: allocates BigNum structure for result
 *
 * Description:
 *
 *****************************************************************************/

BigNum *bn_oper(BigNum *x, BigNum *y) {
  BigNum *bn;

  /* ... */

  return(bn);
}

