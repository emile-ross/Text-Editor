#include "commands.h"

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    limpar_tela();
    FILE *arq = NULL;
    Lista lista;

    printf("        :::   :::   :::::::::: ::::::::: ::::::::::: ::::::::::: ::::::::  ::::::::: \n");
    printf("      :+:+: :+:+:  :+:        :+:    :+:    :+:         :+:    :+:    :+: :+:    :+: \n");
    printf("    +:+ +:+:+ +:+ +:+        +:+    +:+    +:+         +:+    +:+    +:+ +:+    +:+  \n");
    printf("   +#+  +:+  +#+ +#++:++#   +#+    +:+    +#+         +#+    +#+    +:+ +#++:++#:    \n");
    printf("  +#+       +#+ +#+        +#+    +#+    +#+         +#+    +#+    +#+ +#+    +#+    \n");
    printf(" #+#       #+# #+#        #+#    #+#    #+#         #+#    #+#    #+# #+#    #+#     \n");
    printf("###       ### ########## ######### ###########     ###     ########  ###    ###      \n");
 
 
    printf("\n\t\t: : :::+:+++#+###  Editor de Texto  ###+#+++:+::: : :\n");
    printf("Digite 'help' para a lista de comandos de meditor!\n");

    while(1) {
        printf("mtext> ");
        char com[MAX];
        fgets(com, sizeof(com), stdin);
        com[strcspn(com, "\n")] = '\0';
        Com coms = com_to_token(com);

        char *token = coms.t1;
        if(strcmp("help", token) == 0) {
                help();
            }
        else if(strcmp("open", token) == 0) {
            if(open(&arq, coms.t2) == 0) {
                printf("ERRO: não foi possível abrir o arquivo!");
            }
            lista = file_to_list(&arq);
        }
        else if(strcmp("openbin", token) == 0) {
            if(openbin(&arq, coms.t2) == 0) {
                printf("ERRO: não foi possível abrir o arquivo!");
            }
            lista = file_to_list(&arq);
        }
        else if(strcmp("quit", token) == 0) {
            quit(&arq);
        }
        else if(arq != NULL) {
            if(strcmp("save", token) == 0) {
                save(&lista, &arq, coms.t2);
            } 
            else if(strcmp("savebin", token) == 0) {
                savebin(&lista, &arq, coms.t2);
            } 
            else if(strcmp("i", token) == 0) {
                MemNode *mem = (MemNode*)malloc(sizeof(MemNode));
                mem->next = NULL; mem->prev = NULL; strcpy(mem->com, "i"); mem->pam1 = atoi(coms.t2); strcpy(mem->str, coms.t3);
                mem->pam2 = -1;
                memory_stack("i", mem->pam1, -1, mem->str);
                memory_inversor(mem);
                insert(&lista, coms.t2, coms.t3);
            }
            else if(strcmp("d", token) == 0) {
                MemNode *mem = (MemNode*)malloc(sizeof(MemNode));
                mem->next = NULL; mem->prev = NULL; strcpy(mem->com, "d"); mem->pam1 = atoi(coms.t2); 
                Node *cur = lista.head;
                for(int i = 0; i < mem->pam1-1; i++) {
                    cur = cur->next;
                }
                strcpy(mem->str, cur->lin);
                mem->pam2 = -1;
                memory_stack("d", mem->pam1, -1, mem->str);
                memory_inversor(mem);
                delete(&lista, coms.t2);
            }
            else if(strcmp("r", token) == 0) {
                MemNode *mem = (MemNode*)malloc(sizeof(MemNode));
                mem->next = NULL; mem->prev = NULL; strcpy(mem->com, "r"); mem->pam1 = atoi(coms.t2); 
                Node *cur = lista.head;
                for(int i = 0; i < mem->pam1-1; i++) {
                    cur = cur->next;
                }
                strcpy(mem->str, cur->lin);
                mem->pam2 = -1;
                memory_inversor(mem);
                replace(coms.t2, &lista, coms.t3);
                strcpy(mem->str, cur->lin);
                memory_stack("r", mem->pam1, -1, mem->str);
            }
            else if(strcmp("a", token) == 0) {
                MemNode *mem = (MemNode*)malloc(sizeof(MemNode));
                mem->next = NULL; mem->prev = NULL; strcpy(mem->com, "a"); mem->pam1 = atoi(coms.t2); 
                Node *cur = lista.head;
                for(int i = 0; i < mem->pam1-1; i++) {
                    cur = cur->next;
                }
                strcpy(mem->str, cur->lin);
                mem->pam2 = -1;
                memory_inversor(mem);
                add(coms.t2, &lista, coms.t3);
                strcpy(mem->str, cur->lin);
                memory_stack("r", mem->pam1, -1, mem->str);
            }
            else if(strcmp("split", token) == 0) {
                MemNode *mem = (MemNode*)malloc(sizeof(MemNode));
                mem->next = NULL; mem->prev = NULL; strcpy(mem->com, "split"); mem->pam1 = atoi(coms.t2); mem->pam2 = atoi(coms.t3); mem->str[0] = '\0';
                split(coms.t2, coms.t3, &lista);
                memory_stack("split", mem->pam1, mem->pam2, mem->str);
                memory_inversor(mem);
            }
            else if(strcmp("join", token) == 0) {
                MemNode *mem = (MemNode*)malloc(sizeof(MemNode));
                mem->next = NULL; mem->prev = NULL; strcpy(mem->com, "join"); mem->pam1 = atoi(coms.t2); mem->str[0] = '\0';
                Node *cur = lista.head;
                for(int i = 0; i < mem->pam1-1; i++) {
                    cur = cur->next;
                }
                size_t tam = strlen(cur->lin);
                mem->pam2 = (int) tam;
                join(&lista, coms.t2);
                memory_stack("join", mem->pam1, mem->pam2, mem->str);
                memory_inversor(mem);
                
            }
            else if(strcmp("undo", token) == 0) {
                undo(&lista);
            }
            else if(strcmp("redo", token) == 0) {
                redo(&lista);
            }
            else if(strcmp("print", token) == 0) {
                print(lista.head, 1);
            }
        }
        else 
        printf("Você não abriu um arquivo!\n");
    }
    return 0;
}