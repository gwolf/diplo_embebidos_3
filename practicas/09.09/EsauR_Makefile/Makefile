CC = gcc
CFLAGS = -g -Wall -O2
SRC = main.c funciones.c funciones.h
OBJ = main.o funciones.o
DESTDIR = /usr/local/bin


all: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

funciones.o: funciones.c funciones.h 

main.o: main.c funciones.h  

clean:
	$(RM) $(OBJ) *~ *.swap *.swo *.swp main

install: all  
	[ -d $(DESTDIR) ] && mkdir -p $(DESTDIR)
	cp main $(DESTDIR)
