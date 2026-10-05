struct tarefa {
int codigo;
char descricao[40];
int prioridade; /* 1 = mais urgente ... 5 = menos urgente */
};

typedef struct elemento* ListaTarefas;

struct elemento {
struct tarefa dados; // campo de informação
struct elemento *prox; // ponteiro para o próximo nó
};

typedef struct elemento Elemento;

int conta_tarefas_prioridade(ListaTarefas* li, int prioridade);
int tarefa_mais_urgente(ListaTarefas* li, struct tarefa *t);
int busca_tarefa_desc(ListaTarefas* li, char *texto, struct tarefa *t);
int insere_tarefa_final_prioridade(ListaTarefas* li, struct tarefa t);
int remove_tarefas_prioridade(ListaTarefas* li, int prioridade);
int inverte_lista(ListaTarefas* li);
int remove_tarefa_pos(ListaTarefas* li, int pos);
int mescla_tarefas(ListaTarefas* dst, ListaTarefas* src);