PROJECT	= principalProyecto
CC	= gcc
CFLAGS 	= -I -Wall
LDFLAGS	= -lm -lpthread
DESTDIR	= /usr/local/bin/

SOURCES	= $(wildcard *.c)
OBJS	= $(SOURCES:.c=.o)

all: $(PROJECT)

$(PROJECT): $(OBJS) 
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o $(PROJECT)

install: TARGET
	[ -d $(DESTDIR) ] && mkdir -p $(DESTDIR)
	sudo cp $(PROJECT) $(DESTDIR)

uninstall:
	-rm $(DESTDIR)/$(PROJECT)
	@echo "Desinstalando..."

.PHONY: clean, install, uninstall
