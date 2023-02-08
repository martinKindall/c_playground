#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 80
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

int parse(char* args[MAX_LINE/2 + 1], char str[MAX_LINE]);

int main(void) {

    char* args[MAX_LINE/2 + 1];
    char str[MAX_LINE];
    char last_command[MAX_LINE] = {0};
    int should_run = 1;
    int pid;

    while (should_run) {
        printf(YEL "código morsa > " RESET);
        fflush(stdout);

        fgets(str, MAX_LINE, stdin); 
        str[strcspn(str, "\n")] = 0;   // trim newline

        if (strcmp(str, "!!") == 0) {
            if (last_command[0] != 0) {
                sprintf(str, "%s", last_command);
                printf("%s\n", last_command);
            } else {
                printf("No commands in history\n");
                continue;
            }
        } else if (strcmp(str, "") != 0) {
            sprintf(last_command, "%s", str);
        }

        int n_spaces = parse(args, str);

        pid = fork();

        if (pid == 0) {
            int fd = -1;
            if (n_spaces > 2 && strcmp(args[n_spaces-2], "<") == 0) {
                fd = open(args[n_spaces-1], O_RDONLY);
                close(0);
                dup(fd);
                args[n_spaces-2] = args[n_spaces-1] = NULL;
            } else if (n_spaces > 2 && strcmp(args[n_spaces-2], ">") == 0) {
                fd = open(args[n_spaces-1], O_WRONLY | O_CREAT, 0666);
                close(1);
                dup(fd);
                args[n_spaces-2] = args[n_spaces-1] = NULL;
            } else if (n_spaces > 2 && strcmp(args[n_spaces-2], "|") == 0) {
                int p[2];
                pipe(p);

                char* childCommand = args[n_spaces-1];
                char* nestArgs[2] = {childCommand, NULL};
                if (fork() == 0) {
                    close(0);
                    dup(p[0]);
                    close(p[1]);
                    execvp(childCommand, nestArgs);
                    close(p[0]);
                } else {
                    close(1);
                    dup(p[1]);
                    close(p[0]);
                    args[n_spaces-2] = args[n_spaces-1] = NULL;
                    execvp(args[0], args);
                    close(p[1]);
                    wait(NULL);
                }

                return 0;
            }

            execvp(args[0], args);

            if (fd != -1) close(fd);
            return 0;
        } else {
            wait(NULL);
        }
    }

    return 0;
}

/*
    We should not declare str[] as a local variable here
    otherwise it dies on the stack return and produces a 
    leaky reference.
    One way to solve that is using malloc, but this way works 
    too and we don't have to deal with freeing memory.
*/
int parse(char* args[MAX_LINE/2 + 1], char str[MAX_LINE]) {

    char* p = strtok(str, " ");  

    int n_spaces = 0;

    while (p) {
        args[n_spaces++] = p;

        p = strtok(NULL, " ");
    }

    args[n_spaces] = NULL;   // end of array

    return n_spaces;
}
