#include <stdio.h>
#include <inttypes.h>
#include <ctype.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

const int mode1 = 1, mode2 = 2, mode3 = -1;
volatile  int mode = mode1;

void handler(int sig_num) 
{
    if (sig_num == SIGUSR1) mode = mode1;
    else if (sig_num == SIGUSR2) mode = mode2;
    else if (sig_num == SIGTERM) mode = mode3;
}

int main(int argc, char * argv [])
{
    struct sigaction action = {};
    action.sa_flags = SA_RESTART;
    action.sa_handler = handler;

    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    sigaction(SIGTERM, &action, NULL);

    sigset_t current;
    sigset_t last;

    sigemptyset(&current);

    sigaddset(&current, SIGUSR1);
    sigaddset(&current, SIGUSR2);
    sigaddset(&current, SIGTERM);

    sigprocmask(SIG_BLOCK, &current, &last);

    printf("%d\n", getpid());
    fflush(stdout);

    int one = 0, two = 0;

    while (1) {
        while (!mode)
            sigsuspend(&last);

        if (mode == -1)
            _exit(0);

        if (mode == 2) {
            ++two;
        } else {
            printf("%d %d\n", one, two);
            fflush(stdout);
            ++one;
        }

        mode = 0;
    }
}