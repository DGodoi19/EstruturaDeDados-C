#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* proximo;
} No;

void inserir(No **inicio, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = *inicio;
    *inicio = novo;
}

void remover_por_indice(No **inicio, int indice) {
    if (*inicio == NULL) {
        printf("\nA lista esta vazia!\n");
        return;
    }

    No *aux = *inicio;

    if (indice == 0) {
        *inicio = aux->proximo;
        free(aux);
        return;
    }

    for (int i = 0; aux != NULL && i < indice - 1; i++) {
        aux = aux->proximo;
    }

    if (aux == NULL || aux->proximo == NULL) {
        printf("\nIndice maior que a lista\n");
        return;
    }

    No *alvo = aux->proximo;
    aux->proximo = alvo->proximo;
    free(alvo); // Removido o *
}

void listar(No *inicio) {
    No *atual = inicio;
    int i = 0;
    while (atual != NULL) {
        printf("Indice [%d]: %d -> ", i, atual->valor);
        atual = atual->proximo;
        i++;
    }
    printf("NULL\n");
}

int main() {
    No *minhaLista = NULL; // Removido o ()
    int opcao, valor, indice;

    do {
        printf("\n--- MENU LISTA SIMPLES ---");
        printf("\n1. Inserir elemento");
        printf("\n2. Remover por indice");
        printf("\n3. Imprimir lista");
        printf("\n0. Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor para inserir: ");
                scanf("%d", &valor);
                inserir(&minhaLista, valor);
                printf("Valor %d inserido com sucesso!\n", valor);
                break;

            case 2:
                if (minhaLista == NULL) { // Corrigido de 'listar' para 'minhaLista'
                    printf("Erro: A lista esta vazia!\n");
                } else {
                    printf("Digite o indice que deseja remover: ");
                    scanf("%d", &indice);
                    remover_por_indice(&minhaLista, indice);
                    printf("Operacao de remocao concluida.\n");
                }
                break;

            case 3:
                printf("\n--- Estado Atual da Lista ---\n");
                listar(minhaLista);
                break;
        }
    } while (opcao != 0);

    // O free() no final do main precisa de um ponteiro,
    // mas o ideal é fazer um loop para dar free em todos os nós.
    return 0;
}
