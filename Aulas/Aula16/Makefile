main: arvoreAVL.o programa.o
	gcc arvoreAVL.o programa.o -o main

arvoreAVL.o: arvoreAVL.c arvoreAVL.h
	gcc -c arvoreAVL.c -o arvoreAVL.o

programa.o: programa.c arvoreAVL.h
	gcc -c programa.c -o programa.o

run:
	./main

clean:
	rm -f arvoreAVL.o programa.o main

all: clean main run clean
