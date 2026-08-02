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
    return;
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
    servAddr.sin_addr.s_addr = inet_addr("10.229.123.109");

    int connectStatus = connect(sockD, (struct sockaddr*)&servAddr,sizeof(servAddr));

    if (connectStatus == -1) {
        printf("Error...\n");
    }
  
     printf("Client connection Succfully create \n");



//---------- this code is send folder to subfile-------------
DIR *dir = opendir("send_files");//  function is used to open a directory stream so you can read its files and sub-directories. 

if(dir == NULL){   // check folder is Empty
 perror("opendir");
 return;
}

struct dirent *entry;  // create structer  represents a single directory entry

while((entry = readdir(dir)) != NULL){  // read folder to sub files
  if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0){
    continue;
}
char filepath[512];

snprintf(filepath, sizeof(filepath),"send_files/%s", entry->d_name); // createa file path with name
printf("Opening : %s\n", filepath); // print file path
				    
char filename[200];
strcpy(filename, entry->d_name);  // copy file name 
send(sockD, filename , strlen(filename) + 1, 0); // send a file name

FILE *fp = fopen(filepath, "rb");  // oper file for binary data read form

if(fp == NULL){  
  perror("fopen");
  continue;
}

sleep(1); // wait for 1 second

fseek(fp, 0, SEEK_END); // Move to the end
long filesize = ftell(fp); // ftell returns the current byte position
rewind(fp);//resets the file pointer back to the very beginning of the file. 

printf("\nclient side file size :%ld\n",filesize); // print file size
send(sockD, &filesize, sizeof(filesize), 0);  // send file size to server 
send_file(fp, sockD); 

fclose(fp); // close file 

  printf("%s\n", entry->d_name); // print file name
}

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
