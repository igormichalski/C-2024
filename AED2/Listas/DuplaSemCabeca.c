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
    novo->proximo = (*lista);
    novo->anterior = NULL;

    if((*lista)!=NULL){
        (*lista)->anterior = novo;
    }

    (*lista) = novo;
}

void removerINICIO(No **lista){
    if((*lista) != NULL){
        No *aux = (*lista);
        (*lista) = aux->proximo;
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

    if(*lista == NULL){
        *lista = novo;
        novo->anterior = NULL;
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
    if (aux == NULL) {
        printf("Lista vazia\n");
        return;
    }

    // Lista com um elemento
    if (aux->proximo == NULL) {
        free(aux);
        *lista = NULL;
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
    int tamanho = 0;
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
    while (i < index-1){
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
    while (i != index-1){
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
    if(lista == NULL) {
        printf("Lista vazia\n");
        return;
    }

    No *ultimo = lista;
    while (ultimo->proximo != NULL) {
        ultimo = ultimo->proximo;
    }

    while (ultimo != NULL) {
        printf("%d ", ultimo->dado);
        ultimo = ultimo->anterior;
    }
    printf("\n");
}


int main() {

    //Criando No cabeça
    No *Lista = NULL;

    inserir(&Lista, 0, 12);
    inserir(&Lista, 1, 52);
    inserir(&Lista, 2, 62);

    remover(&Lista, 0);
    remover(&Lista, 0);
    remover(&Lista, 0);

    //Imprimindo
    imprimir(Lista);
    printf("\nReverso\n");
    imprimirReverso(Lista);


    return 0;

}
