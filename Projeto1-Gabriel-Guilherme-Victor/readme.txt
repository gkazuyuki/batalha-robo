// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756

Como utilizar o montador:
    montador < entrada > saida
      -Entrada: Arquivo de baixo nível que será interpretado pela máquina.
      -Saída: Arquivo .c que onde o programa interpretado será gravado. O programa recebe como
      			argumento quantas instruções serão executadas.

Comentários sobre a implementação:
	*bases: Essa pilha foi adicionada para guardar a posição das bases de memória local da pilha exec.
    *base: Argumento que contém a base atual da pilha exec.
    *STL: Essa função adiciona um argumento na pilha exec. É importante notar que a base da pilha está
      acima do endereço de retorno, ou seja, igual ao topo da pilha após empilhar o IP.
        Exemplo: Para guardar uma variável na primeira posição da memória local, o comando é:
                	STL 0;
	*RCE: Remove da posição base + arg o elemento da pilha exec.
	*ALC: Soma arg ao topo da pilha (pilha += arg).
    *FRE: Retira arg do topo da pilha (pha -= arg). Para execução correta do Programa é nescessário que
      		o programador de FRE em todos os elementos alocados pela função antes de encerrá-la.
    *CALL: Agora a CALL também empilha a nova base da pilha exec.
    *RET: Agora a RET também pega a base da pilha exec da função anterior.
