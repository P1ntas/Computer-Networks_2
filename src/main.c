#include "TCP.h"
#include "parsing.h"

/**
 * @brief Main function that executes the download
 * 
 * @param argc number of arguments
 * @param argv value of the arguments
 * @return int return value
 */
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
   
    TCP tcp;
   
    tcp.socket_control = connection_to_server(arguments.ip, 21);
    if (tcp.socket_control < 0){
        return -1;
    }

    char buff[1024];
    if(read_response(tcp.socket_control, buff)) {
        printf("Error reading from socket\n");
        return -1;
    }

    // login
    if(login(arguments.user, arguments.password, tcp.socket_control) < 0) {
        return -1;
    }

    char ip[256] = {0};
    int port = -1;

    // go into passive mode
    port = enter_passive_mode(tcp.socket_control, ip);

    if(port == -1) {
        return -1;
    }

    strcpy(tcp.new_ip,ip);
    tcp.new_port = port;

    tcp.socket_data = connection_to_server(tcp.new_ip, tcp.new_port);
    if (tcp.socket_data < 0) {
  		printf("Error connecting to the server\n");
  		return -1;
    }

    char* retr_command = malloc(5 + strlen(arguments.url_path) + 3);
    retr_command[0] = '\0';

    strcat(retr_command, "retr ");
    strcat(retr_command, arguments.url_path);
    strcat(retr_command, "\r\n");

    int file_size = retrieve_file(tcp.socket_control, retr_command);

    if (file_size < 0) {
        return -1;
    }

    // download file in the other end
    if(download(arguments.file_name, tcp.socket_data, tcp.socket_control, file_size) < 0) {
        return -1;
    }

    // disconnect sockets
    if(end_connection(tcp.socket_control,tcp.socket_data) < 0) {
        return -1;
    }

    return 0;
}
