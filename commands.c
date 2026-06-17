#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "utils.h"

int open(FILE **arq, char* comt2) {
    *arq = fopen(comt2, "r+");
    if(*arq != NULL) { //verifica se o arquivo foi aberto
        printf("O arquivo %s foi aberto\n", comt2);
        return 1;
    }
    else
        return 0;
}

int openbin(FILE **arq, char* comt2) {
    *arq = fopen(comt2, "rb+");
    if(*arq != NULL) { //verifica se o arquivo foi aberto
        printf("O arquivo %s foi aberto\n", comt2);
        return 1;
    }
    else
        return 0;
}

void quit(FILE **arq) {
    int conf;
    if(*arq != NULL) {
        printf("Cuidado! Certifique-se que salvou o seu arquivo! Os dados inseridos podem ser perdidos.\n");
        printf("Digite\n [0 - Quero salvar meu arquivo]\t[1 - Quero sair!]\n");
        scanf("%d", &conf);
        if(conf == 0) {
            return;
        }
        else if(conf == 1) {
            fclose(*arq);
            printf("Saindo...");
            exit(EXIT_SUCCESS);
        }
        else {
            printf("Dígito inválido! Tente novamente!\n");
            quit(arq);
        }  
    }
    else {
        printf("Saindo...");
        exit(EXIT_SUCCESS);
    }
}

void insert(Lista *l, char *comt2, char *comt3) {
    int pos = atoi(comt2); //transforma a string em inteiro para poder ser lido no laço for
    
    if(pos <= 0 || pos > l->tam+1) {
        printf("Posição inválida!\n");
        return;
    }
    insert_NodeMid(comt3, pos-1, l);
    }
    

void save(Lista *l, FILE **arq, char *arqname) {
    *arq = freopen(arqname, "w", *arq);
    Node *cur = l->head;
    while(cur != NULL){
        fputs(cur->lin, *arq);
        fputs("\n", *arq);
        cur = cur->next;
    }
    printf("Salvando...\n");
}

void savebin(Lista *l, FILE **arq, char *arqname) {
    *arq = freopen(arqname, "wb", *arq);
    Node *cur = l->head;
    while(cur != NULL){
        fputs(cur->lin, *arq);
        fputs("\n", *arq);
        cur = cur->next;
    }
    printf("Salvando...\n");
}

void print(Node *n, int i) { //precisa receber o i pois se não, como é recursiva, ao ser executada novamente reinicializa o i em 1
    if(n->next == NULL) {
        printf("%d| %s\n", i, n->lin);
        return;
    }
    printf("%d| %s\n", i, n->lin);
    return print(n->next, i+1);
}

void delete(Lista *l, char *comt2) {
    int pos = atoi(comt2); //transforma a string em inteiro para poder ser lido no laço for
    
    if(pos <= 0 || pos > l->tam) {
        printf("Posição inválida!\n");
        return;
    }
    remove_nodeMid(pos-1, l);
}

void join(Lista *l, char *comt2) { 
    int pos = atoi(comt2);

    if(pos <= 0 || pos > l->tam) { 
        printf("Posição inválida!\n");
        return;
    }
    une_Node(pos, l); //une a linha escolhida com a próxima
}

void replace(char *comt2, Lista *l, char *comt3) {
    int pos = atoi(comt2);

    if(pos <= 0 || pos > l->tam) { 
        printf("Posição inválida!\n");
        return;
    }

    Node *cur;
    if(pos < l->tam/2) {
        cur = l->head;
        for(int i = 1; i < pos; i++) {
            cur = cur->next;
        }
    }
    else {
        cur = l->tail;
        for(int i = l->tam; i > pos; i--) {
            cur = cur->prev;
        }
    }
    strcpy(cur->lin, comt3);
}

void add(char *comt2, Lista *l, char *comt3) {
    int pos = atoi(comt2);

    if(pos <= 0 || pos > l->tam) { 
        printf("Posição inválida!\n");
        return;
    }

    Node *cur;
    if(pos < l->tam/2) {
        cur = l->head;
        for(int i = 1; i < pos; i++) {
            cur = cur->next;
        }
    }
    else {
        cur = l->tail;
        for(int i = l->tam; i > pos; i--) {
            cur = cur->prev;
        }
    }
    strcat(cur->lin, comt3);
}

void split(char *comt2, char *comt3, Lista *l) {
    int pos = atoi(comt2);
    int indx = atoi(comt3);

    if(pos <= 0 || pos > l->tam+1) { 
        printf("Posição inválida!\n");
        return;
    }
    Node *cur;
    if(pos < l->tam/2) {
        cur = l->head;
        for(int i = 1; i < pos; i++) {
            cur = cur->next;
        }
    }
    else {
        cur = l->tail;
        for(int i = l->tam; i > pos; i--) {
            cur = cur->prev;
        }
    }
    
    size_t len = strlen(cur->lin);
    if (indx < 0 || (size_t)indx > len) {
        printf("Índice inválido!\n");
        return;
    }
    insert_NodeMid(cur->lin + indx, pos, l);
    cur->lin[indx] = '\0'; //para cortar a linha do índice desejado
}

void help() {
    printf("open <arquivo>\t\tAbre um arquivo de texto e carrega o conteúdo no editor.\n");
    printf("save <arquivo>\t\tSalva o documento atual em um arquivo texto.\n");
    printf("i <pos> <texto>\t\tInsere uma nova linha antes da posição <pos>.\n");
    printf("d <pos>\t\t\tRemove a linha na posição <pos>.\n");
    printf("r <pos> <novo texto>\tSubstitui a linha da posição indicada.\n");
    printf("a <pos> <sufixo>\tConcatena um sufixo ao final da linha da posição indicada.\n");
    printf("split <pos> <idx>\tDivide a linha em duas, no índice indicado.\n");
    printf("join <pos>\t\tUne a linha <pos> com a seguinte.\n");
    printf("undo\t\t\tDesfaz a última operação de edição.\n");
    printf("redo\t\t\tRefaz a última operação desfeita.\n");
    printf("print\t\t\tImprime todas as linhas numeradas, usando recursão.\n");
    printf("quit\t\t\tEncerra o programa, liberando toda a memória alocada dinamicamente.\n");
}

void undo(Lista *l) {
    if(invptr == NULL) {
        printf("Nada para desfazer.\n");
        return;
    }
    // pop do topo de invptr
    MemNode *top = invptr;
    invptr = top->next;
    if(invptr) invptr->prev = NULL;

    char num[16];
    sprintf(num, "%d", top->pam1);
    char num1[16];
    sprintf(num1, "%d", top->pam2);

    
    if(strcmp(top->com, "i") == 0) {
        insert(l, num, top->str);
       
    }
    else if(strcmp(top->com, "d") == 0) {
        delete(l, num);
        
    }
    else if(strcmp(top->com, "a") == 0) {
        replace(num, l, top->str);
       
    }
    else if(strcmp(top->com, "r") == 0) {
        replace(num, l, top->str);
        
    }
    else if(strcmp(top->com, "split") == 0) {
        split(num, num1, l);
    }
    else if(strcmp(top->com, "join") == 0) {
        join(l, num);
    }
    free(top);
}


void redo(Lista *l) {
    if(ptr == NULL) {
        printf("Nada para refazer.\n");
        return;
    }
    
    MemNode *top = ptr;
    ptr = top->next;
    if(ptr) ptr->prev = NULL;

    char num[16];
    sprintf(num, "%d", top->pam1);
    char num1[16];
    sprintf(num1, "%d", top->pam2);

    if(strcmp(top->com, "i") == 0) {
        insert(l, num, top->str);
    }
    else if(strcmp(top->com, "d") == 0) {
        delete(l, num);

    }
    else if(strcmp(top->com, "a") == 0) {
        add(num, l, top->str);

    }
    else if(strcmp(top->com, "r") == 0) {
        replace(num, l, top->str);

    }
    else if(strcmp(top->com, "split") == 0) {
        split(num, num1, l);

    }
    else if(strcmp(top->com, "join") == 0) {
        join(l, num);

    }
    free(top);
}
