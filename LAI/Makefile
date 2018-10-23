#
#  File name: Makefile
#
#  Author: 2018 Fall Semester AED Team
#
#  Release date: 2018/10/16
#
#  Description: Makefile for the individual evaluation lab (LAI) code
#
#  Usage:
#
#     1) To generate the executable file for the program p2-pub, run
#         $ make p2
#
#     2)  To generate the executable file for the program p3-pub, run
#         $ make p3
#
#     3) To clean all object files and the executable file, run
#         $ make clean
#
#     4) Some test run targets are included, e.g. t31 
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -g -Wall -ansi

#  Sources
SOURCES2 =  p2-pub.c
SOURCES3 =  bignum.c bignum.h p3-pub.c

#  Objects
OBJECTS2 = p2-pub.o
OBJECTS3 = bignum.o p3-pub.o

%.o: %.c


p2:	p2-pub
p2-pub: $(OBJECTS2)
	$(CC) -g -o $@ $(OBJECTS2)

p2-pub.o: p2-pub.c
	$(CC) -g -c p2-pub.c

p3:	p3-pub
p3-pub: $(OBJECTS3)
	$(CC) -g -o $@ $(OBJECTS3)

bignum.o: bignum.h bignum.c
	$(CC) -g -c bignum.c

p3-pub.o: bignum.h p3-pub.c
	$(CC) -g -c p3-pub.c

clean::
	rm -f *.o core a.out p3-pub p2-pub *~

depend::
	makedepend $(SOURCES)

# Tests for p3

t31:
	echo 1 0 | ./p3-pub

t32:
	echo 8888888888888888888888 -22 | ./p3-pub

N=9876543210987654321098765432109876543210987654321098765432109876543210
M=22

t33:
	echo $N $M | ./p3-pub

t34:
	echo 64 64 | ./p3-pub

# DO NOT DELETE
