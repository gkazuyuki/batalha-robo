#ifndef __MAQ_H__
#define __MAQ_H__

#include "pilha.h"

#define MAXMEM 100

typedef struct {
    int x, y;
    } pos;

typedef struct {
  Pilha pil;
  Pilha exec;
  Pilha bases;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  OPERANDO base;
  int ip;
  pos position;
  int n_crystalls;
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);

#endif
