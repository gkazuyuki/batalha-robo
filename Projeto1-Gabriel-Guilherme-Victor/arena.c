void Atualiza()
{
    for (int i = 0; i < arena.army_number; i++){
        /*Já cuida do fato de qur se um exercito foi removido ele não sera
         *considerado por ter
        */
        for (int j = 0; j < arena.army_vector[i].numb_robots; j++){
            exec_maquina(arena.army_vector[i].robo[j], 50);
        }
    }
    return;
}

void InsereExercito(char *name, int n)
{
    arena.army_vector[army_number].numb_robots = n;
    arena.army_vector[army_number].chapter = malloc(strlen(name)*sizeof(char));
    strcpy(arena.army_vector[army_number].chapter, name);
    for (int i = 0; i < n; i++){
         arena.army_vector[army_number].robo[i] = cria_maquina(); //isso tem algum argumento
    }
    arena.army_number++;
    return;
}

void RemoveExercito(char *name, int n)
{
    for (int i = 0; i < arena.army_number && strcmp(name, arena.army_vector[i].chapter) != 0; i++) {}
    if (i < arena.army_number) {
        for (int j = 0; j < arena.army_vector[i].numb_robots; j++) {
            destroi_maquina(arena.army_vector[i].robo[j]);
        }
        free(arena.army_vector[i].robots);
        free(arena.army_vector[i].chapter);
        arena.army_vector[i].numb_robots = -1;

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
            if (arena.Board[][].robo == NULL) {
                &robo.pos.x = ;
                &robo.pos.y = ;
            }
        }
        else if (aux.n == 1) {
            if (arena.Board[][].robo == NULL) {
                &robo.pos.x = ;
                &robo.pos.y = ;
            }
        }
        else if (aux.n == 2) {
            if (arena.Board[][].robo == NULL) {
                &robo.pos.x = ;
                &robo.pos.y = ;
            }
        }
        else if (aux.n == 3) {
            if (arena.Board[][].robo == NULL) {
                &robo.pos.x = ;
                &robo.pos.y = ;
            }
        }
        else if (aux.n == 4) {
            if (arena.Board[][].robo == NULL) {
                &robo.pos.x = ;
                &robo.pos.y = ;
            }
        }
        else if (aux.n == 5) {
            if (arena.Board[][].robo == NULL) {
                &robo.pos.x = ;
                &robo.pos.y = ;
            }
        }
    }
    else if (tmp.ac == 10) {
        if (aux.n == 0) {
            if (arena.Board[][].crystall > 0) {
                arena.Board[][].crystall--;
                &robo.n_crystalls++;
            }
        }
        else if (aux.n == 1) {
            if (arena.Board[][].crystall > 0) {
                arena.Board[][].crystall--;
                &robo.n_crystalls++;
            }
        }
        else if (aux.n == 2) {
            if (arena.Board[][].crystall > 0) {
                arena.Board[][].crystall--;
                &robo.n_crystalls++;
            }
        }
        else if (aux.n == 3) {
            if (arena.Board[][].crystall > 0) {
                arena.Board[][].crystall--;
                &robo.n_crystalls++;
            }
        }
        else if (aux.n == 4) {
            if (arena.Board[][].crystall > 0) {
                arena.Board[][].crystall--;
                &robo.n_crystalls++;
            }
        }
        else if (aux.n == 5) {
            if (arena.Board[][].crystall > 0) {
                arena.Board[][].crystall--;
                &robo.n_crystalls++;
            }
        }
    }
    else if (tmp.ac == 20) {
        if (aux.n == 0) {

        }
        else if (aux.n == 1) {

        }
        else if (aux.n == 2) {

        }
        else if (aux.n == 3) {

        }
        else if (aux.n == 4) {

        }
        else if (aux.n == 5) {

        }
    }
    else if (tmp.ac == 30) {
        if (aux.n == 0) {

        }
        else if (aux.n == 1) {

        }
        else if (aux.n == 2) {

        }
        else if (aux.n == 3) {

        }
        else if (aux.n == 4) {

        }
        else if (aux.n == 5) {

        }
    }
    return;
}
