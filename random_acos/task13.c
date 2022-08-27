#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

enum { MAX_SIZE = 1000 };

int main(int argc, char * argv[])
{
    char host[MAX_SIZE];
    char service[MAX_SIZE];

    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *result;

    struct sockaddr_in *ipv4;
    struct sockaddr_in *ipv4_min = NULL;
    int s = 0;
    struct addrinfo *it = NULL;
    while (scanf("%s %s", host, service) == 2)
    {
        s = getaddrinfo(host, service, &hints, &result);
        if (s != 0)
        {
            printf("%s\n", gai_strerror(s));
            exit(EXIT_FAILURE);
            continue;
        }

        it = result;
        while(it != NULL) 
        {
            ipv4 = (struct sockaddr_in *)it->ai_addr;
            if (ipv4_min == NULL) ipv4_min = ipv4;

            if (ntohl(ipv4_min->sin_addr.s_addr) > ntohl(ipv4->sin_addr.s_addr)) 
                ipv4_min = ipv4;
            it = it->ai_next;
        }

        printf("%s:%d\n", inet_ntoa(ipv4_min->sin_addr), ntohs(ipv4_min->sin_port));
        freeaddrinfo(result);
        ipv4_min = NULL;
    }
    return 0;
}