CC = gcc
CFLAGS = -g -Wall -O2
SRC = main.c funciones.c funciones.h
OBJ = main.o funciones.o
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
	$(CC) $(CFLAGS) -o main $(OBJ)
	
funciones.o: funciones.c funciones.h 

main.o: main.c funciones.h  

clean:
	$(RM) $(OBJ) *~ *.swap *.swo *.swp main

clean_ipk: 
	rm -f control.tar.gz data.tar.gz mipaquete.ipk debian-binary 

install: all  
	[ -d $(DESTDIR) ] && mkdir -p $(DESTDIR)
	cp main $(DESTDIR)
