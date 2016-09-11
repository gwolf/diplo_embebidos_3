# makefile para calculadora polaca, versión 2
# uso de variables
# usar tabulador (no espacios) en la línea de comando

CC = gcc
OBJECTS = stack.o getop.o getch.o

polaca : main.o $(OBJECTS)
	$(CC) -o calculadora_pila main.o $(OBJECTS)
main.o: main.c calc.h
	$(CC) -c main.c
stack.o: stack.c calc.h
	$(CC) -c stack.c
getop.o: getop.c calc.h
	$(CC) -c getop.c
getch.o: getch.c
	$(CC) -c getch.c
	top.o getch.o

clean:
	rm calculadora_pila \
	main.o stack.o getop.o getch.o 
