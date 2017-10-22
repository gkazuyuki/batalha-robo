// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756

#include <stdio.h>
#include <stdlib.h>
#include "maq.h"
#include "arena.h"

INSTR SYS[] = {
    {PUSH, 3},
    {ATR, 0},
    {MOV, 2},
    {FETCH, 4},
    {DEPO, 0},
    {END, 0},
};

INSTR Atack[] = {
    {ATK, 0},
    {ATK, 1},
    {ATK, 4},
    {ATK, 5},
    {END,  0},
};

INSTR fat[] = {
    {PUSH, 10},  // 0
    {CALL, 4},  // 1
    {PRN,  0},  // 2
    {END,  0},  // 3

    // FAT
    {ALC,  1},  // 4
    {DUP,  0},  // 5
    {STL,  0},  // 6 n
    {PUSH, 1},  // 7
    {EQ,   0},  // 8 n == 1 ?
    {JIF, 13},  // 9
    {PUSH, 1},  // 10
    {FRE,  1},  // 11
    {RET,  0},  // 12
    {RCE,  0},  // 13 n
    {PUSH, 1},  // 14
    {SUB,  0},  // 15 n-1
    {CALL, 4},  // 16 fat(n-1)
    {RCE,  0},  // 17 n
    {MUL,  0},  // 18 n * fat(n-1)
    {FRE,  1},  // 19
    {RET,  0}   // 20
};

INSTR *army_prog1[] = {Atack, fat, SYS};
INSTR *army_prog2[] = {SYS, fat, fat};
INSTR *army_prog3[] = {fat, Atack, SYS};

int main() {
    Arena *nova_arena;
    nova_arena = InicializaArena(50, 3);
    arena = *nova_arena;

    pos hq_pos1 = {10, 10};
    pos army_pos1[] = {{15, 15}, {15, 14}, {14, 15}};
    InsereExercito("Black_Templars", 3, hq_pos1, army_pos1, army_prog1, 1);

    pos hq_pos2 = {20, 20};
    pos army_pos2[] = {{25, 25}, {25, 24}, {26, 25}};
    InsereExercito("Dark_Angels", 3, hq_pos2, army_pos2, army_prog2, 2);

    pos hq_pos3 = {30, 30};
    pos army_pos3[] = {{15, 16}, {5, 4}, {6, 25}};
    InsereExercito("Ultramarines", 3, hq_pos3, army_pos3, army_prog3, 3);

    while (arena.time < 5)
        Atualiza();
    RemoveExercito("Black_Templars");
    RemoveExercito("Dark_Angels");
    RemoveExercito("Ultramarines");
    destroyArena(arena.size);

    return 0;
}
