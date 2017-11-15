// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756

#include "arena.h"

// Recebe três strings e concatena.
char* concat(const char *s1, const char *s2, const char *s3)
{
    char *result = emalloc(strlen(s1)+strlen(s2)+1); //+1 para o null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    strcat(result, s3);
    return result;
}

pos numbToPos(int n, pos x)
{
    pos y;
    if (n == 0) {
        y.x = x.x;
        y.y = x.y - 1;
    }
    else if (n == 1) {
        y.x = x.x + 1;
        y.y = x.y - 1;
    }
    else if (n == 2) {
        y.x = x.x + 1;
        y.y = x.y + 1;
    }
    else if (n == 3) {
        y.x = x.x;
        y.y = x.y + 1;
    }
    else if (n == 4) {
        y.x = x.x - 1;
        y.y = x.y + 1;
    }
    else if (n == 5) {
        y.x = x.x - 1;
        y.y = x.y;
    }
    return y;
}


Arena *InicializaArena(int size, int army_number)
{
    Arena *new_arena = emalloc(size*sizeof(Arena));
    new_arena->size = size;
    new_arena->army_number = army_number;
    new_arena->top = 0;
    new_arena->time = 0; //FALTA O TEMPO AQUI
    new_arena->next_id = 0; 

    board new_board = emalloc(size*sizeof(node*)); //Criando tabuleiro nxn
    for (int i = 0; i < size; i++) {
        new_board[i] = emalloc(size*sizeof(node));
    }

    //Inicializa terreno e cristais
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            new_board[i][j].crystall = rand()%3; // 0, 1 ou 2 cristais na posição
            new_board[i][j].terrain = rand()%3; //Dois tipos de terreno: estrada, pantano.
            new_board[i][j].HQ = 0; //Sem HQ
            new_board[i][j].armyID = 0; //Inicializa em robos
        }
    new_arena->Board = new_board;

    new_arena->army_vector = emalloc(army_number*sizeof(army));

    return new_arena;
}

void destroyArena(int n)
{
    for (int i = 0; i < n; i++)
        free(arena.Board[i]);
    free(arena.Board);
    return;    
}

void Atualiza(FILE *display)
{
    for (int i = 0; i < arena.army_number; i++){
        /*Já cuida do fato de qur se um exercito foi removido ele não sera
         *considerado por ter num_bots = -1.
        */
        for (int j = 0; j < arena.army_vector[i].num_bots; j++){
            /*Vê se o robo ainda não foi destruido.
             */
            if (arena.Board[arena.army_vector[i].robos[j]->position.x][arena.army_vector[i].robos[j]->position.y].robo)
                exec_maquina(arena.army_vector[i].robos[j], 50, display);
        }
    }
    /*O tempo esta sendo contado por iteração da atualiza.
     */
    arena.time += 1;
    return;
}

void InsereExercito(char *name, int n, pos HQ, pos *army_poss, INSTR **program, int army_tag, FILE *display)
{
    arena.army_vector[arena.top].num_bots = n;
    arena.army_vector[arena.top].HQpos.x = HQ.x;
    arena.army_vector[arena.top].HQpos.y = HQ.y;
    arena.army_vector[arena.top].chapter = emalloc(1 + (strlen(name))*sizeof(char));
    arena.army_vector[arena.top].chapter = strcpy(arena.army_vector[arena.top].chapter, name);
    arena.army_vector[arena.top].robos = emalloc(n*sizeof(Maquina *));
    for (int i = 0; i < n; i++){
         arena.army_vector[arena.top].robos[i] = cria_maquina(program[i]);
         arena.army_vector[arena.top].robos[i]->position.x = army_poss[i].x;
         arena.army_vector[arena.top].robos[i]->position.y = army_poss[i].y;
         arena.army_vector[arena.top].robos[i]->id = arena.next_id; // Identificação do robô no controlador gráfico.
         arena.next_id++; // Atualiza ID do próximo robô a ser criado.
         fprintf(display, "%s", concat("rob assets/", name, ".png\n")); // Registra robô no controlador gráfico.
         arena.Board[army_poss[i].x][army_poss[i].y].armyID = army_tag;
         arena.Board[army_poss[i].x][army_poss[i].y].robo = arena.army_vector[arena.top].robos[i];
    }
    arena.top++;
    return;
}

void RemoveExercito(char *name)
{
    int i;
    for (i = 0; i < arena.army_number && strcmp(name, arena.army_vector[i].chapter) != 0; i++) {}
    if (i < arena.army_number) {
        for (int j = 0; j < arena.army_vector[i].num_bots; j++) {
            if (arena.army_vector[i].robos[j]){
                arena.Board[arena.army_vector[i].robos[j]->position.x][arena.army_vector[i].robos[j]->position.y].robo = NULL;
                arena.Board[arena.army_vector[i].robos[j]->position.x][arena.army_vector[i].robos[j]->position.y].armyID = 0;
                destroi_maquina(arena.army_vector[i].robos[j]);
            }
        }
        free(arena.army_vector[i].robos);
        arena.army_vector[i].num_bots = -1;

    }
    else {
        fprintf(stderr, "ERRO: Exército não existe.\n");
    }
}

void Sistema(Maquina *robo, FILE *display)
{
    OPERANDO tmp = desempilha(&robo->pil), aux = desempilha(&robo->pil);
    int in_swamp = 0;
    pos temp = numbToPos(aux.n, robo->position);
    
    //Ação MOV
    if (tmp.ac == 0) {
        if (arena.Board[robo->position.x][robo->position.y].terrain == 2) in_swamp = 1; //sair do pantano para uma estrada custa 1
        if (arena.Board[temp.x][temp.y].robo == NULL) {
            printf("FOI\n");
            fprintf(display, "%d %d %d %d %d\n",
                    robo->id, robo->position.x, robo->position.y, temp.x, temp.y);
            robo->position.x = temp.x;
            robo->position.y = temp.y;
            if (arena.Board[robo->position.x][robo->position.y].terrain != 2 && in_swamp){
                if (robo->n_crystalls > 0)
                    robo->n_crystalls--;
            }
        arena.Board[robo->position.x][robo->position.y].robo = robo;
        }
    }
    //Ação FETCH
    else if (tmp.ac == 10) {
        if (arena.Board[temp.x][temp.y].crystall > 0) {
            arena.Board[temp.x][temp.y].crystall--;
            robo->n_crystalls++;
        }
    }
    //Ação DEPO
    else if (tmp.ac == 20) {
        if (robo->n_crystalls > 0){
            arena.Board[temp.x][temp.y].crystall += robo->n_crystalls;
            robo->n_crystalls = 0;
        }
    }
    //Ação ATK
    else if (tmp.ac == 30) {
        if (arena.Board[temp.x][temp.y].robo != NULL) {
            if (arena.Board[temp.x][temp.y].robo->n_crystalls > 0) {
                robo->n_crystalls += arena.Board[temp.x][temp.y].robo->n_crystalls;
                arena.Board[temp.x][temp.y].robo->n_crystalls = 0;
            }
            else {
                arena.Board[temp.x][temp.y].armyID = 0;
                arena.Board[temp.x][temp.y].robo = NULL;
            }
        }
    }
    return;
}

void *emalloc(size_t size)
{
    void *pointer;
    pointer = malloc(size);

    if (pointer == NULL) {
        fprintf(stderr,
                "ERRO: Não foi possível alocar memória suficiente.\n");
        exit(EXIT_FAILURE);
    }
    else
        return pointer;
}
