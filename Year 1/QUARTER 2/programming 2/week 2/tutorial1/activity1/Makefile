
# the program to be built (hello) is composed of main.o
hello: main.o functions.o
	@echo "Linking main.o functions.o into hello"
	gcc -o hello main.o functions.o

# main.o is built from main.s
main.o: main.s
	@echo "Assembling main.o from main.s"
	gcc -c main.s
# functions.o is built from functions.s
functions.o: functions.s
	@echo "Assembling functions.o from functions.s"
	gcc -c functions.s
# main.c is complied into main.s
main.s: main.c
	@echo "Compiling main.c into main.s"
	gcc -S main.c
# functions.c is complied into functions.s
functions.s: functions.c
	@echo "Compiling functions.c into functions.s"
	gcc -S functions.c
