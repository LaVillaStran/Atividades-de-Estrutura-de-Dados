#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
//1
int lista_tem_espaco(Lista *li, int n)
{
    if (li == NULL)
        return 2;

    if (li->qtd + n <= MAX)
        return 1;

    return 0;
}
//2
float soma_precos(Lista* li){
    if (li == NULL){
        return 0;
    }
    float soma = 0;
    for (int i ; i < li->qtd ; i++){
        soma += li->dados[i].preco;
    }
    return soma;
}
//3
int busca_por_nome(Lista* li, char *nome, struct produto *p){
    if (li == NULL){
        return 0;
    }
    for (int i = 0; i < li->qtd; i++){
        if (strcmp(li->dados[i].nome, nome) == 0){
            *p = li->dados[i];
            return 1;
        }
    }

    return 0;
}
//4
int insere_lista_decrescente(Lista* li, struct produto p){
    if (li == NULL){
        return  0;
    }

    if (li->qtd == MAX){
        return 0;
    }

    int i = 0;

     while (i < li->qtd && li->dados[i].preco > p.preco){
        i++;
    }

    for (int k = li->qtd - 1; k >= i; k--){
        li->dados[k + 1] = li->dados[k];
    }

    li->dados[i] = p;
    li->qtd++;

    return 1;
}
//5
int remove_mais_caro(Lista* li, struct produto *removido){
    if (li == NULL){
        return 0;
    }
    float maior = li->dados[0].preco;
    int posicao =  0;
    for (int  i = 0 ; i < li->qtd ; i ++){
        if (li->dados[i].preco > maior){
            maior = li->dados[i].preco;
            posicao = i;
        }
    }
    *removido = li->dados[posicao];

    for (int i = posicao; i < li->qtd - 1; i++){
        li->dados[i] = li->dados[i + 1];
    }

    li->qtd--;

    return 1;
}
//6
int conta_faixa_preco(Lista *li, float min, float max){
    if (li == NULL){
        return 0;
    }

    int contador = 0;

    for (int i = 0; i < li->qtd; i++){
        if (li->dados[i].preco >= min &&
            li->dados[i].preco <= max){
            contador++;
        }
    }

    return contador;
}
//7
int remove_abaixo_de(Lista* li, float precoMinimo){
    if (li == NULL){
        return 0;
    }

    int removidos = 0;
    int i = 0;

    while (i < li->qtd){

        if (li->dados[i].preco < precoMinimo){

            li->qtd--;
            li->dados[i] = li->dados[li->qtd];

            removidos++;

        }

        else{
            i++;
        }
    }

    return removidos;
}
//8
int mescla_listas(Lista* destino, Lista* origem){
    if (destino == NULL || origem == NULL){
        return 0;
    }

    int inseridos = 0;

    for (int i = 0; i < origem->qtd; i++){

        if (destino->qtd == MAX){
            break;
        }

        int existe = 0;

        for (int j = 0; j < destino->qtd; j++){
            if (origem->dados[i].codigo == destino->dados[j].codigo){
                existe = 1;
                break;
            }
        }

        if (!existe){
            destino->dados[destino->qtd] = origem->dados[i];
            destino->qtd++;
            inseridos++;
        }
    }

    return inseridos;
}