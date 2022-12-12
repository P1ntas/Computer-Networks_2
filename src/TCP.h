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
    int new_port;
} TCP;

/* creates control socket (setting socket_fd) and connects to ftp server */
int connection_to_server(char * ip, int port);
/* writes cmd to the server through socket_fd */
int write_to_server(int socket_fd, char * cmd);
/* reads reply from server*/
int read_response(int socket_fd, char * buf);
int login(char * user, char * password,int socket_fd);
int enter_passive_mode(int socket_fd,char *ip);
int send_command(int socket_fd, char *command);
int retrieve_file(int socket_fd, char *command);
int download(char * filename, int socketdata, int socket_fd, int file_size);
int end_connection(int socket_fd,int socketdata);

#endif