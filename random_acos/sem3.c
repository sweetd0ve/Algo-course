#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{
    char *p;
    int32_t val1 = (int32_t)strtol(argv[1], &p, 9);
    int32_t val2 = (int32_t)strtol(argv[2], &p, 9);
    int32_t ans = 0;
    printf("%d\n",  __builtin_add_overflow(val1, val2, &ans));
    if (val2 == 0) printf("1\n");
    else printf("0\n");
    return 0;
}