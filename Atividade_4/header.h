#include <stdio.h>

#define MAX 100

struct produto {
int codigo;
char nome[30];
float preco;
};

struct lista {
    int qtd;
    struct produto dados[MAX];
};

typedef struct lista Lista;

/*                  Prototipos a implementar                    */
int lista_tem_espaco(Lista* li, int n);
float soma_precos(Lista* li);
int busca_por_nome(Lista* li, char *nome, struct produto *p);
int insere_lista_decrescente(Lista* li, struct produto p);
int remove_mais_caro(Lista* li, struct produto *removido);
int conta_faixa_preco(Lista* li, float min, float max);
int remove_abaixo_de(Lista* li, float precoMinimo);
int mescla_listas(Lista* destino, Lista* origem);