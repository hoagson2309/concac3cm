CC = gcc
CFLAGS = -Wall
CPPFLAGS = -DDEBUG 

# Get all .c files in the current directory
SOURCES = $(wildcard src/*.c)

# TODO: assign all .o files that need to be created to OBJECTS
#       by replacing .c with .o in SOURCES
OBJECTS = $(SOURCES:src/%.c=build/%.o) 

# This rule now simply prints the list of source files
# TODO: the rule should depend on the object files, not on the source files
# Rule to link .o files into an executable (reverser)
reverser: $(OBJECTS)
	@echo "Linking $(OBJECTS) into $@"
	$(CC) $(CFLAGS) -o build/reverser  $(OBJECTS)

# Rule to compile .c files to .o files
build/%.o: src/%.c
	@mkdir -p build
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@


