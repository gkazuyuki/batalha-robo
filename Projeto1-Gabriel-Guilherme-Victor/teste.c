
#include <stdio.h>
#include <stdlib.h>
#include "maq.h"
#include "arena.h"

INSTR prog[] = {
  {PUSH, 30},
  {PUSH, 24},
  {CALL, 12},
  {POP, 0},
  {DUP, 0},
  {PUSH, 0},
  {LT, 0},
  {JIF, 10},
  {PUSH, -1},
  {MUL, 0},
  {PRN, 0},
  {END, 0},

  {ALC, 2},
  {STL, 1},
  {STL, 0},
  {RCE, 1},
  {RCE, 0},
  {RCE, 1},
  {DUP, 0},
  {PUSH, 0},
  {EQ, 0},
  {JIF, 24},
  {FRE, 2},
  {RET, 0},
  {RCE, 0},
  {RCE, 1},
  {LT, 0},
  {JIF, 32},
  {POP, 0},
  {POP, 0},
  {RCE, 1},
  {RCE, 0},
  {SUB, 0},
  {FRE, 2},
  {CALL, 12},
  {RET, 0},


  {MOV, 3},
  {MOV, 4},
  {MOV, 3}
};

INSTR *army_prog[] = {prog, prog, prog};

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

    while (arena.time < 100) Atualiza();

    RemoveExercito("mdc", 1);
    RemoveExercito("recon", 3);

    return 0;
}
