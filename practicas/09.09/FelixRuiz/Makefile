#
# Makefile exercise
#

# **********  Macros **********
INSTPATH=./bin/myapp
INCPATH=./include
OBJPATH=./obj
CC=gcc
CFLAGS=-g -Wall -I$(INCPATH)
COND1=`stat app 2>/dev/null | grep Modify`
COND2=`stat $(INSTPATH) 2>/dev/null | grep Modify`

# Targets

all: getobj app install misobj

app: factorial.o compara.o
	$(CC) $(CFLAGS) -o app factorial.o compara.o

factorial.o: factorial.c $(INCPATH)/valida.h
	$(CC) $(CFLAGS) -c factorial.c

compara.o: compara.c
	$(CC) $(CFLAGS) -c compara.c

getobj:
	-mv $(OBJPATH)/*.o . 2>/dev/null

misobj:
	-mv *.o $(OBJPATH) 2>/dev/null
 
# Solo funcionará cuando los archivos hayan cambiado
install:
	@if [ "$(COND1)" != "$(COND2)" ];\
	then\
		cp -p ./app $(INSTPATH) 2>/dev/null;\
		chmod 700 $(INSTPATH);\
		echo "Mi aplicación fue instalada en: " $(INSTPATH);\
	fi

# Haciendo limpieza
cleanall:
	-rm -f app
	-rm -f $(OBJPATJ)/*.o
	-rm -f $(INSTPATH)
