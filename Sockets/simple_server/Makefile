main: server.o client.o 
	gcc server.c -o server
	gcc client.c -o client

server.o: server.c
	gcc -c -g server.c -o server.o

client.o: client.c
	gcc -c -g client.c -o client.o

clean:
	rm -f server client client.o server.o
