# makefile para calculadora
CC = gcc
OBJECTS = stack.o getop.o getch.o

polaca : main.o $(OBJECTS)
        $(CC) -o polaca main.o $(OBJECTS)

main.o: calc.h
stack.o: calc.h
getop.o: calc.h
getch.o:

.PHONY : clean
    clean :
             -rm polaca $(objects) 
