/**
 * Example code for getting the IP address from hostname.
 * tidy up includes
 */
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include<arpa/inet.h>

int main(int argc, char *argv[]) {
    

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <address to get IP address>\n", argv[0]);
        exit(-1);
    }



    
    

    return 0;
}
