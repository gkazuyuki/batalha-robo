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
