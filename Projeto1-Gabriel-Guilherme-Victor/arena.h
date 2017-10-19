#include "maq.h"

typedef struct {
    int numb_robots;
    pos *robots;
    Maquina **robo;
    char *chapter;
} army;


typedef struct  {
    Maquina *robo;
    int terrain, crystall, HQ, roboID;
    } node;

typedef node **board;

typedef struct {
    board Board;
    int army_number;
    army *army_vector;
    double time;
    int size; //Estamos considerando arena quadrada
    } Arena;


void Atualiza();

void InsereExercito(char *name, int n);

void RemoveExercito(char *name, int n);

void Sistema(Maquina *robo, int opcode, pos cords);
