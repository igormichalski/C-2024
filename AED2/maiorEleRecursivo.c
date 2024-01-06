#include <stdio.h>
#include <stdlib.h>

//Encontrar o maior número de um conjunto com n elementos

int procurar(int vetor[], int inicio, int fim, int maior){
    if(inicio>fim)
        return maior;
    else {
        if (vetor[inicio] > maior) {
            maior = vetor[inicio];
        }
        return procurar(vetor, inicio + 1, fim, maior);
    }
}

int main(){

    int *vetor, tamanho;

    scanf("%d", &tamanho);

    vetor = (int *)malloc(tamanho*sizeof(int));
    if(vetor==NULL){
        printf("ERRO na alocacao do Vetor\n");
        return 1;
    }

    printf("Informe os valores do Vetor\n");
    for(int i=0; i<tamanho; i++){
        scanf("%d", &vetor[i]);
    }

    printf("O maior elemento e: %d\n" , procurar(vetor, 0, tamanho-1, vetor[0]));

    free(vetor);


    return 0;
}
