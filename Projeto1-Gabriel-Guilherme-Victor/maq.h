// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756


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
    int id;
    pos position;
    int n_crystalls;
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n, FILE *display);

#endif
