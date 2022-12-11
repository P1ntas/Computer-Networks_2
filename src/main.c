#include "TCP.h"
#include "parsing.h"

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Wrong number of arguments.\n");
        return -1;
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
    
    //int sockfd;
    
    //char buf[] = "Mensagem de teste na travessia da pilha TCP/IP\n";
    //size_t bytes;

    TCP tcp;
    // setting socket control to connect with ftp
    tcp.socket_control = connection_to_server(arguments.ip, 21);
    if (tcp.socket_control < 0){
        return -1;
    }

    char buff[1024];
    if(read_reply(tcp.socket_control, buff)) {
    printf("Error reading from socket\n");
    return -1;
  }

    return 0;
}


