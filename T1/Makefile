all: main

main:	dicionario.o le_entrada.o
	gcc -o main *.o

dicionario.o: dicionario.h

le_entrada.o: dicionario.h

run:
	./main
