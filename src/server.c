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

void start_server(void){  
	
	printf("hello i am staring \n");
    
     int server_socket;

     server_socket = create_server_socket();
         printf("\n socket file discrepter = %d\n", server_socket);
    // accept_client(server_socket); 
     return;
 
}
#if 0
void receive_file(FILE *fp, int clientSocket, long filesize)
{
    char buffer[1024];
    ssize_t bytes;
   long total  = 0;
    while ((bytes = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0)
    {
        fwrite(buffer, 1, bytes, fp);
	total += bytes;
	printf("Progress : %.2f %%\n",(total * 100.0)/filesize);
    }
}
#endif

void receive_file(FILE *fp, int clientSocket, long filesize)
{
    char buffer[1024];
    long total = 0;

    while (total < filesize)
    {
        ssize_t bytes = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytes <= 0)
            break;

        fwrite(buffer, 1, bytes, fp);

        total += bytes;
      	printf("Progress : %.2f %%\n",(total * 100.0)/filesize);

    }
}

void accept_client(int clientSocket){
    //----- server will receive all file------------------
            printf("connected to server");

while(1){

        char filename[100]={0};
   ssize_t len = recv(clientSocket, filename, sizeof(filename) - 1, 0); /// receive file name

if (len <= 0)
{
    printf("Filename receive failed\n");
    close(filename);
    close(clientSocket);
    return;
}

filename[len] = '\0';

        printf("i am receive this filename %s \n", filename);  // print a filename

        char path[200];
        snprintf(path,sizeof(path),"/home/gopal/Project/Embedded-TCP-Chat-Application/received_files/%s",filename); // this is my server path create

        FILE *file = fopen(path,"wb"); //  write data in binary form

        if(file == NULL){
          perror("fopen");
      close(clientSocket);
          exit(1);
        }

       long filesize;
       recv(clientSocket, &filesize, sizeof(filesize), 0); // receive the file size
       printf("File Size : %ld Bytes\n", filesize); // print file size

       receive_file(file,clientSocket, filesize); // recive the data into chunck form 

         fclose(file);  
	}
        close(clientSocket); // close server socket
 
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
        servAddr.sin_addr.s_addr =  htonl(INADDR_ANY); // any cleint can connected to the server
	
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
accept_client(clientSocket);
return 0;
}

int main(void){
	
   printf("=================================\n");
   printf(" Embedded TCP File Transfer \n");
   printf("=================================\n");

    start_server();

    return 0;
}
