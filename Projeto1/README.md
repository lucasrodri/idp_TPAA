# Técnicas de Programação e Análise de Algoritmos PROJETO 1

Arquivo binário com o executável do Projeto 1 

## Exemplo de uso

```console
./main
$ git commit -m lucas1
$ git commit -m lucas2
$ git log
Branch: master
jX2A9VNF lucas2
lVAj6ATj lucas1
fzxc0WG0 first commit
$ git branch teste
$ git log
Branch: master
jX2A9VNF lucas2
lVAj6ATj lucas1
fzxc0WG0 first commit
$ git checkout teste
$ git log
Branch: teste
jX2A9VNF lucas2
lVAj6ATj lucas1
fzxc0WG0 first commit
$ git commit -m lucas3
$ git log
Branch: teste
sfJ4qHLo lucas3
jX2A9VNF lucas2
lVAj6ATj lucas1
fzxc0WG0 first commit
$ git checkout master
$ git log
Branch: master
jX2A9VNF lucas2
lVAj6ATj lucas1
fzxc0WG0 first commit
$ git checkout teste
$ git log
Branch: teste
sfJ4qHLo lucas3
jX2A9VNF lucas2
lVAj6ATj lucas1
fzxc0WG0 first commit
$ git checkout lVAj6ATj
$ git log
Branch: lVAj6ATj
lVAj6ATj lucas1
fzxc0WG0 first commit
$ git checkout master
$ git log
Branch: master
jX2A9VNF lucas2
lVAj6ATj lucas1
fzxc0WG0 first commit
$ git checkout teste
$ git git log
Comando inválido!
$ git log
Branch: teste
sfJ4qHLo lucas3
jX2A9VNF lucas2
lVAj6ATj lucas1
fzxc0WG0 first commit
$ exit
Saindo...
```
