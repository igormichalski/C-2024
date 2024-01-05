#include <stdio.h>

int validar(int seq[], int inicio, int fim, int x){
    if(inicio>fim){
        return 0;
    }
    if(seq[inicio] == x){
        return 1;
    }else {
        return validar(seq, inicio + 1, fim, x);
    }
    
}

int main(){
    int sequencia[7] = {-9,5,6,8,4,2,61};

    int x;
    scanf("%d", &x);

    if(validar(sequencia, 0, 6, x))
        printf("X esta na sequencia\n");
    else
        printf("X nao esta na sequencia\n");


    return 0;
}
