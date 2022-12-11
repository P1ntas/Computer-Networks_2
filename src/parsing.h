#ifndef __PARSING_H
#define __PARSING_H

#include <stdio.h>
#include <string.h>
#include <netdb.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct arguments{
    char user[256];
    char password[256];
    char host[256];
    char url_path[256];
    char file_name[256];
    char host_name[256];
    char ip[256];
} arguments;

int parse_args(char *url, arguments *arguments);

int get_ip(char *host, arguments *arguments);

int get_filename(arguments *arguments);

#endif