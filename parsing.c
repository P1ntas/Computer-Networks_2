#include "parsing.h"

int parse_args(char *url, arguments *arguments){
    char ftp[7]= "ftp://";
    int url_len = strlen(url);
    int i = 0;
    int j = 0;
    int user_flag = FALSE;
    int password_flag = FALSE;
    int host_flag = FALSE;

    while(i < url_len){
    
        if(url[i] == ftp[i] && i>=0 && i<= 5){
            i++;
            user_flag = TRUE;
        }
        else if(i > 5 && url[i] != ":"){
            if(user_flag){
              arguments->user[j] = url[i];
              i++;
              j++;  
            }
            
        }
        else if(url[i] == ":"){
            password_flag = TRUE;
            user_flag = FALSE;
            j = 0;
            i++;
        }
        else if(url[i] != "@"){
            if(password_flag){
                arguments->password[j] = url[i];
                j++;
                i++;  
            }
            
        }
        else if(url[i] == "@"){
            password_flag = FALSE;
            host_flag = TRUE;
            j=0;
            i++;
        }
        else if(url[i] != "/"){
            if(host_flag){
                arguments->host[j] = url[i];
                i++;
                j++;
            }
        }
        else if(url[i] == "/"){
            host_flag = FALSE;
            j = 0;
        }
        else if(url[i] != "\n"){
            arguments->url_path[j] = url[i];
            i++;
            j++;
        }
    }   
    return 0;

}

int get_ip(char *host, arguments *arguments){
    struct hostent *h;

    if ((h = gethostbyname(host)) == NULL) {
        herror("gethostbyname()");
        exit(-1);
    }
    
    strcpy(arguments->host,h->h_name);
    strcpy(arguments->ip,inet_ntoa(*((struct in_addr *) h->h_addr)));

    printf("Host name  : %s\n", h->h_name);
    printf("IP Address : %s\n", inet_ntoa(*((struct in_addr *) h->h_addr)));

    /**
    * The struct hostent (host entry) with its terms documented

    struct hostent {
        char *h_name;    // Official name of the host.
        char **h_aliases;    // A NULL-terminated array of alternate names for the host.
        int h_addrtype;    // The type of address being returned; usually AF_INET.
        int h_length;    // The length of the address in bytes.
        char **h_addr_list;    // A zero-terminated array of network addresses for the host.
        // Host addresses are in Network Byte Order.
    };

    #define h_addr h_addr_list[0]	The first address in h_addr_list.
   */

    return 0;
}

int get_filename(arguments *arguments){

    char path_ws[512];
    strcpy(path_ws,arguments->url_path);

    char slash = "/";
    int path_wsl = strlen(path_ws);
    int i = 0;
    while (i < path_wsl){
        if(path_ws[i] == slash){
            memmove(&path_ws[i], &path_ws[i + 1], strlen(path_ws) - i);
        }
        i++;
    }

    return 0;
}