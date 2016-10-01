
GCC = gcc
CFLAGS = -lpthread
OBJ = get_max.o get_min.o main.o
DESTDIR = /usr/local/bin
BIN = $(DESTDIR)/usr/local/bin
OUT = prog

all: bin

%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

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
	install -d $(BIN)
	install ./$(OUT) $(BIN)

uninstall:
	-rm $(BIN)/$(OUT)
