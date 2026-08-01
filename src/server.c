#include "common.h"
#include "server.h"
#include <stdio.h>
#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <string.h>

void start_server(void){  
	
	printf("hello i am staring \n");
    
     int server_socket;

     server_socket = create_server_socket();
         printf("\n socket file discrepter = %d\n", server_socket);
    // accept_client(server_socket); 
     return;
 
}

int create_server_socket(){

	printf("\ncreate a server socket");
	int servSockD = socket(AF_INET, SOCK_STREAM, 0);

	// define server address
	struct sockaddr_in servAddr;
	printf("socket creation successfully...!\n");
	if(servSockD < 0) exit(1);

	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(SERVER_PORT);
	servAddr.sin_addr.s_addr =  htonl(INADDR_ANY); 

	//servAddr.sin_addr.s_addr = inet_addr("10.231.188.109");

	// bind socket to the specified IP and port
	if(bind(servSockD, (struct sockaddr*)&servAddr,
				sizeof(servAddr)) < 0){
		exit(1);
	}
	printf("Bind creation successfully...!\n");

	// listen for connections
	if(listen(servSockD, 1) < 0){
		exit(1);
	}

	printf("listen creation successfully...!\n");
	printf("Family   : %d\n", servAddr.sin_family);
	printf("Port     : %d\n", ntohs(servAddr.sin_port));
	printf("Address  : %u\n", servAddr.sin_addr.s_addr);

	// integer to hold client socket.

	int clientSocket = accept(servSockD, NULL, NULL);
	if(clientSocket < 0){
		printf("client clientSocket not accepted");
		exit(1);
	}

	printf("connected to server");
	char str[200]={0};

	while (1){
        memset(str, 0, sizeof(str));

    ssize_t len = recv(clientSocket, str, sizeof(str)-1, 0);
    str[len] = '\0';
    printf("Client : %s", str);
    fgets(str, sizeof(str), stdin);
    send(clientSocket, str, strlen(str), 0);
}
      
        close(servSockD);

	return servSockD;
}

int main(void){
	
   printf("=================================\n");
   printf(" Embedded TCP File Transfer \n");
   printf("=================================\n");

    start_server();

    return 0;
}
