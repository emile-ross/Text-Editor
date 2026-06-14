Este projeto implementa um editor de texto em linha de comando, escrito em C, que manipula arquivos através de uma lista duplamente encadeada. O programa funciona como um 
pequeno interpretador: o usuário digita comandos no prompt (mtext>) e o editor executa operações como abrir arquivos (open/openbin), salvar (save/savebin), inserir (i), 
remover (d), substituir (r), concatenar (a), dividir (split), unir (join), imprimir (print) e encerrar (quit). Caso o usuário não saiba utilizar os comandos, deve 
digitar (help).

A estrutura central é a lista encadeada de linhas, onde cada nó representa uma linha do arquivo. Essa escolha permite inserções, remoções e alterações em posições arbitrárias 
de forma eficiente. Além disso, o editor mantém um histórico de operações usando pilhas de memória (undo e redo), possibilitando desfazer e refazer edições.

O código foi modularizado em três partes principais:

main.c: gerencia a interface com o usuário e interpreta os comandos.

commands.c: implementa as operações de edição e manipulação de arquivos.

utils.c: fornece as estruturas de dados (lista, pilhas de memória) e funções auxiliares.

Os .h de commands e utils possuem os protótipos das funções para serem utilizadas no main.

O projeto também cuida de detalhes como parsing de comandos em tokens, tratamento básico de erros (posições inválidas, arquivos inexistentes) e limpeza da tela para uma 
experiência mais organizada.

Em resumo, este editor é um exercício de estruturas de dados, manipulação de arquivos e gerenciamento de memória em C, combinando conceitos de listas, pilhas e modularização 
de código em um programa interativo e extensível.

Sobre os comandos disponíveis, todos inseridos na biblioteca commands.h:


open <arquivo> → abre um arquivo texto e carrega no editor.

openbin <arquivo> → abre um arquivo em modo binário.

save <arquivo> → salva o conteúdo atual em arquivo texto.

savebin <arquivo> → salva em formato binário.

quit → encerra o programa (com aviso para salvar antes).

print → imprime todas as linhas numeradas.

i <pos> <texto> → insere uma nova linha antes da posição indicada.

d <pos> → remove a linha na posição indicada.

r <pos> <novo texto> → substitui a linha por um novo conteúdo.

a <pos> <sufixo> → concatena texto ao final da linha.

split <pos> <idx> → divide a linha em duas no índice informado.

join <pos> → une a linha com a seguinte.

undo → desfaz a última operação de edição.

redo → refaz a última operação desfeita.

help → mostra a lista de comandos disponíveis.


Sobre funções extras criandas em utils.h:

Ele possui a declaração dos structs dos nós e das listas utilizados.

O código utiliza dois tipos de nós, sendo eles: nó que arazena uma string e o nó que armazena comandos para a realização de undo e redo.

Utiliza um tipo de lista duplamente encadeada, que armazena as linhas do arquivo em seus nós (como um buffer), e as pihas de undo e redo são pseudo pilhas apenas com ponteiros 
globais, um apontando para o topo da pilha de comandos dados (a ser utilizada em redo), e o outro apontando para o topo da pilha com os inversos dos comandos dados (a ser 
utilizada em undo).


Além do struct que declara as strings que armazenarão as partes do comando inserido na main em três tokens. Isto foi necessário pois houve um problema no uso de strtok, então 
foi feita a função Com_to_token para separar o comando(t1), a posição (linha desejada) ou nome o arquivo (t2) e o índice ou string a ser adicionada no texto(t3).

O utils.c armazena todas as funções de criação, organização, deleção de listas, além da função de limpar a o terminal ao início do programa e também a função que inverte os 
comandos inseridos e adiciona os comandos inseridos e seus inversos em duas pilhas que seráo utilizadas em redo e undo respectivamente.

Para o bom funcionamento do código o arquivo a ser aberto já deve existir e possuir ao menos uma linha com ao menos um caractere escrito nela, apartir disso todas as operações 
podem ser executadas.