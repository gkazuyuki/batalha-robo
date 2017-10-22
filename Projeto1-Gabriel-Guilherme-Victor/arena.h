#ifndef __ARENA_H__
#define __ARENA_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "maq.h"

typedef struct {
    int num_bots;
    Maquina **robos;
    char *chapter;
    pos HQpos;
} army;


typedef struct  {
    Maquina *robo;
    int terrain, crystall, HQ, armyID;
    } node;

typedef node **board;

typedef struct {
    board Board;
    int army_number, top;
    army *army_vector;
    double time;
    int size; //Estamos considerando arena quadrada
    } Arena;

#define NUM_OF_BOTS 5

Arena arena;

pos numbToPos(int n, pos x);

void Atualiza();

Arena *InicializaArena(int size, int army_number);

void InsereExercito(char *name, int n, pos HQ, pos *army_poss, INSTR **program, int army_tag);

void RemoveExercito(char *name);

void Sistema(Maquina *robo);

void *emalloc(size_t size);

#endif
