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
#include "printipv4.h"
#define LOCALHOST "127.0.0.1"

int main(void) {
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; // uses TCP

    int status;
    if ((status = getaddrinfo(NULL, "3490", &hints, &res)) != 0) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
        exit(1);
    }memset(&hints, 0, sizeof hints);

    int socket_file_descriptor = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    bind(socket_file_descriptor, res->ai_addr, res->ai_addrlen);
    listen(socket_file_descriptor, 20);

    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int new_fd;
    printIPV4(res);
    char *msg = "Hey, brother!";
    while(1) {
        addr_size = sizeof their_addr;
        new_fd = accept(socket_file_descriptor, (struct sockaddr *)&their_addr, &addr_size);
        int bytes_sent = send(new_fd, msg, strlen(msg), 0);
        printf("%i\n", bytes_sent);
    }
    return 0;
}