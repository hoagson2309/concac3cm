# TODO: Paste the Makefile you used here
CC = gcc
CFLAGS = -Wall
CPPFLAGS = 
LDFLAGS = -lncurses

BUILDDIR = build

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=build/%.o)

minesweeper: $(OBJECTS)
	@echo "Linking $(OBJECTS) into $@"
	$(CC) $(CFLAGS) -o build/minesweeper $(OBJECTS) $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p build
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up build directory"
	@rm -f build/minesweeper