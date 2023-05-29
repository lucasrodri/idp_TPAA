main: arvoreb.o programa.o
	gcc arvoreb.o programa.o -o main

arvoreb.o: arvoreb.c arvoreb.h
	gcc -c arvoreb.c -o arvoreb.o

programa.o: programa.c arvoreb.h
	gcc -c programa.c -o programa.o

run:
	./main

clean:
	rm -f arvoreb.o programa.o main

all: clean main run clean
