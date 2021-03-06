/* Guilherme Costa Vieira               Nº USP: 9790930
   Gabriel Kazuyuki Isomura             Nº USP: 9793673
   Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756 */

D [0-9]
L [a-zA-Z_]
H [a-zA-Z_0-9]
E [Ee][+-]?{D}+

%{
#include <math.h>
#include "compila.tab.h"
%}


%%
{D}*[.]?{D}+{E}?	{ yylval.val = atof(yytext); return NUMt; }

ret(urn)?  { return RETt; }

if      { return IF; }
else    { return ELSE; }
while	{ return WHILE; }
func|def { return FUNC; }
print   { return PRINT; }

atr { return ATRt; }
atk { return ATKt; }
mov { return MOVt; }
depo { return DEPOt; }
fetch { return FETCHt; }

{L}{H}* {
    strncpy(yylval.cod, yytext, 30);
    return ID;
}

[ \t\n]+	/* pula espacos em branco */

#.*		/* comentarios simples */

;		{ return EOL; }
,		{ return SEP; }
=		{ return ASGN; }
[(]		{ return OPEN; }
[)]		{ return CLOSE; }
[{]		{ return ABRE; }
[}]		{ return FECHA; }
[+]		{ return ADDt; }
[-]		{ return SUBt; }
[*]		{ return MULt; }
[/]		{ return DIVt; }
==		{ return EQt; }
!=		{ return NEt; }
"<"		{ return LTt; }
"<="	{ return LEt; }
">"		{ return GTt; }
">="	{ return GEt; }

.	{  fprintf(stderr, "ERRO: Caractere não suportado.\n-->%s\n", yytext);
       exit(1);
    }

%%

/* Local Variables: */
/* mode: c */
/* End: */
