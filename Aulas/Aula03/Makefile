programa: STR.o Exemplo.o
	gcc STR.o Exemplo.o -o Teste.exe

STR.o: STR.c STR.h
	gcc -c STR.c -o STR.o

Exemplo.o: Exemplo.c
	gcc -c Exemplo.c -o Exemplo.o

run:
	./Teste.exe

clean:
	rm -f STR.o Exemplo.o Teste.exe
	rm -f STR.o Exemplo2.o Teste2.exe
	rm -f programa.o programa
