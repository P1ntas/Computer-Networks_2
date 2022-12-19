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

/**
 * @brief Parses the URL from arguments to the args struct
 * 
 * @param url string received through the arguments of download
 * @param arguments struct where we will save the information
 * @return int Returns 0 if there are no errors or a positive number otherwise
 */
int parse_args(char *url, arguments *arguments);
/**
 * @brief Given a host name returns the ip address
 * 
 * @param host String with the host's name
 * @param arguments struct args in order to put the IP adress
 * @return int Returns 0 if there are no errors or 1 otherwise
 */
int get_ip(char *host, arguments *arguments);
/**
 * @brief Gets the last element of the path, which is the file name
 * 
 * @param arguments arguments struct to get path and fill with the filename
 * @return int Returns 0 if there are no errors
 */
int get_filename(arguments *arguments);

#endif