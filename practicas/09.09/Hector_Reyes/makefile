CC=gcc
DEPS = cositas.h
CFLAGS = 
DESTDIR = ~/Documentos

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $<  $(CFLAGS)
	
#objetos: 
#	$(CC) -o objetos Calcula_cosas.o funcion_cositas.o

binario: Calcula_cosas.o funcion_cositas.o
	$(CC) Calcula_cosas.o funcion_cositas.o -o programita
	mkdir $(DESTDIR)/Programa -p
	cp  programita $(DESTDIR)/Programa
	touch binario
clean: binario 
	rm -f *.o programita objetos

	

