CFLAGS= -g -Wall

lab04a: main4a.o word.o
	gcc $(CFLAGS) -o words word.o main4a.o

main4a.o: main4a.c word.h
	gcc $(CFLAGS) -c main4a.c

word.o: word.c word.h
	gcc $(CFLAGS) -c word.c

clean:
	rm -f *.o *.~ words *.gch
