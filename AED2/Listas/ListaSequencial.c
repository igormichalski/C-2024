#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int dado;
}Registro;

typedef struct {
    Registro A[50];
    int quantiElementos;
}Lista;

void inicializar(Lista **minhalista){
    (*minhalista)->quantiElementos = 0;
}

void exibir(Lista **minhalista){
    printf("Lista: ");
    for(int i = 0; i< (*minhalista)->quantiElementos; i++){
        printf("%d ", (*minhalista)->A[i].dado);
    }
    printf("\n");
}


int buscarNumero(Lista **minhalista, int x){
    for(int i = 0; i < (*minhalista)->quantiElementos; i++){
       if((*minhalista)->A[i].dado == x){
           return 1;
       }
    }
    return 0;
}

void inserir(Lista **minhalista, int valor){
    if((*minhalista)->quantiElementos < 50){
        for(int i = (*minhalista)->quantiElementos - 1; i>=0; i--){
            (*minhalista)->A[i+1].dado =  (*minhalista)->A[i].dado;
        }
        (*minhalista)->A[0].dado = valor;
        (*minhalista)->quantiElementos++;
    }else
        printf("Lista cheia\n");
}

int main() {

    Lista *minhaLista = (Lista *) malloc(sizeof(Lista));

    if (minhaLista == NULL) {
        printf("Erro ao alocar memória.");
        return 1;
    }

    inicializar(&minhaLista);
    inserir(&minhaLista, 10);
    inserir(&minhaLista, 120);
    inserir(&minhaLista, 130);
    inserir(&minhaLista, 140);

   if( buscarNumero(&minhaLista, 10) )
       printf("Encontrado\n");
   else
       printf("Nao Encontrado\n");

    exibir(&minhaLista);

    return 0;
}