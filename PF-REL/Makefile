#compiler used
CC = gcc

#flags for individual object file compilation
CFLAGS = -Wall -std=c99 -O3
#RELEASE
# -Wall -ansi -O3
#DEVELOPMENT
# -Wall -ansi -g

#source .c files
SOURCE = $(wildcard *.c)
#object files created
OBJECTS = $(patsubst %.c,%.o,$(SOURCE))

#executable name
EXECUTABLE = tuktuk

############################################################

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o
