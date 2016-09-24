CC=gcc
DEPS=base.h
CFLAGS = 
DESTDIR=~/Documents

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $<  $(CFLAGS)
	
#objetos: 
	#$(CC) -o objetos funcionMult.c calculadora.c

binario: funcionMult.o calculadora.o
	$(CC) funcionMult.o calculadora.o -o programa
	mkdir $(DESTDIR)/Programa -p
	cp  programa $(DESTDIR)/Programa
	touch binario
clean: binario 
	rm -f *.o programa
