// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756

#include "arena.h"
#include <unistd.h>
// Recebe três strings e concatena.
char* concat(const char *s1, const char *s2, const char *s3)
{
    char *result = emalloc(strlen(s1)+strlen(s2)+1); //+1 para o null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    strcat(result, s3);
    return result;
}

/* Recebe uma posição na matriz hexagonal x e uma direção n. Retorna uma nova
 * posição que segue o mapa abaixo:
                                      ____
                                     /    \
                                ____/  0   \____
                               /    \      /    \
                              /  5   \____/  1   \
                              \      /    \      /
                               \____/ POS  \____/
                               /    \      /    \
                              /  4   \____/  2   \
                              \      /    \      /
                               \____/  3   \____/
                                    \      /
                                     \____/

*/
pos numToPos(int n, pos x)
{
    pos y;
    if (n == 0) {
        y.x = x.x;
        y.y = x.y - 1;
    }
    else if (n == 1) {
        y.x = x.x + 1;
        if (x.x % 2 == 0)
            y.y = x.y - 1;
        else
            y.y = x.y;
    }
    else if (n == 2) {
        y.x = x.x + 1;
        if (x.x % 2 == 0)
            y.y = x.y;
        else
            y.y = x.y + 1;
    }
    else if (n == 3) {
        y.x = x.x;
        y.y = x.y + 1;
    }
    else if (n == 4) {
        y.x = x.x - 1;
        if (x.x % 2 == 0)
            y.y = x.y;
        else
            y.y = x.y + 1;
    }
    else if (n == 5) {
        y.x = x.x - 1;
        if (x.x % 2 == 0)
            y.y = x.y - 1;
        else
            y.y = x.y;
    }
    return y;
}

Arena *InicializaArena(int size, int army_number, FILE *display)
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
            new_board[i][j].terrain = rand()%3; //Dois tipos de terreno: estrada, pantano.
            fprintf(display, "cel %d %d %d\n", i, j, new_board[i][j].terrain);
            fflush(display);

            double prob = (double)rand()/(double)RAND_MAX;
            if (prob < (double)1/4) {
                if (prob > (double)1/8) new_board[i][j].crystall = 1;
                else if (prob < (((double)1/8)*((double)3/4))) new_board[i][j].crystall = 2;
                else new_board[i][j].crystall = 3;
            }
            else
                new_board[i][j].crystall = 0; // 0 cristais na posição

            if (new_board[i][j].crystall > 0) {
                fprintf(display, "cristais %d %d %d\n", new_board[i][j].crystall, i, j);
                fflush(display);
            }
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
                exec_maquina(arena.army_vector[i].robos[j], 10, display);
        }
    }
    /*O tempo esta sendo contado por iteração da atualiza.
     */
    arena.time += 10;
    return;
}

void InsereExercito(char *name, int n, pos HQ, pos *army_poss, INSTR **program, int army_tag, FILE *display)
{
    arena.army_vector[arena.top].num_bots = n;
    arena.army_vector[arena.top].HQpos.x = HQ.x;
    arena.army_vector[arena.top].HQpos.y = HQ.y;
    fprintf(display, "%s %d %d\n", concat("base assets/HQ", name, ".png"), HQ.x, HQ.y);
    fflush(display);
    arena.army_vector[arena.top].chapter = emalloc(1 + (strlen(name))*sizeof(char));
    arena.army_vector[arena.top].chapter = strcpy(arena.army_vector[arena.top].chapter, name);
    arena.army_vector[arena.top].robos = emalloc(n*sizeof(Maquina *));
    for (int i = 0; i < n; i++){

         arena.army_vector[arena.top].robos[i] = cria_maquina(program[i]);
         arena.army_vector[arena.top].robos[i]->position.x = army_poss[i].x;
         arena.army_vector[arena.top].robos[i]->position.y = army_poss[i].y;
         arena.army_vector[arena.top].robos[i]->armyID = army_tag;
         arena.army_vector[arena.top].robos[i]->id = arena.next_id; // Identificação do robô no controlador gráfico.
         arena.next_id++; // Atualiza ID do próximo robô a ser criado.
         fprintf(display, "%s", concat("rob assets/", name, ".png\n")); // Registra robô no controlador gráfico.
         // Imprime a primeira posição do robô
         fprintf(display, "%d %d %d %d %d\n",
                    arena.army_vector[arena.top].robos[i]->id,
                    arena.army_vector[arena.top].robos[i]->position.x,
                    arena.army_vector[arena.top].robos[i]->position.y,
                    arena.army_vector[arena.top].robos[i]->position.x,
                    arena.army_vector[arena.top].robos[i]->position.y);
         fflush(display); // Força os comandos acima executar imediatamente.
         //sleep(); //RETIRAR ISSO AQUI DEBUG
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
    pos temp = numToPos(aux.n, robo->position);
    if (temp.x >= arena.size || temp.y >= arena.size){
        robo->counter += 1;
        return;
    }
    //Ação MOV
    if (tmp.ac == 0) {
        if (arena.Board[robo->position.x][robo->position.y].terrain == 2) in_swamp = 1; //sair do pantano para uma estrada custa 1
        if (arena.Board[temp.x][temp.y].robo == NULL) {
            fprintf(display, "%d %d %d %d %d\n",
                    robo->id, robo->position.x, robo->position.y, temp.x, temp.y);
            fflush(display); // Força os comandos acima executar imediatamente.
            arena.Board[robo->position.x][robo->position.y].robo = NULL;
            arena.Board[robo->position.x][robo->position.y].armyID = 0;
            robo->position.x = temp.x;
            robo->position.y = temp.y;
            if (arena.Board[robo->position.x][robo->position.y].terrain != 2 && in_swamp)
                robo->counter += 2;
            else
                robo->counter += 3;
        arena.Board[robo->position.x][robo->position.y].robo = robo;
        arena.Board[robo->position.x][robo->position.y].armyID = robo->armyID;
        }
    }
    //Ação FETCH
    else if (tmp.ac == 10) {
        if (arena.Board[temp.x][temp.y].crystall > 0) {
            arena.Board[temp.x][temp.y].crystall--;
            robo->n_crystalls++;
        }
        robo->counter += 3;
    }
    //Ação DEPO
    else if (tmp.ac == 20) {
        if (robo->n_crystalls > 0){
            arena.Board[temp.x][temp.y].crystall += robo->n_crystalls;
            robo->n_crystalls = 0;
            fprintf(display, "cristais %d %d %d\n", arena.Board[temp.x][temp.y].crystall, temp.x, temp.y);
            fflush(display);
        }
        robo->counter += 3;
    }
    //Ação ATK
    else if (tmp.ac == 30) {
        if (arena.Board[temp.x][temp.y].robo != NULL) {
            if (arena.Board[temp.x][temp.y].robo->n_crystalls > 0) {
                robo->n_crystalls += arena.Board[temp.x][temp.y].robo->n_crystalls;
                arena.Board[temp.x][temp.y].robo->n_crystalls = 0;
            }
            else{
                arena.Board[temp.x][temp.y].robo->HP -= 50;
                if (arena.Board[temp.x][temp.y].robo->HP <= 0){
                    int x = arena.Board[temp.x][temp.y].robo->id;
                    arena.Board[temp.x][temp.y].armyID = 0;
                    arena.Board[temp.x][temp.y].robo = NULL;
                    fprintf(display, "%d %d %d %d %d\n",
                            x, temp.x, temp.y, 14, 14);
                    fprintf(display, "morre %d %d\n", temp.x, temp.y);
                    fflush(display);
                }
            }
        }
        robo->counter += 3;
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
