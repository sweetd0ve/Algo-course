#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

int main(int argc, char ** argv) {
    char * dir = getenv("XDG_RUNTIME_DIR");
    if (!dir)
        dir = getenv("TMPDIR");
    if (!dir)
        dir = "/tmp/";

    char p[PATH_MAX];
    strcpy(p, dir);    
    strcat(p, "/");

    int pid = (int)getpid();
    char name[sizeof(int) + 2];
    sprintf(name, "%d", pid);
    strcat(p, name);
    strcat(p, ".py");
//    printf("%s\n", p);
    
    int fd = creat(p, 0700);

    char *str = "#!/usr/bin/env python3\nfrom sys import argv\nimport os\nprint(";
    write(fd, str, strlen(str) * sizeof(char));
    
    for (size_t i = 1; i < argc; i++) {
        write(fd, argv[i], strlen(argv[i]) * sizeof(char));
        if (i != argc - 1)
            write(fd, " * ", 3 * sizeof(char));
    }
    
    str = ")\nos.remove(argv[0])\n";
    write(fd, str, strlen(str) * sizeof(char));
//    printf("%ld\n", strlen(str) * sizeof(char));
    close(fd);

    execlp(p, p, NULL);
}