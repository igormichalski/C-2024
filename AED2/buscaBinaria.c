#include <stdio.h>
#include <stdlib.h>

//Realizar a busca binária, que é utilizada quando o vetor de entrada
//está ordenado. A idéia do algoritmo é comparar a chave de busca x
//com o elemento do meio do vetor para decidir se o elemento x foi
//encontrado, ou se é necessário continuar a pesquisa nos subvetores
//à direita ou à esquerda do elemento do meio.

int buscaBinaria(int inicio, int fim, int vetor[], int x){
    int meio = (inicio + fim)/2;

    if(inicio>fim){
        return 0;
    }else{
        if(vetor[meio]==x){
            return 1;
        }else{
            if(x>vetor[meio]){
                return buscaBinaria(meio+1, fim, vetor, x);
            }else{
                return buscaBinaria(inicio, meio-1, vetor, x);
            }
        }
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



    int x=1;
    while(x!=-1) {
        printf("Qual valor deseja procurar?\n");
        scanf("%d", &x);

        //Implemente aqui
        if (buscaBinaria(0, tamanho, vetor, x))
            printf("Numero encontrado!!\n");
        else
            printf("Numero nao encontrado!!\n");
    }

    free(vetor);

    return 0;
}
