
GCC = gcc
CFLAGS = 
DESTDIR = /usr/local/bin

all: binario

objetos: cal_fact.o func_cal_fact.o
	touch objetos

%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

binario: objetos
	$(GCC) $(CFLAGS) func_cal_fact.o cal_fact.o -o factorial
	touch binario

clean:
	rm -f *.o calculadora binario objetos

