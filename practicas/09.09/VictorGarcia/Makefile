GCC = gcc 
DESTDIR = /usr/local/bin/

all: binario

%.o: %.c
	$(GCC) -c $<

binario: serial.o principal.o
	$(GCC) serial.o principal.o -o principal

clean:
	rm -f *.o principal

install: binario
	[ -d $(DESTDIR) ] || mkdir -p $(DESTDIR)
	sudo cp principal $(DESTDIR)

uninstall:
	-rm $(DESTDIR)/principal
	@echo "Desinstalando..."

.PHONY: clean, install, uninstall, binario
