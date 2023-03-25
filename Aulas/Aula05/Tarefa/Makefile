programa: pilha.o programa.o
	gcc pilha.o programa.o -o programa

pilha.o: pilha.c pilha.h
	gcc -c pilha.c -o pilha.o

programa.o: programa.c pilha.h
	gcc -c programa.c -o programa.o

programa2: pilha.o programa2.o
	gcc pilha.o programa2.o -o programa2

programa2.o: programa2.c pilha.h
	gcc -c programa2.c -o programa2.o

run:
	./programa

clean:
	rm -f pilha.o programa.o programa programa2.o programa2

all: programa run clean
