#include <stdio.h>
#include <stdlib.h>

//ESTRUTURA QUE UTILIZAMOSO
typedef struct no{
    int dado;
    struct no *proximo;
}No;



//IMPLEMENTADO PARA O INICIO
void inserirINICIO(No **lista, int valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;
    novo->proximo = (*lista)->proximo; //converte ele com os parenteses primeiro
    (*lista)->proximo = novo;
}

void removerINICIO(No **lista){
    if((*lista)->proximo != NULL){
        No *aux = (*lista)->proximo;
        (*lista)->proximo = aux->proximo;
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

    No *aux = *lista;
    while (aux->proximo!=NULL){
        aux = aux->proximo;
    }

    aux->proximo = novo;
}

void removerFIM(No **lista){
    No *aux = *lista;

    // Lista vazia
    if (aux->proximo == NULL) {
        printf("Lista vazia\n");
        return;
    }

    // Lista com um elemento
    if (aux->proximo == NULL) {
        free(aux->proximo);
        aux->proximo = NULL;
        return;
    }

    while (aux->proximo->proximo !=NULL){
        aux = aux->proximo;
    }

    free(aux->proximo);
    aux->proximo = NULL;

}


//Procedimentos de Ambos
int TamLista(No *lista){
    int tamanho = -1;
    while(lista != NULL){
        tamanho++;
        lista = lista->proximo;
    }
    return tamanho;
}

void inserir(No **Lista, int index, int valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;

    int tamanho = TamLista((*Lista));

    if(index <= 0 || index>tamanho){
        printf("Impossivel adicionar nessa posicao\n");
        return;
    }

    int i = 0;
    No *aux = *Lista;
    while(i != index-1){
        aux = aux->proximo;
        i++;
    }

    novo->proximo = aux->proximo;
    aux->proximo = novo;

}

void remover(No **lista, int index){
    No *aux = *lista;

    //Pegando o tamanho da lista
    int tamanho = TamLista(aux);

    if(index <= 0 || tamanho == 0 || index>tamanho){
        printf("Impossivel remover\n");
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

    //Criando No cabeça
    No *cabeca = (No*) malloc(sizeof(No));
    cabeca->proximo = NULL;


    inserirFIM(&cabeca, 12);
    inserirFIM(&cabeca, 23);
    inserirFIM(&cabeca, 129);
    //removerINICIO(&cabeca);
    //removerINICIO(&cabeca);
    //removerFIM(&cabeca);

    inserir(&cabeca, 2, 486);
    inserir(&cabeca, 4, 4786);
    inserir(&cabeca, 5, 955);

    remover(&cabeca, 2);

    //Imprimindo
    imprimir(cabeca);
    imprimir(cabeca);


    return 0;

}