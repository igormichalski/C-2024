#include "gfx.h"
#include <stdio.h>  /* printf */
#include <unistd.h> /* sleep  */
#include <stdlib.h>
#include <string.h>

//Macro para fornecer valores padrão para aux1 e aux2
//Referencia 1: https://youtu.be/3iX9a_l9W9Y?si=dhelVlUtUGEpTm7Z
//Referencia 2: https://stackoverflow.com/questions/46725369/how-to-get-name-for-each-argument-in-variadic-macros
#define GET_DESENHAR_MACRO(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define DESENHAR(...) GET_DESENHAR_MACRO(__VA_ARGS__, DESENHAR6, DESENHAR5, DESENHAR4)(__VA_ARGS__)

#define DESENHAR4(no, x, y, ajuste) desenhar(no, x, y, ajuste, NULL, NULL)
#define DESENHAR5(no, x, y, ajuste, aux1) desenhar(no, x, y, ajuste, aux1, NULL)
#define DESENHAR6(no, x, y, ajuste, aux1, aux2) desenhar(no, x, y, ajuste, aux1, aux2)

//Todos os codigos de arvore foram retirados do livro e slides da materia disponibilizados.

//No 
struct s_arq_no
{
    int32_t chave:30;
    uint32_t esq:1;
    uint32_t dir:1;
};

typedef struct No{
	int data;
	struct No *esquerda, *direita;
}No;


void desenhar(No *no, float x, float y, float ajuste, No *aux1, No *aux2) {
	char data[4];
	int width;
	int NO_WIDTH = 40; // Largura do retângulo
	int NO_HEIGHT = 20; // Altura do retângulo
    int NO_POSITION_ADJUST = 70; // Ajuste de posição vertical entre os nós

	if(no){
		if(no->esquerda){
			gfx_line(x, y, x - ajuste, y + NO_POSITION_ADJUST);
			DESENHAR(no->esquerda, x - ajuste, y + NO_POSITION_ADJUST, ajuste/2, aux1, aux2);
		}
		if(no->direita){
			gfx_line(x, y, x + ajuste, y + NO_POSITION_ADJUST);
			DESENHAR(no->direita, x + ajuste, y + NO_POSITION_ADJUST, ajuste/2, aux1, aux2);
		}

		sprintf(data, "%d", no->data);
		gfx_set_color(0,0,0);
        
        //Para pintar de verde
        if(aux1 == no){
		    gfx_set_color(0, 100, 0);
        }

        //Para pintar de amarelo
        if(aux2 == no){
		    gfx_set_color(255, 210, 0);
        }

		gfx_filled_rectangle(x - NO_WIDTH/2, y - NO_HEIGHT/2, x + NO_WIDTH/2, y + NO_HEIGHT/2); // Retângulo preenchido
		gfx_set_color(255,255,255);
		gfx_get_text_size(data, &width, 0);
		gfx_rectangle(x - NO_WIDTH/2, y - NO_HEIGHT/2, x + NO_WIDTH/2, y + NO_HEIGHT/2); // Contorno do retângulo
		gfx_text(x-width/2, y-8, data);

		gfx_paint();

    // Caso a árvore seja vazia
	}else{ 
		gfx_clear();
		gfx_paint();
	}
}

//Constroi a arvore do arquivo.
void lerArquivo(FILE *arvore, No **no){
	struct s_arq_no *arq = malloc(sizeof(struct s_arq_no));
	No *auxNo;

	if(fread(arq, sizeof(struct s_arq_no), 1, arvore)){
		(*no)->data = arq->chave;
			
		if(arq->esq){
			No *novoNoEsq = malloc(sizeof(No));
			
			(*no)->esquerda = novoNoEsq;
			auxNo = (*no)->esquerda;
			lerArquivo(arvore, &auxNo);
		}else{
			(*no)->esquerda = NULL;
        }

		if(arq->dir){
			No *novoNoDir = malloc(sizeof(No));
			
			(*no)->direita = novoNoDir;
			auxNo = (*no)->direita;
			lerArquivo(arvore, &auxNo);
		}else{
			(*no)->direita = NULL;
        }
	}
	else{
		*no = NULL;
    }
}

//Função para buscar o no que estamos procurando
void buscarNo(No **no, int x, unsigned *f){

	if(*no == NULL)
		*f = 0;
	else if((*no)->data == x)
		*f = 1;
	else if(x < (*no)->data){
		if((*no)->esquerda == NULL)
			*f = 2;
		else{
			*no = (*no)->esquerda;
			buscarNo(&(*no), x, f);
		}
	}
	else if((*no)->direita == NULL)
		*f = 3;
	else{
		*no = (*no)->direita;
		buscarNo(&(*no), x, f);
	}
}

void inserirNo(No **no, int x, unsigned f){
	No *auxNo = *no;
	
	buscarNo(&auxNo, x, &f);

	if(f == 1)
		printf("Inserção inválida.\n");	
	else{
		No *novoNo = malloc(sizeof(No));
		novoNo->data = x;
		novoNo->esquerda = NULL;
		novoNo->direita = NULL;
	
		if(f == 0)
			*no = novoNo;
		else if(f == 2)
			auxNo->esquerda = novoNo;
		else
			auxNo->direita = novoNo;
	}
}

void buscarPai(No **Pai, No *T, No *u) {
	if(T == u){ //Caso u seja a raiz, não possui pai.
		*Pai = NULL;
		return;
	}
	
	if(T->direita == u || T->esquerda == u){ 
		*Pai = T;
		return;
	}
	else{
		if(T->data < u->data)
			buscarPai(&(*Pai), T->direita, u);
		else
			buscarPai(&(*Pai), T->esquerda, u);
	}
}

void transplante(No **T, No **u, No **v){
	No *PaiU;

	buscarPai(&PaiU, *T, *u);
	
	if(PaiU == NULL)
		*T = *v;
	else if(*u == PaiU->esquerda)
		PaiU->esquerda = *v;
	else
		PaiU->direita = *v;

	if(*v != NULL){
		No *PaiV;
		buscarPai(&PaiV, *T, *v);
		PaiV = PaiU;
	}
}

//Buscar o menor elemento que esta sempre a esquerda
No* menorElemento(No *no){
	if(no){
		if(no->esquerda)
			return menorElemento(no->esquerda);
		else
			return no;
	}
	else
		return NULL;

}

//Buscar o maior elemento que esta sempre a direita
No* maiorElemento(No *no){
	if(no){
		if(no->direita)
			return maiorElemento(no->direita);
		else
			return no;
	}
	else
		return NULL;
}

No* successor(No *no, int x, unsigned f){
	No *auxNo = NULL;

	//Faz a verificação se há sucessor.
	auxNo = maiorElemento(no); 
	if(auxNo->data == x)
		return NULL;

	auxNo = no;
	buscarNo(&auxNo, x, &f);

	if(f != 1) 
		return NULL;

    //Caso em que existe subárvore direita do nó de x.
	if(auxNo->direita){
		auxNo = auxNo->direita;
		while(auxNo->esquerda)
			auxNo = auxNo->esquerda;

		return auxNo;
	}
	else{ //Caso o nó não tenha uma subárvore direita.
		No *successor = NULL;
		No *antecessor = no;

		while(antecessor != auxNo){
			if(auxNo->data < antecessor->data){
				successor = antecessor;
				antecessor = antecessor->esquerda;
			}
			else
				antecessor = antecessor->direita;
		}

		return successor;
	}
}

No* buscarAntecessor(No *no, int x, unsigned f) {
	No *auxNo = NULL;

	//Se o valor for o menor da árvore, não há predecessor.
	auxNo = menorElemento(no);
	if(auxNo->data == x)
		return NULL;
	
	auxNo = no;
	buscarNo(&auxNo, x, &f);

	if(f != 1)
		return NULL;

    //Caso em que possui a subárvore esquerda.
	if(auxNo->esquerda){ 
		auxNo = auxNo->esquerda;

		while(auxNo->direita)
			auxNo = auxNo->direita;
		
		return auxNo;
	}
	else{ //Caso em que não possui a subárvore esquerda.
		No *predeccessor = NULL;
		No *ancestor = no;

		while(ancestor != auxNo){
			if(auxNo->data > ancestor->data){
				predeccessor = ancestor;
				ancestor = ancestor->direita;
			}
			else
				ancestor = ancestor->esquerda;
		}

		return predeccessor;
	}
}

void removerNo(No **no, int x){
	No *auxNo = *no;
	unsigned f;

	buscarNo(&auxNo, x, &f);

	if(f != 1){
		printf("Chave não encontrada!\n");
		return;
	}

	if(auxNo->esquerda == NULL) 
		transplante(&(*no), &auxNo, &(auxNo)->direita);
	else if(auxNo->direita == NULL)
		transplante(&(*no), &auxNo, &(auxNo)->esquerda);
	else{
		No *y, *yFather, *yrFather, *ylFather;
		
		y = successor(*no, x, 1); 
		buscarPai(&yFather, *no, y);
		
		if(yFather != auxNo){
			transplante(&(*no), &y, &(y)->direita);
			y->direita = auxNo->direita;
			buscarPai(&yrFather, *no, y->direita);
			yrFather = y;
		}

		transplante(&(*no), &auxNo, &y);
		y->esquerda = auxNo->esquerda;
		buscarPai(&ylFather, *no, y->esquerda);
		ylFather = y;
	}
}

void salvarArvore(FILE **arvore, No *no) {
	struct s_arq_no arq;

	//Converte do No para s_arq_no
	arq.chave = no->data;

	if(no->esquerda)
		arq.esq = 1;
	else
		arq.esq = 0;

	if(no->direita)
		arq.dir = 1;
	else
		arq.dir = 0;

	fwrite(&arq, sizeof(struct s_arq_no), 1, *arvore);

	if(no->esquerda)
		salvarArvore(&(*arvore), no->esquerda);
	if(no->direita)
		salvarArvore(&(*arvore), no->direita);
}

//da free na arvore
void FreeArvore(No **no) {
	if((*no)->esquerda)
		FreeArvore(&(*no)->esquerda);
	if((*no)->direita)
		FreeArvore(&(*no)->direita);
	
	free(*no);
	*no = NULL;
}

int main(){
    
    int carregar = 0, menu = 0;
    int x = 0;
    unsigned f = 0;
    No *Raiz = NULL, *auxRaiz = NULL;
    No *maior, *menor;
	char nomeArquivo[50];
	FILE *arvore = NULL;

    printf("Quer carregar uma arvore? \n(1)Sim \n(0)Nao\n");
    scanf("%d", &carregar);

    //Para caso ele queira carregar uma arvore de algum arquivo
    if(carregar){
        
		printf("Qual o nome do arquivo? (com .bin)\n"); //validar entrada?
		getchar();
        fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
        nomeArquivo[strcspn(nomeArquivo,"\n")] = '\0';

		arvore = fopen(nomeArquivo, "rb");
        
        if(arvore == NULL){
            printf("Erro ao abrir arquivo ou nome invalido\n");
            exit(1);
        }

        Raiz = malloc(sizeof(No));
        auxRaiz = Raiz;
        lerArquivo(arvore, &auxRaiz);
        if(!auxRaiz)
                Raiz = NULL;
        
        fclose(arvore);
    }
    
    system("clear");
    gfx_init(1200, 900, "RGM 47539");

    do{
        gfx_clear();
        DESENHAR(Raiz, 512, 50, 256);

        printf("(1) Busca por uma chave com valor x \n(2) Insercao de uma chave com valor x \n(3) Remoção de uma chave com valor x \n(4) Busca pela maior e menor chave na arvore \n(5) Busca pelo sucessor e predecessor de uma chave \n(-1)Fechar \n");
        scanf("%d", &menu);

        switch(menu){
            case(1):
                system("clear");
                printf("Qual chave deseja procurar?\n");
                scanf("%d", &x);
                auxRaiz = Raiz;
                buscarNo(&auxRaiz, x, &f);

                switch(f){
					case 0:
						printf("Arvore esta vazia!\n");
						break;
					case 1:
						DESENHAR(Raiz, 512, 50, 256, auxRaiz); //Desenha de verde o elemento na tela se encontrado
						printf("Encontrado!\n");
                        sleep(3);
						break;
					case 2:
						printf("Nao foi encontrado a esquerda.\n");
						break;
					case 3:
						printf("Nao foi encontrado a direita.\n");
						break;
				}
                break;

            case(2):
                system("clear");
                printf("Qual chave deseja inserir?\n");
                scanf("%d", &x);
                inserirNo(&Raiz, x, f);
                break;

            case(3):
                system("clear");
                printf("Qual chave deseja remover?\n");
                scanf("%d", &x);
                removerNo(&Raiz, x);
                break;

            case(4):
                system("clear");
				auxRaiz = Raiz;
				menor = menorElemento(auxRaiz);
				maior = maiorElemento(auxRaiz);

				if(Raiz != NULL){
					DESENHAR(Raiz, 512, 50, 256, maior, menor); //Desenha de verde maior elemento e amarelo menor
					printf("Maior: %d \n Menor: %d\n", maior->data, menor->data);
                    sleep(2);
                }else
					printf("A árvore está vazia!\n");
                break;

            case(5):
                system("clear");
				printf("Qual a chave deseja procurar o sucessor e predecessor?\n");
				scanf("%d", &x);
				auxRaiz = Raiz;

				if(auxRaiz == NULL)
					printf("Árvore vazia!\n");
				else{
					maior = successor(auxRaiz, x, f);
					menor = buscarAntecessor(auxRaiz, x, f);

					if(menor == NULL)
						printf("Erro ao encontrar o predecessor!\n [ ,");
					else
						printf("[%d,", menor->data);
						
					if(maior == NULL)
						printf(" ] \nErro ao encontrar o sucessor!\n");
					else
						printf("%d] \n", maior->data);
					
					DESENHAR(Raiz, 512, 50, 256, maior, menor); //Desenha de verde (sucessor) e amarelo (predecessor)
                    sleep(2);
				}
                break;

            case(-1):
				system("clear");
                printf("Deseja Salvar? \n(1)Sim \n(0)Nao \n");
				scanf("%d", &x);
				if(x){
					printf("Deseja salvar com qual nome? (Com extensao) \n");
					getchar();
        			fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
        			nomeArquivo[strcspn(nomeArquivo,"\n")] = '\0';
					
					arvore = fopen(nomeArquivo, "ab");
					
					//Chama função que salva em arq
					if(Raiz != NULL){
						salvarArvore(&arvore, Raiz);
					}

					fclose(arvore);
					printf("Armazenado com sucesso\n");

				}else{
					printf("Encerrando\n");
				}
                break;

            default:
                printf("valor invalido\n");
        }
    
    }while(menu != -1);

	if(Raiz != NULL){
		FreeArvore(&Raiz);
		//DESENHAR(Raiz, 512, 90, 256);
	}

    gfx_quit();
    return 0;
}
