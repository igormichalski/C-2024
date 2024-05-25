#include "gfx.h"
#include <stdio.h>  /* printf */
#include <unistd.h> /* sleep  */
#include <math.h> //Makefile alterado para poder rodar a biblioteca, "-lm" adicionado
#include <stdlib.h>

//No para Fila/Pilha/SimplisEncadeada
typedef struct no {
    int dado;
    struct no *proximo;
} No;

//No para Duplamente Encadeada
typedef struct noDuplo{
    int dado;
    struct noDuplo *proximo;
    struct noDuplo *anterior;
}NoDuplo;

//Circular
void inserirCircular(No **cabeca, int dado) {
    No *novo = (No*)malloc(sizeof(No));
    novo->dado = dado;

    if (*cabeca == NULL) {
        novo->proximo = novo; // Lista vazia, aponta para si mesmo
        *cabeca = novo;
    } else if (dado <= (*cabeca)->dado) {
        // Inserção no início da lista
        No *ultimo = *cabeca;
        while (ultimo->proximo != *cabeca) {
            ultimo = ultimo->proximo;
        }
        novo->proximo = *cabeca;
        *cabeca = novo;
        ultimo->proximo = novo;
    } else {
        // Inserção no meio ou no final da lista
        No *atual = *cabeca;
        while (atual->proximo != *cabeca && atual->proximo->dado < dado) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}

void removerCircular(No **cabeca, int x) {
    if (*cabeca == NULL) {
        printf("Lista vazia\n");
        return;
    }

    No *atual = *cabeca;
    No *anterior = NULL;

    // Procurar o valor na lista
    while (atual->proximo != *cabeca && atual->dado != x) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Verificar se o valor foi encontrado
    if (atual->dado != x) {
        printf("Valor %d nao encontrado na lista\n", x);
        return;
    }

    // Se o nó a ser removido é o único na lista
    if (atual == *cabeca && atual->proximo == *cabeca) {
        *cabeca = NULL;
    } else if (atual == *cabeca) { // Se o nó a ser removido é o primeiro na lista
        No *ultimo = *cabeca;
        while (ultimo->proximo != *cabeca) {
            ultimo = ultimo->proximo;
        }
        *cabeca = (*cabeca)->proximo;
        ultimo->proximo = *cabeca;
    } else { // Se o nó a ser removido está no meio da lista
        anterior->proximo = atual->proximo;
    }

    free(atual);
}


No* buscarCircular(No *cabeca, int numero) {
    if (cabeca == NULL) {
        return NULL;
    }
    No *atual = cabeca;
    do {
        if (atual->dado == numero) {
            return atual;
        }
        atual = atual->proximo;
    } while (atual != cabeca);
    return NULL;
}

//Simples Encadeado sem No cabeça
void inserirSimples(No** lista, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;

    if (*lista == NULL || (*lista)->dado >= valor) {
        novo->proximo = *lista;
        *lista = novo;
    } else {
        No* atual = *lista;
        while (atual->proximo != NULL && atual->proximo->dado < valor) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}

void removerSimples(No **lista, int valor){
    if((*lista) != NULL){
        No *atual = (*lista);
        No *anterior = NULL;
        
        while(atual != NULL && atual->dado != valor){
            anterior = atual;
            atual = atual->proximo;
        }

        if(atual == NULL){
            printf("Valor %d nao encontrado na lista\n", valor);
            return;
        }

        if(anterior == NULL){
            (*lista) = atual->proximo;
        }else{
            anterior->proximo = atual->proximo;
        }

        free(atual);
    }else{
        printf("Lista já está vazia\n");
        sleep(1);
    }
}

No* buscarSimples(No *lista, int numero){
    while (lista != NULL) {
        if (lista->dado == numero) {
            return lista; 
        }
        lista = lista->proximo;
    }
    return NULL; 
}


//Duplamente Encadeado com No cabeça 
void inserirDuplamente(NoDuplo **lista, int valor){
    NoDuplo *novo = (NoDuplo*) malloc(sizeof(No));
    novo->dado = valor;

    novo->proximo = (*lista)->proximo;

    if((*lista)->proximo != NULL){
        (*lista)->proximo->anterior = novo;
    }
    (*lista)->proximo = novo;
    novo->anterior = (*lista);
}

void removerDuplamente(NoDuplo **lista, int valor) {
    if ((*lista)->proximo != NULL) {
        NoDuplo *atual = (*lista)->proximo;
        while (atual != NULL && atual->dado != valor) {
            atual = atual->proximo;
        }
        if (atual != NULL) {
            if (atual->anterior != NULL) {
                atual->anterior->proximo = atual->proximo;
            }
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            }
            free(atual);
        } else {
            printf("Valor nao encontrado na lista\n");
            sleep(1);
        }
    } else {
        printf("Lista ja esta vazia\n");
        sleep(1);
    }
}


NoDuplo* buscarDuplamente(NoDuplo *cabeca, int numero) {
    NoDuplo* atual = cabeca->proximo; 
    while (atual != NULL) {
        if (atual->dado == numero) {
            return atual; 
        }
        atual = atual->proximo;
    }
    return NULL; 
}

//Pilha
void empilhar(No **topo, int valor){
    No *novo = (No *)malloc(sizeof(No));
    novo->dado = valor;

    if(topo != NULL) {
        novo->proximo = *topo;
        *topo = novo;
    }else{
        *topo = novo;
        novo->proximo = NULL;
    }

}

void desempilhar(No **topo){
    if(*topo != NULL) {
        No *aux = *topo;
        *topo = aux->proximo;
        free(aux);
    }else{
        printf("A pilha ja esta vazia\n");
        sleep(1);
    }
}


//Fila
void entrarNaFila(No **Fila, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;
    novo->proximo = NULL;

    if(novo != NULL) {
        if(*Fila == NULL) {
            *Fila = novo;
        } else {
            No *aux = *Fila;
            while(aux->proximo != NULL) {
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }
    } else {
        printf("Erro ao alocar novo No da fila\n");
        sleep(1);
    }
}

void sairDaFila(No **Fila) {
    if (*Fila == NULL) {
        printf("Fila já esta vazia\n");
        sleep(1);
    } else {
        No *aux = *Fila;
        *Fila = aux->proximo;
        free(aux);
    }
}

//Desenhos

//Circular
void desenharCircular(No *cabeca, No *busca) {
    gfx_clear();
    gfx_set_color(255, 255, 255);
    
    if (cabeca == NULL) {
        gfx_text(50, 100, "Lista Vazia");
        gfx_paint();
        return;
    }
    
    int x = 50, y = 100; // Posição de início
    int nodeWidth = 50, nodeHeight = 30; // Tamanho do nó
    int spacing = 20; // Espaçamento entre nós
    int linhaVertical = 50; // Distância para a linha vertical
    No *atual = cabeca;

    // Desenhar a lista circular em linha reta
    do {
        // Desenhar o nó
        if (atual == busca) {
            gfx_set_color(0, 100, 0);
        } else {
            gfx_set_color(255, 255, 255);
        }
        gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
        char valor[10];
        sprintf(valor, "%d", atual->dado);
        gfx_text(x + 15, y + 10, valor);

        // Desenhar a seta para o próximo nó
        gfx_set_color(255, 255, 255);
        int arrowStartX = x + nodeWidth;
        int arrowStartY = y + nodeHeight / 2;
        if (atual->proximo != cabeca) {
            int arrowEndX = arrowStartX + spacing;
            gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
            gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY - 5);
            gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY + 5);
        } else {
            // Desenhar a seta do último nó para o primeiro nó
            int firstNodeX = 50; // Posição x do primeiro nó
            int firstNodeY = 100; // Posição y do primeiro nó
            int arrowEndX = firstNodeX - spacing;
            int arrowEndY = firstNodeY + linhaVertical;

            // Linha vertical para baixo
            gfx_line(arrowStartX, arrowStartY, arrowStartX, arrowEndY);
            // Linha horizontal para a esquerda
            gfx_line(arrowStartX, arrowEndY, arrowEndX, arrowEndY);
            // Linha vertical para cima
            gfx_line(arrowEndX, arrowEndY, arrowEndX, firstNodeY + nodeHeight / 2);
    
            // Linha para direita
            gfx_line(arrowEndX, arrowStartY, firstNodeX, arrowStartY);

            // Desenhar a ponta da seta encostada no primeiro nó
            gfx_line(firstNodeX, firstNodeY + nodeHeight / 2, firstNodeX - 5, firstNodeY + nodeHeight / 2 - 5);
            gfx_line(firstNodeX, firstNodeY + nodeHeight / 2, firstNodeX - 5, firstNodeY + nodeHeight / 2 + 5);


        }

        // Avançar para o próximo nó
        x += nodeWidth + spacing;
        atual = atual->proximo;
    } while (atual != cabeca);

    gfx_paint();
}

//Simplismente Encadeada
void desenharSimples(No *lista, No *Busca){
    gfx_clear();
    gfx_set_color(255,255,255);
    int x = 50, y = 100; //Posição de inicio
    int nodeWidth = 50, nodeHeight = 30; //tamanho NO
    int spacing = 20; //Tamanho Reta

    if (lista == NULL) {
        gfx_text(x, y, "Lista Vazia");
     }else{
        while (lista != NULL) {
            //Desenha o No
            if(lista == Busca){
                gfx_set_color(0,100,0);
            }
            gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
            char valor[10];
            sprintf(valor, "%d", lista->dado);
            gfx_text(x + 15, y + 10, valor);

            //Desenha a seta para o proximo No
            gfx_set_color(255,255,255);
            if (lista->proximo != NULL) {
                int arrowStartX = x + nodeWidth;
                int arrowStartY = y + nodeHeight / 2;
                int arrowEndX = arrowStartX + spacing;
                gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
                gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY - 5);
                gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY + 5);
            }

            //Anda com o desenho
            x += nodeWidth + spacing;
            lista = lista->proximo;
        }
    }

    gfx_paint();
}

//Duplamente Encadeada
void desenharDuplamenteEncadeada(NoDuplo *cabeca, NoDuplo *Busca) {
    gfx_clear();
    gfx_set_color(255,255,255);
    int x = 50, y = 100; // Posição inicial
    int nodeWidth = 50, nodeHeight = 30; // Tamanho do nó
    int spacing = 20; // Espaçamento entre nós

    // Desenha o nó cabeça
    gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
    gfx_text(x + 15, y + 10, "////");

    if (cabeca == NULL || cabeca->proximo == NULL) {
        gfx_text(x + nodeWidth + spacing, y, "Lista Vazia");
    } else {
        NoDuplo *atual = cabeca->proximo; // Começa após o nó cabeça

        // Desenha a seta do nó cabeça para o primeiro nó
        int arrowStartX = x + nodeWidth;
        int arrowStartY = y + nodeHeight / 2;
        int arrowEndX = arrowStartX + spacing;
        gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
        gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY - 5);
        gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY + 5);

        x += nodeWidth + spacing; // Move a posição inicial após o nó cabeça

        while (atual != NULL) {
            // Desenha o nó
            if(atual == Busca){
                gfx_set_color(0,100,0);
            }
            gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
            char valor[10];
            sprintf(valor, "%d", atual->dado);
            gfx_text(x + 15, y + 10, valor);

            // Desenha a seta para o próximo nó
            gfx_set_color(255,255,255);
            if (atual->proximo != NULL) {
                arrowStartX = x + nodeWidth;
                arrowStartY = y + nodeHeight / 2;
                arrowEndX = arrowStartX + spacing;
                gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
                gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY - 5);
                gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY + 5);
            }

            // Desenha a seta para o nó anterior
            if (atual != cabeca) {
                arrowStartX = x;
                arrowStartY = y + nodeHeight / 2;
                int arrowEndX = arrowStartX - spacing;
                gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
                gfx_line(arrowEndX, arrowStartY, arrowEndX + 5, arrowStartY - 5);
                gfx_line(arrowEndX, arrowStartY, arrowEndX + 5, arrowStartY + 5);
            }

            // Anda com o desenho
            x += nodeWidth + spacing;
            atual = atual->proximo;
        }
    }

    gfx_paint();
}

//Fila
void desenharFila(No *Fila) {
    gfx_clear();
    int x = 50, y = 100; //Posição de inicio
    int nodeWidth = 50, nodeHeight = 30; //tamanho NO
    int spacing = 20; //Tamanho Reta

    if (Fila == NULL) {
        gfx_text(x, y, "Fila Vazia");
     }else{
        while (Fila != NULL) {
            //Desenha o No
            gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
            char valor[10];
            sprintf(valor, "%d", Fila->dado);
            gfx_text(x + 15, y + 10, valor);

            //Desenha a seta para o proximo No
            if (Fila->proximo != NULL) {
                int arrowStartX = x + nodeWidth;
                int arrowStartY = y + nodeHeight / 2;
                int arrowEndX = arrowStartX + spacing;
                gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
                gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY - 5);
                gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY + 5);
            }

            //Anda com o desenho
            x += nodeWidth + spacing;
            Fila = Fila->proximo;
        }
    }

    gfx_paint();
}

//Pilha
void desenharPilha(No *topo) {
    gfx_clear();
    int x = 50, y = 50; // Posição inicial
    int nodeWidth = 50, nodeHeight = 30; // Tamanho do nó
    int spacing = 20; // Espaçamento entre nós

     if (topo == NULL) {
        gfx_text(x, y, "Pilha Vazia");
     }else{
        while (topo != NULL) {
            // Desenha o nó
            gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
            char valor[10];
            sprintf(valor, "%d", topo->dado);
            gfx_text(x + 15, y + 10, valor);

            // Desenha a seta para o próximo nó
            if (topo->proximo != NULL) {
                int arrowStartX = x + nodeWidth / 2;
                int arrowStartY = y + nodeHeight;
                int arrowEndY = arrowStartY + spacing;
                gfx_line(arrowStartX, arrowStartY, arrowStartX, arrowEndY);
                gfx_line(arrowStartX, arrowEndY, arrowStartX - 5, arrowEndY - 5);
                gfx_line(arrowStartX, arrowEndY, arrowStartX + 5, arrowEndY - 5);
            }

            // Move o desenho para o próximo nó
            y += nodeHeight + spacing;
            topo = topo->proximo;
        }
    }

    gfx_paint();
}

int main() { 
    No *comecoFila = NULL;
    No *comecoPilha = NULL;
    No *comecoSimples = NULL;
    No *comecoCircular = NULL;

    NoDuplo *cabecaDuploEncadeada = (NoDuplo*) malloc(sizeof(NoDuplo));
    cabecaDuploEncadeada->proximo = NULL;
    cabecaDuploEncadeada->anterior = NULL;

    gfx_init(800, 600, "Visualizador");

    system("clear");
    int menu = 0;
    int menuFila = 0, menuPilha = 0, menuDuplo = 0, menuSimples = 0, menuCircular = 0;
    int x = 0;

    while(menu != -1){
        printf("(1) Fila \n(2) Pilha \n(3) Lista Duplamente C/Cabeca \n(4) Lista Simples S/Cabeca \n(5) Lista Circular \n(-1) Sair\n");
        scanf("%d", &menu);

        switch (menu){
        case (1):
            menuFila = 0;
            while(menuFila != -1){
                system("clear");
                desenharFila(comecoFila);
                printf("(1) Inserir \n(2) Remover \n(-1) Sair\n");
                scanf("%d", &menuFila);

                system("clear");
                if(menuFila == 1){
                
                    printf("Inserir \nQual valor deseja inserir: \n");
                    scanf("%d", &x);
                    entrarNaFila(&comecoFila, x);
                }

                if(menuFila == 2){
                    printf("Removendo\n");
                    sleep(2);
            	    sairDaFila(&comecoFila);
                }   
            }

            break;
        
        case(2):
            menuPilha = 0;
            while(menuPilha != -1){
                system("clear");
                desenharPilha(comecoPilha);
                printf("(1) Inserir \n(2) Remover \n(-1) Sair\n");
                scanf("%d", &menuPilha);

                system("clear");
                if(menuPilha == 1){
                
                    printf("Inserir \nQual valor deseja inserir: \n");
                    scanf("%d", &x);
                    empilhar(&comecoPilha, x);
                }

                if(menuPilha == 2){
                    printf("Removendo\n");
                    sleep(2);
            	    desempilhar(&comecoPilha);
                }   
            }

            break;

        case(3):
            menuDuplo = 0;
            while(menuDuplo != -1){
                system("clear");
                desenharDuplamenteEncadeada(cabecaDuploEncadeada, NULL);
                printf("(1) Inserir \n(2) Remover \n(3) Buscar \n(-1) Sair\n");
                scanf("%d", &menuDuplo);

                system("clear");
                if(menuDuplo == 1){
                
                    printf("Inserir \nQual valor deseja inserir: \n");
                    scanf("%d", &x);
                    inserirDuplamente(&cabecaDuploEncadeada, x);                
                }

                if(menuDuplo == 2){
                    printf("Removendo\n");
                    printf("Qual valor deseja remover? \n");
                    scanf("%d", &x);
            	    removerDuplamente(&cabecaDuploEncadeada, x);
                }   

                if(menuDuplo == 3){
                    printf("Qual valor deseja buscar? \n");
                    scanf("%d", &x);
                    NoDuplo *resultado = buscarDuplamente(cabecaDuploEncadeada, x);
                    if(resultado == NULL){
                        printf("Nao encontrado\n");
                        sleep(1);
                    }
                    desenharDuplamenteEncadeada(cabecaDuploEncadeada, resultado);
                    sleep(1);
                }
            }
            break;

        case(4):
            menuSimples = 0;
            while(menuSimples != -1){
                system("clear");
                desenharSimples(comecoSimples, NULL);
                printf("(1) Inserir \n(2) Remover \n(3) Buscar \n(-1) Sair\n");
                scanf("%d", &menuSimples);

                system("clear");
                if(menuSimples == 1){
                
                    printf("Inserir \nQual valor deseja inserir: \n");
                    scanf("%d", &x);
                    inserirSimples(&comecoSimples, x);                
                }

                if(menuSimples == 2){
                    printf("Removendo\n");
                    printf("Qual valor deseja remover? \n");
                    scanf("%d", &x);
            	    removerSimples(&comecoSimples, x);
                }   

                if(menuSimples == 3){
                    printf("Qual valor deseja buscar? \n");
                    scanf("%d", &x);
                    No *resultadoSimples = buscarSimples(comecoSimples, x);
                    if(resultadoSimples == NULL){
                        printf("Nao encontrado\n");
                        sleep(1);
                    }
                    desenharSimples(comecoSimples, resultadoSimples);
                    sleep(1);
                }
            }
            break;

        case(5):
            menuCircular = 0;
            while(menuCircular != -1){
                system("clear");
                desenharCircular(comecoCircular, NULL);
                printf("(1) Inserir \n(2) Remover \n(3) Buscar \n(-1) Sair\n");
                scanf("%d", &menuCircular);

                system("clear");
                if(menuCircular == 1){
                
                    printf("Qual valor deseja inserir: \n");
                    scanf("%d", &x);
                    inserirCircular(&comecoCircular, x);                
                }

                if(menuCircular == 2){
                    printf("Removendo\n");
                    printf("Qual valor deseja remover: \n");
                    scanf("%d", &x);
            	    removerCircular(&comecoCircular, x);
                }   

                if(menuCircular == 3){
                    printf("Qual valor deseja buscar? \n");
                    scanf("%d", &x);
                    No *resultadoSimples = buscarCircular(comecoCircular, x);
                    if(resultadoSimples == NULL){
                        printf("Nao encontrado\n");
                        sleep(1);
                    }
                    desenharCircular(comecoCircular, resultadoSimples);
                    sleep(1);
                }
            }
            break;


        default:

            break;
        }
    }

    gfx_quit();

    return 0;
}
