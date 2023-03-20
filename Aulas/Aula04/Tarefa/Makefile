programa: lista.o programa.o
	gcc lista.o programa.o -o programa

lista.o: lista.c lista.h
	gcc -c lista.c -o lista.o

programa.o: programa.c lista.h
	gcc -c programa.c -o programa.o

run:
	./programa

clean:
	rm -f lista.o programa.o programa

all: programa run clean
