#include <stdio.h>

//Inverter uma seqüência com n elementos.

// Maneira de Execução (impar)
// 1 2 3 4 5
// 5 2 3 4 1
// 5 4 3 2 1

// Maneira de Execução (Par)
// 1 2 3 4 5 6
// 6 2 3 4 5 1
// 6 5 3 4 2 1
// 6 5 4 3 2 1


void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void inverter(int seq[], int inicio, int fim) {
    if (inicio < fim) {
        trocar(&seq[inicio], &seq[fim]);
        inverter(seq, inicio + 1, fim - 1);
    }
}

int main(){

    int sequencia[5] = {1,2,3,4,5};

    for(int i=0; i<5; i++){
        printf("%d ", sequencia[i]);
    }

    printf("\n");
    inverter(sequencia, 0, 4);

    for(int i=0; i<5; i++){
        printf("%d ", sequencia[i]);
    }
    return 0;
}
