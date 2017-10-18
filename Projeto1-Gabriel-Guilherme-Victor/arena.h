typedef struct {
    int numb_robots;
    pos *robots;
    Maquina **robo;
    char *chapter;
} army;


typedef struct  {
    Maquina *robo;
    short unsigned int terrain, crystall, HQ;
    } node;

typedef node **board;

typedef struct {
    board Board;
    int army_number;
    army *army_vector;
    double time;
    } Arena;


void Atualiza();

void InsereExercito(char *name, int n);

void RemoveExercito(char *name, int n);

void Sistema(Maquina *robo, int opcode, pos cords);
