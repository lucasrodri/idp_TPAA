main: git.o main.o tools.o
	gcc git.o main.o tools.o -o main

git.o: git.c git.h
	gcc -c git.c -o git.o

tools.o: tools.c tools.h
	gcc -c tools.c -o tools.o

main.o: main.c git.h
	gcc -c main.c -o main.o

run:
	./main

clean:
	rm -f git.o main.o tools.o main

all: clean main run clean