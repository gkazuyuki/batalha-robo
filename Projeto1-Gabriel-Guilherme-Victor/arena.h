typedef struct {
    int x, y;
    } pos;

typedef struct {
    int numb_robots;
    pos *robots;
    char *chapter;
} army;


typedef struct  {
    Maquina *robo;
    short unsigned int terrain, crystall, HQ;
    } node;

typedef node **board;

typedef struct {
    board Board;
    army *army_vector;
    double time;
    } Arena;


void Atualiza();

void InsereExercito(char *name, int n);

void RemoveExercito(char *name, int n);

Sistema(Maquina *robo, int opcode, pos cords);
