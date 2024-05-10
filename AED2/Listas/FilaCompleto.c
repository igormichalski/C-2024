#include <stdio.h>
#include <stdlib.h>


typedef struct no{
    int dado;
    struct no *proximo;
}No;


void entrarNaFila(No **Fila, int valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;

    if(novo != NULL){
        if(*Fila == NULL) {
            *Fila = novo;
        }else{
            No *aux = *Fila;
            while(aux->proximo != NULL){
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }
        novo->proximo = NULL;
    }else{
        printf("Erro ao alocar novo No da fila\n");
    }
}

void sairDaFila(No **Fila) {
    if (*Fila == NULL) {
        printf("Fila já esta vazia\n");
    } else {
        No *aux = *Fila;
        *Fila = aux->proximo;
        free(aux);
    }
}

void imprimir(No *Fila){
    while (Fila != NULL){
        printf("%d\n", Fila->dado);
        Fila = Fila->proximo;
    }
}

int main() {

    No *comecoFila = NULL;

    entrarNaFila(&comecoFila, 2);
    entrarNaFila(&comecoFila, 5);
    entrarNaFila(&comecoFila, 54);
    entrarNaFila(&comecoFila, 3);
    entrarNaFila(&comecoFila, 59);
    entrarNaFila(&comecoFila, 57);

    imprimir(comecoFila);

    printf("ZZZZZZZZZZZZZZZZZZZZZ\n");

    sairDaFila(&comecoFila);
    sairDaFila(&comecoFila);

    imprimir(comecoFila);


    return 0;
}
