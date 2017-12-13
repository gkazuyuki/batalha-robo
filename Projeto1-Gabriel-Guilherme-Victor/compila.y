/* Compilador */

%{
#include <stdio.h>
#include <math.h>
#include "symrec.h"
#include "acertos.h"
#include "instr.h"

int yylex();
void yyerror(char const *);
int compila(FILE *, INSTR *);
static int ip  = 0;					/* ponteiro de instruções */
static int mem = 6;					/* ponteiro da memória */
static INSTR *prog;
static int parmcnt = 0;		/* contador de parâmetros */

void AddInstr(OpCode op, int val) {
    prog[ip++] = (INSTR) {op, val};
}
%}

/*  Declaracoes */
%union {
  double val;
  /* symrec *cod; */
  char cod[30];
}

/* %type  Expr */

%token <val>  NUMt
%token <cod> ID
%token ADDt SUBt MULt DIVt ASGN OPEN CLOSE RETt EOL
%token EQt NEt LTt LEt GTt GEt ABRE FECHA SEP
%token IF ELSE WHILE FUNC PRINT
%token ATKt ATRt MOVt FETCHt DEPOt


// Maior precedência para else
//%nonassoc THEN
//%nonassoc ELSEX

%right ASGN
%left ADDt SUBt
%left MULt DIVt
%left NEG
%right PWR
%left LTt GTt LEt GEt EQt NEt


/* Gramatica */
%%

Programa: Comando
       | Programa Comando
	   ;

Comando: Expr EOL
        | Cond
        | Loop
        | Func
        | PRINT Expr EOL { AddInstr(PRN, 0); }
        | RETt EOL {
            AddInstr(FRE, 0);
            AddInstr(RET, 0);
        }
        | RETt OPEN  Expr CLOSE EOL {
            AddInstr(FRE, 0);
            AddInstr(RET,0);
        }
        /***/
        | MOVt OPEN Expr CLOSE EOL { AddInstr(MOV, 0); }
        | FETCHt OPEN Expr CLOSE EOL { AddInstr(FETCH, 0); }
        | DEPOt OPEN Expr CLOSE EOL { AddInstr(DEPO, 0); }
        | ATKt OPEN Expr CLOSE EOL { AddInstr(ATK, 0); }
        /**/
        /* | EOL {printf("--> %d\n", ip);} */
;

Expr: NUMt {  AddInstr(PUSH, $1);}
    | ID   {
	         symrec *s = getsym($1);
			 if (s == 0)
                s = putsym($1);
			    AddInstr(RCL, s->val);
            }
	| ID ASGN  Expr {
                    symrec *s = getsym($1);
			        if ( s == 0)
                        s = putsym($1);
			        AddInstr(STO, s->val);
                }

    | ATRt OPEN Expr SEP Expr CLOSE { AddInstr(ATR, 0);}

    | Chamada
    | Expr ADDt Expr { AddInstr(ADD,  0); }
	| Expr SUBt Expr { AddInstr(SUB,  0); }
	| Expr MULt Expr { AddInstr(MUL,  0); }
	| Expr DIVt Expr { AddInstr(DIV,  0); }
    /*ver que CHS é esse*/
    | '-' Expr %prec NEG  { printf("  {CHS,  0},\n"); }
	| OPEN Expr CLOSE
	| Expr LTt Expr  { AddInstr(LT, 0);}
	| Expr GTt Expr  { AddInstr(GT, 0);}
	| Expr LEt Expr  { AddInstr(LE, 0);}
	| Expr GEt Expr  { AddInstr(GE, 0);}
	| Expr EQt Expr  { AddInstr(EQ, 0);}
	| Expr NEt Expr  { AddInstr(NE, 0);}
;

Ifheader: IF OPEN Expr {
                    salva_end(ip);
                    AddInstr(JIF,  0);
 		        }
		        CLOSE

Cond: Ifheader Bloco {
                    prog[pega_end()].op = ip;
                }

    | Ifheader Bloco {
                    prog[pega_end()].op = ip + 1;
                    salva_end(ip);
                    AddInstr(JMP, 0);
                }
     ELSE Bloco {
         prog[pega_end()].op = ip;
     };


Loop: WHILE OPEN {
                salva_end(ip);
            }
	  		Expr {
                salva_end(ip);
                AddInstr(JIF, 0);
            }
            CLOSE Bloco {
                int ip2 = pega_end();
                AddInstr(JMP, pega_end());
                prog[ip2].op = ip;
			};

Bloco: ABRE Comandos FECHA ;

Comandos: Comando
    | Comandos Comando
	;

Func: FUNC ID {
        salva_end(ip);
        AddInstr(JMP, 0);
		symrec *s = getsym($2);
		if (s == 0)
            s = putsym($2);
		else {
            yyerror("Função definida duas vezes\n");
            YYABORT;
		}
        s->val = ip;
     }
     OPEN {
         newtab(0);
     }
     Args CLOSE  Bloco{
        /* AddInstr(FRE, 0);
         AddInstr(RET, 0);*/
         prog[pega_end()].op = ip;
         deltab();
     }
	  ;

Args:
	| ID {
        putsym($1);
	  }
    | Args SEP ID {
	  	 putsym($3);
	  }
	;

Chamada:ID OPEN {
        parmcnt = 0;
        /* posição da memória mais avançada */
		}
        ListParms{
            symrec *s = getsym($1);
            if (s == 0) {
                yyerror("Função não definida\n");
                YYABORT;
            }
            AddInstr(ALC, lastval());
            /* Cópia dos parâmetros */
            while (parmcnt > 0)
                AddInstr( STO, --parmcnt);
            AddInstr(CALL, s->val);
        }
        CLOSE ;


ListParms:
	| Expr { parmcnt++;}
	| Expr { parmcnt++;} SEP ListParms
;

%%
extern FILE *yyin;

void yyerror(char const *msg) {
    fprintf(stderr, "ERRO: %s", msg);
}

int compilador(FILE *cod, INSTR *dest) {
    int r;
    yyin = cod;
    prog = dest;
    cleartab();
    ip = 0;
    r = yyparse();
    AddInstr(END, 0);
    return r;
}
