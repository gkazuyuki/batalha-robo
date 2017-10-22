# Guilherme Costa Vieira               Nº USP: 9790930
# Gabriel Kazuyuki Isomura             Nº USP: 9793673
# Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756


CC = gcc

all : maq.o arena.o pilha.o teste.o
	gcc -o teste $?

maq.o :	maq.c
	$(CC) $? -c
arena.o : arena.c
	$(CC) $? -c
pilha.o : pilha.c
	$(CC) $? -c
teste.o : teste.c
	$(CC) $? -c

clean :
	rm *.o teste
