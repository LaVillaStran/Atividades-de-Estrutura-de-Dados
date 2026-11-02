#include "headers.h"
#include <stdio.h>
#include <stdlib.h>

/* Mostra a ordem inversa porque essa e a impressao disponivel. */
static void mostra(Lista *li, const char *esperado) {
    printf("Esperado (inverso): %s\nObtido: ", esperado);
    imprime_lista_inversa(li);
    printf("\nConsistente: %d (esperado: 1)\n\n", lista_consistente(li));
}

int main(void) {
    Lista *li = cria_lista();
    if (li == NULL) return EXIT_FAILURE;

    int matriculas[] = {1, 2, 3, 2, 1};
    struct aluno al = {0};

    puts("1. Criacao e insercao");
    printf("Criou vazia: %d (esperado: 1)\n", *li == NULL);
    for (int i = 0; i < 5; i++) {
        al.matricula = matriculas[i];
        if (!insere_lista_final(li, al)) {
            /* Libera os nos ja inseridos, sem exigir libera_lista. */
            while (*li != NULL) remove_lista_pos(li, 1);
            free(li);
            return EXIT_FAILURE;
        }
    }
    mostra(li, "1 2 3 2 1");

    puts("2. Palindromo");
    printf("Retorno: %d (esperado: 1)\n\n", eh_palindromo(li));

    puts("3. Remove a primeira ocorrencia de 1");
    printf("Retorno: %d (esperado: 1)\n", remove_lista(li, 1));
    mostra(li, "1 2 3 2");
    printf("Palindromo agora: %d (esperado: 0)\n\n", eh_palindromo(li));

    puts("4. Remove a posicao 2 (matricula 3)");
    printf("Retorno: %d (esperado: 1)\n", remove_lista_pos(li, 2));
    mostra(li, "1 2 2");

    puts("5. Move a matricula 1 para o inicio");
    printf("Retorno: %d (esperado: 1)\n", move_para_inicio(li, 1));
    mostra(li, "2 2 1");

    puts("6. Inverte a lista");
    inverte_lista(li);
    mostra(li, "1 2 2");

    puts("7. Remove todas as ocorrencias de 2");
    printf("Removidos: %d (esperado: 2)\n", remove_todos(li, 2));
    mostra(li, "1");

    puts("8. Remove o unico elemento");
    printf("Retorno: %d (esperado: 1)\n", remove_lista(li, 1));
    mostra(li, "(lista vazia)");

    /* Todos os nos ja foram removidos; falta liberar o bloco da lista. */
    free(li);
    return EXIT_SUCCESS;
}
