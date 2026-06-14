#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

Node* create_str_Node(char *str) { //pega linha do arquivo transforma em string no programa e faz um nó armazenando ela 
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->lin, str);
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

Lista file_to_list(FILE **arq) { //pega nó com linha do arquivo e faz uma lista com as linhas do arquivo
    char lin[MAX];
    Lista lista;
    lista.tam = 0;
    lista.head = NULL;
    lista.tail = NULL;
    while(fgets(lin, MAX, *arq) != NULL) {
        lin[strcspn(lin, "\n")] = '\0';
        Node *newNode = create_str_Node(lin);
        if(lista.tam == 0) {
            lista.head = newNode;
            lista.tail = newNode;
        }
        else {
            newNode->prev = lista.tail;
            lista.tail->next = newNode;
            lista.tail = newNode;
        }
        lista.tam++;
    }
    return lista;
}

void insert_Node(char *str, Lista *l) { //não sei se vai precisar nesse trabalho
    Node *newNode = create_str_Node(str);
    if(l->tam == 0) {
        l->head = newNode;
        l->tail = newNode;
    }
    else {
        newNode->next = l->head;
        l->head->prev = newNode;
        l->head = newNode;
    }
    l->tam++;
}

void insert_NodeMid(char *str, int pos, Lista *l) {
    Node *newNode = create_str_Node(str);
    if(l->tam == 0) {
        l->head = newNode;
        l->tail = newNode;
    }
    else if(pos == 0) {
        newNode->next = l->head;
        l->head->prev = newNode;
        l->head = newNode;
    }
    else if(pos == l->tam) {
        newNode->prev = l->tail;
        l->tail->next = newNode;
        l->tail = newNode;
    }
    else {
        Node *cur;
        if(pos < l->tam/2) {
            cur = l->head;
            for(int i = 0; i < pos; i++) {
                cur = cur->next;
            }
        }
        else {
            cur = l->tail;
            for(int i = l->tam-1; i > pos; i--) {
                cur = cur->prev;
            }
        }
        
        newNode->next = cur;
        newNode->prev = cur->prev;
        cur->prev->next = newNode;
        cur->prev = newNode;
    }
    l->tam++;
}

Com com_to_token(char* command) { 
    Com tokens = {{0}, {0}, {0}};
    int i = 0, j, count = 0;

    while (command[i] != '\0') { 
        if (count == 2) { 
            strcpy(tokens.t3, command + i); 
            break; 
        }

        char token[120] = {0}; 
        j = 0;
        while (command[i] != '\0' && !isspace(command[i])) { 
            token[j++] = command[i++];
        }
        token[j] = '\0'; 

        if(count == 0)
            strcpy(tokens.t1, token); 
        else
            strcpy(tokens.t2, token); 
        count++; 
        i++;
    }
    return tokens; 
}

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void remove_nodeMid(int pos, Lista *l) {
    Node *aux;
    if(l->tam == 0) {
        printf("ERRO: Não há nada para remover\n");
        return;
    }
    else if(pos == 0) {
        aux = l->head;
        l->head->next->prev = NULL;
        l->head = l->head->next;
        aux->next = NULL;
        free(aux);
    }
    else if(pos == l->tam-1) {
        aux = l->tail;
        l->tail->prev->next = NULL;
        l->tail = l->tail->prev;
        aux->prev = NULL;
        free(aux);
    }
    else {
        Node *cur;
        if(pos < l->tam/2) {
            cur = l->head;
            for(int i = 0; i < pos; i++) {
                cur = cur->next;
            }
        }
        else {
            cur = l->tail;
            for(int i = l->tam-1; i > pos; i--) {
                cur = cur->prev;
            }
        }
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        cur->next = NULL;
        cur->prev = NULL;
        free(cur);
    }
    l->tam--;
}

void une_Node(int pos, Lista *l) {
    if(l->tam == 0 || pos == l->tam) {
        printf("Não há linhas pra unir!");
        return;
    }
    else if(pos == 1) {
        strcat(l->head->lin, l->head->next->lin);
        remove_nodeMid(1, l);
    }
    else if(pos == l->tam) {
        strcat(l->tail->prev->lin, l->tail->lin);
        remove_nodeMid(l->tam, l);
    }
    else {
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
        strcat(cur->lin, cur->next->lin);
        remove_nodeMid(pos, l); 
    }
}

MemNode* ptr = NULL;

void memory_stack(const char* com, int pam1, int pam2, char* str) {
    MemNode *memNode = (MemNode*)malloc(sizeof(MemNode));
    memNode->next = NULL; memNode->prev = NULL; 
    strcpy(memNode->com, com); memNode->pam1 = pam1; memNode->pam2 = pam2; strcpy(memNode->str, str);

    if(ptr == NULL) {
        ptr = memNode;
    }
    else {
        memNode->next = ptr;
        ptr->prev = memNode;
        ptr = memNode;
    }
}

MemNode *invptr = NULL;

void invmemory_stack(const char* com, int pam1, int pam2, char* str) {
    MemNode *memNode = (MemNode*)malloc(sizeof(MemNode));
    memNode->next = NULL; memNode->prev = NULL; 
    strcpy(memNode->com, com); memNode->pam1 = pam1; memNode->pam2 = pam2; strcpy(memNode->str, str);

    if(invptr == NULL) {
        invptr = memNode;
    }
    else {
        memNode->next = invptr;
        invptr->prev = memNode;
        invptr = memNode;
    }
}

void memory_inversor(MemNode* memNode) {
    if(strcmp(memNode->com, "i") == 0) {
        invmemory_stack("d", memNode->pam1, -1, memNode->str);
    }
    else if(strcmp(memNode->com, "d") == 0) {
        invmemory_stack("i", memNode->pam1, -1, memNode->str);
    }
    else if(strcmp(memNode->com, "a") == 0) {
        invmemory_stack("r", memNode->pam1, -1, memNode->str);
    }
    else if(strcmp(memNode->com, "r") == 0) {
        invmemory_stack("r", memNode->pam1, -1, memNode->str);
    }
    else if(strcmp(memNode->com, "split") == 0) {
        invmemory_stack("join", memNode->pam1, memNode->pam2, memNode->str);
    }
    else if(strcmp(memNode->com, "join") == 0) {
        invmemory_stack("split", memNode->pam1, memNode->pam2, memNode->str);
    }
}