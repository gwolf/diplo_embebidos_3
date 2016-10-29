# makefile para calculadora
CC = gcc
OBJECTS = stack.o getop.o getch.o

polaca : main.o $(OBJECTS)
        $(CC) -o polaca main.o $(OBJECTS)

ipk:
        mkdir -p $(PKGDIR)/build/$(PKG)
        cp *.py $(PKGDIR)/build/$(PKG)
        tar czvf control.tar.gz control
        cd $(PKGDIR); tar czvf ../data.tar.gz .; cd ..
        echo 2.0 > debian-binary
        ar r $(PKG).ipk control.tar.gz data.tar.gz  debian-binary

clean-ipk:
        rm -f control.tar.gz data.tar.gz

main.o: calc.h
stack.o: calc.h
getop.o: calc.h
getch.o:

.PHONY : clean
    clean :
             -rm polaca $(objects) 
