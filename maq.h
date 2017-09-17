#include "pilha.h"

#define MAXMEM 100

typedef struct {
  Pilha pil;
  Pilha exec;
  //add
  Pilha bases; // Pilha das bases
  int base; // Base da função local
  //add
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int ip;

  int rbp;
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);
