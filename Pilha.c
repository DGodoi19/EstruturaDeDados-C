#include <stdio.h>
#include <stdlib.h>

typedef struct NoPilha {
    char simbolo;
    struct NoPilha *proximo;
} NoPilha;

void push(NoPilha **topo, char s) {
    NoPilha *novo = malloc(sizeof(NoPilha));
    novo->simbolo = s;
    novo->proximo = *topo;
    *topo = novo;
}

char pop(NoPilha **topo) {
    if (*topo == NULL) return '\0';
    NoPilha *aux = *topo;
    char s = aux->simbolo;
    *topo = aux->proximo;
    free(aux);
    return s;
}

int main() {
    FILE *arq = fopen("codigo.txt", "r");
    if (!arq) return 1;

    NoPilha *pilha = NULL;
    char c, t;
    int erro = 0;

    while ((c = fgetc(arq)) != EOF) {
        if (c == '(' || c == '[' || c == '{') push(&pilha, c);
        else if (c == ')' || c == ']' || c == '}') {
            t = pop(&pilha);
            if ((c == ')' && t != '(') || (c == ']' && t != '[') || (c == '}' && t != '{')) {
                erro = 1; break;
            }
        }
    }

    if (erro || pilha != NULL) printf("Erro: Parenteses/Chaves desbalanceados!\n");
    else printf("Sucesso: Sintaxe correta!\n");

    fclose(arq);
    return 0;
}
