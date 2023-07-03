main: git.o main.o tools.o tabelahash.o client.o
	gcc git.o main.o tools.o tabelahash.o client.o -o main

server: git.o tabelahash.o server.o
	gcc git.o tabelahash.o server.o -o server

server.o: server.c 
	gcc -c server.c -o server.o

git.o: git.c git.h tabelahash.h
	gcc -c git.c -o git.o

tools.o: tools.c tools.h
	gcc -c tools.c -o tools.o

main.o: main.c git.h
	gcc -c main.c -o main.o

tabelahash.o: tabelahash.c tabelahash.h git.h
	gcc -c tabelahash.c -o tabelahash.o

client.o: client.c client.h
	gcc -c client.c -o client.o

run:
	./main

clean:
	rm -f git.o main.o tools.o tabelahash.o client.o server.o main

all: clean main run clean
