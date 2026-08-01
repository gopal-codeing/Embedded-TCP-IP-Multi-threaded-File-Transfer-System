#ifndef SERVER_H
#define SERVER_H

void start_server(void);
int create_server_socket(void);
void accept_client(int server_socket);

#endif
