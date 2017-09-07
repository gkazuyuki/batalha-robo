### Batalha de robôs

Projeto para a disciplina MAC0216 (2017/2)

### Primeira fase

**Entrega em 17/09**

Progresso (<p id="pt"></p>):

* Implementar uso de variáveis locais para funções (<p id="p0"></p>)
* Implementar instruções STL e RCL (<p id="p1"></p>)
* Adaptar instrução RET (<p id="p2"></p>)
* Finalizar montador (<p id="p3"></p>)

### Links úteis

* ["Especificação" do EP](http://paca.ime.usp.br/pluginfile.php/133698/mod_assign/introattachment/0/Batalha.pdf)
* [Fórum de dúvidas](http://paca.ime.usp.br/mod/forum/view.php?id=37031)

* [Referência rápida: C](http://www.cprogramming.com/reference/)
* [Referência rápida: Python3](https://learnxinyminutes.com/docs/python3/)

<script>
var pt = 0;
var p = [0, 0, 0, 20];
var w = [35, 30, 15, 20];
for (var i = 0; i < p.length; i++) {
    document.getElementById("p"+i).innerHTML = p[i];
    pt += (p[i] * w[i])/100;
}
document.getElementById("pt").innerHTML = Math.floor(pt);
</script>
