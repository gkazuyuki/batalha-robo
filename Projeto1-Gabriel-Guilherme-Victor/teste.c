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
    for (int i = 0; i < 2000; i++ ){
        switch (p1[i].instr) {
            case 0:
                printf("PUSH  %d\n", p1[i].op );
            break;

            case 1:
                printf("POP  %d\n", p1[i].op );
            break;

            case 2:
                printf("DUP  %d\n", p1[i].op );
            break;

            case 3:
                printf("ADD  %d\n", p1[i].op );
            break;

            case 4:
                printf("SUB  %d\n", p1[i].op );
            break;

            case 5:
                printf("MUL  %d\n", p1[i].op );
            break;

            case 6:
                printf("DIV  %d\n", p1[i].op );
            break;

            case 7:
                printf("JMP  %d\n", p1[i].op );
            break;

            case 8:
                printf("JIT  %d\n", p1[i].op );
            break;

            case 9:
                printf("JIF  %d\n", p1[i].op );
            break;

            case 10:
                printf("CALL  %d\n", p1[i].op );
            break;

            case 11:
                printf("RET  %d\n", p1[i].op );
            break;

            case 12:
                printf("EQ  %d\n", p1[i].op );
            break;

            case 13:
                printf("GT  %d\n", p1[i].op );
            break;

            case 14:
                printf("GE  %d\n", p1[i].op );
            break;

            case 15:
                printf("LT  %d\n", p1[i].op );
            break;

            case 16:
                printf("LE  %d\n", p1[i].op );
            break;

            case 17:
                printf("NE  %d\n", p1[i].op );
            break;

            case 18:
                printf("STO  %d\n", p1[i].op );
            break;

            case 19:
                printf("RCL  %d\n", p1[i].op );
            break;

            case 20:
                printf("END  %d\n", p1[i].op );
            break;

            case 21:
                printf("PRN  %d\n", p1[i].op );
            break;

            case 22:
                printf("STL  %d\n", p1[i].op );
            break;

            case 23:
                printf("RCE  %d\n", p1[i].op );
            break;

            case 24:
                printf("ALC  %d\n", p1[i].op );
            break;

            case 25:
                printf("FRE  %d\n", p1[i].op );
            break;

            case 26:
                printf("ATR  %d\n", p1[i].op );
            break;

            case 27:
                printf("MOV  %d\n", p1[i].op );
            break;

            case 28:
                printf("FETCH  %d\n", p1[i].op );
            break;

            case 29:
                printf("DEPO  %d\n", p1[i].op );
            break;

            case 30:
                printf("ATK  %d\n", p1[i].op );
            break;
        }
    }
    */
    while (arena.time < 1000)
        Atualiza(display);
    RemoveExercito("Black_Templars");
    destroyArena(arena.size);
    pclose(display);
    return 0;
}
