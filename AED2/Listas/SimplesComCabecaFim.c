#include <stdio.h>
#include <stdlib.h>


typedef struct no{
    int dado;
    struct no *proximo;
}No;


void inserir(No **lista, int valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;
    novo->proximo = (*lista)->proximo; //converte ele com os parenteses primeiro
    (*lista)->proximo = novo;
}

void remover(No **lista){
    if((*lista)->proximo != NULL){
        No *aux = (*lista)->proximo;
        (*lista)->proximo = aux->proximo;
        free(aux);
    }else{
        printf("Lista já esta vazia\n");
    }
}

void imprimir(No *lista){
    while(lista != NULL){
        printf("%d \n", lista->dado);
        lista = lista->proximo;
    }
}

int main() {

    //Criando No cabeça
    No *cabeca = (No*) malloc(sizeof(No));
    cabeca->proximo = NULL;

    //Inserindo no Inicio
    inserir(&cabeca, 5);
    inserir(&cabeca, 6);
    inserir(&cabeca, 7);

    //Removendo no Inicio
    remover(&cabeca);

    //Imprimindo
    imprimir(cabeca);
    imprimir(cabeca);

    return 0;
}