main: tabelahash.o aluno.o programa.o
	gcc tabelahash.o aluno.o programa.o -o main

tabelahash.o: tabelahash.c tabelahash.h
	gcc -c tabelahash.c -o tabelahash.o

aluno.o: aluno.c aluno.h
	gcc -c aluno.c -o aluno.o

programa.o: programa.c aluno.h tabelahash.h
	gcc -c programa.c -o programa.o

run:
	./main

clean:
	rm -f tabelahash.o aluno.o programa.o main

all: main run clean
