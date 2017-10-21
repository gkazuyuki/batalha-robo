#ifndef __ARENA_H__
#define __ARENA_H__

#include "maq.h"
#include <stdlib.h>

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

void Atualiza();

void InsereExercito(char *name, int n);

void RemoveExercito(char *name, int n);

void Sistema(Maquina *robo);

#endif
