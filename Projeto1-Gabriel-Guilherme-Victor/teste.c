// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756

#include <stdio.h>
#include <stdlib.h>
#include "maq.h"
#include "arena.h"

INSTR SYS[] = {
    {FETCH, 0},
    {FETCH, 1},
    {FETCH, 2},
    {FETCH, 3},
    {FETCH, 4},
    {FETCH, 5},
    {MOV, 0},
    {DEPO, 2},
    {DEPO, 1},
    {DEPO, 2},
    {DEPO, 3},
    {DEPO, 4},
    {DEPO, 5},
    {END, 0},

};

INSTR mov[] = {
    {MOV, 0},
    {MOV, 1},
    {MOV, 2},
    {MOV, 3},
    {MOV, 4},
    {MOV, 5},
    {END, 0},
};

INSTR Atack[] = {
    {ATK, 5},
    {ATK, 5},
    {ATK, 1},
    {ATK, 1},
    {ATK, 2},
    {ATK, 2},
    {ATK, 3},
    {ATK, 3},
    {ATK, 4},
    {ATK, 4},
    {ATK, 0},
    {ATK, 0},
    {END, 0},
};



INSTR *army_prog1[] = {Atack, mov};
INSTR *army_prog2[] = {Atack, SYS};


int main() {
    FILE *display = popen("./apres", "w");
    Arena *nova_arena;
    //nova_arena = InicializaArena(15, 3, display);
    nova_arena = InicializaArena(15, 2, display);
    arena = *nova_arena;

    pos hq_pos1 = {3, 3};
    pos army_pos1[] = {{7, 7}, {4,4}};
    pos hq_pos2 = {10, 10};
    pos army_pos2[] = {{7, 6}, {11,11}};

    InsereExercito("Black_Templars", 2, hq_pos1, army_pos1, army_prog1, 1, display);
    InsereExercito("Ultramarines", 2, hq_pos2, army_pos2, army_prog2, 2, display);

    while (arena.time < 1000)
        Atualiza(display);
    RemoveExercito("Black_Templars");
    RemoveExercito("Ultramarines");
    destroyArena(arena.size);
    sleep(3);
    pclose(display);



    return 0;
}
