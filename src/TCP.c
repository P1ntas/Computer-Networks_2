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
    if (!(bytes_written > 0)){
        perror("write() command not sent");
        return -1;
    }
    return bytes_written;
}

/* reads reply from server, returns 0 if negative, 1 if positive (return value is boolean) */
int read_response(int socket_fd, char * buf){
    FILE * socket = fdopen(socket_fd, "r");

    size_t bytes_read = 0;

    do {
        getline(&buf, &bytes_read,socket);
        printf("%s", buf);
    } while ( !('1' <= buf[0] && buf[0] <= '5') || buf[3] != ' ');
    if (buf[3] == ' '){
      int code=0;
      if (code == 550 || code == 530)
      {
        printf("Command error\n");
        return 1;
      }
    }
    return 0;
}

int login(char * user, char * password, int socket_fd){
    char buf[1024];

    char *user_cmd = malloc(5 + strlen(user) + 3);
    user_cmd[0] = '\0';
    strcat(user_cmd, "user ");
    strcat(user_cmd, user);
    strcat(user_cmd, "\r\n");

    char *password_cmd = malloc(5 + strlen(password) + 3);
    password_cmd[0] = '\0';
    strcat(password_cmd, "pass ");
    strcat(password_cmd, password);
    strcat(password_cmd, "\r\n");


    if (write_to_server(socket_fd, user_cmd) < 0) {
        printf("Error writing USER command\n");
        return -1;
    }
    if (read_response(socket_fd, buf)) {
        printf("Error reading reply to USER command\n");
        return -1;
    }

    if (write_to_server(socket_fd, password_cmd) < 0) {
        printf("Error writing PASS command\n");
        return -1;
    }

    if (read_response(socket_fd, buf)) {
        printf("Error reading reply to PASS command\n");
        return -1;
    }
    return 0;
}
int enter_passive_mode(int socket_fd, char *ip){

    char buff[1024];
    if (write_to_server(socket_fd, "PASV\r\n") < 0) {
        printf("Error writing PASV\n");
        return -1;
    }

    read(socket_fd, buff, 1024);
    
    //parse resposta
    strtok(buff, "(");

    char* ip1 = strtok(NULL, ",");   
    char* ip2 = strtok(NULL, ",");       
    char* ip3 = strtok(NULL, ",");     
    char* ip4 = strtok(NULL, ",");       
    
    char* new_ip = malloc(256);
    new_ip[0] = '\0';
    strcat(new_ip, ip1);
    strcat(new_ip, ".");
    strcat(new_ip, ip2);
    strcat(new_ip, ".");
    strcat(new_ip, ip3);
    strcat(new_ip, ".");
    strcat(new_ip, ip4);
    
    char* p1 = strtok(NULL, ",");       
    char* p2 = strtok(NULL, ")");   

    for (size_t i = 0; i < strlen(new_ip); i++)
    {
        ip[i] = new_ip[i];
    }
       
    int new_port = atoi(p1)*256 + atoi(p2);

    return new_port;
    
    return -1;
}

int retrieve_file(int socket_fd, char *command){
    int size;
    char buffer[1024]= {0};

    if((size = write(socket_fd, command, strlen(command))) <= 0){
        printf("Error: command not sent\n");
        return -1;
    }

    read(socket_fd, buffer, 1024);

    printf("%s\n", buffer);

    strtok(buffer, "(");

    char* size_string = strtok(NULL, "bytes");          

    return atoi(size_string); 

    return -1;
  
}

int download(char * filename, int socketdata, int socket_fd, int file_size){
    int file_fd;

    if ((file_fd = open(filename, O_WRONLY | O_CREAT, 0777)) < 0) {
        fprintf(stderr, "Error opening data file!\n");
        return -1;
    }

    char buff[10024] = {0};
    int numBytesRead=0;

    while((numBytesRead = read(socketdata, buff, 10024)) > 0) {
        file_size -= numBytesRead;
        printf("saving... %d bytes left\n", file_size);
        if (write(file_fd, buff, numBytesRead) < 0) {
            fprintf(stderr, "Error writing data to file!\n");
            return -1;
        }
    }
    if(read_response(socket_fd, buff)) {
		printf("Error reading reply\n");
		return -1;
	}
    if (close(file_fd) < 0) {
        fprintf(stderr, "Error closing file!\n");
        return -1;
    }

    return 0;
}

int end_connection(int socket_fd, int socketdata){
    char buffer[1024];
    char quit_cmd[] = "quit\r\n";

    if(write_to_server(socket_fd, quit_cmd) < 0) {
		printf("Error writing QUIT command to server\n");
		return -1;
	}

	if(read_response(socket_fd, buffer)) {
		printf("Error reading reply to QUIT command\n");
		return -1;
	}

	if(close(socket_fd) < 0 || close(socketdata) < 0){
		printf("Error closing sockets\n");
		return -1;
	}

    return 0;
}