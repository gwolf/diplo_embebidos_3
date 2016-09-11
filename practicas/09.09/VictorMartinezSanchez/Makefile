
GCC = gcc
CFLAGS = -lpthread
OBJ = get_max.o get_min.o main.o
DESTDIR = /usr/local/bin
OUT = prog

all: bin

%.o: %.c
	$(GCC) -c -o $@ $<

$(OUT): $(OBJ) 
	$(GCC) $(CFLAGS) $(OBJ) -o $(OUT)

bin: $(OUT)

clear:
	rm -f $(OBJ)

clean:
	rm -f $(OBJ) $(OUT)

run: bin
	./$(OUT)

install: bin
	[ -d $(DESTDIR) ] || mkdir -p $(DESTDIR)
	cp ./$(OUT) $(DESTDIR)

uninstall:
	-rm $(DESTDIR)/$(OUT)
