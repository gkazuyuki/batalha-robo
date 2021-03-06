// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756


#ifndef __PILHA_H__
#define __PILHA_H__

#include "instr.h"

#define PILMAX 99

typedef struct {
    int topo;
    OPERANDO val[PILMAX+1];
} Pilha;

Pilha *cria_pilha();

void destroi_pilha(Pilha *p);

void empilha(Pilha *p, OPERANDO op);

OPERANDO desempilha(Pilha *p);

void imprime(Pilha *p, int n);

#endif
