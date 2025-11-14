#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(void) {
    // i want to connect to 127.0.0.1:3490
    struct addrinfo hints, *res; 
    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    int status;
    if ((status = getaddrinfo(NULL, "8080", &hints, &res)) != 0) {
        fprintf(stderr, "Operation: %s", gai_strerror(status));
        exit(1);
    }
    int socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    // não preciso de bind agora
    socklen_t addr_len = res->ai_addrlen;

    connect(socket_fd, (struct sockaddr*)res->ai_addr, addr_len);
    char buffer[INET6_ADDRSTRLEN];
    while(1) {
        recv(socket_fd, buffer, INET6_ADDRSTRLEN, 0);
    }
}