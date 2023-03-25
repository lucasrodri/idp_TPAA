programa: fila.o programa.o
	gcc fila.o programa.o -o programa

fila.o: fila.c fila.h
	gcc -c fila.c -o fila.o

programa.o: programa.c fila.h
	gcc -c programa.c -o programa.o

run:
	./programa

clean:
	rm -f fila.o programa.o programa

all: programa run clean
