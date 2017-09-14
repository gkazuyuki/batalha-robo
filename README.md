### Batalha de robôs

Projeto para a disciplina MAC0216 (2017/2)

### Primeira fase

**Entrega em 17/09**

Progresso:

* Implementar uso de variáveis locais para funções ( )
* Implementar instruções STL e RCL ( )
* Adaptar instrução RET ( )
* Finalizar montador ( )
* Elaborar testes ( )

### Links úteis

* [Descrição do EP](http://paca.ime.usp.br/pluginfile.php/133698/mod_assign/introattachment/0/Batalha.pdf)
* [Fórum de dúvidas](http://paca.ime.usp.br/mod/forum/view.php?id=37031)
* [Fórum de avisos](http://paca.ime.usp.br/mod/forum/view.php?id=36956)

* [Referência rápida: C](http://www.cprogramming.com/reference/)
* [Referência rápida: Python3](https://learnxinyminutes.com/docs/python3/)

### Notas

Da descrição: "Uso de variáveis locais para funções. Estas variáveis ficarão na
pilha de execução, de forma parecida com o que ocorre no assembler". Se isso se
trata de funções em linguagem robô há um problema: sem um linker não dá pra
desviar pra intruções abaixo da instrução de desvio. Modifiquei o montador pra
fazer isso mesmo que não seja seu objetivo.
Coloquei uma váriavel rbp na struct da máquina. Assim como se faria em
assembly, a pilha perde sua abstração.
Também da descrição: "A instrução RET deve acertar o valor do registrador de
base antes de desempilhar o endereço de retorno". Não sei o que isso quer dizer.
