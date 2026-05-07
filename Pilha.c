#include <stdio.h>
#include <stdlib.h>

typedef struct NoPilha {
    char simbolo;
    int linha;
    int coluna;
    struct NoPilha *proximo;
} NoPilha;

void push(NoPilha **topo, char s, int linha, int coluna) {
    NoPilha *novo = malloc(sizeof(NoPilha));
    if (!novo) {
        fprintf(stderr, "Erro: falha na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    novo->simbolo = s;
    novo->linha   = linha;
    novo->coluna  = coluna;
    novo->proximo = *topo;
    *topo = novo;
}

NoPilha *pop(NoPilha **topo) {
    if (*topo == NULL) return NULL;
    NoPilha *aux = *topo;
    *topo = aux->proximo;
    return aux;
}

void liberarPilha(NoPilha **topo) {
    while (*topo != NULL) {
        NoPilha *aux = *topo;
        *topo = aux->proximo;
        free(aux);
    }
}

char fechamento(char abertura) {
    if (abertura == '(') return ')';
    if (abertura == '[') return ']';
    if (abertura == '{') return '}';
    return '\0';
}

int main(void) {
    FILE *arq = fopen("codigo.txt", "r");
    if (!arq) {
        fprintf(stderr, "Erro: não foi possível abrir 'codigo.txt'.\n");
        return EXIT_FAILURE;
    }

    NoPilha *pilha = NULL;
    int c;
    int linha  = 1;
    int coluna = 0;
    int erro   = 0;

    while ((c = fgetc(arq)) != EOF) {
        if (c == '\n') { linha++; coluna = 0; continue; }
        coluna++;

        if (c == '(' || c == '[' || c == '{') {
            push(&pilha, (char)c, linha, coluna);

        } else if (c == ')' || c == ']' || c == '}') {
            NoPilha *topo = pop(&pilha);

            if (topo == NULL) {
                fprintf(stderr,
                    "Erro na linha %d, coluna %d: '%c' sem abertura correspondente.\n",
                    linha, coluna, (char)c);
                erro = 1;
                break;
            }

            if ((char)c != fechamento(topo->simbolo)) {
                fprintf(stderr,
                    "Erro na linha %d, coluna %d: esperava '%c' para fechar '%c' "
                    "aberto na linha %d, coluna %d.\n",
                    linha, coluna,
                    fechamento(topo->simbolo), topo->simbolo,
                    topo->linha, topo->coluna);
                free(topo);
                erro = 1;
                break;
            }

            free(topo);
        }
    }

    if (!erro && pilha != NULL) {
        NoPilha *p = pilha;
        fprintf(stderr, "Erro: símbolo(s) aberto(s) sem fechamento:\n");
        while (p != NULL) {
            fprintf(stderr, "  '%c' aberto na linha %d, coluna %d\n",
                    p->simbolo, p->linha, p->coluna);
            p = p->proximo;
        }
        erro = 1;
    }

    liberarPilha(&pilha);
    fclose(arq);

    if (erro) {
        printf("Resultado: ERRO — parênteses/colchetes/chaves desbalanceados.\n");
        return EXIT_FAILURE;
    }

    printf("Resultado: SUCESSO — sintaxe correta!\n");
    return EXIT_SUCCESS;
}
