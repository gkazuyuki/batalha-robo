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

void Sistema(Maquina *robo, int opcode, pos cords)
{

}
