#include <stdio.h>
#include <stdlib.h>

// ESTRUTURA QUE UTILIZAMOS
typedef struct no{
    int dado;
    struct no *proximo;
}No;

// IMPLEMENTADO PARA O INICIO
void inserirINICIO(No **lista, int valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;
    novo->proximo = (*lista);
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

// IMPLEMENTADO PARA O FIM
void inserirFIM(No **lista, int valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;
    novo->proximo = NULL;

    if(*lista == NULL){
        *lista = novo;
    }else{
        No *aux = *lista;
        while(aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
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

// Procedimentos de Ambos
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
    for(int i = 0; i < index - 1; i++){
        aux = aux->proximo;
    }

    novo->proximo = aux->proximo;
    aux->proximo = novo;
}

void remover(No **lista, int index){
    No *aux = *lista;

    // Pegando o tamanho da lista
    int tamanho = TamLista(aux);

    if(index < 0 || tamanho == 0 || index >= tamanho){
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
    free(temp);
}

void imprimir(No *lista){
    while(lista != NULL){
        printf("%d \n", lista->dado);
        lista = lista->proximo;
    }
}

int main() {
    // Criando lista sem nó cabeça
    No *Lista = NULL;

    inserirFIM(&Lista, 12);
    inserirFIM(&Lista, 129);

    inserir(&Lista, 0, 54);
    inserir(&Lista, 1, 96);
    inserir(&Lista, 1, 26);

    removerFIM(&Lista);

    imprimir(Lista);

    return 0;
}
