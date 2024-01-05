#include <stdio.h>

int somar(int seq[], int inicio, int fim){
    if(inicio == fim){
        return seq[fim];
    }else
        return seq[inicio] + somar(seq, inicio+1, fim);
}

int main(){
    int sequencia[7] = {-9,5,6,8,4,2,6};

    printf("Soma: %d\n", somar(sequencia, 0, 6));
    return 0;
}
