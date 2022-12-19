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

/**
 * @brief creates control socket (setting socket_fd) and connects to ftp server
 * 
 * @param ip Server IP Adress
 * @param port Server Port
 * @return int Returns 0 if there are no errors or a positive number otherwise
 */
int connection_to_server(char * ip, int port);

/**
 * @brief writes cmd to the server through socket_fd
 * 
 * @param socket_fd File Descriptor of the socket
 * @param comd Command to send
 * @return int Returns 0 if there are no errors or a positive number otherwise
 */
int write_to_server(int socket_fd, char * cmd);

/**
 * @brief Reads reply from server
 * 
 * @param socket_fd File Descriptor of the socket
 * @param buf Buffer writen by the server with the response that is going to be read
 * @return int Returns 0 if there are no errors, 1 otherwise (return value is boolean)
 */
int read_response(int socket_fd, char * buf);

/**
 * @brief Enables the user's login
 * 
 * @param user String containing the user's name
 * @param password String containing the user's password
 * @param socket_fd File Descriptor of the socket
 * @return int Returns 0 if there are no errors, -1 otherwise
 */
int login(char * user, char * password,int socket_fd);

/**
 * @brief Creates the new ip adress and port
 * 
 * @param socket_fd File Descriptor of the socket
 * @param ip Server IP Adress
 * @return int Returns the new port created, -1 otherwise
 */
int enter_passive_mode(int socket_fd,char *ip);

/**
 * @brief Receives the file and after reading it, it returns its size
 * 
 * @param socket_fd File Descriptor of the socket
 * @param command Command to be wrtiten in socket_fd
 * @return int Returns the size of the file, -1 if encounters errors
 */
int retrieve_file(int socket_fd, char *command);

/**
 * @brief Enables the download of the file
 * 
 * @param filename Name of the file
 * @param socketdata File Descriptor of the socket
 * @param socket_fd File Descriptor of the socket
 * @param file_size Size of the file
 * @return int Returns 0 if there are no errors, -1 otherwise
 */
int download(char * filename, int socketdata, int socket_fd, int file_size);

/**
 * @brief Ends connection with the server
 * 
 * @param socket_fd File Descriptor of the socket
 * @param socketdata File Descriptor of the socket
 * @return int Returns 0 if there are no errors, -1 otherwise
 */
int end_connection(int socket_fd,int socketdata);

#endif