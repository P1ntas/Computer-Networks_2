#include "TCP.h"

int connection_to_server(char * ip, int port){
    int sockfd;
    struct sockaddr_in server_addr;
    
    /*server address handling*/
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);    /*32 bit Internet address network byte ordered*/
    server_addr.sin_port = htons(port);        /*server TCP port must be network byte ordered */

    /*open a TCP socket*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(-1);
    }
    /*connect to the server*/
    if (connect(sockfd,(struct sockaddr *) &server_addr,sizeof(server_addr)) < 0) {
        perror("connect()");
        return -1;
    }
    return sockfd;
}
/* writes cmd to the server through socket_fd */
int write_to_server(int sock_fd, char * cmd){
    int bytes_written= 0;
    bytes_written = write(sock_fd, cmd, strlen(cmd));
    if (bytes_written > 0)
        printf("Bytes escritos %d\n", bytes_written);
    else {
        perror("write() command not sent");
        return -1;
    }
    return bytes_written;
}
/* reads reply from server, returns 0 if negative, 1 if positive (return value is boolean) */
int read_reply(int socket_fd, char * buf){
    FILE * socket = fdopen(socket_fd, "r");

    size_t bytes_read = 0;

    do {
        getline(&buf, &bytes_read,socket);
        printf("%s", buf);
    } while (buf[3] != ' ');
   
    return 0;
}
int login(char * user, char * password){
    return 0;
}
int enter_passive_mode(){
    return 0;
}
int retrieve(char * path){
    return 0;
}
int download(char * filename){
    return 0;
}
int end_connection(){
    
    return 0;
}