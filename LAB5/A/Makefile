#compiler used
CC = gcc

#flags for individual object file compilation
CFLAGS = -Wall -std=c99 -g
#RELEASE
# -Wall -std=c99 -O3
#DEVELOPMENT
# -Wall -std=c99 -g

#source .c files
SOURCE = $(wildcard src/*.c)
#object files created
OBJECTS = $(patsubst src/%.c,bin/%.o,$(SOURCE))
#resources to test
RESOURCES = $(wildcard res/*.adj)
IEXT = adj
OEXT = ram
#output of tests
OUTPUTS = $(wildcard res/*.ram)
ORIGINALS = $(patsubst res/%.ram,org/%.ram,$(OUTPUTS))

#executable name
EXECUTABLE = lab6a

############################################################


all: $(EXECUTABLE)

run: $(EXECUTABLE)
	@for file in $(RESOURCES); do \
		echo "\n\n======================="; \
		echo $$file; \
		echo "=======================\n\n"; \
		./$(EXECUTABLE) $$file; \
	done

cmp: FORCE $(ORIGINALS)
	
org/%.ram: res/%.ram
	@diff -s $< $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm bin/*.o $(EXECUTABLE)

FORCE: ;