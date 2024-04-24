#include "gfx.h"
#include <stdio.h>  /* printf */
#include <unistd.h> /* sleep  */
#include <math.h> //Makefile alterado para poder rodar a biblioteca, "-lm" adicionado

#define TAM 600
#define LadoQuadrado TAM/3

// void quadrado()
// {

// 	//Principal
// 	gfx_rectangle(400, 800, 800, 400);

// 	//Cima
// 	gfx_rectangle(500, 400, 700, 200);

// 	//Baixo
// 	gfx_rectangle(500, 1000, 700, 800);

// 	//Direita
// 	gfx_rectangle(800, 700, 1000, 500);

// 	//Esquerda
// 	gfx_rectangle(200, 700, 400, 500);

// }

void showQuadrado(int x1, int y1, int x2, int y2){
	//Para tapar os quadrados internos ("invisiveis") Preto
	gfx_set_color(0, 0, 0);
	gfx_filled_rectangle(x1+1, y1+1, x2-1, y2-1); 

	//Para gerar os quadrados externos ("visiveis") Branco
	gfx_set_color(255, 255, 255);
	gfx_rectangle(x1, y1, x2, y2);
}

void quadradosExtras(float x1, float y1, float x2, float y2, int recursao, float tela){

	if(recursao){
		quadradosExtras(x1 + tela/4, y1 - tela/2, x2- tela/4, y2-tela, recursao - 1, tela/2); //cima
		quadradosExtras(x1+ tela/4, y1 + tela, x2 - tela/4, y2 + tela/2, recursao - 1, tela/2); //baixo
		quadradosExtras(x1 - tela/2, y1 + tela/4, x2- tela, y2- tela/4, recursao - 1, tela/2); //esquerda
		quadradosExtras(x1+tela, y1+tela/4, x2+tela/2, y2-tela/4, recursao - 1, tela/2); //direita	
	}
	
	showQuadrado(x1,y1,x2,y2);
}

void showCirculo(int x, int y, int raio){
	gfx_set_color(255, 255, 255);
	gfx_ellipse(x, y, raio, raio); 

}

void  circulosExtras(int x, int y, int recursao, int raio){
	if (recursao)
	{
		circulosExtras(x + ((raio/2)*(sqrt(2)/2)), y - ((raio/2)*(sqrt(2)/2)), recursao - 1 ,raio/2); //SD
		circulosExtras(x - ((raio/2)*(sqrt(2)/2)), y - ((raio/2)*(sqrt(2)/2)), recursao - 1 ,raio/2); //SE

		circulosExtras(x + ((raio/2)*(sqrt(2)/2)), y + ((raio/2)*(sqrt(2)/2)), recursao - 1 ,raio/2); //ID
		circulosExtras(x - ((raio/2)*(sqrt(2)/2)), y + ((raio/2)*(sqrt(2)/2)), recursao - 1 ,raio/2); //IE
	}
	showCirculo(x, y, raio);
}

int main()
{	
	
	int menu=0;
	
	printf("Inicializando...\n");

	while(menu!=-1){
		int recursao;
		
		system("clear");
		printf("Menu Principal\n (1)Quadrado\n (2)Circulo\n (-1)Sair\n");
		scanf("%d", &menu);

		switch (menu)
		{
		case (1):
			system("clear");
			printf("Digite o nivel: \n");
			scanf("%d", &recursao);

			gfx_init(TAM, TAM, "Igor Roberto - RGM 47539");
			quadradosExtras(LadoQuadrado, LadoQuadrado, 2*LadoQuadrado, 2*LadoQuadrado, recursao, LadoQuadrado);
			gfx_paint();
			sleep(6);
			gfx_quit();
			break;
		
		case(2):
			system("clear");
			printf("Digite o nivel: \n");
			scanf("%d", &recursao);

			gfx_init(TAM, TAM, "Igor Roberto - RGM 47539");
			circulosExtras(TAM/2, TAM/2, recursao, 512/2);
			gfx_paint();
			sleep(6);
			gfx_quit();
			break;

		default:
			break;
		}

	}

	return 0;
} 
 

// gfx_set_color(255, 0, 0);
// 	gfx_rectangle(50, 50, 300, 150);
// 	gfx_set_color(0, 0, 255);
// 	gfx_filled_ellipse(60, 60, 50, 40);
// 	gfx_set_color(0, 255, 0);
// 	gfx_text(80, 80, "Texto");    
	
// 	gfx_paint();

// 	sleep(5);
