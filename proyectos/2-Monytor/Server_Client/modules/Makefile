GCC = gcc
CFLAGS = -Wall
OBJ_GSM = GSM_Module.o
GSM = gsm_module
OBJ_GPS = GPS_Module.o
GPS = gps_module
DESTDIR = /usr/bin
BIN = $(DESTDIR)/usr/bin


all: bin

%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

$(GSM): $(OBJ_GSM)
	$(GCC) $(CFLAGS) $(OBJ_GSM) -o $(GSM)

$(GPS): $(OBJ_GPS)
	$(GCC) $(CFLAGS) $(OBJ_GPS) -o $(GPS)

bin: $(GSM) $(GPS)

clear:
	rm -f $(OBJ_GSM) $(OBJ_GPS)

clean:
	rm -f $(OBJ_GSM) $(OBJ_GPS) $(GSM) $(GPS)

install: bin
	install -d $(BIN)
	install ./$(GSM) $(BIN)
	install ./$(GPS) $(BIN)

uninstall:
	-rm $(BIN)/$(GSM)
	-rm $(BIN)/$(GPS)

