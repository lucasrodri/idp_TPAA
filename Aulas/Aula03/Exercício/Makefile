programa: matriz.o programa.o
	gcc matriz.o programa.o -o programa

matriz.o: matriz.c matriz.h
	gcc -c matriz.c -o matriz.o

programa.o: programa.c matriz.h
	gcc -c programa.c -o programa.o

run:
	./programa

clean:
	rm -f matriz.o programa.o programa

all: programa run clean
