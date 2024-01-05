#include <stdio.h>
#include <string.h>


int palindromo(char string[], int inicio, int fim) {
      if(inicio < fim) {;
          if (string[inicio] != string[fim]) {
              return 0;
          } else {
              palindromo(string, inicio + 1, fim - 1);
          }
      }else{
          return 1;
      }
}

int main(){

    char string[50];
    int tamanho;

    fgets(string,sizeof(string), stdin);
    string[strcspn(string, "\n")] = '\0';
    tamanho = strlen(string);
    printf("%d", tamanho);

    printf("\n");
    int resultado = palindromo(string, 0, tamanho-1);

    if(resultado)
        printf("E palindromo\n");
    else
        printf("Nao e palindromo\n");

    return 0;
}
