main: tabelahash.o lista.o programa.o
	gcc tabelahash.o lista.o programa.o -o main

tabelahash.o: tabelahash.c tabelahash.h
	gcc -c tabelahash.c -o tabelahash.o

lista.o: lista.c lista.h
	gcc -c lista.c -o lista.o

programa.o: programa.c lista.h tabelahash.h
	gcc -c programa.c -o programa.o

run:
	./main

clean:
	rm -f tabelahash.o lista.o programa.o main

all: main run clean
