
#include <stdio.h>
#include <stdlib.h>
#include "maq.h"
#include "arena.h"

INSTR fat[] = {
    {PUSH, 10},  // 0
    {ATK, 0},
    {CALL, 5},  // 1
    {PRN,  0},  // 2
    {END,  0},  // 3

    // FAT
    {ALC,  1},  // 4
    {DUP,  0},  // 5
    {STL,  0},  // 6 n
    {PUSH, 1},  // 7
    {EQ,   0},  // 8 n == 1 ?
    {JIF, 14},  // 9
    {PUSH, 1},  // 10
    {FRE,  1},  // 11
    {RET,  0},  // 12
    {RCE,  0},  // 13 n
    {PUSH, 1},  // 14
    {SUB,  0},  // 15 n-1
    {CALL, 5},  // 16 fat(n-1)
    {RCE,  0},  // 17 n
    {MUL,  0},  // 18 n * fat(n-1)
    {FRE,  1},  // 19
    {RET,  0}   // 20
};

INSTR *army_prog[] = {fat, fat, fat};

int main(int ac, char **av) {
    Arena *nova_arena;
    nova_arena = InicializaArena(50, 2);
    arena = *nova_arena;

    pos hq_pos1 = {10, 10};
    pos army_pos1[] = {{15, 15}, {15, 14}, {14, 15}};
    InsereExercito("army1", 3, hq_pos1, army_pos1, army_prog, 1);

    pos hq_pos2 = {30, 30};
    pos army_pos2[] = {{25, 25}, {25, 24}, {26, 25}};
    InsereExercito("army2", 3, hq_pos2, army_pos2, army_prog, 2);
    while (arena.time < 5) Atualiza();
    RemoveExercito("army1");
    RemoveExercito("army2");

    return 0;
}
