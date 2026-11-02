#include "headers.h"
#include <stdio.h>
#include <stdlib.h>

struct elemento {
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};

typedef struct elemento Elem;
// Extras
Lista* cria_lista(void) {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}
////////////////////////////////////////////////////////
int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = NULL;
    if ((*li) == NULL) {         /* lista vazia: insere inicio */
        no->ant = NULL;
        *li = no;
    } else {
        Elem* aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}
///////////////////////////////////////////////////////

// 1
void imprime_lista_inversa(Lista* li){
    if (li == NULL || *li == NULL) {
        printf("(lista vazia)\n");
        return;
    }

    Elem *no = *li;
    
    while(no -> prox != NULL){
        no = no -> prox;
    }

    while (no != NULL) {
    printf("%d ", no->dados.matricula);
    no = no->ant;
    }
}
// Nesse caso, o custo operacional se dá de O(2n), por conta dos 2 whiles.
// ou somente O(n), pelos laços percorrerem (n - 1) + n passos.

// 2
int lista_consistente(Lista* li){
    if (li == NULL) return 0;         
    if (*li == NULL) return 1;        

    Elem* no = *li;

    if (no->ant != NULL) return 0;

    while (no->prox != NULL) {
        if (no->prox->ant != no) return 0;
        no = no->prox;
    }

    return 1;
}

// 3 
/*
int remove_lista(Lista* li, int mat){
if(li == NULL) return 0;
if((*li) == NULL) return 0;
Elem* no = *li;
while(no != NULL && no->dados.matricula != mat)
no = no->prox;
if(no == NULL) return 0;
no->ant->prox = no->prox;
free(no);
return 1;
}
*/

// (a) o código faz as verificações inicias e não notifica um erro,
// depois ele pegamos no para percorrer no while que não funcionará pois 
// o primeiro elemento já é o 33 que procuramos, mas quando 
// o código tenta acessar o no->ant->prox entramos num ponteiro nulo
// e o comportamento do código se torna indefinido, podendo fechar ou
// acessar lixo de memória.

// (b)
/*
Questão 3b — Após remove_lista(li, 23):

*li aponta para o nó 33.

Nó 33:
    ant  = NULL
    prox = endereço do nó 16

Nó 16:
    ant  = endereço do antigo nó 23 (memória já liberada)
    prox = NULL

Percurso por prox: 33 → 16 → NULL
O ant de 16 permanece pendente, apontando para o antigo nó 23.

tamanho_lista devolve 2 porque percorre somente os campos
prox, visitando os nós 33 e 16.

lista_consistente devolve 0 porque 33->prox aponta para 16,
mas 16->ant não aponta para 33, quebrando a reciprocidade
das ligações.
*/

// (c)
int remove_lista(Lista* li, int mat) {
    if (!lista_consistente(li))
        return 0;

    Elem* no = *li;

    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;

    if (no == NULL)
        return 0;

    if (no->ant != NULL)
        no->ant->prox = no->prox;
    else
        *li = no->prox;

    if (no->prox != NULL)
        no->prox->ant = no->ant;

    free(no);
    return 1;
}

// 4
int remove_lista_pos(Lista* li, int pos) {
    if (pos <= 0 || !lista_consistente(li))
        return 0;

    Elem* no = *li;
    int i = 1;

    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }

    if (no == NULL)
        return 0;

    if (no->ant != NULL)
        no->ant->prox = no->prox;
    else
        *li = no->prox;

    if (no->prox != NULL)
        no->prox->ant = no->ant;

    free(no);
    return 1;
}

// O custo operacional é O(n), pela verificação da consistência
// e pelo percurso do while até a posição desejada.
// Não consegui fazer o teste no código mas digitarei a qtd do custo:

/*
Lista inicial: 33, 23, 16, 10, 5

1) Remoção da primeira posição: remove_lista_pos(li, 1)
   Remove 33.
   Resultado: 23, 16, 10, 5
   O campo ant do nó 23 passa a ser NULL.
   Retorno esperado: 1.

2) Remoção intermediária: remove_lista_pos(li, 2)
   Remove 16 da lista atual.
   Resultado: 23, 10, 5
   O prox de 23 aponta para 10 e o ant de 10 aponta para 23.
   Retorno esperado: 1.

3) Remoção da última posição: remove_lista_pos(li, 3)
   Remove 5 da lista atual.
   Resultado: 23, 10
   O campo prox do nó 10 passa a ser NULL.
   Retorno esperado: 1.

*/

// 5
int move_para_inicio(Lista* li, int mat) {
    if (!lista_consistente(li))
        return 0;

    Elem* no = *li;

    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;

    if (no == NULL)
        return 0;

    if (no == *li)
        return 1;

    no->ant->prox = no->prox;

    if (no->prox != NULL)
        no->prox->ant = no->ant;

    no->ant = NULL;
    no->prox = *li;
    (*li)->ant = no;
    *li = no;

    return 1;
}
/*
Quando o elemento está no meio, são escritos 5 campos:
no->ant->prox, no->prox->ant, no->ant, no->prox e (*li)->ant.

Quando é o último, são escritos 4 campos, pois
no->prox é NULL e a atribuição a no->prox->ant não ocorre.

Além desses campos, *li é atualizado nos dois casos.
Contando essa atualização, são 6 escritas no meio e 5 no último.
*/

// 6
int remove_todos(Lista* li, int mat) {
    if (li == NULL || *li == NULL)
        return 0;

    Elem* no = *li;
    int removidos = 0;

    while (no != NULL) {

        Elem* proximo = no->prox;

        if (no->dados.matricula == mat) {
            if (no->ant != NULL)
                no->ant->prox = no->prox;
            else
                *li = no->prox;

            if (no->prox != NULL)
                no->prox->ant = no->ant;

            free(no);
            removidos++;
        }

        no = proximo;
    }

    return removidos;
}

/*
Teste 1 — Matrículas repetidas:
Lista inicial: 7, 3, 7, 7, 5, 7
Chamada: remove_todos(li, 7)
Resultado: 3, 5
Retorno esperado: 4.
O ant de 3 é NULL e o prox de 5 é NULL.

Teste 2 — Todos os elementos têm a matrícula procurada:
Lista inicial: 7, 7, 7
Chamada: remove_todos(li, 7)
Resultado: lista vazia (*li == NULL).
Retorno esperado: 3.

Teste 3 — Matrícula inexistente:
Lista inicial: 3, 5
Chamada: remove_todos(li, 7)
Resultado: 3, 5
Retorno esperado: 0.

Custo operacional: O(n), com uma única passagem pela lista.
Espaço auxiliar: O(1).

Não chamamos lista_consistente porque ela faria uma
passagem adicional pela lista.
*/

// 7 
void inverte_lista(Lista* li) {
    if (li == NULL || *li == NULL)
        return;

    Elem* no = *li;
    Elem* proximo;

    while (no != NULL) {
        proximo = no->prox;

        no->prox = no->ant;
        no->ant = proximo;

        // O antigo último nó será o novo início.
        if (proximo == NULL)
            *li = no;

        no = proximo;
    }
}

/*
Ao trocar ant e prox de cada nó, todas as ligações passam
a ter o sentido inverso. Atualizar *li para o antigo último
nó completa a inversão, mantendo os vínculos recíprocos.

Exemplo:
Antes: 1, 2, 3, 4, 5
Depois: 5, 4, 3, 2, 1
lista_consistente(li) retorna 1.

Custo: O(n), pois cada nó é visitado uma vez.
Espaço auxiliar: O(1).
*/

// 8

int eh_palindromo(Lista* li) {
    if (li == NULL)
        return 0;

    if (*li == NULL)
        return 1;

    Elem* inicio = *li;
    Elem* fim = *li;

    while (fim->prox != NULL)
        fim = fim->prox;

    while (inicio != fim && inicio->ant != fim) {
        if (inicio->dados.matricula != fim->dados.matricula)
            return 0;

        inicio = inicio->prox;
        fim = fim->ant;
    }

    return 1;
}

/*
Condição de parada:
- Tamanho ímpar: inicio == fim (encontro no nó central).
- Tamanho par: inicio->ant == fim (os ponteiros se cruzam).

Testes:
1, 2, 3, 2, 1 → retorna 1.
4, 8, 8, 4     → retorna 1.
1, 2, 2, 3     → retorna 0.
Lista vazia        → retorna 1.
Um único elemento  → retorna 1.
li == NULL         → retorna 0.

Custo: O(n), pela busca do último nó e pelas comparações.
Espaço auxiliar: O(1).

Na lista simplesmente encadeada, não existe o campo ant,
portanto o ponteiro do final não pode caminhar para trás
diretamente.
*/