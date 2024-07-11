#include "gfx.h"
#include <stdio.h>  /* printf */
#include <unistd.h> /* sleep  */
#include <stdlib.h>

//No 
struct s_arq_no
{
    int32_t chave:30;
    uint32_t esq:1;
    uint32_t dir:1;
};

FILE* lerArquivo(char arquivo[]){
    FILE *arvore = fopen(arquivo, "rb");
    if(arvore == NULL){
        printf("Arquivo nao abriu \n");
        exit(1);
    }


    struct s_arq_no *No = (struct s_arq_no*) malloc(sizeof(struct s_arq_no));
    while(fread(No, sizeof(struct s_arq_no), 1, arvore)){
        if(No->esq)
            printf("Esquerda: %d\n", No->chave);
        if(No->dir)
            printf("Direira: %d\n", No->chave);
    }
    
    return arvore;
}


int main(){

    char arquivo[20]= "6.bin";

    FILE *arvore = lerArquivo(arquivo);

    fclose(arvore);

    return 0;
}