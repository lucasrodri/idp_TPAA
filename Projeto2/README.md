# Técnicas de Programação e Análise de Algoritmos PROJETO 2

Arquivos binários com os códigos executáveis do Projeto 2 (```server``` e ```main```)

## Exemplo de uso

```console
./main
$ git init
$ git commit -m lucas1
$ git commit -m lucas2
$ git log
Branch: master
Branch: master
6uhhRGEE lucas2
Hut9IP4v lucas1
itG1yZvn first commit
$ git branch teste (já tá fazendo o checkout)
$ git log
Branch: teste
6uhhRGEE lucas2
Hut9IP4v lucas1
itG1yZvn first commit
$ git commit -m lucas3
$ git log
Branch: teste
4aP7iINU lucas3
6uhhRGEE lucas2
Hut9IP4v lucas1
itG1yZvn first commit
$ git checkout master
$ git log
Branch: master
6uhhRGEE lucas2
Hut9IP4v lucas1
itG1yZvn first commit
$ git checkout Hut9IP4v
$ git log
Branch: Hut9IP4v
Hut9IP4v lucas1
itG1yZvn first commit
$ git checkout master
$ git log
Branch: master
6uhhRGEE lucas2
Hut9IP4v lucas1
itG1yZvn first commit
```

## Em outro console:

```console
./server
Iniciando o servidor...
Criando estruturas de dados...
Abrindo socket do servidor...
Iniciando o Servidor
Soquete do servidor criado com fd: 3
Ouvindo na porta 4242
```

## Volta para o console anterior:

```console
$ git push
PUSH_BRANCH_OK
$ exit
Saindo...
```

## Console do servidor:
```console
...
Cliente conectado.
Aguardando mensagem do cliente ...
Recebendo push do cliente...
Push realizado com sucesso!

Branch: master
6uhhRGEE lucas2
Hut9IP4v lucas1
itG1yZvn first commit
Conexão fechada

Soquete do servidor criado com fd: 3
Ouvindo na porta 4242
```

## Abre um terceiro console:

```console
./main  
$ git pull
Branch: master
6uhhRGEE lucas2
Hut9IP4v lucas1
itG1yZvn first commit
PULL_BRANCH_OK
$ git log
Branch: master
6uhhRGEE lucas2
Hut9IP4v lucas1
itG1yZvn first commit
$ exit
Saindo...
```

Funciona com novo branchs também ;)