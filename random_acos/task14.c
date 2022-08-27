#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <inttypes.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    struct sockaddr_in addr = {
            .sin_family = AF_INET,
            .sin_port = htons(atoi(argv[1])),
            .sin_addr.s_addr = INADDR_ANY
    };

    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd < 0) exit(1);
    int val = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));
    if (bind(lfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) exit(1);
    if (listen(lfd, 5) < 0) exit(1);
    int32_t result = 0;
    int32_t scanned = 1;
    while (scanned)
    {
        int size = sizeof(addr);
        int sfd = accept(lfd, (struct sockaddr *) &addr, (socklen_t *) &size);

        if (sfd < 0) exit(1);
        read(sfd, &scanned, sizeof(scanned));
        close(sfd);
        scanned = ntohl(scanned);
        result += scanned;
    }

    printf("%" PRId32 "\n", result);
    fflush(stdout);

    close(lfd);
    return 0;
}