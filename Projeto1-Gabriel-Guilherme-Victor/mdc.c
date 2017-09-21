
#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

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
};

int main(int ac, char **av) {
  Maquina *maq = cria_maquina(prog);
  exec_maquina(maq, 10000);
  destroi_maquina(maq);
  return 0;
}
