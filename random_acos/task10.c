#include <stdio.h>
#include <inttypes.h>
#include <ctype.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

const int mode1 = 1, mode2 = 2;
volatile  int mode = mode1;

void handler(int sig_num)
{
    if (sig_num == SIGUSR1) mode = mode1;
    else if (sig_num == SIGUSR2) mode = mode2;
}

int main(int argc, char * argv[])
{
    printf("%d\n", getpid());
    fflush(stdout);

    struct  sigaction sig_act;
    sig_act.sa_handler = handler;  
    sigemptyset(&sig_act.sa_mask);           
    sig_act.sa_flags = SA_RESTART;

    sigaction(SIGUSR1, &sig_act, NULL);
    sigaction(SIGUSR2, &sig_act, NULL);


    int64_t x = 0;
    while (scanf("%" SCNd64, &x) == 1)
    {
        if (mode == mode1)
            printf("%" PRId64 "\n", -x);
        else if (mode == mode2) 
            printf("%" PRId64 "\n", (int64_t) (x * x));
        fflush(stdout);
    }



    return 0;
}
