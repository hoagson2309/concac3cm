# TODO: enter contents here so that calculator is built from main.c and functions.c
#       using a separate compilation step from source to object files

CC = gcc;
CFLAGS = -Wall;
CPPFLAGS = -I; 

# the program to be built (calculator) is composed of main.o and functions.o
calculator: main.o functions.o 
	@echo "linking main.o functions.o into calculator"
	$(CC) -o calculator main.o functions.o 

# main.o is built from main.s
main.o: main.s 
	@echo "Assembling main.o from main.s"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c main.s

# functions.o is built from functions.s
functions.o: functions.s 
	@echo "Assembling functions.o from functions.s"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c functions.s

# main.c is compiled into main.s
main.s: main.c
	@echo "Compiling main.c into main.s"
	$(CC) $(CFLAGS) $(CPPFLAGS) -S main.c 
functions.s: functions.c
# functions.c is compile into functions.s
	@echo "compiling functions.c into functions.s"
	$(CC) $(CFLAGS) $(CPPFLAGS) -S functions.c 