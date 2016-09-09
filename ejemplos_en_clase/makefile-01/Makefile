
GCC = gcc
CFLAGS = 
DESTDIR = /usr/local/bin

all: binario

objetos: calculadora.o func_calc.o
	touch objetos

%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

binario: objetos
	$(GCC) $(CFLAGS) func_calc.o calculadora.o -o calculadora
	touch binario

clean:
	rm -f *.o calculadora binario objetos

install: binario
	[ ! -d $(DESTDIR) ] && mkdir -p $(DESTDIR)
	cp calculadora $(DESTDIR)
