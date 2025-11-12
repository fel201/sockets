#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
int main() {
    struct sockaddr_in sa;
    struct sockaddr_in6 sa6;
    char ipv4_buffer[INET_ADDRSTRLEN];
    inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr));
    inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr));
    printf("%u\n", htonl(sa.sin_addr.s_addr));
    printf("0X%X\n", sa6.sin6_addr.s6_addr);

    inet_ntop(AF_INET, &(sa.sin_addr), ipv4_buffer, INET_ADDRSTRLEN);
    printf("%s\n", ipv4_buffer);
    return 0;
}
    