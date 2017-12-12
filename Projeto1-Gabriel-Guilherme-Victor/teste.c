// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756

#include <stdio.h>
#include <stdlib.h>
#include "compila.tab.h"
#include "maq.h"
#include "arena.h"

INSTR p1[2000];

int compilador(FILE *, INSTR *);

int main(int ac, char **av) {
    FILE *p = stdin;

    int res;
    ac --; av++;
    if (ac > 0)
  	    p = fopen(*av,"r");
    res = compilador(p, p1);
    if (res) return 1;

    FILE *display = popen("./apres", "w");
    Arena *nova_arena;
    nova_arena = InicializaArena(15, 1, display);
    arena = *nova_arena;


    INSTR *army_prog1[] = {p1};
    pos hq_pos1 = {3, 3};
    pos army_pos1[] = {{7, 7}};

    InsereExercito("Black_Templars", 1, hq_pos1, army_pos1, army_prog1, 1, display);

    while (arena.time < 1000)
        Atualiza(display);
    RemoveExercito("Black_Templars");
    destroyArena(arena.size);
    pclose(display);
    return 0;
}
