#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main(void) {

    char* args[MAX_LINE/2 + 1];
    int should_run = 1;
    int pid;

    while (should_run) {
        printf("morsa>");
        fflush(stdout);

        char str[MAX_LINE];

        fgets(str, MAX_LINE, stdin); 
        str[strcspn(str, "\n")] = 0;   // trim newline

        char* p = strtok(str, " ");
        int n_spaces = 0;

        while (p) {
            args[n_spaces++] = p;

            p = strtok (NULL, " ");
        }

        args[n_spaces] = NULL;   // end of array

        pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
        } else {
            wait(NULL);
        }
    }

    return 0;
}