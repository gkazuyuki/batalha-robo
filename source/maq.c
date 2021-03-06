// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756

#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include "maq.h"

/* #define DEBUG */

#ifdef DEBUG
#  define D(X) X
char *CODES[] = {
    "PUSH",
    "POP",
    "DUP",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "JMP",
    "JIT",
    "JIF",
    "CALL",
    "RET",
    "EQ",
    "GT",
    "GE",
    "LT",
    "LE",
    "NE",
    "STO",
    "RCL",
    "END",
    "PRN",
    "STL",
    "RCE",
    "ALC",
    "FRE",
    "ATR",
    "MOV",
    "FETCH",
    "DEPO",
    "ATK"
};
#else
#  define D(X)
#endif

static void Erro(char *msg)
{
    fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod)
{
    Erro(msg);
    exit(cod);
}

Maquina *cria_maquina(INSTR *p)
{
    Maquina *m = (Maquina*)malloc(sizeof(Maquina));
    if (!m) Fatal("Memória insuficiente",4);
    m->ip = 0;
    m->prog = p;
    m->n_crystalls = 0;
    m->HP = 100;
    m->counter = 0;
    m->ib = 0;
    return m;
}

void destroi_maquina(Maquina *m)
{
    free(m);
}

int new_frame(Maquina *m, int n) {
  int ibc = m->ib;
  if (ibc < MAXFRM - 1) {
	m->bp[++m->ib] = n + ibc;
	return m->ib;
  }
  return -1;
}

int del_frame(Maquina *m) {
  if (m->ib > 0) return --m->ib;
  return -1;
}


/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)

void exec_maquina(Maquina *m, int n, FILE *display)
{
    int i;
    OPERANDO x, y;

    for (i = 0; i < n; i++) {
        if (m->counter%6 != 0) {
            m->counter += 1;
            continue;
        }
        else
            m->counter = 0;
        OpCode   opc = prg[ip].instr;
        OPERANDO arg;
        if (opc == ATR || opc == MOV ||opc == FETCH || opc == DEPO || opc == ATK){
            arg.t = ACAO;
            arg.ac = prg[ip].op;
        }
        else {
            arg.t = NUM;
            arg.n = prg[ip].op;
        }
        D(printf("%3d: %-4.4s %d\n     ", ip, CODES[opc], arg));
        switch (opc) {
            OPERANDO tmp;
        case PUSH: ;
            empilha(pil, arg);
            break;
        case POP: ;
            desempilha(pil);
            break;
        case DUP: ;
            tmp = desempilha(pil);
            empilha(pil, tmp);
            empilha(pil, tmp);
            break;
        case ADD: ;
            x = desempilha(pil), y = desempilha(pil);
            tmp.n = x.n + y.n;
            tmp.t = NUM;
            empilha(pil, tmp);
            break;
        case SUB: ;
            x = desempilha(pil), y = desempilha(pil);
            tmp.n = y.n - x.n;
            tmp.t = NUM;
            empilha(pil, tmp);
            break;
        case MUL: ;
            x = desempilha(pil), y = desempilha(pil);
            tmp.n = x.n * y.n;
            tmp.t = NUM;
            empilha(pil, tmp);
            break;
        case DIV: ;
            x = desempilha(pil), y = desempilha(pil);
            tmp.n = y.n / x.n;
            tmp.t = NUM;
            empilha(pil, tmp);
            break;
        case JMP: ;
            ip = arg.n;
            continue;
        case JIT:
            if (desempilha(pil).n != 0) {
                ip = arg.n;
                continue;
            }
            break;
        case JIF:
            if (desempilha(pil).n == 0) {
                ip = arg.n;
                continue;
            }
            break;
        case CALL: ;
            OPERANDO ip2;
            ip2.t = NUM;
            ip2.n = ip;
            empilha(exec, ip2);
            ip = arg.n;
            continue;
        case RET: ;
            ip = desempilha(exec).n;
            break;
        case EQ: ;
            x = desempilha(pil), y = desempilha(pil);
            tmp.t = NUM;
            tmp.n = 0;
            if (y.t == x.t) {
                if (x.t == NUM) {
                    if (y.n == x.n)
                        tmp.n = 1;
                }
                else if (x.t == ACAO) {
                    if (y.ac == x.ac)
                        tmp.n = 1;
                }
            }
            empilha(pil, tmp);
            break;
        case GT: ;
            x = desempilha(pil), y = desempilha(pil);
            tmp.t = NUM;
            tmp.n = 0;
            if (x.t == y.t) {
                if (x.t == NUM) {
                    if (y.n > x.n)
                        tmp.n = 1;
                }
                else if (x.t == ACAO) {
                    if (y.ac > x.ac)
                        tmp.n = 1;
                }
            }
            empilha(pil, tmp);
            break;
        case GE: ;
            x = desempilha(pil), y = desempilha(pil);
            tmp.t = NUM;
            tmp.n = 0;
            if (y.t == x.t) {
                if (x.t == NUM) {
                    if (y.n >= x.n)
                        tmp.n = 1;
                    }
                else if (x.t == ACAO) {
                    if (y.ac >= x.ac)
                        tmp.n = 1;
                }
            }
            empilha(pil, tmp);
            break;
        case LT: ;
            x = desempilha(pil), y = desempilha(pil);
            tmp.t = NUM;
            tmp.n = 0;
            if (y.t == x.t) {
                if (x.t == NUM) {
                    if (y.n < x.n)
                        tmp.n = 1;
                }
                else if (x.t == ACAO) {
                    if (y.ac < x.ac)
	  	  	             tmp.n = 1;
                }
            }
            empilha(pil, tmp);
            break;
        case LE: ;
            x = desempilha(pil), y = desempilha(pil);
            tmp.t = NUM;
            tmp.n = 0;
            if (y.t == x.t) {
                if (x.t == NUM) {
                    if (y.n <= x.n)
                        tmp.n = 1;
                }
                else if (x.t == ACAO) {
                    if (y.ac <= x.ac)
                        tmp.n = 1;
                }
            }
            empilha(pil, tmp);
            break;
        case NE: ;
            x = desempilha(pil), y = desempilha(pil);
            tmp.t = NUM;
            tmp.n = 0;
            if (y.t == x.t) {
                if (x.t == NUM) {
                    if (y.n != x.n)
                        tmp.n = 1;
                }
            }
            else if (x.t == ACAO) {
                if (y.ac != x.ac)
                tmp.n = 1;
            }
            empilha(pil, tmp);
            break;
        case STO: ;
            m->Mem[arg.n + m->bp[m->ib]] = desempilha(pil);
            break;
        case RCL: ;
            empilha(pil, m->Mem[arg.n + m->bp[m->ib]]);
            break;
        case END: ;
            return;
        case PRN: ;
            x = desempilha(pil);
            if (x.t == NUM) printf("%d\n", x.n);
            else if (x.t == ACAO) printf ("%d\n", x.ac);
            break;
        case ALC: ;
          new_frame(m, arg.n);
          break;
        case FRE: ;
          del_frame(m);
          break;
        case ATR: ;
            arg = desempilha(pil);
            x = desempilha(pil);
            pos z;
            z = numToPos(x.n, m->position, arena.size);
            y.t = NUM;
            if (arg.n == 0) {
                y.n = arena.Board[z.x][z.y].terrain;
            }
            else if (arg.n == 1) {
                y.n = arena.Board[z.x][z.y].crystall;
            }
            else if (arg.n == 2) {
                y.n = arena.Board[z.x][z.y].armyID;
            }
            else {
                y.n = arena.Board[z.x][z.y].HQ;
            }
            empilha(pil, y);
            break;
        case MOV: ;
            arg = desempilha(pil);
            tmp.t = NUM;
            tmp.ac = arg.n;
            empilha(pil, tmp);
            tmp.t = ACAO;
            tmp.ac = 0;
            empilha(pil, tmp);
            Sistema(m, display);
            break;
        case FETCH: ;
            arg = desempilha(pil);
            tmp.t = NUM;
            tmp.ac = arg.n;
            empilha(pil, tmp);
            tmp.t = ACAO;
            tmp.ac = 10;
            empilha(pil, tmp);
            Sistema(m, display);
            break;
        case DEPO: ;
            arg = desempilha(pil);
            tmp.t = NUM;
            tmp.ac = arg.n;
            empilha(pil, tmp);
            tmp.t = ACAO;
            tmp.ac = 20;
            empilha(pil, tmp);
            Sistema(m, display);
            break;
        case ATK: ;
            arg = desempilha(pil);
            tmp.t = NUM;
            tmp.ac = arg.n;
            empilha(pil, tmp);
            tmp.t = ACAO;
            tmp.ac = 30;
            empilha(pil, tmp);
            Sistema(m, display);
            break;
        }
        D(imprime(pil, 5));
        D(puts("\n"));
        ip++;
    }
}
