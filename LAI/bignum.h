/******************************************************************************
 *
 * File Name: bignum.h
 *	      (c) 2018 AED
 * Author:    Luis Miguel SIlveira & AED Team
 * Revision:  14 Oct 2018
 *
 * NAME
 *     bignum.h - implementation library for handling bignums
 *
 * SYNOPSIS
 *     #include <stdio.h>
 *     #include <stdlib.h>
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#ifndef _BIGNUM_H
#define _BIGNUM_H

#include <stdio.h>
#include <stdlib.h>



#define MAX_STR 2048


typedef struct _bignum BigNum;

BigNum *bn_BNfromBinStr (char *binstr);
char *bn_BinStrfromBN (BigNum *bn);

BigNum *bn_add (BigNum *x, BigNum *y);

BigNum *bn_symmetric (BigNum *x);

int bn_compare (BigNum *x, BigNum *y);

int bn_isZero (BigNum *x);

BigNum *bn_open (BigNum *x, BigNum *y);

#endif
