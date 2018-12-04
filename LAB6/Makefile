#compiler used
CC = gcc

#flags for individual object file compilation
CFLAGS = -Wall -std=c99 -g
#RELEASE
# -Wall -ansi -O3
#DEVELOPMENT
# -Wall -ansi -g

#source .c files
SOURCE = $(wildcard src/*.c)
#object files created
OBJECTS = $(patsubst src/%.c,bin/%.o,$(SOURCE))

#executable name
EXECUTABLE = app

############################################################

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@