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
    return;
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
    servAddr.sin_addr.s_addr = inet_addr("10.229.123.109");

    int connectStatus = connect(sockD, (struct sockaddr*)&servAddr,sizeof(servAddr));

    if (connectStatus == -1) {
        printf("Error...\n");
    }
  
     printf("Client connection Succfully create \n");


//---------- this code is send folder to subfile-------------
DIR *dir = opendir("send_files");
if(dir == NULL){
 perror("opendir");
 return 0;
}

struct dirent *entry;

while((entry = readdir(dir)) != NULL){
if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0){
    continue;
}  
char filepath[512];

snprintf(filepath, sizeof(filepath),"send_files/%s", entry->d_name);
printf("Opening : %s\n", filepath);
char filename[200];
strcpy(filename, entry->d_name);
send(sockD, filename , strlen(filename) + 1, 0);

FILE *fp = fopen(filepath, "rb");

if(fp == NULL){
  perror("fopen");
  continue;
}

sleep(1);
fseek(fp, 0, SEEK_END);
long filesize = ftell(fp);
rewind(fp);

printf("\nclient side file size :%ld\n",filesize);
send(sockD, &filesize, sizeof(filesize), 0);
send_file(fp, sockD);
fclose(fp);

  printf("%s\n", entry->d_name);
}

//send_file(ptr, sockD);
  closedir(dir);
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
