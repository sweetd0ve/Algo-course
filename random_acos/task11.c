#include <inttypes.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    struct addrinfo hints;
    struct addrinfo *result;
    int sfd, s;

    if (argc != 3)
    {
        fprintf(stderr, "Too few parametrs\n");
        exit(1);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = PF_INET;
    hints.ai_socktype = SOCK_STREAM;

    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(1);
    }
    if ((sfd = socket(result->ai_family, result->ai_socktype, 0)) < 0)
    {
        perror("soket");
        freeaddrinfo(result);
        exit(1);
    }
    if (connect(sfd, result->ai_addr, result->ai_addrlen) < 0) {
        freeaddrinfo(result);
        exit(1);
    }
    int sfd2 = dup(sfd);
    FILE * in = fdopen(sfd, "r");
    FILE * out = fdopen(sfd2, "w");
    if (fprintf(out, "%s\n", argv[3]) == -1)
    {
        freeaddrinfo(result);
        exit(1);
    }
    fflush(out);

    int k;
    if (fscanf(in, "%d", &k) == -1)
    {
        freeaddrinfo(result);
        exit(1);
    }
    for (int i = 0; i <= k; ++i)
    {
        if (fprintf(out, "%d\n", i) == -1)
        {
            freeaddrinfo(result);
            exit(1);
        }
        fflush(out);
    }
    uint64_t answer = 0;
    if (fscanf(in, "%" SCNu64, &answer) == -1)
    {
        freeaddrinfo(result);
        _exit(0);
    }
    printf("%" SCNu64 "\n", answer);
    fflush(stdout);

    fclose(in);
    fclose(out);
    freeaddrinfo(result);
    return 0;
}