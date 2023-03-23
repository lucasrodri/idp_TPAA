programa: racional.o programa.o
	gcc racional.o programa.o -o programa

racional.o: racional.c racional.h
	gcc -c racional.c -o racional.o

programa.o: programa.c racional.h
	gcc -c programa.c -o programa.o

run:
	./programa

clean:
	rm -f racional.o programa.o programa

all: programa run clean
