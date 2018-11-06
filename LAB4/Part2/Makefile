#
#  File name: makefile
#
#  Author: 2013 Fall Semester AED Team
#
#  Release date: 2013/10/04
#
#  Description: Makefile for the program lab03b
#
#  Usage:
#     1) To generate the executable file for the program lab04,
#       run
#         $ make
#
#     2) To clean all object files and the executable file of
#        lab04b, run
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -g -Wall -ansi -pedantic

#  Sources
SOURCES = LinkedList.c Entry.c lab04b.c

#  Objects
OBJECTS = LinkedList.o Entry.o lab04b.o

lab04b: $(OBJECTS)
	gcc -o $@ $(OBJECTS)

Entry.o: Entry.h Entry.c

LinkedList.o: LinkedList.h defs.h LinkedList.c


clean::
	rm -f *.o core a.out lab04b *~

# DO NOT DELETE
