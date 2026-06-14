#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#define MAX 100

typedef struct Node{
    char lin[MAX];
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct Lista{
    int tam;
    Node *head;
    Node *tail;
}Lista;

typedef struct Com {
    char t1[10];
    char t2[10];
    char t3[100];
}Com;

typedef struct MemNode {
    char com[10];
    int pam1, pam2;
    char str[100];
    struct MemNode *next, *prev;
}MemNode;

extern MemNode* ptr;
extern MemNode *invptr;

Com com_to_token(char* command);
Node* create_str_Node(char *str);
Lista file_to_list(FILE **arq);
void insert_Node(char *str, Lista *l);
void insert_NodeMid(char *str, int pos, Lista *l);
void limpar_tela();
void remove_nodeMid(int pos, Lista *l);
void une_Node(int pos, Lista *l);
void memory_stack(const char* com, int pam1, int pam2, char* str);
void invmemory_stack(const char* com, int pam1, int pam2, char* str);
void memory_inversor(MemNode* memNode);

#endif