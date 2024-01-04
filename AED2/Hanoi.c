#include <stdio.h>
#include <math.h>

void moveDisco(int n, char ori, char dest, char aux){
    if(n==1)
        printf("Mover disco: %d de %c para %c\n", n, ori, dest);
    else{
        moveDisco(n-1, ori, aux, dest);
        printf("Mover disco: %d de %c para %c\n", n, ori, dest);
        moveDisco(n-1, aux, dest, ori);
    }
}

int main(){

    int n;

    printf("Qual o numero de pecas: \n");
    scanf("%d", &n);

    int numeroMovimentos = pow(2,n) - 1;

    printf("%d\n", numeroMovimentos);

    moveDisco(n, 'A', 'B', 'C');

    return 0;
}
