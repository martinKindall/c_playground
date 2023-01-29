
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MSGSIZE 16
char* msg = "hello, world!";

int main() {

    char inbuf[MSGSIZE];
    int p[2], pid, nbytes;

    if (pipe(p) < 0) {
        exit(1);
    }

    pid = fork();

    if (pid > 0) {
        close(p[0]);
        write(p[1], msg, MSGSIZE);
        close(p[1]);

        wait(NULL);
    } else if (pid == 0) {
        close(p[1]);

        while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0)
            printf("%s\n", inbuf);

        if (nbytes != 0)
            exit(2);

        close(p[0]);
        printf("Finished reading\n");
    }

    return 0;
}
