GCC = gcc
CFLAGS =
LFLAGS =
DESTDIR = /usr/local/bin/
BINDIR = usr/local/bin/
BINROOT = usr

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: install

pack: principal control
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	cp principal $(BINDIR)
	tar -zcvf data.tar.gz $(BINDIR)
	tar -zcvf control.tar.gz control
	echo "2.0" > debian_binary
	ar r ejemplo_alu.ipk control.tar.gz data.tar.gz debian_binary

install: principal
	[ -d $(DESTDIR) ] || mkdir -p $(DESTDIR)
	cp principal $(DESTDIR)

uninstall:
	[ -f "$(DESTDIR)principal" ]
	rm "$(DESTDIR)principal"

principal: $(OBJS)
	$(GCC) $(LFLAGS) -o $@ $^

%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o principal
	rm control.tar.gz
	rm data.tar.gz
	rm ejemplo_alu.ipk
	rm debian_binary
	rm -R $(BINROOT)

.PHONY: clean install
