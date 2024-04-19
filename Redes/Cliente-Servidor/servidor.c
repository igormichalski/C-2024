//servidor
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){

	int meu_socket, sock_cliente;
	struct sockaddr_in addr; //guarda o endereço de entrada do sock
	meu_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(meu_socket == -1){
		printf("Erro ao criar o scoket\n");	
		return(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

	//Parte adicionada para resolver erro da porta não estar liberada ainda
	int opt = 1;
	if (setsockopt(meu_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
    	perror("setsockopt");
    	return 1;
	}


	if(bind(meu_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1){
		printf("Erro na função bind()\n");
		return 1;
	}
 
	if(listen(meu_socket, 1) == -1){
		printf("Erro na função listen()\n");
		return 1;
	}

	printf("Aguardando conexão...\n");

	sock_cliente = accept(meu_socket, 0, 0);

	if(sock_cliente == -1){
		printf("Erro na função accept()\n");
		return 1;
	}
	
	printf("Pedido de conexão feito...\n");

	//Implementa aqui??
	int result = 0, recebidos, num1, num2, sendControl;
    char result_str[256];
	char resposta[256];
	char operador[1];
	bool valido = true, divZero = false;

	
	//Pegando a meensagem que o cliente manda e convertando para um int
	//Num1
	recebidos = recv(sock_cliente, resposta, 256, 0);        
    resposta[recebidos] = '\0';
    printf("Cliente Mandou: %s\n", resposta);
	num1 = atoi(resposta);

	//Operador
	recebidos = recv(sock_cliente, resposta, 256, 0);        
    resposta[recebidos] = '\0';
	printf("Cliente Mandou: %s\n", resposta);
	strcpy(operador , resposta);

	//Num2
	recebidos = recv(sock_cliente, resposta, 256, 0);        
    resposta[recebidos] = '\0';
    printf("Cliente Mandou: %s\n", resposta);
	num2 = atoi(resposta);

	
	//Processamento
	switch (*operador) {
		case '+':
			result = num1 + num2;
			break;
		case '-':
			result = num1 - num2;
			break;
		case '*':
			result = num1 * num2;
			break;
		case '/':
			if (num2 != 0) {
				result = num1 / num2;
			} else {
				divZero = true;
			}
			break;
		case '^':
			result = 1;
			for (int i = 0; i < num2; i++) {
				result *= num1;
			}
			break;
		default:
			valido = 0;
	}


	if(!valido)
		strcpy(result_str, "Operador Invalido\n");
	else
		if(divZero)
			strcpy(result_str, "Não Podemos dividir por Zero\n");
		else
		    //Convertendo o inteiro para string
			snprintf(result_str, sizeof(result_str), "%d", result);
 

	if(send(sock_cliente, result_str, sizeof(result_str), 0) == -1){
		printf("Erro ao enviar dados |função send()|\n");
		return 1;
	}

	close(meu_socket);	//fecha o servidor
	close(sock_cliente); //fecha a conexão com o cliente

	return 0;

}

