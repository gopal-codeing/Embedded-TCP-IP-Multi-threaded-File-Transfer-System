#include "common.h"
#include "server.h"
#include <stdio.h>
#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>

void start_server(void){  
	
	printf("hello i am staring \n");
    
     int server_socket;

     server_socket = create_server_socket();
         printf("\n socket file discrepter = %d\n", server_socket);
    // accept_client(server_socket); 
     return;
 
}

void receive_file(FILE *fp, int clientSocket,  long filesize)
{
    char buffer[1024];
    long long total = 0;

    while (total < filesize)
    {
        size_t remain = filesize - total;

        size_t chunk = remain > sizeof(buffer) ? sizeof(buffer) :remain;

        ssize_t bytes = recv(clientSocket, buffer, chunk, 0);

        if (bytes <= 0)
            break;

        fwrite(buffer, 1, bytes, fp);
        total += bytes;
        printf("\rDownloading : %.2f%%",(total * 100.0) / filesize);
        fflush(stdout);
    }
}

void accept_client(int clientSocket){
    //----- server will recevice all file------------------
            printf("\nconnected to server\n");

while(1){

   char filename[100]={0};
   ssize_t len = recv(clientSocket, filename, sizeof(filename) - 1, 0);
 
if (len <= 0){
    printf("\n All file are Downloads...\n");
   // fclose(filename);
    close(clientSocket);
    break;
}

filename[len] = '\0';
printf("\ni am receve this filename %s \n", filename);


        char path[200];
        snprintf(path,sizeof(path),"/home/gopal/Project/Embedded-TCP-Chat-Application/received_files/%s",filename);

        FILE *file = fopen(path,"wb");

        if(file == NULL){
          perror("fopen");
          close(clientSocket);
          exit(1);
        }

       long filesize;
       recv(clientSocket, &filesize, sizeof(filesize), 0);
       printf("File Size : %ld Bytes\n", filesize);
       receive_file(file,clientSocket, filesize); // recive the data into chunck form 

        fclose(file);
	}
        close(clientSocket);
 
return;
}

void *client_handler(void *arg)
{
    int clientSocket = *(int *)arg;

    free(arg);

    printf("Client Connected : %d\n", clientSocket);

    accept_client(clientSocket);  

    close(clientSocket);

    return NULL;
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
	//servAddr.sin_addr.s_addr = inet_addr("192.168.6.88");
	servAddr.sin_addr.s_addr = INADDR_ANY;

	// bind socket to the specified IP and port
	if(bind(servSockD, (struct sockaddr*)&servAddr,sizeof(servAddr)) < 0){
		exit(1);
	}
	printf("Bind creation successfully...!\n");

	// listen for connections
	if(listen(servSockD, 10) < 0){
		exit(1);
	}

	printf("listen creation successfully...!\n");
	printf("Family   : %d\n", servAddr.sin_family);
	printf("Port     : %d\n", ntohs(servAddr.sin_port));
	printf("Address  : %u\n", servAddr.sin_addr.s_addr);

while(1){
      
       	int *clientSocket = malloc(sizeof(int));
	*clientSocket = accept(servSockD, NULL, NULL);
        if(*clientSocket < 0){
                printf("client Socket not accepted");
                exit(1);
        }
    pthread_t thread_id;
      if (pthread_create(&thread_id, NULL,client_handler,clientSocket) != 0)
    {
        perror("pthread_create");

        close(*clientSocket);

        free(clientSocket);

        continue;
    }


}
return 0;
}

int main(void){
	
   printf("=================================\n");
   printf(" Embedded TCP File Transfer \n");
   printf("=================================\n");

    start_server();

    return 0;
}
