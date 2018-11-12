// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756

static int Pilha[20];
static int top = 0;

int salva_end(int ip) {
  if (top < 19) {
	Pilha[++top] = ip;
	return 1;
  }
  return 0;
}

int pega_end() {
  if (top >0)
	return Pilha[top--];
  return -1;
}

int pega_atu() {
  return top;
}
