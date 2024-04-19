//cliente
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

int main(){

    int meu_socket;
    struct sockaddr_in addr;
    meu_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(meu_socket == -1){
        printf("Erro ao criar Scoket\n");
        return 1;
    }
    addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

    printf("Tentando se conectar ao servidor...\n");

    if(connect(meu_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        printf("Erro ao conectar\n");
        return 1;
    }

    printf("Conectado!!\n");

    int recebidos = 1, enviados = 1;
    char mensagem[256];
    char resposta[256];

  //  do{
        //O processo inverso é feito aqui, como o servidor espera uma mensagem inicialmente o cliente deveria fornecela 
        //O cliente deveria fornece-la
        printf("Cliente (Num1): ");
        fgets(mensagem, 256, stdin);
        enviados = send(meu_socket, mensagem, strlen(mensagem), 0);

        fflush(stdin);

        printf("Cliente (Operador): ");
        fgets(mensagem, 256, stdin);
        enviados = send(meu_socket, mensagem, strlen(mensagem), 0);

        fflush(stdin);

        printf("Cliente (Num2): ");
        fgets(mensagem, 256, stdin);
        enviados = send(meu_socket, mensagem, strlen(mensagem), 0);

        //Apos enviar a mensagem espera-se a resposta do servidor
        recebidos =recv(meu_socket, resposta, 256, 0);
        resposta[recebidos] = '\0';
        printf("Servidor: %s\n", resposta);
//    }while(recebidos != -1 && enviados != -1);
    
    //Porque precisa desses 2 send para ele não bugar o bind na proxima execução
   // enviados = send(meu_socket, mensagem, strlen(mensagem), 0);
   // enviados = send(meu_socket, mensagem, strlen(mensagem), 0);


    close(meu_socket);
    
    return 0;
}