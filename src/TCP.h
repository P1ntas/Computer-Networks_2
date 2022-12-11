#ifndef __TCP_H
#define __TCP_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>

typedef struct TCP {
    int socket_control;
    int socket_data;
    char new_ip[1024];
    char new_port;
} TCP;

/* creates control socket (setting socket_fd) and connects to ftp server */
int connection_to_server(char * ip, int port);
/* writes cmd to the server through socket_fd */
int write_to_server(int socket_fd, char * cmd);
/* reads reply from server*/
int read_reply(int socket_fd, char * buf);
int login(char * user, char * password);
int enter_passive_mode();
int retrieve(char * path);
int download(char * filename);
int end_connection();

#endif