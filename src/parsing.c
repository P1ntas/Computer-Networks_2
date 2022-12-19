#include "parsing.h"

int parse_args(char *url, arguments *arguments){
    char ftp[7]= "ftp://";
    int url_len = strlen(url);
    int i = 0;
    int j = 0;
    int user_flag = FALSE;
    int password_flag = FALSE;
    int host_flag = FALSE;
    int path_flag = FALSE;

    while(i < url_len){
        if(url[i] == ftp[i] && i>=0 && i<= 5){
            i++;
            user_flag = TRUE;
        }
        else if(i > 5 && url[i] != ':' && url[i] != '@' && url[i] != '/'){
            if(user_flag){
              arguments->user[j] = url[i];
              i++;
              j++;  
            } else if(password_flag){
                arguments->password[j] = url[i];
                j++;
                i++;  
            } else if(host_flag){
                arguments->host[j] = url[i];
                i++;
                j++;
            } else if (path_flag) {
                arguments->url_path[j] = url[i];
                i++;
                j++;
            }
            
        }
        else if(url[i] == ':'){
            password_flag = TRUE;
            user_flag = FALSE;
            j = 0;
            i++;
        }
        else if(url[i] == '@'){
            password_flag = FALSE;
            host_flag = TRUE;
            j=0;
            i++;
        }
        else if(url[i] == '/'){
            if (user_flag) {
                //it means that the user was not specified
                for (int k = 0; k < j; k++) {
                    arguments->host[k] = arguments->user[k];
                }
                host_flag = FALSE;
                user_flag = FALSE;
                path_flag = TRUE;
                j=0;
                i++;
                char def_user[] = "anonymous";
                char def_password[] = "pass";
                for (int k = 0; k < 10; k++) {
                    arguments->user[k] = def_user[k];
                }
                for (int k = 0; k < 5; k++) {
                    arguments->password[k] = def_password[k];
                }
            } else if (host_flag) {
                host_flag = FALSE;
                j = 0;
                i++;
                path_flag = TRUE;
            } else
            {
                arguments->url_path[j] = url[i];
                i++;
                j++;
            }
            
        }
        else {
            break;
        }
    }   
    if(get_ip(arguments->host, arguments) != 0){
        printf("getIp() failed\n");
        return -1;
    }

    if(get_filename(arguments) != 0){
        printf("Error getFileName()\n");
        return -1;
    }

    return 0;

}

int get_ip(char *host, arguments *arguments){
    struct hostent *h;

    if ((h = gethostbyname(host)) == NULL) {
        herror("gethostbyname()");
        exit(-1);
    }
    
    strcpy(arguments->host_name,h->h_name);
    strcpy(arguments->ip,inet_ntoa(*((struct in_addr *) h->h_addr)));

    return 0;
}

int get_filename(arguments *arguments){

    char path_cpy[256];
  
    strcpy(path_cpy,arguments->url_path);

    int k = 0;
    for(int i = strlen(path_cpy)-1; i>=0; i--){
        if(path_cpy[i] == '/'){
            for(int j = i+1; j < strlen(path_cpy)-1; j++){
                strcpy(&arguments->file_name[k],&path_cpy[j]);
                k++;
            }
            break;
        }
    }

    return 0;
}