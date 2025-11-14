#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "printipv4.h"
#include <errno.h>

int main(void) {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }

    // i want to connect to 127.0.0.1:3490
    struct addrinfo hints, *res; 
    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    int status;
    if ((status = getaddrinfo(NULL, "3490", &hints, &res)) != 0) {
        fprintf(stderr, "Operation: %s", gai_strerror(status));
        exit(1);
    }
    int socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    socklen_t addr_len = res->ai_addrlen;
    struct sockaddr_in *ai_addr = (struct sockaddr_in*)res->ai_addr;
    printf("%i", ai_addr->sin_port);
    connect(socket_fd, res->ai_addr, addr_len);
    char buffer[INET6_ADDRSTRLEN];
    printIPV4(res);
    int bytes_read;
    while(1) {
        bytes_read = recv(socket_fd, buffer, INET6_ADDRSTRLEN, 0);
        if (bytes_read == -1) {
            perror("An error has occured");
        }
        printf("%i\n", bytes_read);
        for (int i = 0; i < strlen(buffer); i++) {
            printf("%c", buffer[i]);
        }
        printf("\n");
    }
    if (LOBYTE(wsaData.wVersion) != 2 ||
        HIBYTE(wsaData.wVersion) != 2)
    {
        fprintf(stderr,"Version 2.2 of Winsock not available.\n");
        WSACleanup();
        exit(2);
    }
}