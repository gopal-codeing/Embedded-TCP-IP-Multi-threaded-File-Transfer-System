#include "common.h"
#include "client.h"
#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <string.h>

void start_client(){
   printf("hello working client mode \n");
   int clientfd = connect_server();
   printf("clinet file discripter = %d", clientfd);
}

int connect_server(){

  int sockD = socket(AF_INET, SOCK_STREAM, 0);
  if(sockD < 0){
    printf(" Socket discrepter  is not create \n");
    exit(1);
  }

    struct sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(SERVER_PORT); // use some unused port number
    servAddr.sin_addr.s_addr = inet_addr("192.168.68.107");

    int connectStatus = connect(sockD, (struct sockaddr*)&servAddr,sizeof(servAddr));

    if (connectStatus == -1) {
        printf("Error...\n");
    }
  
     printf("Client connection Succfully create \n");
    
       char str[200]={0};
     while (1)
{
    printf("Client : ");
    fgets(str, sizeof(str), stdin);
     
    if(strncmp(str,"exit",4) == 0) {
        printf("Server disconnected\n");
        break;
    }
    send(sockD, str, strlen(str), 0);
    memset(str, 0, sizeof(str));
    ssize_t len = recv(sockD, str, sizeof(str)-1, 0);
   
   /* if(strcmp(str,"exit") == 0) {
        printf("Server disconnected\n");
        break;
    }*/
    str[len] = '\0';

    printf("Server : %s", str);
}
  close(sockD);
    return 0;
}


int main(int argc, char const* argv[])
{
       printf("====================================\n");	
       printf("Hello  i am client mode \n");
       printf("====================================\n");
       start_client();
    return 0;
}
