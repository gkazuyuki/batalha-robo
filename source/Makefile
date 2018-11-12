# Guilherme Costa Vieira               Nº USP: 9790930
# Gabriel Kazuyuki Isomura             Nº USP: 9793673
# Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756


compila: compila.tab.o lex.yy.o symrec.o acertos.o maq.o pilha.o teste.o arena.o
	gcc -o $@ $^ -lm -lfl

compila.tab.o: compila.y
	bison -d compila.y
	gcc -c compila.tab.c

lex.yy.o: compila.l
	flex compila.l
	gcc -c lex.yy.c


clean:
	rm -f *.o lex.yy.c compila.tab.c compila.tab.h *~ compila
