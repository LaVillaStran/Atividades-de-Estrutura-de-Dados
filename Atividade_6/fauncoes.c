#include <stdio.h>
#include <stdlib.h>
/* Prioridade: 1 = mais urgente ... 5 = menos urgente */
#include "header.h"
//1
int conta_tarefas_prioridade(ListaTarefas* li, int prioridade){
    if (li == NULL){
        return -1;
    }
    int contador = 0;
    Elemento* no = *li;

    while (no != NULL ){
        if (no->dados.prioridade == prioridade){
            contador ++;
        }
        no = no->prox;
    }
    return contador;
}
//2
int tarefa_mais_urgente(ListaTarefas* li, struct tarefa *t){
    if (li == NULL)return 0;
    Elemento* no = *li;
    if (no == NULL) return 0;

    struct tarefa ATIVIDADE_PRIODIRADE = no->dados;
    no = no->prox;

    while (no != NULL){
        if(no->dados.prioridade < ATIVIDADE_PRIODIRADE.prioridade){
            ATIVIDADE_PRIODIRADE = no->dados;
        }
        no = no->prox;
    *t = ATIVIDADE_PRIODIRADE;
    return 1;
    }
}
//3
#include <string.h>

int busca_tarefa_desc(ListaTarefas* li, char *texto, struct tarefa *t){
    if (li == NULL || texto == NULL) return 0;
    Elemento* no = *li;
    if (no == NULL) return 0;

    while (no != NULL){
        if (strstr(no->dados.descricao,texto)){
            *t = no->dados;
            return 1;
        }
        no = no->prox;
    }
    return 0;
}
//4
int insere_tarefa_final_prioridade(ListaTarefas* li, struct tarefa t){
    if (li == NULL) return 0;
    Elemento* no = *li;
    if (no != NULL) return 0;
    
    else{
        Elemento *ant = NULL, *atual = *li;
        while (no != NULL){
            
        }
    }
}