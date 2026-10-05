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
    Elemento *no = *li;

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
    Elemento *no = *li;
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
    Elemento *no = *li;
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
    Elemento *no = *li;
    Elemento *novo = malloc(sizeof(Elemento));
    
    novo->dados = t;
    novo->prox = NULL;

    if (no != NULL) return 0;

    else
    {
        Elemento* aux = NULL, *final = *li;

        while (no != NULL){
            if (no->dados.prioridade == t.prioridade){
                aux = no;
            }
            final = no;
            no = no->prox;
        }
        if (aux != NULL){
            novo->prox = aux->prox;
            aux->prox = novo;
        }
        else if (final != NULL){
            final->prox = novo;
        }   
        else{
            *li = novo;
        }
    }
    return 1;
}
//5
int remove_tarefas_prioridade(ListaTarefas* li, int prioridade){
    if (li == NULL) return -1;
    if ((*li) == NULL) return 0;

    int qtd_removidos = 0;
    Elemento *no = li, *ant = NULL;

    while (no != NULL){
        if (no->dados.prioridade == prioridade){
            Elemento *apagar = no;

            if (ant == NULL){
                *li = no->prox;
            }
            else{
                ant->prox = no->prox;
            }
        no = no->prox;
        free(apagar);
        qtd_removidos++;
        }
        

        else{
            ant = no;
            no = no->prox; 
        }
    }
    return qtd_removidos;
}
//6
int inverte_lista(ListaTarefas* li){
    if (li == NULL) return 0;

    Elemento *ant = NULL, *no = *li, *seguinte;

    while(no != NULL){
        seguinte = no->prox;
        no->prox = ant;

        ant = no;
        no = seguinte;
    }

    *li = ant;
    return 1;
}
//7
int remove_tarefa_pos(ListaTarefas* li, int pos){
    if (li == NULL || pos < 1) return 0;

    Elemento *no = *li, *ant = NULL;
    int atual = 1;

    while (no != NULL && atual < pos) {
        ant = no;
        no = no->prox;
        atual++;
    }

    if (no == NULL) return 0;

    if (ant == NULL){
        *li = no->prox;
    }
    else{
        ant->prox = no->prox;
    }
    free(no);
    return 1;
}
//8
int mescla_tarefas(ListaTarefas* dst, ListaTarefas* src){
    if (dst == NULL || src == NULL) return -1;

    Elemento *no1 = src, *no2 = dst;
    int qtd_transferida = 0;

    while (no1->prox != NULL){
        no1 = no1->prox, qtd_transferida++;
    }   

    if (no2 == NULL){
        dst = src;
    }
    else{

        while (no2->prox != NULL){
            no2 = no2->prox;
        }
        no2->prox = src;
    }
    *src = NULL;
    return qtd_transferida;
}