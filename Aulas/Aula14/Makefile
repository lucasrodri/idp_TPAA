main: grafo.o programa.o
	gcc grafo.o programa.o -o main

grafo.o: grafo.c grafo.h
	gcc -c grafo.c -o grafo.o

programa.o: programa.c grafo.h
	gcc -c programa.c -o programa.o

run:
	./main

clean:
	rm -f grafo.o programa.o main

all: clean main run clean
