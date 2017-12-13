// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756

#include <stdio.h>
#include <stdlib.h>
#include "compila.tab.h"
#include "maq.h"
#include "arena.h"

INSTR p1[2000];

int compilador(FILE *, INSTR *);

int main(int ac, char **av) {
    FILE *p = stdin;

    int res;
    ac --; av++;
    if (ac > 0)
  	    p = fopen(*av,"r");
    res = compilador(p, p1);
    if (res) return 1;
    
    FILE *display = popen("./apres", "w");
    Arena *nova_arena;
    nova_arena = InicializaArena(15, 1, display);
    arena = *nova_arena;


    INSTR *army_prog1[] = {p1};
    pos hq_pos1 = {3, 3};
    pos army_pos1[] = {{7, 7}};

    InsereExercito("Black_Templars", 1, hq_pos1, army_pos1, army_prog1, 1, display);
    /*
    for (int i; i < 2000; i++ ){
        switch (p1[i].instr)
            case 0:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 1:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 2:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 3:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 4:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 5:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 6:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 7:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 8:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 9:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 10:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 11:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 12:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 13:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 14:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 15:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 16:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 17:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 18:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 19:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 20:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 21:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 22:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 23:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 24:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 25:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 26:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 27:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 28:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 29:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;

            case 30:
                printf("%d  %d\n", p1[i].instr , p1[i].op );
            break;
    }
    */
    while (arena.time < 1000)
        Atualiza(display);
    RemoveExercito("Black_Templars");
    destroyArena(arena.size);
    pclose(display);
    return 0;
}
