/**      (C)2000-2021 FEUP
 *       tidy up some includes and parameters
 * */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "parsing.c"
#include <string.h>

#define SERVER_PORT 6000
#define SERVER_ADDR "192.168.28.96"

int main(int argc, char **argv) {

    if (argc != 2) {
        fprintf(stderr, "usage: download ftp://[<user>:<password>@]<host>/<url-path>\n");
        exit(0);
    }

    arguments arguments;
    char urlc[256];
    strcpy(urlc,argv[1]);

    memset(arguments.file_name, 0, 256);
    memset(arguments.host, 0, 256);
    memset(arguments.host_name, 0, 256);
    memset(arguments.ip, 0, 256);
    memset(arguments.password, 0, 256);
    memset(arguments.url_path, 0, 256);
    memset(arguments.user, 0, 256);
    
    if(parse_args(urlc, &arguments) == -1){
        printf("usage: %s ftp://[<user>:<password>]@<host>/<url-path>\n", argv[1]);
        return -1;
    }
    printf("host: %s\nurl path: %s\nuser: %s\npassword: %s\nfile name: %s\nhost name: %s\nip addr: %s\n", arguments.host, arguments.url_path, arguments.user, arguments.password, arguments.file_name, arguments.host_name, arguments.ip);
    
    int sockfd;
    struct sockaddr_in server_addr;
    char buf[] = "Mensagem de teste na travessia da pilha TCP/IP\n";
    size_t bytes;

    /*server address handling*/
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);    /*32 bit Internet address network byte ordered*/
    server_addr.sin_port = htons(SERVER_PORT);        /*server TCP port must be network byte ordered */

    /*open a TCP socket*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(-1);
    }
    /*connect to the server*/
    if (connect(sockfd,
                (struct sockaddr *) &server_addr,
                sizeof(server_addr)) < 0) {
        perror("connect()");
        return -1;
    }
    /*send a string to the server*/
    bytes = write(sockfd, buf, strlen(buf));
    if (bytes > 0)
        printf("Bytes escritos %ld\n", bytes);
    else {
        perror("write()");
        exit(-1);
    }

    if (close(sockfd)<0) {
        perror("close()");
        exit(-1);
    }
    return 0;
}


