#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <inttypes.h>

int main()
{
    int32_t k = 0;
    pid_t proc1, proc2;
    int pipe_[2];
    if (pipe(pipe_) == -1) exit(1);

    proc1 = fork();
    if (proc1 == -1) exit(1);
    if (proc1)
    {
        close(pipe_[0]);
        while (scanf("%" SCNd32, &k))
            write(pipe_[1], &k, 4);
        close(pipe_[1]);
    }
    proc2 = fork();
    if (proc2 == -1) exit(1);
    if (proc2)
    {
        close(pipe_[1]);
        int64_t sum = 0;
        while (read(pipe_[0], &k, 4))
                sum += k;
        close(pipe_[1]);

        printf("%" PRId64, sum);
        fflush(stdout);
        exit(0);
    }
    wait(NULL);
    wait(NULL);
    exit(0);
    return 0;
}