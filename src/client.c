#include "common.h"
#include "client.h"
#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void start_client(){
   printf("hello working client mode \n");
   int clientfd = connect_server();
   printf("clinet file discripter = %d", clientfd);
   return;
}

// send file data in chuncks 
void send_file(FILE *fp, int sockfd)
{
    char buffer[BUFFER_SIZE];

    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) 
    {
        if (send(sockfd, buffer, bytesRead, 0) == -1)
        {
            perror("send");
            break;
        }
    }
}
// client said connection
int connect_server(){

  int sockD = socket(AF_INET, SOCK_STREAM, 0);
  if(sockD < 0){
    printf(" Socket discrepter  is not create \n");
    exit(1);
  }

    struct sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(SERVER_PORT); // use some unused port number
    servAddr.sin_addr.s_addr = inet_addr("192.168.6.205");
   
    // connect the client socket to server socket
    int connectStatus = connect(sockD, (struct sockaddr*)&servAddr,sizeof(servAddr));

    if (connectStatus == -1) {
        printf("Error...\n");
    }else{
     printf("Client connection Succfully create \n");
    }

FILE *ptr = fopen("send_files/demo.txt", "rb");  //  mode stands for Read Binary

if (ptr == NULL)
{
    perror("fopen");
    close(sockD);
    return -1;
}
char filename[] = "demo.txt"; // create a file same sending file name 

send(sockD, filename, strlen(filename) + 1, 0); // Fast send a file name
sleep(1);
fseek(ptr, 0, SEEK_END); // Move to the end
long filesize = ftell(ptr); // ftell returns the current byte position

rewind(ptr); //resets the file pointer back to the very beginning of the file. 
printf("\nclient side file size :%ld\n",filesize); 
send(sockD, &filesize, sizeof(filesize), 0); // send a file size

send_file(ptr, sockD); // send a two perameter ptr file pointer and  sockect
  close(sockD);
    return 0;
}

// main function staring point
int main(int argc, char const* argv[])
{
       printf("====================================\n");	
       printf("Hello  i am client mode \n");
       printf("====================================\n");
       start_client();
    return 0;
}
