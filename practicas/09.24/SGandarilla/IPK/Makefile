CC = gcc
CFLAGS = -g -Wall -O2
SRC = calculadora.c func_calc.c func_calc.h
OBJ = calculadora.o func_calc.o
DESTDIR = /usr/local/bin
PKG = mipaquete
VERSION = 0.1.0
PKGDIR = ../
IPKDEST = $(PKDIR)/$(PKG)_$(VERSION)


all: principal 

ipk: principal control
	mkdir -p $(PKGDIR)/build/$(PKG)
	cp *.c *.h $(PKGDIR)/build/$(PKG)
	tar czvf control.tar.gz control
	cd $(PKGDIR); tar czvf ../data.tar.gz .; cd ..
	echo 2.0 > debian-binary
	ar r $(PKG).ipk control.tar.gz data.tar.gz debian-binary

principal: $(OBJ)
	  $(CC) $(CFLAGS) -o calculadora $(OBJ)
	
funciones.o: func_calc.c func_calc.h 

calculadora.o: calculadora.c func_calc.h  

clean:
	$(RM) $(OBJ) *~ *.swap *.swo *.swp calculadora

clean_ipk: 
	rm -f control.tar.gz data.tar.gz mipaquete.ipk debian-binary 

install: all  
	[ -d $(DESTDIR) ] && mkdir -p $(DESTDIR) cp calculadora $(DESTDIR)
