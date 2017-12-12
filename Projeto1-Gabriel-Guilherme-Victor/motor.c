#include <stdio.h>
#include "compila.tab.h"
#include "maq.h"

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

  for (int i = 0; i < 2000; i++) {
      printf("%d %d\n", p1[i].instr, p1[i].op);
  }
  Maquina *maq = cria_maquina(p1);
  exec_maquina(maq, 1000);
  destroi_maquina(maq);
  return 0;
}
