#ifndef COMMANDS_H
#define COMMANDS_H
#include "utils.h"

int open(FILE **arq, char* comt2);

int openbin(FILE **arq, char* comt2);

void quit(FILE **arq);

void insert(Lista *l, char *comt2, char *comt3);

void save(Lista *l, FILE **arq, char *arqname);

void savebin(Lista *l, FILE **arq, char *arqname);

void print(Node *n, int i);

void delete(Lista *l, char *comt2);

void join(Lista *l, char *comt2);

void add(char *comt2, Lista *l, char *comt3);

void replace(char *comt2, Lista *l, char *comt3);

void split(char *comt2, char *comt3, Lista *l);

void help();

void undo(Lista *l);

void redo(Lista *l);

#endif