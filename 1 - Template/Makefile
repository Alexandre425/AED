#compiler used
COMPILER = gcc

#flags for individual object file compilation
DEVFLAGS = -Wall -ansi -g
RELFLAGS = -Wall -ansi -O3

#source foo.c files
SOURCE = 
#object files created
OBJECTS = $(SOURCES:.c=.o)

#executable name
EXECUTABLE = app


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) $(DEVFLAGS) -o $(EXECUTABLE) $(OBJECTS)





