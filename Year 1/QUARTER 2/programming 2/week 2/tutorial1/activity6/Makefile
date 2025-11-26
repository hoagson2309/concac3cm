CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Werror
CPPFLAGS = -D NUM_NUMBERS=10

numbers: main.o functions.o
	@echo "Linking main.o and functions.o into numbers"
	$(CC) -o numbers main.o functions.o

# implicit rules (these use CC, CFLAGS, and CPPFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c main.c

functions.o: functions.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c functions.c

