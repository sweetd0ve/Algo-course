#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    float x0 = strtof(argv[1], NULL);
    float (*f) (float);
    void *p = NULL;

    for (int i = 2; i < argc - 1; i += 2) {
        if (i > 2)
        {
            if ((strcmp(argv[i], "-") != 0) && p)
            {
            dlclose(p);
            p = dlopen(argv[i], RTLD_LAZY);
            }
        }
        else p = dlopen(argv[i], RTLD_LAZY);
        if (!p) continue;
        f = dlsym(p, argv[i + 1]);
        if (dlerror() != NULL) continue;
        x0 = (*f)(x0);
    }

    if (p) dlclose(p);
    printf("%.6g\n", x0);

    return 0;
}