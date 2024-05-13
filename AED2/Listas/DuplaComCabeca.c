#include <stdio.h>
#include <stdlib.h>

//ESTRUTURA QUE UTILIZAMOSO
typedef struct no{
    int dado;
    struct no *proximo;
    struct no *anterior;
}No;

//IMPLEMENTADO PARA O INICIO
void inserirINICIO(No **lista, int valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;

    novo->proximo = (*lista)->proximo;

    if((*lista)->proximo != NULL){
        (*lista)->proximo->anterior = novo;
    }
    (*lista)->proximo = novo;
    novo->anterior = (*lista);
}

void removerINICIO(No **lista){
    if((*lista)->proximo != NULL){
        No *aux = (*lista)->proximo;
        (*lista)->proximo = aux->proximo;
        if(aux->proximo != NULL){
            aux->proximo->anterior = aux;
        }
        free(aux);
    }else{
        printf("Lista já esta vazia\n");
    }
}


//IMPLEMENTADO PARA O FIM
void inserirFIM(No **lista, int valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;
    novo->proximo = NULL;

    if((*lista)->proximo == NULL){
        (*lista)->proximo = novo;
        novo->anterior = (*lista);
    }else{
        No *aux = *lista;
        while(aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
        novo->anterior = aux;
    }
}

void removerFIM(No **lista){
    No *aux = *lista;

    // Lista vazia
    if (aux->proximo == NULL) {
        printf("Lista vazia\n");
        return;
    }

    while (aux->proximo->proximo != NULL){
        aux = aux->proximo;
    }

    free(aux->proximo);
    aux->proximo = NULL;

}


//Procedimentos de Ambos
int TamLista(No *lista){
    int tamanho = 0; // Começar com 0, pois o nó cabeça não é considerado
    lista = lista->proximo; // Ignorar o nó cabeça
    while(lista != NULL){
        tamanho++;
        lista = lista->proximo;
    }
    return tamanho;
}

void inserir(No **lista, int index, int valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;

    int tamanho = TamLista(*lista);

    if(index < 0 || index > tamanho){
        printf("Impossivel adicionar nessa posicao\n");
        return;
    }

    if(index == 0){
        inserirINICIO(&(*lista), valor);
        return;
    }

    No *aux = *lista;
    int i = 0;
    while (i < index){
        aux = aux->proximo;
        i++;
    }

    novo->proximo = aux->proximo;
    novo->anterior = aux;

    if(aux->proximo !=NULL) {
        aux->proximo->anterior = novo;
    }
    aux->proximo = novo;
}

void remover(No **lista, int index){
    No *aux = *lista;

    //Pegando o tamanho da lista
    int tamanho = TamLista(aux);

    if(index < 0 || index >= tamanho){
        printf("Impossivel remover\n");
        return;
    }

    if(index == 0){
        removerINICIO(&(*lista));
        return;
    }

    int i=0;
    while (i != index){
        aux = aux->proximo;
        i++;
    }

    No *temp = aux->proximo;
    aux->proximo = aux->proximo->proximo;
    if(aux->proximo != NULL){
        aux->proximo->anterior = aux;
    }

    free(temp);

}


void imprimir(No *lista){
    lista = lista->proximo; // Ignorar o nó cabeça
    if(lista == NULL) {
        printf("Lista vazia\n");
        return;
    }

    while(lista != NULL){
        printf("%d ", lista->dado);
        lista = lista->proximo;
    }
    printf("\n");
}

void imprimirReverso(No *lista) {
    lista = lista->proximo; // Ignorar o nó cabeça
    if(lista == NULL) {
        printf("Lista vazia\n");
        return;
    }

    No *ultimo = lista;
    while (ultimo->proximo != NULL) {
        ultimo = ultimo->proximo;
    }

    while (ultimo != lista->anterior) { // Parar antes do nó cabeça
        printf("%d ", ultimo->dado);
        ultimo = ultimo->anterior;
    }
    printf("\n");
}

int main() {

    //Criando No cabeça
    No *cabeca = (No*) malloc(sizeof(No));
    cabeca->proximo = NULL;
    cabeca->anterior = NULL;

    inserirFIM(&cabeca, 52322);
    inserirINICIO(&cabeca, 12);
    inserirINICIO(&cabeca, 52);
    inserirFIM(&cabeca, 522);
    inserir(&cabeca, 0, 62);

    //removerINICIO(&cabeca);
    //removerFIM(&cabeca);
    remover(&cabeca, 0);

    //Imprimindo
    imprimir(cabeca);
    printf("\nReverso\n");
    imprimirReverso(cabeca);


    return 0;

}