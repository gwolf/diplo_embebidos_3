CC=gcc
CFLAGS=-I.
DEPS = hellomake.h 
#Macro DEPS que incluye los archivos .h los cuales los .c dependen.
# Regla que aplica a todos los archivos .o, la regla dice que los .o dependen si hay cambios
# en los archivos .c y .h, tambien dice que para generar el archivo .o, make necesita compilar 
# .c con el compilador indicado con la macro CC.
# la bandera -c indica que se genera el object file
# "-o $@" dice que la salida de la compilación se pondra en el archivo a la izquierda de :
# "$<" es el primer archivo en la lista de dependencias

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
hellomake: hellomake.o hellofunc.o
	gcc hellomake.o hellofunc.o -I. 
