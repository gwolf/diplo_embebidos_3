IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)
ODIR=obj

_DEPS = hellomake.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = hellomake.o hellofunc.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#Macro DEPS que incluye los archivos .h los cuales los .c dependen.
#Macro OBJ que incluye los archivos
# Regla que aplica a todos los archivos .o, la regla dice que los .o dependen en los cambios
# de .c y .h, tambien dice que para generar el archivo .o, make necesita compilar 
# .c con el compilador indicado con la macro CC.
# la bandera -c indica que se genera el object file
# "-o $@" dice que la salida de la compilación se pondra en el archivo a la izquierda de :
# "$<" es el primer archivo en la lista de dependencias

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
hellomake: $(OBJ)
	gcc $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
