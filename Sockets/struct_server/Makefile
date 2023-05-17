main: server.o client.o aluno.o
	gcc server.o aluno.o -o server
	gcc client.o aluno.o -o client

server.o: server.c aluno.h
	gcc -c server.c -o server.o

client.o: client.c aluno.h
	gcc -c client.c -o client.o

aluno.o: aluno.c aluno.h
	gcc -c aluno.c -o aluno.o

clean:
	rm -f server client aluno.o server.o client.o
