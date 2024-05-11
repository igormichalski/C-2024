#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int dado;
    struct no *proximo;
}No;

void empilhar(No **topo, int valor){
    No *novo = (No *)malloc(sizeof(No));
    novo->dado = valor;

    if(topo != NULL) {
        novo->proximo = *topo;
        *topo = novo;
    }else{
        *topo = novo;
        novo->proximo = NULL;
    }

}

void desempilhar(No **topo){
    if(*topo != NULL) {
        No *aux = *topo;
        *topo = aux->proximo;
        free(aux);
    }else{
        printf("A pilha ja esta vazia\n");
    }
}

// Função para imprimir os elementos da pilha
void printStack(No *top) {
    printf("Conteudo da pilha:\n");
    while (top != NULL) {
        printf("%d\n", top->dado);
        top = top->proximo;
    }
}

//Desalocar a pilha
void freeLista(No **topo){
    No *atual = *topo;
    while (atual != NULL){
        No *aux = atual->proximo;
        free(atual);
        atual = aux;
    }
    *topo = NULL;
}

int main(){

    //Iniciamos nossa Pilha
    No *topo = NULL;

    //push (empilhar)
    empilhar(&topo, 10);
    empilhar(&topo, 5);
    empilhar(&topo, 150);
    empilhar(&topo, 15);

    printStack(topo);

    printf("\nApos remocao\n\n");

    desempilhar(&topo);
    printStack(topo);

    freeLista(&topo);

    return 0;
}