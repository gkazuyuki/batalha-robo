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

static void Erro(char *msg) {
  fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

Maquina *cria_maquina(INSTR *p) {
    Maquina *m = (Maquina*)malloc(sizeof(Maquina));
    if (!m) Fatal("Memória insuficiente",4);
    m->ip = 0;
    m->prog = p;
    m->n_crystalls = 0;
  return m;
}

void destroi_maquina(Maquina *m) {
  free(m);
}

/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)
#define base (m->base)
#define bases (&m->bases)

void exec_maquina(Maquina *m, int n) {
  int i;
  OPERANDO x, y;

  for (i = 0; i < n; i++) {
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
		x = desempilha(pil), y = desempilha(pil); //estamos supondo que esta tudo ok e que o cara sabe programar!!
		tmp.n = x.n + y.n;
		tmp.t = NUM;
        empilha(pil, tmp);
        break;
	case SUB: ;
	   x = desempilha(pil), y = desempilha(pil); //estamos supondo que esta tudo ok e que o cara sabe programar!!
       tmp.n = y.n - x.n;
       tmp.t = NUM;
	   empilha(pil, tmp);
	   break;
	case MUL: ;
        x = desempilha(pil), y = desempilha(pil); //estamos supondo que esta tudo ok e que o cara sabe programar!!
		tmp.n = x.n * y.n;
		tmp.t = NUM;
        empilha(pil, tmp);
        break;
	case DIV: ;
        x = desempilha(pil), y = desempilha(pil); //estamos supondo que esta tudo ok e que o cara sabe programar!!
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
        base.n = exec->topo;
        empilha(bases, base);
	    ip = arg.n;
	    continue;
	case RET: ;
        desempilha(bases);
        if (bases->topo != 0)
            base.n = bases->val[bases->topo - 1].n;
      ip = desempilha(exec).n;
	  break;
	case EQ: ;
	  x = desempilha(pil), y = desempilha(pil);
	  tmp.t = NUM;
	  tmp.n = 0;
	  if (x.t == y.t) {
	  	if (x.t == NUM) {
	  		if (x.n == y.n)
	  			tmp.n = 1;
	    }
	    else if (x.t == ACAO) {
	  	  if (x.ac == y.ac)
	  	  	tmp.n = 1;
	  	}
		  else if (x.t == VAR) {
		  	if (x.v == y.v)
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
                if (x.n >= y.n)
                    tmp.n = 1;
            }
	        else if (x.t == ACAO) {
                if (x.ac >= y.ac)
                    tmp.n = 1;
            }
            else if (x.t == VAR) {
                if (x.v >= y.v)
                    tmp.n = 1;
            }
        }
		empilha(pil, tmp);
	  break;
	case GE: ;
	  x = desempilha(pil), y = desempilha(pil);
	  tmp.t = NUM;
	  tmp.n = 0;
	  if (x.t == y.t) {
	  	if (x.t == NUM) {
	  		if (x.n >= y.n)
	  			tmp.n = 1;
	    }
	    else if (x.t == ACAO) {
	  	  if (x.ac >= y.ac)
	  	  	tmp.n = 1;
	  	}
		  else if (x.t == VAR) {
		  	if (x.v >= y.v)
		  		tmp.n = 1;
		  }
		}
		empilha(pil, tmp);
	  break;
	case LT: ;
	  x = desempilha(pil), y = desempilha(pil);
	  tmp.t = NUM;
	  tmp.n = 0;
	  if (x.t == y.t) {
	  	if (x.t == NUM) {
	  		if (x.n < y.n)
	  			tmp.n = 1;
	    }
	    else if (x.t == ACAO) {
	  	  if (x.ac < y.ac)
	  	  	tmp.n = 1;
	  	}
		  else if (x.t == VAR) {
		  	if (x.v < y.v)
		  		tmp.n = 1;
		  }
		}
		empilha(pil, tmp);
	  break;
	case LE: ;
        x = desempilha(pil), y = desempilha(pil);
        tmp.t = NUM;
        tmp.n = 0;
        if (x.t == y.t) {
            if (x.t == NUM) {
                if (x.n <= y.n)
                    tmp.n = 1;
            }
            else if (x.t == ACAO) {
                if (x.ac <= y.ac)
                    tmp.n = 1;
            }
            else if (x.t == VAR) {
                if (x.v <= y.v)
                tmp.n = 1;
            }
        }
        empilha(pil, tmp);
        break;
	case NE: ;
        x = desempilha(pil), y = desempilha(pil);
        tmp.t = NUM;
        tmp.n = 0;
        if (x.t == y.t) {
            if (x.t == NUM) {
                if (x.n != y.n)
                    tmp.n = 1;
	        }
        }
        else if (x.t == ACAO) {
            if (x.ac != y.ac)
                tmp.n = 1;
        }
        else if (x.t == VAR) {
		  	if (x.v != y.v)
		  		tmp.n = 1;
		}
        empilha(pil, tmp);
        break;
	case STO: ;
        m->Mem[arg.n] = desempilha(pil);
        break;
	case RCL: ;
        empilha(pil,m->Mem[arg.n]); // Mudar isso (empilhar várias fita)
        break;
	case END: ;
        return;
	case PRN: ;
        x = desempilha(pil);
        if (x.t == NUM) printf("%d\n", x.n);
        else if (x.t == ACAO) printf ("%d\n", x.ac);
        else if (x.t == VAR) printf ("%d\n", x.v);
        break;
    case STL: ;
        exec->val[base.n + arg.n] = desempilha(pil);
        break;
    case RCE: ;
        empilha(pil, exec->val[base.n + arg.n]);
        break;
    case ALC: ;
        exec->topo += arg.n;
        break;
    case FRE: ;
        exec->topo -= arg.n;
        break;
    case ATR: ;
    	x = desempilha(pil);
        pos z;
        z = numbToPos(x.n, m->position);
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
        tmp.t = NUM;
        tmp.ac = arg.n;
        empilha(pil, tmp);
    	tmp.t = ACAO;
        tmp.ac = 0;
        empilha(pil, tmp);
        Sistema(m);
        break;
    case FETCH: ;
        tmp.t = NUM;
        tmp.ac = arg.n;
        empilha(pil, tmp);
    	tmp.t = ACAO;
        tmp.ac = 10;
        empilha(pil, tmp);
        Sistema(m);
        break;
    case DEPO: ;
        tmp.t = NUM;
        tmp.ac = arg.n;
        empilha(pil, tmp);
        tmp.t = ACAO;
        tmp.ac = 20;
        empilha(pil, tmp);
        Sistema(m);
        break;
    case ATK: ;
        tmp.t = NUM;
        tmp.ac = arg.n;
        empilha(pil, tmp);
    	tmp.t = ACAO;
        tmp.ac = 30;
        empilha(pil, tmp);
        Sistema(m);
        break;
    }
	D(imprime(pil,5));
	D(puts("\n"));

	ip++;
  }
}
