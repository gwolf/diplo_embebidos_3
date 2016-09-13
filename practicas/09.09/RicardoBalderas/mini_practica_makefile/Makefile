GCC = gcc
CFLAGS =
LFLAGS =
DESTDIR = /usr/local/bin/

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: install

install: principal
	[ ! -d $(DESTDIR) ] && mkdir -p $(DESTDIR)
	cp principal $(DESTDIR)

principal: $(OBJS)
	$(GCC) $(LFLAGS) -o $@ $^
	
%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o principal

.PHONY: clean install
