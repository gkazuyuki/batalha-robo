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

INSTR Test[] = {
    {MOV, 0},
    {MOV, 3},
};

INSTR DepTest[] = {
    {MOV, 0},
    {MOV, 3},
    {MOV, 1},
    {MOV, 4},
    {MOV, 2},
    {MOV, 5},
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

INSTR *army_prog1[] = {DepTest};

/*
INSTR *army_prog1[] = {Test, Test, Test};
INSTR *army_prog2[] = {Test, Test, Test};
INSTR *army_prog3[] = {Test, Test, Test};
*/

int main() {
    FILE *display = popen("./apres", "w");
    Arena *nova_arena;
    //nova_arena = InicializaArena(15, 3, display);
    nova_arena = InicializaArena(15, 1, display);
    arena = *nova_arena;

    /*
    pos hq_pos1 = {1, 1};
    pos army_pos1[] = {{1, 2}, {2, 2}, {2, 1}};
    InsereExercito("Black_Templars", 3, hq_pos1, army_pos1, army_prog1, 1, display);

    pos hq_pos2 = {7, 9};
    pos army_pos2[] = {{7, 8}, {6, 9}, {5, 8}};
    InsereExercito("Dark_Angels", 3, hq_pos2, army_pos2, army_prog2, 2, display);

    pos hq_pos3 = {14, 1};
    pos army_pos3[] = {{6, 1}, {7, 2}, {6, 2}};
    InsereExercito("Ultramarines", 3, hq_pos3, army_pos3, army_prog3, 3, display);
	*/

    pos hq_pos1 = {1, 1};
    pos army_pos1[] = {{7, 7}};

    InsereExercito("Black_Templars", 1, hq_pos1, army_pos1, army_prog1, 1, display);

    while (arena.time < 100)
        Atualiza(display);
    RemoveExercito("Black_Templars");
    //RemoveExercito("Dark_Angels");
    //RemoveExercito("Ultramarines");
    destroyArena(arena.size);
    pclose(display);

    return 0;
}
