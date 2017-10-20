

Arena *InicializaArena(int size, int army_number)
{
    Arena *new_arena;
    new_arena->size = size;
    new_arena->army_number = army_number;
    new_arena->top = 0;
    new_arena->time = ; //FALTA O TEMPO AQUI

    board new_board = emalloc(size*sizeof(node*)); //Criando tabuleiro nxn
    for (int i = 0; i < size; i++) {
        board[i] = emalloc(n*sizeof(node));
    }

    //Inicializa terreno e cristais
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            board[i][j].crystall = rand()%3; // 0, 1 ou 2 cristais na posição
            board[i][j].terrain = rand()%3; //Três tipos de terreno: estrada, montanha, rio
            board[i][j].HQ = 0; //Sem HQ
            board[i][j].roboID = 0; //Inicializa em robos
        }
    new_arena->Board = new_board;

    new_arena->army_vector = emalloc(army_number*sizeof(army)); //IDEIA FAZER ISSO ESTATICAMENTE COM UM TOPO

    return new_arena;
}

void Atualiza()
{
    for (int i = 0; i < arena.army_number; i++){
        /*Já cuida do fato de qur se um exercito foi removido ele não sera
         *considerado por ter
        */
        for (int j = 0; j < arena.army_vector[i].num_bots; j++){
            exec_maquina(arena.army_vector[i].robo[j], 50);
        }
    }
    return;
}

void InsereExercito(char *name, int n)
{
    arena.army_vector[arena.top].num_bots = n;
    arena.HQpos = ; // FALTA INICIALIZAR
    arena.army_vector[arena.top].chapter = malloc(strlen(name)*sizeof(char));
    strcpy(arena.army_vector[arena.top].chapter, name);
    for (int i = 0; i < n; i++){
         arena.army_vector[arena.top].robo[i] = cria_maquina(); //isso tem algum argumento
    }
    arena.top++;
    return;
}

void RemoveExercito(char *name, int n)
{
    for (int i = 0; i < arena.army_number && strcmp(name, arena.army_vector[i].chapter) != 0; i++) {}
    if (i < arena.army_number) {
        for (int j = 0; j < arena.army_vector[i].num_bots; j++) {
            destroi_maquina(arena.army_vector[i].robo[j]);
        }
        free(arena.army_vector[i].robots);
        free(arena.army_vector[i].chapter);
        arena.army_vector[i].num_bots = -1;

    }
    else {
        fprintf(stderr, "ERRO: Execito não existe.\n");
    }
}

void Sistema(Maquina *robo)
{
    OPERANDO tmp = desempilha(&robo->pil), aux = desempilha(&robo->pil);
    if (tmp.ac == 0) {
        if (aux.n == 0) {
            if (arena.Board[robo->pos.x][robo->pos.y - 1].robo == NULL) {
                robo->pos.x = robo->pos.x;
                robo->pos.y = robo->pos.y - 1;
            }
        }
        else if (aux.n == 1) {
            if (arena.Board[robo->pos.x + 1][robo->pos.y - 1].robo == NULL) {
                robo->pos.x = robo->pos.x + 1;
                robo->pos.y = robo->pos.y - 1;
            }
        }
        else if (aux.n == 2) {
            if (arena.Board[robo->pos.x + 1][robo->pos.y + 1].robo == NULL) {
                robo->pos.x = robo->pos.x + 1;
                robo->pos.y = robo->pos.y + 1;
            }
        }
        else if (aux.n == 3) {
            if (arena.Board[robo->pos.x][robo->pos.y + 1].robo == NULL) {
                robo->pos.x = robo->pos.x + 1;
                robo->pos.y = robo->pos.y + 1;
            }
        }
        else if (aux.n == 4) {
            if (arena.Board[robo->pos.x - 1][robo->pos.y + 1].robo == NULL) {
                robo->pos.x = robo->pos.x - 1;
                robo->pos.y = robo->pos.y + 1;
            }
        }
        else if (aux.n == 5) {
            if (arena.Board[robo->pos.x - 1][robo->pos.y].robo == NULL) {
                robo->pos.x = robo->pos.x - 1;
                robo->pos.y = robo->pos.y;
            }
        }
        arena.Board[robo->pos.x][robo->pos.y].robo = robo;
    }
    else if (tmp.ac == 10) {
        if (aux.n == 0) {
            if (arena.Board[robo->pos.x][robo->pos.y - 1].crystall > 0) {
                arena.Board[robo->pos.x][robo->pos.y - 1].crystall--;
                &robo.n_crystalls++;
            }
        }
        else if (aux.n == 1) {
            if (arena.Board[robo->pos.x + 1][robo->pos.y - 1].crystall > 0) {
                arena.Board[robo->pos.x + 1][robo->pos.y - 1].crystall--;
                &robo.n_crystalls++;
            }
        }
        else if (aux.n == 2) {
            if (arena.Board[robo->pos.x + 1][robo->pos.y + 1].crystall > 0) {
                arena.Board[robo->pos.x + 1][robo->pos.y + 1].crystall--;
                &robo.n_crystalls++;
            }
        }
        else if (aux.n == 3) {
            if (arena.Board[robo->pos.x][robo->pos.y + 1].crystall > 0) {
                arena.Board[robo->pos.x][robo->pos.y + 1].crystall--;
                &robo.n_crystalls++;
            }
        }
        else if (aux.n == 4) {
            if (arena.Board[robo->pos.x - 1][robo->pos.y + 1].crystall > 0) {
                arena.Board[robo->pos.x - 1][robo->pos.y + 1].crystall--;
                &robo.n_crystalls++;
            }
        }
        else if (aux.n == 5) {
            if (arena.Board[robo->pos.x - 1][robo->pos.y].crystall > 0) {
                arena.Board[robo->pos.x - 1][robo->pos.y].crystall--;
                &robo.n_crystalls++;
            }
        }
    }
    else if (tmp.ac == 20) {
        if (aux.n == 0) {
            arena.Board[robo->pos.x][robo->pos.y - 1].crystall++;
        }
        else if (aux.n == 1) {
            arena.Board[robo->pos.x + 1][robo->pos.y - 1].crystall++;
        }
        else if (aux.n == 2) {
            arena.Board[robo->pos.x + 1][robo->pos.y + 1].crystall++;
        }
        else if (aux.n == 3) {
            arena.Board[robo->pos.x][robo->pos.y + 1].crystall++;
        }
        else if (aux.n == 4) {
            arena.Board[robo->pos.x - 1][robo->pos.y + 1].crystall++;
        }
        else if (aux.n == 5) {
            arena.Board[robo->pos.x - 1][robo->pos.y].crystall++;
        }
        &robo.n_crystalls--;
    }
    else if (tmp.ac == 30) {
        if (aux.n == 0) {
            if (arena.Board[robo->pos.x][robo->pos.y - 1].robo != NULL) {
                if (arena.Board[robo->pos.x][robo->pos.y - 1].robo->n_crystalls > 0) {
                    robo->n_crystalls += arena.Board[robo->pos.x][robo->pos.y - 1].robo->n_crystalls;
                    arena.Board[robo->pos.x][robo->pos.y - 1].robo->n_crystalls = 0;
                }
                else {

                }
            }
        }
        else if (aux.n == 1) {
            if (arena.Board[robo->pos.x + 1][robo->pos.y - 1].robo != NULL) {

            }
        }
        else if (aux.n == 2) {
            if (arena.Board[robo->pos.x + 1][robo->pos.y + 1].robo != NULL) {

            }
        }
        else if (aux.n == 3) {
            if (arena.Board[robo->pos.x][robo->pos.y + 1].robo != NULL) {

            }
        }
        else if (aux.n == 4) {
            if (arena.Board[robo->pos.x - 1][robo->pos.y + 1].robo != NULL) {

            }
        }
        else if (aux.n == 5) {
            if (arena.Board[robo->pos.x + 1][robo->pos.y].robo != NULL) {

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
