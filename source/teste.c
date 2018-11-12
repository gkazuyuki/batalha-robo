// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756

#include <stdio.h>
#include <stdlib.h>
#include "compila.tab.h"
#include "maq.h"
#include "arena.h"

INSTR p1[20000];
INSTR p2[20000];
INSTR p3[20000];
INSTR p4[20000];

int compilador(FILE *, INSTR *);

int main()
{
    FILE *p;

    int res;
  	p = fopen("prog1", "r");
    res = compilador(p, p1);
    if (res) return 1;

    p = fopen("prog2" ,"r");
    res = compilador(p, p2);
    if (res) return 1;

    p = fopen("prog3" ,"r");
    res = compilador(p, p3);
    if (res) return 1;

    p = fopen("prog4" ,"r");
    res = compilador(p, p4);
    if (res) return 1;


    FILE *display = popen("./apres", "w");
    Arena *nova_arena;
    nova_arena = InicializaArena(15, 2, display);
    arena = *nova_arena;


    INSTR *army_prog1[] = {p1, p2};
    INSTR *army_prog2[] = {p3, p4};

    pos hq_pos1 = {3, 3};
    pos hq_pos2 = {10, 10};
    pos army_pos1[] = {{7, 7}, {9, 9}};
    pos army_pos2[] = {{3, 3}, {14, 7}};

    InsereExercito("Black_Templars", 2, hq_pos1, army_pos1, army_prog1, 1, display);
    InsereExercito("Ultramarines", 2, hq_pos2, army_pos2, army_prog2, 2, display);

    while (arena.time < 1000)
        Atualiza(display);
    RemoveExercito("Black_Templars");
    RemoveExercito("Ultramarines");
    destroyArena(arena.size);
    pclose(display);
    return 0;
}
